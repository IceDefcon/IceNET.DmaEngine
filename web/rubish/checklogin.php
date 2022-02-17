<?php

// MySQL Connection
mysql_connect("localhost", "root", "toor") or die(mysql_error());
mysql_select_db("login") or die(mysql_error());

// POST variables
$user=$_POST['user'];
$pass=$_POST['pass'];

// MD5 hash
//$pass=md5($pass);

// Query "login" table
$result = mysql_query("SELECT * FROM login WHERE user = '$user' AND pass = '$pass'") or die(mysql_error());

// Login validation
if(mysql_num_rows($result) != 0) {
$row = mysql_fetch_array($result);
echo "<font color='blue'>Welcome, ".$row['user']."!</font>";
}
else {
echo "Wrong username or password!";
}

// Query highlight
echo "<br><br>";
echo "SELECT * FROM login WHERE user = '";
echo "<font color='red'>".$user."</font>' AND pass = '<font color='red'>".$pass."</font>';";

?> 