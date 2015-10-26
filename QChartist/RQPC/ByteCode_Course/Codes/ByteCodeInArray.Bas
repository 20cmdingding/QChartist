'
' -------------------------------------------------------------------
'  ByteCode in an Array                         Nov 2006,     Jacques
' -------------------------------------------------------------------
' bBytecode is the array build with the bytecode of the following
' RapidQ Code:
'
'Create myForm as QForm
'    Width = 400
'    Caption = "Test RQ_ExecuteMemory ByteCode"
'End Create
'myForm.ShowModal
' ----------
''pre cmd Tiny opt nokill
'
DECLARE FUNCTION RQ_ExecuteMemory LIB "RAPIDQ32.DLL" ALIAS "RQ_ExecuteMemory" _
           (Memory AS LONG, MemorySize AS LONG, Commands AS LONG, Count AS LONG) AS LONG
'
DefByte bByteCode(0 To 77) = _
       {&H1E, &H04, &H00, &H00, &H00, &H00, &H00, &H00, _
        &H01, &H1E, &H00, &H00, &H08, &H1E, &H00, &H00, _
        &H06, &H02, &H07, &H00, &H00, &H00, &H00, &H00, _
        &H00, &H79, &H40, &H0B, &H08, &H1E, &H00, &H00, _
        &H00, &H02, &H00, &H1E, &H00, &H54, &H65, &H73, _
        &H74, &H20, &H52, &H51, &H5F, &H45, &H78, &H65, _
        &H63, &H75, &H74, &H65, &H4D, &H65, &H6D, &H6F, _
        &H72, &H79, &H20, &H42, &H79, &H74, &H65, &H43, _
        &H6F, &H64, &H65, &H0B, &H08, &H1E, &H00, &H00, _
        &H04, &H0B, &H4A, &H00, &H00, &H00}
'
RQ_ExecuteMemory (VarPtr(bByteCode(0)), 78, 0, 0)
' -------------------------------------------------------------------


