// ============================================================================
// Allan CORNET - 2011
// ============================================================================
#include "StdAfx.h"
// ============================================================================
#define DLL_NAME_LIBSCILAB L"libscilab.dll"
#define DLL_NAME_API_SCILAB L"api_scilab.dll"
#define DLL_NAME_SCILAB_WINDOWS L"scilab_windows.dll"
#define DLL_NAME_GUI L"scigui.dll"
#define DLL_NAME_CONSOLE L"sciconsole.dll"
#define DLL_NAME_OUTPUT_STREAM L"output_stream.dll"
#define DLL_NAME_CALL_SCILAB L"call_scilab.dll"
// ============================================================================
static HINSTANCE hLibScilabDll = NULL;
static HINSTANCE hApi_ScilabDll = NULL;
static HINSTANCE hScilab_WindowsDll = NULL;
static HINSTANCE hGuiDll = NULL;
static HINSTANCE hConsoleDll = NULL;
static HINSTANCE hOutput_StreamDll = NULL;
static HINSTANCE hCall_ScilabDll = NULL;
// ============================================================================
static unsigned int execID = 0;
// ============================================================================
static bool bSymbolsLoaded = false;
static bool bVisible = false;
// ============================================================================
#define MESSAGE_STACK_SIZE 5
// ============================================================================
typedef struct api_Err
{
	int iErr; /**< The error ID */
	int iMsgCount; /**< Error level */
	char* pstMsg[MESSAGE_STACK_SIZE]; /**< The error message */
} SciErr;
//=============================================================================
typedef struct api_Ctx
{
	char* pstName; /**< Function name */
} StrCtx, *pStrCtx;
// ============================================================================
static StrCtx* pvApiCtx = NULL;
// ============================================================================
#define WINDOWS_MAIN "Windows_Main"
typedef int (*Windows_MainPROC) (HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow);
static Windows_MainPROC dynlib_Windows_Main = NULL;
int Windows_Main(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow)
{
	return (dynlib_Windows_Main)(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
}
// ============================================================================
#define SETVISIBLEMAINWINDOW "setVisibleMainWindow"
typedef void (*setVisibleMainWindowPROC)(BOOL newVisibleState);
static setVisibleMainWindowPROC dynlib_setVisibleMainWindow = NULL;
void setVisibleMainWindow(bool newVisibleState)
{
	BOOL bState = newVisibleState == true ? TRUE : FALSE;
	(dynlib_setVisibleMainWindow)(bState);
	bVisible = newVisibleState;
}
// ============================================================================
bool isVisibleMainWindow(void)
{
	return bVisible;
}
// ============================================================================
#define STOREPRIORITYCOMMANDWITHFLAG "StorePrioritaryCommandWithFlag"
typedef int (*StorePrioritaryCommandWithFlagPROC) (char *command, int flag);
static StorePrioritaryCommandWithFlagPROC dynlib_StorePrioritaryCommandWithFlag = NULL;
static int StorePrioritaryCommandWithFlag (wchar_t *wcommand, int flag)
{
	int iErr = -1;
	if (wcommand)
	{
		char *command = wide_string_to_UTF8(wcommand);
		if (command)
		{
			iErr = dynlib_StorePrioritaryCommandWithFlag(command, flag);
			delete command;
			command = NULL;
		}
	}
	return iErr;
}
// ============================================================================
bool putCommandInScilabQueue(wchar_t *wcommand)
{
	int iErr = -1;
	if (wcommand)
	{
		iErr = StorePrioritaryCommandWithFlag(wcommand, 1);
	}
	return (iErr == 0 ? true : false);
}
// ============================================================================
#define ISEMPTYCOMMANDQUEUE "isEmptyCommandQueue"
typedef int (*isEmptyCommandQueuePROC)(void);
static isEmptyCommandQueuePROC dynlib_isEmptyCommandQueue = NULL;
bool isEmptyCommandQueue(void)
{
	return (dynlib_isEmptyCommandQueue() == 1) ? true : false;
}
// ============================================================================
#define GETLASTERRORVALUE "getLastErrorValue"
typedef int (*getLastErrorValuePROC)(void);
static getLastErrorValuePROC dynlib_getLastErrorValue = NULL;
int getLastErrorValue(void)
{
	return dynlib_getLastErrorValue();
}
// ============================================================================
#define ISNAMEDEMPTYMATRIX "isNamedEmptyMatrix"
typedef int (*isNamedEmptyMatrixPROC)(void* _pvCtx, const char* _pstName);
static isNamedEmptyMatrixPROC dynlib_isNamedEmptyMatrix = NULL;
bool isNamedEmptyMatrix(const wchar_t* _pstName)
{
	bool bEmpty = false;
	if (_pstName)
	{
		char *varname = wide_string_to_UTF8(_pstName);
		if (varname)
		{
			bEmpty = dynlib_isNamedEmptyMatrix(pvApiCtx, varname) == 1 ? true : false;
			delete varname;
			varname = NULL;
		}
	}
	return bEmpty;
}
// ============================================================================
#define CREATENAMEDSINGLEWIDESTRING "createNamedSingleWideString"
typedef int (*createNamedSingleWideStringPROC)(void* _pvCtx, const char* _pstName, const wchar_t* _pwstStrings);
static createNamedSingleWideStringPROC dynlib_createNamedSingleWideString = NULL;
bool createNamedSingleWideString(const wchar_t* _pstName, const wchar_t* _pwstStrings)
{
	int iErr = -1;
	char *varname = wide_string_to_UTF8(_pstName);
	if (varname)
	{
		iErr = dynlib_createNamedSingleWideString( pvApiCtx, varname , _pwstStrings);
		delete varname;
		varname = NULL;
	}
	return (iErr == 0 ? true : false);
}
// ============================================================================
#define GETALLOCATEDNAMEDSINGLEWIDESTRING "getAllocatedNamedSingleWideString"
typedef int (*getAllocatedNamedSingleWideStringPROC)(void* _pvCtx, const char* _pstName, wchar_t** _pwstData);
static getAllocatedNamedSingleWideStringPROC dynlib_getAllocatedNamedSingleWideString = NULL;
bool getAllocatedNamedSingleWideString(const wchar_t* _pstName,  wchar_t** _pwstData)
{
	char *varname = wide_string_to_UTF8(_pstName);
	if (varname)
	{
		int ierr = dynlib_getAllocatedNamedSingleWideString( pvApiCtx, varname, _pwstData);
		delete varname;
		varname = NULL;
		if (ierr == 0) return true;
	}
	return false;
}
// ============================================================================
#define FREEALLOCATEDSINGLEWIDESTRING "freeAllocatedSingleWideString"
typedef void (*freeAllocatedSingleWideStringPROC)(wchar_t* _pwstData);
static freeAllocatedSingleWideStringPROC dynlib_freeAllocatedSingleWideString = NULL;
void freeAllocatedSingleWideString(wchar_t* _pwstData)
{
	if (_pwstData)
	{
		dynlib_freeAllocatedSingleWideString(_pwstData);
	}
}
// ============================================================================
#define SCIRUN "scirun_"
typedef int (*scirunPROC)(char *startupCode, long int startupCode_len);
static scirunPROC dynlib_scirun = NULL;
static bool scirun(wchar_t *wcommand)
{
	bool bOK = false;
	if (wcommand)
	{
		char *command = wide_string_to_UTF8(wcommand);
		if (command)
		{
			dynlib_scirun(command, strlen(command));
			delete command;
			command = NULL;
			bOK = true;
		}
	}
	return bOK;
}
// ============================================================================
static bool bLockExec = false;
int executeCommand(wchar_t *wcommand)
{
	int iErr = -1;

	while(!isEmptyCommandQueue())
	{
		Sleep(1);
	}

	// lock interpreter ONLY ONE Scilab
	while (bLockExec)
	{
		Sleep(1);
	}
	bLockExec = true;

	if (isNamedVarExist(L"__ERROR_EXECSTR__"))
	{
		scirun(L"clear __ERROR_EXECSTR__;quit");
	}

	if (createNamedSingleWideString(L"__EXECSTR_STRING__", wcommand))
	{
		if (isNamedVarExist(L"__EXECSTR_STRING__"))
		{
			std::wstring command_execstr(L"__ERROR_EXECSTR__ = execstr(__EXECSTR_STRING__, \"errcatch\", \"n\");quit");
			scirun((wchar_t*)command_execstr.c_str());
			if (isNamedVarExist(L"__ERROR_EXECSTR__"))
			{
				double dError = 0;
				if (getNamedScalarDouble(L"__ERROR_EXECSTR__", &dError))
				{
					iErr = (int)dError; 
				}
			}
		}
	}

	if (isNamedVarExist(L"__ERROR_EXECSTR__"))
	{
		scirun(L"clear __ERROR_EXECSTR__;quit");
	}

	if (isNamedVarExist(L"__EXECSTR_STRING__"))
	{
		scirun(L"clear __EXECSTR_STRING__;quit");
	}

	scirun(L"quit");

	// unlock interpreter
	bLockExec = false;
	return iErr;
}
// ============================================================================
#define CREATENAMEDSCALARDOUBLE "createNamedScalarDouble"
typedef int (*createNamedScalarDoublePROC)(void* _pvCtx, const char* _pstName, double _dblReal);
static createNamedScalarDoublePROC dynlib_createNamedScalarDouble = NULL;
bool createNamedScalarDouble(const wchar_t* _pstName, double _dblReal)
{
	int iErr = -1;
	if (_pstName)
	{
		char *varname = wide_string_to_UTF8(_pstName);
		if (varname)
		{
			iErr = dynlib_createNamedScalarDouble(pvApiCtx, varname, _dblReal);
			delete [] varname;
			varname = NULL;
		}
	}
	return (iErr == 0 ? true : false);
}
// ============================================================================
#define CREATENAMEDMATRIXOFDOUBLE "createNamedMatrixOfDouble"
typedef SciErr (*createNamedMatrixOfDoublePROC)(void* _pvCtx, const char* _pstName, int _iRows, int _iCols, const double* _pdblReal);
static createNamedMatrixOfDoublePROC dynlib_createNamedMatrixOfDouble = NULL;
bool createNamedMatrixOfDouble(const wchar_t* _pstName, int _iRows, int _iCols, const double* _pdblReal)
{
	if (_pstName)
	{
		char *varname = wide_string_to_UTF8(_pstName);
		if (varname)
		{
			SciErr sciErr = dynlib_createNamedMatrixOfDouble(pvApiCtx, varname, _iRows, _iCols, _pdblReal);
			delete [] varname;
			varname = NULL;
			return (sciErr.iErr == 0 ? true : false);
		}
	}
	return false;
}
// ============================================================================
#define READNAMEDMATRIXOFDOUBLE "readNamedMatrixOfDouble"
typedef SciErr (*readNamedMatrixOfDoublePROC)(void* _pvCtx, const char* _pstName, int* _piRows, int* _piCols, double* _pdblReal);
static readNamedMatrixOfDoublePROC dynlib_readNamedMatrixOfDouble = NULL;
bool getNamedMatrixOfDouble(const wchar_t* _pstName, int* _piRows, int* _piCols, double* _pdblReal)
{
	if (_pstName)
	{
		char *varname = wide_string_to_UTF8(_pstName);
		if (varname)
		{
			SciErr sciErr = dynlib_readNamedMatrixOfDouble(pvApiCtx, varname, _piRows, _piCols, _pdblReal);
			delete [] varname;
			varname = NULL;
			return (sciErr.iErr == 0 ? true : false);
		}
	}
	return false;
}
// ============================================================================
#define ISNAMEDVAREXIST "isNamedVarExist"
typedef int (*isNamedVarExistPROC)(void* _pvCtx, const char* _pstName);
static isNamedVarExistPROC dynlib_isNamedVarExist = NULL;
bool isNamedVarExist(const wchar_t* _pstName)
{
	int iExist = 0;
	if (_pstName)
	{
		char *varname = wide_string_to_UTF8(_pstName);
		if (varname)
		{
			iExist = dynlib_isNamedVarExist(pvApiCtx, varname);
			delete [] varname;
			varname = NULL;
		}
	}
	return (iExist == 1 ? true : false);
}
// ============================================================================
#define GETNAMEDSCALARDOUBLE "getNamedScalarDouble"
typedef int (*getNamedScalarDoublePROC)(void* _pvCtx, const char* _pstName, double* _pdblReal);
static getNamedScalarDoublePROC dynlib_getNamedScalarDouble = NULL;
bool getNamedScalarDouble(const wchar_t* _pstName, double* _pdblReal)
{
	int iErr = -1;
	if (_pstName)
	{
		char *varname = wide_string_to_UTF8(_pstName);
		if (varname)
		{
			iErr = dynlib_getNamedScalarDouble(pvApiCtx, varname, _pdblReal);
			delete [] varname;
			varname = NULL;
		}
	}
	return (iErr == 0 ? true : false);
}
// ============================================================================
#define GETNAMEDSCALARBOOLEAN "getNamedScalarBoolean"
typedef int (*getNamedScalarBooleanPROC)(void* _pvCtx, const char* _pstName, int* _pBool);
static getNamedScalarBooleanPROC dynlib_getNamedScalarBoolean = NULL;
bool getNamedScalarBoolean(const wchar_t* _pstName, bool* _pbool)
{
	int iErr = -1;
	if (_pstName)
	{
		char *varname = wide_string_to_UTF8(_pstName);
		if (varname)
		{
			int bVal = 0;
			iErr = dynlib_getNamedScalarBoolean(pvApiCtx, varname, &bVal);
			*_pbool = (bVal == TRUE) ? true : false;
			delete [] varname;
			varname = NULL;
		}
	}
	return (iErr == 0 ? true : false);
}
// ============================================================================
#define CREATENAMEDSCALARBOOLEAN "createNamedScalarBoolean"
typedef int (*createNamedScalarBooleanPROC)(void* _pvCtx, const char* _pstName, int _BOOL);
static createNamedScalarBooleanPROC dynlib_createNamedScalarBoolean = NULL;
bool createNamedScalarBoolean(const wchar_t* _pstName, bool _bool)
{
	int iErr = -1;
	if (_pstName)
	{
		char *varname = wide_string_to_UTF8(_pstName);
		if (varname)
		{
			iErr = dynlib_createNamedScalarBoolean(pvApiCtx, varname, (_bool == true) ? TRUE : FALSE);
			delete [] varname;
			varname = NULL;
		}
	}
	return (iErr == 0 ? true : false);
}
// ============================================================================
#define READNAMEDCOMPLEXMATRIXOFDOUBLE "readNamedComplexMatrixOfDouble"
typedef SciErr (*readNamedComplexMatrixOfDoublePROC)(void* _pvCtx, const char* _pstName, int* _piRows, int* _piCols, double* _pdblReal, double* _pdblImg);
static readNamedComplexMatrixOfDoublePROC dynlib_readNamedComplexMatrixOfDouble = NULL;
bool getNamedComplexMatrixOfDouble(const wchar_t* _pstName, int* _piRows, int* _piCols, double* _pdblReal, double* _pdblImg)
{
	if (_pstName)
	{
		char *varname = wide_string_to_UTF8(_pstName);
		if (varname)
		{
			SciErr sciErr = dynlib_readNamedComplexMatrixOfDouble(pvApiCtx, varname, _piRows, _piCols, _pdblReal, _pdblImg);
			delete [] varname;
			varname = NULL;
			return (sciErr.iErr == 0 ? true : false);
		}
	}
	return false;
}
// ============================================================================
bool loadSymbols(void)
{
	if (bSymbolsLoaded == false)
	{
		if (loadScilabDlls())
		{
			dynlib_Windows_Main = (Windows_MainPROC) GetProcAddress(hScilab_WindowsDll, WINDOWS_MAIN);
			dynlib_setVisibleMainWindow = (setVisibleMainWindowPROC) GetProcAddress(hGuiDll, SETVISIBLEMAINWINDOW);
			dynlib_StorePrioritaryCommandWithFlag = (StorePrioritaryCommandWithFlagPROC) GetProcAddress(hLibScilabDll, STOREPRIORITYCOMMANDWITHFLAG);
			dynlib_isEmptyCommandQueue = (isEmptyCommandQueuePROC) GetProcAddress(hLibScilabDll, ISEMPTYCOMMANDQUEUE);
			dynlib_scirun = (scirunPROC) GetProcAddress(hLibScilabDll, SCIRUN);
			pvApiCtx = (StrCtx *)(GetProcAddress(hApi_ScilabDll, "pvApiCtx"));
			dynlib_createNamedScalarDouble = (createNamedScalarDoublePROC) GetProcAddress(hApi_ScilabDll, CREATENAMEDSCALARDOUBLE);
			dynlib_isNamedVarExist = (isNamedVarExistPROC) GetProcAddress(hApi_ScilabDll, ISNAMEDVAREXIST);
			dynlib_isNamedEmptyMatrix = (isNamedEmptyMatrixPROC) GetProcAddress(hApi_ScilabDll, ISNAMEDEMPTYMATRIX);
			dynlib_getNamedScalarDouble = (getNamedScalarDoublePROC) GetProcAddress(hApi_ScilabDll, GETNAMEDSCALARDOUBLE);
			dynlib_createNamedSingleWideString = (createNamedSingleWideStringPROC) GetProcAddress(hApi_ScilabDll, CREATENAMEDSINGLEWIDESTRING);
			dynlib_getAllocatedNamedSingleWideString = (getAllocatedNamedSingleWideStringPROC)GetProcAddress(hApi_ScilabDll, GETALLOCATEDNAMEDSINGLEWIDESTRING);
			dynlib_freeAllocatedSingleWideString = (freeAllocatedSingleWideStringPROC)GetProcAddress(hApi_ScilabDll, FREEALLOCATEDSINGLEWIDESTRING);

			dynlib_getNamedScalarBoolean = (getNamedScalarBooleanPROC)GetProcAddress(hApi_ScilabDll, GETNAMEDSCALARBOOLEAN);
			dynlib_createNamedScalarBoolean = (createNamedScalarBooleanPROC)GetProcAddress(hApi_ScilabDll, CREATENAMEDSCALARBOOLEAN);

			dynlib_readNamedComplexMatrixOfDouble = (readNamedComplexMatrixOfDoublePROC)GetProcAddress(hApi_ScilabDll, READNAMEDCOMPLEXMATRIXOFDOUBLE);
			dynlib_createNamedMatrixOfDouble = (createNamedMatrixOfDoublePROC)GetProcAddress(hApi_ScilabDll, CREATENAMEDMATRIXOFDOUBLE);
			dynlib_readNamedMatrixOfDouble = (readNamedMatrixOfDoublePROC)GetProcAddress(hApi_ScilabDll, READNAMEDMATRIXOFDOUBLE);

			dynlib_getLastErrorValue = (getLastErrorValuePROC) GetProcAddress(hOutput_StreamDll, GETLASTERRORVALUE);

			if (dynlib_Windows_Main &&
				dynlib_setVisibleMainWindow &&
				dynlib_StorePrioritaryCommandWithFlag &&
				dynlib_isEmptyCommandQueue &&
				dynlib_scirun &&
				pvApiCtx &&
				dynlib_createNamedScalarDouble &&
				dynlib_isNamedVarExist &&
				dynlib_isNamedEmptyMatrix &&
				dynlib_getNamedScalarDouble &&
				dynlib_getLastErrorValue &&
				dynlib_createNamedSingleWideString &&
				dynlib_getAllocatedNamedSingleWideString &&
				dynlib_freeAllocatedSingleWideString &&
				dynlib_getNamedScalarBoolean &&
				dynlib_createNamedScalarBoolean &&
				dynlib_readNamedComplexMatrixOfDouble &&
				dynlib_createNamedMatrixOfDouble &&
				dynlib_readNamedMatrixOfDouble)
			{
				bSymbolsLoaded = true;
			}
			else
			{
				bSymbolsLoaded = freeSymbols(false);
			}
		}
		else
		{
			bSymbolsLoaded = false;
		}
	}
	return bSymbolsLoaded;
}
//=============================================================================
bool isSymbolsLoaded(void)
{
	return bSymbolsLoaded;
}
//=============================================================================
bool loadScilabDlls(void)
{
	if (!bSymbolsLoaded)
	{
		std::wstring strScilabPath = getScilabPath();
		if (!fileExists(strScilabPath.c_str())) return false;

		std::wstring strScilab_WindowsDllFullFilename(strScilabPath + std::wstring(L"\\bin\\" + std::wstring(DLL_NAME_SCILAB_WINDOWS)));
		if (!fileExists(strScilab_WindowsDllFullFilename.c_str())) return false;

		std::wstring strLibScilabDllFullFilename(strScilabPath + std::wstring(L"\\bin\\" + std::wstring(DLL_NAME_LIBSCILAB)));
		if (!fileExists(strLibScilabDllFullFilename.c_str())) return false;

		std::wstring strApi_ScilabDllFullFilename(strScilabPath + std::wstring(L"\\bin\\" + std::wstring(DLL_NAME_API_SCILAB)));
		if (!fileExists(strApi_ScilabDllFullFilename.c_str())) return false;

		std::wstring strGuiDllFullFilename(strScilabPath + std::wstring(L"\\bin\\" + std::wstring(DLL_NAME_GUI)));
		if (!fileExists(strGuiDllFullFilename.c_str())) return false;

		std::wstring strConsoleDllFullFilename(strScilabPath + std::wstring(L"\\bin\\" + std::wstring(DLL_NAME_CONSOLE)));
		if (!fileExists(strConsoleDllFullFilename.c_str())) return false;

		std::wstring strOutput_StreamDllFullFilename(strScilabPath + std::wstring(L"\\bin\\" + std::wstring(DLL_NAME_OUTPUT_STREAM)));
		if (!fileExists(strOutput_StreamDllFullFilename.c_str())) return false;

		std::wstring strCall_ScilabDllFullFilename(strScilabPath + std::wstring(L"\\bin\\" + std::wstring(DLL_NAME_CALL_SCILAB)));
		if (!fileExists(strCall_ScilabDllFullFilename.c_str())) return false;

		hLibScilabDll = LoadLibraryExW(strLibScilabDllFullFilename.c_str(), NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
		if (hLibScilabDll == NULL) return false;

		hApi_ScilabDll = LoadLibraryExW(strApi_ScilabDllFullFilename.c_str(), NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
		if (hApi_ScilabDll == NULL) return false;

		hScilab_WindowsDll = LoadLibraryExW(strScilab_WindowsDllFullFilename.c_str(), NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
		if (hScilab_WindowsDll == NULL) return false;

		hGuiDll = LoadLibraryExW(strGuiDllFullFilename.c_str(), NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
		if (hGuiDll == NULL) return false;

		hConsoleDll = LoadLibraryExW(strConsoleDllFullFilename.c_str(), NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
		if (hConsoleDll == NULL) return false;

		hOutput_StreamDll = LoadLibraryExW(strOutput_StreamDllFullFilename.c_str(), NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
		if (hOutput_StreamDll == NULL) return false;

		hCall_ScilabDll = LoadLibraryExW(strCall_ScilabDllFullFilename.c_str(), NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
		if (hOutput_StreamDll == NULL) return false;

		return true;
	}
	return false;
}
//=============================================================================
bool freeSymbols(bool bFreeDlls)
{
	if (bSymbolsLoaded)
	{
		if (bFreeDlls) freeScilabDlls();
		if (dynlib_Windows_Main) dynlib_Windows_Main = NULL;
		if (dynlib_setVisibleMainWindow) dynlib_setVisibleMainWindow = NULL;
		if (dynlib_StorePrioritaryCommandWithFlag) dynlib_StorePrioritaryCommandWithFlag = NULL;
		if (dynlib_isEmptyCommandQueue) dynlib_isEmptyCommandQueue = NULL;
		if (dynlib_scirun) dynlib_scirun = NULL;
		if (dynlib_createNamedScalarDouble) dynlib_createNamedScalarDouble = NULL;
		if (dynlib_isNamedVarExist) dynlib_isNamedVarExist = NULL;
		if (dynlib_isNamedEmptyMatrix) dynlib_isNamedEmptyMatrix = NULL;
		if (dynlib_getNamedScalarDouble) dynlib_getNamedScalarDouble = NULL;
		if (dynlib_getLastErrorValue) dynlib_getLastErrorValue = NULL;

		if (dynlib_createNamedSingleWideString) dynlib_createNamedSingleWideString = NULL;
		if (dynlib_getAllocatedNamedSingleWideString) dynlib_getAllocatedNamedSingleWideString = NULL;
		if (dynlib_freeAllocatedSingleWideString) dynlib_freeAllocatedSingleWideString = NULL;

		if (dynlib_getNamedScalarBoolean) dynlib_getNamedScalarBoolean = NULL;
		if (dynlib_createNamedScalarBoolean) dynlib_createNamedScalarBoolean = NULL;

		if (dynlib_readNamedComplexMatrixOfDouble) dynlib_readNamedComplexMatrixOfDouble = NULL;
		if (dynlib_createNamedMatrixOfDouble) dynlib_createNamedMatrixOfDouble = NULL;
		if (dynlib_readNamedMatrixOfDouble) dynlib_readNamedMatrixOfDouble = NULL;

		bSymbolsLoaded = false;
	}
	return bSymbolsLoaded;
}
//=============================================================================
bool freeScilabDlls(void)
{
	if (bSymbolsLoaded)
	{
		if (hLibScilabDll)
		{
			FreeLibrary(hLibScilabDll);
			hLibScilabDll = NULL;
		}

		if (hApi_ScilabDll)
		{
			FreeLibrary(hApi_ScilabDll);
			hApi_ScilabDll = NULL;
		}

		if (hScilab_WindowsDll)
		{
			FreeLibrary(hScilab_WindowsDll);
			hScilab_WindowsDll = NULL;
		}

		if (hGuiDll)
		{
			FreeLibrary(hGuiDll);
			hGuiDll = NULL;
		}

		if (hConsoleDll)
		{
			FreeLibrary(hConsoleDll);
			hConsoleDll = NULL;
		}

		if (hOutput_StreamDll)
		{
			FreeLibrary(hOutput_StreamDll);
			hOutput_StreamDll = NULL;
		}

		if (hCall_ScilabDll)
		{
			FreeLibrary(hCall_ScilabDll);
			hCall_ScilabDll = NULL;
		}

		return true;
	}
	return false;
}
//=============================================================================
