<?php
    #
    #   VOTO ELECTRONICO - Software para elecciones - SOFTWARE PUBLICO URUGUAYO
    # 
    #  Creado en el Municipio de Maldonado (http://www.municipiomaldonado.gub.uy)
    #  por Iris Montes de Oca (http://www.irismontesdeoca.com)
    #  en la plataforma de Gobierno Electr�nico Free-gov (http://free-gov.org)
    #    
    #  Este Software de distribuye bajo los t�rminos de la Licencia AGPL 3
    #  El texto de la licencia AGPL se encuentra an el archivo 'license.txt'
    #  (en idioma ingl�s), en el mismo paquete de distribuci�n de este software.
    #
    #  El cumpliminto internacional de la Licencia AGPL requiere la inclusi�n
    #  del siguiente bloque de licenciamiento en idioma ingl�s, en cada archivo:
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
    
//IMPORTANTE: tambien hay que editar abajo, la URL de retorno del formulario luego del ingreso
$_FG['table']          = 'elecciones_votos'; // nombre de la table mysql
//$_FG['edittitle']      = '<h1>Modificar datos</h1>'; // t�tulo de la pantalla cuando estamos editando datos
$_FG['newregtitle']    = '<h1>Ingresar Datos de Votante</h1>'; // t�tulo de la pantalla cuando ingresamos nuevo registro
//$_FG['editbutton']     = 'Confirmar modificaci�n'; // Texto del boton del formulario cuando estamos en modo edicion
$_FG['newregbutton']   = 'Pasar a pantalla del votante';  // Texto del boton del formulario cuando estamos ingresando un nuevo registro


        // elabora la lista de series, para informar
        $result0 = mysqli_query($_FG['db0'], "SELECT * FROM `elecciones_serieshab`;"); 
        $numresults0 = mysqli_num_rows($result0);
        if ($numresults0<1)
        {
           FG_error ('No se puede procesar votos si no hay series de credencial habilitadas.');
        }
        else // hay series habilitadas
        $series = ' ';
        {
        while($fila0 = mysqli_fetch_assoc($result0)) {  $series .= "{$fila0['name']} "; }
        }


// Este es un formulario que no sigue los estandares free-gov.org
FG_form_start ('form1', 'POST', 'votar2');

FG_form_text ('apellidos', 'Apellidos del votante:', $_FG ['updateinfo']['apellidos'], 'required,minSize[2]'); 
FG_form_text ('nombres', 'Nombres del votante:', $_FG ['updateinfo']['nombres'], 'required,minSize[2]'); 


FG_form_container ('', ' ', ' &nbsp; &nbsp; <span style="color:red;font-size:larger;"><b>Usar C�dula de Identidad s�lo para votantes entre 16 y 18 a�os:</b></span><br>');
FG_form_text ('numerocedula', 'C�d. Identidad (sin puntos ni guion):', $_FG ['updateinfo']['numerocedula'], "custom[integer]");

FG_form_container ('', ' ', ' &nbsp; &nbsp; <span style="color:red;font-size:larger;"><b>Usar Credencial C�vica s�lo para votantes mayores de 18 a�os:</b></span><br>');
FG_form_container ('', ' ', " S�lo pueden votar las series $series");

FG_form_text ('seriecredencial', 'Serie de Credencial C�vica:', $_FG ['updateinfo']['seriecredencial'], "custom[onlyLetterSp],minSize[3],maxSize[3]");

/*
$series = FG_mkselect ('elecciones_serieshab', $_FG ['updateinfo']['seriecredencial']);
FG_form_select ('seriecredencial', 'Serie de Credencial C�vica:', $series);
*/

FG_form_text ('numerocredencial', 'N�mero de Credencial C�vica:', $_FG ['updateinfo']['numerocredencial'], "custom[integer]");  
  
FG_form_submit ('submit', '', $_FG['buttontext']);


if ($_FG['is_reception']){

}


