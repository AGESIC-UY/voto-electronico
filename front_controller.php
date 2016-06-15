<?php
    #         ____
    #        / __/________  ___        ____ _____ _   __
    #       / /_ / ___/ _ \/ _ \______/ __ `/ __ \ | / /
    #      / __// /  /  __/  __/_____/ /_/ / /_/ / |/ /
    #     /_/  /_/   \___/\___/      \__, /\____/|___/   > http://free-gov.org
    #                               /____/
    #
    #  This file is part of 'Free-gov' - http-root/front_controller.php
    #
    #  Free-gov - e-government free software system
    #  Copyright (C) 2011 Iris Montes de Oca <http://www.irismontesdeoca.com>
    #  Copyright (C) 2011 Eduardo Glez <http://www.eduardoglez.com>
    #
    #  Free-gov is free software; you can redistribute it and/or modify
    #  it under the terms of the GNU Affero General Public License as published
    #  by the Free Software Foundation; either version 3 of the License, or
    #  (at your option) any later version.
    #
    #  Free-gov is distributed in the hope that it will be useful,
    #  but WITHOUT ANY WARRANTY; without even the implied warranty of
    #  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    #  GNU Affero General Public License for more details.
    #
    #  You should have received a copy of the GNU Affero General Public License
    #  along with Free-gov: see the file 'license.txt'.  If not, write to
    #  the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
    #  Boston, MA 02111-1307, USA.
    #
    #   Authors: Iris Montes de Oca <http://www.irismontesdeoca.com>
    #            Eduardo Glez <http://www.eduardoglez.com>
    #  Internet: http://free-gov.org
    #
    #  Registered in the United States Copyright Office on May 18, 2011
    #  Registration Number at the Library of the Congress of the USA: TXu001756584
    #
     
    // Default paths. Optionally you may change values to fit your installation
    define('PUBLIC_PATH', dirname(__FILE__));
    // Front-controller, templates, html stuff
    define('BASE_PATH', PUBLIC_PATH); //  just used to compose CORE_PATH & MODULES_PATH
    define('CORE_PATH', BASE_PATH . '/free-gov-core'); // Configuration & system files
    define('MODULES_PATH', BASE_PATH . '/modules');
    // Free-gov modules
     
    // Set various headers to avoid caching
    header('Expires: Tue, 03 Jul 2001 06:00:00 GMT'); // date in the past
    header('Last-Modified: ' . gmdate('D, d M Y H:i:s') . ' GMT');
    header('Cache-Control: no-store, no-cache, must-revalidate');
    header('Cache-Control: post-check=0, pre-check=0', false);
    header('Pragma: no-cache');
     
    // Include core functions, configuration file, db connection, etc.
    include (CORE_PATH . '/core.inc');
    
    // Clean HTTP inputs against hackers (XSS and SQL nasty injection attemps)
    FG_escapePOST(); FG_escapeGET();
     
    // Request URL elements will be available in $_FG['request'][0], $_FG['request'][1] ... $_FG['request'][n]
    $_FG['request'] = explode('/', rtrim(ltrim($_SERVER['REQUEST_URI'], '/'), '/'));
    
    ob_start(); // Start capturing 'level 0' output buffer stack
     
    // SESION START/RESTART (disable following line if values were set in your custom php.ini)
    session_name('FREE-GOV2'); ini_set('session.cookie_httponly',1); ini_set('session.cookie_secure',1);
    if (!session_start(['cookie_httponly'=>TRUE,'cookie_secure'=>TRUE])) // redundant cookie security setting
        FG_error('Imposible iniciar sesión en front_controller...');
         
    if (isset($_SESSION['user_id'])) $FGreq2 = 'main';
     else $FGreq2 = 'session';
    if (strlen($_FG['request'][0]) < 1) $_FG['request'][0] = $FGreq2;
    // default values if no request parameters
    if (strlen($_FG['request'][1]) < 1) $_FG['request'][1] = 'index';
     
    // Control if user is properly loged in
    if ((!isset($_SESSION['user_id'])) && !($_FG['request'][0] == 'session' && $_FG['request'][1] == 'index')) FG_redirect('/');
     
    // Control if possible Session hijacking
    if (isset($_SESSION['user_id'])) {
        if ($_SESSION['user_ip'] != $_SERVER['REMOTE_ADDR']) {
            FG_log('CHANGEDIP', 'userid: ' . $_SESSION['user_id'] . 'old ip: ' . $_SESSION['user_ip'] . ' - new ip: ' . $_SERVER['REMOTE_ADDR']);
            FG_redirect('/session/logout/changedip');
        }
    }
     
    // Check ACL permissions to access current requested resource
    if (isset($_SESSION['user_id'])) {
        if (!in_array('admin', $_SESSION['acl_groups'])) {
            if (!in_array('/' . $_FG['request'][0] . '/' . $_FG['request'][1], $_SESSION['acl_available_res'])) {
                FG_log('ACLVIOLATION', 'userid: ' . $_SESSION['user_id'] . ' ip: ' . $_SERVER['REMOTE_ADDR'] . ' res: /' .$_FG['request'][0] .  '/' . $_FG['request'][1] . '/' . $_FG['request'][2] );
                FG_redirect('/session/logout');
            }
        }
    }
     
    // RESTORE MENU FROM SESSION TO RENDER SEGMENT ['render']['menu']
    if (strlen($_SESSION['menu']) > 10) $_FG['render']['menu'] = $_SESSION['menu'];
     
    // if module/operation folder/file exists, is included  << Most of the magic happen HERE !!
    $FG_mainfile = MODULES_PATH . '/' . $_FG['request'][0] . '/' . $_FG['request'][1] . '.inc';
    if (file_exists($FG_mainfile)) include ($FG_mainfile);
        else FG_error ('El <b>módulo/operación</b> requerido no existe: <b>' . $_FG['request'][0] . '/' . $_FG['request'][1] . '/' . $_FG['request'][2] . '</b>...');
     
    FG_render(); // main render in normal system flow
     
     
    /////////////////////////////////////////////////////////////////////
    // MAIN FUNCTIONS ( identified by namespace prefix 'FG_' )
     
    // Render page using specified template
    /////////////////////////////////////////////////////////////////////
    function FG_render ($template = 'template_default' ) {
        global $_FG;
        $_FG['render']['main'] = ob_get_contents();
         ob_end_clean();
        $templatefile = PUBLIC_PATH . '/' . $template . '.html';
        if (file_exists($templatefile)) include ($templatefile );
        else {FG_error ('La plantilla requerida (' . $template . ') no existe...');}
        flush();
        exit;
    }
     
    // Show error page, discarding previous buffered contents
    /////////////////////////////////////////////////////////////////////
    function FG_error ($message, $errorclass = 'ORDINARYERROR') {
        ob_end_clean();
        ob_start(); // discard previous content of output buffer
        include (PUBLIC_PATH . '/template_sub_error.html');
        FG_log ($errorclass, $message);
        FG_render ();
    }
     
    // Show OK confirmation page, discarding previous buffered contents
    /////////////////////////////////////////////////////////////////////
    function FG_ok ($message, $redirect, $timeout = 3) {
        ob_end_clean();
        ob_start(); // discard previous content of output buffer
        include (PUBLIC_PATH . '/template_sub_ok.html');
        FG_redirect ($redirect, $timeout);
        FG_render ();
    }

    // Clean page redirection with optional timeout
    /////////////////////////////////////////////////////////////////////
    function FG_redirect ($location, $timeout = 0) {
        if ($timeout == 0) header('Location: ' . $location);
            else header('refresh:' . $timeout . ';url=' . $location );
    }
     
