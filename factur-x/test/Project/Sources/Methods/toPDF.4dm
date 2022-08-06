//%attributes = {}
#DECLARE($formName : Text)->$file : 4D:C1709.File

$folder:=Folder:C1567(Temporary folder:C486; fk platform path:K87:2).folder(Generate UUID:C1066)
$folder.create()

$file:=$folder.file($formName+".pdf")

If (Not:C34(Semaphore:C143(Generic PDF driver:K47:15; 99)))
	
	SET PRINT PREVIEW:C364(False:C215)
	SET CURRENT PRINTER:C787(Generic PDF driver:K47:15)
	
	If (Is macOS:C1572)
		SET PRINT OPTION:C733(Destination option:K47:7; 3; $file.platformPath)
	Else 
		SET PRINT OPTION:C733(Destination option:K47:7; 2; $file.platformPath)
	End if 
	
	SET PRINT OPTION:C733(Spooler document name option:K47:10; $file.fullName)
	
	OPEN PRINTING JOB:C995
	$h:=Print form:C5($formName)
	CLOSE PRINTING JOB:C996
	
Else 
	CLEAR SEMAPHORE:C144(Generic PDF driver:K47:15)
End if 