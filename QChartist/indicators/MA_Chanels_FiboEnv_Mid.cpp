static arrayofdoubles MA_Chanels_FiboEnv_Midbuffer1; // This line of code must stay here.
static arrayofdoubles MA_Chanels_FiboEnv_Midbuffer2; // This line of code must stay here.
static arrayofdoubles MA_Chanels_FiboEnv_Midbuffer3; // This line of code must stay here.
static arrayofdoubles MA_Chanels_FiboEnv_Midbuffer4; // This line of code must stay here.
static arrayofdoubles MA_Chanels_FiboEnv_Midbuffer5; // This line of code must stay here.
static arrayofdoubles MA_Chanels_FiboEnv_Midbuffer6; // This line of code must stay here.
static arrayofdoubles MA_Chanels_FiboEnv_Midbuffer7; // This line of code must stay here.

//+------------------------------------------------------------------+
//|                           MA Chanels FiboEnv Mid.mq4             |
//|                                                           °njel° |
//|                                           iamnotlinked   mod. ik |
//+------------------------------------------------------------------+
//#property copyright "°njel°"
//#property link      "iamnotlinked"

//#property indicator_chart_window
//#property indicator_buffers 7

//#property indicator_color1 MediumOrchid
//#property indicator_color2 Violet
//#property indicator_color3 MediumOrchid
//#property indicator_color4 Violet
//#property indicator_color5 MediumOrchid
//#property indicator_color6 Violet
//#property indicator_color7 MediumOrchid
//---- input parameters

//
/***
PRICE_CLOSE    0 Close price. 
PRICE_OPEN     1 Open price. 
PRICE_HIGH     2 High price. 
PRICE_LOW      3 Low price. 
PRICE_MEDIAN   4 Median price, (high+low)/2. 
PRICE_TYPICAL  5 Typical price, (high+low+close)/3. 
PRICE_WEIGHTED 6 Weighted close price, (high+low+close+close)/4
MAMethod
MODE_SMA    0 Simple moving average, 
MODE_EMA    1 Exponential moving average, 
MODE_SMMA   2 Smoothed moving average, 
MODE_LWMA   3 Linear weighted moving average. 

***/



//---- buffers
//double ExtMapBuffer1[];
//double ExtMapBuffer2[];
//double ExtMapBuffer3[];
//double ExtMapBuffer4[];
//double ExtMapBuffer5[];
//double ExtMapBuffer6[];
//double ExtMapBuffer7[];

//+------------------------------------------------------------------+
//| Custom indicator iteration function                              |
//+------------------------------------------------------------------+
char* MA_Chanels_FiboEnv_Mid (char* period, char* curtf)
  {
    static char periodd[1000];
    strncpy(periodd, period, 1000);
    int intperiod=atoi(periodd);
    static char curtff[1000];
    strncpy(curtff, curtf, 1000);
    int intcurtf=atoi(curtff);

int BarsCount = 400;
int MAPeriod=55;
int MAMethod=MODE_SMA;
int MAPrice=4;
int MAShift=0;
int i;
double  max =0;
double  min =0;
double    Inc1 = 0.0000;
double    Inc2 = 0.0000;
double    Inc3 = 0.0000;
double    Inc4 = 0.0000;

int ____;
int Note;
int ______;
int priceClose_0__priceOpen_1; 
int priceHigh_2__priceLow_3;
int priceMedian_4__priceTypical_5; 
int priceWeightedclose_6; 
int _______;
int MA_Method;
int SMA_0_EMA1_SMMA2_LWMA3;

   max =0;
   min =0;
   
  
      
   for (i =BarsCount; i>=0; i--)
   {
   
      double m = ima(intcurtf,MAPeriod,0,MAMethod,MAPrice,i);
      double top = higha[i] - m;      
      if (top > max)
         max = top;
      
      double bottom = lowa[i] - m;      
      if (bottom < min)
         min = bottom;
    
   }
   
   if (fabs(max) >  fabs(min))
      Inc4 = max; 
      else
      Inc4 = min;
    
      Inc1 = (max-min)*0.118; 
      Inc2 = (max-min)*0.264; 
      Inc3 = (max-min)*0.5;
      

   for (i =BarsCount; i>=0; i--)
   {
      MA_Chanels_FiboEnv_Midbuffer1[i] = ima(intcurtf,MAPeriod,0,MAMethod,MAPrice,i) + Inc3; 
      MA_Chanels_FiboEnv_Midbuffer2[i] = ima(intcurtf,MAPeriod,0,MAMethod,MAPrice,i) + Inc2 ;
      MA_Chanels_FiboEnv_Midbuffer3[i] = ima(intcurtf,MAPeriod,0,MAMethod,MAPrice,i) + Inc1 ;
      MA_Chanels_FiboEnv_Midbuffer4[i] = ima(intcurtf,MAPeriod,0,MAMethod,MAPrice,i);      
      MA_Chanels_FiboEnv_Midbuffer5[i] = ima(intcurtf,MAPeriod,0,MAMethod,MAPrice,i) - Inc1;
      MA_Chanels_FiboEnv_Midbuffer6[i] = ima(intcurtf,MAPeriod,0,MAMethod,MAPrice,i) - Inc2;
      MA_Chanels_FiboEnv_Midbuffer7[i] = ima(intcurtf,MAPeriod,0,MAMethod,MAPrice,i) - Inc3;
  
      
   }

   return(0);
  }
//+------------------------------------------------------------------+