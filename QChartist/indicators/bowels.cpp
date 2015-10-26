//+------------------------------------------------------------------+
//|   AutoPivotIndicator.mq4          ver 4.02           by Habeeb   |
//|                                                                  |
//|          This version solves the Sunday Bar problem.             |
//| Ver4 calculated daily pivots incorrectly when Use_Sunday_Data    |
//|        was set to "False".  Fixed in this version.               |
//| Ported to QChartist by Julien Moog                               |
//+------------------------------------------------------------------+

//#property indicator_chart_window

static arrayofdoubles pivot;
static arrayofdoubles s1;
static arrayofdoubles s2;
static arrayofdoubles s3;
static arrayofdoubles r1;
static arrayofdoubles r2;
static arrayofdoubles r3;

char* bowels (char* period,char* tfbase)
{
static char tfbasee[1000];
    strncpy(tfbasee, tfbase, 1000);
    int inttfbase=atoi(tfbasee);
	bool Daily             = True;
 
   double YesterdayHigh;
   double YesterdayLow;
   double YesterdayClose;
   //double Day_Price[][6];
   double Pivot,S1,S2,S3,R1,R2,R3;
      
   double WeekHigh;
   double WeekLow;
   double WeekClose;
   //double Weekly_Price[][6];
   double WeekPivot,WS1,WS2,WS3,WR1,WR2,WR3;
   
   double MonthHigh;
   double MonthLow;
   double MonthClose;
   //double Month_Price[][6];
   double MonthPivot,MS1,MS2,MS3,MR1,MR2,MR3;
   
   double YearHigh;
   double YearLow;
   double YearClose;
   //double Year_Price[][6];
   double YearPivot,YS1,YS2,YS3,YR1,YR2,YR3;

//ArrayCopyRates(Day_Price,(Symbol()), 1440);

   
switch (inttfbase) {
            case 0:  
   YesterdayHigh  = ihigh(1440,1); //Day_Price[1][3];
   YesterdayLow   = ilow(1440,1); //Day_Price[1][2];
   YesterdayClose = iclose(1440,1); //Day_Price[1][4];
break;
case 1:
   YesterdayHigh  = ihigh(10080,1); //Day_Price[1][3];
   YesterdayLow   = ilow(10080,1); //Day_Price[1][2];
   YesterdayClose = iclose(10080,1); //Day_Price[1][4];
break;
}
   
   Pivot = ((YesterdayHigh + YesterdayLow + YesterdayClose)/3);

   R1 = (2*Pivot)-YesterdayLow;
   S1 = (2*Pivot)-YesterdayHigh;

   R2 = Pivot+(R1-S1);
   S2 = Pivot-(R1-S1);
   
   R3 = (YesterdayHigh + (2*(Pivot-YesterdayLow)));
   S3 = (YesterdayLow - (2*(YesterdayHigh-Pivot)));  
      
//--------------------------------------------------------

if (Daily==true)
 {
  for (int i=0;i<=100;i++) {

pivot[i]=Pivot;
s1[i]=S1;
s2[i]=S2;
s3[i]=S3;
r1[i]=R1;
r2[i]=R2;
r3[i]=R3;

}
}

//---------------------------------------------------------

//ObjectsRedraw();

   return(0);
}