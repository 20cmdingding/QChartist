''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'>>> SOURCE LICENSE >>>
'This program is free software; you can redistribute it and/or modify
'it under the terms of the GNU General Public License as published by
'the Free Software Foundation (www.fsf.org); either version 2 of the
'License, or (at your option) any later version.
'
'This program is distributed in the hope that it will be useful,
'but WITHOUT ANY WARRANTY; without even the implied warranty of
'MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
'GNU General Public License for more details.
'
'A copy of the GNU General Public License is available at
'http://www.fsf.org/licensing/licenses
'
'>>> END OF LICENSE >>>
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'Routines
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'Calculation of the value of the Legendre polynomial Pn.
'
'Parameters:
'    n   -   degree, n>=0
'    x   -   argument
'
'Result:
'    the value of the Legendre polynomial Pn at x
'
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Public Function LegendreCalculate(ByRef n As Long, ByRef x As Double) As Double
    Dim Result As Double
    Dim a As Double
    Dim b As Double
    Dim i As Long

    Result = 1#
    a = 1#
    b = x
    If n=0# then
        Result = a
        LegendreCalculate = Result
        Exit Function
    End If
    If n=1# then
        Result = b
        LegendreCalculate = Result
        Exit Function
    End If
    For i=2# To n Step 1
        Result = ((2#*i-1#)*x*b-(i-1#)*a)/i
        a = b
        b = Result
    Next i

    LegendreCalculate = Result
End Function


''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'Summation of Legendre polynomials using Clenshaw’s recurrence formula.
'
'This routine calculates
'    c[0]*P0(x) + c[1]*P1(x) + ... + c[N]*PN(x)
'
'Parameters:
'    n   -   degree, n>=0
'    x   -   argument
'
'Result:
'    the value of the Legendre polynomial at x
'
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Public Function LegendreSum(ByRef C() As Double, _
         ByRef n As Long, _
         ByRef x As Double) As Double
    Dim Result As Double
    Dim b1 As Double
    Dim b2 As Double
    Dim i As Long

    b1 = 0#
    b2 = 0#
    For i=n To 0# Step -1
        Result = (2#*i+1#)*x*b1/(i+1#)-(i+1#)*b2/(i+2#)+C(i)
        b2 = b1
        b1 = Result
    Next i

    LegendreSum = Result
End Function


''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'Representation of Pn as C[0] + C[1]*X + ... + C[N]*X^N
'
'Input parameters:
'    N   -   polynomial degree, n>=0
'
'Output parameters:
'    C   -   coefficients
'
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Public Sub LegendreCoefficients(ByRef N As Long, ByRef C() As Double)
    Dim I As Long

    ReDim C(0# To N)
    For I=0# To N Step 1
        C(I) = 0#
    Next I
    C(N) = 1#
    For i=1# To N Step 1
        C(N) = C(N)*(n+i)/2#/i
    Next i
    For i=0# To n\2#-1# Step 1
        C(N-2#*(i+1#)) = -(C(N-2#*i)*(n-2#*i)*(n-2#*i-1#)/2#/(i+1#)/(2#*(n-i)-1#))
    Next i
End Sub


