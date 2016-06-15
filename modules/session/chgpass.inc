<?php
    #         ____
    #        / __/________  ___        ____ _____ _   __
    #       / /_ / ___/ _ \/ _ \______/ __ `/ __ \ | / /
    #      / __// /  /  __/  __/_____/ /_/ / /_/ / |/ /
    #     /_/  /_/   \___/\___/      \__, /\____/|___/   > http://free-gov.org
    #                               /____/
    #
    #  This file is part of 'Free-gov' - .htaccess
    #
    #  This file is part of 'Free-gov' - modules/session/chgpass.inc
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
<br><br><br>
<h2>Cambio de password...</h2>
<form name="loginform" id="loginform" style="margin-bottom:0; margin-top:0;" action="/session/chgpass" method="POST" enctype="multipart/form-data">
<table cellpadding=2 cellspacing=2 border=0 width=370>
<tr><td colspan=2 align="center" bgcolor="#efefef">Usuario: &nbsp; <b>{$_SESSION['user_realname']}</b></td></tr>
<tr><td width=150 align="right">Password actual:</td><td width=210> &nbsp; &nbsp; <input type="password" name="pass1" id="pass1" value="" size=25 maxlength=40 class="validate[required,minSize[6]] form"></td></tr>
<tr><td width=150 align="right">Password nuevo:</td><td width=210> &nbsp; &nbsp; <input type="password" name="pass2" id="pass2" value="" size=25 maxlength=16
class="validate[required,minSize[6]] form"></td></tr>
<tr><td width=150 align="right">Password nuevo (2):</td><td width=210> &nbsp; &nbsp; <input type="password" name="pass3" id="pas3" value="" size=25 maxlength=16
class="validate[required,equals[pass2]] form"></td></tr>
<tr><td width=370 colspan=2 align="right" valign="middle"><br>
<table width=190 cellpadding=3 cellspacing=3 border=0><tr>
<td valign="middle" align="right"><a href="javascript:document.forms[0].reset()" onclick="$('#loginform').validationEngine('hideAll')" title="clean form fields"><img width=24 height=24 src="/images/session/editdelete.png" border=0></a></td><td > &nbsp; </td>
<td valign="top" align="left"><input type="submit" name="btn" value=" &nbsp; cambiar password &nbsp; " style="padding:3px;"></td>
</tr></table></td></tr>
</table><br></form>
EOF;

    $waitpage = <<<EOF
<br><br><br><br>
<h2>Cambio de password...</h2>
&nbsp; &nbsp; &nbsp; &nbsp; aguarde mientras se procesa su petición...
<br><br><br>
<center><img src="/images/session/bar.gif" width=200 height=10></center>
<br><br>
EOF;

    $errorpage = <<<EOF
<br><br><br><br>
<h2>Error en cambio de password...</h2>
&nbsp; &nbsp; &nbsp; &nbsp; La información suministrada es incorrecta...<br> 
&nbsp; &nbsp; &nbsp; &nbsp; Verifique sus datos e <a href="/session/chgpass">intente nuevamente</a>.
<br><br>
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; <img src="/images/session/dialog-cancel.png" width=48 height=48>
EOF;

    $errornonewpass = <<<EOF
<br><br><br><br>
<h2>Error en cambio de password...</h2>
&nbsp; &nbsp; &nbsp; &nbsp; Ud. no está poniendo un nuevo password...<br> 
&nbsp; &nbsp; &nbsp; &nbsp; Verifique sus datos e <a href="/session/chgpass">intente nuevamente</a>.
<br><br>
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; <img src="/images/session/dialog-cancel.png" width=48 height=48>
EOF;

    $successchange = <<<EOF
<br><br><br><br>
<h2>Password cambiado con éxito</h2>
&nbsp; &nbsp; &nbsp; &nbsp; Su password fue cambiado exitosamente.<br> 
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;<a href="/">continuar con la sesión...</a>.
<br><br><br><br><br><br>
EOF;


  // If called by POST method, we must process login
    if ($_SERVER['REQUEST_METHOD'] == 'POST') {
         
         FG_escapePOST();
         
        // check minimum password length
        if ((strlen($_POST['pass1']) < 6) || (strlen($_POST['pass2']) < 6) || (strlen($_POST['pass3']) < 6) ) {
            FG_error("Error updating password for user {$_SESSION['user_name']}: CHGPASSFAIL...");
        }
         
        // check if pass2 equals pass3
        if ($_POST['pass2'] != $_POST['pass3']) {
            FG_error("Error updating password for user {$_SESSION['user_name']}: NO EQUALPASS...");
        }
         
        // check if pass1 equals pass2
        if ($_POST['pass1'] == $_POST['pass2']) {
            FG_redirect('/session/chgpass/errornonewpass', 4);
            FG_log ('CHGPASSFAIL', "NO NEWPASS for user {$_SESSION['user_name']}");
            loginscreen($waitpage);
        }
         
         
        $superhash1 = sha1(md5($_POST['pass1']));
         
        $result = mysqli_query($_FG['db0'], "SELECT * FROM `acl_users` WHERE `id`='{$_SESSION['user_id']}' AND `cryptpass`='$superhash1'");
        if (mysqli_num_rows($result) < 1) {
            $_POST['pass1'] = mysqli_real_escape_string($_FG['db0'], $_POST['pass1']); // only if login fail, to store on logs
            $_POST['pass2'] = mysqli_real_escape_string($_FG['db0'], $_POST['pass2']);
            FG_redirect('/session/chgpass/error', 4);
            FG_log ('CHGPASSFAIL', "BADOLDPASS - username: {$_POST['name']} - pass1: {$_POST['pass1']} - pass2: {$_POST['pass2']}");
        } else {
            // SUCCESSFULL PASSWORD CHANGE
            $newhash = sha1(md5($_POST['pass2']));
            mysqli_query($_FG['db0'], "UPDATE `acl_users` SET `cryptpass` = '$newhash' WHERE `id`='{$_SESSION['user_id']}'");
            if (mysqli_affected_rows($_FG['db0']) < 1) {
                FG_error("Error updating password for user {$_SESSION['user_name']}...");
            }
            FG_log ('CHGPASOK', "username: {$_POST['name']} - userid={$_SESSION['user_id']}");
            FG_redirect('/session/chgpass/success', 4);
        }
        loginscreen($waitpage);
    }
     
    // If called with just two parameters, we show form
    if (($_SERVER['REQUEST_METHOD'] == 'GET') && !isset($_FG['request'][2])) {
        loginscreen($formpage);
    }
     
    // If called with $_FG['request'][2]=='error', we show error message
    if (($_SERVER['REQUEST_METHOD'] == 'GET') && $_FG['request'][2] == 'error') {
        loginscreen($errorpage);
    }
     
    // If called with $_FG['request'][2]=='success', we show success message
    if (($_SERVER['REQUEST_METHOD'] == 'GET') && $_FG['request'][2] == 'success') {
        loginscreen($successchange);
    }
     
    // If called with $_FG['request'][2]=='errornonewpass', we show error message
    if (($_SERVER['REQUEST_METHOD'] == 'GET') && $_FG['request'][2] == 'errornonewpass') {
        loginscreen($errornonewpass);
    }
     
     
    // show composed screen
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

        FG_render();
    }


 


