<?php
    #         ____
    #        / __/________  ___        ____ _____ _   __
    #       / /_ / ___/ _ \/ _ \______/ __ `/ __ \ | / /
    #      / __// /  /  __/  __/_____/ /_/ / /_/ / |/ /
    #     /_/  /_/   \___/\___/      \__, /\____/|___/   > http://free-gov.org
    #                               /____/
    #
    #  This file is part of 'Free-gov' - modules/session/index.inc
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
     
     
    // this is the form
    $formpage = <<<EOF
<br><br><br><br>
<h2>Ingreso al sistema...</h2>
<form name="loginform" id="loginform" style="margin-bottom:0; margin-top:0;" action="/session/index" method="POST" enctype="multipart/form-data">
<table cellpadding=2 cellspacing=2 border=0 width=300><br> 
<tr><td width=90 align="right">Usuario: &nbsp; <img src="/images/list/1/user-trans.png" width=16 height=16></td><td width=210> <input type="text" autocomplete="off" autocorrect="off" name="name" id="name" value="" size=25 maxlength=40 class="validate[required,minSize[6]] formfield_short"></td></tr>
<tr><td width=90 align="right">Password: &nbsp; <img src="/images/list/1/key-trans.png" width=16 height=16></td><td width=210> <input type="password" autocomplete="off" autocorrect="off" name="pass" id="pass" value="" size=25 maxlength=16
class="validate[required,minSize[6]] formfield_short"></td></tr>
<tr><td width=300 colspan=2 align="right" valign="middle"><br>
<table width=130 cellpadding=3 cellspacing=3 border=0><tr>
<td valign="middle" align="right"><a href="javascript:document.forms[0].reset()" onclick="$('#loginform').validationEngine('hideAll')" title="vaciar formulario"><img width=24 height=24 src="/images/session/editdelete.png" border=0></a></td><td > &nbsp; </td>
<td valign="top" align="left"><input type="submit" name="btn" value=" &nbsp; Ingresar &nbsp; " style="padding:3px;"></td></tr>
</table>
<br>
<a href="/passwdhelp" class="modal tth" title="Información sobre cómo obtener ayuda">¿Necesita ayuda?</a> &nbsp; <a href="/passwdhelp" class="modal tth" title="Detalles acerca del Software SISTEMA DE VOTO ELECTRÓNICO">Acerca del VOTO ELECTRÓNICO</a> &nbsp; &nbsp; 
</td></tr>
</table></form>
EOF;

    $waitpage = <<<EOF
<br><br><br><br>
<h2>Ingresando al sistema...</h2>
&nbsp; &nbsp; &nbsp; &nbsp; aguarde mientras se procesa su ingreso
<br><br><br>
<center><img src="/images/session/bar.gif" width=200 height=10></center>
<br><br>
EOF;

    $errorpage = <<<EOF
<br><br><br><br>
<h2>Error de ingreso al sistema...</h2>
&nbsp; &nbsp; &nbsp; &nbsp; Alguno de los datos requeridos es erróneo o incompleto.<br> 
&nbsp; &nbsp; &nbsp; &nbsp; Verifique su información e <a href="/">intente nuevamente</a>.
<br><br>
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; <img src="/images/session/dialog-cancel.png" width=48 height=48>
EOF;


  
    // If called by POST method, we must process login
    if ($_SERVER['REQUEST_METHOD'] == 'POST') {
 
        // Clean received data. don't clean $_POST['pass'] 'cause will be hashed
        $_POST['name'] = mysqli_real_escape_string($_FG['db0'], $_POST['name']); 
        $superhash = sha1(md5($_POST['pass']));
 
        // check minimum username and password length
        if ((strlen($_POST['name']) < 6) || (strlen($_POST['pass']) < 6)) {
            $_POST['pass'] = mysqli_real_escape_string($_FG['db0'], $_POST['pass']); // only if login fail to store on logs
            FG_redirect('/session/index/e99008846853ff3b725c27315e469fbc', 4);
            FG_log ('LOGINFAIL', "NO MIN LEN - username: {$_POST['name']} - pass: {$_POST['pass']}");
        }
        // check max username and password length, in case of attack
        if ((strlen($_POST['name']) > 40) || (strlen($_POST['pass']) > 16)) {
            $_POST['pass'] = mysqli_real_escape_string($_FG['db0'], $_POST['pass']); // only if login fail to store on logs
            FG_redirect('/session/index/e99008846853ff3b725c27315e469fbc', 4);            
            FG_log ('HACKERATTACK', "> MAX LEN - username: {$_POST['name']} - pass: {$_POST['pass']}");
        }        
                                   
        $result = mysqli_query($_FG['db0'], "SELECT * FROM `acl_users` WHERE username='{$_POST['name']}' AND cryptpass='$superhash' LIMIT 0,1");
        if (mysqli_num_rows($result) < 1) {
            $_POST['pass'] = mysqli_real_escape_string($_FG['db0'], $_POST['pass']); // only if login fail to store on logs
            FG_redirect('/session/index/e99008846853ff3b725c27315e469fbc', 4);
            FG_log ('LOGINFAIL', "username: {$_POST['name']} - pass: {$_POST['pass']}");
        } else {
 
            // SUCCESSFUL LOGIN 
            $currentCookieParams = session_get_cookie_params();  
            $sidvalue = session_id();  
            /*
            setcookie(  
                'FREE-GOV2',//name  
                 $sidvalue,//value  
                 0,//expires at end of session  
                 $currentCookieParams['path'],//path  
                 $currentCookieParams['domain'],//domain  
                 true, //secure
                 true // httponly
                 ); 
            */
         
            $buf = mysqli_fetch_assoc($result);
             mysqli_free_result($result);
            $_SESSION['user_id'] = $buf['id'];
            $_SESSION['user_realname'] = $buf['realname'];
            $_SESSION['user_ip'] = $_SERVER['REMOTE_ADDR'];
             
             
            // RETRIEVE ACL INFORMATION FOR THIS USER
            // metagroups
            $result = mysqli_query($_FG['db0'], "SELECT * FROM `acl_users2metagroups` WHERE `user`={$_SESSION['user_id']}");
            if (mysqli_num_rows($result) > 0) {
                while ($row = mysqli_fetch_assoc($result)) {
                    $result2 = mysqli_query($_FG['db0'], "SELECT * FROM `acl_metagroups2groups` WHERE `metagroup`='{$row['metagroup']}'");
                    if ($result2) {
                        if (mysqli_num_rows($result2) > 0) {
                            while ($row2 = mysqli_fetch_assoc($result2)) $_SESSION['acl_groups'][] = $row2['group'];
                        }
                    }
                }
                @mysqli_free_result($result);
                @mysqli_free_result($result2);
            }
            // groups
            $result = mysqli_query($_FG['db0'], "SELECT * FROM `acl_users2groups` WHERE `user`={$_SESSION['user_id']}");
            if (mysqli_num_rows($result) < 1) {
                // if ACL ERROR in user confiruration (no group assigned)
                $_SESSION = array();
                session_destroy();
                FG_error("NO ACL GROUPS ASSIGNED FOR USER {$buf['id']}", 'ACLFAIL');
            }
            while ($row = mysqli_fetch_assoc($result)) $_SESSION['acl_groups'][] = $row['group'];
             @mysqli_free_result($result);
             
            $_SESSION['acl_groups'] = array_unique($_SESSION['acl_groups']); // delete possible group duplications
             
            // resources list for this user
            $_SESSION['acl_available_res'] = array();
            foreach($_SESSION['acl_groups'] as $group ) {
                $result = mysqli_query($_FG['db0'], "SELECT * FROM `acl_groups2res` WHERE `group`='$group'");
                if (mysqli_num_rows($result) > 0) {
                    while ($row = mysqli_fetch_assoc($result)) {
                        // populate pre-menu array
                        if (strlen($row['menu_group']) > 0) {
                            $menutmp["{$row['menu_group']}"][] = array($row['menu_caption'], "/{$row['module']}/{$row['operation']}");
                        }
                         
                        // revoke negative permissions
                        if ($row['negative'] == 0) {
                            $_SESSION['acl_available_res'][] = "/{$row['module']}/{$row['operation']}";
                        } else {
                            if (($k = array_search("/{$row['module']}/{$row['operation']}", $_SESSION['acl_available_res'])) !== FALSE) {
                                unset($_SESSION['acl_available_res'][$k]);
                                 unset($k);
                            }
                        }
                    }
                }
            }
             
            //$_SESSION['acl_menutmp'] = $menutmp;
             
            // ACL-FREE MODULES. THESE MODULES WILL BE AVAILABLE FOR ALL USERS
            $_SESSION['acl_available_res'][] = '/session/index';
            $_SESSION['acl_available_res'][] = '/session/chgpass';
            $_SESSION['acl_available_res'][] = '/session/logout';
            $_SESSION['acl_available_res'][] = '/session/keepalive';
            $_SESSION['acl_available_res'][] = '/photos/t';
            $_SESSION['acl_available_res'][] = '/photos/';
            $_SESSION['acl_available_res'][] = '/userfiles/';
            $_SESSION['acl_available_res'][] = '/main/index';
            $_SESSION['acl_available_res'][] = '/aux/barcode';
            $_SESSION['acl_available_res'][] = '/aux/qrcode';
            $_SESSION['acl_available_res'][] = '/aux/selectplus';
            $_SESSION['acl_available_res'][] = '/aux/multiphoto';
            $_SESSION['acl_available_res'][] = '/aux/webcam';
            $_SESSION['acl_available_res'][] = '/aux/webcam-save';
            $_SESSION['acl_available_res'][] = '/main/' . $_SESSION['acl_groups'][0];
             
             
            // COMPOSE MENU FOR THIS USER ***************************************************************************
             
            function columnmenu ($inputarray) {
                $columns = array();
                $n = 1;
                foreach ($inputarray as $element) {
                    $columns[$n][] = $element;
                    $n++;
                    if ($n > 5) $n = 1;
                }
                for ($i = 1; $i < 5; $i++) {
                    if (!is_array($columns[$i])) break;
                    $ret .= '<div class="col_1"><p>';
                    foreach ($columns[$i] as $item) {
                        $ret .= '<img src="/images/bullet.gif" alt="" width=4 height=7> <a href="' . $item[1] . '">' . $item[0] . '</a><br>';
                    }
                    $ret .= '</p></div>';
                }
                return $ret . '<hr>';
            }
             

            if (is_array($menutmp)) {
                $menu = '';
                 
                //$menu = var_export($menutmp, TRUE);

                foreach ($menutmp as $categorytitle => $category) {
                    $menu .= '<div class="col_5"><h3>' . $categorytitle . '</h3></div>';
                    $menu .= columnmenu ($category);
                    $menu .= '<div class="col_5"><br><hr></div>';
                }
                 
            } else {
                $menu = "no se asignaron permisos para este usuario...";
            }
               
            $_SESSION['menu'] = <<<EOF
<div class="row">
<div class="column grid_12"><ul id="menu">
<li><img src="/images/menubut-trans.png" width=80 height=28 alt="" class="imgmenu"><div class="dropdown_5columns">
<div class="col_5"> <h2>Menú de sistema de {$_SESSION['user_realname']}</h2></div>
$menu
</div><!-- End 5 columns container --></li><li><a class="menutxt" href="/" title="Pantalla de Inicio">Inicio</a></li><li><a class="menutxt" href="/session/chgpass" title="Cambiar su password">Cambiar password</a></li><li><a class="menutxt" title="Terminar la sesión" href="javascript:void(0)" onclick="confirmExit();">Salir</a></li><li><span class="menutxt2">|</span>  &nbsp; &nbsp; <span class="menutxt2">Usuario actual: <i>{$_SESSION['user_realname']}</i></span></li></ul>
</div>
</div>
EOF;
	      FG_log ('LOGINOK', "username: {$_POST['name']}");
	      FG_log ('LOGINOK', "userid: {$_SESSION['user_id']} username: {$_POST['name']}");
	      FG_redirect('/', 4); 
	  }

        loginscreen($waitpage); // loginscreen() is last operation, 'cause kills script execution
    }


    // If called with just two parameters, we show login form
    if (($_SERVER['REQUEST_METHOD'] == 'GET') && !isset($_FG['request'][2])) {
        loginscreen($formpage);
    }
     
    // If called with three parameters, we show error message
    if (($_SERVER['REQUEST_METHOD'] == 'GET') && isset($_FG['request'][2])) {
        loginscreen($errorpage);
    }
     
     
    // show the composed screen
    /////////////////////////////////////////////////////////
    function loginscreen ($rightbox) {
        global $_FG;
         
        $_FG['render']['extrahead'] .= <<<EOF
<script>
$(document).ready( function() { $("#loginform").validationEngine('attach'); });
</script>
EOF;

        echo <<<EOF
<br>
<center>
<table width=860 cellspacing=0 cellpadding=0 border=0><tr>
<td widht=400 align="right" valign="top"><img src="/images/session/secure.png" width=256 height=256 border=0><br><br>
</td><td width=40>&nbsp;</td><td width=420 valign="top" align="left">
$rightbox
</td></tr>
<tr>
<td widht=860 align="center" valign="middle" colspan=3>
<hr width="70%">
Este es un sistema de <b>GOBIERNO ELECTRONICO</b>. &nbsp; Por seguridad, sus acciones están siendo grabadas.
<hr width="70%">
</td>
</tr>
</table>
</center>
EOF;

        FG_render ('template_nomenu');  // Uses a template without menu bar to render login screens
    }


