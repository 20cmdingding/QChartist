Type TINFO
     dwInfoSize            As Long
     dwMajorPlatform      As Long
     dwMinorPlatform      As Long
     dwBuildNumber         As Long
     dwPlatformId          As Long
     szCSDPlatform        As String * 128
End Type

Const PLATFORM_WIN32 = 0
Const PLATFORM_WIN32_WINDOWS = 1
Const PLATFORM_WIN32_NT = 2
Const PLATFORM_WIN32_CE = 3

' -= Or maybe the user is running Wine? Section added by Julien Moog - julien.moog@laposte.net on 2014-07-17 =-

DECLARE FUNCTION GetWindowsDirectory LIB "kernel32" ALIAS "GetWindowsDirectoryA" _
      (lpBuffer AS STRING, nSize AS LONG) AS LONG

' -=================================================================-

'Declare Function GetLastError Lib "kernel32.dll" AliAs "GetLastError" () As Long
Declare Function GetPlatformEx Lib "kernel32.dll" AliAs "GetVersionExA" (ByVal lpPlatformInformation As Long) As Long

Dim rtn As Long, FDouble As Double, mmbp As Byte
Dim OSV As TINFO, Mem As QMemoryStream
Dim Platform As String,Build As String

Sub Get_Version
OSV.dwInfoSize = SIZEOF(OSV)
Mem.WriteUDT(OSV)
rtn = GetPlatformEx(Mem.Pointer)
If rtn <> 0 then
   Mem.Position = 0
   Mem.ReadUDT(OSV)
   OSV.dwBuildNumber = (OSV.dwBuildNumber And &H0000FFFF)
      If OSV.dwPlatformId = PLATFORM_WIN32_WINDOWS then
     ' Windows 95, 98 And ME.
      If OSV.dwMajorPlatform = 4 then
      If OSV.dwMinorPlatform = 10 then
      ' Windows 98
      If OSV.dwBuildNumber = 1998 then
         mmbp = 11
      ElseIf ((OSV.dwBuildNumber > 1998) And (OSV.dwBuildNumber < 2183)) then
         mmbp = 12
      ElseIf OSV.dwBuildNumber > 2182 then
         mmbp = 13
      Else
      mmbp = 200
      End If
      ElseIf OSV.dwMinorPlatform < 10 then
      ' Windows 95
      If OSV.dwBuildNumber = 950 then
         mmbp = 1
      ElseIf ((OSV.dwBuildNumber>950) And (OSV.dwBuildNumber < 1081)) then
         mmbp = 2
      ElseIf OSV.dwBuildNumber > 1080 then
         mmbp = 3
      Else
         mmbp = 200
      End If
      ElseIf OSV.dwMinorPlatform=90 then
      ' Windows ME
      If OSV.dwBuildNumber=3000 then
         mmbp = 21
      Else
         mmbp = 200
      End If
      Else
         mmbp = 201
      End If
      Else
         mmbp = 202
      End If
      ElseIf OSV.dwPlatformId = PLATFORM_WIN32_NT then
      ' Windows NT, XP And 2000
        If OSV.dwMajorPlatform = 3 then
      ' Windows NT 3.51
        If OSV.dwMinorPlatform = 51 then
          If OSV.dwBuildNumber = 1057 then
             mmbp = 31
          Else
             mmbp = 200
          End If
        Else
          mmbp = 201
        End If
        ElseIf OSV.dwMajorPlatform = 4 then
       ' Windows NT 4
        If OSV.dwMinorPlatform = 0 then
          If OSV.dwBuildNumber = 1381 then
             mmbp = 41
          Else
             mmbp = 200
          End If
        Else
            mmbp = 201
        End If
        ElseIf OSV.dwMajorPlatform = 5 then
       ' Windows XP And 2000
        If OSV.dwMinorPlatform = 0 then
           If OSV.dwBuildNumber = 2195 then
              mmbp = 51
           Else
              mmbp = 200
           End If
        ElseIf OSV.dwMinorPlatform = 1 then
           mmbp = 61
        Else
           mmbp = 201
        End If
	ElseIf OSV.dwMajorPlatform = 6 then
       ' Windows 7
	If OSV.dwMinorPlatform = 1 then
           If OSV.dwBuildNumber = 7601 then
              mmbp = 71
	   end if
	end if
        Else
           mmbp = 202
        End If
     ElseIf OSV.dwPlatformId = PLATFORM_WIN32_CE then
    ' Pocket Phone, Small Devices, etc.
       Else
        mmbp = 203
       End If
       Else
       mmbp = 204
      End If

      If mmbp = 1 then
       Platform = ("Windows 95")
      ElseIf mmbp = 2 then
       Platform = ("Windows 95 SP1")
      ElseIf mmbp = 3 then
       Platform = ("Windows 95 OSR2")
      ElseIf mmbp = 11 then
       Platform = ("Windows 98")
      ElseIf mmbp = 12 then
       Platform = ("Windows 98 SP1")
      ElseIf mmbp = 13 then
       Platform = ("Windows 98 SE")
      ElseIf mmbp = 21 then
       Platform = ("Windows ME")
      ElseIf mmbp = 31 then
       Platform = ("Windows NT 3.51")
      ElseIf mmbp = 41 then
       Platform = ("Windows NT 4")
      ElseIf mmbp = 51 then
       Platform = ("Windows 2000 / Windows 2000 Pro")
      ElseIf mmbp = 61 then
       Platform = ("Windows XP")
      ElseIf mmbp = 71 then
       Platform = ("Windows 7")
      ElseIf mmbp = 200 then
       Platform = ("Unknown Build Number")
      ElseIf mmbp = 201 then
       Platform = ("Unknown Minor Platform")
      ElseIf mmbp=202 then
       Platform = ("Unknown Major Platform")
      ElseIf mmbp = 203 then
       Platform = ("Unknown Windows Platform")
      ElseIf mmbp = 204 then
       Platform = (STR$(GetLastError())+" "+str$(rtn))
      Else
       Platform = ("Can't get OS Version for your Machine.")
      End If
' -= Or maybe the user is running Wine? Section added by Julien Moog - julien.moog@laposte.net on 2014-07-17 =-

' Inspired From: Lance(8/10/02 7:24:24 pm)

     DIM WinDir AS STRING*256
     GetWindowsDirectory(WinDir, 256)

if fileexists(replacesubstr$(RTRIM$(WinDir),chr$(0),"")+"\system32\winebrowser.exe") then Platform = "Wine"
if fileexists(replacesubstr$(RTRIM$(WinDir),chr$(0),"")+"\winebrowser.exe") then Platform = "Wine"    

' -=================================================================-
Build = str$(OSV.dwBuildNumber)
End Sub

