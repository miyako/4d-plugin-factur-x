# 4d-plugin-factur-x
research project

## PDF/A

first step is to create a [PDF/A](https://en.wikipedia.org/wiki/PDF/A) document. 

1. install OpenJDK 

https://formulae.brew.sh/cask/temurin

```
brew install --cask temurin
```

2. install VeraPDF

https://docs.verapdf.org/install/

3. print a form using standard 4D printing commands.

### Result

**VeraPDF** validation reports failure in 2 domains.

* ISO 19005-1:2005@6.7.2: The document catalog dictionary of a conforming file shall contain the Metadata key.

* ISO 19005-1:2005@6.7.3: If a document information dictionary does appear at a document, then all of its entries that have analogous properties in predefined XMP schemas, shall also be embedded in the file in XMP form with equivalent values.

we are not using any banned features, at the same time, we have no metadata. the PDF is *too* basic.

### Next

use GhostScript to add missing elements to PDF.


