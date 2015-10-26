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
'Incomplete beta integral
'
'Returns incomplete beta integral of the arguments, evaluated
'from zero to x.  The function is defined as
'
'                 x
'    -            -
'   | (a+b)      | |  a-1     b-1
' -----------    |   t   (1-t)   dt.
'  -     -     | |
' | (a) | (b)   -
'                0
'
'The domain of definition is 0 <= x <= 1.  In this
'implementation a and b are restricted to positive values.
'The integral from x to 1 may be obtained by the symmetry
'relation
'
'   1 - incbet( a, b, x )  =  incbet( b, a, 1-x ).
'
'The integral is evaluated by a continued fraction expansion
'or, when b*x is small, by a power series.
'
'ACCURACY:
'
'Tested at uniformly distributed random points (a,b,x) with a and b
'in "domain" and x between 0 and 1.
'                                       Relative error
'arithmetic   domain     # trials      peak         rms
'   IEEE      0,5         10000       6.9e-15     4.5e-16
'   IEEE      0,85       250000       2.2e-13     1.7e-14
'   IEEE      0,1000      30000       5.3e-12     6.3e-13
'   IEEE      0,10000    250000       9.3e-11     7.1e-12
'   IEEE      0,100000    10000       8.7e-10     4.8e-11
'Outputs smaller than the IEEE gradual underflow threshold
'were excluded from these statistics.
'
'Cephes Math Library, Release 2.8:  June, 2000
'Copyright 1984, 1995, 2000 by Stephen L. Moshier
'
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

declare Function IncompleteBetaPS(ByVal a As Double, _
         ByVal b As Double, _
         ByVal x As Double, _
         ByVal MAXGAM As Double) As Double
         
declare Function IncompleteBetaFE(ByVal a As Double, _
         ByVal b As Double, _
         ByVal x As Double, _
         ByVal big As Double, _
         ByVal biginv As Double) As Double   
         
declare Function IncompleteBetaFE2(ByVal a As Double, _
         ByVal b As Double, _
         ByVal x As Double, _
         ByVal big As Double, _
         ByVal biginv As Double) As Double            
         
Public Function IncompleteBeta(ByVal a As Double, _
         ByVal b As Double, _
         ByVal x As Double) As Double
    Dim Result As Double
    Dim t As Double
    Dim xc As Double
    Dim w As Double
    Dim y As Double
    Dim flag As Long
    Dim sg As Double
    Dim big As Double
    Dim biginv As Double
    Dim MAXGAM As Double
    Dim MINLOG As Double
    Dim MAXLOG As Double

    big = 4.503599627370496e15
    biginv = 2.22044604925031308085e-16
    MAXGAM = 171.624376956302725
    MINLOG = Log(MinRealNumber)
    MAXLOG = Log(MaxRealNumber)
    If x=0# then
        Result = 0#
        IncompleteBeta = Result
        Exit Function
    End If
    If x=1# then
        Result = 1#
        IncompleteBeta = Result
        Exit Function
    End If
    flag = 0#
    If b*x<=1.0 And x<=0.95 then
        Result = IncompleteBetaPS(a, b, x, MAXGAM)
        IncompleteBeta = Result
        Exit Function
    End If
    w = 1.0-x
    If x>a/(a+b) then
        flag = 1#
        t = a
        a = b
        b = t
        xc = x
        x = w
    Else
        xc = w
    End If
    If flag=1# And b*x<=1.0 And x<=0.95 then
        t = IncompleteBetaPS(a, b, x, MAXGAM)
        If t<=MachineEpsilon then
            Result = 1.0-MachineEpsilon
        Else
            Result = 1.0-t
        End If
        IncompleteBeta = Result
        Exit Function
    End If
    y = x*(a+b-2.0)-(a-1.0)
    If y<0.0 then
        w = IncompleteBetaFE(a, b, x, big, biginv)
    Else
        w = IncompleteBetaFE2(a, b, x, big, biginv)/xc
    End If
    y = a*Log(x)
    t = b*Log(xc)
    If a+b<MAXGAM And Abs(y)<MAXLOG And Abs(t)<MAXLOG then
        t = power(xc, b)
        t = t*power(x, a)
        t = t/a
        t = t*w
        t = t*(gamma(a+b)/(gamma(a)*gamma(b)))
        If flag=1# then
            If t<=MachineEpsilon then
                Result = 1.0-MachineEpsilon
            Else
                Result = 1.0-t
            End If
        Else
            Result = t
        End If
        IncompleteBeta = Result
        Exit Function
    End If
    y = y+t+lngamma(a+b, sg)-lngamma(a, sg)-lngamma(b, sg)
    y = y+Log(w/a)
    If y<MINLOG then
        t = 0.0
    Else
        t = exp(y)
    End If
    If flag=1# then
        If t<=MachineEpsilon then
            t = 1.0-MachineEpsilon
        Else
            t = 1.0-t
        End If
    End If
    Result = t

    IncompleteBeta = Result
End Function


''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'Inverse of imcomplete beta integral
'
'Given y, the function finds x such that
'
' incbet( a, b, x ) = y .
'
'The routine performs interval halving or Newton iterations to find the
'root of incbet(a,b,x) - y = 0.
'
'
'ACCURACY:
'
'                     Relative error:
'               x     a,b
'arithmetic   domain  domain  # trials    peak       rms
'   IEEE      0,1    .5,10000   50000    5.8e-12   1.3e-13
'   IEEE      0,1   .25,100    100000    1.8e-13   3.9e-15
'   IEEE      0,1     0,5       50000    1.1e-12   5.5e-15
'With a and b constrained to half-integer or integer values:
'   IEEE      0,1    .5,10000   50000    5.8e-12   1.1e-13
'   IEEE      0,1    .5,100    100000    1.7e-14   7.9e-16
'With a = .5, b constrained to half-integer or integer values:
'   IEEE      0,1    .5,10000   10000    8.3e-11   1.0e-11
'
'Cephes Math Library Release 2.8:  June, 2000
'Copyright 1984, 1996, 2000 by Stephen L. Moshier
'
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Public Function InvIncompleteBeta(ByVal a As Double, _
         ByVal b As Double, _
         ByVal y As Double) As Double
    Dim Result As Double
    Dim aaa As Double
    Dim bbb As Double
    Dim y0 As Double
    Dim d As Double
    Dim yyy As Double
    Dim x As Double
    Dim x0 As Double
    Dim x1 As Double
    Dim lgm As Double
    Dim yp As Double
    Dim di As Double
    Dim dithresh As Double
    Dim yl As Double
    Dim yh As Double
    Dim xt As Double
    Dim i As Long
    Dim rflg As Long
    Dim dir As Long
    Dim nflg As Long
    Dim s As Double
    Dim MainLoopPos As Long
    Dim ihalve As Long
    Dim ihalvecycle As Long
    Dim newt As Long
    Dim newtcycle As Long
    Dim breaknewtcycle As Long
    Dim breakihalvecycle As Long

    i = 0#
    If y=0# then
        Result = 0#
        InvIncompleteBeta = Result
        Exit Function
    End If
    If y=1.0 then
        Result = 1#
        InvIncompleteBeta = Result
        Exit Function
    End If
    x0 = 0.0
    yl = 0.0
    x1 = 1.0
    yh = 1.0
    nflg = 0#
    MainLoopPos = 0#
    ihalve = 1#
    ihalvecycle = 2#
    newt = 3#
    newtcycle = 4#
    breaknewtcycle = 5#
    breakihalvecycle = 6#
    While True
        
        '
        ' start
        '
        If MainLoopPos=0# then
            If a<=1.0 Or b<=1.0 then
                dithresh = 1.0e-6
                rflg = 0#
                aaa = a
                bbb = b
                y0 = y
                x = aaa/(aaa+bbb)
                yyy = IncompleteBeta(aaa, bbb, x)
                MainLoopPos = ihalve
                GoTo Cont_1
            Else
                dithresh = 1.0e-4
            End If
            yp = -InvNormalDistribution(y)
            If y>0.5 then
                rflg = 1#
                aaa = b
                bbb = a
                y0 = 1.0-y
                yp = -yp
            Else
                rflg = 0#
                aaa = a
                bbb = b
                y0 = y
            End If
            lgm = (yp*yp-3.0)/6.0
            x = 2.0/(1.0/(2.0*aaa-1.0)+1.0/(2.0*bbb-1.0))
            d = yp*Sqr(x+lgm)/x-(1.0/(2.0*bbb-1.0)-1.0/(2.0*aaa-1.0))*(lgm+5.0/6.0-2.0/(3.0*x))
            d = 2.0*d
            If d<Log(MinRealNumber) then
                x = 0#
                Exit Do
            End If
            x = aaa/(aaa+bbb*exp(d))
            yyy = IncompleteBeta(aaa, bbb, x)
            yp = (yyy-y0)/y0
            If Abs(yp)<0.2 then
                MainLoopPos = newt
                GoTo Cont_1
            End If
            MainLoopPos = ihalve
            GoTo Cont_1
        End If
        
        '
        ' ihalve
        '
        If MainLoopPos=ihalve then
            dir = 0#
            di = 0.5
            i = 0#
            MainLoopPos = ihalvecycle
            GoTo Cont_1
        End If
        
        '
        ' ihalvecycle
        '
        If MainLoopPos=ihalvecycle then
            If i<=99# then
                If i<>0# then
                    x = x0+di*(x1-x0)
                    If x=1.0 then
                        x = 1.0-MachineEpsilon
                    End If
                    If x=0.0 then
                        di = 0.5
                        x = x0+di*(x1-x0)
                        If x=0.0 then
                            Exit Do
                        End If
                    End If
                    yyy = IncompleteBeta(aaa, bbb, x)
                    yp = (x1-x0)/(x1+x0)
                    If Abs(yp)<dithresh then
                        MainLoopPos = newt
                        GoTo Cont_1
                    End If
                    yp = (yyy-y0)/y0
                    If Abs(yp)<dithresh then
                        MainLoopPos = newt
                        GoTo Cont_1
                    End If
                End If
                If yyy<y0 then
                    x0 = x
                    yl = yyy
                    If dir<0# then
                        dir = 0#
                        di = 0.5
                    Else
                        If dir>3# then
                            di = 1.0-(1.0-di)*(1.0-di)
                        Else
                            If dir>1# then
                                di = 0.5*di+0.5
                            Else
                                di = (y0-yyy)/(yh-yl)
                            End If
                        End If
                    End If
                    dir = dir+1#
                    If x0>0.75 then
                        If rflg=1# then
                            rflg = 0#
                            aaa = a
                            bbb = b
                            y0 = y
                        Else
                            rflg = 1#
                            aaa = b
                            bbb = a
                            y0 = 1.0-y
                        End If
                        x = 1.0-x
                        yyy = IncompleteBeta(aaa, bbb, x)
                        x0 = 0.0
                        yl = 0.0
                        x1 = 1.0
                        yh = 1.0
                        MainLoopPos = ihalve
                        GoTo Cont_1
                    End If
                Else
                    x1 = x
                    If rflg=1# And x1<MachineEpsilon then
                        x = 0.0
                        Exit Do
                    End If
                    yh = yyy
                    If dir>0# then
                        dir = 0#
                        di = 0.5
                    Else
                        If dir<-3# then
                            di = di*di
                        Else
                            If dir<-1# then
                                di = 0.5*di
                            Else
                                di = (yyy-y0)/(yh-yl)
                            End If
                        End If
                    End If
                    dir = dir-1#
                End If
                i = i+1#
                MainLoopPos = ihalvecycle
                GoTo Cont_1
            Else
                MainLoopPos = breakihalvecycle
                GoTo Cont_1
            End If
        End If
        
        '
        ' breakihalvecycle
        '
        If MainLoopPos=breakihalvecycle then
            If x0>=1.0 then
                x = 1.0-MachineEpsilon
                Exit Do
            End If
            If x<=0.0 then
                x = 0.0
                Exit Do
            End If
            MainLoopPos = newt
            GoTo Cont_1
        End If
        
        '
        ' newt
        '
        If MainLoopPos=newt then
            If nflg<>0# then
                Exit Do
            End If
            nflg = 1#
            lgm = lngamma(aaa+bbb, s)-lngamma(aaa, s)-lngamma(bbb, s)
            i = 0#
            MainLoopPos = newtcycle
            GoTo Cont_1
        End If
        
        '
        ' newtcycle
        '
        If MainLoopPos=newtcycle then
            If i<=7# then
                If i<>0# then
                    yyy = IncompleteBeta(aaa, bbb, x)
                End If
                If yyy<yl then
                    x = x0
                    yyy = yl
                Else
                    If yyy>yh then
                        x = x1
                        yyy = yh
                    Else
                        If yyy<y0 then
                            x0 = x
                            yl = yyy
                        Else
                            x1 = x
                            yh = yyy
                        End If
                    End If
                End If
                If x=1.0 Or x=0.0 then
                    MainLoopPos = breaknewtcycle
                    GoTo Cont_1
                End If
                d = (aaa-1.0)*Log(x)+(bbb-1.0)*Log(1.0-x)+lgm
                If d<Log(MinRealNumber) then
                    Exit Do
                End If
                If d>Log(MaxRealNumber) then
                    MainLoopPos = breaknewtcycle
                    GoTo Cont_1
                End If
                d = exp(d)
                d = (yyy-y0)/d
                xt = x-d
                If xt<=x0 then
                    yyy = (x-x0)/(x1-x0)
                    xt = x0+0.5*yyy*(x-x0)
                    If xt<=0.0 then
                        MainLoopPos = breaknewtcycle
                        GoTo Cont_1
                    End If
                End If
                If xt>=x1 then
                    yyy = (x1-x)/(x1-x0)
                    xt = x1-0.5*yyy*(x1-x)
                    If xt>=1.0 then
                        MainLoopPos = breaknewtcycle
                        GoTo Cont_1
                    End If
                End If
                x = xt
                If Abs(d/x)<128.0*MachineEpsilon then
                    Exit Do
                End If
                i = i+1#
                MainLoopPos = newtcycle
                GoTo Cont_1
            Else
                MainLoopPos = breaknewtcycle
                GoTo Cont_1
            End If
        End If
        
        '
        ' breaknewtcycle
        '
        If MainLoopPos=breaknewtcycle then
            dithresh = 256.0*MachineEpsilon
            MainLoopPos = ihalve
            GoTo Cont_1
        End If
Cont_1:
    wend
    
    '
    ' done
    '
    If rflg<>0# then
        If x<=MachineEpsilon then
            x = 1.0-MachineEpsilon
        Else
            x = 1.0-x
        End If
    End If
    Result = x

    InvIncompleteBeta = Result
End Function


''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'Continued fraction expansion #1 for incomplete beta integral
'
'Cephes Math Library, Release 2.8:  June, 2000
'Copyright 1984, 1995, 2000 by Stephen L. Moshier
'
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Private Function IncompleteBetaFE(ByVal a As Double, _
         ByVal b As Double, _
         ByVal x As Double, _
         ByVal big As Double, _
         ByVal biginv As Double) As Double
    Dim Result As Double
    Dim xk As Double
    Dim pk As Double
    Dim pkm1 As Double
    Dim pkm2 As Double
    Dim qk As Double
    Dim qkm1 As Double
    Dim qkm2 As Double
    Dim k1 As Double
    Dim k2 As Double
    Dim k3 As Double
    Dim k4 As Double
    Dim k5 As Double
    Dim k6 As Double
    Dim k7 As Double
    Dim k8 As Double
    Dim r As Double
    Dim t As Double
    Dim ans As Double
    Dim thresh As Double
    Dim n As Long

    k1 = a
    k2 = a+b
    k3 = a
    k4 = a+1.0
    k5 = 1.0
    k6 = b-1.0
    k7 = k4
    k8 = a+2.0
    pkm2 = 0.0
    qkm2 = 1.0
    pkm1 = 1.0
    qkm1 = 1.0
    ans = 1.0
    r = 1.0
    n = 0#
    thresh = 3.0*MachineEpsilon
    Do
        xk = -(x*k1*k2/(k3*k4))
        pk = pkm1+pkm2*xk
        qk = qkm1+qkm2*xk
        pkm2 = pkm1
        pkm1 = pk
        qkm2 = qkm1
        qkm1 = qk
        xk = x*k5*k6/(k7*k8)
        pk = pkm1+pkm2*xk
        qk = qkm1+qkm2*xk
        pkm2 = pkm1
        pkm1 = pk
        qkm2 = qkm1
        qkm1 = qk
        If qk<>0# then
            r = pk/qk
        End If
        If r<>0# then
            t = Abs((ans-r)/r)
            ans = r
        Else
            t = 1.0
        End If
        If t<thresh then
            Exit Do
        End If
        k1 = k1+1.0
        k2 = k2+1.0
        k3 = k3+2.0
        k4 = k4+2.0
        k5 = k5+1.0
        k6 = k6-1.0
        k7 = k7+2.0
        k8 = k8+2.0
        If Abs(qk)+Abs(pk)>big then
            pkm2 = pkm2*biginv
            pkm1 = pkm1*biginv
            qkm2 = qkm2*biginv
            qkm1 = qkm1*biginv
        End If
        If Abs(qk)<biginv Or Abs(pk)<biginv then
            pkm2 = pkm2*big
            pkm1 = pkm1*big
            qkm2 = qkm2*big
            qkm1 = qkm1*big
        End If
        n = n+1#
    Loop Until n=300#
    Result = ans

    IncompleteBetaFE = Result
End Function


''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'Continued fraction expansion #2
'for incomplete beta integral
'
'Cephes Math Library, Release 2.8:  June, 2000
'Copyright 1984, 1995, 2000 by Stephen L. Moshier
'
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Private Function IncompleteBetaFE2(ByVal a As Double, _
         ByVal b As Double, _
         ByVal x As Double, _
         ByVal big As Double, _
         ByVal biginv As Double) As Double
    Dim Result As Double
    Dim xk As Double
    Dim pk As Double
    Dim pkm1 As Double
    Dim pkm2 As Double
    Dim qk As Double
    Dim qkm1 As Double
    Dim qkm2 As Double
    Dim k1 As Double
    Dim k2 As Double
    Dim k3 As Double
    Dim k4 As Double
    Dim k5 As Double
    Dim k6 As Double
    Dim k7 As Double
    Dim k8 As Double
    Dim r As Double
    Dim t As Double
    Dim ans As Double
    Dim z As Double
    Dim thresh As Double
    Dim n As Long

    k1 = a
    k2 = b-1.0
    k3 = a
    k4 = a+1.0
    k5 = 1.0
    k6 = a+b
    k7 = a+1.0
    k8 = a+2.0
    pkm2 = 0.0
    qkm2 = 1.0
    pkm1 = 1.0
    qkm1 = 1.0
    z = x/(1.0-x)
    ans = 1.0
    r = 1.0
    n = 0#
    thresh = 3.0*MachineEpsilon
    Do
        xk = -(z*k1*k2/(k3*k4))
        pk = pkm1+pkm2*xk
        qk = qkm1+qkm2*xk
        pkm2 = pkm1
        pkm1 = pk
        qkm2 = qkm1
        qkm1 = qk
        xk = z*k5*k6/(k7*k8)
        pk = pkm1+pkm2*xk
        qk = qkm1+qkm2*xk
        pkm2 = pkm1
        pkm1 = pk
        qkm2 = qkm1
        qkm1 = qk
        If qk<>0# then
            r = pk/qk
        End If
        If r<>0# then
            t = Abs((ans-r)/r)
            ans = r
        Else
            t = 1.0
        End If
        If t<thresh then
            Exit Do
        End If
        k1 = k1+1.0
        k2 = k2-1.0
        k3 = k3+2.0
        k4 = k4+2.0
        k5 = k5+1.0
        k6 = k6+1.0
        k7 = k7+2.0
        k8 = k8+2.0
        If Abs(qk)+Abs(pk)>big then
            pkm2 = pkm2*biginv
            pkm1 = pkm1*biginv
            qkm2 = qkm2*biginv
            qkm1 = qkm1*biginv
        End If
        If Abs(qk)<biginv Or Abs(pk)<biginv then
            pkm2 = pkm2*big
            pkm1 = pkm1*big
            qkm2 = qkm2*big
            qkm1 = qkm1*big
        End If
        n = n+1#
    Loop Until n=300#
    Result = ans

    IncompleteBetaFE2 = Result
End Function


''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'Power series for incomplete beta integral.
'Use when b*x is small and x not too close to 1.
'
'Cephes Math Library, Release 2.8:  June, 2000
'Copyright 1984, 1995, 2000 by Stephen L. Moshier
'
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Private Function IncompleteBetaPS(ByVal a As Double, _
         ByVal b As Double, _
         ByVal x As Double, _
         ByVal MAXGAM As Double) As Double
    Dim Result As Double
    Dim s As Double
    Dim t As Double
    Dim u As Double
    Dim v As Double
    Dim n As Double
    Dim t1 As Double
    Dim z As Double
    Dim ai As Double
    Dim sg As Double

    ai = 1.0/a
    u = (1.0-b)*x
    v = u/(a+1.0)
    t1 = v
    t = u
    n = 2.0
    s = 0.0
    z = MACHinEePsilon*ai
    While Abs(v)>z
        u = (n-b)*x/n
        t = t*u
        v = t/(a+n)
        s = s+v
        n = n+1.0
    wend
    s = s+t1
    s = s+ai
    u = a*Log(x)
    If a+b<MAXGAM And Abs(u)<Log(MaxRealNumber) then
        t = gamma(a+b)/(gamma(a)*gamma(b))
        s = s*t*power(x, a)
    Else
        t = lngamma(a+b, sg)-lngamma(a, sg)-lngamma(b, sg)+u+Log(s)
        If t<Log(MinRealNumber) then
            s = 0.0
        Else
            s = exp(t)
        End If
    End If
    Result = s

    IncompleteBetaPS = Result
End Function


