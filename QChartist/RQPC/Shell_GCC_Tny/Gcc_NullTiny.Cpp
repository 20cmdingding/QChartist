//
// ------------------------------------------------------------------
// RQPC V 0.1   C++ GCC    ByteCode Launcher         Nov 2006, Jacques
// + Run Time Linked (RTL) in RapidQ  full  C++/GCC   Function
// ------------------------------------------------------------------
// ==================================================================
// Executes a RapidQ Gui or Console bytecode appended to this executable
// The Console will always be Shown.
// 1024 command line arguments possible
// Icon of any size must be set in a resource file: icon.rc
// Compile me:RqTiny.Cpp with
// c:\MinGw\Bin\windres -i icon.rc -o icon.o
// c:\MinGw\Bin\g++ -O -s -o main RqTiny.cpp icon.o -mwindows
//
// I am not a great window programmer, remarks at erdemaal@yahoo.fr
//
// This code will be modyfied by RqPreCompiler to create a Console or
// not, to encrypt bytecode or not and to select which version of
// RapidQ32.Dll to use. Then recompiled to obj, then relinked with your
// selected Icon .Obj file.
// ==================================================================
//
#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//
typedef int (__stdcall *RQ_EXECUTEMEMORY) (int i1, int i2, int i3, int i4);
//
// ==== GCC C++:  ENCRYPT.INC =======================================
int __stdcall Encrypt (int Arg1, int Arg2, int Arg3, int Arg4)  {
    asm(".intel_syntax noprefix");
    asm("pop ebp");
    asm(".byte 0x55,0x89,0xE5,0x83,0xEC,0x04,0x53,0x56,0x57,0xC7,0x45,0xFC");
    asm(".byte 0x00,0x00,0x00,0x00,0x8B,0x75,0x08,0x8B,0x55,0x0C,0x83,0xEA");
    asm(".byte 0x04,0x83,0xFA,0x04,0x72,0x0F,0x8B,0x06,0xC1,0xC0,0x03,0x89");
    asm(".byte 0x06,0x83,0xEA,0x04,0x83,0xC6,0x04,0xEB,0xEC,0xC7,0x45,0xFC");
    asm(".byte 0x00,0x00,0x00,0x00,0x8B,0x45,0xFC,0x5F,0x5E,0x5B,0x89,0xEC");
    asm(".byte 0x5D,0xC2,0x10,0x00");
    asm(".att_syntax noprefix");
    }
// ==== GCC C++: end of ENCRYPT.INC =================================
//
// ----------------------------------------------------------------------
// ---- User Functions and RTL with RapidQ Here -------------------------
// ----------------------------------------------------------------------
// Functions are runtime linked to RQ bytecode via a String NameAddress
// of format  ";name,Address;" passed via two Environment variables
// "ptrNameAddress" "lenNameAddress"  (not compiler dependent)
//
// Global Variable RunTimeLinker String
// ------------------------------------
char Name__Address[32768];
//
// Function Add Name and Address to String Name__Address
// -----------------------------
void AddName__Address (char *FuncName, int FuncPtr) {
     char sInt2Str[16];
     strcat (Name__Address, FuncName);
     strcat (Name__Address, ",");
     ltoa (FuncPtr, sInt2Str, 10); 
     strcat (Name__Address, sInt2Str);
     strcat (Name__Address, ";");
	}
// ----------------------------------------------------------------------
// ---- USER FUNCTIONS AND DATAS ----------------------------------------
// ----------------------------------------------------------------------
// ===================================================================
// ==== user bit =====================================================
// ===================================================================
//
// ==== user code: C:\Tiny_2006\RqPreCompiler\Distribution_01_01_2007_HNY\GCC_Tny_Shell\GCC_Null.Cpp 
// ''RQEXPORT function AddInt (i1, i2)
int __stdcall AddInt ( int i1, int i2, int i3, int i4) {
      return (i1 + i2);
	}
//
// ==== end user code: C:\Tiny_2006\RqPreCompiler\Distribution_01_01_2007_HNY\GCC_Tny_Shell\GCC_Null.Cpp
// ===================================================================
// ==== end of user bit ==============================================
// ===================================================================
// ----------------------------------------------------------------------
// ---- RTL Table Builder -----------------------------------------------
// ----------------------------------------------------------------------
void Build_RTL () {
    char sInt2Str[16];
    strcat (Name__Address, ";");
    AddName__Address ("AddInt", (int)AddInt);
    // Set Environment Runtime Linkage Variables
    ltoa ((int)Name__Address, sInt2Str, 10);
    SetEnvironmentVariable ("ptrNameAddress", sInt2Str);
    ltoa (strlen(Name__Address), sInt2Str, 10);
    SetEnvironmentVariable ("lenNameAddress", sInt2Str);
}
// -------------------------------------------------------------------
// user configured variables  console/encrypt/dllname/msgDllError
// -------------------------
int flag__Encrypt = 0;
int flag__Console = 1;
char *sRQ32Dll = "RapidQ32.Dll";
// ------------------------------------------------------------------
// ------------------------------------------------------------------
// ------------------------------------------------------------------
LRESULT CALLBACK Main__Proc(HWND Dlg,UINT message,WPARAM wParam,LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{

     // RunTime Link Functions
     Build_RTL();

     // --------------------------------------
	WNDCLASSEX frmmain;
	frmmain.cbSize=sizeof(WNDCLASSEX);
	frmmain.style=CS_HREDRAW|CS_VREDRAW;
	frmmain.lpfnWndProc=Main__Proc;
	frmmain.cbClsExtra=0;
	frmmain.cbWndExtra=0;
	frmmain.hInstance=hInstance;
	frmmain.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	frmmain.hCursor=LoadCursor(NULL,IDC_ARROW);
	frmmain.hbrBackground=reinterpret_cast<HBRUSH>(COLOR_WINDOW+1);
	frmmain.lpszMenuName=NULL;
	frmmain.lpszClassName="GccTinyJp";
	frmmain.hIconSm=LoadIcon(NULL,IDI_APPLICATION);
/////////////////////////////////////////////////////////////////////  
//
// Create a Console or Not
// -----------------------
if (flag__Console==TRUE) AllocConsole();
//
// Command Line to Argc Argv  (api dont work in win98)
// multiple space as separator = end of cmd line
// tab is not separator
// -------------------------
     char *Argv[1024];
     char	*ptrCmd = GetCommandLine();     //lpCmdLine skips Arg [0]
     int Argc = 0, flagDQ = 0;
     char *ptrCL = ptrCmd;
     char *ptrWrite = ptrCmd;
     Argv[Argc] = ptrWrite;
//     
     while (*ptrCL != 0) {
          switch (*ptrCL) {
		     case 34:
                    if (flagDQ == 0) flagDQ = 1;
                    else	flagDQ = 0;
				break;
               case 32:
                   	if (flagDQ == 0) {
			          *ptrWrite=0;
     	               ptrWrite ++;
				     Argc ++;     
				    	Argv[Argc] = ptrWrite;
				     }
                    else {
	                    *ptrWrite = *ptrCL;
     	               ptrWrite ++;
                         }
				break;
               default:
                    *ptrWrite = *ptrCL;
                    ptrWrite ++;
                    break;
		}
          ptrCL ++;
	}
     *ptrWrite = 0;   
     Argc ++;          // 0 >> 1  ArgCount
//
// read the content of file passed as Argv[0] = sExe in *sExe
// ---------------------------------------------------------
    	char *sExeFileName = Argv[0];
    	char *sExe;
    	int iExeLen;
    	FILE *fExe = fopen(sExeFileName, "rb"); 
        	// get file size   (phew ...)
	   	fseek(fExe, 0, SEEK_END);
        	iExeLen = ftell(fExe);
        	rewind (fExe); 
        	// allocate memory to contain the whole file.
        	sExe = (char*) malloc (iExeLen);
        	if (sExe == NULL) exit (2);
        	fread (sExe, 1, iExeLen, fExe);
    	if (fclose(fExe)!=0) return(0);
//
// Get BC size in the last RQ exe 4 bytes
// --------------------------------------
     int iBCLen;
     iBCLen = *(int*) (sExe + iExeLen - 4);
     if(iBCLen==0|iBCLen==3686465) {
		MessageBoxA (0, "No Bytecode attached,  I QUIT", "ERROR GccTinyJP", 0);
		ExitProcess(333);
		}
//
// Run the BC code in memory
// -------------------------
	int iBCStart, ptrBC, iRet;
    	iBCStart = iExeLen - iBCLen - 4;
    	ptrBC = (int) sExe + iBCStart;

     if(flag__Encrypt == TRUE) iRet = Encrypt (ptrBC, iBCLen + 4, 0, 0);

     // Resolve Api RapidQ32.Dll/RQ_ExecuteMemory
     HINSTANCE hDll = LoadLibraryA (sRQ32Dll);
     RQ_EXECUTEMEMORY RQ_ExecuteMemory;
     RQ_ExecuteMemory = (RQ_EXECUTEMEMORY)GetProcAddress (hDll, "RQ_ExecuteMemory");

     if (RQ_ExecuteMemory(ptrBC, iBCLen + 4, (int)&Argv[1], Argc - 1) == -1) {
		MessageBoxA (0, "CANNOT EXECUTE BYTECODE.  I QUIT !", "ERROR GCC RQTINY", 0);
          }
//
	FreeConsole();
     free (sExe);
     FreeLibrary (hDll);
     ExitProcess (444);
/////////////////////////////////////////////////////////////////////
}

LRESULT CALLBACK Main__Proc(HWND hWnd, UINT mes, WPARAM wParam, LPARAM lParam)
{
	switch (mes)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hWnd, mes, wParam, lParam);
	}
}
// ------------------------------------------------------------------
