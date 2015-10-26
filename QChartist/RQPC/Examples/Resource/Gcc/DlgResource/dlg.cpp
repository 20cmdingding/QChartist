// modified gcc example
#include <windows.h>
#include "resource.h"

LRESULT CALLBACK dlgProc(HWND Dlg,UINT message,WPARAM wParam,LPARAM lParam);

// ''RQEXPORT function ShowDialog ()
int __stdcall ShowDialog (int i1, int i2, int i3, int i4) {
	HINSTANCE hInstance = GetModuleHandle (0);
	DialogBox(hInstance,(LPCTSTR)IDD_MAIN,NULL,(DLGPROC)dlgProc);
	return 0;
}

LRESULT CALLBACK dlgProc(HWND Dlg,UINT message,WPARAM wParam,LPARAM lParam)
{
	int Select;
	char buf[501];
	HANDLE hFile;
	DWORD Read;
	switch(message)
	{
	case WM_COMMAND:
		Select=LOWORD(wParam);
		switch(Select)
		{
		case IDC_LIRE:
			GetDlgItemText(Dlg,IDC_FILENAME,buf,256);
			hFile=CreateFile(buf,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
			if(hFile==INVALID_HANDLE_VALUE)
			{
				MessageBox(Dlg,"Error, cannot open file.","Error",MB_OK);
				return 0;
			}
			ReadFile(hFile,buf,500,&Read,NULL);
			CloseHandle(hFile);
			buf[Read]='\0';
			SetDlgItemText(Dlg,IDC_TEXT,buf);
			return 0;
		case IDOK:
			EndDialog(Dlg,0);
			return TRUE;
		case IDCANCEL:
			EndDialog(Dlg,0);
			return TRUE;
		}
	default:
		return FALSE;
	}
}