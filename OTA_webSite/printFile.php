<?php

//$target_file = "uploads\imt_blinky.hex";


// if(file_exists($target_file))
// {
//     $file = fopen($target_file,"r") or die("Unable to open file");

//     if($file){echo "file opened </br>";}
   

//   //  echo readfile($target_file);
// // while(! feof($file))
// // {
// //     for($i = 0; $i<8 ; $i++)
// //     {
// //         $line = fread($file,2); //read  bytes
// //         $line_unpacked = unpack("H*",$line);
// //         echo $line_unpacked[1];
// //         echo " ";
// //     }
// //     echo "</br>";
// // }


// // HEX file Record Format
// // :CC-ADDR-RT-<DATA>-CS
// //1. read first byte -> 1 digit ':'
// //2. read cc -> 2 digits 
// //3. read ADDR -> 4 digits
// //4. read RT -> 2 digits
// //5. read DATA -> total= CC*2 digits, read byte by byte
// //6. read CS -> 2 digits
// while(! feof($file))
// {
//     $colon = fread($file,1);
//     echo $colon;
    
//     $CharCnt = fread($file,2);
//     // $N_CharCnt = unpack("C*",$CharCnt);
//     // echo $N_CharCnt[1];
//     // echo $N_CharCnt[2];
//     echo $CharCnt;
//     $N_CharCnt = intval($CharCnt,16);
//     // echo "CC=";
//     // echo $N_CharCnt;
//     echo "|";
//      $addr = fread($file,4);
//     // $N_addr = unpack("H*",$addr);
//     // echo $N_addr[1];
//     echo $addr;
    
//     echo "|";
//     $RecType = fread($file,2);
//     // $N_RecType = unpack("H*",$RecType);
//     // echo $N_RecType[1];
//     echo $RecType;

//     echo "| ";
//     for($i = 0; $i<$N_CharCnt ; $i++)
//     {
//         $line = fread($file,2); //read  bytes
//         //$N_line = unpack("H*",$line);
//         //echo $N_line[1];
//         echo $line;
//         echo " ";
//     }
//     echo " |";
//     $CheckSum = fread($file,2);
//     //$N_CheckSum = unpack("h*",$CheckSum);
//     echo $CheckSum ;
//     fread($file,2); //flush <CR/LF> char
//     echo "</br>";
// }

//     // echo $line;
//     // echo "</br>";
//     // print_r($line_unpacked);
//     // echo "</br>";


// //Output lines until EOF is reached
// // while(! feof($file)) {
// //     $line = fgets($file);
// //     echo $line. "<br>";
// //   }

// // while(! feof($file))
// // {
// //     if(fread($file))
// //     {
// //     $line = fread($file,16);
// //     //$binString = pack("ah*",$line);
// //     //echo $binString;
// //     echo "</br>";    
// //     }
// //     else
// //     {
// //         echo("couldn't read");
// //     }

    
// // }



//   fclose($file);
// }


if(empty($destination))
{
    echo "empty destination";
    exit();
}
$file_arr = file($destination);

//save no of line in the file
$file_size = fopen("file_size.txt","r+");

fwrite($file_size, $fileSize);
fclose($file_size);


$buffer_file = fopen("buffer.txt","w+");

if($buffer_file == false)
{
    throw new RuntimeException("Unable to Open File!!");
}
// Loop through our array, show HTML source as HTML source; and line numbers too.
// foreach ($file_arr as $line_num => $line) {
//     echo "Line<b>{$line_num}</b> " . htmlspecialchars($line) ;
//      echo "</br>";
// }

    // $i = $idx;
    for($i = 0; $i < count($file_arr); $i++)
    {
        fputs($buffer_file,$file_arr[$i]); //rewind($buffer_file);
        
        //$line = fgets($buffer_file);//rewind($buffer_file);
        echo $file_arr[$i];
        echo "</br>";
        // $ack = 0;
    }
fclose($buffer_file)

  


?>