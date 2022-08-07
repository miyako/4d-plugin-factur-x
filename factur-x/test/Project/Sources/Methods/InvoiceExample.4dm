//%attributes = {"invisible":true}
#DECLARE()->$invoice : Object

$invoice:=New object:C1471

$ExchangedDocument:=New object:C1471
$invoice.ExchangedDocument:=$ExchangedDocument
$ExchangedDocument.ID:="471102"
$ExchangedDocument.TypeCode:="380"

$ExchangedDocument.IssueDateTime:=New object:C1471
$ExchangedDocument.IssueDateTime.DateTimeString:=New object:C1471
$ExchangedDocument.IssueDateTime.DateTimeString.format:="102"
$ExchangedDocument.IssueDateTime.DateTimeString.value:="20200305"

$IncludedNote:=New collection:C1472
$ExchangedDocument.IncludedNote:=$IncludedNote
$IncludedNote[0]:=New object:C1471
$IncludedNote[0].Content:="Rechnung gemäß Bestellung vom 01.03.2020."

$IncludedNote[1]:=New object:C1471
$IncludedNote[1].Content:="Lieferant GmbH\r\nLieferantenstraße 20\r\n80333 München\r\nDeutschland\r\nGeschäftsführer: Hans Muster\r\nHandelsregisternummer: H A 123"

$IncludedNote[2]:=New object:C1471
$IncludedNote[2].Content:="Unsere GLN: 4000001123452\r\nIhre GLN: 4000001987658\r\nIhre Kundennummer: GE2020211\r\n\r\n\r\nZahlbar innerhalb 30 Tagen netto bis 04.04.2020, 3% Skonto innerhalb 10 Tagen bis 15.03.2020."

$SupplyChainTradeTransaction:=New object:C1471
$invoice.SupplyChainTradeTransaction:=$SupplyChainTradeTransaction

$ApplicableHeaderTradeAgreement:=New object:C1471
$ApplicableHeaderTradeDelivery:=New object:C1471
$ApplicableHeaderTradeSettlement:=New object:C1471

$SupplyChainTradeTransaction.ApplicableHeaderTradeAgreement:=$ApplicableHeaderTradeAgreement
$SupplyChainTradeTransaction.ApplicableHeaderTradeDelivery:=$ApplicableHeaderTradeDelivery
$SupplyChainTradeTransaction.ApplicableHeaderTradeSettlement:=$ApplicableHeaderTradeSettlement

$TradeLineItem:=New collection:C1472
$TradeLineItem[0]:=New object:C1471

$SupplyChainTradeTransaction.IncludedSupplyChainTradeLineItem:=$TradeLineItem
$TradeLineItem[0].AssociatedDocumentLineDocument:=New object:C1471
$TradeLineItem[0].AssociatedDocumentLineDocument.LineID:="1"

$TradeLineItem[0].SpecifiedTradeProduct:=New object:C1471
$TradeLineItem[0].SpecifiedTradeProduct.GlobalID:=New object:C1471
$TradeLineItem[0].SpecifiedTradeProduct.GlobalID.schemeID:="0160"
$TradeLineItem[0].SpecifiedTradeProduct.GlobalID.value:="4012345001235"
$TradeLineItem[0].SpecifiedTradeProduct.Name:="GTIN: 4012345001235\r\nUnsere Art.-Nr.: TB100A4\r\nTrennblätter A4"

$TradeLineItem[0].SpecifiedLineTradeAgreement:=New object:C1471
$TradeLineItem[0].SpecifiedLineTradeAgreement.NetPriceProductTradePrice:=New object:C1471
$TradeLineItem[0].SpecifiedLineTradeAgreement.NetPriceProductTradePrice.ChargeAmount:="9.90"

$TradeLineItem[0].SpecifiedLineTradeDelivery:=New object:C1471
$TradeLineItem[0].SpecifiedLineTradeDelivery.BilledQuantity:=New object:C1471
$TradeLineItem[0].SpecifiedLineTradeDelivery.BilledQuantity.unitCode:="H87"
$TradeLineItem[0].SpecifiedLineTradeDelivery.BilledQuantity.value:="20.0000"

$TradeLineItem[0].SpecifiedLineTradeSettlement:=New object:C1471
$TradeLineItem[0].SpecifiedLineTradeSettlement.ApplicableTradeTax:=New object:C1471
$TradeLineItem[0].SpecifiedLineTradeSettlement.ApplicableTradeTax.TypeCode:="VAT"
$TradeLineItem[0].SpecifiedLineTradeSettlement.ApplicableTradeTax.CategoryCode:="S"
$TradeLineItem[0].SpecifiedLineTradeSettlement.ApplicableTradeTax.RateApplicablePercent:="19"

$TradeLineItem[0].SpecifiedLineTradeSettlement.SpecifiedTradeSettlementLineMonetarySummation:=New object:C1471
$TradeLineItem[0].SpecifiedLineTradeSettlement.SpecifiedTradeSettlementLineMonetarySummation.LineTotalAmount:="198.00"

$SellerTradeParty:=New object:C1471
$ApplicableHeaderTradeAgreement.SellerTradeParty:=$SellerTradeParty
$SellerTradeParty.Name:="Lieferant GmbH"
$SellerTradeParty.PostalTradeAddress:=New object:C1471
$SellerTradeParty.PostalTradeAddress.PostcodeCode:="80333"
$SellerTradeParty.PostalTradeAddress.LineOne:="Lieferantenstraße 20"
$SellerTradeParty.PostalTradeAddress.LineTwo:=""
$SellerTradeParty.PostalTradeAddress.CityName:="München"
$SellerTradeParty.PostalTradeAddress.CountryID:="DE"

$SellerTradeParty.SpecifiedTaxRegistration:=New collection:C1472
$SellerTradeParty.SpecifiedTaxRegistration[0]:=New object:C1471
$SellerTradeParty.SpecifiedTaxRegistration[0].schemeID:="FC"
$SellerTradeParty.SpecifiedTaxRegistration[0].value:="201/113/40209"
$SellerTradeParty.SpecifiedTaxRegistration[1]:=New object:C1471
$SellerTradeParty.SpecifiedTaxRegistration[1].schemeID:="VA"
$SellerTradeParty.SpecifiedTaxRegistration[1].value:="DE123456789"

$BuyerTradeParty:=New object:C1471
$ApplicableHeaderTradeAgreement.BuyerTradeParty:=$BuyerTradeParty
$BuyerTradeParty.Name:="Kunden AG Mitte"
$BuyerTradeParty.PostalTradeAddress:=New object:C1471
$BuyerTradeParty.PostalTradeAddress.PostcodeCode:="69876"
$BuyerTradeParty.PostalTradeAddress.LineOne:="Hans Muster"
$BuyerTradeParty.PostalTradeAddress.LineTwo:="Kundenstraße 15"
$BuyerTradeParty.PostalTradeAddress.CityName:="Frankfurt"
$BuyerTradeParty.PostalTradeAddress.CountryID:="DE"

$ActualDeliverySupplyChainEvent:=New object:C1471

$ApplicableHeaderTradeDelivery.ActualDeliverySupplyChainEvent:=$ActualDeliverySupplyChainEvent
$ActualDeliverySupplyChainEvent.OccurrenceDateTime:=New object:C1471
$ActualDeliverySupplyChainEvent.OccurrenceDateTime.DateTimeString:=New object:C1471
$ActualDeliverySupplyChainEvent.OccurrenceDateTime.DateTimeString.format:="102"
$ActualDeliverySupplyChainEvent.OccurrenceDateTime.DateTimeString.value:="20200305"

$ApplicableHeaderTradeSettlement.InvoiceCurrencyCode:="EUR"
$ApplicableTradeTax:=New object:C1471
$ApplicableHeaderTradeSettlement.ApplicableTradeTax:=$ApplicableTradeTax
$ApplicableTradeTax.CalculatedAmount:="37.62"
$ApplicableTradeTax.TypeCode:="VAT"
$ApplicableTradeTax.BasisAmount:="198.00"
$ApplicableTradeTax.CategoryCode:="S"
$ApplicableTradeTax.RateApplicablePercent:="19.00"

$PaymentTerms:=New object:C1471
$ApplicableHeaderTradeSettlement.SpecifiedTradePaymentTerms:=$PaymentTerms
$PaymentTerms.DueDateDateTime:=New object:C1471
$PaymentTerms.DueDateDateTime.DateTimeString:=New object:C1471
$PaymentTerms.DueDateDateTime.DateTimeString.format:="102"
$PaymentTerms.DueDateDateTime.DateTimeString.value:="20200404"

$MonetarySummation:=New object:C1471
$ApplicableHeaderTradeSettlement.SpecifiedTradeSettlementHeaderMonetarySummation:=$MonetarySummation
$MonetarySummation.LineTotalAmount:="198.00"
$MonetarySummation.ChargeTotalAmount:="0.00"
$MonetarySummation.AllowanceTotalAmount:="0.00"
$MonetarySummation.TaxBasisTotalAmount:="198.00"
$MonetarySummation.TaxTotalAmount:=New object:C1471
$MonetarySummation.TaxTotalAmount.currencyID:="EUR"
$MonetarySummation.TaxTotalAmount.value:="37.62"
$MonetarySummation.GrandTotalAmount:="235.62"
$MonetarySummation.DuePayableAmount:="235.62"