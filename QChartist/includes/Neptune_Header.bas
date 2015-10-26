declare Function NEPTUNE_LBR_FOR(Date_String as string, Time_String as string) as string

Function NEPTUNE_LBR_FOR(Date_String as string, Time_String as string)
' Compute heliocentric, spherical coordinates, LBR
' for Neptune.

defdbl L, B, R, T, DFrac

' DEPENDENCY: JD_NUM_FOR()

  DFrac = (Val(Time_String) * 3600 + Val(Mid$(Time_String, 4, 2)) * 60 + Val(Mid$(Time_String, 7, 2))) / 86400

' Compute T (for 0h on date) as Julian millennia since J2000.0
  T = (JD_NUM_FOR(Date_String) - 2451545 + DFrac) / 365250
            
' Compute heliocentric, ecliptical Longitude L in radians
  L = Neptune_L01(T)
  L = L + Neptune_L11(T)
  L = L + Neptune_L21(T)
  L = L + Neptune_L31(T)
  L = L + Neptune_L41(T)
  L = L + Neptune_L51(T)
    
' Modulate L value between 0 and 2*Pi
  If Abs(L) > (2 * rqPi) Then L = L - 2 * rqPi * Int(L / 2 / rqPi)

' Compute heliocentric, ecliptical Latitude B in radians
  B = Neptune_B01(T)
  B = B + Neptune_B11(T)
  B = B + Neptune_B21(T)
  B = B + Neptune_B31(T)
  B = B + Neptune_B41(T)
  B = B + Neptune_B51(T)
      
' Compute heliocentric distance R in AU
  R = Neptune_R01(T) + Neptune_R02(T)
  R = R + Neptune_R11(T)
  R = R + Neptune_R21(T)
  R = R + Neptune_R31(T)
  R = R + Neptune_R41(T)

  result = "L = " + str$(L) + "; B = " + str$(B) + "; R = " + str$(R)

End Function