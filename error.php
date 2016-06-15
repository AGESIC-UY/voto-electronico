<?php
    #         ____
    #        / __/________  ___        ____ _____ _   __
    #       / /_ / ___/ _ \/ _ \______/ __ `/ __ \ | / /
    #      / __// /  /  __/  __/_____/ /_/ / /_/ / |/ /
    #     /_/  /_/   \___/\___/      \__, /\____/|___/   > http://free-gov.org
    #                               /____/
    #
    #  This file is part of 'Free-gov' - http-root/error.php
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
     
    // Set various headers to avoid caching
    header('Expires: Tue, 03 Jul 2001 06:00:00 GMT'); // date in the past
    header('Last-Modified: ' . gmdate('D, d M Y H:i:s') . ' GMT');
    header('Cache-Control: no-store, no-cache, must-revalidate');
    header('Cache-Control: post-check=0, pre-check=0', false);
    header('Pragma: no-cache');
     
    $strcode[400] = '<b>HTTP ERROR 400:</b> The request cannot be fulfilled due to bad syntax.';
    $strcode[401] = '<b>HTTP ERROR 401:</b> The request requires user authentication (username and a password).';
    $strcode[403] = '<b>HTTP ERROR 403:</b> Access is forbidden to the requested page.';
    $strcode[404] = '<b>HTTP ERROR 404:</b> The server can not find the requested page.';
    $strcode[500] = '<b>HTTP ERROR 500:</b> The request was not completed. The server met an unexpected condition.';
    $strcode[501] = '<b>HTTP ERROR 501:</b> The request was not completed. The server did not support the functionality required.';
     
    if (strlen($_GET['code']) != 3) $_GET['code'] = '404';
    if (!array_key_exists($_GET['code'], $strcode)) $_GET['code'] = '404';
    // if asking for a non-existent code, it's an error 404...
     
    $message = $strcode[$_GET['code']];
     
    ob_start();
    include ('template_sub_error.html');
    $_FG['render']['main'] = ob_get_contents();
     ob_end_clean();
    include ('template_nomenu.html');
    exit;
    