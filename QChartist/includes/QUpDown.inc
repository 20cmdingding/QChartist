' UpDown Component fo Rapidq
' Version 1.1 (stable)
' Coded by Nastase Eodor
' http://rqwork.evonet.ro
' mailTo: rqwork@evonet.ro

$DEFINE udsHorizontal UDS_HORZ
$DEFINE udsVertical   0
$DEFINE udaLeft       UDS_ALIGNLEFT
$DEFINE udaRight      UDS_ALIGNRIGHT

Type QUpDown Extends QObject
     Private:
     NewProc        As Integer
     ClassProc      As Integer
     ParentProc     As Integer
     LastParentProc As Integer
     ParentWnd      As Integer
     Public:
     Handle         As Integer
     Associate      As QEdit   Property Set SetAssociate
     Associate2     As Integer Property Set SetAssociate2
     Parent         As QForm   Property Set SetParent
     Parent2        As QPanel  Property Set SetParent2
     ParetWindow    As Integer Property Set SetParentWindow
     Left           As Integer Property Set SetLeft
     Top            As Integer Property Set SetTop
     Width          As Integer Property Set SetWidth
     Height         As Integer Property Set SetHeight
     Enabled        As Integer Property Set SetEnabled
     Visible        As Integer Property Set SetVisible
     Min            As Short   Property Set SetMin
     Max            As Short   Property Set SetMax
     Position       As Short   Property Set SetPosition
     Arrowkeys      As Integer Property Set SetArrowkeys
     WrapOpposite   As Integer Property Set SetWrapOpposite
     AlignTo        As Integer Property Set SetAlignTo
     Style          As Integer Property Set SetStyle
     Base           As Integer Property Set SetBase
     
     With This
     
     Sub CreateWnd
         If .Handle Then Exit Sub
         DefInt Style = ws_child
         Style = Style Or .Style
         Style = Style Or .AlignTo
         Style = Style Or IIf(.ArrowKeys,UDS_ARROWKEYS,0)
         .Handle = CreateWindowEx(0,"QUpDown","",Style,.Left,.Top,.Width,.Height,.ParentWnd,0,GetModuleHandle(0),0)
         If .Handle Then
            SendMessage(.Handle,UDM_SETRANGE,0,MakeLong(.Min,.Max))
            SendMessage(.Handle,UDM_SETPOS,0,MakeLong(.Position,0))
            SetWindowText(.Associate2,Str$(.Position))
            ShowWindow(.Handle,IIf(.Visible,SW_SHOW,SW_HIDE))
         End If
     End Sub
     
     Sub ReCreateWnd
         DefInt i
         If .Handle Then
            DestroyWindow(.Handle)
            .Handle = 0
         End If
         .CreateWnd
         If .Handle Then
            SendMessage(.Handle,UDM_SETBUDDY,.Associate2,0)
         End If
     End Sub
     
     Sub Invalidate
         If .Handle Then InvalidateRect(.Handle,0,0)
     End Sub

     Sub Update
         If .Handle Then UpdateWindow(.Handle)
     End Sub

     Sub Repaint
         If .Handle Then
            RedrawWindow(.Handle,0,0,RDW_ERASE Or RDW_INVALIDATE)
            .Update
         End If
     End Sub
     
     Property Set SetParent(Value As QForm)
         .ParentWnd = Value.Handle
         If .Handle Then
            SetParent(.Handle,Value.Handle)
            If GetWindowLong(.ParentWnd,GWL_WNDPROC) <> .ParentProc Then
               .LastParentProc = SetWindowLong(.ParentWnd,GWL_WNDPROC,.ParentProc)
            End If
         Else
            .CreateWnd
            If GetWindowLong(.ParentWnd,GWL_WNDPROC) <> .ParentProc Then
               .LastParentProc = SetWindowLong(.ParentWnd,GWL_WNDPROC,.ParentProc)
            End If
         End If
     End Property

     Property Set SetParent2(Value As QPanel)
         .ParentWnd = Value.Handle
         If .Handle Then
            SetParent(.Handle,Value.Handle)
            If GetWindowLong(.ParentWnd,GWL_WNDPROC) <> .ParentProc Then
               .LastParentProc = SetWindowLong(.ParentWnd,GWL_WNDPROC,.ParentProc)
            End If
         Else
            .CreateWnd
            If GetWindowLong(.ParentWnd,GWL_WNDPROC) <> .ParentProc Then
               .LastParentProc = SetWindowLong(.ParentWnd,GWL_WNDPROC,.ParentProc)
            End If
         End If
     End Property

     Property Set SetParentWindow(Value As Integer)
         .ParentWnd = Value
         If .Handle Then
            SetParent(.Handle,Value)
            If GetWindowLong(.ParentWnd,GWL_WNDPROC) <> .ParentProc Then
               .LastParentProc = SetWindowLong(.ParentWnd,GWL_WNDPROC,.ParentProc)
            End If
         Else
            .CreateWnd
            If GetWindowLong(.ParentWnd,GWL_WNDPROC) <> .ParentProc Then
               .LastParentProc = SetWindowLong(.ParentWnd,GWL_WNDPROC,.ParentProc)
            End If
         End If
     End Property

     Property Set SetLeft(Value As Integer)
         .Left = Value
         If .Handle Then MoveWindow(.Handle,.Left,.Top,.Width,.Height,1)
     End Property

     Property Set SetTop(Value As Integer)
         .Top = Value
         If .Handle Then MoveWindow(.Handle,.Left,.Top,.Width,.Height,1)
     End Property

     Property Set SetWidth(Value As Integer)
         .Width = value
         If .Handle Then MoveWindow(.Handle,.Left,.Top,.Width,.Height,1)
     End Property

     Property Set SetHeight(Value As Integer)
         .Height = value
         If .Handle Then MoveWindow(.Handle,.Left,.Top,.Width,.Height,1)
     End Property
     
     Property Set SetEnabled(Value As Integer)
         .Enabled = Value
         If .Handle Then EnableWindow(.Handle,.Enabled)
     End Property

     Property Set SetVisible(Value As Integer)
         .Visible = value
         If .Handle Then ShowWindow(.Handle,IIf(.Visible,SW_SHOW,SW_HIDE))
     End Property
     
     Property Set SetAssociate(Value As QEdit)
         .Associate2 = Value.Handle
         If .Handle Then
            SendMessage(.Handle,UDM_SETBUDDY,.Associate2,0)
            SetWindowText(.Associate2,Str$(.Position))
         End If
     End Property
     
     Property Set SetAssociate2(Value As Integer)
         .Associate2 = Value
         If .Handle Then
            SendMessage(.Handle,UDM_SETBUDDY,.Associate2,0)
            SetWindowText(.Associate2,Str$(.Position))
         End If
     End Property
     
     Property Set SetArrowKeys(Value As Integer)
         .ArrowKeys = value
         .RecreateWnd
     End Property
     
     Property Set SetWrapOpposite(Value As Integer)
         .WrapOpposite = value
         .RecreateWnd
     End Property
     
     Property Set SetBase(Value As Integer)
         .Base = value
         If .Handle Then SendMessage(.Handle,UDM_SETBASE,.Base,0)
     End Property
     
     Property Set SetMin(Value As Short)
         .Min = value
         If .Handle Then SendMessage(.Handle,UDM_SETRANGE,0,MakeLong(.Min,.Max))
     End Property
     
     Property Set SetMax(Value As Short)
         .Max = value
         If .Handle Then SendMessage(.Handle,UDM_SETRANGE,0,MakeLong(.Min,.Max))
     End Property
     
     Property Set SetPosition(Value As Short)
         .Position = value
         If .Handle Then SendMessage(.Handle,UDM_SETPOS,0,MakeLong(.Position,0))
     End Property
     
     Property Set SetStyle(Value As Integer)
         .Style = value
         .RecreateWnd
     End Property
     
     Property Set SetAlignTo(Value As Integer)
         .AlignTo = value
         .RecreateWnd
     End Property
     
     Function ParentWndProc(hWnd&,Msg&,wParam&,lParam&) As Integer
         Result = CallWindowProc(.LastParentProc,hWnd&,Msg&,wParam&,lParam&)
         Select Case Msg&
         Case WM_NOTIFY
              Dim NM As NMHDR
              MemCpy NM,LParam&,SizeOf(NM)
              If NM.code = UDN_DELTAPOS Then
                 Dim NMU As NM_UPDOWNW
                 MemCpy NMU,LParam&,SizeOf(NMU)
                 .Position = NMU.iPos
                 If .Associate2 Then
                    SetWindowText(.Associate2,Str$(.Position))
                 End If
              End If
         End Select
     End Function
     
     Function WndProc(hWnd&,Msg&,wParam&,lParam&) As Integer
         Result = CallWindowProc(.ClassProc,hWnd&,Msg&,wParam&,lParam&)
     End Function
     
     Sub Register
         DefInt F4,ClassProc
         Dim Wc As WNDCLASS
         Bind F4 To This.WndProc
         .NewProc = SetNewCallBack_4(F4)
         Bind F4 To This.ParentWndProc
         .ParentProc = SetNewCallBack_4(F4)
         InitCommonControls
         If GetClassInfo(0,"msctls_updown32",Wc) Then
            .ClassProc = Wc.lpfnWndProc
            If GetClassInfo(GetModuleHandle(0),"QUpDown",Wc) = 0 Then
               Wc.lpfnWndProc   = .NewProc
               Wc.lpszClassName = NewZStr("QUpDown")
               Wc.hInstance     = GetModuleHandle(0)
               RegisterClass(Wc)
            End If
         End If
     End Sub
     
     End With
     
     Constructor
     Register
     Base       = 10
     Style      = udsVertical
     ArrowKeys  = 1
     AlignTo    = udaRight
     Width      = 19
     Height     = 38
     Visible    = 1
     Max        = 100
     Position   = 0
     End Constructor
End Type
