//%attributes = {"invisible":true}
$input:=Folder:C1567(Get 4D folder:C485(Current resources folder:K5:16); fk platform path:K87:2).file("BASIC_Einfach.pdf").path
$output:=Folder:C1567(fk desktop folder:K87:19).file("extracted.xml").path

$status:=PDFA GET XML($input; $output)
$info:=Split string:C1554($status.info; "\n")