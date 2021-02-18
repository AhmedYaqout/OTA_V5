
   <?php

function alert($msg) {
    echo "<script type='text/javascript'>alert('$msg');</script>";
}



if( isset($_GET['command']))
{
    $file=$_FILES["fileupload"];
	
	$fileName   =$_FILES["fileupload"]['name'];
	$fileTmpName=$_FILES["fileupload"]['tmp_name'];
	$fileSize   =$_FILES["fileupload"]['size'];
	$fileError  =$_FILES["fileupload"]['error'];
	$fileType   =$_FILES["fileupload"]['type'];
   
    $fileNameOnly = explode('.',$fileName) ;
    $fileNameOnly =  strtolower($fileNameOnly[0]);
    
    $fileExt = explode('.',$fileName) ; 
	$fileActualExt = strtolower(end($fileExt));


    //W3schools php_file_upload tutorial: https://www.w3schools.com/php/php_file_upload.asp
$destination = "uploads/".$fileNameOnly.".txt" ;
// "uploads\\".
if( $_GET['command'] == 0) //upload file to server
{
    if (move_uploaded_file($fileTmpName, $destination)) 
    {
     $msg = "The file ". htmlspecialchars( basename( $_FILES["fileToUpload"]["name"])). " has been uploaded."; 
    }
    else
    {
     $msg = "Sorry, there was an error uploading your file.";
     
    }
    alert($msg);
    


    echo 'Here is some more debugging info:</br>';
    print_r($_FILES);
    echo "</br>";
    echo $fileTmpName; 
    echo "</br>";
    $source=fopen("source.txt","w+");
    fputs($source,$destination);
    echo "file saved at ".$destination;
    echo "</br>"; 
    fclose($source); 
}
elseif(($_GET['command'] == 1) ) //print file
{
    $source=fopen("source.txt","r+");
    
    $destination = fgets($source);
    // echo $destination;
    if(empty($destination))
    {
        echo "empty destination";
        exit();
    }
    fclose($source);
    $file_arr = file($destination);

// Loop through our array, show HTML source as HTML source; and line numbers too.
    // foreach ($file_arr as $line_num => $line) {
    //     echo "Line<b>{$line_num}</b> " . htmlspecialchars($line) ;
    //      echo "</br>";
    // }

    //save no of line in the file
    $status = fopen("status.txt","w");

    fwrite($status, "1");
    fclose($status);
    
   
    $buffer_file = fopen("buffer.txt","w+");

    if($buffer_file == false)
    {
        throw new RuntimeException("Unable to Open File!!");
    }
    

    // before looping throug the file and copying to buffer
    // yuo should: 
    // 1. read the progress value from the progress file
    // $progress=intval(fgets($progress_file));
    // 2. save the progress value in progress
    // rewind($progress_file);

    $no_lines = count($file_arr);
     $page_no = 1; //is sent from microcontroller
     if(isset($_GET['page_no']) && is_numeric($_GET['page_no']) )
     {
         $page_no= $_GET['page_no'];
     }
     
    $no_lines_per_page = (floor($no_lines/30) >= $page_no) ? 30: $no_lines%30 ; 
    $offset = ($page_no-1)*30;
      
    // echo "Debug data:\n";
    // echo $page_no." ".$offset." ".$no_lines_per_page;
    // echo "</br>";
    //  die();


    for($i = $offset; $i < ($no_lines_per_page+$offset) ; $i++)
    {
        fputs($buffer_file,$file_arr[$i]); //rewind($buffer_file);
        
        //$line = fgets($buffer_file);//rewind($buffer_file);
        echo $file_arr[$i];
        echo "</br>";
        // $ack = 0;
    }
            // $progress+=$i;
            // if($progress > $no_lines)
            // {
            //     // reset progress to zero for the next burn
            //     $progress=0;
            //     echo $progress;
            // }
           
           
            // rewind($buffer_file);
            
            // clear file contents before saveing the new value
            // file_put_contents("progress.txt", "");
            //save your progress for the next run
            // fwrite($progress_file,$progress);
            
            //close all file handles
            // fclose($progress_file);
            fclose($buffer_file);
            
}
elseif(($_GET['command'] == 2)) // means that the micrcontroller is done so write the status to zero
{
    $status = fopen("status.txt","w");

    fwrite($status, "0");
    fclose($status);
}




}


?> 