//+------------------------------------------------------------------+
//|                                                         MACD.mq4 |
//|                                Copyright © 2005, David W. Thomas |
//|                                           mailto:davidwt@usa.net |
//+------------------------------------------------------------------+
// This is the correct computation and display of MACD.
/*
#property copyright "Copyright © 2005, David W. Thomas"
#property link      "mailto:davidwt@usa.net"

#property indicator_separate_window
#property indicator_buffers 3
#property indicator_color1 Yellow
#property indicator_color2 Red
#property indicator_color3 Blue
*/

//---- buffers
static arrayofdoubles MACDLineBuffer;
static arrayofdoubles SignalLineBuffer;
static arrayofdoubles HistogramBuffer;

//+------------------------------------------------------------------+
//| Custom indicator initialization function                         |
//+------------------------------------------------------------------+
/*
int init()
{
   IndicatorDigits(MarketInfo(Symbol(),MODE_DIGITS)+1);
   //---- indicators
   SetIndexStyle(2,DRAW_LINE,STYLE_SOLID,2);
   SetIndexBuffer(2,MACDLineBuffer);
   SetIndexDrawBegin(0,SlowMAPeriod);
   SetIndexStyle(1,DRAW_LINE,STYLE_SOLID,2);
   SetIndexBuffer(1,SignalLineBuffer);
   SetIndexDrawBegin(1,SlowMAPeriod+SignalMAPeriod);
   SetIndexStyle(0,DRAW_HISTOGRAM,STYLE_SOLID,3);
   SetIndexBuffer(0,HistogramBuffer);
   SetIndexDrawBegin(2,SlowMAPeriod+SignalMAPeriod);
   //---- name for DataWindow and indicator subwindow label
   IndicatorShortName("MACD("+FastMAPeriod+","+SlowMAPeriod+","+SignalMAPeriod+")");
   SetIndexLabel(0,"MACD");
   SetIndexLabel(1,"Signal");
   //----
	alpha = 2.0 / (SignalMAPeriod + 1.0);
	alpha_1 = 1.0 - alpha;
   //----
   return(0);
}
*/
//+------------------------------------------------------------------+
//| Custor indicator deinitialization function                       |
//+------------------------------------------------------------------+
/*
int deinit()
{
   //---- 
   
   //----
   return(0);
}
*/
//+------------------------------------------------------------------+
//| Custom indicator iteration function                              |
//+------------------------------------------------------------------+
char* realMACD (char* curtf)
{
    static char curtff[1000];
    strncpy(curtff, curtf, 1000);
    int intcurtf=atoi(curtff);

//---- input parameters
int       FastMAPeriod=12;
int       SlowMAPeriod=26;
int       SignalMAPeriod=9;

//---- variables
double alpha = 0;
double alpha_1 = 0;

alpha = 2.0 / (SignalMAPeriod + 1.0);
	alpha_1 = 1.0 - alpha;

   int limit;
   //int counted_bars = IndicatorCounted();
   //---- check for possible errors
   //if (counted_bars<0) return(-1);
   //---- last counted bar will be recounted
   //if (counted_bars>0) counted_bars--;
   limit = 333; //Bars - counted_bars;
if (limit>chartbars[displayedfile]) limit=chartbars[displayedfile];

   for(int i=limit; i>=0; i--)
   {
      MACDLineBuffer[i] = ima(intcurtf,FastMAPeriod,0,MODE_EMA,PRICE_CLOSE,i) - ima(intcurtf,SlowMAPeriod,0,MODE_EMA,PRICE_CLOSE,i);
      SignalLineBuffer[i] = alpha*MACDLineBuffer[i] + alpha_1*SignalLineBuffer[i+1];
      HistogramBuffer[i] = (MACDLineBuffer[i] - SignalLineBuffer[i]) * 2;
   }
   
   //----
   return(0);
}
//+------------------------------------------------------------------+