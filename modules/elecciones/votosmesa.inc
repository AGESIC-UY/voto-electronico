<?php
    #
    #   VOTO ELECTRONICO - Software para elecciones - SOFTWARE PUBLICO URUGUAYO
    # 
    #  Creado en el Municipio de Maldonado (http://www.municipiomaldonado.gub.uy)
    #  por Iris Montes de Oca (http://www.irismontesdeoca.com)
    #  en la plataforma de Gobierno Electrónico Free-gov (http://free-gov.org)
    #    
    #  Este Software de distribuye bajo los términos de la Licencia AGPL 3
    #  El texto de la licencia AGPL se encuentra an el archivo 'license.txt'
    #  (en idioma inglés), en el mismo paquete de distribución de este software.
    #
    #  El cumpliminto internacional de la Licencia AGPL requiere la inclusión
    #  del siguiente bloque de licenciamiento en idioma inglés, en cada archivo:
    #
    #
    #  This file is part of 'VOTO ELECTRONICO' 
    #
    #  VOTO ELECTRONICO - Electronic Voting Software.
    #  Copyright (C) 2016 Iris Montes de Oca <http://www.irismontesdeoca.com>
    #  working with Municipio de Maldonado <http://www.municipiomaldonado.gub.uy>
    #
    #  VOTO ELECTRONICO is free software; you can redistribute it and/or modify
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
    #  Internet: http://www.municipiomaldonado.gub.uy/voto_electronico
    #
    #  This software is built on top of free-gov platform (http://free-gov.org)
    #
    
	include_once (CORE_PATH . '/lib/id_document_uy.php'); // funciones de chequeo de cedula de identidad uruguaya    
    
echo <<<EOF
<h1>Votos recepcionados bajo responsabilidad de <i>{$_SESSION['user_realname']}</i></h1>

<center>
<table width=830 cellpadding=2 cellspacing=2 border=0 id="listtable">
<tr><td align="right"><a href="votar">Emitir voto</a></td></tr>
</table></center>
EOF;



    $result = mysqli_query($_FG['db0'], 'SELECT * FROM `elecciones_votos` WHERE `usuariosesion`=' .   $_SESSION['user_id'] . ' ORDER BY `id` DESC;'); 
        $numresults = mysqli_num_rows($result);
        if ($numresults<1)
        {
           echo "<br><b> &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; Aún no hay votos emitidos bajo responsabilidad de este funcionario.<b><br><br><br><br><br><br><br>";
        }
        else // hay votos emitidos
        {
        
$result2 = mysqli_query($_FG['db0'], 'SELECT `hora` FROM `elecciones_votos` WHERE `usuariosesion`=' .   $_SESSION['user_id'] . ' ORDER BY `hora` ASC LIMIT 1;');
$fila2 = mysqli_fetch_assoc($result2);
$hora2 = $fila2['hora'];


$result3 = mysqli_query($_FG['db0'], 'SELECT `hora` FROM `elecciones_votos` WHERE `usuariosesion`=' .   $_SESSION['user_id'] . ' ORDER BY `hora` DESC LIMIT 1;');
$fila3 = mysqli_fetch_assoc($result3);
$hora3 = $fila3['hora'];

        
        
echo <<<EOF
<center>
<table width=830 cellpadding=2 cellspacing=2 border=0 id="listtable">
<thead>
<tr>
<td height=30 valign="middle" align="center" bgcolor="#dddddd" width=60 colspan=6><b>Total votos recepcionados por este responsable: $numresults</b> &nbsp; &nbsp; <b>Primer voto recibido hora:</b> $hora2  &nbsp; &nbsp; <b>Ultimo voto recibido hora:</b> $hora3 </td>
</tr>
<tr>
<td height=30 align="center" bgcolor="#CFCFFF" width=90><b>HORA</b></td><td align="center" bgcolor="#CFCFFF" width=394><b>VOTANTE</b></td><td align="center" bgcolor="#CFCFFF" width=90 ><b>CEDULA</b></td><td align="center" bgcolor="#CFCFFF" width=70><b>SERIE</b></td><td align="center" bgcolor="#CFCFFF" ><b>CREDENCIAL</b></td><td align="center" bgcolor="#CFCFFF" >&nbsp;</td>
</tr>
</tr></thead><tbody>
EOF;
        
          while($fila = mysqli_fetch_assoc($result)) {
               renglonvoto ($fila);
	       }

echo <<<EOF
<tr>
<td height=15 align="center" bgcolor="#dddddd" colspan=6> &nbsp; </td>
</tr>
</tbody></table>
</center>
EOF;

        }
        
        
        
///////////////////////////////////////////////////////////////////////
function renglonvoto ($filavoto) {

if (strlen($filavoto['seriecredencial'])>0) { $filavoto['seriecredencial'] = FG_id2name('elecciones_serieshab',$filavoto['seriecredencial'] ); }
else {$filavoto['seriecredencial'] = '-';}

if (strlen($filavoto['numerocedula'])<1)  {$filavoto['numerocedula'] = '-';} 
else { $filavoto['numerocedula'] = inflatecedula($filavoto['numerocedula']); }
if (strlen($filavoto['numerocredencial'])<1)  {$filavoto['numerocredencial'] = '-';}

$cryptolink = FG_encode($filavoto['id']);

echo <<<EOF
<tr>
<td align="center" bgcolor="#eeeeee" width=90>{$filavoto['hora']}</td><td align="left" bgcolor="#eeeeee" width=394> &nbsp; &nbsp; &nbsp; &nbsp; {$filavoto['name']}</td><td align="center" bgcolor="#eeeeee" width=90 >{$filavoto['numerocedula']}</td><td align="center" bgcolor="#eeeeee" width=70 >{$filavoto['seriecredencial']}</td><td align="center" bgcolor="#eeeeee" >{$filavoto['numerocredencial']}</td>
<td align="center" bgcolor="#eeeeee" ><a href="votosmesa_p/$cryptolink" title="Imprimir Comprobante de Voto" class="modalprint"><img src="/images/list/1/print-trans.png" width=16 height=16 border=0></a></td>
</tr>
EOF;

}        

