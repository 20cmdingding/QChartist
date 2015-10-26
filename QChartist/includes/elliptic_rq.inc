''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'Cephes Math Library Release 2.8:  June, 2000
'Copyright 1984, 1987, 1995, 2000 by Stephen L. Moshier
'
'Contributors:
'    * Sergey Bochkanov (ALGLIB project). Translation from C to
'      pseudocode.
'
'See subroutines comments for additional copyrights.
'
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
'Complete elliptic integral of the first kind
'
'Approximates the integral
'
'
'
'           pi/2
'            -
'           | |
'           |           dt
'K(m)  =    |    ------------------
'           |                   2
'         | |    sqrt( 1 - m sin t )
'          -
'           0
'
'using the approximation
'
'    P(x)  -  log x Q(x).
'
'ACCURACY:
'
'                     Relative error:
'arithmetic   domain     # trials      peak         rms
'   IEEE       0,1        30000       2.5e-16     6.8e-17
'
'Cephes Math Library, Release 2.8:  June, 2000
'Copyright 1984, 1987, 2000 by Stephen L. Moshier
'
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

declare Function EllipticIntegralKHighPrecision(ByVal m1 As Double) As Double

Public Function EllipticIntegralK(ByVal m As Double) As Double
    Dim Result As Double

    Result = EllipticIntegralKHighPrecision(1.0-m)

    EllipticIntegralK = Result
End Function


''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'Complete elliptic integral of the first kind
'
'Approximates the integral
'
'
'
'           pi/2
'            -
'           | |
'           |           dt
'K(m)  =    |    ------------------
'           |                   2
'         | |    sqrt( 1 - m sin t )
'          -
'           0
'
'where m = 1 - m1, using the approximation
'
'    P(x)  -  log x Q(x).
'
'The argument m1 is used rather than m so that the logarithmic
'singularity at m = 1 will be shifted to the origin; this
'preserves maximum accuracy.
'
'K(0) = pi/2.
'
'ACCURACY:
'
'                     Relative error:
'arithmetic   domain     # trials      peak         rms
'   IEEE       0,1        30000       2.5e-16     6.8e-17
'
'Алгоритм взят из библиотеки Cephes
'
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Public Function EllipticIntegralKHighPrecision(ByVal m1 As Double) As Double
    Dim Result As Double
    Dim P As Double
    Dim Q As Double

    If m1<=MachineEpsilon then
        Result = 1.3862943611198906188E0-0.5*Log(m1)
    Else
        P = 1.37982864606273237150E-4
        P = P*m1+2.28025724005875567385E-3
        P = P*m1+7.97404013220415179367E-3
        P = P*m1+9.85821379021226008714E-3
        P = P*m1+6.87489687449949877925E-3
        P = P*m1+6.18901033637687613229E-3
        P = P*m1+8.79078273952743772254E-3
        P = P*m1+1.49380448916805252718E-2
        P = P*m1+3.08851465246711995998E-2
        P = P*m1+9.65735902811690126535E-2
        P = P*m1+1.38629436111989062502E0
        Q = 2.94078955048598507511E-5
        Q = Q*m1+9.14184723865917226571E-4
        Q = Q*m1+5.94058303753167793257E-3
        Q = Q*m1+1.54850516649762399335E-2
        Q = Q*m1+2.39089602715924892727E-2
        Q = Q*m1+3.01204715227604046988E-2
        Q = Q*m1+3.73774314173823228969E-2
        Q = Q*m1+4.88280347570998239232E-2
        Q = Q*m1+7.03124996963957469739E-2
        Q = Q*m1+1.24999999999870820058E-1
        Q = Q*m1+4.99999999999999999821E-1
        Result = P-Q*Log(m1)
    End If

    EllipticIntegralKHighPrecision = Result
End Function


''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'Incomplete elliptic integral of the first kind F(phi|m)
'
'Approximates the integral
'
'
'
'               phi
'                -
'               | |
'               |           dt
'F(phi_\m)  =    |    ------------------
'               |                   2
'             | |    sqrt( 1 - m sin t )
'              -
'               0
'
'of amplitude phi and modulus m, using the arithmetic -
'geometric mean algorithm.
'
'
'
'
'ACCURACY:
'
'Tested at random points with m in [0, 1] and phi as indicated.
'
'                     Relative error:
'arithmetic   domain     # trials      peak         rms
'   IEEE     -10,10       200000      7.4e-16     1.0e-16
'
'Cephes Math Library Release 2.8:  June, 2000
'Copyright 1984, 1987, 2000 by Stephen L. Moshier
'
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Public Function IncompleteEllipticIntegralK(ByVal phi As Double, _
         ByVal m As Double) As Double
    Dim Result As Double
    Dim a As Double
    Dim b As Double
    Dim c As Double
    Dim e As Double
    Dim temp As Double
    Dim PIO2 As Double
    Dim t As Double
    Dim K As Double
    Dim d As Long
    Dim md As Long
    Dim s As Long
    Dim npio2 As Long

    PIO2 = 1.57079632679489661923
    If m=0# then
        Result = phi
        IncompleteEllipticIntegralK = Result
        Exit Function
    End If
    a = 1#-m
    If a=0# then
        Result = Log(Tan(0.5*(PIO2+phi)))
        IncompleteEllipticIntegralK = Result
        Exit Function
    End If
    npio2 = Int(phi/PIO2)
    If npio2 Mod 2#<>0# then
        npio2 = npio2+1#
    End If
    If npio2<>0# then
        K = EllipticIntegralK(1#-a)
        phi = phi-npio2*PIO2
    Else
        K = 0#
    End If
    If phi<0# then
        phi = -phi
        s = -1#
    Else
        s = 0#
    End If
    b = Sqr(a)
    t = tan(phi)
    If Abs(t)>10# then
        e = 1.0/(b*t)
        If Abs(e)<10# then
            e = Atn(e)
            If npio2=0# then
                K = EllipticIntegralK(1#-a)
            End If
            temp = K-IncompleteEllipticIntegralK(e, m)
            If s<0# then
                temp = -temp
            End If
            Result = temp+npio2*K
            IncompleteEllipticIntegralK = Result
            Exit Function
        End If
    End If
    a = 1.0
    c = Sqr(m)
    d = 1#
    md = 0#
    While Abs(c/a)>MachineEpsilon
        temp = b/a
        phi = phi+Atn(t*temp)+md*Pi()
        md = Fix((phi+PIO2)/Pi())
        t = t*(1.0+temp)/(1.0-temp*t*t)
        c = 0.5*(a-b)
        temp = Sqr(a*b)
        a = 0.5*(a+b)
        b = temp
        d = d+d
    wend
    temp = (Atn(t)+md*Pi())/(d*a)
    If s<0# then
        temp = -temp
    End If
    Result = temp+npio2*K

    IncompleteEllipticIntegralK = Result
End Function


''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'Complete elliptic integral of the second kind
'
'Approximates the integral
'
'
'           pi/2
'            -
'           | |                 2
'E(m)  =    |    sqrt( 1 - m sin t ) dt
'         | |
'          -
'           0
'
'using the approximation
'
'     P(x)  -  x log x Q(x).
'
'ACCURACY:
'
'                     Relative error:
'arithmetic   domain     # trials      peak         rms
'   IEEE       0, 1       10000       2.1e-16     7.3e-17
'
'Cephes Math Library, Release 2.8: June, 2000
'Copyright 1984, 1987, 1989, 2000 by Stephen L. Moshier
'
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Public Function EllipticIntegralE(ByVal m As Double) As Double
    Dim Result As Double
    Dim P As Double
    Dim Q As Double

    m = 1#-m
    If m=0# then
        Result = 1#
        EllipticIntegralE = Result
        Exit Function
    End If
    P = 1.53552577301013293365E-4
    P = P*m+2.50888492163602060990E-3
    P = P*m+8.68786816565889628429E-3
    P = P*m+1.07350949056076193403E-2
    P = P*m+7.77395492516787092951E-3
    P = P*m+7.58395289413514708519E-3
    P = P*m+1.15688436810574127319E-2
    P = P*m+2.18317996015557253103E-2
    P = P*m+5.68051945617860553470E-2
    P = P*m+4.43147180560990850618E-1
    P = P*m+1.00000000000000000299E0
    Q = 3.27954898576485872656E-5
    Q = Q*m+1.00962792679356715133E-3
    Q = Q*m+6.50609489976927491433E-3
    Q = Q*m+1.68862163993311317300E-2
    Q = Q*m+2.61769742454493659583E-2
    Q = Q*m+3.34833904888224918614E-2
    Q = Q*m+4.27180926518931511717E-2
    Q = Q*m+5.85936634471101055642E-2
    Q = Q*m+9.37499997197644278445E-2
    Q = Q*m+2.49999999999888314361E-1
    Result = P-Q*m*Log(m)

    EllipticIntegralE = Result
End Function


''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'Incomplete elliptic integral of the second kind
'
'Approximates the integral
'
'
'               phi
'                -
'               | |
'               |                   2
'E(phi_\m)  =    |    sqrt( 1 - m sin t ) dt
'               |
'             | |
'              -
'               0
'
'of amplitude phi and modulus m, using the arithmetic -
'geometric mean algorithm.
'
'ACCURACY:
'
'Tested at random arguments with phi in [-10, 10] and m in
'[0, 1].
'                     Relative error:
'arithmetic   domain     # trials      peak         rms
'   IEEE     -10,10      150000       3.3e-15     1.4e-16
'
'Cephes Math Library Release 2.8:  June, 2000
'Copyright 1984, 1987, 1993, 2000 by Stephen L. Moshier
'
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Public Function IncompleteEllipticIntegralE(ByVal phi As Double, _
         ByVal m As Double) As Double
    Dim Result As Double
    Dim PIO2 As Double
    Dim a As Double
    Dim b As Double
    Dim c As Double
    Dim e As Double
    Dim temp As Double
    Dim lphi As Double
    Dim t As Double
    Dim EBig As Double
    Dim d As Long
    Dim md As Long
    Dim npio2 As Long
    Dim s As Long

    PIO2 = 1.57079632679489661923
    If m=0# then
        Result = phi
        IncompleteEllipticIntegralE = Result
        Exit Function
    End If
    lphi = phi
    npio2 = Int(lphi/PIO2)
    If npio2 Mod 2#<>0# then
        npio2 = npio2+1#
    End If
    lphi = lphi-npio2*PIO2
    If lphi<0# then
        lphi = -lphi
        s = -1#
    Else
        s = 1#
    End If
    a = 1.0-m
    EBig = EllipticIntegralE(m)
    If a=0# then
        temp = sin(lphi)
        If s<0# then
            temp = -temp
        End If
        Result = temp+npio2*Ebig
        IncompleteEllipticIntegralE = Result
        Exit Function
    End If
    t = tan(lphi)
    b = Sqr(a)
    
    '
    ' Thanks to Brian Fitzgerald <fitzgb@mml0.meche.rpi.edu>
    ' for pointing out an instability near odd multiples of pi/2
    '
    If Abs(t)>10# then
        
        '
        ' Transform the amplitude
        '
        e = 1.0/(b*t)
        
        '
        ' ... but avoid multiple recursions.
        '
        If Abs(e)<10# then
            e = Atn(e)
            temp = EBig+m*sin(lphi)*sin(e)-IncompleteEllipticIntegralE(e, m)
            If s<0# then
                temp = -temp
            End If
            Result = temp+npio2*Ebig
            IncompleteEllipticIntegralE = Result
            Exit Function
        End If
    End If
    c = Sqr(m)
    a = 1.0
    d = 1#
    e = 0.0
    md = 0#
    While Abs(c/a)>MachineEpsilon
        temp = b/a
        lphi = lphi+Atn(t*temp)+md*PI()
        md = Fix((lphi+PIO2)/PI())
        t = t*(1.0+temp)/(1.0-temp*t*t)
        c = 0.5*(a-b)
        temp = Sqr(a*b)
        a = 0.5*(a+b)
        b = temp
        d = d+d
        e = e+c*sin(lphi)
    wend
    temp = EBig/EllipticIntegralK(m)
    temp = temp*((Atn(t)+md*PI())/(d*a))
    temp = temp+e
    If s<0# then
        temp = -temp
    End If
    Result = temp+npio2*EBig
    IncompleteEllipticIntegralE = Result
    Exit Function

    IncompleteEllipticIntegralE = Result
End Function


