declare Function URANUS_LBR_FOR(Date_String as string, Time_String as string) as string

Function URANUS_LBR_FOR(Date_String as string, Time_String as string)
' Compute heliocentric, spherical coordinates, LBR
' for Saturn.

defdbl L, B, R, T, DFrac

' DEPENDENCY: JD_NUM_FOR()

  DFrac = (Val(Time_String) * 3600 + Val(Mid$(Time_String, 4, 2)) * 60 + Val(Mid$(Time_String, 7, 2))) / 86400

' Compute T (for 0h on date) as Julian millennia since J2000.0
  T = (JD_NUM_FOR(Date_String) - 2451545 + DFrac) / 365250
            
' Compute heliocentric, ecliptical Longitude L in radians
  L = Uranus_L01(T) + Uranus_L02(T) _
    + Uranus_L11(T) + Uranus_L21(T) + Uranus_L31(T) _
    + Uranus_L41(T) + Uranus_L51(T)
    
' Modulate L value between 0 and 2*Pi
  If Abs(L) > (2 * rqPi) Then L = L - 2 * rqPi * Int(L / 2 / rqPi)

' Compute heliocentric, ecliptical Latitude B in radians
  B = Uranus_B01(T) _
    + Uranus_B11(T) + Uranus_B21(T) + Uranus_B31(T) _
    + Uranus_B41(T)
      
' Compute heliocentric distance R in AU
  R = Uranus_R01(T) + Uranus_R02(T) + Uranus_R03(T) _
    + Uranus_R11(T) + Uranus_R12(T) + Uranus_R21(T) _
    + Uranus_R31(T) + Uranus_R41(T)

  result = "L = " + str$(L) + "; B = " + str$(B) + "; R = " + str$(R)

End Function