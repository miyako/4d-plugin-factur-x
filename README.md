![version](https://img.shields.io/badge/version-19%2B-5682DF)
![platform](https://img.shields.io/static/v1?label=platform&message=mac-intel%20|%20mac-arm%20|%20win-64&color=blue)
[![license](https://img.shields.io/github/license/miyako/4d-plugin-factur-x)](LICENSE)
![downloads](https://img.shields.io/github/downloads/miyako/4d-plugin-factur-x/total)

# 4d-plugin-factur-x
Convert PDF to PDF/A-3. combine XML and PDF to generate Factur-X.

## PDF/A

*first step is to create a [PDF/A](https://en.wikipedia.org/wiki/PDF/A) document.*

if you don't care why we need this, jump to [Factur-X](https://github.com/miyako/4d-plugin-factur-x/blob/main/README.md#factur-x)

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

if you don't care how it works, jump to [Distribution](https://github.com/miyako/4d-plugin-factur-x/blob/main/README.md#distribtution)

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

contains **python** for Apple Silicon and Intel and Windows 64-bit. contains **factur-x** and all its dependencies such as **PyPDF4**, **lxml**. also contains **ghostscript** for Apple Silicon and Intel and Windows 64-bit.

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

/*
	
	convert to Factur-X internally using python
	
*/

If ($error=0)
	
	$output:=Folder(fk desktop folder).file("TEST.pdf")
	
	If ($output.exists)
		$output.delete()  //library will not overwrite existing file
	End if 
	
	$status:=PDFA SET XML($PDFA.path; $XML.path; $output.path)
	$info:=Split string($status.info; "\n")
	
	If ($status.success)
		SHOW ON DISK($output.platformPath)
	End if 
	
End if
```

## Validate 

* https://services.fnfe-mpe.org/account/home

<img width="561" alt="スクリーンショット 2022-08-07 0 39 55" src="https://user-images.githubusercontent.com/1725068/183255935-10686b54-ec51-4db8-a59a-d1626043aed0.png">

## Note for Windows

* `pip3 install -U factur-x` might fail because of hard-coded folder separators in [MANIFEST.in](https://github.com/akretion/factur-x/blob/master/MANIFEST.in). download the repo, edit the file and `pip` on a local path.

* some XSD files have extra long names. see [Maximum Path Length Limitation](https://docs.microsoft.com/en-us/windows/win32/fileio/maximum-file-path-limitation?tabs=registry#enable-long-paths-in-windows-10-version-1607-and-later)
