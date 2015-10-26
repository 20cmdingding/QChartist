'
' -------------------------------------------------------------------
' RQPC FB EXAMPLE: Minimum Code                   nov 2006   Jacques
' -------------------------------------------------------------------
'
$Include "MyRqTiny.Inc" ' added by RQPC (add only comments above me)
''pre cmd FBVERSION=017 FBLANG=deprecated console Tiny run nokill opt MyFB.Fbb nodone Kill nobk
Print Chr$(10);Chr$(10);Chr$(10);"FB AddInt (7 + 8) = ";AddInt (7, 8)
ShowMessage ("FINISHED")
