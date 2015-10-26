const one_day_in_years=0.00273790926

' Period of revolution in years
const mercury_period_of_revolution=0.24093601488
const venus_period_of_revolution=0.615208210722
const earth_period_of_revolution=1
const mars_period_of_revolution=1.88094366162
const jupiter_period_of_revolution=11.86
const saturn_period_of_revolution=29.46
const uranus_period_of_revolution=83.75
const neptune_period_of_revolution=163.72
const pluto_period_of_revolution=247.92

' Rotation period in years
const mercury_rotation_period=0.16153664634
const venus_rotation_period=0.66531195018 ' retrograde
const earth_rotation_period=0.997268518518519
const mars_rotation_period=1.0256944444444444
const jupiter_rotation_period=0.413541666666666622
const saturn_rotation_period=0.444722222222222578
const uranus_rotation_period=0.7 ' Retrograde
const neptune_rotation_period=0.67430555555555589
const pluto_rotation_period=6.3875 ' Retrograde

' Equatorial diameter in kilometers
const mercury_equatorial_diameter=4880
const venus_equatorial_diameter=12100
const earth_equatorial_diameter=12756
const mars_equatorial_diameter=6794
const jupiter_equatorial_diameter=142800
const saturn_equatorial_diameter=120660
const uranus_equatorial_diameter=51810
const neptune_equatorial_diameter=49528
const pluto_equatorial_diameter=2290

' Volume of the planets and the sun in cubic km
const sun_volume=1.409*10^18
const jupiter_volume=1.43128*10^15
const saturn_volume=8.2713*10^14
const uranus_volume=6.833*10^13
const neptune_volume=6.254*10^13
const earth_volume=1.08321*10^12
const venus_volume=9.2843*10^11
const mars_volume=1.6318*10^11
const mercury_volume=6.083*10^10
const moon_volume=2.1958*10^10
const pluto_volume=7.15*10^9

' Mass of the planets and the sun in kg
const sun_mass=1.9891*10^30
const jupiter_mass=1.8986*10^27
const saturn_mass=5.6846*10^26
const neptune_mass=10.243*10^25
const uranus_mass=8.6810*10^25
const earth_mass=5.9736*10^24
const venus_mass=4.8685*10^24
const mars_mass=6.4185*10^23
const mercury_mass=3.3022*10^23
const moon_mass=7.349*10^22
const pluto_mass=1.25*10^22

' Gravitational constant in m^3/kg*s^2
const gravitational_constant=6.6732*10^-11

' Light speed in m/s
const light_speed=2.99792458*10^8

' Acceleration of gravity in m/s^2
const acceleration_of_gravity=9.80665

declare function is_retrograde (d as double, period as integer, Body as integer, iflag as integer) as integer

function is_retrograde (d as double, period as integer, body as integer, iflag as integer) as integer

   defdbl longtitude_past, latitude_past
   defdbl longtitude_now, latitude_now
   defdbl tmp

Dim x(6) As Double
    Dim x2(6) As Double
    Dim cusp(13) As Double
    Dim ascmc(10) As Double
    Dim attr(20) As Double
    Dim tret(20) As Double
    Dim geopos(10) As Double
    Dim geoposx(10) As Double
    Dim xnasc(6) As Double
    Dim xndsc(6) As Double
    Dim xperi(6) As Double
    Dim xaphe(6) As Double
    Dim cal As Byte
    Dim o As orient
    Dim ss As String * 16
    cal = 103  ' g for gregorian calendar
    'defdbl h = phour + pmin / 60
    'olen = LenB(ss)
    defdbl plon=8
    defdbl plat=47
    geopos(0) = plon
    geopos(1) = plat
    geopos(2) = 0

defstr year,month,day,hours,minutes,seconds
defint pday
defint pmonth
defint pyear
defint phour
defint pmin
defdbl h
defdbl ptjd_ut
defdbl ptdj_et
defstr pparameters
defstr iyearstr,imonthstr,idaystr,hstr
defint planet 
defstr serr$ 
defstr plnam$ 
defstr planetstr
defstr iflagstr
defstr x0str
defdbl ret_flag
defstr tjd_utstr
defstr retvalstr
deflng retval
defdbl tjd_et
defstr tjd_etstr
defdbl t2
defstr tjd_ut_formated
defstr tjd_et_formated
defstr ut$

defdbl d_minus_period=d-period
defstr d_minus_periodstr=Format$("%12.0f", d_minus_period)
defstr d_minus_period_datestr=varptr$(unix_time_to_date(varptr(d_minus_periodstr)))
defstr dstr=Format$("%12.0f", d)
defstr d_datestr=varptr$(unix_time_to_date(varptr(dstr)))

year=mid$(d_minus_period_datestr,21,4)
month=strtomonth(mid$(d_minus_period_datestr,5,3))
day=mid$(d_minus_period_datestr,9,2)
hours=mid$(d_minus_period_datestr,12,2)
minutes=mid$(d_minus_period_datestr,15,2)
seconds=mid$(d_minus_period_datestr,18,2)

pday=val(day)
pmonth=val(month)
pyear=val(year)
phour=val(hours)
pmin=val(minutes)
h = phour + pmin / 60


    iyearstr=str$(pyear)
    imonthstr=str$(pmonth)
    idaystr=str$(pday)
    hstr=str$(h)
    pparameters=iyearstr+";"+imonthstr+";"+idaystr+";"+hstr+";1"
    tjd_utstr=varptr$(swe_julday(varptr(pparameters)))
    ptjd_ut=val(tjd_utstr)

    pparameters=iyearstr+";"+imonthstr+";"+idaystr+";"+hstr+";g;"+tjd_utstr
    retvalstr=varptr$(swe_date_conversion(varptr(pparameters)))
    retval = val(retvalstr)

If retval <> 0 Then
        showmessage "Illegal Date"
        Exit Sub
    End If 

'If ephemeris_time.checked=1 Then
     tjd_et = ptjd_ut
     tjd_etstr=str$(tjd_et)
     ptjd_ut = tjd_et - val(varptr$(swe_deltat(varptr(tjd_etstr))))
'    Else    
'     tjd_et = ptjd_ut + val(varptr$(swe_deltat(varptr(tjd_utstr))))
'    End If    
    
    t2 = ptjd_ut - 2415018.5
    If t2 < 0 Then
      t2 = t2
    End If
    
    tjd_ut_formated=Format$("%.8f", ptjd_ut)
    tjd_et_formated=Format$("%.8f", tjd_et)   
    
    
    If ptjd_ut=tjd_et Then
      ut$ = ""
      
    Else
      ut$ = "  UT=" + tjd_ut_formated
    End If    



planet=body

serr$ = String$(255, 0)
        plnam$ = String$(20, 0)
        tjd_etstr=str$(tjd_et)
        planetstr=str$(planet)
        iflagstr=str$(iflag)
        x0str=str$(x(0))
        pparameters=tjd_etstr+";"+planetstr+";"+iflagstr
        ret_flag = val(varptr$(swe_calc(varptr(pparameters),varptr(x(0)),varptr(serr$)))) 

longtitude_past=x(0)  

year=mid$(d_datestr,21,4)
month=strtomonth(mid$(d_datestr,5,3))
day=mid$(d_datestr,9,2)
hours=mid$(d_datestr,12,2)
minutes=mid$(d_datestr,15,2)
seconds=mid$(d_datestr,18,2)

pday=val(day)
pmonth=val(month)
pyear=val(year)
phour=val(hours)
pmin=val(minutes)
h = phour + pmin / 60

    iyearstr=str$(pyear)
    imonthstr=str$(pmonth)
    idaystr=str$(pday)
    hstr=str$(h)
    pparameters=iyearstr+";"+imonthstr+";"+idaystr+";"+hstr+";1"
    tjd_utstr=varptr$(swe_julday(varptr(pparameters)))
    ptjd_ut=val(tjd_utstr)

    pparameters=iyearstr+";"+imonthstr+";"+idaystr+";"+hstr+";g;"+tjd_utstr
    retvalstr=varptr$(swe_date_conversion(varptr(pparameters)))
    retval = val(retvalstr)

If retval <> 0 Then
        showmessage "Illegal Date"
        Exit Sub
    End If 

'If ephemeris_time.checked=1 Then
     tjd_et = ptjd_ut
     tjd_etstr=str$(tjd_et)
     ptjd_ut = tjd_et - val(varptr$(swe_deltat(varptr(tjd_etstr))))
'    Else    
'     tjd_et = ptjd_ut + val(varptr$(swe_deltat(varptr(tjd_utstr))))
'    End If    
    
    t2 = ptjd_ut - 2415018.5
    If t2 < 0 Then
      t2 = t2
    End If
    
    tjd_ut_formated=Format$("%.8f", ptjd_ut)
    tjd_et_formated=Format$("%.8f", tjd_et)   
    
    
    If ptjd_ut=tjd_et Then
      ut$ = ""
      
    Else
      ut$ = "  UT=" + tjd_ut_formated
    End If    



planet=body

serr$ = String$(255, 0)
        plnam$ = String$(20, 0)
        tjd_etstr=str$(tjd_et)
        planetstr=str$(planet)
        iflagstr=str$(iflag)
        x0str=str$(x(0))
        pparameters=tjd_etstr+";"+planetstr+";"+iflagstr
        ret_flag = val(varptr$(swe_calc(varptr(pparameters),varptr(x(0)),varptr(serr$)))) 

longtitude_now=x(0)
   
'   astro_swe_calc(d-period, Body, iflag, longtitude_past, latitude_past, tmp, tmp);
'   astro_swe_calc(d, Body, iflag, longtitude_now, latitude_now, tmp, tmp);
   
   if(longtitude_now < longtitude_past) then   
     result=1   
   else   
     result=0
   end if
end function