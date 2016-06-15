<?php
    #         ____
    #        / __/________  ___        ____ _____ _   __
    #       / /_ / ___/ _ \/ _ \______/ __ `/ __ \ | / /
    #      / __// /  /  __/  __/_____/ /_/ / /_/ / |/ /
    #     /_/  /_/   \___/\___/      \__, /\____/|___/   > http://free-gov.org
    #                               /____/
    #
    #  This file is part of 'Free-gov' - modules/aux/multiphoto.inc
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

    //if (!isset($_FG['request'][2])) FG_error('QR barcode fail: no parameter received');

$photofolder = '/photos/';
$destination = PUBLIC_PATH . $photofolder;
$width = 640;


    if (!isset($_FG['request'][2])) $id=0; else $id = $_FG['request'][2];
    if (!is_numeric($_FG['request'][2])) $id=0;

echo '<form action="/aux/multiphoto/' . $id . '" method="POST" id="formiframe" enctype="multipart/form-data"><input type="hidden" name="MAX_FILE_SIZE" value="12000000"><table width=450 cellpadding=5 cellspacing=5 border=0><tr><td width=320><input type="file" id="fileframe" name="fileframe"></td><td width=130 align="right"><input type="submit" name="submitbut" id="submitbut" value="enviar imagen"></td></tr><tr><td colspan=2><hr></td></tr></table></form>';


        /////////////////////////////////
        if ($_SERVER['REQUEST_METHOD']=='POST') { // resize photo and insert in database
            if (is_uploaded_file($_FILES['fileframe']['tmp_name'])){
            if ((($_FILES['fileframe']['type'] != 'image/jpeg') && ($_FILES['fileframe']['type'] != 'image/pjpeg')) ||  $_FILES['fileframe']['error'] > 0) { ; }
            else {   
            $newname = str_replace( ' ' , '_', microtime()) . '.jpg';
            $newfilepath = $destination . '/' . $newname;
            move_uploaded_file($_FILES['fileframe']['tmp_name'], $newfilepath);
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
                $fullpaththumbname =  $destination . '/t/' . $newname;
                $thumbheight = (320 * $height_orig) / $width_orig; 
                $image_t = imagecreatetruecolor(320, $thumbheight);
                imagecopyresampled($image_t, $image, 0, 0, 0, 0, 320, $thumbheight, $width_orig, $height_orig);
                imagejpeg($image_t, $fullpaththumbname, 100);

                if($id==0) $fileframe['incomplete'] = session_id(); else $fileframe['incomplete'] = '';
                $fileframe['article'] = $id;
                $fileframe['filename'] = $newname;
                $fileframe['origfilename'] = $_FILES['fileframe']['name'];
                //$fileframe['filesize'] = 0;
               
                FG_dbinsert ('photos', $fileframe);
            }
            }
        }

        /////////////////////////////////
        if (isset($_FG['request'][3]) && is_numeric($_FG['request'][3])) { // delete photo

          $res = FG_dbget ('photos', $_FG['request'][3]);
            if (($res['article']==$id)||($res['incomplete']==session_id())) { // we can delete this photo, this is ours

             @unlink ($destination . '/' . $_FG['request'][3]);
             @unlink ($destination . '/t/' . $_FG['request'][3]);
             FG_dbdelete ('photos', $_FG['request'][3]);
            }
        }
  
        if($id!=0)
        $result = mysqli_query($_FG['db0'], 'SELECT * FROM `photos` WHERE `article` = ' . $id);
        else
        $result = mysqli_query($_FG['db0'], 'SELECT * FROM `photos` WHERE `incomplete` = \'' . session_id() . '\'');

        while($fila = mysqli_fetch_assoc($result)) {
            photorow ($fila);
            }     

    FG_render ('template_iframed'); // Uses an empty output environment


        ///////////////////////////////////////////////////////////////////////////////
        function photorow ($data) {
          global $photofolder, $id;

        echo <<<EOF
<table width=450 cellpadding=5 cellspacing=5 border=0><tr>
<td width=20>&nbsp;</td><td width=120><img src="{$photofolder}t/{$data['filename']}" width=100></td>
<td valign="top">FOTO: {$data['origfilename']} <br> <a href="/aux/multiphoto/$id/{$data['id']}"><img src="/images/list/1/delete-trans.png" width=16 height=16 border=0> borrar foto</a></td>
</tr></table>
EOF;
        }

