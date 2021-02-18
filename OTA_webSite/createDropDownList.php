<?php
function createDropDown($label,$options)
{
    echo ("<label for=$label> select file: </label>") ;
    echo ("<select id=$label>");
    for($i = 0; $i < count($options); $i++ )
    {
        echo ("<option>$options[$i]</option>") ;
    }
    echo ("</select>");
}



?>