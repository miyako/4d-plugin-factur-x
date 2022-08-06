/* --------------------------------------------------------------------------------
 #
 #  4DPlugin-GS.cpp
 #	source generated by 4D Plugin Wizard
 #	Project : GS
 #	author : miyako
 #	2020/05/15
 #  
 # --------------------------------------------------------------------------------*/

#include "4DPlugin-GS.h"

#pragma mark -

void PluginMain(PA_long32 selector, PA_PluginParameters params) {
    
	try
	{
        switch(selector)
        {
			// --- GS
            
			case 1 :
                PDF_TO_PDFA(params);
				break;

        }

	}
	catch(...)
	{

	}
}

#pragma mark -

#if VERSIONMAC
typedef std::vector<std::string>  gsparam_t;
#else
typedef std::vector<std::wstring> gsparam_t;
#endif

static void u8_to_u16(std::string& u8, std::wstring& u16) {
    
#ifdef _WIN32
    int len = MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)u8.c_str(), u8.length(), NULL, 0);
    
    if(len){
        std::vector<uint8_t> buf((len + 1) * sizeof(wchar_t));
        if(MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)u8.c_str(), u8.length(), (LPWSTR)&buf[0], len)){
            u16 = std::wstring((const wchar_t *)&buf[0]);
        }
    }else{
        u16 = std::wstring((const wchar_t *)L"");
    }
#endif
}

static void _(std::string& value, gsparam_t *argv) {
    
#if VERSIONMAC
    argv->push_back(value);
#else
    CUTF16String u16;
    u8_to_u16(value, u16);
    argv->push_back(u16);
#endif
}

static void PDF_TO_PDFA(PA_PluginParameters params) {
    
    sLONG_PTR *pResult = (sLONG_PTR *)params->fResult;
    PackagePtr pParams = (PackagePtr)params->fParameters;
    
    C_TEXT Param1, Param2;
    
    Param1.fromParamAtIndex(pParams, 1);
    Param2.fromParamAtIndex(pParams, 2);
    
    CUTF8String inPdfu8, outPdfu8;
    Param1.copyUTF8String(&inPdfu8);
    Param2.copyUTF8String(&outPdfu8);
    std::string outPdf = "-sOutputFile=";
    outPdf += (const char *)outPdfu8.c_str();
    std::string inPdf = (const char *)inPdfu8.c_str();
    
    C_LONGINT returnValue;
        
    void *minst = NULL;/* must be initialised to NULL, else crash */
    
    gsparam_t _gsargv;//buffer to point
    
    std::vector<std::string>cli;
    
    cli.push_back("-dBATCH");
    cli.push_back("-dNOPAUSE");
    
    /*
     the default since 9.50 (we are using 9.21)
     Enables access controls on files.
     Access controls fall into three categories, files from which Ghostscript is permitted to
     read, ones to which it is permitted to write,
     and ones over which it has "control" (i.e. delete/rename).
     */
    cli.push_back("-dSAFER");

    /*
     Suppresses routine information comments on standard output.
     This is currently necessary when redirecting device output to standard output.
     */
    cli.push_back("-dQUIET");
    
    cli.push_back("-dPDFA=1");//PDFA-1b

    /*
     Set UseCIEColor in the page device dictionary,
     remapping device-dependent color values through a Postscript defined CIE color space.
     If accurate colors are desired, it is recommended that an ICC workflow be used.
     */
    cli.push_back("-dUseCIEColor");
    
    cli.push_back("-dPDFACompatibilityPolicy=2");
    cli.push_back("-sColorConversionStrategy=UseDeviceIndependentColor");
        
    cli.push_back("-sDEVICE=pdfwrite");
    cli.push_back(outPdf);
    cli.push_back("-f");
    cli.push_back(inPdf);
    
    for (std::vector<std::string>::iterator it = cli.begin() ; it != cli.end(); ++it) {
        _(*it, &_gsargv);
    }

    std::vector<char *>gsargv;//just pointers
    
    for(unsigned int i = 0;i < _gsargv.size();++i)
    {
        gsargv.push_back((char *)(_gsargv.at(i).c_str()));
    }
    
    int gsargc = (int)gsargv.size();
    
    if(gsapi_new_instance(&minst, NULL) == 0)
    {
#if VERSIONMAC
        gsapi_set_arg_encoding(minst, GS_ARG_ENCODING_UTF8);
#else
        gsapi_set_arg_encoding(minst, GS_ARG_ENCODING_UTF16LE);
#endif
        
        returnValue.setIntValue(gsapi_init_with_args(minst, gsargc, (char **)&gsargv[0]));
        
        gsapi_exit(minst);//finalises the output
        gsapi_delete_instance(minst);
    }
    
        returnValue.setReturn(pResult);
}

