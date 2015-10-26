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
'Beta function
'
'
'                  -     -
'                 | (a) | (b)
'beta( a, b )  =  -----------.
'                    -
'                   | (a+b)
'
'For large arguments the logarithm of the function is
'evaluated using lgam(), then exponentiated.
'
'ACCURACY:
'
'                     Relative error:
'arithmetic   domain     # trials      peak         rms
'   IEEE       0,30       30000       8.1e-14     1.1e-14
'
'Cephes Math Library Release 2.0:  April, 1987
'Copyright 1984, 1987 by Stephen L. Moshier
'
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

Public Function Beta(ByVal a As Double, ByVal b As Double) As Double
    Dim Result As Double
    Dim y As Double
    Dim sg As Double
    Dim S As Double

    sg = 1#
    y = a+b
    If Abs(y)>171.624376956302725 then
        y = LnGamma(y, S)
        sg = sg*S
        y = LnGamma(b, S)-y
        sg = sg*S
        y = LnGamma(a, S)+y
        sg = sg*S
        Result = sg*Exp(y)
        Beta = Result
        Exit Function
    End If
    y = Gamma(y)
    If a>b then
        y = Gamma(a)/y
        y = y*Gamma(b)
    Else
        y = Gamma(b)/y
        y = y*Gamma(a)
    End If
    Result = y

    Beta = Result
End Function



