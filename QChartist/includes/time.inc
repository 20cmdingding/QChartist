'/*
'   Time library
'   
'   last modified 
'   30.09.2005
'   20.04.2005
'   created 13.04.2005
'
'samples:
'   int period       = get_period_by_str("MN1")
'   int period_value = get_period_value(shift, period)
'   int shift        = goto_one_period_back(int shift, int period)
'   
'   double open, high, low, close;
'   ohlc(0,PERIOD_D1, 1, open, high, low, close);
'   Print("Open is ", DoubleToStr(open, Digits()), " High is ", DoubleToStr(high,Digits())," Low is ", DoubleToStr(low,Digits()), " Close is ", DoubleToStr(close,Digits()) );
'   
'*/

declare function get_period(shift as integer) as integer

function get_period(shift as integer) as integer

defint shiftvar=shift
   defint period_gp
defint shiftplusone=shiftvar+1
defint shiftplustwo=shiftvar+2
defdbl timebcpp_shift=val(varptr$(timebcpp(varptr(shiftvar))))
defdbl timebcpp_shiftplusone=val(varptr$(timebcpp(varptr(shiftplusone))))
defdbl timebcpp_shiftplustwo=val(varptr$(timebcpp(varptr(shiftplustwo))))

   if (charttf(displayedfile) = 1440) then
   
     '// дневки - исключаем ошибки в понедельник (макс будет в этом случае = 3 дня)
     period_gp = minreal( timebcpp_shift - timebcpp_shiftplusone, timebcpp_shiftplusone - timebcpp_shiftplustwo)
     '//Comment(period_gp);   
   else   
     period_gp = minreal( timebcpp_shift - timebcpp_shiftplusone, timebcpp_shiftplusone - timebcpp_shiftplustwo)
   end if   
   result=period_gp
end function