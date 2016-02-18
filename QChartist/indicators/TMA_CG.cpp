//+------------------------------------------------------------------+
//|                                                       TMA+CG.mq4 |
//|                                                           mladen |
//| arrowse coded acording to idea presented by rajiv                |
//+------------------------------------------------------------------+
/*
#property copyright "rajivxxx"
#property link      "rajivxxx@gmail.com"

#property indicator_chart_window
#property indicator_buffers 5
#property indicator_color1  DimGray
#property indicator_color2  Red
#property indicator_color3  LimeGreen
#property indicator_color4  Red
#property indicator_color5  Blue
#property indicator_style1  STYLE_DOT
*/

static arrayofdoubles tmBuffer;
static arrayofdoubles upBuffer;
static arrayofdoubles dnBuffer;
static arrayofdoubles wuBuffer;
static arrayofdoubles wdBuffer;
static arrayofdoubles upArrow;
static arrayofdoubles dnArrow;

/*
string IndicatorFileName;
int   calculatingTma = 0;
int   returningBars  = 0;
int    timeFrame;
*/

void calculateTma(int,double,int,double,int);

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
/*
int init()
{
   timeFrame  = stringToTimeFrame(TimeFrame);
   HalfLength = MathMax(HalfLength,1);
   IndicatorBuffers(7);
         SetIndexBuffer(0,tmBuffer);  SetIndexDrawBegin(0,HalfLength);
         SetIndexBuffer(1,upBuffer);  SetIndexDrawBegin(1,HalfLength);
         SetIndexBuffer(2,dnBuffer);  SetIndexDrawBegin(2,HalfLength);
         SetIndexBuffer(3,dnArrow);   SetIndexStyle(3,DRAW_ARROW); SetIndexArrow(5,242);
         SetIndexBuffer(4,upArrow);   SetIndexStyle(4,DRAW_ARROW); SetIndexArrow(6,241);
         SetIndexBuffer(5,wuBuffer);
         SetIndexBuffer(6,wdBuffer);

         if (TimeFrame=="calculateTma")  { calculatingTma=true; return(0); }
         if (TimeFrame=="returnBars")    { returningBars=true;  return(0); }

   
   IndicatorFileName = WindowExpertName();
   return(0);
}
int deinit() { return(0); }
*/
//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+

char* TMA_CG (char* curtf)
{
//extern string TimeFrame       = "current time frame";
int    HalfLength      = 56;
Price           = PRICE_WEIGHTED;
double BandsDeviations = 2.5;
int   Interpolate     = 1;
/*
int   alertsOn        = 0;
int   alertsOnCurrent = 0;
int   alertsOnHighLow = 1;
int   alertsMessage   = 1;
int   alertsSound     = 0;
int   alertsEmail     = 0;
*/

static char curtff[1000];
    strncpy(curtff, curtf, 1000);
    int intcurtf=atoi(curtff);

//timeFrame  = stringToTimeFrame(TimeFrame);
   HalfLength = mathmax(HalfLength,1);

         //if (TimeFrame=="calculateTma")  { calculatingTma=true; return(0); }
         //if (TimeFrame=="returnBars")    { returningBars=true;  return(0); }

   
   //IndicatorFileName = WindowExpertName();

   //int counted_bars=333; //IndicatorCounted();
   int i,limit;
   int Bars=333;
if (Bars>chartbars[displayedfile]) Bars=chartbars[displayedfile];

   //if(counted_bars<0) return(-1);
   //if(counted_bars>0) counted_bars--;
           //limit=mathmin(Bars-1,Bars-counted_bars+HalfLength);
	   limit=Bars-1;

           //if (returningBars)  { tmBuffer[0] = limit; return(0); }
           //if (calculatingTma) { calculateTma(limit); return(0); }
           //if (timeFrame > intcurtf) limit = MathMax(limit,MathMin(Bars-1,iCustom(NULL,timeFrame,IndicatorFileName,"returnBars",0,0)*timeFrame/Period()));
   calculateTma(limit,HalfLength,Price,BandsDeviations,intcurtf);
 	for(i = limit; i >= 0; i--)
   {
      //int      shift1 = ibarshift(intcurtf,timeb(i),chartbars[displayedfile],0);
	int shift1=i;
      int time1  = itimeb    (intcurtf,shift1);
      
         //tmBuffer[i] = iCustom(NULL,timeFrame,IndicatorFileName,"calculateTma",HalfLength,Price,BandsDeviations,0,shift1);
//tmBuffer[i] = calculateTma(limit,HalfLength,Price,BandsDeviations,0,shift1,intcurtf);
         //upBuffer[i] = iCustom(NULL,timeFrame,IndicatorFileName,"calculateTma",HalfLength,Price,BandsDeviations,1,shift1);
//upBuffer[i] = calculateTma(limit,HalfLength,Price,BandsDeviations,1,shift1,intcurtf);
         //dnBuffer[i] = iCustom(NULL,timeFrame,IndicatorFileName,"calculateTma",HalfLength,Price,BandsDeviations,2,shift1);
//dnBuffer[i] = calculateTma(limit,HalfLength,Price,BandsDeviations,2,shift1,intcurtf);
//sprintf(debugmsg,"%i",i);MessageBox( NULL, debugmsg,"Debug",MB_OK);
         //upArrow[i] = 0;
         //dnArrow[i] = 0;            
            //if (higha[i+1]>upBuffer[i+1] && closea[i+1]>opena[i+1] && closea[i]<opena[i]) upArrow[i] = higha[i]+iATR(NULL,0,20,i);
            //if ( lowa[i+1]<dnBuffer[i+1] && closea[i+1]<opena[i+1] && closea[i]>opena[i]) dnArrow[i] = higha[i]-iATR(NULL,0,20,i);

         //if (timeFrame <= Period() || shift1==iBarShift(NULL,timeFrame,Time[i-1])) continue;
         if (Interpolate==0) continue;
	 int n;
         for(n = 1; i+n < Bars && timeb(i+n) >= time1; n++) continue;
         double factor = 1.0 / n;
	 int k;
         for(k = 1; k < n; k++)
            {
               tmBuffer[i+k] = k*factor*tmBuffer[i+n] + (1.0-k*factor)*tmBuffer[i];
               upBuffer[i+k] = k*factor*upBuffer[i+n] + (1.0-k*factor)*upBuffer[i];
               dnBuffer[i+k] = k*factor*dnBuffer[i+n] + (1.0-k*factor)*dnBuffer[i];
            }               
   }
/*   
   if (alertsOn)
   {
      if (alertsOnCurrent)
            int forBar = 0;
      else      forBar = 1;
      if (alertsOnHighLow)       
      {
         if (High[forBar] > upBuffer[forBar] && High[forBar+1] < upBuffer[forBar+1]) doAlert("high penetrated upper bar");
         if (Low[forBar]  < dnBuffer[forBar] && Low[forBar+1]  > dnBuffer[forBar+1]) doAlert("low penetrated lower bar");
      }
      else
      {
         if (Close[forBar] > upBuffer[forBar] && Close[forBar+1] < upBuffer[forBar+1]) doAlert("close penetrated upper bar");
         if (Close[forBar] < dnBuffer[forBar] && Close[forBar+1] > dnBuffer[forBar+1]) doAlert("close penetrated lower bar");
      }
   } 
*/
   return(0);
}

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
//
//
//
//
//

void calculateTma(int limit,double HalfLength,int Price,double BandsDeviations,int intcurtf)
{
   int i,j,k;
   double FullLength = 2.0*HalfLength+1.0;  
   int Bars=333;
if (Bars>chartbars[displayedfile]) Bars=chartbars[displayedfile];
   
   for (i=limit; i>=0; i--)
   {
      double sum  = (HalfLength+1)*ima(intcurtf,1,0,MODE_SMA,Price,i);
      double sumw = (HalfLength+1);

      for(j=1, k=HalfLength; j<=HalfLength; j++, k--)
      {
         sum  += k*ima(intcurtf,1,0,MODE_SMA,Price,i+j);
         sumw += k;

         if (j<=i)
         {
            sum  += k*ima(intcurtf,1,0,MODE_SMA,Price,i-j);
            sumw += k;
         }
      }

      tmBuffer[i] = sum/sumw;   
          
         double diff = ima(intcurtf,1,0,MODE_SMA,Price,i)-tmBuffer[i];

         if (i> (Bars-HalfLength-1)) continue;

         if (i==(Bars-HalfLength-1))
         {
            upBuffer[i] = tmBuffer[i];	    
            dnBuffer[i] = tmBuffer[i];

            if (diff>=0)
               {
                  wuBuffer[i] = pow(diff,2);
                  wdBuffer[i] = 0;
               }
            else
               {               
                  wdBuffer[i] = pow(diff,2);
                  wuBuffer[i] = 0;
               }
                 
            continue;

         }     
         
         if(diff>=0)
            {
               wuBuffer[i] = (wuBuffer[i+1]*(FullLength-1)+pow(diff,2))/FullLength;
               wdBuffer[i] =  wdBuffer[i+1]*(FullLength-1)/FullLength;

            }
         else
            {
               wdBuffer[i] = (wdBuffer[i+1]*(FullLength-1)+pow(diff,2))/FullLength;
               wuBuffer[i] =  wuBuffer[i+1]*(FullLength-1)/FullLength;

            }
         upBuffer[i] = tmBuffer[i] + BandsDeviations*sqrt(wuBuffer[i]);
         dnBuffer[i] = tmBuffer[i] - BandsDeviations*sqrt(wdBuffer[i]);

   }
return ;
}
    


//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
//
//
//
//
//
/*
void doAlert(string doWhat)
{
   static string   previousAlert="";
   static datetime previousTime;
   string message;

   //
   //
   //
   //
   //
   
   if (previousAlert!=doWhat || previousTime!=Time[0]) 
   {
      previousAlert = doWhat;
      previousTime  = Time[0];

      message= StringConcatenate(Symbol()," at ",TimeToStr(TimeLocal(),TIME_SECONDS)," THA : ",doWhat);
         if (alertsMessage) Alert(message);
         if (alertsEmail)   SendMail(StringConcatenate(Symbol(),"TMA "),message);
         if (alertsSound)   PlaySound("alert2.wav");
    }
}

//
//
//
//
//

int stringToTimeFrame(string tfs)
{
   for(int l = StringLen(tfs)-1; l >= 0; l--)
   {
      int char1 = StringGetChar(tfs,l);
          if((char1 > 96 && char1 < 123) || (char1 > 223 && char1 < 256))
               tfs = StringSetChar(tfs, 1, char1 - 32);
          else 
              if(char1 > -33 && char1 < 0)
                  tfs = StringSetChar(tfs, 1, char1 + 224);
   }
   int tf=0;
         if (tfs=="M1" || tfs=="1")     tf=PERIOD_M1;
         if (tfs=="M5" || tfs=="5")     tf=PERIOD_M5;
         if (tfs=="M15"|| tfs=="15")    tf=PERIOD_M15;
         if (tfs=="M30"|| tfs=="30")    tf=PERIOD_M30;
         if (tfs=="H1" || tfs=="60")    tf=PERIOD_H1;
         if (tfs=="H4" || tfs=="240")   tf=PERIOD_H4;
         if (tfs=="D1" || tfs=="1440")  tf=PERIOD_D1;
         if (tfs=="W1" || tfs=="10080") tf=PERIOD_W1;
         if (tfs=="MN" || tfs=="43200") tf=PERIOD_MN1;
         if (tf==0 || tf<Period())      tf=Period();
   return(tf);
} 
*/