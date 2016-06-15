<?php
    #         ____
    #        / __/________  ___        ____ _____ _   __
    #       / /_ / ___/ _ \/ _ \______/ __ `/ __ \ | / /
    #      / __// /  /  __/  __/_____/ /_/ / /_/ / |/ /
    #     /_/  /_/   \___/\___/      \__, /\____/|___/   > http://free-gov.org
    #                               /____/
    #
    #  This file is part of 'Free-gov' - modules/aux/webcam.inc
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


$_FG['render']['extrahead'] .= <<<EOF
<link href="/css/openbooth.css" media="all" rel="stylesheet" type="text/css"> 
EOF;

echo <<<EOF
		<div id="photo-booth" class="custom_overlay">
			<div id="photo-booth-viewarea">
				<object classid="clsid:D27CDB6E-AE6D-11cf-96B8-444553540000" width="459" height="344" id="openbooth">
					<param name="movie" value="/js/openbooth.swf">
					<param name="allowScriptAccess" value="always">
					<!--[if !IE]>-->
					<object type="application/x-shockwave-flash" data="/js/openbooth.swf" width="459" height="344">
						<!--<![endif]-->
						<div id="photo-booth-noflash-dev"></div>
						<!--[if !IE]>-->
					</object>
					<!--<![endif]-->
				</object>
			</div>
			<div id="photo-booth-controls" class="controls">
				<button class="round_gray_button left_aligned" id="cancel-retry-btn"><span>Cancelar</span></button>
				<button class="round_gray_button disabled right_aligned" id="save-btn"><span>Guardar foto</span></button>
				<br class="clearfix">
				<button id="photo-booth-capture"><span>Capturar</span></button>
			</div>
		</div> 


 	<script src="/js/swfobject.js" type="text/javascript"></script> 
	<script type="text/javascript">
	swfobject.switchOffAutoHideShow();
	swfobject.registerObject("openbooth", "9");
	var openbooth = swfobject.getObjectById("openbooth");

	$(function() {
		$("#cancel-retry-btn").bind('click', function() { closePhotobooth(); });
		$("#save-btn").bind('click', function() {if (! $(this).hasClass("disabled")) { savePhoto(); } });
		$("#photo-booth-capture").bind('click', function() { if (! $(this).hasClass("disabled")) { previewPhoto(); } });
	});
	
	var options = {
		'enableSound': true, // Camera sounds
		'enableFlash': true, // Camera Flash effect
		'enableSettingsButton': true, // Flash settings button (only appears when hovering over video)
		'bandwidth': 0, // Max Bandwidth (0 = unlimited)
		'photoQuality': 100, // JPEG Photo quality (0 - 100)
		'photoWidth': 459, // Photo width
		'photoHeight': 344, // Photo height
		'cameraWidth': 640, // Camera source width (tip: should be in increments of 320)
		'cameraHeight': 480, // Camera source height (tip: should be in increments of 240)
		'cameraFPS': 25, // Camera source frames per second
		'timerTimeout': 0, // Camera timer length
		'timerX': 198, // Camera timer X position on video
		'timerY': 250, // Camera timer Y position on video
		'timerAlpha': 0.6, // Camera timer opacity (0 - 1)
		'callbacks': {
			'initComplete': 'onInitComplete', // Fired when Flash finished initializing the init() function
			'uploadSuccessful': 'onUploadSuccessful', // Fired when an upload was successful
			'onError': 'onError', // Fired when there was an upload error
			'previewComplete': 'onPreviewComplete', // Fired when a snapshot was taken
			'previewCanceled': 'onPreviewCanceled', // Fired when a snapshot was dismissed
			'videoStart': false, // Fired when a video source started
			'noVideoDevices': false, // Fired when no video sources were detected
			'uploadComplete': false  // Fired when an upload function was completed
		},
		'placeholders':{
			'load':	'/images/openbooth/openbooth_allow_dev.jpg',  // Placeholder image: Before video started
			'save':	'/images/openbooth/openbooth_saving_dev.jpg', // Placeholder image: While image is uploaded
			'noVideoDevices': '/images/openbooth/openbooth_nocameras_dev.jpg' // Placeholder image: When no video devices were detected
		}
	};


	// This function cannot be renamed. OpenBooth will always automatically call "onFlashReady" upon initializing itself.
	function onFlashReady() {
		setTimeout(function() { openbooth.init(options); }, 500);
	}
		
	function previewPhoto() {
		openbooth.startPreviewTimer();
		$("#photo-booth-capture").addClass("disabled");
	}
	
	function cancelPreview() {
		openbooth.cancelPreview();
	}
	
	function closePhotobooth() {
		$("#photo-booth").remove();
                parent.jQuery.fancybox.close();
	}
	
	function selectCamera() {
		openbooth.selectCamera();
	}
	
	function savePhotoS3() {
		var s3vars = {
			'policy':'',
			'signature': '',
			'acl': 'public-read',
			'accessKeyId':'',
			'bucket':'',
			'key':'',
			'extraPostVars' : { // Supports virtually unlimited extra post variables
			'x-amz-meta-': ''
			}
		};
	
		$("#save-btn").addClass("disabled");
		$("#cancel-retry-btn")
			.unbind('click')
			.bind('click', function() { closePhotobooth(); })
			.html("<span>Cancelar</span>");
		openbooth.savePhotoS3(s3vars);
	}
	
	function savePhoto() {
		var postvars = {
			'URL': '/aux/webcam-save'
		};

		$("#save-btn").addClass("disabled");
		$("#cancel-retry-btn")
			.unbind('click')
			.bind('click', function() { closePhotobooth(); })
			.html("<span>Cancelar</span>");
		openbooth.savePhoto(postvars);	
	}
	
	function onPreviewComplete() {
		$("#save-btn").removeClass("disabled");
		$("#cancel-retry-btn")
			.unbind('click')
			.bind('click', function() { cancelPreview(); })
			.html("<span>Reintentar</span>");
	}
	
	function onPreviewCanceled() {
		$("#photo-booth-capture").removeClass("disabled");
		$("#save-btn").addClass("disabled");
		$("#cancel-retry-btn")
			.unbind('click')
			.bind('click', function() { closePhotobooth(); })
			.html("<span>Cancelar</span>");
	}
	
	function onInitComplete() {
		openbooth.camInit();
	}
	
	function onError(event) {
	
	}
	
	function onUploadSuccessful() {
		parent.jQuery.fancybox.close();
	}  
	</script>

EOF;



   

    FG_render ('template_iframed'); // Uses an empty output environment

 
