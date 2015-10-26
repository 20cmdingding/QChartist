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
'Incomplete gamma integral
'
'The function is defined by
'
'                          x
'                           -
'                  1       | |  -t  a-1
' igam(a,x)  =   -----     |   e   t   dt.
'                 -      | |
'                | (a)    -
'                          0
'
'
'In this implementation both arguments must be positive.
'The integral is evaluated by either a power series or
'continued fraction expansion, depending on the relative
'values of a and x.
'
'ACCURACY:
'
'                     Relative error:
'arithmetic   domain     # trials      peak         rms
'   IEEE      0,30       200000       3.6e-14     2.9e-15
'   IEEE      0,100      300000       9.9e-14     1.5e-14
'
'Cephes Math Library Release 2.8:  June, 2000
'Copyright 1985, 1987, 2000 by Stephen L. Moshier
'
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

declare Function IncompleteGammaC(ByVal a As Double, _
         ByVal x As Double) As Double

Public Function IncompleteGamma(ByVal a As Double, ByVal x As Double) As Double
    Dim Result As Double
    Dim IGammaEpsilon As Double
    Dim ans As Double
    Dim ax As Double
    Dim c As Double
    Dim r As Double
    Dim Tmp As Double

    IGammaEpsilon = 0.000000000000001
    If x<=0# Or a<=0# then
        Result = 0#
        IncompleteGamma = Result
        Exit Function
    End If
    If x>1# And x>a then
        Result = 1#-IncompleteGammaC(a, x)
        IncompleteGamma = Result
        Exit Function
    End If
    ax = a*Log(x)-x-LnGamma(a, Tmp)
    If ax<-709.78271289338399 then
        Result = 0#
        IncompleteGamma = Result
        Exit Function
    End If
    ax = Exp(ax)
    r = a
    c = 1#
    ans = 1#
    Do
        r = r+1#
        c = c*x/r
        ans = ans+c
    Loop Until c/ans<=IGammaEpsilon
    Result = ans*ax/a

    IncompleteGamma = Result
End Function


''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'Complemented incomplete gamma integral
'
'The function is defined by
'
'
' igamc(a,x)   =   1 - igam(a,x)
'
'                           inf.
'                             -
'                    1       | |  -t  a-1
'              =   -----     |   e   t   dt.
'                   -      | |
'                  | (a)    -
'                            x
'
'
'In this implementation both arguments must be positive.
'The integral is evaluated by either a power series or
'continued fraction expansion, depending on the relative
'values of a and x.
'
'ACCURACY:
'
'Tested at random a, x.
'               a         x                      Relative error:
'arithmetic   domain   domain     # trials      peak         rms
'   IEEE     0.5,100   0,100      200000       1.9e-14     1.7e-15
'   IEEE     0.01,0.5  0,100      200000       1.4e-13     1.6e-15
'
'Cephes Math Library Release 2.8:  June, 2000
'Copyright 1985, 1987, 2000 by Stephen L. Moshier
'
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Public Function IncompleteGammaC(ByVal a As Double, _
         ByVal x As Double) As Double
    Dim Result As Double
    Dim IGammaEpsilon As Double
    Dim IGammaBigNumber As Double
    Dim IGammaBigNumberInv As Double
    Dim ans As Double
    Dim ax As Double
    Dim c As Double
    Dim yc As Double
    Dim r As Double
    Dim t As Double
    Dim y As Double
    Dim z As Double
    Dim pk As Double
    Dim pkm1 As Double
    Dim pkm2 As Double
    Dim qk As Double
    Dim qkm1 As Double
    Dim qkm2 As Double
    Dim Tmp As Double

    IGammaEpsilon = 0.000000000000001
    IGammaBigNumber = 4503599627370496.0
    IGammaBigNumberInv = 2.22044604925031308085*0.0000000000000001
    If x<=0# Or a<=0# then
        Result = 1#
        IncompleteGammaC = Result
        Exit Function
    End If
    If x<1# Or x<a then
        Result = 1#-IncompleteGamma(a, x)
        IncompleteGammaC = Result
        Exit Function
    End If
    ax = a*Log(x)-x-LnGamma(a, Tmp)
    If ax<-709.78271289338399 then
        Result = 0#
        IncompleteGammaC = Result
        Exit Function
    End If
    ax = Exp(ax)
    y = 1#-a
    z = x+y+1#
    c = 0#
    pkm2 = 1#
    qkm2 = x
    pkm1 = x+1#
    qkm1 = z*x
    ans = pkm1/qkm1
    Do
        c = c+1#
        y = y+1#
        z = z+2#
        yc = y*c
        pk = pkm1*z-pkm2*yc
        qk = qkm1*z-qkm2*yc
        If qk<>0# then
            r = pk/qk
            t = Abs((ans-r)/r)
            ans = r
        Else
            t = 1#
        End If
        pkm2 = pkm1
        pkm1 = pk
        qkm2 = qkm1
        qkm1 = qk
        If Abs(pk)>IGammaBigNumber then
            pkm2 = pkm2*IGammaBigNumberInv
            pkm1 = pkm1*IGammaBigNumberInv
            qkm2 = qkm2*IGammaBigNumberInv
            qkm1 = qkm1*IGammaBigNumberInv
        End If
    Loop Until t<=IGammaEpsilon
    Result = ans*ax

    IncompleteGammaC = Result
End Function


''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'Inverse of complemented imcomplete gamma integral
'
'Given p, the function finds x such that
'
' igamc( a, x ) = p.
'
'Starting with the approximate value
'
'        3
' x = a t
'
' where
'
' t = 1 - d - ndtri(p) sqrt(d)
'
'and
'
' d = 1/9a,
'
'the routine performs up to 10 Newton iterations to find the
'root of igamc(a,x) - p = 0.
'
'ACCURACY:
'
'Tested at random a, p in the intervals indicated.
'
'               a        p                      Relative error:
'arithmetic   domain   domain     # trials      peak         rms
'   IEEE     0.5,100   0,0.5       100000       1.0e-14     1.7e-15
'   IEEE     0.01,0.5  0,0.5       100000       9.0e-14     3.4e-15
'   IEEE    0.5,10000  0,0.5        20000       2.3e-13     3.8e-14
'
'Cephes Math Library Release 2.8:  June, 2000
'Copyright 1984, 1987, 1995, 2000 by Stephen L. Moshier
'
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Public Function InvIncompleteGammaC(ByVal a As Double, _
         ByVal y0 As Double) As Double
    Dim Result As Double
    Dim IGammaEpsilon As Double
    Dim IInvGammaBigNumber As Double
    Dim x0 As Double
    Dim x1 As Double
    Dim x As Double
    Dim yl As Double
    Dim yh As Double
    Dim y As Double
    Dim d As Double
    Dim lgm As Double
    Dim dithresh As Double
    Dim i As Long
    Dim dir As Long
    Dim Tmp As Double

    IGammaEpsilon = 0.000000000000001
    IInvGammaBigNumber = 4503599627370496.0
    x0 = IInvGammaBigNumber
    yl = 0#
    x1 = 0#
    yh = 1#
    dithresh = 5#*IGammaEpsilon
    d = 1#/(9#*a)
    y = 1#-d-InvNormalDistribution(y0)*Sqr(d)
    x = a*y*y*y
    lgm = LnGamma(a, Tmp)
    i = 0#
    While i<10#
        If x>x0 Or x<x1 then
            d = 0.0625
            Exit Do
        End If
        y = IncompleteGammaC(a, x)
        If y<yl Or y>yh then
            d = 0.0625
            Exit Do
        End If
        If y<y0 then
            x0 = x
            yl = y
        Else
            x1 = x
            yh = y
        End If
        d = (a-1#)*Log(x)-x-lgm
        If d<-709.78271289338399 then
            d = 0.0625
            Exit Do
        End If
        d = -Exp(d)
        d = (y-y0)/d
        If Abs(d/x)<IGammaEpsilon then
            Result = x
            InvIncompleteGammaC = Result
            Exit Function
        End If
        x = x-d
        i = i+1#
    wend
    If x0=IInvGammaBigNumber then
        If x<=0# then
            x = 1#
        End If
        While x0=IInvGammaBigNumber
            x = (1#+d)*x
            y = IncompleteGammaC(a, x)
            If y<y0 then
                x0 = x
                yl = y
                Exit Do
            End If
            d = d+d
        wend
    End If
    d = 0.5
    dir = 0#
    i = 0#
    While i<400#
        x = x1+d*(x0-x1)
        y = IncompleteGammaC(a, x)
        lgm = (x0-x1)/(x1+x0)
        If Abs(lgm)<dithresh then
            Exit Do
        End If
        lgm = (y-y0)/y0
        If Abs(lgm)<dithresh then
            Exit Do
        End If
        If x<=0.0 then
            Exit Do
        End If
        If y>=y0 then
            x1 = x
            yh = y
            If dir<0# then
                dir = 0#
                d = 0.5
            Else
                If dir>1# then
                    d = 0.5*d+0.5
                Else
                    d = (y0-yl)/(yh-yl)
                End If
            End If
            dir = dir+1#
        Else
            x0 = x
            yl = y
            If dir>0# then
                dir = 0#
                d = 0.5
            Else
                If dir<-1# then
                    d = 0.5*d
                Else
                    d = (y0-yl)/(yh-yl)
                End If
            End If
            dir = dir-1#
        End If
        i = i+1#
    wend
    Result = x

    InvIncompleteGammaC = Result
End Function

$typecheck on
