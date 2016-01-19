//+------------------------------------------------------------------+
//|                                     CoronaSwingPosition_v2.1.mq4 |
//|                                Copyright © 2009, TrendLaboratory |
//|            http://finance.groups.yahoo.com/group/TrendLaboratory |
//|                                   E-mail: igorad2003@yahoo.co.uk |
//+------------------------------------------------------------------+
// List of Prices:
// Price    = 0 - Close  
// Price    = 1 - Open  
// Price    = 2 - High  
// Price    = 3 - Low  
// Price    = 4 - Median Price   = (High+Low)/2  
// Price    = 5 - Typical Price  = (High+Low+Close)/3  
// Price    = 6 - Weighted Close = (High+Low+Close*2)/4
// Price    = 7 - Heiken Ashi Close  
// Price    = 8 - Heiken Ashi Open
// Price    = 9 - Heiken Ashi High
// Price    =10 - Heiken Ashi Low
/*
#property copyright "Copyright © 2009, TrendLaboratory"
#property link      "http://finance.groups.yahoo.com/group/TrendLaboratory"

#property indicator_separate_window
#property indicator_buffers   1
#property indicator_color1    Aquamarine
#property indicator_width1    2  
#property indicator_maximum   5.2
#property indicator_minimum  -5.2

//---- 
extern int     TimeFrame         =        0;   //Time Frame in min
extern int     Price             =        4;   //Price Mode (0...10)
extern color   LineColor         = Aquamarine;
extern int     FuzzR             =        0;
extern int     FuzzG             =      172;
extern int     FuzzB             =       64;
extern int     VisualMode        =        0;   //0-Psn+Corona,1-Psn,2-Corona 
extern int     CoronaBars        =     1000;
*/

static arrayofdoubles CoronaSwingPositionbuffer; // This line of code must stay here.
double Median(arrayofdoubles,int,int);
double HeikenAshi(int,int,int);

int     TimeFrame;//         =        1440; //charttf[displayedfile]; //0;   //Time Frame in min
int     Price             =        4;   //Price Mode (0...10)
int     FuzzR             =        0;
int     FuzzG             =      172;
int     FuzzB             =       64;
int     VisualMode        =        0;   //0-Psn+Corona,1-Psn,2-Corona 
int     CoronaBars        =     1000; 
//---- 
//double   Psn[];
//----
arrayofdoubles   haClose, haOpen, haHigh, haLow;
double MaxAmpl;
int      draw_begin, pBars, mcnt_bars, per, win, LineR, LineG, LineB; 
string   short_name, hex;
long pTime;
double   Q[60], I[60], Real[60], Imag[60], Ampl[60], DB[60], OldI[60], OlderI[60], OldQ[60], OlderQ[60], 
         OldReal[60], OlderReal[60], OldImag[60], OlderImag[60], OldDB[60], Raster[51],OldRaster[51]; 
double   FuzzWidth = 0.2;

char* CoronaSwingPosition (char* timeframe)
{
    static char timeframee[1000];
    strncpy(timeframee, timeframe, 1000);
    TimeFrame=atoi(timeframee);
    // Put your indicator C++ code here
int limit, y, i, shift, n, cnt_bars=1000; //IndicatorCounted(); 
   arrayofdoubles price, mDomCyc, DC, SmoothHP, HP, mPsn, Lead60, BP2;
price.assign(0);
mDomCyc.assign(0);
DC.assign(0);
SmoothHP.assign(0);
HP.assign(0);
mPsn.assign(0);
Lead60.assign(0);
BP2.assign(0);
double dB;
double Width;
   
   double pi = 4 * atan(1);
   
   //win = WindowFind(short_name);
      
   //if(TimeFrame!=Period()) int mBars = iBars(NULL,TimeFrame); else mBars = Bars; 
   int mBars = 666; //chartbars[displayedfile];  
   /*
   if(mBars != pBars)
   {
   ArrayResize(price,mBars);
   ArrayResize(mDomCyc,mBars);
   ArrayResize(DC,mBars);
   ArrayResize(SmoothHP,mBars);
   ArrayResize(HP,mBars);
   ArrayResize(mPsn,mBars);
   ArrayResize(Lead60,mBars);
   ArrayResize(BP2,mBars);   
      if(Price > 6 && Price <= 10)
      {
      ArrayResize(haClose,mBars);
      ArrayResize(haOpen,mBars);
      ArrayResize(haHigh,mBars);
      ArrayResize(haLow,mBars);
      }
  
   pBars = mBars;
   } 
*/ 
   pBars = mBars;

   if(cnt_bars<1)
   {
      //for(i=bars-1;i>0;i--) CoronaSwingPositionbuffer[i]=0;
	for(i=666-1;i>0;i--) CoronaSwingPositionbuffer[i]=0;
   mcnt_bars = 0;
   }
CoronaSwingPositionbuffer.assign(0);

//---- 
   if(mcnt_bars > 0) mcnt_bars--;
   
   //for(y=mcnt_bars+1;y<mBars;y++)
   for(y=0;y<mBars;y++)
   {
      if(Price <= 6) price[y] = ima(TimeFrame,1,0,0,Price,mBars-y-1);   
      else
      if(Price > 6 && Price <= 10) price[y] = HeikenAshi(TimeFrame,Price-7,mBars-y-1);
     
   double alpha1 = (1 - sin(2*pi/30)) / cos(2*pi/30);
   HP[y] = 0.5*(1 + alpha1)*(price[y] - price[y-1]) + alpha1*HP[y-1];
   SmoothHP[y] = (HP[y] + 2.0*HP[y-1] + 3.0*HP[y-2] + 3.0*HP[y-3] + 2.0*HP[y-4] + HP[y-5]) / 12.0;
   if(y < 6)  SmoothHP[y] = price[y] - price[y-1];
   if(y == 0) SmoothHP[y] = 0;
   
   double delta = -0.015*(y+1) + 0.5;
   if(delta < 0.1) delta = 0.1;
   
      if(y > 11)
      {
         if(itimeb(TimeFrame,mBars-y-1) != pTime)
         {
            for(n = 11; n<= 59; n++)
            { 
            OlderI[n] = OldI[n];
            OldI[n] = I[n];
            OlderQ[n] = OldQ[n];
            OldQ[n] = Q[n];
            OlderReal[n] = OldReal[n];
            OldReal[n] = Real[n];
            OlderImag[n] = OldImag[n];
            OldImag[n] = Imag[n];
            OldDB[n] = DB[n];
            }
         pTime = itimeb(TimeFrame,mBars-y-1);
         }
         
         for(n = 11; n<= 59; n++)
         { 	
         double beta = cos(4*pi/(n+1));
         double gamma = 1.0/cos(8*pi*delta/(n+1));
         double alpha = gamma - sqrt(gamma*gamma - 1);
         Q[n] = ((n+1)/4/pi)*(SmoothHP[y] - SmoothHP[y-1]);
         I[n] = SmoothHP[y];
         Real[n] = 0.5*(1 - alpha)*(I[n] - OlderI[n]) + beta*(1 + alpha)*OldReal[n] - alpha*OlderReal[n];
         Imag[n] = 0.5*(1 - alpha)*(Q[n] - OlderQ[n]) + beta*(1 + alpha)*OldImag[n] - alpha*OlderImag[n];
         Ampl[n] = (Real[n]*Real[n] + Imag[n]*Imag[n]);
         }	  
      
      MaxAmpl = Ampl[11];
      for(n = 11; n<= 59; n++) 
         if(Ampl[n] > MaxAmpl) {MaxAmpl = Ampl[n]; int nmax = n;}
   
         for(n = 11; n<= 59; n++)
         {
         if(MaxAmpl != 0) 
            if (Ampl[n] / MaxAmpl > 0) dB = -10.0*log(0.01/(1 - 0.99*Ampl[n]/MaxAmpl))/log(10.0);
         
         DB[n] = 0.33*dB + 0.67*OldDB[n];
         if(DB[n] > 20) DB[n] = 20;
         }   
         
         double Num = 0;
         double Denom = 0;
         for(n = 11; n<= 59; n++)
         {
            if(DB[n] <= 6) 
            {  
            Num = Num + (n+1)*(20 - DB[n]);
            Denom = Denom + (20 - DB[n]);
            }      
                 
         if(Denom != 0) DC[y] = 0.5*Num / Denom;
         else DC[y] = DC[y-1];
         }
      mDomCyc[y] = Median(DC, 5, y); 
      if(mDomCyc[y] < 6) mDomCyc[y] = 6; 
      
      double delta2 = 0.1;
      double beta2 = cos(2*pi/mDomCyc[y]);
      double gamma2 = 1.0/cos(4*pi*delta2/mDomCyc[y]);
      double alpha2 = gamma2 - sqrt(gamma2*gamma2 - 1);
      BP2[y] = 0.5*(1 - alpha2)*(price[y] - price[y-2]) + beta2*(1 + alpha2)*BP2[y-1] - alpha2*BP2[y-2];
      double Q2 = (mDomCyc[y]/2/pi)*(BP2[y] - BP2[y-1]);
      Lead60[y] = 0.5*BP2[y] + 0.866*Q2;

         double HL = Lead60[y];
         double LL = Lead60[y];
         for (i = 0; i<=50; i++)
         {
         if(Lead60[y-i] > HL) HL = Lead60[y-i];
         if(Lead60[y-i] < LL) LL = Lead60[y-i];
         }
      
      if((HL - LL) != 0) mPsn[y] = (Lead60[y] - LL)/(HL - LL);
      
         HL = mPsn[y];
         LL = mPsn[y];
         for (i = 0; i<=20; i++)
         { 
         if(mPsn[y-i] > HL) HL = mPsn[y-i];
	      if(mPsn[y-i] < LL) LL = mPsn[y-i];
         }
       
      if((HL - LL) > 0.85) Width = 0.01; else Width = 0.15*(HL - LL);	
      
         for(n = 1; n<= 50; n++)
         {
         Raster[n] = 20;
	      if(n <  round(50*mPsn[y]) && Width > 0) Raster[n] = 0.5*(pow(( 20*mPsn[y] - 0.4*n)/Width,0.95) + 0.5*OldRaster[n]);
	      if(n >  round(50*mPsn[y]) && Width > 0) Raster[n] = 0.5*(pow((-20*mPsn[y] + 0.4*n)/Width,0.95) + 0.5*OldRaster[n]);
	      if(n == round(50*mPsn[y])) Raster[n] = 0.5*OldRaster[n];
	  	   if(Raster[n] <   0) Raster[n] =  0;
	      if(Raster[n] >  20) Raster[n] = 20;
	      if((HL - LL) > 0.8) Raster[n] = 20;
	      OldRaster[n] = Raster[n];
         }
      }      
   
   //if(TimeFrame == Period() && VisualMode != 2) Psn[mBars-y-1] = 10*mPsn[y] - 5;
CoronaSwingPositionbuffer[mBars-y-1] = 10*mPsn[y] - 5;
   
   /*
   if(VisualMode != 1 && ((CoronaBars > 0 && y > mBars - CoronaBars)||(CoronaBars == 0 && y > draw_begin)))
      for(n = 1; n<= 50; n++)
      {
         if(Raster[n] <= 10)
         {
         int Color1 = LineR + Raster[n]*(FuzzR - LineR) / 10.0;
         int Color2 = LineG + Raster[n]*(FuzzG - LineG) / 10.0;
		   int Color3 = LineB + Raster[n]*(FuzzB - LineB) / 10.0;
         }
         else
         if(Raster[n] > 10)
         {
         Color1 = FuzzR*(2 - Raster[n] / 10.0);
         Color2 = FuzzG*(2 - Raster[n] / 10.0);
		   Color3 = FuzzB*(2 - Raster[n] / 10.0);
         }
      
     
      Plot(TimeFrame,FuzzWidth*n - 5 - 0.5*FuzzWidth,win+"CSP"+n+"_"+y, RGB(Color1, Color2, Color3),FuzzWidth,mBars-y-1);
      }   
   
   */
   
   
   mcnt_bars = mBars-1;
   }
   /*
   if(TimeFrame > Period() && VisualMode != 2)
   { 
      if(cnt_bars>0) cnt_bars--;
      limit = bars-cnt_bars+TimeFrame/Period()-1;
      
      for(shift=0,y=0;shift<limit;shift++)
      {
      if (Time[shift] < iTime(NULL,TimeFrame,y)) y++; 
      CoronaSwingPositionbuffer[shift] = 10* mPsn[mBars-y-1] - 5;
      }
   }
*/
//----------   
   //WindowRedraw();
   return(0);
}




//+------------------------------------------------------------------+
//| Custom indicator initialization function                         |
//+------------------------------------------------------------------+
/*
int init()
{
   //hex = IntegerToHexString(LineColor);
//----
   //LineR = LineColor&0x000000FF;
   //LineG = (LineColor>>8)&0x000000FF;
   //LineB = (LineColor>>16)&0x000000FF;
//---- 
   SetIndexStyle(0,DRAW_LINE);

   if(TimeFrame == 0 || TimeFrame < Period()) TimeFrame = Period();
   per = 30;   
   draw_begin=2*per*TimeFrame/Period();
//---- 
   switch(TimeFrame)
   {
   case 1     : string TF = "M1"; break;
   case 5     : TF = "M5"; break;
   case 15    : TF = "M15"; break;
   case 30    : TF = "M30"; break;
   case 60    : TF = "H1"; break;
   case 240   : TF = "H4"; break;
   case 1440  : TF = "D1"; break;
   case 10080 : TF = "W1"; break;
   case 43200 : TF = "MN1"; break;
   default    : TF = "Current";
   } 
   short_name = "CoronaSwingPosition_v2.1 ["+TF+"] ("+Price+")";
   IndicatorShortName(short_name);
   SetIndexLabel(0,"Swing Psn");
  
   SetIndexDrawBegin(0,draw_begin);
//---- 
   SetIndexBuffer(0,Psn);
//---- 
   
   return(0);
}

//----  
void deinit()
{ 
   ObjectsDeleteAll(win,OBJ_RECTANGLE);  
  
   return(0);
}


//+------------------------------------------------------------------+
//| CoronaSwingPosition_v2                                           |
//+------------------------------------------------------------------+
int start()
{
   
}
*/

double Median(arrayofdoubles price,int per,int bar)
{
double median;
   //double array[per];
std::vector<double> array (per,0);
   //ArrayResize(array,per);
   
   for(int i = 0; i < per;i++) array[i] = price[bar-i];
   //ArraySort(array);
std::sort(array.begin(), array.end());
   
   int num = round((per-1)/2); 
   if((per % 2)>0) median = array[num]; else median = 0.5*(array[num]+array[num+1]);
   
   return(median); 
}

double HeikenAshi(int tf,int price,int bar)
{ 
   //if(bar == iBars(NULL,TimeFrame)- 1) 
//if(bar == chartbars[displayedfile]- 1) 
if(bar == 666- 1) 
   {
   haClose[bar] = iclose(tf,bar);
   haOpen[bar]  = iopen(tf,bar);
   haHigh[bar]  = ihigh(tf,bar);
   haLow[bar]   = ilow(tf,bar);
   }
   else
   {
   haClose[bar] = (iopen(tf,bar)+ihigh(tf,bar)+ilow(tf,bar)+iclose(tf,bar))/4;
   haOpen[bar]  = (haOpen[bar+1]+haClose[bar+1])/2;
   haHigh[bar]  = mathmax(ihigh(tf,bar),mathmax(haOpen[bar], haClose[bar]));
   haLow[bar]   = mathmin(ilow(tf,bar),mathmin(haOpen[bar], haClose[bar]));
   }
   
   switch(price)
   {
   case 0: return(haClose[bar]);break;
   case 1: return(haOpen[bar]);break;
   case 2: return(haHigh[bar]);break;
   case 3: return(haLow[bar]);break;
   }
}     

//int RGB(int R, int G, int B)
//{
   //return (256*(256*B + G) + R);
//}


//void Plot(int tf,double value,string name,color clr,double width,int bar)
//{   
//   ObjectCreate(name,OBJ_RECTANGLE,win,iTime(NULL,tf,bar+1),value-0.5*width,iTime(NULL,tf,bar),value+0.5*width);
//   ObjectSet(name,OBJPROP_COLOR,clr);
//}

/*
string IntegerToHexString(int integer_number)
{
   string hex_string="00000000";
   int    value, shift=28;
//----
   for(int i=0; i<8; i++)
     {
      value=(integer_number>>shift)&0x0F;
      if(value<10) hex_string=StringSetChar(hex_string, i, value+'0');
      else         hex_string=StringSetChar(hex_string, i, (value-10)+'A');
      shift-=4;
     }
//----
   return(hex_string);
}
*/
