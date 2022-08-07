//%attributes = {"invisible":true}
/*

generate electronic invoice data (XML)

*/

$invoice:=InvoiceExample
$template:=Folder:C1567(fk resources folder:K87:11).file("template.xml")
$data:=toXML($invoice; $template)
$XML:=Folder:C1567(Temporary folder:C486; fk platform path:K87:2).file("data.xml")
$XML.setText($data)

/*

generate PDF using native printing commands (result is not PDF/A)

*/

$PDF:=toPDF("TEST")

/*

convert to PDF/A; internally using ghostscript

*/

$PDFA:=Folder:C1567(Temporary folder:C486; fk platform path:K87:2).file("TEST.pdf")
$error:=PDF TO PDFA($PDF.path; $PDFA.path)

/*

convert to Factur-X internally using python

*/

If ($error=0)
	
	$output:=Folder:C1567(fk desktop folder:K87:19).file("TEST.pdf")
	
	If ($output.exists)
		$output.delete()  //library will not overwrite existing file
	End if 
	
	$status:=PDFA SET XML($PDFA.path; $XML.path; $output.path)
	$info:=Split string:C1554($status.info; "\n")
	
	If ($status.success)
		SHOW ON DISK:C922($output.platformPath)
	End if 
	
End if 