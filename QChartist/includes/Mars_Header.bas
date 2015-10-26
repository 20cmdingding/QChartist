declare Function MARS_LBR_FOR(Date_String as string, Time_String as string) as string

Function MARS_LBR_FOR(Date_String as string, Time_String as string)
' Compute heliocentric, spherical coordinates, LBR
' for Mars.

defdbl L, B, R, T, DFrac

' DEPENDENCY: JD_NUM_FOR()

  DFrac = (Val(Time_String) * 3600 + Val(Mid$(Time_String, 4, 2)) * 60 + Val(Mid$(Time_String, 7, 2))) / 86400

' Compute T (for 0h on date) as Julian millennia since J2000.0
  T = (JD_NUM_FOR(Date_String) - 2451545 + DFrac) / 365250
      
' Compute heliocentric longitude L in radians
  L = Mars_L01(T) + Mars_L02(T) + Mars_L03(T) _
    + Mars_L11(T) + Mars_L12(T) _
    + Mars_L21(T) + Mars_L31(T) + Mars_L41(T) + Mars_L51(T)
    
' Modulate L value between 0 and 2*Pi
  If Abs(L) > (2 * rqPi) Then L = L - 2 * rqPi * Int(L / 2 / rqPi)
    
' Compute heliocentric latitude B in radians
  B = Mars_B01(T) + Mars_B11(T) + Mars_B21(T) + Mars_B31(T) _
    + Mars_B41(T) + Mars_B51(T)
  
' Compute heliocentric distance R in AU
  R = Mars_R01(T) + Mars_R02(T) + Mars_R03(T) + Mars_R11(T) _
    + Mars_R12(T) _
    + Mars_R21(T) + Mars_R31(T) + Mars_R41(T) + Mars_R51(T)
  

  MARS_LBR_FOR = "L = " + str$(L) + "; B = " + str$(B) + "; R = " + str$(R)

End Function
