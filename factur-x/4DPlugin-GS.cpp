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
                
            case 2 :
                PDFA_GET_XML(params);
                break;
                
            case 3 :
                PDFA_SET_XML(params);
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

#if VERSIONWIN

#define GS_BUFFER_SIZE 4096

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

static void u16_to_u8(std::wstring& u16, std::string& u8) {

#ifdef _WIN32
    int len = WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)u16.c_str(), u16.length(), NULL, 0, NULL, NULL);

    if (len) {
        std::vector<uint8_t> buf(len + 1);
        if (WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)u16.c_str(), u16.length(), (LPSTR)&buf[0], len, NULL, NULL)) {
            u8 = std::string((const char *)&buf[0]);
        }
    }
    else {
        u8 = std::string((const char *)"");
    }
#endif
}

#endif

#if VERSIONWIN

static void launchTaskForCLI(std::wstring& name,
                             std::wstring& arg1,
                             std::wstring& arg2,
                             std::wstring& arg3,
                             PA_CollectionRef arg4,
                             PA_ObjectRef returnValue
                             ) {

    std::string info;
    bool success = false;
    int terminationStatus = -1;
    
    wchar_t thisPath[_MAX_PATH] = {0};
    wchar_t fDrive[_MAX_DRIVE], fDir[_MAX_DIR], fName[_MAX_FNAME], fExt[_MAX_EXT];
    
    HMODULE hplugin = GetModuleHandleW(L"Factur-X.4DX");
    
    if(hplugin) {
        
        GetModuleFileNameW(hplugin, thisPath, _MAX_PATH);
        _wsplitpath_s(thisPath, fDrive, fDir, fName, fExt);
        
        std::wstring path = fDrive;
        path += fDir;//path to plugin parent folder (windows64)
        
        std::wstring currentDirectoryPath = path;
        
        path += name;
        path += L".exe";
        
        std::wstring arguments = L"\"";
        arguments += path;
        arguments += L"\"";
        
        if(arg1.length() != 0) {
            arguments += L" \"";
            arguments += arg1;
            //remove delimiter to avoid open-ended escape sequence
            if(arguments.at(arguments.size() - 1) == L'\\')
                arguments = arguments.substr(0, arguments.size() - 1);
            arguments += L"\"";
        }
        
        if(arg2.length() != 0) {
            arguments += L" \"";
            arguments += arg2;
            //remove delimiter to avoid open-ended escape sequence
            if(arguments.at(arguments.size() - 1) == L'\\')
                arguments = arguments.substr(0, arguments.size() - 1);
            arguments += L"\"";
        }

        if(arg3.length() != 0) {
            arguments += L" \"";
            arguments += arg3;
            //remove delimiter to avoid open-ended escape sequence
            if(arguments.at(arguments.size() - 1) == L'\\')
                arguments = arguments.substr(0, arguments.size() - 1);
            arguments += L"\"";
        }

        std::vector<wchar_t> buf(32768);
		wchar_t *p = (wchar_t *)&buf[0];
        wchar_t *commandLine = (wchar_t *)p;
        p += arguments.copy((wchar_t *)p, arguments.size());
        
        if(arg4 != NULL) {
            PA_long32 count = PA_GetCollectionLength(arg4);
            for(PA_long32 i = 0; i < count; ++i) {
                PA_Variable v = PA_GetCollectionElement(arg4, i);
                if(PA_GetVariableKind(v) == eVK_Unistring) {
                    PA_Unistring u16 = PA_GetStringVariable(v);
					std::wstring v((const wchar_t *)u16.fString, u16.fLength);
                    if(v.size())
                    {
                        std::wstring arg = L" \"";
                        arg += v;
                        //remove delimiter to avoid open-ended escape sequence
                        if(arg.at(arg.size() - 1) == L'\\')
                            arg = arg.substr(0, arg.size() - 1);
                        arg += L"\"";
                        p += arg.copy(p, arg.size());
                    }
                }
            }
        }

		SECURITY_ATTRIBUTES saAttr;
		saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
		saAttr.bInheritHandle = TRUE;
		saAttr.lpSecurityDescriptor = NULL;

		HANDLE hOut = INVALID_HANDLE_VALUE;
		HANDLE hRedir = INVALID_HANDLE_VALUE;

		// Create Temp File for redirection

		wchar_t szTempPath[_MAX_PATH];
		wchar_t szOutput[_MAX_PATH];
		GetTempPath(_MAX_PATH, szTempPath);
		GetTempFileName(szTempPath, L"tmp", 0, szOutput);

		hOut = CreateFile(szOutput,
			GENERIC_WRITE,
			FILE_SHARE_READ,
			&saAttr,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_TEMPORARY,
			0);

		hRedir = CreateFile(szOutput,
			GENERIC_READ,
			FILE_SHARE_WRITE,
			0,
			OPEN_EXISTING,
			0,
			0);

        STARTUPINFO si;
        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
		if ((hOut != INVALID_HANDLE_VALUE) && (hRedir != INVALID_HANDLE_VALUE)) {
			si.dwFlags |= STARTF_USESTDHANDLES;
			si.hStdError = hOut;
			si.hStdOutput = hOut;
		}
        si.dwFlags |=STARTF_USESHOWWINDOW;
        si.wShowWindow = SW_HIDE;

		PROCESS_INFORMATION pi;
        ZeroMemory(&pi, sizeof(pi));

		std::vector<uint8_t>infobuf(GS_BUFFER_SIZE);

        if (CreateProcess(
                          NULL,
                          commandLine,
                          NULL,
                          NULL,
                          TRUE,
                          0,    //CREATE_NO_WINDOW | CREATE_UNICODE_ENVIRONMENT
                          NULL,    //pointer to the environment block for the new process
                          currentDirectoryPath.c_str(),
                          &si,
                          &pi
                          ))
        {            
            time_t started, passed;
            BOOL exited = 0;
            int TO = 9;
            
            started = time(0);
            time_t startTime = started;
            
            for (
                 time_t now = started;
                 !exited && ((passed = now - started) < TO);
                 now = time(0)
                 )
            {
                DWORD exitCode;
                if (GetExitCodeProcess(pi.hProcess, &exitCode))
                {
                    if(exitCode != STILL_ACTIVE)
                    {
                        exited = 1;
                    }
                };

                if (!exited)
                {
                    time_t now = time(0);
                    time_t elapsedTime = abs(startTime - now);
                    if (elapsedTime > 0)
                    {
                        startTime = now;
                        PA_YieldAbsolute();
                    }
                }
            }
            
            DWORD exitCode;
            if (GetExitCodeProcess(pi.hProcess, &exitCode))
            {
                if(exitCode == STILL_ACTIVE)
                {
                    TerminateProcess(pi.hProcess, 1);
                }else {

					for (;;)
					{
						ZeroMemory(&infobuf[0], infobuf.size());

						DWORD dwRead;
						BOOL bSuccess;

						bSuccess = ReadFile(hRedir, &infobuf[0], GS_BUFFER_SIZE - 1, &dwRead, NULL);

						if (!bSuccess || dwRead == 0)
							break;

						std::string u8((const char *)&infobuf[0], dwRead);
						info += u8;

					}

                    terminationStatus = exitCode;	

                }

            };

            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);

			CloseHandle(hOut);
			CloseHandle(hRedir);
			DeleteFile(szOutput);
        }
    }
       
    if(terminationStatus == 0) {
        success = true;
    }
    
    ob_set_s(returnValue, L"info", info.c_str());
    ob_set_b(returnValue, L"success", success);
    ob_set_n(returnValue, L"terminationStatus", terminationStatus);
}

#endif

#if VERSIONMAC

static NSString *pathForCLI(NSString *name) {
    
    NSBundle *b = [NSBundle bundleWithIdentifier:@"com.4D.Factur-X"];
    
    if(b){
        
        return [
            [
                [b executablePath]
                stringByDeletingLastPathComponent
            ]
            stringByAppendingPathComponent:name
        ];
        
    }
    
    return nil;
}

static bool waitTaskUntilExitWithTimeout(NSTask *task, CFTimeInterval TO, BOOL SENDTERM, BOOL SENDKILL) {
    
    CFAbsoluteTime      started;
    CFAbsoluteTime      passed;
    BOOL                exited = NO;

    started = CFAbsoluteTimeGetCurrent();
    for (
         CFAbsoluteTime now = started;
         !exited && ((passed = now - started) < TO);
         now = CFAbsoluteTimeGetCurrent()
         )
    {
        if (![task isRunning])
        {
            exited = YES;
        } else {

            CFAbsoluteTime sleepTime = 0.1;
            useconds_t sleepUsec = round(sleepTime * 1000000.0);
            if (sleepUsec == 0) sleepUsec = 1;
            PA_YieldAbsolute();
        }
    }

    if (!exited)
    {
        //NSLog(@"%@ didn't exit after timeout of %0.2f sec", self, TO);

        if (SENDTERM)
        {
            TO = 2; // 2 second timeout, waiting for SIGTERM to kill process

            [task terminate];

            started = CFAbsoluteTimeGetCurrent();
            for (
                 CFAbsoluteTime now = started;
                 !exited && ((passed = now - started) < TO);
                 now = CFAbsoluteTimeGetCurrent()
                 )
            {
                if (![task isRunning])
                {
                    exited = YES;
                } else {
                    PA_YieldAbsolute();
                }
            }
        }

        if (!exited && SENDKILL)
        {
            TO = 2; // 2 second timeout, waiting for SIGKILL to kill process

            pid_t pid = [task processIdentifier];
            kill(pid, SIGKILL);

            started = CFAbsoluteTimeGetCurrent();
            for (
                 CFAbsoluteTime now = started;
                 !exited && ((passed = now - started) < TO);
                 now = CFAbsoluteTimeGetCurrent()
                 )
            {
                if (![task isRunning])
                {
                    exited = YES;
                } else {
                    PA_YieldAbsolute();
                }
            }
        }
    }

    return exited;
}

static void launchTaskForCLI(NSString *name, PA_ObjectRef returnValue, NSTask *task) {
    
    NSString *path = pathForCLI(name);
    task.launchPath = path;
    
    std::string info;
    bool success = false;
    int terminationStatus = -1;

    NSPipe *pipe = [NSPipe pipe];
    NSFileHandle *file = pipe.fileHandleForReading;
    task.standardError = pipe;
    
    //this crashed 4D!
    
    /*
     __block std::string info;
     __block bool success = false;
     __block int terminationStatus = 0;
     
    task.terminationHandler = ^(NSTask *task){

        NSData *data = [file readDataToEndOfFile];
        if(data) {
            NSString *_info = [[NSString alloc]initWithData:data encoding:NSUTF8StringEncoding];
            if(_info) {
                info = [_info UTF8String];
                [_info release];
            }
        }
        
        terminationStatus = task.terminationStatus;
        
        if(terminationStatus == 0) {
            success = true;
        }
        
    };
     */
    
    [task launch];
    
    waitTaskUntilExitWithTimeout(task, 9, true, true);
    
    terminationStatus = task.terminationStatus;
    
    NSData *data = [file readDataToEndOfFile];
    if(data) {
        NSString *_info = [[NSString alloc]initWithData:data encoding:NSUTF8StringEncoding];
        if(_info) {
            info = [_info UTF8String];
            [_info release];
        }
    }
    
    if(terminationStatus == 0) {
        success = true;
    }
    
    [file closeFile];
    
    ob_set_s(returnValue, L"info", info.c_str());
    ob_set_b(returnValue, L"success", success);
    ob_set_n(returnValue, L"terminationStatus", terminationStatus);
}

#endif

static void PDFA_SET_XML(PA_PluginParameters params) {

    PackagePtr pParams = (PackagePtr)params->fParameters;
    
    C_TEXT Param1, Param2, Param3;
    
    Param1.fromParamAtIndex(pParams, 1);
    Param2.fromParamAtIndex(pParams, 2);
    Param3.fromParamAtIndex(pParams, 3);
    
    PA_CollectionRef Param4 = PA_GetCollectionParameter(params, 4);
    
    PA_ObjectRef returnValue = PA_CreateObject();
    
#if VERSIONMAC
    
    NSString *inPathPDF, *inPathXML, *outPath;
    inPathPDF = Param1.copyUTF16String();
    inPathXML = Param2.copyUTF16String();
    outPath = Param3.copyUTF16String();

    NSTask *task = [[NSTask alloc]init];
    NSMutableArray *arguments = [[NSMutableArray alloc]initWithArray:@[inPathPDF, inPathXML, outPath]];
    
    PA_long32 count = PA_GetCollectionLength(Param4);
    for(PA_long32 i = 0; i < count; ++i) {
        PA_Variable v = PA_GetCollectionElement(Param4, i);
        if(PA_GetVariableKind(v) == eVK_Unistring) {
            PA_Unistring u16 = PA_GetStringVariable(v);
            NSString *s = [[NSString alloc]initWithCharacters:u16.fString length:u16.fLength];;
            [arguments addObject:s];
            [s release];
        }
    }
    
    task.arguments = arguments;
    
    launchTaskForCLI(@"facturx-pdfgen", returnValue, task);
 
    [task release];
    
    [outPath release];
    [inPathXML release];
    [inPathPDF release];
    
#else
    
    CUTF16String _inPathPDF, _inPathXML, _outPath;
    Param1.copyUTF16String(&_inPathPDF);
    Param2.copyUTF16String(&_inPathXML);
    Param3.copyUTF16String(&_outPath);
    std::wstring inPathPDF = (const wchar_t *)_inPathPDF.c_str();
    std::wstring inPathXML = (const wchar_t *)_inPathXML.c_str();
    std::wstring outPath = (const wchar_t *)_outPath.c_str();
	std::wstring name = L"facturx-pdfgen";

    launchTaskForCLI(name, inPathPDF, inPathXML, outPath, Param4, returnValue);
    
#endif
    
    PA_ReturnObject(params, returnValue);
}

static void PDFA_GET_XML(PA_PluginParameters params) {

    PackagePtr pParams = (PackagePtr)params->fParameters;
    
    C_TEXT Param1, Param2;
    
    Param1.fromParamAtIndex(pParams, 1);
    Param2.fromParamAtIndex(pParams, 2);
    
    PA_ObjectRef returnValue = PA_CreateObject();

#if VERSIONMAC

    NSString *inPath, *outPath;
    inPath = Param1.copyUTF16String();
    outPath = Param2.copyUTF16String();

    NSTask *task = [[NSTask alloc]init];
    task.arguments = @[inPath, outPath];
    
    launchTaskForCLI(@"facturx-pdfextractxml", returnValue, task);
 
    [task release];
    
    [outPath release];
    [inPath release];

#else
    
    CUTF16String _inPath, _outPath;
    Param1.copyUTF16String(&_inPath);
    Param2.copyUTF16String(&_outPath);
    std::wstring inPath = (const wchar_t *)_inPath.c_str();
    std::wstring outPath = (const wchar_t *)_outPath.c_str();
	std::wstring path;
	std::wstring name = L"facturx-pdfextractxml";

    launchTaskForCLI(name, inPath, outPath, path, NULL, returnValue);
    
#endif
    
    PA_ReturnObject(params, returnValue);
}

static void makeArguments(std::string& value, gsparam_t *argv) {
    
#if VERSIONMAC
    argv->push_back(value);
#else
    std::wstring u16;
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
    
    cli.push_back("-dPDFA=3");

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
        makeArguments(*it, &_gsargv);
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
