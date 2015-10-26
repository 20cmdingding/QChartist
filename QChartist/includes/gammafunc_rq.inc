$typecheck off

''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'Cephes Math Library Release 2.8:  June, 2000
'Copyright by Stephen L. Moshier
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
'Gamma function
'
'Input parameters:
'    X   -   argument
'
'Domain:
'    0 < X < 171.6
'    -170 < X < 0, X is not an integer.
'
'Relative error:
' arithmetic   domain     # trials      peak         rms
'    IEEE    -170,-33      20000       2.3e-15     3.3e-16
'    IEEE     -33,  33     20000       9.4e-16     2.2e-16
'    IEEE      33, 171.6   20000       2.3e-15     3.2e-16
'
'Cephes Math Library Release 2.8:  June, 2000
'Original copyright 1984, 1987, 1989, 1992, 2000 by Stephen L. Moshier
'Translated to AlgoPascal by Bochkanov Sergey (2005, 2006, 2007).
'
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

declare Function GammaStirF(ByVal X As Double) As Double

Public Function Gamma(ByVal x As Double) As Double
    Dim Result As Double
    Dim p As Double
    Dim PP As Double
    Dim q As Double
    Dim QQ As Double
    Dim z As Double
    Dim i As Long
    Dim SgnGam As Double

    SgnGam = 1#
    q = Abs(x)
    If q>33.0 then
        If x<0.0 then
            p = Int(q)
            i = Round(p)
            If i Mod 2#=0# then
                SgnGam = -1#
            End If
            z = q-p
            If z>0.5 then
                p = p+1#
                z = q-p
            End If
            z = q*Sin(Pi()*z)
            z = Abs(z)
            z = Pi()/(z*GammaStirF(q))
        Else
            z = GammaStirF(x)
        End If
        Result = SgnGam*z
        Gamma = Result
        Exit Function
    End If
    z = 1#
    While x>=3#
        x = x-1#
        z = z*x
    wend
    While x<0#
        If x>-0.000000001 then
            Result = z/((1#+0.5772156649015329*x)*x)
            Gamma = Result
            Exit Function
        End If
        z = z/x
        x = x+1#
    wend
    While x<2#
        If x<0.000000001 then
            Result = z/((1#+0.5772156649015329*x)*x)
            Gamma = Result
            Exit Function
        End If
        z = z/x
        x = x+1.0
    wend
    If x=2# then
        Result = z
        Gamma = Result
        Exit Function
    End If
    x = x-2.0
    PP = 1.60119522476751861407E-4
    PP = 1.19135147006586384913E-3+X*PP
    PP = 1.04213797561761569935E-2+X*PP
    PP = 4.76367800457137231464E-2+X*PP
    PP = 2.07448227648435975150E-1+X*PP
    PP = 4.94214826801497100753E-1+X*PP
    PP = 9.99999999999999996796E-1+X*PP
    QQ = -2.31581873324120129819E-5
    QQ = 5.39605580493303397842E-4+X*QQ
    QQ = -4.45641913851797240494E-3+X*QQ
    QQ = 1.18139785222060435552E-2+X*QQ
    QQ = 3.58236398605498653373E-2+X*QQ
    QQ = -2.34591795718243348568E-1+X*QQ
    QQ = 7.14304917030273074085E-2+X*QQ
    QQ = 1.00000000000000000320+X*QQ
    Result = z*PP/QQ
    Gamma = Result
    Exit Function

    Gamma = Result
End Function


''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'Natural logarithm of gamma function
'
'Input parameters:
'    X       -   argument
'
'Result:
'    logarithm of the absolute value of the Gamma(X).
'
'Output parameters:
'    SgnGam  -   sign(Gamma(X))
'
'Domain:
'    0 < X < 2.55e305
'    -2.55e305 < X < 0, X is not an integer.
'
'ACCURACY:
'arithmetic      domain        # trials     peak         rms
'   IEEE    0, 3                 28000     5.4e-16     1.1e-16
'   IEEE    2.718, 2.556e305     40000     3.5e-16     8.3e-17
'The error criterion was relative when the function magnitude
'was greater than one but absolute when it was less than one.
'
'The following test used the relative error criterion, though
'at certain points the relative error could be much higher than
'indicated.
'   IEEE    -200, -4             10000     4.8e-16     1.3e-16
'
'Cephes Math Library Release 2.8:  June, 2000
'Copyright 1984, 1987, 1989, 1992, 2000 by Stephen L. Moshier
'Translated to AlgoPascal by Bochkanov Sergey (2005, 2006, 2007).
'
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Public Function LnGamma(ByVal x As Double, ByRef SgnGam As Double) As Double
    Dim Result As Double
    Dim A As Double
    Dim B As Double
    Dim C As Double
    Dim p As Double
    Dim q As Double
    Dim u As Double
    Dim w As Double
    Dim z As Double
    Dim i As Long
    Dim LogPi As Double
    Dim LS2PI As Double
    Dim Tmp As Double

    SgnGam = 1#
    LogPi = 1.14472988584940017414
    LS2PI = 0.91893853320467274178
    If x<-34.0 then
        q = -x
        w = LnGamma(q, Tmp)
        p = Int(q)
        i = Round(p)
        If i Mod 2#=0# then
            SgnGam = -1#
        Else
            SgnGam = 1#
        End If
        z = q-p
        If z>0.5 then
            p = p+1#
            z = p-q
        End If
        z = q*Sin(Pi()*z)
        Result = LogPi-Log(z)-w
        LnGamma = Result
        Exit Function
    End If
    If x<13# then
        z = 1#
        p = 0#
        u = x
        While u>=3#
            p = p-1#
            u = x+p
            z = z*u
        wend
        While u<2#
            z = z/u
            p = p+1#
            u = x+p
        wend
        If z<0# then
            sgngam = -1#
            z = -z
        Else
            sgngam = 1#
        End If
        If u=2# then
            Result = Log(z)
            LnGamma = Result
            Exit Function
        End If
        p = p-2#
        x = x+p
        B = -1378.25152569120859100
        B = -38801.6315134637840924+X*B
        B = -331612.992738871184744+X*B
        B = -1162370.97492762307383+X*B
        B = -1721737.00820839662146+X*B
        B = -853555.664245765465627+X*B
        C = 1#
        C = -351.815701436523470549+X*C
        C = -17064.2106651881159223+X*C
        C = -220528.590553854454839+X*C
        C = -1139334.44367982507207+X*C
        C = -2532523.07177582951285+X*C
        C = -2018891.41433532773231+X*C
        p = x*B/C
        Result = Log(z)+p
        LnGamma = Result
        Exit Function
    End If
    q = (x-0.5)*Log(x)-x+LS2PI
    If x>100000000# then
        Result = q
        LnGamma = Result
        Exit Function
    End If
    p = 1#/(x*x)
    If x>=1000.0 then
        q = q+((7.9365079365079365079365*0.0001*p-2.7777777777777777777778*0.001)*p+0.0833333333333333333333)/x
    Else
        A = 8.11614167470508450300*0.0001
        A = -(5.95061904284301438324*0.0001)+p*A
        A = 7.93650340457716943945*0.0001+p*A
        A = -(2.77777777730099687205*0.001)+p*A
        A = 8.33333333333331927722*0.01+p*A
        q = q+A/x
    End If
    Result = q

    LnGamma = Result
End Function


Private Function GammaStirF(ByVal X As Double) As Double
    Dim Result As Double
    Dim y As Double
    Dim w As Double
    Dim v As Double
    Dim Stir As Double

    w = 1#/x
    Stir = 7.87311395793093628397E-4
    Stir = -2.29549961613378126380E-4+w*Stir
    Stir = -2.68132617805781232825E-3+w*Stir
    Stir = 3.47222221605458667310E-3+w*Stir
    Stir = 8.33333333333482257126E-2+w*Stir
    w = 1#+w*Stir
    y = Exp(x)
    If x>143.01608 then
        v = Power(x, 0.5*x-0.25)
        y = v*(v/y)
    Else
        y = Power(x, x-0.5)/y
    End If
    Result = 2.50662827463100050242*y*w

    GammaStirF = Result
End Function

$typecheck on
