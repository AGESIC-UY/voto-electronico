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


// Verifica el método sea  GET para mostrar el formulario
if ($_SERVER['REQUEST_METHOD']!='POST') {


$_FG['table']          = 'elecciones_votos'; // nombre de la table mysql
//$_FG['edittitle']      = '<h1>Modificar datos</h1>'; // título de la pantalla cuando estamos editando datos
$_FG['newregtitle']    = '<h1>Seleccionar Circuito a escrutar</h1>'; // título de la pantalla cuando ingresamos nuevo registro
//$_FG['editbutton']     = 'Confirmar modificación'; // Texto del boton del formulario cuando estamos en modo edicion
$_FG['newregbutton']   = 'Confirmar';  // Texto del boton del formulario cuando estamos ingresando un nuevo registro

// Este es un formulario que no sigue los estandares free-gov.org
FG_form_start ('form1', 'POST', 'escrutiniocircuito');

  $listacircuitos = FG_mkselect ('elecciones_circuitos', $_FG ['updateinfo']['circuito']); 
  FG_form_select ('circuito', 'Circuito:', $listacircuitos);

FG_form_submit ('submit', '', $_FG['buttontext']);

}



// Verifica el método sea  POST para mostrar los resultados
else {

        if ((strlen($_POST['circuito'])<1)||(!is_numeric($_POST['circuito']))) { FG_error ('Llamada incorrecta: falta circuito, o tiene valor incorrecto'); }
        
        $nombrecircuito = FG_id2name ('elecciones_circuitos', $_POST['circuito']);
        
        
echo <<<EOF
<h1>Escrutinio Circuital</h1>
<center><b>$nombrecircuito</b> &nbsp; &nbsp; &nbsp; &nbsp; - &nbsp; &nbsp; &nbsp; &nbsp; <a href="escrutiniocircuito">Cambiar a otro circuito</a></center><br>
EOF;
        
        // Detecta funcionarios asignados al circuito
        $result0 = mysqli_query($_FG['db0'], "SELECT `userid` FROM `elecciones_funcionarios` WHERE `circuito`={$_POST['circuito']};"); 
        $numresults0 = mysqli_num_rows($result0);
        if ($numresults0<1)
        {
           FG_error ('No se puede hacer escrutinio si no configura los circuitos y funcionarios a cargo.');
        }
        else // hay funcionarios
        {
        $wherefuncionario = ' WHERE (';
        $flagor = 0;
        while($fila0 = mysqli_fetch_assoc($result0)) { if ($flagor==1) { $wherefuncionario .= ' OR ';} $wherefuncionario .= "`usuariosesion`={$fila0['userid']} ";  $flagor=1; }
        $wherefuncionario .= ') ';
        }


        // configura resumen general
        $result = mysqli_query($_FG['db0'], "SELECT `id` FROM `elecciones_votos` $wherefuncionario;"); 
        $numresults = mysqli_num_rows($result);
        mysqli_free_result($result);
        if ($numresults<1)
        {
           echo "<br><b> &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; Aún no hay votos en el sistema.<b><br><br><br><br><br><br><br>";
        }
        else // hay votos emitidos
        {
        
        // hora del primer voto
        $result2 = mysqli_query($_FG['db0'], 'SELECT `hora` FROM `elecciones_votos` ' . $wherefuncionario . ' ORDER BY `hora` ASC LIMIT 1;');
        $fila2 = mysqli_fetch_assoc($result2);
        $hora2 = $fila2['hora'];
        mysqli_free_result($result2);

        // hora del ultimo voto
        $result3 = mysqli_query($_FG['db0'], 'SELECT `hora` FROM `elecciones_votos` ' . $wherefuncionario . ' ORDER BY `hora` DESC LIMIT 1;');
        $fila3 = mysqli_fetch_assoc($result3);
        $hora3 = $fila3['hora'];
        mysqli_free_result($result3);


        
echo <<<EOF
<center>
<table width=830 cellpadding=2 cellspacing=2 border=0 id="listtable">
<thead>
<tr>
<td height=30 valign="middle" align="center" bgcolor="#dddddd" width=60 colspan=5><b>Total votos en circuito: $numresults</b> &nbsp; &nbsp; <b>Primer voto recibido hora:</b> $hora2  &nbsp; &nbsp; <b>Ultimo voto recibido hora:</b> $hora3 </td>
</tr>
<tr>
<td height=30 align="center" bgcolor="#CFCFFF" width=500><b>LISTA</b></td><td align="center" bgcolor="#CFCFFF"><b>VOTOS</b></td>
</tr>
</tr></thead><tbody>
EOF;
        

        // Busca las listas participantes, para hacer un recuento de votos para cada una de ellas
        $result4 = mysqli_query($_FG['db0'], 'SELECT * FROM `elecciones_listas` ORDER BY `id` ASC;'); 
        $numresults4 = mysqli_num_rows($result4);
        if ($numresults4<1)
        {
           FG_error ('No se puede hacer escrutinio si no configura las listas.');
        }
        else // hay listas, se hace conteo de votos para cada una de ellas
        {
       
           while($fila4 = mysqli_fetch_assoc($result4)) {  
           
             $numresults5 = 0;
             $result5 = mysqli_query($_FG['db0'], "SELECT `id` FROM `elecciones_votos` $wherefuncionario AND `voto`={$fila4['id']};");
             $numresults5 = mysqli_num_rows($result5);
             mysqli_free_result($result5);    
             renglon ($numresults5, $fila4['name']); 
           }        
             renglon ("<font color='#cc0000'>$numresults</font>", "<font color='#cc0000'><b>  &nbsp; &nbsp;  &nbsp; &nbsp; VOTOS TOTAL TODAS LAS LISTAS EN ESTE CIRCUITO</b></font>"); 
        }
        

echo <<<EOF
<tr>
<td height=15 align="center" bgcolor="#dddddd" colspan=5> &nbsp; </td>
</tr>
</tbody></table>
</center>
EOF;

        }

}        





///////////////////////////////////////////////////////////////////////
function renglon   ($cantvotos, $nombrelista) {

echo <<<EOF
<tr>
<td align="left" bgcolor="#eeeeee" width=500>&nbsp; &nbsp; &nbsp; $nombrelista</td><td align="left" bgcolor="#eeeeee" width=400> &nbsp; &nbsp; &nbsp; &nbsp; <b>$cantvotos</b></td>
</tr>
EOF;

}



      






