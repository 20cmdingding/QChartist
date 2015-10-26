//+------------------------------------------------------------------+
//|                                                  WeeklyPivot.mq4 |
//| Ported to QChartist by Julien Moog (Buggy, don't rely on it yet) |
//+------------------------------------------------------------------+
//#property indicator_chart_window
//#property indicator_buffers 7
//#property indicator_color1 Magenta
//#property indicator_color2 RoyalBlue
//#property indicator_color3 Crimson
//#property indicator_color4 RoyalBlue
//#property indicator_color5 Crimson
//#property indicator_color6 SeaGreen
//#property indicator_color7 SeaGreen
//---- input parameters
//---- buffers
static arrayofdoubles PBuffer;
static arrayofdoubles S1Buffer;
static arrayofdoubles R1Buffer;
static arrayofdoubles S2Buffer;
static arrayofdoubles R2Buffer;
static arrayofdoubles S3Buffer;
static arrayofdoubles R3Buffer;
string Pivot="WeeklyPivotPoint",Sup1="W_S 1", Res1="W_R 1";
string Sup2="W_S 2", Res2="W_R 2", Sup3="W_S 3", Res3="W_R 3";
int fontsize=10;
double P,S1,R1,S2,R2,S3,R3;
double last_week_high, last_week_low, this_week_open, last_week_close;

//+------------------------------------------------------------------+
//| Custom indicator iteration function                              |
//+------------------------------------------------------------------+
char* weeklypivotcpp(char* barsback)
  {
static char barsbackk[1000];
    strncpy(barsbackk, barsback, 1000);
    int intbarsback=atoi(barsbackk);
   //int counted_bars=IndicatorCounted();
   int limit, i;
//---- indicator calculation
/*   if (counted_bars==0)
     {
      ObjectCreate("WeeklyPivot", OBJ_TEXT, 0, 0,0);
      ObjectSetText("WeeklyPivot", "                            Weekly Pivot Point",fontsize,"Arial",Red);
      ObjectCreate("Sup1", OBJ_TEXT, 0, 0, 0);
      ObjectSetText("Sup1", "        wS 1",fontsize,"Arial",Red);
      ObjectCreate("Res1", OBJ_TEXT, 0, 0, 0);
      ObjectSetText("Res1", "        wR 1",fontsize,"Arial",Red);
      ObjectCreate("Sup2", OBJ_TEXT, 0, 0, 0);
      ObjectSetText("Sup2", "        wS 2",fontsize,"Arial",Red);
      ObjectCreate("Res2", OBJ_TEXT, 0, 0, 0);
      ObjectSetText("Res2", "        wR 2",fontsize,"Arial",Red);
      ObjectCreate("Sup3", OBJ_TEXT, 0, 0, 0);
      ObjectSetText("Sup3", "        wS 3",fontsize,"Arial",Red);
      ObjectCreate("Res3", OBJ_TEXT, 0, 0, 0);
      ObjectSetText("Res3", "        wR 3",fontsize,"Arial",Red);
     }
   if(counted_bars<0) return(-1);
*/
//----
   //limit=(Bars-counted_bars)-1;
	limit=intbarsback;
//----
   for(i=limit; i>=0;i--)
     {
      // Monday
      if(1==timedayofweek(timeb(i)) && 1!=timedayofweek(timeb(i+1)) )
        {
         //last_week_close=iclose(1440,i+1);
         //this_week_open=iopen(1440,i);
	 last_week_close=closea[i+1];
         this_week_open=opena[i];
         // WeeklyPivot
         P=(last_week_high + last_week_low + this_week_open + last_week_close)/4;
         R1=(2*P)-last_week_low;
         S1=(2*P)-last_week_high;
         R2=P+(last_week_high - last_week_low);
         S2=P-(last_week_high - last_week_low);
         R3=(2*P)+(last_week_high-(2*last_week_low));
         S3=(2*P)-((2* last_week_high)-last_week_low);
         //last_week_low=ilow(1440,i); last_week_high=ihigh(1440,i);
	 last_week_low=lowa[i]; last_week_high=higha[i];
//----

        }
      //last_week_high=mathmax(last_week_high, ihigh(1440,i));
      //last_week_low=mathmin(last_week_low, ilow(1440,i));
      last_week_high=mathmax(last_week_high, higha[i]);
      last_week_low=mathmin(last_week_low, lowa[i]);
      PBuffer[i]=P;
      S1Buffer[i]=S1;
      R1Buffer[i]=R1;
      S2Buffer[i]=S2;
      R2Buffer[i]=R2;
      S3Buffer[i]=S3;
      R3Buffer[i]=R3;
     }
//----
   return(0);
  }
//+------------------------------------------------------------------+