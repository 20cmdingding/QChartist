// ''RQEXPORT function filegetline (integerlinenb,stringfilename)
// ''RQEXPORT function filegetlinecount (stringfilename)
// ''RQEXPORT function filegetalllines (stringfilename,strreinit)
// ''RQEXPORT function filegetlinesarray (stringfilename)
// ''RQEXPORT function delfile (stringfilename)
// ''RQEXPORT function useindifunc (cntbarseditstr)
// ''RQEXPORT function displayedfileminusone()
// ''RQEXPORT function openedfilesnbminusone()
// ''RQEXPORT function displayedfileplusone()
// ''RQEXPORT function openedfilesnbplusone()
// ''RQEXPORT function setdisplayedfile(displayedfilestr)
// ''RQEXPORT function setnumbars(numbarsstr)
// ''RQEXPORT function setnumbars_first(numbars_firststr)
// ''RQEXPORT function setnumbars_last(numbars_laststr)
// ''RQEXPORT function setrowgridoffset(rowgridoffsetstr)
// ''RQEXPORT function setchartbars (chartbarsdisplayedfilestr,chartbarsoffsetstr)
// ''RQEXPORT function setchartbarstmp (chartbarstmpdisplayedfilestr,chartbarstmpoffsetstr)
// ''RQEXPORT function setcharttf (charttfdisplayedfilestr,charttfoffsetstr)
// ''RQEXPORT function setbars (barsstr)
// ''RQEXPORT function setcntbarsedit (barsstr)
// ''RQEXPORT function getbufferdata (buffernamestr,offsetstr)
// ''RQEXPORT function setimportedfile (importedfilestr,importedfileoffsetstr)
// ''RQEXPORT function shiftgridsonebackward()
// ''RQEXPORT function reversebarscomputesubbcpp(graphbarnboncurstaticstr)
// ''RQEXPORT function refreshgridscpp()
// ''RQEXPORT function getdatagrid (rowgridoffsetstr,offsetstr)
// ''RQEXPORT function setdatagrid (rowgridoffsetstr,offsetstr,datavalstr)
// ''RQEXPORT function getchartbars (chartnbstr)
// ''RQEXPORT function getchartbarstmp (chartnbtmpstr)
// ''RQEXPORT function tfmultok_clickcpp(tfmultstr)
// ''RQEXPORT function savegridtmpcpp()
// ''RQEXPORT function writetfcpp (tftowritestr)
// ''RQEXPORT function playsoundcpp (sndfreqstr,snddurstr)
// ''RQEXPORT function timecpp (barstr)
// ''RQEXPORT function swe_julday(parameters)
// ''RQEXPORT function swe_date_conversion(parameters)
// ''RQEXPORT function swe_deltat(parameters)
// ''RQEXPORT function swe_calc(parameters,x,serr)
// ''RQEXPORT function swe_get_planet_name(parameters,plnam)
// ''RQEXPORT function unix_time_to_date(unix_time)
// ''RQEXPORT function date_to_unix_time(parameters)
// ''RQEXPORT function swe_sidtime(parameters)
// ''RQEXPORT function swe_house_pos(parameters,xpin,serr)
// ''RQEXPORT function swe_houses(parameters,hcusps,ascmc)
// ''RQEXPORT function swe_houses_ex(parameters,hcusps,ascmc)
// ''RQEXPORT function swe_set_topo_and_swe_calc(parameters,x,serr)
// ''RQEXPORT function timebcpp(bar)
// ''RQEXPORT function calculate_seconds_since_1_1_1970_cpp(parameters)
// ''RQEXPORT function current_time()
// ''RQEXPORT function Scilab_test()
// ''RQEXPORT function conic_section(parameters,x,y)
// ''RQEXPORT function getdayofyear (year,month,day)

#include "includes\QChartist.cpp"
#include "includes\swedll32.cpp"
#include "includes\scilab.cpp"

// ''RQEXPORT function bandscpp(periodstr)
#include "indicators\bandscpp.cpp"


// ''RQEXPORT function bbhlcpp(periodstr,barsbackstr)
#include "indicators\bbhlcpp.cpp"


// ''RQEXPORT function zigzagcpp(barsbackstr,extdepthstr)
#include "indicators\zigzagcpp.cpp"


// ''RQEXPORT function RSTL(periodstr)
#include "indicators\RSTL.cpp"


// ''RQEXPORT function cogcpp(barsbackstr)
#include "indicators\cogcpp.cpp"


// ''RQEXPORT function ADR112cpp(periodstr,tfbasestr)
#include "indicators\ADR112cpp.cpp"


// ''RQEXPORT function initwaterlevelcpp(curtfstr)
// ''RQEXPORT function waterlevelcpp(periodstr,curtfstr)
#include "indicators\waterlevelcpp.cpp"


// ''RQEXPORT function dinfibohighcpp(curtfstr)
#include "indicators\Din_fibo_high.cpp"


// ''RQEXPORT function weeklypivotcpp(barsbackstr)
#include "indicators\weeklypivotcpp.cpp"


// ''RQEXPORT function rstlcogcpp(barsbackstr,kstdstr)
#include "indicators\COG_of_RSTL.cpp"


// ''RQEXPORT function Levels(periodstr)
#include "indicators\Levels.cpp"


// ''RQEXPORT function bowels(periodstr,tfbasestr)
#include "indicators\bowels.cpp"


// ''RQEXPORT function smFisherTransform3nr(periodstr,curtfstr)
#include "indicators\smFisherTransform3nr.cpp"


// ''RQEXPORT function VolatilityStop(periodstr)
#include "indicators\VolatilityStop.cpp"



// ''RQEXPORT function Ehlersfishertransform(periodstr,curtfstr)
#include "indicators\Ehlersfishertransform.cpp"


// ''RQEXPORT function MA_Chanels_FiboEnv_Mid(periodstr,curtfstr)
#include "indicators\MA_Chanels_FiboEnv_Mid.cpp"


// ''RQEXPORT function threeD_Oscilator(periodstr,curtfstr)
#include "indicators\threeD_Oscilator.cpp"


// ''RQEXPORT function stepftvcprdl(periodstr)
#include "indicators\stepftvcprdl.cpp"


// ''RQEXPORT function spectrometer(periodstr,curtfstr)
#include "indicators\spectrometer.cpp"


// ''RQEXPORT function balance_point_fibo(curtfstr)
#include "indicators\balance_point_fibo.cpp"



// ''RQEXPORT function Murrey_Math(barsbackstr)
#include "indicators\Murrey_Math.cpp"


// ''RQEXPORT function CoronaSwingPosition(periodstr)
#include "indicators\CoronaSwingPosition.cpp"


// ''RQEXPORT function Ichimoku(periodstr)
#include "indicators\Ichimoku.cpp"


// ''RQEXPORT function Elliot_Wave_3_Level_ZZ_Semafor(periodstr)
#include "indicators\Elliot_Wave_3_Level_ZZ_Semafor.cpp"


// ''RQEXPORT function RBCI(periodstr)
#include "indicators\RBCI.cpp"


// ''RQEXPORT function TSCD(periodstr)
#include "indicators\TSCD.cpp"


// ''RQEXPORT function TMA_CG(periodstr)
#include "indicators\TMA_CG.cpp"


// ''RQEXPORT function realMACD(periodstr)
#include "indicators\realMACD.cpp"


// ''RQEXPORT function Weighted_WCCI(periodstr)
#include "indicators\Weighted_WCCI.cpp"


// ''RQEXPORT function past_regression_deviated(periodstr)
#include "indicators\past_regression_deviated.cpp"

#include "includes\getbufferdata.cpp"
