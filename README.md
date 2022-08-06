# 4d-plugin-factur-x
research project

## PDF/A

*first step is to create a [PDF/A](https://en.wikipedia.org/wiki/PDF/A) document.*

### Validator

1. install OpenJDK

https://formulae.brew.sh/cask/temurin

```
brew install --cask temurin
```

2. install VeraPDF

https://docs.verapdf.org/install/

### Validate 4D print to PDF

**VeraPDF** validation reports failure in 2 domains.

* ISO 19005-1:2005@6.7.2: The document catalog dictionary of a conforming file shall contain the Metadata key.

* ISO 19005-1:2005@6.7.3: If a document information dictionary does appear at a document, then all of its entries that have analogous properties in predefined XMP schemas, shall also be embedded in the file in XMP form with equivalent values.

we are not using any banned features, at the same time, we have no metadata. the PDF is *too* basic.

### PDF→PDF/A

use **GhostScript** to prepare PDF for archive.

* https://stackoverflow.com/questions/1659147/how-to-use-ghostscript-to-convert-pdf-to-pdf-a-or-pdf-x
* https://stackoverflow.com/questions/57167784/ghostscript-wont-generate-pdf-a-with-utf16be-text-string-detected-in-docinfo

```4d
$error:=PDF TO PDFA($input; $output)
```

**Note**: warning message

```
Use of -dUseCIEColor detected!
Since the release of version 9.11 of Ghostscript we recommend you do not set
-dUseCIEColor with the pdfwrite/ps2write device family.
```

## Factur-X

*next step is to extract, edit and embed XML in PDF.*

* [akretion/factur-x](https://github.com/akretion/factur-x)
* [pyinstaller](https://pyinstaller.org/en/stable/)

```
pip3 install -U factur-x 
pip3 install -U pyinstaller
```

```
cd /opt/homebrew/bin
```

or 

```
cd /usr/local/bin
```

```
pyinstaller facturx-pdfextractxml
pyinstaller facturx-pdfgen
pyinstaller facturx-webservice 
pyinstaller facturx-xmlcheck
```
```4d
$status:=PDFA GET XML($inPDF; $outXML)
$status:=PDFA SET XML($inPDF; $inXML; $outPDF{; $attachments})
```

* "GET" internally calls *facturx-pdfextractxml*
* "SET" internally calls *facturx-pdfgen*

## Distribtution

a very large plugin. 

contains **python** for Apple Silicon and Intel. contains **factur-x** and all its dependencies. also contains **ghostscript** for Apple Silicon and Intel.

## Examples

```4d
/*
	
	generate electronic invoice data (XML)
	
*/

$invoice:=InvoiceExample
$template:=Folder(fk resources folder).file("template.xml")
$data:=toXML($invoice; $template)
$XML:=Folder(Temporary folder; fk platform path).file("data.xml")
$XML.setText($data)

/*
	
	generate PDF using native printing commands (result is not PDF/A)
	
*/

$PDF:=toPDF("TEST")

/*
	
	convert to PDF/A; internally using ghostscript
	
*/

$PDFA:=Folder(Temporary folder; fk platform path).file("TEST.pdf")
$error:=PDF TO PDFA($PDF.path; $PDFA.path)

If ($error=0)
	
	$output:=Folder(fk desktop folder).file("TEST.pdf")
	
	If ($output.exists)
		$output.delete()  //library with not overwrite existing file
	End if 
	
	$status:=PDFA SET XML($PDFA.path; $XML.path; $output.path)
	$info:=Split string($status.info; "\n")
	
	If ($status.success)
		SHOW ON DISK($output.platformPath)
	End if 
	
End if
```
