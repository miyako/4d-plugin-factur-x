//%attributes = {}
$folder:=Folder:C1567("Macintosh HD:Users:miyako:Documents:GitHub:4d-plugin-factur-x:factur-x:dist:u-test:"; fk platform path:K87:2)

For each ($f; $folder.files(fk recursive:K87:7 | fk ignore invisible:K87:22))
	
	If ($f.extension=".so") | ($f.extension=".dylib") | ($f.extension="")
		
		$components:=Split string:C1554($f.path; "/")
		$components[8]:="arm"
		$arm:=File:C1566($components.join("/"))
		
		LAUNCH EXTERNAL PROCESS:C811("lipo -create "+$f.path+" "+$arm.path+" -output "+$f.path)
		
	End if 
	
End for each 
