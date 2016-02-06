//+------------------------------------------------------------------+
//|                                                     FTVCPRDL.mq4 |
//|        Fisher Transform Value Chart Past Regression Deviated Log |
//|                               Copyright © 2009-2010, Julien Moog |
//|                                          julien.moog@lapsote.net |
//|                                                      Credits to: |
//|            © 2006, tageiger, aka fxid10t@yahoo.com (Todd Geiger) |
//|                             Mark W. Helweg and David C. Stendahl |
//|                                Smallcaps90 http://www.pro-at.com |
//|                         Copyright © 2005, Luis Guilherme Damiani |
//|                                      http://www.damianifx.com.br |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+

// Still buggy

//#property indicator_separate_window
//#property indicator_buffers 12
//#property indicator_color1 White
//#property indicator_color2 White
//#property indicator_color3 White
//#property indicator_color4 White
//#property indicator_color5 White
//#property indicator_color6 White
//#property indicator_color7 White
//#property indicator_color8 Lime
//#property indicator_color9 Red
//#property indicator_color10 Red
//#property indicator_color11 Magenta
//#property indicator_color12 Lime
//Limites des surachats et des surventes
//#property  indicator_level1  8
//#property  indicator_level2  4
//#property  indicator_level3  -4
//#property  indicator_level4  -8

static arrayofdoubles vo;
static arrayofdoubles vh;
static arrayofdoubles vb;
static arrayofdoubles vc;

//---- indicator buffers
static arrayofdoubles meanBuffer;
static arrayofdoubles high1Buffer;
static arrayofdoubles low1Buffer;
static arrayofdoubles high2Buffer;
static arrayofdoubles low2Buffer;
static arrayofdoubles high3Buffer;
static arrayofdoubles low3Buffer;
static arrayofdoubles AuxBuffer;
static arrayofdoubles Linearregressiontrendline;

static arrayofdoubles Line1Buffer;
static arrayofdoubles Line2Buffer;
static arrayofdoubles Line3Buffer;

static arrayofdoubles steplevelup;
static arrayofdoubles stepleveldn;

/*
int init()  {
//---- line shifts when drawing
   SetIndexShift(0,JawsShift);
   SetIndexShift(1,TeethShift);
   SetIndexShift(2,LipsShift);
//---- first positions skipped when drawing
   SetIndexDrawBegin(0,LR.length);
   SetIndexDrawBegin(1,LR.length);
   SetIndexDrawBegin(2,LR.length);
   SetIndexDrawBegin(3,LR.length);
   SetIndexDrawBegin(4,LR.length);
   SetIndexDrawBegin(5,LR.length);
   SetIndexDrawBegin(6,LR.length);
//---- 3 indicator buffers mapping
   SetIndexBuffer(0,mean.Buffer);
   SetIndexBuffer(1,high.1.Buffer);
   SetIndexBuffer(2,low.1.Buffer);
   SetIndexBuffer(3,high.2.Buffer);
   SetIndexBuffer(4,low.2.Buffer);
   SetIndexBuffer(5,high.3.Buffer);
   SetIndexBuffer(6,low.3.Buffer);
//---- drawing settings
   SetIndexStyle(0,DRAW_NONE,0); SetIndexArrow(0,158);
   SetIndexStyle(1,DRAW_NONE,0); SetIndexArrow(1,158);
   SetIndexStyle(2,DRAW_NONE,0); SetIndexArrow(2,158);
   SetIndexStyle(3,DRAW_NONE,0); SetIndexArrow(3,158);
   SetIndexStyle(4,DRAW_NONE,0); SetIndexArrow(4,158);
   SetIndexStyle(5,DRAW_NONE,0); SetIndexArrow(5,158);
   SetIndexStyle(6,DRAW_NONE,0); SetIndexArrow(6,158);
//---- index labels
   SetIndexLabel(0,"mean");
   SetIndexLabel(1,"1st Std up");
   SetIndexLabel(2,"1st Std down");
   SetIndexLabel(3,"2nd Std up");
   SetIndexLabel(4,"2nd Std down");
   SetIndexLabel(5,"3rd Std up");
   SetIndexLabel(6,"3rd Std down");  
   //IndicatorBuffers(4);
   //SetIndexBuffer(7, vo);
   SetIndexBuffer(7, vc);
   SetIndexStyle(7, DRAW_LINE, STYLE_SOLID, 1);    
   //SetIndexDrawBegin(7, p1);
   //SetIndexBuffer(8, vh);
   //SetIndexStyle(8, DRAW_LINE, STYLE_SOLID, 1);    
   //SetIndexDrawBegin(8, p1);
   //SetIndexBuffer(9, vb);
   //SetIndexStyle(9, DRAW_LINE, STYLE_SOLID, 1);    
   //SetIndexDrawBegin(9, p1);
   //SetIndexBuffer(10, vc);
   //SetIndexStyle(10, DRAW_LINE, STYLE_SOLID, 1);    
   //SetIndexDrawBegin(10, p1);    
   //SetIndexStyle(11,DRAW_LINE);
   //SetIndexBuffer(11,AuxBuffer);
   SetLevelValue(0,0.8);
   SetLevelValue(1,-0.8);
   SetLevelValue(2,0);
   ArrayInitialize(AuxBuffer,0); 
   #property indicator_minimum -0.9
   #property indicator_maximum 0.9
//---- initialization done
return(0);
}

int deinit() {
ObjectsDeleteAll(0,OBJ_ARROW);ObjectDelete(period+"m "+LR.length+" TL");
}
*/

char* stepftvcprdl (char* period2)
{
if (chartbars[displayedfile]<2000) {
sprintf(debugmsg,"%s","Not enough bars to load the indicator");
MessageBox( NULL, debugmsg,"Debug",MB_OK);
for (int iii=0;iii<=chartbars[displayedfile];iii++) {
Line1Buffer[iii]=0;
Line2Buffer[iii]=0;
Line3Buffer[iii]=0;
}
return (0);
}
if (cntbarsedit<2000) {
sprintf(debugmsg,"%s","Please set counted bars to 2000 for stepftvcprdl. However, other indicators may not work with this value, that's why you should use stepftvcprdl alone. Don't forget to put counted bars back to 1000 after using this indicator!");
MessageBox( NULL, debugmsg,"Debug",MB_OK);
for (int iii=0;iii<=chartbars[displayedfile];iii++) {
Line1Buffer[iii]=0;
Line2Buffer[iii]=0;
Line3Buffer[iii]=0;
}
return (0);
}
int PeriodRSI=14;
int StepSizeFast=5;
int StepSizeSlow=15;
//extern int HighLow=0;
//---- indicator buffers
    
    
    int p1=5;
//---- input parameters

int period=0;
/*default 0 means the channel will use the open time from "x" bars back on which ever time period 
the indicator is attached to.  one can change to 1,5,15,30,60...etc to "lock" the start time to a specific 
period, and then view the "locked" channels on a different time period...*/

int LRlength=500;   // bars back regression begins
double stdchannel1=1;        // 1st channel
double stdchannel2=2;        // 2nd channel
double stdchannel3=3;        // 3nd channel
int       lenth=10;
int       maxbars=2000;
int bbperiod = 20;
int bbdev = 2;
    
    static char periodd[1000];
    strncpy(periodd, period2, 1000);
    int intperiod=atoi(periodd);
   //ObjectDelete(period+"m "+LR.length+" TL");
   int limit;
   //int counted_bars=IndicatorCounted();
   //if(counted_bars<0) return(-1);
   //if(counted_bars>0) counted_bars--;
   limit=2000; //chartbars[displayedfile]; //2000; //Bars-counted_bars;
// Past Regression Deviated Log   
//---- main loop
int i;
   for(i=0; i<limit; i++) {
//linear regression calculation
      int startbar=i+LRlength, endbar=i;
      int n=startbar-endbar+1;
//---- calculate price values.. Linear regression calculation
      double value=closea[endbar];
      double a,b,c;
      double sumy=value;
      double sumx=0.0;
      double sumxy=0.0;
      double sumx2=0.0;
      for(int ii=1; ii<n; ii++)  {
         value=closea[endbar+ii];
         sumy+=value;
         sumxy+=value*ii;
         sumx+=ii;
         sumx2+=ii*ii; }
      c=log(sumx2)*n-sumx*sumx;
      if(c==0.0) return 0;
      b=(sumxy*n-sumx*sumy)/c;
      a=(sumy-log(sumx)*b)/n;
      double LRprice2=a;
      double LRprice1=a+b*n;
      //mean.Buffer[i]=NormalizeDouble(LR.price.2,Digits);
      meanBuffer[i]=LRprice2;
/*---- maximal deviation calculation (3rd deviation line)
      double maxdev=0;
      double deviation=0;
      double dvalue=a;
      for(int i1=0; i1<n; i1++)   {
         value=closea[end.bar+i1];
         dvalue+=b;
         deviation=fabs(value-dvalue);
         if(maxdev<=deviation) maxdev=deviation; 
	 } */  
//Linear regression trendline
      //ObjectDelete(period+"m "+LR.length+" TL");
      Linearregressiontrendline.assign(0);
      //ObjectCreate(period+"m "+LR.length+" TL",OBJ_TREND,0,Time[start.bar],LR.price.1,Time[end.bar],LR.price.2);
      Linearregressiontrendline[startbar]=LRprice1;
      Linearregressiontrendline[endbar]=LRprice2;
      double range=LRprice2-LRprice1;
      double step=range/(startbar-endbar);
      for (int j=startbar-1;j>endbar;j--)
            {
            Linearregressiontrendline[j]=Linearregressiontrendline[j+1]+step;				
            }
      //ObjectSet(period+"m "+LR.length+" TL",OBJPROP_COLOR,Orange);
      //ObjectSet(period+"m "+LR.length+" TL",OBJPROP_WIDTH,2);
      //ObjectSet(period+"m "+LR.length+" TL",OBJPROP_RAY,false);
//...standard deviation...
      double x=0,xsum=0,xavg=0,xsumsquared=0,stddev=0;
      for(int iii=i; iii<startbar; iii++)    {
         //x=MathAbs(Close[iii]-ObjectGetValueByShift(period+"m "+LR.length+" TL",iii));
         x=fabs(closea[iii]-Linearregressiontrendline[iii]);
         xsumsquared+=(x*x);   }
         stddev=sqrt(xsumsquared/((startbar-endbar)-1));
      //Print("LR.price.1 ",LR.price.1,"  LR.Price.2 ",LR.price.2," std.dev ",std.dev);

//...standard deviation channels...
high1Buffer[i]=meanBuffer[i]+(stdchannel1*stddev);
low1Buffer[i]=meanBuffer[i]-(stdchannel1*stddev);
high2Buffer[i]=meanBuffer[i]+(stdchannel2*stddev);
low2Buffer[i]=meanBuffer[i]-(stdchannel2*stddev);
high3Buffer[i]=meanBuffer[i]+(stdchannel3*stddev);//max.dev;
low3Buffer[i]=meanBuffer[i]-(stdchannel3*stddev);//max.dev;
}

// Value Chart   
   double m1,dvu;   
   //if(Bars<=p1) return(0);
//---- initial zero
/*   if(counted_bars<1)
      {
      for(i=1;i<=p1;i++) 
         {
         vo[Bars-i]=0.0;   
         vh[Bars-i]=0.0;   
         vb[Bars-i]=0.0;   
         vc[Bars-i]=0.0; 	 		           
         }
      }
      */
//----
   //i=Bars-p1-1;
   i=2000; //chartbars[displayedfile]-p1-1; //2000;
   //if(counted_bars>=p1) i=Bars-counted_bars-1;
   while(i>=0)
      {
      //Ligne moyenne sur P1 (=5) jours
      m1=0.5*(high3Buffer[i]+low3Buffer[i]);
      m1=m1+0.5*(high3Buffer[i+1]+low3Buffer[i+1]);
      m1=m1+0.5*(high3Buffer[i+2]+low3Buffer[i+2]);
      m1=m1+0.5*(high3Buffer[i+3]+low3Buffer[i+3]);
      m1=m1+0.5*(high3Buffer[i+4]+low3Buffer[i+4]);
      m1=m1/5; 
      //Dynamic Volatility Units     
      dvu=(high3Buffer[i]-low3Buffer[i]);
      dvu=dvu+(high3Buffer[i+1]-low3Buffer[i+1]);
      dvu=dvu+(high3Buffer[i+2]-low3Buffer[i+2]);
      dvu=dvu+(high3Buffer[i+3]-low3Buffer[i+3]);
      dvu=dvu+(high3Buffer[i+4]-low3Buffer[i+4]);
      dvu=dvu/5;
      dvu=dvu*0.2;
      //Valeurs relatives des ouvertures, des hautes, 
      //des basses et des clotures
      vo[i]=opena[i]-m1;      
      vh[i]=high3Buffer[i]-m1;
      vb[i]=low3Buffer[i]-m1;
      vc[i]=closea[i]-m1;
      //Correction par les DVU
      if (dvu!=0)
         {
         vo[i]=vo[i]/dvu;
         vh[i]=vh[i]/dvu;
         vb[i]=vb[i]/dvu;
         vc[i]=vc[i]/dvu;  
         // Fisher Transform       
         vc[i]=0.5*((vc[i]+4)*12.5/100-0.5)*2+0.5*vc[i+1];
         
         }
      else
         {
         vo[i]=0;
         vh[i]=0;
         vb[i]=0;
         vc[i]=0;    
         // Fisher Transform     
         vc[i]=0.5*((vc[i]+4)*12.5/100-0.5)*2+0.5*vc[i+1];  
               
         }  
      //Autre adaptation possible avec des points
      /* 
      if (vh>l1) pth=vh;
      if (vh>l2 && vh<l1) pmh=vh;
      if (vb<l4) ptb=vb;
      if (vb<l3 && vb>l4) pmb=vb;   
      */ 
      i--;	 	       
      }

// Fisher Transform
//if(counted_bars<0) return(-1);      
      //if(limit>maxbars)limit=maxbars;      
      ////if (limit>Bars-lenth-1)limit=Bars-lenth-1;   
      ////---- 
      //for (int shift = limit; shift>=0;shift--)
      //{
          //AuxBuffer[shift]=0.5*((vc[shift]+4)*12.5/100-0.5)*2+0.5*AuxBuffer[shift+1];                    
       //}
       
int shift,ftrend,strend;
   double fmin0,fmax0,fmin1,fmax1,smin0,smax0,smin1,smax1,RSI0;
limit=2000; //chartbars[displayedfile]-1; //2000;
   
   for(shift=limit;shift>=0;shift--)
   {    
   //RSI0=iRSI(NULL,0,PeriodRSI,PRICE_CLOSE,shift);
   RSI0=(vc[shift]+1)*0.5*100;
   
      fmax0=RSI0+2*StepSizeFast;
      fmin0=RSI0-2*StepSizeFast;
            
      if (RSI0>fmax1)  ftrend=1; 
      if (RSI0<fmin1)  ftrend=-1;

      if(ftrend>0 && fmin0<fmin1) fmin0=fmin1;
      if(ftrend<0 && fmax0>fmax1) fmax0=fmax1;
      
      smax0=RSI0+2*StepSizeSlow;
      smin0=RSI0-2*StepSizeSlow;
        
      if (RSI0>smax1)  strend=1; 
      if (RSI0<smin1)  strend=-1;

      if(strend>0 && smin0<smin1) smin0=smin1;
      if(strend<0 && smax0>smax1) smax0=smax1;
        
      
      Line1Buffer[shift]=RSI0;
      
      if (ftrend>0) Line2Buffer[shift]=fmin0+StepSizeFast;
      if (ftrend<0) Line2Buffer[shift]=fmax0-StepSizeFast;
      
      if (strend>0) Line3Buffer[shift]=smin0+StepSizeSlow;
      if (strend<0) Line3Buffer[shift]=smax0-StepSizeSlow;
      
      fmin1=fmin0;
      fmax1=fmax0;
      smin1=smin0;
      smax1=smax0;

      steplevelup[shift]=80;
      stepleveldn[shift]=20;		
     }       

return(0);
}
//+------------------------------------------------------------------+