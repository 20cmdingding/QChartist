// static arrayofdoubles stochasticbuffer; // This line of code must stay here.
static arrayofdoubles MainBuffer;
static arrayofdoubles SignalBuffer;
static arrayofdoubles stochup;
static arrayofdoubles stochdn;

//+------------------------------------------------------------------+
//|                                                   Stochastic.mq4 |
//|                      Copyright © 2004, MetaQuotes Software Corp. |
//|                                       http://www.metaquotes.net/ |
//+------------------------------------------------------------------+
/*
#property copyright "Copyright © 2004, MetaQuotes Software Corp."
#property link      "http://www.metaquotes.net/"

#property indicator_separate_window
#property indicator_minimum 0
#property indicator_maximum 100
#property indicator_buffers 2
#property indicator_color1 LightSeaGreen
#property indicator_color2 Red
//---- input parameters
extern int KPeriod=5;
extern int DPeriod=3;
extern int Slowing=3;
//---- buffers
double MainBuffer[];
double SignalBuffer[];
double HighesBuffer[];
double LowesBuffer[];
//----
int draw_begin1=0;
int draw_begin2=0;
//+------------------------------------------------------------------+
//| Custom indicator initialization function                         |
//+------------------------------------------------------------------+
int init()
  {
   string short_name;
//---- 2 additional buffers are used for counting.
   IndicatorBuffers(4);
   SetIndexBuffer(2, HighesBuffer);
   SetIndexBuffer(3, LowesBuffer);
//---- indicator lines
   SetIndexStyle(0,DRAW_LINE);
   SetIndexBuffer(0, MainBuffer);
   SetIndexStyle(1,DRAW_LINE);
   SetIndexBuffer(1, SignalBuffer);
//---- name for DataWindow and indicator subwindow label
   short_name="Sto("+KPeriod+","+DPeriod+","+Slowing+")";
   IndicatorShortName(short_name);
   SetIndexLabel(0,short_name);
   SetIndexLabel(1,"Signal");
//----
   draw_begin1=KPeriod+Slowing;
   draw_begin2=draw_begin1+DPeriod;
   SetIndexDrawBegin(0,draw_begin1);
   SetIndexDrawBegin(1,draw_begin2);
//----
   return(0);
  }
*/
//+------------------------------------------------------------------+
//| Stochastic oscillator                                            |
//+------------------------------------------------------------------+
char* stochastic (char* period)
{
    static char periodd[1000];
    strncpy(periodd, period, 1000);
    int intperiod=atoi(periodd);

//---- input parameters
int KPeriod=5;
int DPeriod=3;
int Slowing=3;
//---- buffers

static arrayofdoubles HighesBuffer;
static arrayofdoubles LowesBuffer;
//----
int draw_begin1=0;
int draw_begin2=0;

   int    i,k;
   int    counted_bars=cntbarsedit;//IndicatorCounted();
   double price;
//----
   if(bars<=draw_begin2) return(0);
//---- initial zero
   if(counted_bars<1)
     {
      for(i=1;i<=draw_begin1;i++) MainBuffer[bars-i]=0;
      for(i=1;i<=draw_begin2;i++) SignalBuffer[bars-i]=0;
     }
//---- minimums counting
   i=bars-KPeriod;
   if(counted_bars>KPeriod) i=bars-counted_bars-1;
   while(i>=0)
     {
      double min=1000000;
      k=i+KPeriod-1;
      while(k>=i)
        {
         price=lowa[k];
         if(min>price) min=price;
         k--;
        }
      LowesBuffer[i]=min;
      i--;
     }
//---- maximums counting
   i=bars-KPeriod;
   if(counted_bars>KPeriod) i=bars-counted_bars-1;
   while(i>=0)
     {
      double max=-1000000;
      k=i+KPeriod-1;
      while(k>=i)
        {
         price=higha[k];
         if(max<price) max=price;
         k--;
        }
      HighesBuffer[i]=max;
      i--;
     }
//---- %K line
   i=bars-draw_begin1;
   if(counted_bars>draw_begin1) i=bars-counted_bars-1;
   while(i>=0)
     {
      double sumlow=0.0;
      double sumhigh=0.0;
      for(k=(i+Slowing-1);k>=i;k--)
        {
         sumlow+=closea[k]-LowesBuffer[k];
         sumhigh+=HighesBuffer[k]-LowesBuffer[k];
        }
      if(sumhigh==0.0) MainBuffer[i]=100.0;
      else MainBuffer[i]=sumlow/sumhigh*100;
      i--;
     }
//---- last counted bar will be recounted
   if(counted_bars>0) counted_bars--;
   int limit=bars-counted_bars;
//---- signal line is simple movimg average
   for(i=0; i<limit; i++) {
      SignalBuffer[i]=imaonarray(MainBuffer,bars,DPeriod,0,MODE_SMA,i);
stochup[i]=80;
stochdn[i]=20;
}
//----

   return(0);
  }
//+------------------------------------------------------------------+