<?php
    #         ____
    #        / __/________  ___        ____ _____ _   __
    #       / /_ / ___/ _ \/ _ \______/ __ `/ __ \ | / /
    #      / __// /  /  __/  __/_____/ /_/ / /_/ / |/ /
    #     /_/  /_/   \___/\___/      \__, /\____/|___/   > http://free-gov.org
    #                               /____/
    #
    #  This file is part of 'Free-gov' - free-gov-core/forms.inc
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
    
    
    

    
    
     
    //////////////////////////////////////////////////////////////////////////
    function FG_form_prepare_radio () {
        // fieldname, checked, columns, rows [value, label] ... [value, label]
         
        if (func_num_args() < 6) return NULL;
        $args = func_get_args();
        $width = intval (100 / $args[2]); // make columns same size
        $k = 4;
        //first usable value
        $r = '<table cellpadding=3 cellspacing=0 border=0 width="100%" style="margin: 0 0 0 10px">';
        for($j = 0; $j < $args[3]; $j++) {
             $r .= '<tr>';
            for($i = 0; $i < $args[2]; $i++) {
                $val = $args[$k];
                 $lab = $args[$k+1];
                if ($val == $args[1]) $checked = ' checked ';
                else $checked = ''; // checked?
                if (isset($args[$k])) {
                    $input = "<input type=\"radio\" name=\"{$args[0]}\" value=\"$val\" $checked> $lab";
                }
                 else $input = '&nbsp;';
                $r .= "<td width=\"{$width}%\">$input</td>";
                $k += 2;
            }
            $r .= '</tr>';
        }
        $r .= '</table>';
        return $r;
    }
     
     
     
    //////////////////////////////////////////////////////////////////////////
    function FG_form_prepare_checkbox () {
        // fieldname, checked, columns, rows [value, label] ... [value, label]
         
        if (func_num_args() < 6) return NULL;
        $args = func_get_args();
        if (is_array($args[1])) $preloadvalues = TRUE;
        $width = intval (100 / $args[2]); // make columns same size
        $k = 4;
        //first usable value
        $r = '<table cellpadding=3 cellspacing=0 border=0 width="100%" style="margin: 0 0 0 10px">';
        for($j = 0; $j < $args[3]; $j++) {
             $r .= '<tr>';
            for($i = 0; $i < $args[2]; $i++) {
                $val = $args[$k];
                 $lab = $args[$k+1];
                if ($preloadvalues) {
                    if (in_array($val, $args[1])) $checked = ' checked ';
                    else $checked = '';
                }
                if (isset($args[$k])) {
                    $input = "<input type=\"checkbox\" name=\"{$args[0]}[]\" value=\"$val\" $checked> $lab";
                }
                 else $input = '&nbsp;';
                $r .= "<td width=\"{$width}%\">$input</td>";
                $k += 2;
            }
            $r .= '</tr>';
        }
        $r .= '</table>';
        return $r;
    }
     
        
    //////////////////////////////////////////////////////////////////////////
    function FG_form_hidden ($name, $label, $value, $checkrule = '') {
        global $_FG;
         
        if (!$_FG['is_reception']) {
            echo "<input type=\"hidden\" name=\"$name\" id=\"$name\" value=\"$value\">\n";
        } else {
            FG_form_validate($_FG['getpost'][$name], $name, 'required');
        } // hidden fields content must always exist
    }
     
    //////////////////////////////////////////////////////////////////////////
    function FG_form_text ($name, $label, $value, $checkrule = '') {
        global $_FG;
         
        if (!$_FG['is_reception']) {
            $FG_local_segment1 = FG_form_asterisk($checkrule) . $label;
            if (strlen($checkrule) > 0) $class = "validate[$checkrule] ";
            $FG_local_segment2 = "<input type=\"text\" name=\"$name\" id=\"$name\" value=\"$value\" class=\"{$class}formfield\">";
            include (PUBLIC_PATH . '/template_sub_formrow.html');
        } else {
            if (strlen($checkrule) > 0) FG_form_validate($_FG['getpost'][$name], $name, $checkrule);
        }
    }
     
    //////////////////////////////////////////////////////////////////////////
    function FG_form_textarea ($name, $label, $value, $checkrule = '') {
        global $_FG;
         
        if (!$_FG['is_reception']) {
            $FG_local_segment1 = FG_form_asterisk($checkrule) . $label;
            if (strlen($checkrule) > 0) $class = "validate[$checkrule] ";
            $FG_local_segment2 = "<textarea name=\"$name\" class=\"{$class}formfield\" id=\"$name\">$value</textarea>";
            include (PUBLIC_PATH . '/template_sub_formrow.html');
        } else {
            if (strlen($checkrule) > 0) FG_form_validate($_FG['getpost'][$name], $name, $checkrule);
        }
    }


    //////////////////////////////////////////////////////////////////////////
    function FG_form_textarea_editor ($name, $label, $value, $checkrule = '') {
        global $_FG;
         
        if (!$_FG['is_reception']) {
                if(!isset($_FG['ckeditor_flag'])) {
                    $_FG['ckeditor_flag'] = 1;  
                    $_FG['render']['extrahead'] .= '<script type="text/javascript" src="/ckeditor/ckeditor.js"></script>';
                }
            $FG_local_segment1 = FG_form_asterisk($checkrule) . $label;
            //if (strlen($checkrule) > 0) $class = "validate[$checkrule] ";
            $FG_local_segment2 = "<textarea name=\"$name\" class=\"ckeditor\" id=\"$name\">$value</textarea>";
            include (PUBLIC_PATH . '/template_sub_formrow.html');
        } else {
            if (strlen($checkrule) > 0) FG_form_validate($_FG['getpost'][$name], $name, $checkrule);
        }
    }
     
    //////////////////////////////////////////////////////////////////////////
    function FG_form_password ($name, $label, $value, $checkrule = '') {
        global $_FG;
         
        if (!$_FG['is_reception']) {
            $FG_local_segment1 = FG_form_asterisk($checkrule) . $label;
            if (strlen($checkrule) > 0) $class = "validate[$checkrule] ";
            $FG_local_segment2 = "<input type=\"password\" name=\"$name\" id=\"$name\" value=\"$value\" class=\"{$class}formfield\">";
            include (PUBLIC_PATH . '/template_sub_formrow.html');
        } else {
            if (strlen($checkrule) > 0) FG_form_validate($_FG['getpost'][$name], $name, $checkrule);
        }
    }


    //////////////////////////////////////////////////////////////////////////
    function FG_form_select ($name, $label, $value, $checkrule = '') {
        global $_FG;
         
        if (!$_FG['is_reception']) {
            $FG_local_segment1 = FG_form_asterisk($checkrule) . $label;
            if (strlen($checkrule) > 0) $class = "validate[$checkrule] ";
            $FG_local_segment2 = "<select name=\"$name\" id=\"$name\" class=\"{$class}formfield\">$value</select>";
            include (PUBLIC_PATH . '/template_sub_formrow.html');
        } else {
            if (strlen($checkrule) > 0) FG_form_validate($_FG['getpost'][$name], $name, $checkrule);
        }
    }

    
    //////////////////////////////////////////////////////////////////////////
    function FG_form_select_multiple ($name, $label, $value, $checkrule = '', $size=5) {
        global $_FG;
         
        if (!$_FG['is_reception']) {
            $FG_local_segment1 = FG_form_asterisk($checkrule) . $label;
            if (strlen($checkrule) > 0) $class = "validate[$checkrule] ";
            $FG_local_segment2 = "<select multiple=\"multiple\" name=\"{$name}[]\" id=\"$name\" class=\"{$class}formfield\" size=\"$size\">$value</select>";
            include (PUBLIC_PATH . '/template_sub_formrow.html');
        } else {
            if (strlen($checkrule) > 0) FG_form_validate($_FG['getpost'][$name], $name, $checkrule);
        }
    }    

    //////////////////////////////////////////////////////////////////////////
    function FG_form_select_plus ($name, $label, $parameters, $checkrule = '') {
        global $_FG;
         
        if (!$_FG['is_reception']) {
            $parameters['name'] = $name;
            if (isset($parameters['value'])) $value_show = FG_id2name($parameters['searchtable'], $parameters['value']);
            $codedparameters = FG_encode($parameters);

            $FG_local_segment1 = FG_form_asterisk($checkrule) . $label;
            if (strlen($checkrule) > 0) $class = "validate[$checkrule] ";
            $FG_local_segment2 =  "<input type=\"hidden\" name=\"$name\" id=\"$name\" value=\"{$parameters['value']}\">\n<input type=\"text\" disabled name=\"{$name}_show\" id=\"{$name}_show\" value=\"$value_show\" class=\"{$class}formfield_selectplus\"> &nbsp; &nbsp; <a href=\"/aux/selectplus/$codedparameters\" class=\"modal\" title=\"Buscar dato\"><img src=\"/images/list/2/magnifier-trans.png\" width=16 height=16></a> &nbsp; &nbsp; <a href=\"#\"  title=\"Vaciar este campo\" onClick=\"document.forms[0].{$name}_show.value=''; document.forms[0].{$name}.value=''; return false;\"><img src=\"/images/list/1/delete-trans.png\" width=16 height=16></a>";      

            include (PUBLIC_PATH . '/template_sub_formrow.html');
        } else {
            if (strlen($checkrule) > 0) FG_form_validate($_FG['getpost'][$name], $name, $checkrule); 
        }
    }




    //////////////////////////////////////////////////////////////////////////
    function FG_form_container ($name, $label, $value, $checkrule = '') {
        global $_FG;
         
        if (!$_FG['is_reception']) {
            $FG_local_segment1 = FG_form_asterisk($checkrule) . $label;
            if (strlen($checkrule) > 0) $class = "validate[$checkrule] ";
            $FG_local_segment2 = $value;
            include (PUBLIC_PATH . '/template_sub_formrow.html');
        }
    }

  
    //  "$name" is for reference only. This value is not included in form results array  
    //////////////////////////////////////////////////////////////////////////
    function FG_form_photo ($name, $label, $value, $photofolder, $width, $checkrule = '') {
        global $_FG;
         
        if (!$_FG['is_reception']) {
            $_FG['render']['extrahead'] .= '<script src="/js/fancyfileinput.js" type="text/javascript"></script>';
            $FG_local_segment1 = $label;
            $FG_local_segment2 = ' &nbsp; &nbsp; <span class="file-wrapper"><input type="file" id="' . $name . '" name="' . $name . '"><span class="button">Seleccionar una foto</span></span>';
            if((strlen($value)>0)&&(file_exists(PUBLIC_PATH . '/' . $photofolder .'/t/'. $value . '.jpg'))) {$FG_local_segment2 .= '<br> &nbsp; &nbsp; <img src="/' . $photofolder .'/t/'. $value .'.jpg">'; }
            include (PUBLIC_PATH . '/template_sub_formrow.html');
        }

        else { // move photo and name it as the session name
            if (is_uploaded_file($_FILES[$name]['tmp_name'])){
            if ($_FILES[$name]['error'] > 0) FG_error("Problema subiendo foto", 'FORMERROR');
            if (($_FILES[$name]['type'] != 'image/jpeg') && ($_FILES[$name]['type'] != 'image/pjpeg')) FG_error('Sólo se aceptan imágenes JPG', 'FORMERROR');

            $newname = session_id();  //str_replace( ' ' , '_', microtime()) . '.jpg';
            $newfilepath = PUBLIC_PATH . '/' . $photofolder . '/' . $newname;
            move_uploaded_file($_FILES[$name]['tmp_name'], $newfilepath);
            list($width_orig, $height_orig, $type, $attr) = getimagesize($newfilepath);
            $newheight = ($width * $height_orig) / $width_orig;          
            $image = imagecreatefromjpeg($newfilepath);
                // resize image if needed
                if ($width_orig != $width){
                $image_n = imagecreatetruecolor($width, $newheight);
                imagecopyresampled($image_n, $image, 0, 0, 0, 0, $width, $newheight, $width_orig, $height_orig);	
                unlink ($newfilepath);
                imagejpeg($image_n, $newfilepath, 100);
                }
                // thumbnail
                $fullpaththumbname =  PUBLIC_PATH . '/' . $photofolder . '/t/' . $newname;
                $thumbheight = (320 * $height_orig) / $width_orig; 
                $image_t = imagecreatetruecolor(320, $thumbheight);
                imagecopyresampled($image_t, $image, 0, 0, 0, 0, 320, $thumbheight, $width_orig, $height_orig);
                imagejpeg($image_t, $fullpaththumbname, 100);
            }
           // return $newname;
        }
    }

    //  "$name" is for reference only. This value is not included in form results array  
    //////////////////////////////////////////////////////////////////////////
    function FG_form_photo_webcam ($name, $label, $photofolder){
        global $_FG;
         
        if (!$_FG['is_reception']) {
            $FG_local_segment1 = $label;
            $FG_local_segment2 = <<<EOF
&nbsp; &nbsp; <a href="/aux/webcam" class="modalwebcam" title="Abrir webcam para tomar foto"><img src="/images/list/1/camera-trans.png" width=16 height=16></a> &nbsp; (verifique que su webcam esté conectada y haga click en el ícono de la cámara a la izquierda)
EOF;
            include (PUBLIC_PATH . '/template_sub_formrow.html');
        }
    }


    //////////////////////////////////////////////////////////////////////////
    function FG_form_photo_update ($photofolder, $newid){

        $provname  =  PUBLIC_PATH . '/' . $photofolder . '/' . session_id() ;
        $newname   =  PUBLIC_PATH . '/' . $photofolder . '/' . $newid . '.jpg';
        $tprovname =  PUBLIC_PATH . '/' . $photofolder . '/t/' . session_id();
        $tnewname  =  PUBLIC_PATH . '/' . $photofolder . '/t/' . $newid . '.jpg';

        rename ($provname, $newname);
        rename ($tprovname, $tnewname);
    }


    //////////////////////////////////////////////////////////////////////////
    function FG_form_multiphoto($table_folder, $label, $id = 0) {

        $_SESSION['multiphoto_table_folder'] = $table_folder; // 0=> table_name (where to register uploaded files)   1=> folder name (where to store files)
        $FG_local_segment1 =  $label;
        $FG_local_segment2 = '&nbsp;<iframe src="/aux/multiphoto/' . $id . '" width=470 height=300 scrolling="auto" id="multiphoto" class="formfield"></iframe>';
        include (PUBLIC_PATH . '/template_sub_formrow.html');
    }



    //////////////////////////////////////////////////////////////////////////
    function FG_form_multiphoto_update($id) {
        global $_FG;
        
        $result = mysqli_query($_FG['db0'], 'UPDATE `' . $_SESSION['multiphoto_table_folder'][0] . '` SET `article`=' . $id . ', `incomplete`=\'\' WHERE `article`=0 AND `incomplete`=\'' . session_id() . '\'');
        unset($_SESSION['multiphoto_table_folder']);
    }



    //////////////////////////////////////////////////////////////////////////
    function FG_form_submit ($name, $label, $value) {
        global $_FG;
         
        if (!$_FG['is_reception']) {
            $FG_local_segment1 = '&nbsp;';
            $FG_local_segment2 = <<<EOF
 &nbsp; &nbsp; <a href="javascript:document.forms[0].reset()" onclick="$('#{$_FG['currentformname']}').validationEngine('hideAll')" title="vaciar todos los campos"><img width=24 height=24 src="/images/session/editdelete.png" border=0 style="padding:0; margin:0 0 0 0;"></a> &nbsp; &nbsp; 
<input type="submit" name="$name" id="$name" value="$value" class="formbutton">
EOF;
            include (PUBLIC_PATH . '/template_sub_formrow.html');
            echo '</form></table></center>';
        }
    }


    /*
    form validation rules - a sting of comma separated rules (no space between rules)

    required
    custom[phone - url - email - date - number - integer - ipv4 - onlyNumberSp - onlyLetterSp - onlyLetterNumber]
    equals[field.id]
    min[float]
    max[float]
    minSize[integer]
    maxSize[integer]
    past[NOW or YYYY-MM-DD]
    future[NOW or YYYY-MM-DD]
    minCheckbox[integer]
    maxCheckbox[integer]

    // ajax[selector] TODO

    example: required,custom[date],future[2009-01-01],past[2009-12-31]
    */

    // Make every validation required in the specifications field
    //////////////////////////////////////////////////////////////////////////
    function FG_form_validate ($data, $field, $validation) {
    
        $pieces1 = explode (',', $validation);
        if (!is_array($pieces1)) return;
        foreach ($pieces1 as $piece) {
            $posopen = strpos($piece, '[');
            if ($posopen === FALSE) {
                $varfunction = 'FGformcheck_' . $piece;
                $varparam = NULL;
            } else {
                $varfunction = 'FGformcheck_' . substr($piece, 0, $posopen);
                $varparam = rtrim(substr($piece, $posopen+1), ']');
            }
            //FG_error ("<br>DATA: $data - FIELD: $field - VARFUNCTION: $varfunction - VARPARAM: $varparam<hr>");
            if (function_exists($varfunction)) $varfunction($data, $field, $varparam);
            }
    }
     
    // VALIDATION: required
    //////////////////////////////////////////////////////////////////////////
    function FGformcheck_required ($data, $field, $varparam) {
        if (strlen(strval($data)) < 1) FG_error("Checking 'required' in field '$field' ($data)", 'FORMERROR');
        }
     
    // VALIDATION: minSize
    //////////////////////////////////////////////////////////////////////////
    function FGformcheck_minSize ($data, $field, $varparam) {
        if (strlen($data) < $varparam) FG_error("Checking 'minSize' in field '$field' ($data)", 'FORMERROR');
        }
     
    // VALIDATION: maxSize
    //////////////////////////////////////////////////////////////////////////
    function FGformcheck_maxSize ($data, $field, $varparam) {
        if (strlen($data) > $varparam) FG_error("Checking 'maxSize' in field '$field' ($data)", 'FORMERROR');
        }
     
    // VALIDATION: min
    //////////////////////////////////////////////////////////////////////////
    function FGformcheck_min ($data, $field, $varparam) {
        if ((float)$data < (float)$varparam) FG_error("Checking 'min' in field '$field' ($data)", 'FORMERROR');
        }
     
    // VALIDATION: max
    //////////////////////////////////////////////////////////////////////////
    function FGformcheck_max ($data, $field, $varparam) {
        if ((float)$data > (float)$varparam) FG_error("Checking 'max' in field '$field' ($data)", 'FORMERROR');
        }
     
    // VALIDATION: equals
    //////////////////////////////////////////////////////////////////////////
    function FGformcheck_equals ($data, $field, $varparam) {
        global $_FG;
        if ($data != $_FG['getpost'][$varparam]) FG_error("Checking 'equals' in field '$field' ($data)", 'FORMERROR');
        }
     
    // VALIDATION: past[NOW or YYYY-MM-DD]
    //////////////////////////////////////////////////////////////////////////
    function FGformcheck_past ($data, $field, $varparam) {
        if ($varparam == 'NOW') {
             $varparam = date('Y-m-d');
        }
        if (strtotime($varparam) > strtotime($data)) FG_error("Checking 'past' in field '$field' ($data)", 'FORMERROR');
    }
     
    // VALIDATION: future[NOW or YYYY-MM-DD]
    //////////////////////////////////////////////////////////////////////////
    function FGformcheck_future ($data, $field, $varparam) {
        if ($varparam == 'NOW') {
             $varparam = date('Y-m-d');
        }
        if (strtotime($varparam) < strtotime($data)) FG_error("Checking 'future' in field '$field' ($data)", 'FORMERROR');
    }
     
     
    // VALIDATION: custom[phone - url - email - date - number - integer - ipv4 - onlyNumberSp - onlyLetterSp - onlyLetterNumber]
    //////////////////////////////////////////////////////////////////////////
    function FGformcheck_custom ($data, $field, $varparam) {
                          
        switch ($varparam) {
            case 'email':
            {
                if (!FGformcheck_validmail($data)) FG_error("Checking 'email' in field '$field' ($data)", 'FORMERROR');
                    break;
            }
            case 'number':
            {
                if (strlen(strval($data)) < 1) $data = '0';
                if (!is_numeric($data)) FG_error("Checking 'number' in field '$field' ($data)", 'FORMERROR');
                    break;
            }
            case 'integer':
            {  
               if (strlen(strval($data)) < 1) $data = '0';
               if (!(strval(intval($data)) === $data)) FG_error("Checking 'integer' in field '$field' ($data)", 'FORMERROR');               
                    break;
            }
            case 'url':
            {
                if (!preg_match('|^http(s)?://[a-z0-9-]+(.[a-z0-9-]+)*(:[0-9]+)?(/.*)?$|i', $data)) FG_error("Checking 'url' in field '$field' ($data)", 'FORMERROR');
                    break;
            }
            case 'ipv4':
            {
                if (!preg_match("/^(([1-9]?[0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5]).){3}([1-9]?[0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])$/", $data)) FG_error("Checking 'ipv4' in field '$field' ($data)", 'FORMERROR');
                    break;
            }
            case 'phone':
            {
                if (!FGformcheck_validtel($data)) FG_error("Checking 'phone' in field '$field' ($data)", 'FORMERROR');
                    break;
            }
            case 'date':
            {
                if (!FGformcheck_validdate($data)) FG_error("Checking 'date' in field '$field' ($data)", 'FORMERROR');
                    break;
            }
        } //switch
    }
     
     
    //////////////////////////////////////////////////////////////////////////
    function FGformcheck_validmail($email, $return_mxhost = 0) {
        if (!preg_match("/^([\w|\.|\-|_]+)@([\w||\-|_]+)\.([\w|\.|\-|_]+)$/i", $email)) return FALSE;
        list($local, $domain) = explode("@", $email, 2);
        $mxhosts = array();
        if (!checkdnsrr($domain, "MX") || !getmxrr($domain, $mxhosts)) return FALSE;
        if ($return_mxhost) return $mxhosts;
        return TRUE;
    }
     
    //////////////////////////////////////////////////////////////////////////
    function FGformcheck_validtel($telnumber) {
        $formats = array('(###)-###-###', '###-###-###', '(###) ###-###', '### ######', '##-######', '########', '## ## ## ##',
            '##-##-##-##', '## ######', '#########');
        $format = trim(ereg_replace("[0-9]", "#", $telnumber));
        return (in_array($format, $formats)) ? TRUE :
         FALSE;
    }
     
    //////////////////////////////////////////////////////////////////////////
    function FGformcheck_validdate($strdate) {
        $stamp = strtotime($strdate);
        if (!is_numeric($stamp)) return FALSE;
        $month = date('m', $stamp);
        $day = date('d', $stamp);
        $year = date('Y', $stamp);
        if (checkdate($month, $day, $year)) return TRUE;
        return FALSE;
    }
     
    // Show red asterisk in label if field is required
    //////////////////////////////////////////////////////////////////////////
    function FG_form_asterisk ($rule) {
        if (strpos($rule, 'required') !== FALSE) return '<span class="red">*</span> ';
         return '';
    }
    
    
        // Populate an HTML "select" from a given SQL Key-Value table
    //////////////////////////////////////////////////////////////////////////
    function FG_mkselect ($table, $selected = 1, $order = 'ASC', $dbhandler = 'db0') {
        global $_FG;
        $result = mysqli_query($_FG[$dbhandler], "SELECT * FROM `$table` ORDER BY id $order");
        if (mysqli_num_rows($result) < 1) return FALSE;
        while ($row = mysqli_fetch_assoc($result)) {
            if ($row['id']==$selected) $text .= "<option value=\"{$row['id']}\" selected>{$row['name']}</option>\n";
            else $text .= "<option value=\"{$row['id']}\">{$row['name']}</option>\n";
        }
        mysqli_free_result($result);
         return $text;
    }     
     
    // decode checkbox accumulated letters, using names from a table
    //////////////////////////////////////////////////////////////////////////
    function FG_decodecheckbox ($table, $string){
        $arrbuf = str_split ($string, 1);
        if ((!is_array($arrbuf))||(@count($arrbuf)<1)) return ' ';
        foreach($arrbuf as $letter) { 
            $ret = FG_dbgetbyfield ($table, 'id2', $letter);
            $output .= ' &nbsp; - ' . $ret['name'] . ' ';  
            }
        return $output;
    }

    
    // builds an SQL sentence AND (`field`='value1' OR `field`='valueN' OR ... )
    //////////////////////////////////////////////////////////////////////////
    function FG_mkSqlWhereFromArrayOred ($fieldname, $arrayvalues, $istext=FALSE){
        
        if (!is_array($arrayvalues)) return '';
        $toreturn = ' AND (';
        $flaginit='';
        if ($istext==TRUE) { $quote="'"; } else { $quote=''; } 
        foreach ($arrayvalues as $value) {
            $toreturn .= $flaginit . '`' . $fieldname . '`=' . $quote . $value . $quote . ' ';
            $flaginit='OR ';
        }
        return  $toreturn . ') ';
    }

    
    