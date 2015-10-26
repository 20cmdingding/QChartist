declare Function SATURN_LBR_FOR(Date_String as string, Time_String as string) as string

Function SATURN_LBR_FOR(Date_String as string, Time_String as string)
' Compute heliocentric, spherical coordinates, LBR
' for Saturn.

defdbl L, B, R, T, DFrac

' DEPENDENCY: JD_NUM_FOR()

  DFrac = (Val(Time_String) * 3600 + Val(Mid$(Time_String, 4, 2)) * 60 + Val(Mid$(Time_String, 7, 2))) / 86400

' Compute T (for 0h on date) as Julian millennia since J2000.0
  T = (JD_NUM_FOR(Date_String) - 2451545 + DFrac) / 365250
            
' Compute heliocentric, ecliptical Longitude L in radians
  L = Saturn_L01(T) + Saturn_L02(T) + Saturn_L03(T) _
    + Saturn_L11(T) + Saturn_L12(T) _
    + Saturn_L21(T) + Saturn_L31(T) + Saturn_L41(T) _
    + Saturn_L51(T)
    
' Modulate L value between 0 and 2*Pi
  If Abs(L) > (2 * rqPi) Then L = L - 2 * rqPi * Int(L / 2 / rqPi)

' Compute heliocentric, ecliptical Latitude B in radians
  B = Saturn_B01(T) + Saturn_B02(T) _
    + Saturn_B11(T) + Saturn_B21(T) + Saturn_B31(T) _
    + Saturn_B41(T) + Saturn_B51(T)
      
' Compute heliocentric distance R in AU
  R = Saturn_R01(T) + Saturn_R02(T) + Saturn_R03(T) _
    + Saturn_R11(T) + Saturn_R12(T) + Saturn_R21(T) _
    + Saturn_R31(T) + Saturn_R41(T) + Saturn_R51(T)

  result = "L = " + str$(L) + "; B = " + str$(B) + "; R = " + str$(R)

End Function