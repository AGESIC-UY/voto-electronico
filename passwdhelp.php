<?php
    #         ____
    #        / __/________  ___        ____ _____ _   __
    #       / /_ / ___/ _ \/ _ \______/ __ `/ __ \ | / /
    #      / __// /  /  __/  __/_____/ /_/ / /_/ / |/ /
    #     /_/  /_/   \___/\___/      \__, /\____/|___/   > http://free-gov.org
    #                               /____/
    #
    #  This file is part of 'Free-gov' - modules/session/passwdhelp.inc
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
     
$_FG['render']['main'] = <<<EOF
<center><table width="95%" cellpadding=0 cellspacing=0 border=0><tr>
<td width="50%" align="left" valign="bottom"><img src="/images/uy.png">  &nbsp; <img src="/images/logoweb.png"></td>
<td width="50%" align="right" valign="bottom">
<img src="/images/gnu_logo.png"> <img src="/images/osi.png"> &nbsp; &nbsp;<img src="/images/agpl.png"></td></tr></table></center><br>
<h2>Este es un Sistema de Gobierno Electrónico (Voto Electrónico)</h2><br>
<b>El Sistema de Voto Electrónico es Software Público Uruguayo, desarrollado en el Muncipio de Maldonado
</b>.<br>Licencia: <a href="https://es.wikipedia.org/wiki/GNU_Affero_General_Public_License">AGPL 3</a>. &nbsp; Por
consultas comunicarse con <a href="http://www.municipiomaldonado.gub.uy" target="_blank" title="Municipio de
Maldonado">http://www.municipiomaldonado.gub.uy</a>.<br>Este Software puede ser usado y adaptado sin costos de
licencia en cualquier organización pública o privada.<br><br>
<h2>Acerca de la Plataforma Free-gov</h2>
<div align="justify"><br>"<b>Free-gov</b>" es la plataforma de <b>Software Libre</b> sobre la cual se 
programó este Sistema. <b>Free-gov</b> es una organización  internacional sin fines de lucro 
(<a href="http://free-gov.org" target="_blank" title="Free-gov is the first e-Government free software
platform">http://free-gov.org</a>), que desarrolla una plataforma de Software Libre para Gobierno Electrónico,
disponible  sin costos de licencias y libremente para todos los gobiernos del mundo.</div>
EOF;

   include ('template_iframed.html');
     
