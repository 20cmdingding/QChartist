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
'Calculation of the value of the Hermite polynomial.
'
'Parameters:
'    n   -   degree, n>=0
'    x   -   argument
'
'Result:
'    the value of the Hermite polynomial Hn at x
'
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Public Function HermiteCalculate(ByRef N As Long, ByRef X As Double) As Double
    Dim Result As Double
    Dim I As Long
    Dim a As Double
    Dim b As Double

    
    '
    ' Prepare A and B
    '
    a = 1#
    b = 2#*x
    
    '
    ' Special cases: N=0 or N=1
    '
    If n=0# then
        Result = a
        HermiteCalculate = Result
        Exit Function
    End If
    If n=1# then
        Result = b
        HermiteCalculate = Result
        Exit Function
    End If
    
    '
    ' General case: N>=2
    '
    For I=2# To N Step 1
        Result = 2#*x*b-2#*(I-1#)*a
        a = b
        b = Result
    Next I

    HermiteCalculate = Result
End Function


''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'Summation of Hermite polynomials using Clenshaw’s recurrence formula.
'
'This routine calculates
'    c[0]*H0(x) + c[1]*H1(x) + ... + c[N]*HN(x)
'
'Parameters:
'    n   -   degree, n>=0
'    x   -   argument
'
'Result:
'    the value of the Hermite polynomial at x
'
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Public Function HermiteSum(ByRef C() As Double, _
         ByRef n As Long, _
         ByRef x As Double) As Double
    Dim Result As Double
    Dim b1 As Double
    Dim b2 As Double
    Dim i As Long

    b1 = 0#
    b2 = 0#
    For i=n To 0# Step -1
        Result = 2#*(x*b1-(i+1#)*b2)+C(i)
        b2 = b1
        b1 = Result
    Next i

    HermiteSum = Result
End Function


''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'Representation of Hn as C[0] + C[1]*X + ... + C[N]*X^N
'
'Input parameters:
'    N   -   polynomial degree, n>=0
'
'Output parameters:
'    C   -   coefficients
'
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Public Sub HermiteCoefficients(ByRef N As Long, ByRef C() As Double)
    Dim I As Long

    ReDim C(0# To N)
    For I=0# To N Step 1
        C(I) = 0#
    Next I
    C(N) = Exp(N*Log(2#))
    For i=0# To n\2#-1# Step 1
        C(N-2#*(i+1#)) = -(C(N-2#*i)*(n-2#*i)*(n-2#*i-1#)/4#/(i+1#))
    Next i
End Sub


