//+------------------------------------------------------------------+
//|                                                       Levels.mq4 |
//|                                                             Maks |
//| Ported to QChartist by Julien Moog                               |
//+------------------------------------------------------------------+
static arrayofdoubles sopr1; // This line of code must stay here.
static arrayofdoubles sopr2; // This line of code must stay here.
static arrayofdoubles sopr3; // This line of code must stay here.
static arrayofdoubles sopr4; // This line of code must stay here.
static arrayofdoubles sopr5; // This line of code must stay here.
static arrayofdoubles pod1; // This line of code must stay here.
static arrayofdoubles pod2; // This line of code must stay here.
static arrayofdoubles pod3; // This line of code must stay here.
static arrayofdoubles pod4; // This line of code must stay here.
static arrayofdoubles pod5; // This line of code must stay here.

//+------------------------------------------------------------------+
//| Custom indicator iteration function                              |
//+------------------------------------------------------------------+
char* Levels()
  {

//#property copyright "Maks aka ug"
//#property link      ""

//#property indicator_chart_window

string Timeframe="D1";

//extern color LineColor_sopr = Blue;
int LineWidth_sopr = 2;
int LineStyle_sopr = 0;

//extern color LineColor_pod = DarkOrange;
int LineWidth_pod = 2;
int LineStyle_pod = 0;

//Служат для
int high_diap = 200;
int low_diap = 50;

double close_price,high_price,low_price;
static arrayofdoubles R;static arrayofdoubles S;
int PeriodName=0;
int diap = 0;

if (Timeframe=="M1") PeriodName=PERIOD_M1;
   else
      if (Timeframe=="M5") PeriodName=PERIOD_M5;
      else
         if (Timeframe=="M15")PeriodName=PERIOD_M15;
         else
            if (Timeframe=="M30")PeriodName=PERIOD_M30;
            else
               if (Timeframe=="H1") PeriodName=PERIOD_H1;
               else
                  if (Timeframe=="H4") PeriodName=PERIOD_H4;
                  else
                     if (Timeframe=="D1") PeriodName=PERIOD_D1;
                     else
                        if (Timeframe=="W1") PeriodName=PERIOD_W1;
                        else
                           if (Timeframe=="MN") PeriodName=PERIOD_MN1;
                           else
                             {
                              return(0);
                             }

   close_price=iclose(PeriodName,1);
   high_price=ihigh(PeriodName,1);
   low_price=ilow(PeriodName,1);
   
   if (high_price - low_price > high_diap) diap = 1;
   if (high_price - low_price < low_diap) diap = 2;

if (diap == 1)
{   
//Суженный
S[1] = close_price - ((high_price - low_price)*0.146)/2;
R[1] = ((high_price - low_price)*0.146)/2 + close_price;
R[2] = ((high_price - low_price)*0.236)+R[1];
R[3] = R[1]+2*((high_price - low_price)*0.236);
R[4] = R[3] + (R[1] - S[1]);
R[5] = R[4] + ((high_price - low_price)*0.236);
S[2] = S[1] - ((high_price - low_price)*0.236);
S[3] = S[1]- ((high_price - low_price)*0.236)*2;
S[4] = S[3] - (R[1] - S[1]);
S[5] = S[4] - ((high_price - low_price)*0.236);
}

if (diap == 0)
{
//Нормальный
S[1] = close_price - ((high_price - low_price)*0.236)/2; 
R[1] = ((high_price - low_price)*0.236)/2 + close_price;
R[2] = ((high_price - low_price)*0.382)+R[1];
R[3] = R[1]+2*((high_price - low_price)*0.382);
R[4] = R[3] + (R[1] - S[1]);
R[5] = R[4] + ((high_price - low_price)*0.382);
S[2] = S[1] - ((high_price - low_price)*0.382);
S[3] = S[1]-2*((high_price - low_price)*0.382);
S[4] = S[3] - (R[1] - S[1]);
S[5] = S[4] - ((high_price - low_price)*0.382);
}

if (diap == 2)
{
//Расширенный
S[1] = close_price - ((high_price - low_price)*0.382)/2; 
R[1] = ((high_price - low_price)*0.382)/2 + close_price;
R[2] = ((high_price - low_price)*0.618)+R[1];
R[3] = R[1]+2*((high_price - low_price)*0.618);
R[4] = R[3] + (R[1] - S[1]);
R[5] = R[4] + ((high_price - low_price)*0.618);
S[2] = S[1] - ((high_price - low_price)*0.618);
S[3] = S[1]-2*((high_price - low_price)*0.618);
S[4] = S[3] - (R[1] - S[1]);
S[5] = S[4] - ((high_price - low_price)*0.618);
}


   for (int i=0;i<=100;i++) {
	sopr1[i]=R[1]; // Nearest from middle
	sopr2[i]=R[2];
	sopr3[i]=R[3];
	sopr4[i]=R[4];
	sopr5[i]=R[5];
	pod1[i]=S[1]; // Nearest from middle
	pod2[i]=S[2];
	pod3[i]=S[3];
	pod4[i]=S[4];
	pod5[i]=S[5];
	}   

   return(0);
  }
//+------------------------------------------------------------------+