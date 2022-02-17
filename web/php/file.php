<?php
	$myfilename = "/var/www/html/text/power1_true.txt";
	if(file_exists($myfilename)){
	echo file_get_contents($myfilename);
	}
?>