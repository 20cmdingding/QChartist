declare Function Jupiter_LBR_FOR(Date_String as string, Time_String as string) as string

Function Jupiter_LBR_FOR(Date_String as string, Time_String as string)
' Compute heliocentric, spherical coordinates, LBR
' for Jupiter.

defdbl L, B, R, T, DFrac

' DEPENDENCY: JD_NUM_FOR()


  DFrac = (Val(Time_String) * 3600 + Val(Mid$(Time_String, 4, 2)) * 60 + Val(Mid$(Time_String, 7, 2))) / 86400

' Compute T (for 0h on date) as Julian millennia since J2000.0
  T = (JD_NUM_FOR(Date_String) - 2451545 + DFrac) / 365250
  
' Compute heliocentric, ecliptical Longitude L in radians
  L = Jupiter_L01(T) + Jupiter_L02(T)
  L = L + Jupiter_L11(T) + Jupiter_L21(T) + Jupiter_L31(T) _
    + Jupiter_L41(T) + Jupiter_L51(T)
    
' Modulate L value between 0 and 2*Pi
  If Abs(L) > (2 * rqPi) Then L = L - 2 * rqPi * Int(L / 2 / rqPi)

' Compute heliocentric, ecliptical Latitude B in radians
  B = Jupiter_B01(T) _
    + Jupiter_B11(T) + Jupiter_B21(T) + Jupiter_B31(T) _
    + Jupiter_B41(T) + Jupiter_B51(T)

' Compute heliocentric distance R in AU
  R = Jupiter_R01(T) + Jupiter_R02(T)
  R = R + Jupiter_R11(T)
  R = R + Jupiter_R21(T)
  R = R + Jupiter_R31(T)
  R = R + Jupiter_R41(T)
  R = R + Jupiter_R51(T)

  
' Return LBR values within a labeled and delimited string.
  result = "L = " + str$(L) + "; B = " + str$(B) + "; R = " + str$(R)

End Function
