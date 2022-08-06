//%attributes = {}
$file:=toPDF("TEST")

$input:=$file.path

$output:=Folder:C1567(fk desktop folder:K87:19).file("converted.pdf").path

$error:=PDF TO PDFA($input; $output)
