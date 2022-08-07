//%attributes = {}
#DECLARE($invoice : Object; $file : 4D:C1709.File)->$XML : Text

If ($file.exists)
	
	$source:=$file.getText()
	
	PROCESS 4D TAGS:C816($source; $XML; $invoice)
	
End if 