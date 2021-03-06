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
$_FG['table']          = 'elecciones_listas'; // nombre de la table mysql
$_FG['edittitle']      = '<h1>Modificar datos de Lista</h1>'; // t�tulo de la pantalla cuando estamos editando datos
$_FG['newregtitle']    = '<h1>Ingresar nueva Lista</h1>'; // t�tulo de la pantalla cuando ingresamos nuevo registro
$_FG['editbutton']     = 'Confirmar modificaci�n'; // Texto del boton del formulario cuando estamos en modo edicion
$_FG['newregbutton']   = 'Ingresar Lista';  // Texto del boton del formulario cuando estamos ingresando un nuevo registro


FG_form_start ('form1'); // as� se empiezan todos los formularios
FG_form_text ('name', 'Nombre de Lista/Propuesta:', $_FG ['updateinfo']['name'], 'required,minSize[2]'); //campo texto: nombre del campo,tiqueta,valor, valida

  
FG_form_submit ('submit', '', $_FG['buttontext']);


if ($_FG['is_reception']){

    if ($_FG['is_update']){
        $retorno = FG_dbupdate ($_FG['table'], $_FG['form1']);
        if ($retorno==FALSE) FG_error ('No se realiz� ninguna modificaci�n de datos');
        else FG_ok ('Se modifico el registro', $_SESSION['pageback']);
    }
    else {
        $retorno = FG_dbinsert ($_FG['table'], $_FG['form1'] );
        if ($retorno==FALSE) FG_error ('No se pudo ingresar el registro');
        else FG_ok ('Se insert� nuevo registro', '/elecciones/listas');
    }
}


