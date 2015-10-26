dim Q(2500) as string

declare function JD_NUM_FOR(Dd_Mmm_Yyyy_BCAD as string) as double
declare Function IS_LEAP_YEAR(Year as string) As integer
declare Function DAYS_IN_MONTH_OF(Month_Year_BCAD as string) as integer
declare Function MONTH_NUM_FOR_ABBREV(Month_Abbrev as string) as integer

function JD_NUM_FOR(Dd_Mmm_Yyyy_BCAD as string)
' Version Alpha 0.003
' Compute astronomical JD number for any given date
' on either the Julian or Gregorian calendars.
'
' In this module, the Julian or Gregorian calendar mode is AUTOMATICALLY
' selected according to the given date.  Any dates PRIOR to the date
' "15 OCT 1582" are considered Julian calendar dates and any dates
' from that date forward are considered Gregorian calendar dates.
'
' Examples of valid date strings are:
' "20 MAY 1977 AD" or "25 DEC 357 BC" or "4 JUL 1776"
' The "AD" is optional and implied if "BC" is not indicated.
'
' FUNCTION LEVEL 0 - No external function dependency.
'
' This function assumes that all input arguments are valid.
' NO error checking is done.
'
'  Define the main function variables
   defstr Date_String, Cal_Mode
   
   defstr MMM, BCAD
   defint DD, Mm, YYYY
   defdbl JD, Q2
       
'  Define random work variables
   defstr Q, Q1   
   Dim Pointer As Integer
    
'  Read the (Cal_Mode) from the (JG_Mode).  This determines the calendar,
'  Julian or Gregorian, to which the computed JD number applies.
'  Only the 1st character of (JG_Mode) is used. If that character is "J"
'  then Julian "J" mode is set, otherwise Gregorian "G" mode is set.
'  This test is NOT case sensitive.
 ' If InStr(UCase(JG_Mode), "J") <> 0 Then Cal_Mode = "J" Else Cal_Mode = "G"
  
' ------------------------------------------------
' Read calendar date (Assumed to be a valid date).
' No error tests are done in this core version.

'   Strip all spaces from within date string and force all
'   text into upper case.
    Date_String = replacesubstr$(UCase$(Dd_Mmm_Yyyy_BCAD)," ","")
    Q = ""
For Pointer = 1 To Len(Date_String)
     Q1 = Mid$(Date_String, Pointer, 1): If Q1 <> " " Then Q = Q + Q1
Next Pointer
     Date_String = Q

' Read the absolute value of the day of the month (1 to 31).
' The value of the day should be the number beginning the date string
' such as "20 MAY 1977" which would return the value 20.
  DD = Val(Q)

' Set (Pointer) to 1st character beyond the (Day) value.  This
' should be the 1st character in the 3 letter month abbreviation
' or simply the 1st 3 letters in the month name and is NOT case
' sensitive.
  Pointer = InStr(1, Q, str$(DD)) + Len(str$(DD))

' Now get the 3 letters of the month abbreviation and then update the (Pointer)
' to aim at the following (Year) value.
  MMM = Mid$(Q, Pointer, 3): Pointer = Pointer + 3
  
' Determine the number of the month corresponding to the three letter
' (Month_Abbreviation).  This abbreviation is simply the first three letters
' in the name of the month in English.  The returned value will range from
' 1=January to 12=December.  Zero is returned if no match is found
' for the abbreviation.  This test is NOT case sensitive.
  Mm = Int(1 + ((InStr(1, "JANFEBMARAPRMAYJUNJULAUGSEPOCTNOVDEC", MMM) - 1) / 3))

' Read the value of the year (assumed positive 1 to 9999).
  YYYY = Val(Mid$(Q, Pointer, Len(Q)))
  
'  Check for BC or AD - If NOT a BC year, then assume AD.
If InStr(Q, "BC") <> 0 Then 
    BCAD = "BC" 
Else 
    BCAD = "AD"
end if
If BCAD = "BC" Then YYYY = (1 - YYYY)

' At this point the separate numerical date elements should be collected
' and ready to be used for any subsequent calendar computations. They are:
' (DD: 1 to 31)  (MM: 1 to 12)  (YYYY: 1 to 9999 BC|AD)  (Cal_Mode: J|G)
' --------------------------------------------------------------------------
'
'     Now compute (JD) number according to the old Julian calendar.
  Q2 = Int((14 - Mm) / 12)
 JD = DD + Int(367 * (Mm + (Q2 * 12) - 2) / 12) + Int(1461 * (YYYY + 4800 - Q2) / 4) - 32113

'  THIS IS A PATCH TO AUTOMATICALLY SWITCH INTO JULIAN CALENDAR
'  MODE IF DATE IS PRIOR TO 15 OCT 1582 (JD = 2299161).  THIS
'  REPLACES THE OLD EXTERNAL CalMode SETTING.
If JD < 2299161 Then 
    Cal_Mode = "J" 
Else 
    Cal_Mode = "G"
end if

'  Apply Julian (JD) correction to convert to (JD) according
'  to the Gregorian calendar if indicated by (Cal_Mode).
If Cal_Mode = "G" Then JD = JD - (Int(3 * Int((YYYY + 100 - Q2) / 100) / 4) - 2)
    
'  Return the final JD value for output as astronomical JD
'  for 0h on date.

   result = JD - 0.5
  
End Function

Function IS_LEAP_YEAR(Year as string)
' Determine if given year is a leap year an return
' boolean "True" if leap year and "False" if not leap.
'
' Year is in standard BC|AD format such as "321 BC"  or "1776 AD"

  defdbl JD1, JD2
   
' If 29 FEB has a different JD# than 1 MAR, then it is a leap year.
  JD1 = JD_NUM_FOR("29 FEB " + replacesubstr$(Year," ",""))
  JD2 = JD_NUM_FOR(" 1 MAR " + replacesubstr$(Year," ",""))
   
If (JD1 <> JD2) Then 
    result = 1 
Else 
    result = 0
end if

End Function

Function DAYS_IN_MONTH_OF(Month_Year_BCAD as string)
' Return number of days in month of given year.  Accounts
' for leap years.
' Month and year is input in format such as: "JUL 1684 BC|AD"
'
' DEPENDENCY: MONTH_NUM_FOR()

  defstr Q, M, Y ' Leap
  defint Days

  Q = replacesubstr$(Month_Year_BCAD," ","")

  M = MONTH_NUM_FOR_ABBREV(Left$(Q, 3))
  
  Y = replacesubstr$(Mid$(Q, 4, 16)," ","")
  
  Days = Mid$("312831303130313130313031", 2 * M - 1, 2)
  
  If (IS_LEAP_YEAR(Y) = 1 And M = 2) Then Days = 29
  
  result = val(Days)
  
End Function

Function MONTH_NUM_FOR_ABBREV(Month_Abbrev as string)
' Return number of month corresponding to given 3 letter
' month abbreviation. (NOT case sensitive).
' If input argument is invalid, then 0 (zero) is returned.

defstr Q, Abbrevs
defint Pointer

  Abbrevs = "JANFEBMARAPRMAYJUNJULAUGSEPOCTNOVDEC"

  Q = Left$(UCase$(replacesubstr$(Month_Abbrev," ","")), 3)

' 0 (zero) returned if less than 3 characters
  If Len(Q) <> 3 Then 
    result = 0
    Exit Function
  end if
  
' Search for abbreviation match
  Pointer = InStr(1, Abbrevs, Q)
  
' 0 (zero) returned if no match found
  If Pointer = 0 Then 
    result = 0
    Exit Function
  end if

' Otherwise:
' Return month number corresponding to valid abbreviation
  result = 1 + Int((Pointer - 1) / 3)

End Function
