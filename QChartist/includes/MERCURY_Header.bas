declare Function MERCURY_LBR_FOR(Date_String as string, Time_String as string) as string

Function MERCURY_LBR_FOR(Date_String as string, Time_String as string)
' Compute heliocentric, spherical coordinates, LBR
' for MERCURY.

defdbl L, B, R, T, DFrac

' DEPENDENCY: JD_NUM_FOR()

  DFrac = (Val(Time_String) * 3600 + Val(Mid$(Time_String, 4, 2)) * 60 + Val(Mid$(Time_String, 7, 2))) / 86400

' Compute T (for 0h on date) as Julian millennia since J2000.0
  T = (JD_NUM_FOR(Date_String) - 2451545 + DFrac) / 365250
            
' Compute heliocentric, ecliptical Longitude L in radians
  L = Mercury_L01(T) + Mercury_L02(T) + Mercury_L03(T) + Mercury_L11(T) _
    + Mercury_L12(T) + Mercury_L21(T) + Mercury_L31(T) + Mercury_L41(T) _
    + Mercury_L51(T)
    
' Modulate L value between 0 and 2*Pi
  If Abs(L) > (2 * rqPi) Then L = L - 2 * rqPi * Int(L / 2 / rqPi)

' Compute heliocentric, ecliptical Latitude B in radians
  B = Mercury_B01(T) + Mercury_B02(T) + Mercury_B11(T) + Mercury_B21(T) _
    + Mercury_B31(T) + Mercury_B41(T) + Mercury_B51(T)
      
' Compute heliocentric distance R in AU
  R = Mercury_R01(T) + Mercury_R02(T) + Mercury_R03(T) + Mercury_R11(T) _
    + Mercury_R12(T) + Mercury_R21(T) + Mercury_R31(T) + Mercury_R41(T) _
    + Mercury_R51(T)

  result = "L = " + str$(L) + "; B = " + str$(B) + "; R = " + str$(R)

End Function