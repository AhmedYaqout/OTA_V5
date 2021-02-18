<DOCTYPE html>
    <html>
    <head>
    <meta charset="utf-8">
    <title></title>
     </head>
    
    
    <body>
    
    <form action="php_tutorial.php " method="get">
       Name: <input type="text" name="username">
       <input type="submit">
       </form>

<?php
$charachtername = "Mohamed";
$age = 26;
echo(" <h1> $charachtername 's simple Site</h1>");
echo("<hr> ");
echo(" <p> he is $age years old. </p> " );

//data types in php
//1. strings:
$phrase = "To be or not be?!!";
//2. ints
$nInteger = 30;
//3. floats
$fFloat = 3.3 ;
//4. booleans
$bFlag = false ;
//5. null value
echo($_GET["username"]);


?>