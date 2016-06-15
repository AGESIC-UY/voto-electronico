<?php
    #         ____
    #        / __/________  ___        ____ _____ _   __
    #       / /_ / ___/ _ \/ _ \______/ __ `/ __ \ | / /
    #      / __// /  /  __/  __/_____/ /_/ / /_/ / |/ /
    #     /_/  /_/   \___/\___/      \__, /\____/|___/   > http://free-gov.org
    #                               /____/
    #
    #  This file is part of 'Free-gov' - modules/aux/webcam-save.inc
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
     
    $photofolder =  'photos'; 
    $width = 640;
    //if (strlen($_FG['request'][2])>1) $photofolder = FG_decode ($_FG['request'][2]);
    $cont = file_get_contents('php://input');

            $newname = session_id();  //str_replace( ' ' , '_', microtime()) . '.jpg';
            $newfilepath = PUBLIC_PATH . '/' . $photofolder . '/' . $newname;
            file_put_contents ($newfilepath, $cont);

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


