<?php
$kfm_db_type = 'sqlitepdo';
$kfm_db_prefix   = 'kfm_';
$kfm_db_host     = 'localhost';
$kfm_db_name     = 'kfm';
$kfm_db_username = 'username';
$kfm_db_password = 'password';
$kfm_db_port     = '';
$use_kfm_security=false;

  if(!isset($_SERVER['DOCUMENT_ROOT'])) {
    $n = $_SERVER['SCRIPT_NAME'];
    $f = ereg_replace('\\', '/',$_SERVER["PATH_TRANSLATED"]);
    $f = str_replace('//','/',$f);
    $_SERVER['DOCUMENT_ROOT'] = eregi_replace($n, "", $f);
    } 

$kfm_userfiles_address = $_SERVER['DOCUMENT_ROOT'] . '/userfiles';
//$kfm_userfiles_address =  dirname(__FILE__) . '/userfiles';
//$kfm_userfiles_output = dirname(__FILE__) . '/get.php';
$kfm_userfiles_output = '/userfiles';
$kfm_workdirectory = '.files-sqlite-pdo';
$kfm_imagemagick_path = '/usr/bin/convert';
//$kfm_imagemagick_path = '/usr/bin/cnvert';
$kfm_dont_send_metrics = 0;
$kfm_server_hours_offset = 1;
