//+------------------------------------------------------------------+
//|                                                         TSCD.mq4 |
//|                                         Copyright © 2007 Mulyadi |
//| Time Series Convergen Divergen                                   |
//| indi ini menunjukkan  Conv.Div. dari 2 TSF                       |
//| Enter price , diatur oleh BarS & BarC                            |
//| BarS : jumlah total seleksi Bars                                 |
//| BarC : Bar patokan harga                                         |
//| Test aja supaya mengerti                                         |
//| Test it, you'll love it
//+------------------------------------------------------------------+
/*
#property copyright "Copyright © 2007 Mulyadi Santoso"
#property link      "musanto@yahoo.com"
#property indicator_separate_window
#property indicator_buffers 2
#property indicator_color1 Red
#property indicator_width1 4
#property indicator_color2 DodgerBlue
#property indicator_width2 2

#define MaxMarkHL 50


//+------------------------------------------------------------------+
//| Custom indicator initialization function                         |
//+------------------------------------------------------------------+


int init()
  {
//---- indicators
   SetIndexStyle(0,DRAW_HISTOGRAM);
   SetIndexBuffer(0,CdBuffer);
   SetIndexStyle(1,DRAW_LINE);
   SetIndexBuffer(1,MaBuffer);
   IndicatorShortName("TSCD");
   SetIndexLabel(0,"TSCD");   
   SetIndexLabel(1,"MA");   
   awal=true;FlagMaxMarkHL=false;
   MarkHL = 0;lastLo=0;lastHi=0;
//----
   return(0);
  }

//+------------------------------------------------------------------+
//| Custom indicator deinitialization function                       |
//+------------------------------------------------------------------+
int deinit()
  {   string st;
//----
   if (FlagMaxMarkHL) MarkHL=MaxMarkHL;
   for (int i=MarkHL;i>=0;i--)
   {
      st = "Mark"+StringTrimRight(DoubleToStr(i,0));
      ObjectDelete(st);
   }   
//----
   return(0);
  }
*/
double Lreg(int, int, int);
static arrayofdoubles TSCDbuffer; // This line of code must stay here.
//+------------------------------------------------------------------+
//| Custom indicator iteration function                              |
//+------------------------------------------------------------------+
char* TSCD (char* curtf)
{
    static char curtff[1000];
    strncpy(curtff, curtf, 1000);
    int intcurtf=atoi(curtff);

//---- input parameters
int        TSFfast      =  20;
int        TSFslow      =  220;
int        TSFma1       =  5;
int        maxbar       =  300;
int       MarkEnable   = 1; 
int        BarS         =  4;
int        BarC         =  50;

//---- buffers
//double CdBuffer[];
arrayofdoubles MaBuffer;

int awal,FlagMaxMarkHL;
double   sigma;
double   MarkHL;
long lastHi,lastLo;

awal=1;FlagMaxMarkHL=0;
   MarkHL = 0;lastLo=0;lastHi=0;

   int      counted_bars=cntbarsedit;
   int      limit,i;
   int Bars=333;

//----
   
   
   if (awal) 
   {  
      limit = maxbar ;
   } else
      limit = Bars - counted_bars;
   
   for (i=limit;i>=0;i--)
   {  
      TSCDbuffer[i] = Lreg(i,i+TSFfast-1,intcurtf)-Lreg(i,i+TSFslow-1,intcurtf);
      if (awal && limit-i <TSFma1) 
      {
         MaBuffer[i]=0;  
      }
      else 
      {  MaBuffer[i] = imaonarray(TSCDbuffer,0,TSFma1,i,MODE_SMA,0);
         if (  TSCDbuffer[i]>0.0 
            && MarkEnable
            && MaBuffer[i]>TSCDbuffer[i]
            && MaBuffer[i+1]<=TSCDbuffer[i+1]
            && higha[ihighest(intcurtf,MODE_HIGH,BarS,i)]> higha[ihighest(intcurtf,MODE_HIGH,BarC,i+BarS)]
            && timeb(i) > lastHi+60*60
            )
            {
               //MarkHi(i);
               lastHi = timeb(i);
            }
         if (  TSCDbuffer[i]<0.0 && MaBuffer[i]<TSCDbuffer[i]
            && MarkEnable
            && MaBuffer[i+1]>=TSCDbuffer[i+1]
            && lowa[ilowest(intcurtf,MODE_LOW,BarS,i)]<=lowa[ilowest(intcurtf,MODE_LOW,BarC,i+BarS)]
            && timeb(i)>lastLo+60*60
            )
            {
               //MarkLo(i);
               lastLo = timeb(i);
            }
      }     
   }
   awal=0;
   
//----
   return(0);
  }
//+------------------------------------------------------------------+
double Lreg(int st0, int st1, int curtf)
{ double    Sx=0,Sxx=0,Sxy=0,Sy;
  double    Beta,Alfa,x,y,c,rv;
  int       i,n;

  rv = 0.0;
  n = st1 - st0 + 1 ;                       //int n=m_pos[1]-m_pos[0]+1;
  Sy  = (iopen(curtf,st0)+ihigh(curtf,st0)+ilow(curtf,st0)+
            iclose(curtf,st0))/4;          //double sumy=value;
  //Sy  = iclose(curtf,st0);          //double sumy=value;
  
  Sx  = 0.0;                                // double sumx=0.0;
  Sxy = 0.0;                                // double sumxy=0.0;
  Sxx = 0.0;                                // double sumx2=0.0;
  for (i=1;i<n;i++)                         //for(i=1; i<n; i++)
  {  
     x   = i;   
     y   = (iopen(curtf,st0+i)+ihigh(curtf,st0+i)+ilow(curtf,st0+i)+
            iclose(curtf,st0+i))/4;    //value  = Close[m_pos[0]+i];
     //y  = iclose(NULL,0,st0+i);          //double sumy=value;
     Sx  = Sx + x;                          //sumx+  = i;
     Sy  = Sy + y;                          //sumy+  = value
     Sxx = Sxx + (x* x);                    //sumx2+ = i*i
     Sxy = Sxy + (x* y);                    //sumxy+ = value*i;
  }
  c    = Sxx*n - Sx * Sx;                   //c=sumx2*n-sumx*sumx;
  if (c==0.0) return(0);                     //if(c==0.0) return;
  Beta = (n*Sxy-Sx*Sy)/c;                   //b=(sumxy*n-sumx*sumy)/c;
  Alfa = (Sy-Beta*Sx)/n;                    //a=(sumy-sumx*b)/n;
  rv = Alfa;       
   return(rv);
}
/*
void  MarkLo(int i)
{  string   st;
   st = "Mark"+StringTrimRight(DoubleToStr(MarkHL,0));MarkHL++;
   if (MarkHL>50) {MarkHL=0;FlagMaxMarkHL=true;}
   ObjectCreate(st,OBJ_ARROW,0,0,0);
   ObjectSet(st,OBJPROP_TIME1,Time[i]);
   ObjectSet(st,OBJPROP_PRICE1,Low[iLowest(NULL,0,MODE_LOW,BarS,i)]);
   ObjectSet(st,OBJPROP_ARROWCODE,241);
   ObjectSet(st,OBJPROP_COLOR,Red);
   ObjectCreate("comment_label",OBJ_LABEL,0,0,0);
   ObjectSet("comment_label",OBJPROP_XDISTANCE,5);
   ObjectSet("comment_label",OBJPROP_YDISTANCE,50);
   ObjectSetText("comment_label","BULL ",8,"Arial",Lime);
   if (i == 0)
   {
   Alert("TSCD buy: ",Symbol()," ",Period(),"");
   }
}

void  MarkHi(int i)

{  string   st;
   st = "Mark"+StringTrimRight(DoubleToStr(MarkHL,0));MarkHL++;
   if (MarkHL>50) {MarkHL=0;FlagMaxMarkHL=true;}
   ObjectCreate(st,OBJ_ARROW,0,0,0);
   ObjectSet(st,OBJPROP_TIME1,Time[i]);
   ObjectSet(st,OBJPROP_PRICE1,High[iHighest(NULL,0,MODE_HIGH,BarS,i)]+8*Point);
   ObjectSet(st,OBJPROP_ARROWCODE,242);
   ObjectSet(st,OBJPROP_COLOR,Red);
   ObjectCreate("comment_label",OBJ_LABEL,0,0,0);
   ObjectSet("comment_label",OBJPROP_XDISTANCE,5);
   ObjectSet("comment_label",OBJPROP_YDISTANCE,50);
   ObjectSetText("comment_label","BEAR ",8,"Arial",Red);
   if (i == 0)
   {
   Alert("TSCD sell: ",Symbol()," ",Period(),""); 
   }
}
*/


