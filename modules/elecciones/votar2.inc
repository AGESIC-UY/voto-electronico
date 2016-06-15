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


include (CORE_PATH . '/lib/id_document_uy.php'); // funciones de chequeo de cedula de identidad uruguaya

// Verifica que el método sea POST, de lo contrario hay un error
if ($_SERVER['REQUEST_METHOD']!='POST') { FG_error ('Llamada incorrecta, no acceda directamente a este elemento.'); }

// Verifica integridad de datos
if (strlen($_POST['apellidos'])<2) { FG_error ('Llamada incorrecta: falta apellido'); }
if (strlen($_POST['nombres'])<2) { FG_error ('Llamada incorrecta: falta nombre'); }

         $badreplace = array('á', 'é', 'í', 'ó', 'ú', 'A', 'E', 'I', 'O', 'U');
         $badsearch  = array('à', 'è', 'ì', 'ò', 'ù', 'À', 'È', 'Ì', 'Ò', 'Ù');

         $_POST['apellidos'] =  str_replace ($badsearch, $badreplace, trim(ucwords(strtolower($_POST['apellidos'])))); 
         $_POST['nombres']   =  str_replace ($badsearch, $badreplace, trim(ucwords(strtolower($_POST['nombres'])))); 

         
if ((strlen($_POST['numerocedula'])>0)&&(strlen($_POST['numerocredencial'])>0)) { FG_error ('No puede votar con Cédula de Identidad y Credencial Cívica a la vez'); }

if ((strlen($_POST['numerocedula'])<8)&&(strlen($_POST['numerocredencial'])<1)) { FG_error ('Para votar debe ingresar Cédula de Identidad o Credencial Cívica'); }

if (strlen($_POST['numerocredencial'])>6) { FG_error ('Verifique el número de Credencial (' . $_POST['numerocredencial'] . ')'); }




// VOTA CON CEDULA, elimina la serie de credencial
if (strlen($_POST['numerocedula'])>7) { $_POST['seriecredencial']=''; $_POST['numerocredencial']=''; 

    // Verificación y normalización de cédula de identidad
    $documento = compactcedula($_POST['numerocedula']);
    if (!verifycedula($documento))     FG_error ('El número de Documento de Identidad (' . $documento . ') contiene errores');
    if (!chkdigitcedula($documento))   FG_error ('El número de Documento de Identidad no es real (' . $documento . '). Verifíquelo.');
    $_POST['numerocedula'] = $documento;
    
    
    // Verifico que esta cedula no haya votado ya
        $result0 = mysqli_query($_FG['db0'], "SELECT * FROM `elecciones_votos` WHERE `numerocedula`='$documento' LIMIT 1;"); 
        $numresults0 = mysqli_num_rows($result0);
        if ($numresults0>0)
        {
           $fila0 = mysqli_fetch_assoc($result0);
           $documento2 = inflatecedula($documento);
           FG_error ("Esta persona ya <b>votó a la hora {$fila0['hora']}</b> usando su <b>Cédula de Identidad $documento2</b>...");
        }    
}
// VOTA CON CREDENCIAL
else {

    $_POST['numerocredencial'] = trim($_POST['numerocredencial']);
    if (!ctype_digit($_POST['numerocredencial'])) { FG_error ('Numero de credencial incorrecto. Verifíquelo.'); }

    // Verifico que la serie sea valida
    if (strlen($_POST['seriecredencial'])!=3)    { FG_error ('Serie de credencial incorrecta (' . $_POST['seriecredencial'] . '). Verifíquela.'); }
    if (!ctype_alpha($_POST['seriecredencial'])) { FG_error ('Serie de credencial incorrecta (' . $_POST['seriecredencial'] . '). Verifíquela.'); }
     $_POST['seriecredencial'] = strtoupper($_POST['seriecredencial']);
    $result0b = mysqli_query($_FG['db0'], "SELECT * FROM `elecciones_serieshab` WHERE `name`='{$_POST['seriecredencial']}' LIMIT 1;"); 
        $numresults0b = mysqli_num_rows($result0b);
        if ($numresults0b<1)
        {
           FG_error ('Esta serie de credencial no está habilitada (' . $_POST['seriecredencial'] . ').');
        }
        else
        {
        $fila0b = mysqli_fetch_assoc($result0b);
        $_POST['seriecredencialnr'] = $fila0b['id']; // tomo el id de la serie de credencial de la tabla elecciones_serieshab
        }


    // Verifico que esta credencial no haya votado ya
        $result01 = mysqli_query($_FG['db0'], "SELECT * FROM `elecciones_votos` WHERE `seriecredencial`='{$_POST['seriecredencialnr']}' AND `numerocredencial`='{$_POST['numerocredencial']}' LIMIT 1;"); 
        $numresults01 = mysqli_num_rows($result01);
        if ($numresults01>0)
        {
           $fila01 = mysqli_fetch_assoc($result01);
           $credencial =  $fila0b['name'];// FG_id2name('elecciones_serieshab',  $_POST['seriecredencial']);

           FG_error ("Esta persona ya <b>votó a la hora {$fila01['hora']}</b> usando su Credencial <b>$credencial  {$_POST['numerocredencial']}</b>...");
        } 



}













if (strlen($_POST['votando'])<1) {  // Muestro el formulario, ya que no es el POST de voto final

$_FG['render']['extrahead'] .= <<<EOF
<style type="text/css">
.btn {
  background: #cfecff;
  background-image: -webkit-linear-gradient(top, #cfecff, #44abeb);
  background-image: -moz-linear-gradient(top, #cfecff, #44abeb);
  background-image: -ms-linear-gradient(top, #cfecff, #44abeb);
  background-image: -o-linear-gradient(top, #cfecff, #44abeb);
  background-image: linear-gradient(to bottom, #cfecff, #44abeb);
  -webkit-border-radius: 4;
  -moz-border-radius: 4;
  border-radius: 4px;
  font-family: Arial;
  color: #000000;
  font-size: 15px;
  padding: 6px 6px 6px 6px;
  text-decoration: none;
}
.btn:hover {
  background: #fc3c3c;
  background-image: -webkit-linear-gradient(top, #fc3c3c, #d93434);
  background-image: -moz-linear-gradient(top, #fc3c3c, #d93434);
  background-image: -ms-linear-gradient(top, #fc3c3c, #d93434);
  background-image: -o-linear-gradient(top, #fc3c3c, #d93434);
  background-image: linear-gradient(to bottom, #fc3c3c, #d93434);
  text-decoration: none;
}
.btn:active {
  background: #ff0000;
  background-image: -webkit-linear-gradient(top, #ff0000, #870000);
  background-image: -moz-linear-gradient(top, #ff0000, #870000);
  background-image: -ms-linear-gradient(top, #ff0000, #870000);
  background-image: -o-linear-gradient(top, #ff0000, #870000);
  background-image: linear-gradient(to bottom, #ff0000, #870000);
  text-decoration: none;
}
</style>
EOF;


echo <<<EOF
<div id="confirmVoted" title="Confirmación de voto">
<p><span class="ui-icon ui-icon-circle-close" style="float:left; margin:0 7px 20px 0;"></span> 
 ¿confirma que desea votar esta lista?</p></div>
 
<script type="text/javascript">
$("#confirmVoted").dialog({ modal: true, bgiframe: true, width: 400, height: 200, autoOpen: false, draggable: false, resizable: false }); 
function confirmVote() {   $('#confirmVoted').dialog('option', 'buttons', { "Cancelar": function() { $(this).dialog("close"); },
"Votar": function() { document.form1.submit(); }  }); $('#confirmVoted').dialog('open'); return false; }

function UpdateVoteField(value) { $('input[name=voto]').val(value); }
</script>

<h1>Pantalla del votante: seleccione su voto</h1>
<center>
<form action="votar2" method="POST" id="form1" name="form1" enctype="multipart/form-data" onsubmit="return confirmVote();"><input type="hidden" name="MAX_FILE_SIZE" value="700000"><input type="hidden" name="apellidos" value="{$_POST['apellidos']}"><input type="hidden" name="nombres" value="{$_POST['nombres']}"><input type="hidden" name="numerocedula" value="{$_POST['numerocedula']}"><input type="hidden" name="seriecredencial" value="{$_POST['seriecredencial']}"><input type="hidden" name="seriecredencialnr" value="{$_POST['seriecredencialnr']}"><input type="hidden" name="numerocredencial" value="{$_POST['numerocredencial']}"> <input type="hidden" name="votando" value="votando!">
<input type="hidden" name="voto" value="voto">
<table width=830 cellpadding=2 cellspacing=2 border=0 id="listtable">
<thead>
<tr>
<td height=30 align="center" bgcolor="#CFCFFF" colspan=2><b>Seleccione la lista que desea votar, haciendo click sobre la misma</b></td>
</tr>
</tr></thead><tbody>
EOF;

        $result = mysqli_query($_FG['db0'], 'SELECT * FROM `elecciones_listas` ORDER BY `id` ASC;'); 
        $numresults = mysqli_num_rows($result);
        if ($numresults<1)
        {
           FG_error ('No se cargaron listas en el sistema!');
        }
        else // hay votos emitidos
        {
               $indexbuffer=0;
               $buffer = array();
               while($fila = mysqli_fetch_assoc($result)) {
        
               $buffer[$indexbuffer] = $fila['name']; if ($indexbuffer==0) { $indexbuffer=1; }
               else {
               $indexbuffer=0;
echo <<<EOF
<tr>
<td align="left" bgcolor="#eeeeee" width="50%"><b> &nbsp; &nbsp; &nbsp; <input onclick="UpdateVoteField(this.value)" type="submit" class="btn" name="votobt" value="$buffer[0]"></b></td>
<td align="left" bgcolor="#eeeeee" width="50%"><b> &nbsp; &nbsp; &nbsp; <input onclick="UpdateVoteField(this.value)" type="submit" class="btn" name="votobt" value="$buffer[1]"></b></td>
</tr>
EOF;
                    }
	       }
	       if ($indexbuffer==1) { // imprimimos la ultima lista huerfana impar
echo <<<EOF
<tr>
<td align="left" bgcolor="#eeeeee" width="50%"><b> &nbsp; &nbsp; &nbsp; <input onclick="UpdateVoteField(this.value)" type="submit" class="btn" name="votobt" value="$buffer[0]"></b></td>
<td align="left" bgcolor="#eeeeee" width="50%"><b> &nbsp; &nbsp; &nbsp; </b></td>
</tr>
EOF;
	       }
        }

echo <<<EOF
<tr>
<td height=15 align="center" bgcolor="#dddddd" colspan=2> &nbsp; </td>
</tr>
</tbody></table>
</center></form>
EOF;
}




else { // Vino $_POST['votando'].  Tomo los datos finales para registrar en la base de datos
/*
echo $_POST['apellidos'] . ' <br>';
echo $_POST['nombres'] . ' <br>';
echo $_POST['numerocedula'] . ' <br>';
echo $_POST['seriecredencial'] . ' <br>';
echo $_POST['numerocredencial'] . ' <br>';
echo $_POST['voto'] . ' <br>';
*/

$name = $_POST['nombres'] . ' ' . $_POST['apellidos'];
date_default_timezone_set ('America/Montevideo');
$hora = date('H:i:s');
$usuariosesion = $_SESSION['user_id'];

$result3 = mysqli_query($_FG['db0'], "SELECT * FROM `elecciones_listas` WHERE `name`= '{$_POST['voto']}' LIMIT 1;"); 
        $numresults = mysqli_num_rows($result3);
        if ($numresults<1)
        {
           FG_error ('No se identifica la lista votada');
        }
        else { $fila3 = mysqli_fetch_assoc($result3); $voto = $fila3['id']; }


if (strlen($_POST['seriecredencialnr'])<1) {$_POST['seriecredencialnr'] = 'NULL';}

$result2 = mysqli_query($_FG['db0'], "INSERT INTO `elecciones_votos` (`name`, `apellidos`, `nombres`, `numerocedula`, `seriecredencial`, `numerocredencial`, `hora`, `usuariosesion`, `voto`) VALUES ('$name', '{$_POST['apellidos']}', '{$_POST['nombres']}', '{$_POST['numerocedula']}', {$_POST['seriecredencialnr']}, '{$_POST['numerocredencial']}', '$hora', $usuariosesion, $voto )");

//echo "INSERT INTO `elecciones_votos` (`name`, `apellidos`, `nombres`, `numerocedula`, `seriecredencial`, `numerocredencial`, `hora`, `usuariosesion`, `voto`) VALUES ('$name', '{$_POST['apellidos']}', '{$_POST['nombres']}', '{$_POST['numerocedula']}', {$_POST['seriecredencialnr']}, '{$_POST['numerocredencial']}', '$hora', $usuariosesion, $voto )";


FG_ok ('Su voto fue realizado con éxito', '/elecciones/votosmesa');
}


