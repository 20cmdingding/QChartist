
// ------------------------------------------------------------------
// RQPC GCC example:  RapidQ External CallBack      Jan 2007, Jacques
// ------------------------------------------------------------------

WNDPROC ptrOldRchWndProcTop, ptrOldRchWndProcBottom;

// ''RQEXPORT function CB_RichEdit_Top ()
LRESULT CB_RichEdit_Top(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)  {
    if (uMsg < 0x200||uMsg > 0x20A)
         return CallWindowProc(ptrOldRchWndProcTop, hwnd, uMsg, wParam, lParam);
    printf("\nin callback TOP");
    }

// ''RQEXPORT function CB_RichEdit_Bottom ()
LRESULT CB_RichEdit_Bottom(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)  {
    if (uMsg < 0x200||uMsg > 0x20A)
         return CallWindowProc(ptrOldRchWndProcBottom, hwnd, uMsg, wParam, lParam);
    printf("\nin callback BOTTOM");
    }

// ''RQEXPORT function SubClassTop (hRichEditTop)
void __stdcall SubClassTop (HWND RichEditTop, int a2, int a3, int a4) {
     ptrOldRchWndProcTop = (WNDPROC) SetWindowLong (RichEditTop, (-4), (int)ptrOldRchWndProcTop);
    printf("\nSub Class Top");
    }

// ''RQEXPORT function SubClassBottom (hRichEditBottom)
void __stdcall SubClassBottom (HWND RichEditBottom, int a2, int a3, int a4) {
     ptrOldRchWndProcBottom = (WNDPROC) SetWindowLong (RichEditBottom, (-4), (int)ptrOldRchWndProcBottom);
    printf("\nSub Class Bottom");
    }

// ''RQEXPORT function InitSubClass ()
void  __stdcall InitSubClass (int a1, int a2, int a3, int a4) {
    ptrOldRchWndProcTop    = (WNDPROC)CB_RichEdit_Top;
    ptrOldRchWndProcBottom = (WNDPROC)CB_RichEdit_Bottom;
    printf("\nin InitSubClass");    
	}
