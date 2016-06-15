<?php
    #         ____
    #        / __/________  ___        ____ _____ _   __
    #       / /_ / ___/ _ \/ _ \______/ __ `/ __ \ | / /
    #      / __// /  /  __/  __/_____/ /_/ / /_/ / |/ /
    #     /_/  /_/   \___/\___/      \__, /\____/|___/   > http://free-gov.org
    #                               /____/
    #
    #  This file is part of 'Free-gov' - modules/aux/qrcode.inc
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
     
     /*
     $_FG['request'][3] is Level of error correction (	QR_ECLEVEL_L=0, QR_ECLEVEL_M=1, QR_ECLEVEL_Q=2,  QR_ECLEVEL_H'=3) where 3 is best
     $_FG['request'][4] is QR image size: 1 to 10, where 10 is bigest    
      
     $_FG['request'][3] and $_FG['request'][4] are not encoded.   $_FG['request'][2] (data) is FG_encoded
     $_FG['request'][3] and $_FG['request'][4] can be omitted
     */
     
    if (!isset($_FG['request'][2])) FG_error('QR barcode fail: no parameter received');
         
    include ('lib/phpqrcode.php');
     
    header('Content-Type: image/png');
    
    if (!isset($_FG['request'][3]) || !isset($_FG['request'][4]) )
        QRcode::png(FG_decode($_FG['request'][2]));
    else
        QRcode::png(FG_decode($_FG['request'][2]), $_FG['request'][3], $_FG['request'][4]);      
  
    FG_render ('template_empty'); // Uses an empty output environment

