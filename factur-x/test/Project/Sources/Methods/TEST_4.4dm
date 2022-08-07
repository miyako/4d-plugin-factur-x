//%attributes = {"invisible":true}
$PDF:=toPDF("TEST")

$PDFA:=Folder:C1567(fk desktop folder:K87:19).file("TEST-pdfa.pdf")

$error:=PDF TO PDFA($PDF.path; $PDFA.path)

If ($error=0)
	
	$XML:=Folder:C1567(Get 4D folder:C485(Current resources folder:K5:16); fk platform path:K87:2).file("BASIC_Einfach.xml")
	
	$output:=Folder:C1567(fk desktop folder:K87:19).file("TEST-factur-x.pdf")
	
	If ($output.exists)
		$output.delete()
	End if 
	
	$status:=PDFA SET XML($PDFA.path; $XML.path; $output.path)
	$info:=Split string:C1554($status.info; "\n")
	
	If ($status.success)
		SHOW ON DISK:C922($output.platformPath)
	End if 
	
End if 

