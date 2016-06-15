<?php
    #         ____
    #        / __/________  ___        ____ _____ _   __
    #       / /_ / ___/ _ \/ _ \______/ __ `/ __ \ | / /
    #      / __// /  /  __/  __/_____/ /_/ / /_/ / |/ /
    #     /_/  /_/   \___/\___/      \__, /\____/|___/   > http://free-gov.org
    #                               /____/
    #
    #  This file is part of 'Free-gov' - free-gov-core/lib/id_document_uy.php
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

    // Compression, decompression and checking functions for Uruguayan ID citizen document


    /*
        An uruguayan "Cedula de Identidad" usually contains 8 digits in the following format:
         1.234.567-8
 
        Last digit is just a checksum digit to verify number integity
        There is the possibility of shorter numbers (< 1.000.000) in older people, then this 
        possibility must be included

        People can write this number with or without periods, spaces, comma, or any other
        punctuation, however number must be validated despite presentation format, and 
        normalized for database insertion.
    */


    function verifycedula ($input){
        if (!is_numeric($input)) return FALSE;
        if (strlen($input)<7)  return FALSE;
        if (strlen($input)>8)  return FALSE;
        return TRUE;
    }



    function compactcedula ($input){
        return str_replace(array(' ', ',', '-', '/', '.', ';', '_', '='), '', $input);
    }


    function inflatecedula ($input){
        $lastdigit = substr($input, -1);
        $cedula =  substr($input, 0, -1);
        if(strlen($cedula)==7) {  return substr($cedula, 0,1) . '.' . substr($cedula, 1,3) . '.' .  substr($cedula, 4,3) . '-' . $lastdigit; }
        else if(strlen($cedula)==6) {  return  substr($cedula, 0,3) . '.' .  substr($cedula, 3,3) . '-' . $lastdigit; }
    }


    // check verification digit of uruguayan "cedula de identidad"
    // function must receive the clean number: only integers without periods or minus sign
    function chkdigitcedula ($input){
        $lastdigit = substr($input, -1);
        $cedula = rtrim ($input, $lastdigit);
        if (strlen($cedula)<7) return TRUE; // no check if short cedula (smaller than 1.000.000-x)
        $p1 = substr($cedula, 0,1) * 2; if (strlen($p1)>1) $p1 = substr ($p1, -1);
        $p2 = substr($cedula, 1,1) * 9; if (strlen($p2)>1) $p2 = substr ($p2, -1);
        $p3 = substr($cedula, 2,1) * 8; if (strlen($p3)>1) $p3 = substr ($p3, -1);
        $p4 = substr($cedula, 3,1) * 7; if (strlen($p4)>1) $p4 = substr ($p4, -1);
        $p5 = substr($cedula, 4,1) * 6; if (strlen($p5)>1) $p5 = substr ($p5, -1);
        $p6 = substr($cedula, 5,1) * 3; if (strlen($p6)>1) $p6 = substr ($p6, -1);
        $p7 = substr($cedula, 6,1) * 4; if (strlen($p7)>1) $p7 = substr ($p7, -1);
        $p = $p1 + $p2 + $p3 + $p4 + $p5 + $p6 + $p7; if (strlen($p)>1) $p = substr ($p, -1);
        if ($p>0) $p = 10 - $p;
        if ($lastdigit == $p) return TRUE; else return FALSE;
    }
 
