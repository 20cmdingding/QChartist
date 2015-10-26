' -------------------------------------------------------------------
' Rapidq side RunTime Linker Code                 Nov 2006,  Jacques
' -------------------------------------------------------------------
' Common Part
' -----------
Declare Function RTL_lstrlen Lib "kernel32" Alias "lstrlenA" (lpString As Long) As Long
'
DefInt ptrNameAddress = Val(Environ$("ptrNameAddress"))
DefInt lenNameAddress = Val(Environ$("lenNameAddress"))
'
DefStr sNameAddress = Space$(lenNameAddress)
memcpy (VarPtr(sNameAddress), ptrNameAddress, lenNameAddress)
'
Function GetFuncPtr (sName As String) As Long
    DefInt i0, i1, i2
    DefStr sPtr
    i0 = Instr (sNameAddress, ";" & sName & ",")
    If i0 = 0 Then Result = 0:Exit Function
    i1 = Instr(i0, sNameAddress, ",")
    i2 = Instr(i1, sNameAddress, ";")
    sPtr = Mid$(sNameAddress, i1 + 1, i2 - i1 - 1)
    Result = Val(sPtr)
End Function
' --------------------------------------------------------------------
' User Code Part
' --------------
' ------------------------------------------------
' // ''RQEXPORT function filegetline (integerlinenb,stringfilename)
Declare Function cwp_filegetline Lib "user32" Alias "CallWindowProcA" _
                   (ptrfilegetline As Long, integerlinenb As Long, stringfilename As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrfilegetline = GetFuncPtr ("filegetline")
Function filegetline(integerlinenb, stringfilename) As Long
    DefInt iRet = cwp_filegetline(ptrfilegetline, integerlinenb, stringfilename, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function filegetlinecount (stringfilename)
Declare Function cwp_filegetlinecount Lib "user32" Alias "CallWindowProcA" _
                   (ptrfilegetlinecount As Long, stringfilename As Long, Arg2 As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrfilegetlinecount = GetFuncPtr ("filegetlinecount")
Function filegetlinecount(stringfilename) As Long
    DefInt iRet = cwp_filegetlinecount(ptrfilegetlinecount, stringfilename, 0, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function filegetalllines (stringfilename,strreinit)
Declare Function cwp_filegetalllines Lib "user32" Alias "CallWindowProcA" _
                   (ptrfilegetalllines As Long, stringfilename As Long, strreinit As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrfilegetalllines = GetFuncPtr ("filegetalllines")
Function filegetalllines(stringfilename, strreinit) As Long
    DefInt iRet = cwp_filegetalllines(ptrfilegetalllines, stringfilename, strreinit, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function filegetlinesarray (stringfilename)
Declare Function cwp_filegetlinesarray Lib "user32" Alias "CallWindowProcA" _
                   (ptrfilegetlinesarray As Long, stringfilename As Long, Arg2 As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrfilegetlinesarray = GetFuncPtr ("filegetlinesarray")
Function filegetlinesarray(stringfilename) As Long
    DefInt iRet = cwp_filegetlinesarray(ptrfilegetlinesarray, stringfilename, 0, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function delfile (stringfilename)
Declare Function cwp_delfile Lib "user32" Alias "CallWindowProcA" _
                   (ptrdelfile As Long, stringfilename As Long, Arg2 As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrdelfile = GetFuncPtr ("delfile")
Function delfile(stringfilename) As Long
    DefInt iRet = cwp_delfile(ptrdelfile, stringfilename, 0, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function useindifunc (cntbarseditstr)
Declare Function cwp_useindifunc Lib "user32" Alias "CallWindowProcA" _
                   (ptruseindifunc As Long, cntbarseditstr As Long, Arg2 As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptruseindifunc = GetFuncPtr ("useindifunc")
Function useindifunc(cntbarseditstr) As Long
    DefInt iRet = cwp_useindifunc(ptruseindifunc, cntbarseditstr, 0, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function displayedfileminusone()
Declare Function cwp_displayedfileminusone Lib "user32" Alias "CallWindowProcA" _
                   (ptrdisplayedfileminusone As Long, Arg1 As Long, Arg2 As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrdisplayedfileminusone = GetFuncPtr ("displayedfileminusone")
Function displayedfileminusone() As Long
    DefInt iRet = cwp_displayedfileminusone(ptrdisplayedfileminusone, 0, 0, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function openedfilesnbminusone()
Declare Function cwp_openedfilesnbminusone Lib "user32" Alias "CallWindowProcA" _
                   (ptropenedfilesnbminusone As Long, Arg1 As Long, Arg2 As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptropenedfilesnbminusone = GetFuncPtr ("openedfilesnbminusone")
Function openedfilesnbminusone() As Long
    DefInt iRet = cwp_openedfilesnbminusone(ptropenedfilesnbminusone, 0, 0, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function displayedfileplusone()
Declare Function cwp_displayedfileplusone Lib "user32" Alias "CallWindowProcA" _
                   (ptrdisplayedfileplusone As Long, Arg1 As Long, Arg2 As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrdisplayedfileplusone = GetFuncPtr ("displayedfileplusone")
Function displayedfileplusone() As Long
    DefInt iRet = cwp_displayedfileplusone(ptrdisplayedfileplusone, 0, 0, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function openedfilesnbplusone()
Declare Function cwp_openedfilesnbplusone Lib "user32" Alias "CallWindowProcA" _
                   (ptropenedfilesnbplusone As Long, Arg1 As Long, Arg2 As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptropenedfilesnbplusone = GetFuncPtr ("openedfilesnbplusone")
Function openedfilesnbplusone() As Long
    DefInt iRet = cwp_openedfilesnbplusone(ptropenedfilesnbplusone, 0, 0, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function setdisplayedfile(displayedfilestr)
Declare Function cwp_setdisplayedfile Lib "user32" Alias "CallWindowProcA" _
                   (ptrsetdisplayedfile As Long, displayedfilestr As Long, Arg2 As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrsetdisplayedfile = GetFuncPtr ("setdisplayedfile")
Function setdisplayedfile(displayedfilestr) As Long
    DefInt iRet = cwp_setdisplayedfile(ptrsetdisplayedfile, displayedfilestr, 0, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function setrowgridoffset(rowgridoffsetstr)
Declare Function cwp_setrowgridoffset Lib "user32" Alias "CallWindowProcA" _
                   (ptrsetrowgridoffset As Long, rowgridoffsetstr As Long, Arg2 As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrsetrowgridoffset = GetFuncPtr ("setrowgridoffset")
Function setrowgridoffset(rowgridoffsetstr) As Long
    DefInt iRet = cwp_setrowgridoffset(ptrsetrowgridoffset, rowgridoffsetstr, 0, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function setchartbars (chartbarsdisplayedfilestr,chartbarsoffsetstr)
Declare Function cwp_setchartbars Lib "user32" Alias "CallWindowProcA" _
                   (ptrsetchartbars As Long, chartbarsdisplayedfilestr As Long, chartbarsoffsetstr As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrsetchartbars = GetFuncPtr ("setchartbars")
Function setchartbars(chartbarsdisplayedfilestr, chartbarsoffsetstr) As Long
    DefInt iRet = cwp_setchartbars(ptrsetchartbars, chartbarsdisplayedfilestr, chartbarsoffsetstr, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function setchartbarstmp (chartbarstmpdisplayedfilestr,chartbarstmpoffsetstr)
Declare Function cwp_setchartbarstmp Lib "user32" Alias "CallWindowProcA" _
                   (ptrsetchartbarstmp As Long, chartbarstmpdisplayedfilestr As Long, chartbarstmpoffsetstr As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrsetchartbarstmp = GetFuncPtr ("setchartbarstmp")
Function setchartbarstmp(chartbarstmpdisplayedfilestr, chartbarstmpoffsetstr) As Long
    DefInt iRet = cwp_setchartbarstmp(ptrsetchartbarstmp, chartbarstmpdisplayedfilestr, chartbarstmpoffsetstr, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function setcharttf (charttfdisplayedfilestr,charttfoffsetstr)
Declare Function cwp_setcharttf Lib "user32" Alias "CallWindowProcA" _
                   (ptrsetcharttf As Long, charttfdisplayedfilestr As Long, charttfoffsetstr As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrsetcharttf = GetFuncPtr ("setcharttf")
Function setcharttf(charttfdisplayedfilestr, charttfoffsetstr) As Long
    DefInt iRet = cwp_setcharttf(ptrsetcharttf, charttfdisplayedfilestr, charttfoffsetstr, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function setbars (barsstr)
Declare Function cwp_setbars Lib "user32" Alias "CallWindowProcA" _
                   (ptrsetbars As Long, barsstr As Long, Arg2 As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrsetbars = GetFuncPtr ("setbars")
Function setbars(barsstr) As Long
    DefInt iRet = cwp_setbars(ptrsetbars, barsstr, 0, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function getbufferdata (buffernamestr,offsetstr)
Declare Function cwp_getbufferdata Lib "user32" Alias "CallWindowProcA" _
                   (ptrgetbufferdata As Long, buffernamestr As Long, offsetstr As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrgetbufferdata = GetFuncPtr ("getbufferdata")
Function getbufferdata(buffernamestr, offsetstr) As Long
    DefInt iRet = cwp_getbufferdata(ptrgetbufferdata, buffernamestr, offsetstr, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function setimportedfile (importedfilestr,importedfileoffsetstr)
Declare Function cwp_setimportedfile Lib "user32" Alias "CallWindowProcA" _
                   (ptrsetimportedfile As Long, importedfilestr As Long, importedfileoffsetstr As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrsetimportedfile = GetFuncPtr ("setimportedfile")
Function setimportedfile(importedfilestr, importedfileoffsetstr) As Long
    DefInt iRet = cwp_setimportedfile(ptrsetimportedfile, importedfilestr, importedfileoffsetstr, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function shiftgridsonebackward()
Declare Function cwp_shiftgridsonebackward Lib "user32" Alias "CallWindowProcA" _
                   (ptrshiftgridsonebackward As Long, Arg1 As Long, Arg2 As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrshiftgridsonebackward = GetFuncPtr ("shiftgridsonebackward")
Function shiftgridsonebackward() As Long
    DefInt iRet = cwp_shiftgridsonebackward(ptrshiftgridsonebackward, 0, 0, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function reversebarscomputesubbcpp(graphbarnboncurstaticstr)
Declare Function cwp_reversebarscomputesubbcpp Lib "user32" Alias "CallWindowProcA" _
                   (ptrreversebarscomputesubbcpp As Long, graphbarnboncurstaticstr As Long, Arg2 As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrreversebarscomputesubbcpp = GetFuncPtr ("reversebarscomputesubbcpp")
Function reversebarscomputesubbcpp(graphbarnboncurstaticstr) As Long
    DefInt iRet = cwp_reversebarscomputesubbcpp(ptrreversebarscomputesubbcpp, graphbarnboncurstaticstr, 0, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function refreshgridscpp()
Declare Function cwp_refreshgridscpp Lib "user32" Alias "CallWindowProcA" _
                   (ptrrefreshgridscpp As Long, Arg1 As Long, Arg2 As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrrefreshgridscpp = GetFuncPtr ("refreshgridscpp")
Function refreshgridscpp() As Long
    DefInt iRet = cwp_refreshgridscpp(ptrrefreshgridscpp, 0, 0, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function getdatagrid (rowgridoffsetstr,offsetstr)
Declare Function cwp_getdatagrid Lib "user32" Alias "CallWindowProcA" _
                   (ptrgetdatagrid As Long, rowgridoffsetstr As Long, offsetstr As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrgetdatagrid = GetFuncPtr ("getdatagrid")
Function getdatagrid(rowgridoffsetstr, offsetstr) As Long
    DefInt iRet = cwp_getdatagrid(ptrgetdatagrid, rowgridoffsetstr, offsetstr, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function setdatagrid (rowgridoffsetstr,offsetstr,datavalstr)
Declare Function cwp_setdatagrid Lib "user32" Alias "CallWindowProcA" _
                   (ptrsetdatagrid As Long, rowgridoffsetstr As Long, offsetstr As Long, datavalstr As Long, Arg4 As Long) As Long
DefInt ptrsetdatagrid = GetFuncPtr ("setdatagrid")
Function setdatagrid(rowgridoffsetstr, offsetstr, datavalstr) As Long
    DefInt iRet = cwp_setdatagrid(ptrsetdatagrid, rowgridoffsetstr, offsetstr, datavalstr, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function getchartbars (chartnbstr)
Declare Function cwp_getchartbars Lib "user32" Alias "CallWindowProcA" _
                   (ptrgetchartbars As Long, chartnbstr As Long, Arg2 As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrgetchartbars = GetFuncPtr ("getchartbars")
Function getchartbars(chartnbstr) As Long
    DefInt iRet = cwp_getchartbars(ptrgetchartbars, chartnbstr, 0, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function getchartbarstmp (chartnbtmpstr)
Declare Function cwp_getchartbarstmp Lib "user32" Alias "CallWindowProcA" _
                   (ptrgetchartbarstmp As Long, chartnbtmpstr As Long, Arg2 As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrgetchartbarstmp = GetFuncPtr ("getchartbarstmp")
Function getchartbarstmp(chartnbtmpstr) As Long
    DefInt iRet = cwp_getchartbarstmp(ptrgetchartbarstmp, chartnbtmpstr, 0, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function tfmultok_clickcpp(tfmultstr)
Declare Function cwp_tfmultok_clickcpp Lib "user32" Alias "CallWindowProcA" _
                   (ptrtfmultok_clickcpp As Long, tfmultstr As Long, Arg2 As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrtfmultok_clickcpp = GetFuncPtr ("tfmultok_clickcpp")
Function tfmultok_clickcpp(tfmultstr) As Long
    DefInt iRet = cwp_tfmultok_clickcpp(ptrtfmultok_clickcpp, tfmultstr, 0, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function savegridtmpcpp()
Declare Function cwp_savegridtmpcpp Lib "user32" Alias "CallWindowProcA" _
                   (ptrsavegridtmpcpp As Long, Arg1 As Long, Arg2 As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrsavegridtmpcpp = GetFuncPtr ("savegridtmpcpp")
Function savegridtmpcpp() As Long
    DefInt iRet = cwp_savegridtmpcpp(ptrsavegridtmpcpp, 0, 0, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function writetfcpp (tftowritestr)
Declare Function cwp_writetfcpp Lib "user32" Alias "CallWindowProcA" _
                   (ptrwritetfcpp As Long, tftowritestr As Long, Arg2 As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrwritetfcpp = GetFuncPtr ("writetfcpp")
Function writetfcpp(tftowritestr) As Long
    DefInt iRet = cwp_writetfcpp(ptrwritetfcpp, tftowritestr, 0, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function playsoundcpp (sndfreqstr,snddurstr)
Declare Function cwp_playsoundcpp Lib "user32" Alias "CallWindowProcA" _
                   (ptrplaysoundcpp As Long, sndfreqstr As Long, snddurstr As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrplaysoundcpp = GetFuncPtr ("playsoundcpp")
Function playsoundcpp(sndfreqstr, snddurstr) As Long
    DefInt iRet = cwp_playsoundcpp(ptrplaysoundcpp, sndfreqstr, snddurstr, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function timecpp (barstr)
Declare Function cwp_timecpp Lib "user32" Alias "CallWindowProcA" _
                   (ptrtimecpp As Long, barstr As Long, Arg2 As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrtimecpp = GetFuncPtr ("timecpp")
Function timecpp(barstr) As Long
    DefInt iRet = cwp_timecpp(ptrtimecpp, barstr, 0, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function swe_julday(parameters)
Declare Function cwp_swe_julday Lib "user32" Alias "CallWindowProcA" _
                   (ptrswe_julday As Long, parameters As Long, Arg2 As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrswe_julday = GetFuncPtr ("swe_julday")
Function swe_julday(parameters) As Long
    DefInt iRet = cwp_swe_julday(ptrswe_julday, parameters, 0, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function swe_date_conversion(parameters)
Declare Function cwp_swe_date_conversion Lib "user32" Alias "CallWindowProcA" _
                   (ptrswe_date_conversion As Long, parameters As Long, Arg2 As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrswe_date_conversion = GetFuncPtr ("swe_date_conversion")
Function swe_date_conversion(parameters) As Long
    DefInt iRet = cwp_swe_date_conversion(ptrswe_date_conversion, parameters, 0, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function swe_deltat(parameters)
Declare Function cwp_swe_deltat Lib "user32" Alias "CallWindowProcA" _
                   (ptrswe_deltat As Long, parameters As Long, Arg2 As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrswe_deltat = GetFuncPtr ("swe_deltat")
Function swe_deltat(parameters) As Long
    DefInt iRet = cwp_swe_deltat(ptrswe_deltat, parameters, 0, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function swe_calc(parameters,x,serr)
Declare Function cwp_swe_calc Lib "user32" Alias "CallWindowProcA" _
                   (ptrswe_calc As Long, parameters As Long, x As Long, serr As Long, Arg4 As Long) As Long
DefInt ptrswe_calc = GetFuncPtr ("swe_calc")
Function swe_calc(parameters, x, serr) As Long
    DefInt iRet = cwp_swe_calc(ptrswe_calc, parameters, x, serr, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function swe_get_planet_name(parameters,plnam)
Declare Function cwp_swe_get_planet_name Lib "user32" Alias "CallWindowProcA" _
                   (ptrswe_get_planet_name As Long, parameters As Long, plnam As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrswe_get_planet_name = GetFuncPtr ("swe_get_planet_name")
Function swe_get_planet_name(parameters, plnam) As Long
    DefInt iRet = cwp_swe_get_planet_name(ptrswe_get_planet_name, parameters, plnam, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function unix_time_to_date(unix_time)
Declare Function cwp_unix_time_to_date Lib "user32" Alias "CallWindowProcA" _
                   (ptrunix_time_to_date As Long, unix_time As Long, Arg2 As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrunix_time_to_date = GetFuncPtr ("unix_time_to_date")
Function unix_time_to_date(unix_time) As Long
    DefInt iRet = cwp_unix_time_to_date(ptrunix_time_to_date, unix_time, 0, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function date_to_unix_time(parameters)
Declare Function cwp_date_to_unix_time Lib "user32" Alias "CallWindowProcA" _
                   (ptrdate_to_unix_time As Long, parameters As Long, Arg2 As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrdate_to_unix_time = GetFuncPtr ("date_to_unix_time")
Function date_to_unix_time(parameters) As Long
    DefInt iRet = cwp_date_to_unix_time(ptrdate_to_unix_time, parameters, 0, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function swe_sidtime(parameters)
Declare Function cwp_swe_sidtime Lib "user32" Alias "CallWindowProcA" _
                   (ptrswe_sidtime As Long, parameters As Long, Arg2 As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrswe_sidtime = GetFuncPtr ("swe_sidtime")
Function swe_sidtime(parameters) As Long
    DefInt iRet = cwp_swe_sidtime(ptrswe_sidtime, parameters, 0, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function swe_house_pos(parameters,xpin,serr)
Declare Function cwp_swe_house_pos Lib "user32" Alias "CallWindowProcA" _
                   (ptrswe_house_pos As Long, parameters As Long, xpin As Long, serr As Long, Arg4 As Long) As Long
DefInt ptrswe_house_pos = GetFuncPtr ("swe_house_pos")
Function swe_house_pos(parameters, xpin, serr) As Long
    DefInt iRet = cwp_swe_house_pos(ptrswe_house_pos, parameters, xpin, serr, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function swe_houses(parameters,hcusps,ascmc)
Declare Function cwp_swe_houses Lib "user32" Alias "CallWindowProcA" _
                   (ptrswe_houses As Long, parameters As Long, hcusps As Long, ascmc As Long, Arg4 As Long) As Long
DefInt ptrswe_houses = GetFuncPtr ("swe_houses")
Function swe_houses(parameters, hcusps, ascmc) As Long
    DefInt iRet = cwp_swe_houses(ptrswe_houses, parameters, hcusps, ascmc, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function swe_houses_ex(parameters,hcusps,ascmc)
Declare Function cwp_swe_houses_ex Lib "user32" Alias "CallWindowProcA" _
                   (ptrswe_houses_ex As Long, parameters As Long, hcusps As Long, ascmc As Long, Arg4 As Long) As Long
DefInt ptrswe_houses_ex = GetFuncPtr ("swe_houses_ex")
Function swe_houses_ex(parameters, hcusps, ascmc) As Long
    DefInt iRet = cwp_swe_houses_ex(ptrswe_houses_ex, parameters, hcusps, ascmc, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function timebcpp(bar)
Declare Function cwp_timebcpp Lib "user32" Alias "CallWindowProcA" _
                   (ptrtimebcpp As Long, bar As Long, Arg2 As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrtimebcpp = GetFuncPtr ("timebcpp")
Function timebcpp(bar) As Long
    DefInt iRet = cwp_timebcpp(ptrtimebcpp, bar, 0, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function calculate_seconds_since_1_1_1970_cpp(parameters)
Declare Function cwp_calculate_seconds_since_1_1_1970_cpp Lib "user32" Alias "CallWindowProcA" _
                   (ptrcalculate_seconds_since_1_1_1970_cpp As Long, parameters As Long, Arg2 As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrcalculate_seconds_since_1_1_1970_cpp = GetFuncPtr ("calculate_seconds_since_1_1_1970_cpp")
Function calculate_seconds_since_1_1_1970_cpp(parameters) As Long
    DefInt iRet = cwp_calculate_seconds_since_1_1_1970_cpp(ptrcalculate_seconds_since_1_1_1970_cpp, parameters, 0, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function bandscpp(periodstr)
Declare Function cwp_bandscpp Lib "user32" Alias "CallWindowProcA" _
                   (ptrbandscpp As Long, periodstr As Long, Arg2 As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrbandscpp = GetFuncPtr ("bandscpp")
Function bandscpp(periodstr) As Long
    DefInt iRet = cwp_bandscpp(ptrbandscpp, periodstr, 0, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function bbhlcpp(periodstr,barsbackstr)
Declare Function cwp_bbhlcpp Lib "user32" Alias "CallWindowProcA" _
                   (ptrbbhlcpp As Long, periodstr As Long, barsbackstr As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrbbhlcpp = GetFuncPtr ("bbhlcpp")
Function bbhlcpp(periodstr, barsbackstr) As Long
    DefInt iRet = cwp_bbhlcpp(ptrbbhlcpp, periodstr, barsbackstr, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function zigzagcpp(barsbackstr,extdepthstr)
Declare Function cwp_zigzagcpp Lib "user32" Alias "CallWindowProcA" _
                   (ptrzigzagcpp As Long, barsbackstr As Long, extdepthstr As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrzigzagcpp = GetFuncPtr ("zigzagcpp")
Function zigzagcpp(barsbackstr, extdepthstr) As Long
    DefInt iRet = cwp_zigzagcpp(ptrzigzagcpp, barsbackstr, extdepthstr, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function RSTL(periodstr)
Declare Function cwp_RSTL Lib "user32" Alias "CallWindowProcA" _
                   (ptrRSTL As Long, periodstr As Long, Arg2 As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrRSTL = GetFuncPtr ("RSTL")
Function RSTL(periodstr) As Long
    DefInt iRet = cwp_RSTL(ptrRSTL, periodstr, 0, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function cogcpp(barsbackstr)
Declare Function cwp_cogcpp Lib "user32" Alias "CallWindowProcA" _
                   (ptrcogcpp As Long, barsbackstr As Long, Arg2 As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrcogcpp = GetFuncPtr ("cogcpp")
Function cogcpp(barsbackstr) As Long
    DefInt iRet = cwp_cogcpp(ptrcogcpp, barsbackstr, 0, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function ADR112cpp(periodstr,tfbasestr)
Declare Function cwp_ADR112cpp Lib "user32" Alias "CallWindowProcA" _
                   (ptrADR112cpp As Long, periodstr As Long, tfbasestr As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrADR112cpp = GetFuncPtr ("ADR112cpp")
Function ADR112cpp(periodstr, tfbasestr) As Long
    DefInt iRet = cwp_ADR112cpp(ptrADR112cpp, periodstr, tfbasestr, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function initwaterlevelcpp(curtfstr)
Declare Function cwp_initwaterlevelcpp Lib "user32" Alias "CallWindowProcA" _
                   (ptrinitwaterlevelcpp As Long, curtfstr As Long, Arg2 As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrinitwaterlevelcpp = GetFuncPtr ("initwaterlevelcpp")
Function initwaterlevelcpp(curtfstr) As Long
    DefInt iRet = cwp_initwaterlevelcpp(ptrinitwaterlevelcpp, curtfstr, 0, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function waterlevelcpp(periodstr,curtfstr)
Declare Function cwp_waterlevelcpp Lib "user32" Alias "CallWindowProcA" _
                   (ptrwaterlevelcpp As Long, periodstr As Long, curtfstr As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrwaterlevelcpp = GetFuncPtr ("waterlevelcpp")
Function waterlevelcpp(periodstr, curtfstr) As Long
    DefInt iRet = cwp_waterlevelcpp(ptrwaterlevelcpp, periodstr, curtfstr, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function dinfibohighcpp(curtfstr)
Declare Function cwp_dinfibohighcpp Lib "user32" Alias "CallWindowProcA" _
                   (ptrdinfibohighcpp As Long, curtfstr As Long, Arg2 As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrdinfibohighcpp = GetFuncPtr ("dinfibohighcpp")
Function dinfibohighcpp(curtfstr) As Long
    DefInt iRet = cwp_dinfibohighcpp(ptrdinfibohighcpp, curtfstr, 0, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function weeklypivotcpp(barsbackstr)
Declare Function cwp_weeklypivotcpp Lib "user32" Alias "CallWindowProcA" _
                   (ptrweeklypivotcpp As Long, barsbackstr As Long, Arg2 As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrweeklypivotcpp = GetFuncPtr ("weeklypivotcpp")
Function weeklypivotcpp(barsbackstr) As Long
    DefInt iRet = cwp_weeklypivotcpp(ptrweeklypivotcpp, barsbackstr, 0, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function rstlcogcpp(barsbackstr,kstdstr)
Declare Function cwp_rstlcogcpp Lib "user32" Alias "CallWindowProcA" _
                   (ptrrstlcogcpp As Long, barsbackstr As Long, kstdstr As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrrstlcogcpp = GetFuncPtr ("rstlcogcpp")
Function rstlcogcpp(barsbackstr, kstdstr) As Long
    DefInt iRet = cwp_rstlcogcpp(ptrrstlcogcpp, barsbackstr, kstdstr, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function Levels(periodstr)
Declare Function cwp_Levels Lib "user32" Alias "CallWindowProcA" _
                   (ptrLevels As Long, periodstr As Long, Arg2 As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrLevels = GetFuncPtr ("Levels")
Function Levels(periodstr) As Long
    DefInt iRet = cwp_Levels(ptrLevels, periodstr, 0, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function bowels(periodstr,tfbasestr)
Declare Function cwp_bowels Lib "user32" Alias "CallWindowProcA" _
                   (ptrbowels As Long, periodstr As Long, tfbasestr As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrbowels = GetFuncPtr ("bowels")
Function bowels(periodstr, tfbasestr) As Long
    DefInt iRet = cwp_bowels(ptrbowels, periodstr, tfbasestr, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function smFisherTransform3nr(periodstr,curtfstr)
Declare Function cwp_smFisherTransform3nr Lib "user32" Alias "CallWindowProcA" _
                   (ptrsmFisherTransform3nr As Long, periodstr As Long, curtfstr As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrsmFisherTransform3nr = GetFuncPtr ("smFisherTransform3nr")
Function smFisherTransform3nr(periodstr, curtfstr) As Long
    DefInt iRet = cwp_smFisherTransform3nr(ptrsmFisherTransform3nr, periodstr, curtfstr, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function VolatilityStop(periodstr)
Declare Function cwp_VolatilityStop Lib "user32" Alias "CallWindowProcA" _
                   (ptrVolatilityStop As Long, periodstr As Long, Arg2 As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrVolatilityStop = GetFuncPtr ("VolatilityStop")
Function VolatilityStop(periodstr) As Long
    DefInt iRet = cwp_VolatilityStop(ptrVolatilityStop, periodstr, 0, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function Ehlersfishertransform(periodstr,curtfstr)
Declare Function cwp_Ehlersfishertransform Lib "user32" Alias "CallWindowProcA" _
                   (ptrEhlersfishertransform As Long, periodstr As Long, curtfstr As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrEhlersfishertransform = GetFuncPtr ("Ehlersfishertransform")
Function Ehlersfishertransform(periodstr, curtfstr) As Long
    DefInt iRet = cwp_Ehlersfishertransform(ptrEhlersfishertransform, periodstr, curtfstr, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function MA_Chanels_FiboEnv_Mid(periodstr,curtfstr)
Declare Function cwp_MA_Chanels_FiboEnv_Mid Lib "user32" Alias "CallWindowProcA" _
                   (ptrMA_Chanels_FiboEnv_Mid As Long, periodstr As Long, curtfstr As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrMA_Chanels_FiboEnv_Mid = GetFuncPtr ("MA_Chanels_FiboEnv_Mid")
Function MA_Chanels_FiboEnv_Mid(periodstr, curtfstr) As Long
    DefInt iRet = cwp_MA_Chanels_FiboEnv_Mid(ptrMA_Chanels_FiboEnv_Mid, periodstr, curtfstr, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function threeD_Oscilator(periodstr,curtfstr)
Declare Function cwp_threeD_Oscilator Lib "user32" Alias "CallWindowProcA" _
                   (ptrthreeD_Oscilator As Long, periodstr As Long, curtfstr As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrthreeD_Oscilator = GetFuncPtr ("threeD_Oscilator")
Function threeD_Oscilator(periodstr, curtfstr) As Long
    DefInt iRet = cwp_threeD_Oscilator(ptrthreeD_Oscilator, periodstr, curtfstr, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function stepftvcprdl(periodstr)
Declare Function cwp_stepftvcprdl Lib "user32" Alias "CallWindowProcA" _
                   (ptrstepftvcprdl As Long, periodstr As Long, Arg2 As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrstepftvcprdl = GetFuncPtr ("stepftvcprdl")
Function stepftvcprdl(periodstr) As Long
    DefInt iRet = cwp_stepftvcprdl(ptrstepftvcprdl, periodstr, 0, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function spectrometer(periodstr,curtfstr)
Declare Function cwp_spectrometer Lib "user32" Alias "CallWindowProcA" _
                   (ptrspectrometer As Long, periodstr As Long, curtfstr As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrspectrometer = GetFuncPtr ("spectrometer")
Function spectrometer(periodstr, curtfstr) As Long
    DefInt iRet = cwp_spectrometer(ptrspectrometer, periodstr, curtfstr, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function balance_point_fibo(curtfstr)
Declare Function cwp_balance_point_fibo Lib "user32" Alias "CallWindowProcA" _
                   (ptrbalance_point_fibo As Long, curtfstr As Long, Arg2 As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrbalance_point_fibo = GetFuncPtr ("balance_point_fibo")
Function balance_point_fibo(curtfstr) As Long
    DefInt iRet = cwp_balance_point_fibo(ptrbalance_point_fibo, curtfstr, 0, 0, 0)
    Result = iRet
End Function
' ------------------------------------------------
' // ''RQEXPORT function Murrey_Math(barsbackstr)
Declare Function cwp_Murrey_Math Lib "user32" Alias "CallWindowProcA" _
                   (ptrMurrey_Math As Long, barsbackstr As Long, Arg2 As Long, Arg3 As Long, Arg4 As Long) As Long
DefInt ptrMurrey_Math = GetFuncPtr ("Murrey_Math")
Function Murrey_Math(barsbackstr) As Long
    DefInt iRet = cwp_Murrey_Math(ptrMurrey_Math, barsbackstr, 0, 0, 0)
    Result = iRet
End Function
' --------------------------------------------------------------------
