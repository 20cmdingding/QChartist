// ------------------------------------
// ''RQEXPORT function CWP_Test ()
int __stdcall CWP_Test (int i1, int i2, int i3, int i4){
    // do nothing
	return (0);
    }
// ------------------------------------
// ''RQEXPORT function LoopGTC (LoopCount)
int __stdcall LoopGTC (int LoopCount, int i2, int i3, int i4){
    int i1;
    while (LoopCount > 0) {
        i1 = GetTickCount ();
        LoopCount --;
        }
    }
// ------------------------------------
// ''RQEXPORT function LoopNull (LoopCount)
int __stdcall LoopNull (int LoopCount, int i2, int i3, int i4){
    while (LoopCount > 0) {
        LoopCount --;
        }
    }
// ------------------------------------
// ''RQEXPORT function LoopCWP (LoopCount)
int __stdcall LoopCWP (int LoopCount, int i2, int i3, int i4){
    while (LoopCount > 0) {
        CallWindowProc ((WNDPROC)CWP_Test, 0, 0, 0, 0);
        LoopCount --;
        }
    }
// ------------------------------------
