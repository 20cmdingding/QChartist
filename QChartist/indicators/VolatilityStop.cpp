//+------------------------------------------------------------------+
//|                                              Volatility Stop.mq4 |
//|                                       Copyright © 2006, Akuma99. |
//|                                      http://akuma99.blogspot.com |
//+------------------------------------------------------------------+
//#property copyright "Copyright © 2006, Akuma99."
//#property link      "http://akuma99.blogspot.com"

//#property indicator_chart_window
//#property indicator_buffers 2
//#property indicator_color1 Red
//#property indicator_color2 Blue


//---- buffers
static arrayofdoubles volatilitystopBuffer1;
static arrayofdoubles volatilitystopBuffer2;

double findRange(int);

//+------------------------------------------------------------------+
//| Custom indicator iteration function                              |
//+------------------------------------------------------------------+
char* VolatilityStop (char* period)
  {
//---- input parameters
bool short2=False;
   //int    counted_bars=IndicatorCounted();
//----
   int   limit = 100; // Bars-counted_bars;
   int   i;
   
   for (i=limit; i>=0; i--) {

      double r = findRange(i);
      
      //Print (r);
      
      if (short2 == True) {
      
         volatilitystopBuffer1[i] = mathmin(higha[i]+r, volatilitystopBuffer1[i+1]);
         
      } else if (short2 == False) {
         
         volatilitystopBuffer2[i] = mathmax(lowa[i]-r,volatilitystopBuffer2[i+1]);
         
      }
      
      //Print (volatilitystopBuffer2[i]);
   
   }
//----
   return(0);
  }
//+------------------------------------------------------------------+

double findRange(int i) {
double volatrange=1.3;
   static double rng;
   
   for (int j=24; j>=0; j--) {
      rng += (higha[i+j]-lowa[i+j]);
   }

   rng = (rng/24)*volatrange;

   return(rng);

}