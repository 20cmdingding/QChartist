//+------------------------------------------------------------------------------------+
//|                                                Din_fibo_high.mq4                   |
//|                                 unknown author, get from kaizer, conversed by Rosh |
//| link to kaizer: http://forum.alpari-idc.ru/profile.php?mode=viewprofile&u=4196161  |
//|                                              http://forexsystems.ru/phpBB/index.php|
//|     Ported from MT4 to QChartist by Julien Moog - julien.moog@laposte.net          |
//+------------------------------------------------------------------------------------+
//#property copyright "unknown author, get from kaizer, conversed by Rosh"
//#property link      "http://forexsystems.ru/phpBB/index.php"

//#property indicator_chart_window
//#property indicator_buffers 2
//#property indicator_color1 Blue
//#property indicator_color2 Yellow
//---- input parameters
int       Ch_Period=3;
double    Ratio=0.786;
bool SetAllBars=false;
//---- buffers
static arrayofdoubles dinfibohighbuffer1;
static arrayofdoubles dinfibohighbuffer2;
static arrayofdoubles tvBuffer;
int hh,ll,first,counterPeriod;
double tv,MaH,MaL;
int bars2=200;

bool isDelimeter(int, int);
int SetHnL(int,int);
int SetValuesNullBar(int,int);
int SetMovingHnL(int,int);
//+------------------------------------------------------------------+
//| ѕроверим - разделитель диапазона или нет                         |
//+------------------------------------------------------------------+
bool isDelimeter(int _Period, int _shift)
  {

  bool result=0;
//---- 

//Buggy, commented

  switch (_Period)
   {
   case 5:
result=(timeminute(timeb(_shift))==0)&&(timehour(timeb(_shift))==0); 
break;

   case 15:
result=(timeminute(timeb(_shift))==0)&&(timehour(timeb(_shift))==0); 
break;

   case 30:
result=(timeminute(timeb(_shift))==0)&&(timehour(timeb(_shift))==0); 
break;

   case 60:
result=(timeminute(timeb(_shift))==0)&&(timehour(timeb(_shift))==0); 
break;


   //case 240:result=(timeDayOfWeek(Time[_shift])==1)&&(TimeHour(Time[_shift])==0); break;
   //case 1440:result=(timeDay(Time[_shift])==1)||((TimeDay(Time[_shift])==2 && TimeDay(Time[_shift+1])!=1))||((TimeDay(Time[_shift])==3 && TimeDay(Time[_shift+1])!=2)); break;
   //case 10080:result=timeDay(Time[_shift])<=7 && TimeMonth(Time[_shift])==1; break;
   //default: Print("Ќедопустимый период!!!"); 
   }
//----
   return(result);
  }
//+------------------------------------------------------------------+
//| ”становим MaH и MaL на границе диапазона                           |
//+------------------------------------------------------------------+
int SetHnL(int _shift, int intperiod)
  { 
//static char periodd[1000];
//    strncpy(periodd, period, 1000);
//    int intperiod=atoi(periodd);
//---- 
   int i=_shift+1;
   counterPeriod=0;
   while (counterPeriod<Ch_Period)
      {
      while (tvBuffer[i]==0.0 && i<bars2) i++;
      counterPeriod++;
      i++;
      }
   i--;   
   hh=ihighest(intperiod,MODE_HIGH,i-_shift,_shift+1);
   ll=ilowest(intperiod,MODE_LOW,i-_shift,_shift+1);
   //tv=NormalizeDouble((High[hh]+Low[ll]+Close[_shift+1])/3.0,Digits);
tv=(higha[hh]+lowa[ll]+closea[_shift+1])/3.0;
   //MaH=tv+NormalizeDouble((High[hh]-Low[ll])/2.0*Ratio,Digits);
MaH=tv+(higha[hh]-lowa[ll])/2.0*Ratio;
   //MaL=tv-NormalizeDouble((High[hh]-Low[ll])/2.0*Ratio,Digits);
MaL=tv-(higha[hh]-lowa[ll])/2.0*Ratio;
   tvBuffer[_shift]=tv;
   dinfibohighbuffer1[_shift]=MaH;
   dinfibohighbuffer2[_shift]=MaL;
   SetMovingHnL(i, _shift);    

//----
   return 0;
  }
//+------------------------------------------------------------------+
//| ”становим MaH и MaL внутри диапазона                             |
//+------------------------------------------------------------------+
int SetMovingHnL(int _DelimeterBar,int CurBar)
  {
   double delta;
//---- 
   delta=(tvBuffer[_DelimeterBar]-tvBuffer[CurBar])/(_DelimeterBar-CurBar);
//----
   return 0;
  }
//+------------------------------------------------------------------+
//| ”становим MaH и MaL на правом краю                               |
//+------------------------------------------------------------------+
int SetValuesNullBar(int _shift,int intperiod)
  {
//---- 
//static char periodd[1000];
    //strncpy(periodd, period, 1000);
    //int intperiod=atoi(periodd);
   int i=_shift;
   while (tvBuffer[i]==0.0) i++;
   for (int j=i-1;j>_shift;j--)
      {
      dinfibohighbuffer1[j]=0.0;
      dinfibohighbuffer2[j]=0.0;
      }
   i=_shift;
   counterPeriod=0;
   while (counterPeriod<Ch_Period)
      {
      while (tvBuffer[i]==0.0 && i<bars2) i++;
      counterPeriod++;
      i++;
      }
   i--;   
   hh=ihighest(intperiod,MODE_HIGH,i-_shift,_shift);
   ll=ilowest(intperiod,MODE_LOW,i-_shift,_shift);
   //tv=NormalizeDouble((High[hh]+Low[ll]+Close[_shift])/3.0,Digits);
   //MaH=tv+NormalizeDouble((High[hh]-Low[ll])/2.0*Ratio,Digits);
   //MaL=tv-NormalizeDouble((High[hh]-Low[ll])/2.0*Ratio,Digits);
   tv=(higha[hh]+lowa[ll]+closea[_shift])/3.0;
   MaH=tv+(higha[hh]-lowa[ll])/2.0*Ratio;
   MaL=tv-(higha[hh]-lowa[ll])/2.0*Ratio;
   dinfibohighbuffer1[_shift]=MaH;
   dinfibohighbuffer2[_shift]=MaL;
   //SetMovingHnL(j, _shift);    
//----
   return 0;
  }

//+------------------------------------------------------------------+
//| Custom indicator iteration function                              |
//+------------------------------------------------------------------+
char* dinfibohighcpp(char* period)
  {
static char periodd[1000];
    strncpy(periodd, period, 1000);
    int intperiod=atoi(periodd);
   //int    counted_bars=IndicatorCounted();
   int cnt,limit;
	limit=bars2;

//---- 
   //if (Period()==10080) return;
   //if (counted_bars<0) return(-1);
   //if (counted_bars>0) limit=bars2-counted_bars;
/* //if (counted_bars==0)
      //{
      // найти первый и второй разделитель и установить limit
      cnt=bars2-1;
      while (!isDelimeter(intperiod,cnt)) cnt--;
      first=cnt;
      cnt--;
      counterPeriod=0;
      while (counterPeriod<Ch_Period)
         {
         while (!isDelimeter(intperiod,cnt)) cnt--;
         cnt--;
         counterPeriod++;
         }
      cnt++;
      hh=ihighest(intperiod,MODE_HIGH,first-cnt,cnt+1);
      ll=ilowest(intperiod,MODE_LOW,first-cnt,cnt+1);
      //tv=NormalizeDouble((High[hh]+Low[ll]+Close[cnt+1])/3.0,Digits);
      //MaH=tv+NormalizeDouble((High[hh]-Low[ll])/2.0*Ratio,Digits);
      //MaL=tv-NormalizeDouble((High[hh]-Low[ll])/2.0*Ratio,Digits);
      tv=(higha[hh]+lowa[ll]+closea[cnt+1])/3.0;
      MaH=tv+(higha[hh]-lowa[ll])/2.0*Ratio;
      MaL=tv-(higha[hh]-lowa[ll])/2.0*Ratio;
      tvBuffer[cnt]=tv;
      dinfibohighbuffer1[cnt]=MaH;
      dinfibohighbuffer2[cnt]=MaL;
      limit=cnt-1;
      //} */   
//----
   for (int shift=limit;shift>=0;shift--)
      {
      if (isDelimeter(intperiod,shift)) SetHnL(shift,intperiod);// else SetMovingHnL(shift);
      if (shift==0) SetValuesNullBar(shift,intperiod);

      }

// Zig Zag algorithm
int begin; int end; double range; double step;int start;
start=0;
for (int i=0;i<=limit;i++)
	{
	if (dinfibohighbuffer1[i]==0 && dinfibohighbuffer1[i-1]!=0 && i>0)
		{
		begin=i;
		start=1;
		}
	if (dinfibohighbuffer1[i]==0 && dinfibohighbuffer1[i+1]!=0 && start==1)	
		{
		end=i;
		range=dinfibohighbuffer1[end+1]-dinfibohighbuffer1[begin-1];
		step=range/(end-begin+2);
		for (int j=begin;j<=end;j++)
			{
			dinfibohighbuffer1[j]=dinfibohighbuffer1[j-1]+step;
			}
		start=0;
		}
	}
start=0;
for (int i=0;i<=limit;i++)
	{
	if (dinfibohighbuffer2[i]==0 && dinfibohighbuffer2[i-1]!=0 && i>0)
		{
		begin=i;
		start=1;
		}
	if (dinfibohighbuffer2[i]==0 && dinfibohighbuffer2[i+1]!=0 && start==1)	
		{
		end=i;
		range=dinfibohighbuffer2[end+1]-dinfibohighbuffer2[begin-1];
		step=range/(end-begin+2);
		for (int j=begin;j<=end;j++)
			{
			dinfibohighbuffer2[j]=dinfibohighbuffer2[j-1]+step;
			}
		start=0;
		}
	}
// End Zig Zag algorithm
      
   return(0);
  }
//+------------------------------------------------------------------+
