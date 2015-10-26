declare Function VENUS_LBR_FOR(Date_String as string, Time_String as string) as string

Function VENUS_LBR_FOR(Date_String as string, Time_String as string)
' Compute heliocentric, spherical coordinates, LBR
' for Saturn.

defdbl L, B, R, T, DFrac

' DEPENDENCY: JD_NUM_FOR()

  DFrac = (Val(Time_String) * 3600 + Val(Mid$(Time_String, 4, 2)) * 60 + Val(Mid$(Time_String, 7, 2))) / 86400

' Compute T (for 0h on date) as Julian millennia since J2000.0
  T = (JD_NUM_FOR(Date_String) - 2451545 + DFrac) / 365250
            
' Compute heliocentric, ecliptical Longitude L in radians
  L = Venus_L01(T) + Venus_L11(T) + Venus_L21(T) + Venus_L31(T) _
    + Venus_L41(T) + Venus_L51(T)
    
' Modulate L value between 0 and 2*Pi
  If Abs(L) > (2 * rqPi) Then L = L - 2 * rqPi * Int(L / 2 / rqPi)

' Compute heliocentric, ecliptical Latitude B in radians
  B = Venus_B01(T) + Venus_B11(T) + Venus_B21(T) + Venus_B31(T) _
    + Venus_B41(T) + Venus_B51(T)
      
' Compute heliocentric distance R in AU
  R = Venus_R01(T) + Venus_R11(T) + Venus_R21(T) + Venus_R31(T) _
    + Venus_R41(T) + Venus_R51(T)

  result = "L = " + str$(L) + "; B = " + str$(B) + "; R = " + str$(R)

End Function