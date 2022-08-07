//%attributes = {"invisible":true}
$input1:=Folder:C1567(fk desktop folder:K87:19).file("converted.pdf").path
$input2:=Folder:C1567(Get 4D folder:C485(Current resources folder:K5:16); fk platform path:K87:2).file("BASIC_Einfach.xml").path
$output:=Folder:C1567(fk desktop folder:K87:19).file("result.pdf").path

$status:=PDFA SET XML($input1; $input2; $output)
$info:=Split string:C1554($status.info; "\n")