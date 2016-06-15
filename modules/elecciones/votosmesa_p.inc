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
<h1>Sistema de Voto Electrónico - Municipio de Maldonado</h1>
<div align="right"><form> &nbsp; &nbsp; &nbsp; <input id="printbutton" type="button" value="Imprimir comprobante" onClick="window.print()" /></form></div><br>
<center><b>CONSTANCIA DE VOTO EN ELECCIONES DE PRESUPUESTO PARTICIPATIVO</b></center><br>
EOF;

if (!isset($_FG['request'][2])) { echo '...'; FG_render ('template_iframed'); }
$id = FG_decode($_FG['request'][2]);  //echo $id;

    include_once(CORE_PATH . '/lists.inc');

    
    $votante = FG_dbget ('elecciones_votos', $id);
    
    if (strlen($votante['seriecredencial'])>0) { $votante['seriecredencial'] = FG_id2name('elecciones_serieshab',$votante['seriecredencial']); }
    if (strlen($votante['numerocedula'])>0) { $votante['numerocedula'] = inflatecedula($votante['numerocedula']); }    
    
echo <<<EOF
<center><table width=830 cellpadding=10 cellspacing=10 border=1>
<tr><td  align="left" width="100%" bgcolor="#EFEFFF" >
        <br><br>
&nbsp;  &nbsp; &nbsp; &nbsp; Se hace constar que <b>{$votante['name']}</b>, (Documento <b>{$votante['numerocedula']} {$votante['seriecredencial']}  {$votante['numerocredencial']}</b>)<br>
&nbsp;  &nbsp; &nbsp; &nbsp; emitió su voto en las Elecciones de Presupuesto Participativo del Municipio de Maldonado.<br><br>
&nbsp;  &nbsp; &nbsp; &nbsp; Maldonado, 10 de abril de 2016, <b>hora de emitido el voto: {$votante['hora']}</b>
        
        <br><br><br><br>
&nbsp;  &nbsp; &nbsp; &nbsp; ________________________<br>
&nbsp;  &nbsp; &nbsp; &nbsp; Firma Responsable de Circuito
        <br><br>
        </td></tr>
        </tbody></table></center>
EOF;

        
        //echo '<hr><center>' . $comments . 'CANTIDAD DE ITEMS: <b>' . $items . '</b> &nbsp; &nbsp; TOTAL PRODUCTOS ENTREGADOS: <b>' . $totalquantity ;
        //echo '</b><hr><br><br><br><br><br><hr>FIRMA DEL FUNCIONARIO &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; NUMERO DE FICHA </center>';        
    

 FG_render ('template_iframed');


