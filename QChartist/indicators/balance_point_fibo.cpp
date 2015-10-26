static arrayofdoubles dbp;
static arrayofdoubles dbph;
static arrayofdoubles dbpl;

char* balance_point_fibo (char* curtf)
{
    static char curtff[1000];
    strncpy(curtff, curtf, 1000);
    int intcurtf=atoi(curtff);
    // Put your indicator C++ code here



//+------------------------------------------------------------------+
//|                                        dynamic balance point.mq4 |
//+------------------------------------------------------------------+
//#property copyright "mladen"
//#property link      "mladenfx@gmail.com"

//#property indicator_chart_window
//#property indicator_buffers 3
//#property indicator_color1  DeepSkyBlue
//#property indicator_width1  2
//#property indicator_color2  Red
//#property indicator_width2  1
//#property indicator_color3  Red
//#property indicator_width3  1
 
int dbpLength = 5;
int bars_limit=200;
double max =0;
double min =0;
double Inc0 = 0.0000;
double Inc1 = 0.0000;
double Inc2 = 0.0000;
double Inc3 = 0.0000;
dbpLength = mathmax(1,dbpLength);
//   int counted_bars=IndicatorCounted();
   int i,limit;
double m;
double top;
double bottom;

//   if(counted_bars<0) return(-1);
//   if(counted_bars>0) counted_bars--;
         //limit = MathMin(Bars-counted_bars,Bars-1);
         limit=bars_limit;
   
   max =0;
   min =0;
   
   for(i=limit; i>=0; i--)
   {
      int k = ibarshift(intcurtf,datetimeserial[i]-dbpLength*PERIOD_W1*60,500);
      int weekDay = timedayofweek(datetimeserial[i]);
      for (; k<bars; k++)
      {
         if (timedayofweek(datetimeserial[k]) != weekDay) break;
      }
         
      int x = k-1;
      int l = x-i+1;
         
         double hi = higha[ihighest(charttf[displayedfile],MODE_HIGH,l,i)];
         double lo = lowa[ilowest(charttf[displayedfile],MODE_LOW,l,i)];

      //
      //
      //
      //
      //
      
      dbp[i] = (hi+lo+closea[i])/3.0;
      
      m = dbp[i];
      top = higha[i] - m;      
      if (top > max) 
	 max = top; 
      
      bottom = lowa[i] - m;      
      if (bottom < min) 
	 min = bottom; 

   }
   
   //
   //
   //
   //
   //
   
   if (fabs(max) >  fabs(min)) 
      Inc3 = max; 
   else 
      Inc3 = min;       
       
      Inc2 = Inc3*0.809; //0.618;
      Inc1 = Inc3*0.5;
      Inc0 = Inc3*0.236;
      Inc3 = Inc3*0.382;


      
for(i=limit; i>=0; i--)
   {
   
   dbph[i] = dbp[i] + Inc2; 
   dbpl[i] = dbp[i] - Inc2;
   
   }      


   
   return(0);
}