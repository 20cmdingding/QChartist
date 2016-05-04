//+------------------------------------------------------------------+
//|            © 2006, tageiger, aka fxid10t@yahoo.com (Todd Geiger) |
//|                       	  Past Regression Deviated indicator |
//|					       for QC by Julien Moog |
//+------------------------------------------------------------------+

//#property indicator_separate_window
//#property indicator_buffers 12
//#property indicator_color1 White
//#property indicator_color2 White
//#property indicator_color3 White
//#property indicator_color4 Orange
//#property indicator_color5 Orange
//#property indicator_color6 White
//#property indicator_color7 White

//---- indicator buffers
static arrayofdoubles prd_meanBuffer;
static arrayofdoubles prd_high1Buffer;
static arrayofdoubles prd_low1Buffer;
static arrayofdoubles prd_high2Buffer;
static arrayofdoubles prd_low2Buffer;
static arrayofdoubles prd_high3Buffer;
static arrayofdoubles prd_low3Buffer;
static arrayofdoubles prd_Linearregressiontrendline;

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

char* past_regression_deviated (char* period2)
{
/*
if (chartbars[displayedfile]<2000) {
sprintf(debugmsg,"%s","Not enough bars to load the indicator");
MessageBox( NULL, debugmsg,"Debug",MB_OK);
return (0);
}
if (cntbarsedit<2000) {
sprintf(debugmsg,"%s","Please set counted bars to 2000 for the prd indicator. However, other indicators may not work with this value, that's why you should use prd alone. Don't forget to put counted bars back to 1000 after using this indicator!");
MessageBox( NULL, debugmsg,"Debug",MB_OK);
return (0);
}
*/

int p1=5;

int period=0;
/*default 0 means the channel will use the open time from "x" bars back on which ever time period 
the indicator is attached to.  one can change to 1,5,15,30,60...etc to "lock" the start time to a specific 
period, and then view the "locked" channels on a different time period...*/

int LRlength=225;   // bars back regression begins
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
// Past Regression Deviated   
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
      c=sumx2*n-sumx*sumx;
      if(c==0.0) return 0;
      b=(sumxy*n-sumx*sumy)/c;
      a=(sumy-sumx*b)/n;
      double LRprice2=a;
      double LRprice1=a+b*n;
      //mean.Buffer[i]=NormalizeDouble(LR.price.2,Digits);
      prd_meanBuffer[i]=LRprice2;
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
prd_high1Buffer[i]=prd_meanBuffer[i]+(stdchannel1*stddev);
prd_low1Buffer[i]=prd_meanBuffer[i]-(stdchannel1*stddev);
prd_high2Buffer[i]=prd_meanBuffer[i]+(stdchannel2*stddev);
prd_low2Buffer[i]=prd_meanBuffer[i]-(stdchannel2*stddev);
prd_high3Buffer[i]=prd_meanBuffer[i]+(stdchannel3*stddev);//max.dev;
prd_low3Buffer[i]=prd_meanBuffer[i]-(stdchannel3*stddev);//max.dev;
}    

return(0);
}
//+------------------------------------------------------------------+