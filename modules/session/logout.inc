<?php
    #         ____
    #        / __/________  ___        ____ _____ _   __
    #       / /_ / ___/ _ \/ _ \______/ __ `/ __ \ | / /
    #      / __// /  /  __/  __/_____/ /_/ / /_/ / |/ /
    #     /_/  /_/   \___/\___/      \__, /\____/|___/   > http://free-gov.org
    #                               /____/
    #
    #  This file is part of 'Free-gov' - modules/session/logout.inc
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
     
    // TODO: add diferent messages and logging for each logout reason: timeout, IP change and natural logout
     
    if ($_FG['request'][2] == 'idle') {
        FG_log('LOGOUTINACTIVE', "userid: {$_SESSION['user_id']}");
        $msg = ' por inactividad';
    }
    else if ($_FG['request'][2] == 'changedip') {
        $msg = ' (cambió su IP)';
    } else {
        FG_log('LOGOUTOK', "userid: {$_SESSION['user_id']}");
    }
     
    $waitpage = <<<EOF
<br><br><br><br>
<h2>Cierre del sistema{$msg}...</h2>
&nbsp; &nbsp; &nbsp; &nbsp; aguarde mientras se cierra su sesión
<br><br><br>
<center><img src="/images/session/bar.gif" width=200 height=10></center>
<br><br>
EOF;

    if (isset($_SESSION['user_id'])) {
        unset ($_SESSION['user_id']);
    } // delete 'id'
       
    @$_SESSION = array(); // empty $_SESSION array
     
    @session_destroy(); // can guess what happen here...     
    // CAUTION: cookie name (FREE-GOV2) must be configured at php.ini
    setcookie ('FREE-GOV2', '', time() - 42000); // rewrite cookie
    //setcookie ('FREE-GOV2', '', time() - 42000, '/', BASE_URL);

     
    FG_redirect ('/', 4); // go home...
     
    loginscreen($waitpage);
     
     
     
    // show the composed screen
    /////////////////////////////////////////////////////////
    function loginscreen ($rightbox) {
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
 
