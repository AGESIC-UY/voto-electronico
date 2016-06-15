<?php
    #         ____
    #        / __/________  ___        ____ _____ _   __
    #       / /_ / ___/ _ \/ _ \______/ __ `/ __ \ | / /
    #      / __// /  /  __/  __/_____/ /_/ / /_/ / |/ /
    #     /_/  /_/   \___/\___/      \__, /\____/|___/   > http://free-gov.org
    #                               /____/
    #
    #  This file is part of 'Free-gov' - modules/aux/selectplus.inc
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


if ((isset($_FG['request'][2])) && (strpos($_FG['request'][2],'?')===FALSE) && (strpos($_FG['request'][2],'_removefilter')===FALSE) && (strlen($_FG['request'][2])>6)) $_SESSION['tmp_modal_params'] = FG_decode($_FG['request'][2]);

//var_dump ($_SESSION['tmp_modal_params']);
//FG_render ('template_iframed'); 

//if (strlen($_SESSION['tmp_modal_params'])<4) {  echo '...'; FG_render ('template_iframed'); } // close with empty content

$_FG['render']['extrahead'] .= "<script type=\"text/javascript\">
function closemymodal(ValueShow, ValueHide) { parent.document.getElementById('{$_SESSION['tmp_modal_params']['name']}').value = ValueHide;  parent.document.getElementById('{$_SESSION['tmp_modal_params']['name']}_show').value = ValueShow;  parent.jQuery.fancybox.close(); return false; }
</script>\n";

echo <<<EOF
<h1>Seleccionar elemento para insertar en el formulario</h1>
EOF;

        if (isset($_SESSION['tmp_modal_params']['labels'])) $params['labelslist'] = $_SESSION['tmp_modal_params']['labels']; else $params['labelslist'] = array ('Nombre'=>0);
        if (isset($_SESSION['tmp_modal_params']['fields'])) $params['fieldslist'] = $_SESSION['tmp_modal_params']['fields']; else $params['fieldslist'] = array('name');
        if (isset($_SESSION['tmp_modal_params']['fieldsearch'])) $params['fieldsearch'] = $_SESSION['tmp_modal_params']['fieldsearch']; else $params['fieldsearch'] = array('name'=>'Nombre');

        $params['searchtable']   = $_SESSION['tmp_modal_params']['searchtable']; //'stock_stock';


        $params['controls']      = array ('modal');
       //// $params['substitutions'] = array ('category'=>'stock_prodfamilies', 'subcategory'=>'stock_subprodfamilies', 'measureunit'=>'stock_measureunits');
      
        if (isset($_SESSION['tmp_modal_params']['crud_add'])) $params['crud_add']= $_SESSION['tmp_modal_params']['crud_add'];
        else $params['crud_no_add'] = TRUE; 


        if (isset($_SESSION['tmp_modal_params']['orderby']))  $params['orderby'] = $_SESSION['tmp_modal_params']['orderby']; else $params['orderby'] = 'name';
        if (isset($_SESSION['tmp_modal_params']['substitutions']))  $params['substitutions'] = $_SESSION['tmp_modal_params']['substitutions']; else $params['substitutions'] = array();


        FG_list ($params);
   

    FG_render ('template_iframed'); // Uses an empty output environment


      
