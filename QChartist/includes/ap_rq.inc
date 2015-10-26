$TYPECHECK off

public Type Complex
    X As Double
    Y As Double
End Type

Public Type RCommState
    Stage As Long
    BA() As Boolean
    IA() As Long
    RA() As Double
    CA() As Complex
End Type

Public Type ALGLIBDataset
    NIn As Long
    NOut As Long
    NClasses As Long
    
    Trn() As Double
    Tst() As Double
    Val() As Double
    AllDataset() As Double
    
    TrnSize As Long
    TstSize As Long
    ValSize As Long
    TotalSize As Long
End Type

Public Const MachineEpsilon = 5E-16
Public Const MaxRealNumber = 1E+300
Public Const MinRealNumber = 1E-300

Private Const BigNumber As Double = 1E+70
Private Const SmallNumber As Double = 1E-70
Private Const PiNumber As Double = 3.14159265358979

Public Function FormatInteger(I As Long, W As Long) As String
    If W <= 1 Then
        FormatInteger = Format$(I, "0")
    Else
        Tmp = Format$(I, String$(W - 1, "#") & "0")
        While Len(Tmp) < W
            Tmp = " " & Tmp
        wend
        FormatInteger = Tmp
    End If
End Function

Public Function FormatFReal(R As Double, W As Long, P As Long) As String
    Tmp = Format$(R, "0." & String$(P, "0"))
    While Len(Tmp) < W
        Tmp = " " & Tmp
    wend
    FormatFReal = Tmp
End Function

Public Function FormatEReal(R As Double, W As Long, P As Long) As String
    Tmp = Format$(R, "0." & String$(P, "0") & "E+0")
    While Len(Tmp) < W
        Tmp = " " & Tmp
    wend
    FormatEReal = Tmp
End Function

Public Sub ConsoleOutputString(S As String)
End Sub

Public Function MaxReal(ByVal M1 As Double, ByVal M2 As Double) As Double
    If M1 > M2 Then
        MaxReal = M1
    Else
        MaxReal = M2
    End If
End Function

Public Function MinReal(ByVal M1 As Double, ByVal M2 As Double) As Double
    If M1 < M2 Then
        MinReal = M1
    Else
        MinReal = M2
    End If
End Function

Public Function MaxInt(ByVal M1 As Long, ByVal M2 As Long) As Long
    If M1 > M2 Then
        MaxInt = M1
    Else
        MaxInt = M2
    End If
End Function

Public Function MinInt(ByVal M1 As Long, ByVal M2 As Long) As Long
    If M1 < M2 Then
        MinInt = M1
    Else
        MinInt = M2
    End If
End Function

Public Function ArcSin(ByVal X As Double) As Double
    Dim T As Double
    T = Sqr(1 - X * X)
    If T < SmallNumber Then
        ArcSin = Atn(BigNumber * Sgn(X))
    Else
        ArcSin = Atn(X / T)
    End If
End Function

Public Function ArcCos(ByVal X As Double) As Double
    Dim T As Double
    T = Sqr(1 - X * X)
    If T < SmallNumber Then
        ArcCos = Atn(BigNumber * Sgn(-X)) + 2 * Atn(1)
    Else
        ArcCos = Atn(-X / T) + 2 * Atn(1)
    End If
End Function

'Public Function SinH(ByVal X As Double) As Double ' already available in rq-math
'    SinH = (Exp(X) - Exp(-X)) / 2
'End Function

'Public Function CosH(ByVal X As Double) As Double ' already available in rq-math
'    CosH = (Exp(X) + Exp(-X)) / 2
'End Function

'Public Function TanH(ByVal X As Double) As Double ' already available in rq-math
'    Dim T As Double
'    If X > 0 Then
'        T = Exp(-X)
'        T = T * T
'        TanH = (1 - T) / (1 + T)
'    Else
'        T = Exp(X)
'        T = T * T
'        TanH = (T - 1) / (T + 1)
'    End If
'End Function

Public Function Pi() As Double
    'Pi = PiNumber
    Pi = ArcCos(-1)
End Function

Public Function Power(ByVal Base As Double, ByVal Exponent As Double) As Double
    Power = Base ^ Exponent
End Function

Public Function Square(ByVal X As Double) As Double
    Square = X * X
End Function

'Public Function Log10(ByVal X As Double) As Double ' already available in rq-math
'    Log10 = Log(X) / Log(10)
'End Function

'Public Function Ceil(ByVal X As Double) As Double
'    Ceil = -Int(-X)
'End Function

Public Function RandomInteger(ByVal X As Long) As Long
    RandomInteger = Int(Rnd() * X)
End Function

Public Function Atn2(ByVal Y As Double, ByVal X As Double) As Double
    If SmallNumber * Abs(Y) < Abs(X) Then
        If X < 0 Then
            If Y = 0 Then
                Atn2 = Pi()
            Else
                Atn2 = Atn(Y / X) + Pi() * Sgn(Y)
            End If
        Else
            Atn2 = Atn(Y / X)
        End If
    Else
        Atn2 = Sgn(Y) * Pi() / 2
    End If
End Function

Public Function C_Complex(ByVal X As Double) As long 'Complex
    Dim Result As Complex

    Result.X = X
    Result.Y = 0

    C_Complex = Result
End Function


Public Function AbsComplex(ByRef Z As Complex) As Double
    Dim Result As Double
    Dim W As Double
    Dim XABS As Double
    Dim YABS As Double
    Dim V As Double

    XABS = Abs(Z.X)
    YABS = Abs(Z.Y)
    W = MaxReal(XABS, YABS)
    V = MinReal(XABS, YABS)
    If V = 0 Then
        Result = W
    Else
        Result = W * Sqr(1 + Square(V / W))
    End If

    AbsComplex = Result
End Function


Public Function C_Opposite(ByRef Z As Complex) As long 'Complex
    Dim Result As Complex

    Result.X = -Z.X
    Result.Y = -Z.Y

    C_Opposite = Result
End Function


Public Function Conj(ByRef Z As Complex) As long 'Complex
    Dim Result As Complex

    Result.X = Z.X
    Result.Y = -Z.Y

    Conj = Result
End Function


Public Function CSqr(ByRef Z As Complex) As long 'Complex
    Dim Result As Complex

    Result.X = Square(Z.X) - Square(Z.Y)
    Result.Y = 2 * Z.X * Z.Y

    CSqr = Result
End Function


Public Function C_Add(ByRef Z1 As Complex, ByRef Z2 As Complex) As long 'Complex
    Dim Result As Complex

    Result.X = Z1.X + Z2.X
    Result.Y = Z1.Y + Z2.Y

    C_Add = Result
End Function


Public Function C_Mul(ByRef Z1 As Complex, ByRef Z2 As Complex) As long 'Complex
    Dim Result As Complex

    Result.X = Z1.X * Z2.X - Z1.Y * Z2.Y
    Result.Y = Z1.X * Z2.Y + Z1.Y * Z2.X

    C_Mul = Result
End Function


Public Function C_AddR(ByRef Z1 As Complex, ByVal R As Double) As long 'Complex
    Dim Result As Complex

    Result.X = Z1.X + R
    Result.Y = Z1.Y

    C_AddR = Result
End Function


Public Function C_MulR(ByRef Z1 As Complex, ByVal R As Double) As long 'Complex
    Dim Result As Complex

    Result.X = Z1.X * R
    Result.Y = Z1.Y * R

    C_MulR = Result
End Function


Public Function C_Sub(ByRef Z1 As Complex, ByRef Z2 As Complex) As long 'Complex
    Dim Result As Complex

    Result.X = Z1.X - Z2.X
    Result.Y = Z1.Y - Z2.Y

    C_Sub = Result
End Function


Public Function C_SubR(ByRef Z1 As Complex, ByVal R As Double) As long 'Complex
    Dim Result As Complex

    Result.X = Z1.X - R
    Result.Y = Z1.Y

    C_SubR = Result
End Function


Public Function C_RSub(ByVal R As Double, ByRef Z1 As Complex) As long 'Complex
    Dim Result As Complex

    Result.X = R - Z1.X
    Result.Y = -Z1.Y

    C_RSub = Result
End Function


Public Function C_Div(ByRef Z1 As Complex, ByRef Z2 As Complex) As long 'Complex
    Dim Result As Complex
    Dim A As Double
    Dim B As Double
    Dim C As Double
    Dim D As Double
    Dim E As Double
    Dim F As Double

    A = Z1.X
    B = Z1.Y
    C = Z2.X
    D = Z2.Y
    If Abs(D) < Abs(C) Then
        E = D / C
        F = C + D * E
        Result.X = (A + B * E) / F
        Result.Y = (B - A * E) / F
    Else
        E = C / D
        F = D + C * E
        Result.X = (B + A * E) / F
        Result.Y = (-A + B * E) / F
    End If

    C_Div = Result
End Function


Public Function C_DivR(ByRef Z1 As Complex, ByVal R As Double) As long 'Complex
    Dim Result As Complex

    Result.X = Z1.X / R
    Result.Y = Z1.Y / R

    C_DivR = Result
End Function


Public Function C_RDiv(ByVal R As Double, ByRef Z2 As Complex) As long 'Complex
    Dim Result As Complex
    Dim A As Double
    Dim C As Double
    Dim D As Double
    Dim E As Double
    Dim F As Double

    A = R
    C = Z2.X
    D = Z2.Y
    If Abs(D) < Abs(C) Then
        E = D / C
        F = C + D * E
        Result.X = A / F
        Result.Y = -(A * E / F)
    Else
        E = C / D
        F = D + C * E
        Result.X = A * E / F
        Result.Y = -(A / F)
    End If

    C_RDiv = Result
End Function


Public Function C_Equal(ByRef Z1 As Complex, ByRef Z2 As Complex) As integer 'Boolean
    Dim Result As integer 'Boolean

    Result = Z1.X = Z2.X And Z1.Y = Z2.Y

    C_Equal = Result
End Function


Public Function C_NotEqual(ByRef Z1 As Complex, _
         ByRef Z2 As Complex) As integer 'Boolean
    Dim Result As integer 'Boolean

    Result = Z1.X <> Z2.X Or Z1.Y <> Z2.Y

    C_NotEqual = Result
End Function

Public Function C_EqualR(ByRef Z1 As Complex, ByVal R As Double) As integer 'Boolean
    Dim Result As integer 'Boolean

    Result = Z1.X = R And Z1.Y = 0

    C_EqualR = Result
End Function


Public Function C_NotEqualR(ByRef Z1 As Complex, _
         ByVal R As Double) As integer 'Boolean
    Dim Result As integer 'Boolean

    Result = Z1.X <> R Or Z1.Y <> 0

    C_NotEqualR = Result
End Function


Public Function SplitTrim(ByVal S As String, ByVal Sep As String) As String '()
    Dim SPrev As String
    S = Trim(S)
    Do
        SPrev = S
        S = Replacesubstr$(S, "  ", " ")
    Loop Until S = SPrev
    ' SplitTrim = Split(S, Sep) ' Need split equivalent for RQ
End Function


$TYPECHECK on
