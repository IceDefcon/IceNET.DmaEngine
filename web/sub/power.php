<!DOCTYPE html>
<html lang="en-UK">
	<head>
		<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
		<title>MEng 4th Year Project</title>
		<link rel="stylesheet" href="/css/style.css"/>
		<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css">
		<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.1.1/jquery.min.js"></script>
		<script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js"></script>
		<script src="/js/main.js"></script>
		<style>
  		.carousel-inner > .item > img,
  		.carousel-inner > .item > a > img {
      	width: 100%;
      	margin: 15px;
  		}
  		</style>
	</head>
	<body style="background-color:white;">

	<div class="container">
	<img align="right" src="/img/ice.jpg" width="200" height="86">
	<h1>Power Consumption</h1>
	<br>
	</div>

	<div class="container">
	  <div class="btn-group btn-group-justified" role="group" aria-label="...">
	  	<div class="btn-group" role="group">
	      <a class="btn btn-primary" href="index.php" role="button">Home</a>
	    </div>
	    <div class="btn-group" role="group">
	      <button type="button" class="btn btn-primary dropdown-toggle" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">Voltage and Current <span class="caret"></span>
	      </button>
	      <ul class="dropdown-menu dropdown-menu-right dropdown-menu-wide">
	        <li><a href="voltage.php">Phase 1</a>
	        </li>
	        <li><a href="#">Phase 2</a>
	        </li>
	        <li><a href="#">Phase 3</a>
	        </li>
	        <li><a href="#">Neutral to Earth</a>
	        </li>
	        <li><a href="#">Phase Imbalance</a>
	        </li>
	      </ul>
	    </div>    <div class="btn-group" role="group">
	      <button type="button" class="btn btn-primary dropdown-toggle" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">Power <span class="caret"></span>
	      </button>
	      <ul class="dropdown-menu dropdown-menu-right dropdown-menu-wide">
	        <li><a href="power.php">Phase 1</a>
	        </li>
	        <li><a href="#">Phase 2</a>
	        </li>
	        <li><a href="#">Phase 3</a>
	        </li>
	        <li><a href="#">Total power</a>
	        </li>
	      </ul>
	    </div>
	    <div class="btn-group" role="group">
	      <button type="button" class="btn btn-primary dropdown-toggle" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">Harmonics Interference <span class="caret"></span>
	      </button>
	      <ul class="dropdown-menu dropdown-menu-right dropdown-menu-wide">
	        <li><a href="interferance.php">Phase 1</a>
	        </li>
	        <li><a href="#">Phase 2</a>
	        </li>
	        <li><a href="#">Phase 3</a>
	        </li>
	      </ul>
	    </div>
	  </div>
	</div>

	<div class="container">
	  <br>
	  <div id="myCarousel" class="carousel slide" data-ride="carousel" data-interval="false">
	    <!-- Indicators -->
	    <ol class="carousel-indicators">
	      <li data-target="#myCarousel" data-slide-to="0" class="active"></li>
	      <li data-target="#myCarousel" data-slide-to="1"></li>
	    </ol>

	    <!-- Wrapper for slides -->
	    <div class="carousel-inner" role="listbox">
	      <div class="item active">
	        <img src="/img/power.png" alt="Voltage FFT" width="460" height="345">
	      </div>
	    </div>

	    <!-- Left and right controls -->
	    <a class="left carousel-control" href="#myCarousel" role="button" data-slide="prev">
	      <span class="glyphicon glyphicon-chevron-left" aria-hidden="true"></span>
	      <span class="sr-only">Previous</span>
	    </a>
	    <a class="right carousel-control" href="#myCarousel" role="button" data-slide="next">
	      <span class="glyphicon glyphicon-chevron-right" aria-hidden="true"></span>
	      <span class="sr-only">Next</span>
	    </a>
	  </div>
	</div>

	<div class="container">
	  <h2>Power measurements in Phase 1</h2>           
	  <table class="table table-bordered">
	    <thead>
	      <tr>
	        <th>Real [W]</th>
	        <th>Apparent [VA]</th>
	        <th>Reactive [Var]</th>
	        <th>Power factor</th>
	      </tr>
	    </thead>
	    <tbody>
	      <tr>
	        <td>
				<div>
					<?php
					    $myfilename = "/var/www/html/text/power1_real.txt";
					    if(file_exists($myfilename)){
					      echo file_get_contents($myfilename);
					    }
					?>
				</div>
	        </td>
	        <td>
				<div>
					<?php
					    $myfilename = "/var/www/html/text/power1_appa.txt";
					    if(file_exists($myfilename)){
					      echo file_get_contents($myfilename);
					    }
					?>
				</div>
	        </td>
	        <td>
				<div>
					<?php
					    $myfilename = "/var/www/html/text/power1_reac.txt";
					    if(file_exists($myfilename)){
					      echo file_get_contents($myfilename);
					    }
					?>
				</div>
	        </td>
	        <td>
				<div>
					<?php
					    $myfilename = "/var/www/html/text/pf1.txt";
					    if(file_exists($myfilename)){
					      echo file_get_contents($myfilename);
					    }
					?>
				</div>
	        </td>
	    </tbody>
	  </table>
	</div>