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
'Binomial distribution
'
'Returns the sum of the terms 0 through k of the Binomial
'probability density:
'
'  k
'  --  ( n )   j      n-j
'  >   (   )  p  (1-p)
'  --  ( j )
' j=0
'
'The terms are not summed directly; instead the incomplete
'beta integral is employed, according to the formula
'
'y = bdtr( k, n, p ) = incbet( n-k, k+1, 1-p ).
'
'The arguments must be positive, with p ranging from 0 to 1.
'
'ACCURACY:
'
'Tested at random points (a,b,p), with p between 0 and 1.
'
'              a,b                     Relative error:
'arithmetic  domain     # trials      peak         rms
' For p between 0.001 and 1:
'   IEEE     0,100       100000      4.3e-15     2.6e-16
'
'Cephes Math Library Release 2.8:  June, 2000
'Copyright 1984, 1987, 1995, 2000 by Stephen L. Moshier
'
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

Public Function BinomialDistribution(ByVal k As Long, _
         ByVal n As Long, _
         ByVal p As Double) As Double
    Dim Result As Double
    Dim dk As Double
    Dim dn As Double

    If k=-1# then
        Result = 0#
        BinomialDistribution = Result
        Exit Function
    End If
    If k=n then
        Result = 1#
        BinomialDistribution = Result
        Exit Function
    End If
    dn = n-k
    If k=0# then
        dk = 1.0-p^dn
    Else
        dk = k+1#
        dk = IncompleteBeta(dn, dk, 1.0-p)
    End If
    Result = dk

    BinomialDistribution = Result
End Function


''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'Complemented binomial distribution
'
'Returns the sum of the terms k+1 through n of the Binomial
'probability density:
'
'  n
'  --  ( n )   j      n-j
'  >   (   )  p  (1-p)
'  --  ( j )
' j=k+1
'
'The terms are not summed directly; instead the incomplete
'beta integral is employed, according to the formula
'
'y = bdtrc( k, n, p ) = incbet( k+1, n-k, p ).
'
'The arguments must be positive, with p ranging from 0 to 1.
'
'ACCURACY:
'
'Tested at random points (a,b,p).
'
'              a,b                     Relative error:
'arithmetic  domain     # trials      peak         rms
' For p between 0.001 and 1:
'   IEEE     0,100       100000      6.7e-15     8.2e-16
' For p between 0 and .001:
'   IEEE     0,100       100000      1.5e-13     2.7e-15
'
'Cephes Math Library Release 2.8:  June, 2000
'Copyright 1984, 1987, 1995, 2000 by Stephen L. Moshier
'
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Public Function BinomialCDistribution(ByVal k As Long, _
         ByVal n As Long, _
         ByVal p As Double) As Double
    Dim Result As Double
    Dim dk As Double
    Dim dn As Double

    If k=-1# then
        Result = 1#
        BinomialCDistribution = Result
        Exit Function
    End If
    If k=n then
        Result = 0#
        BinomialCDistribution = Result
        Exit Function
    End If
    dn = n-k
    If k=0# then
        If p<0.01 then
            dk = -expm1(dn*log1p(-p))
        Else
            dk = 1.0-((1.0-p)^dn)
        End If
    Else
        dk = k+1#
        dk = IncompleteBeta(dk, dn, p)
    End If
    Result = dk

    BinomialCDistribution = Result
End Function


''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'Inverse binomial distribution
'
'Finds the event probability p such that the sum of the
'terms 0 through k of the Binomial probability density
'is equal to the given cumulative probability y.
'
'This is accomplished using the inverse beta integral
'function and the relation
'
'1 - p = incbi( n-k, k+1, y ).
'
'ACCURACY:
'
'Tested at random points (a,b,p).
'
'              a,b                     Relative error:
'arithmetic  domain     # trials      peak         rms
' For p between 0.001 and 1:
'   IEEE     0,100       100000      2.3e-14     6.4e-16
'   IEEE     0,10000     100000      6.6e-12     1.2e-13
' For p between 10^-6 and 0.001:
'   IEEE     0,100       100000      2.0e-12     1.3e-14
'   IEEE     0,10000     100000      1.5e-12     3.2e-14
'
'Cephes Math Library Release 2.8:  June, 2000
'Copyright 1984, 1987, 1995, 2000 by Stephen L. Moshier
'
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
Public Function InvBinomialDistribution(ByVal k As Long, _
         ByVal n As Long, _
         ByVal y As Double) As Double
    Dim Result As Double
    Dim dk As Double
    Dim dn As Double
    Dim p As Double

    dn = n-k
    If k=0# then
        If y>0.8 then
            p = -expm1(log1p(y-1.0)/dn)
        Else
            p = 1.0-(y^(1.0/dn))
        End If
    Else
        dk = k+1#
        p = IncompleteBeta(dn, dk, 0.5)
        If p>0.5 then
            p = InvIncompleteBeta(dk, dn, 1.0-y)
        Else
            p = 1.0-InvIncompleteBeta(dn, dk, y)
        End If
    End If
    Result = p

    InvBinomialDistribution = Result
End Function


