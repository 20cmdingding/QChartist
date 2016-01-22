/*
//+------------------------------------------------------------------+
//|                                                     Ichimoku.mq4 |
//|                      Copyright © 2004, MetaQuotes Software Corp. |
//|                                       http://www.metaquotes.net/ |
//+------------------------------------------------------------------+
#property copyright "Copyright © 2004, MetaQuotes Software Corp."
#property link      "http://www.metaquotes.net/"

#property indicator_chart_window
#property indicator_buffers 7
#property indicator_color1 Red
#property indicator_color2 Blue
#property indicator_color3 SandyBrown
#property indicator_color4 Thistle
#property indicator_color5 Lime
#property indicator_color6 SandyBrown
#property indicator_color7 Thistle
*/

/*
//+------------------------------------------------------------------+
//| Custom indicator initialization function                         |
//+------------------------------------------------------------------+
int init()
  {
//----
   SetIndexStyle(0,DRAW_LINE);
   SetIndexBuffer(0,Tenkan_Buffer);
   SetIndexDrawBegin(0,Tenkan-1);
   SetIndexLabel(0,"Tenkan Sen");
//----
   SetIndexStyle(1,DRAW_LINE);
   SetIndexBuffer(1,Kijun_Buffer);
   SetIndexDrawBegin(1,Kijun-1);
   SetIndexLabel(1,"Kijun Sen");
//----
   a_begin=Kijun; if(a_begin<Tenkan) a_begin=Tenkan;
   SetIndexStyle(2,DRAW_HISTOGRAM,STYLE_DOT);
   SetIndexBuffer(2,SpanA_Buffer);
   SetIndexDrawBegin(2,Kijun+a_begin-1);
   SetIndexShift(2,Kijun);
   SetIndexLabel(2,NULL);
   SetIndexStyle(5,DRAW_LINE,STYLE_DOT);
   SetIndexBuffer(5,SpanA2_Buffer);
   SetIndexDrawBegin(5,Kijun+a_begin-1);
   SetIndexShift(5,Kijun);
   SetIndexLabel(5,"Senkou Span A");
//----
   SetIndexStyle(3,DRAW_HISTOGRAM,STYLE_DOT);
   SetIndexBuffer(3,SpanB_Buffer);
   SetIndexDrawBegin(3,Kijun+Senkou-1);
   SetIndexShift(3,Kijun);
   SetIndexLabel(3,NULL);
   SetIndexStyle(6,DRAW_LINE,STYLE_DOT);
   SetIndexBuffer(6,SpanB2_Buffer);
   SetIndexDrawBegin(6,Kijun+Senkou-1);
   SetIndexShift(6,Kijun);
   SetIndexLabel(6,"Senkou Span B");
//----
   SetIndexStyle(4,DRAW_LINE);
   SetIndexBuffer(4,Chinkou_Buffer);
   SetIndexShift(4,-Kijun);
   SetIndexLabel(4,"Chinkou Span");
//----
   return(0);
  }
*/

static arrayofdoubles Tenkan_Buffer; // This line of code must stay here.
static arrayofdoubles Kijun_Buffer;
static arrayofdoubles SpanA_Buffer;
static arrayofdoubles SpanB_Buffer;
static arrayofdoubles Chinkou_Buffer;
static arrayofdoubles SpanA2_Buffer;
static arrayofdoubles SpanB2_Buffer;

char* Ichimoku (char* period)
{
    static char periodd[1000];
    strncpy(periodd, period, 1000);
    int intperiod=atoi(periodd);
    // Put your indicator C++ code here
        
//---- input parameters
int Tenkan=9;
int Kijun=26;
int Senkou=52;
//---- buffers
//double Tenkan_Buffer[];
//double Kijun_Buffer[];
//double SpanA_Buffer[];
//double SpanB_Buffer[];
//double Chinkou_Buffer[];
//double SpanA2_Buffer[];
//double SpanB2_Buffer[];
//----
int a_begin;
a_begin=Kijun; if(a_begin<Tenkan) a_begin=Tenkan;

//+------------------------------------------------------------------+
//| Ichimoku Kinko Hyo                                               |
//+------------------------------------------------------------------+

   int    i,k;
   int    counted_bars=cntbarsedit; //IndicatorCounted();
   double high2,low2,price2;
   int Bars=333;
//----
   if(Bars<=Tenkan || Bars<=Kijun || Bars<=Senkou) return(0);
//---- initial zero
   if(counted_bars<1)
     {
      for(i=1;i<=Tenkan;i++)    Tenkan_Buffer[Bars-i]=0;
      for(i=1;i<=Kijun;i++)     Kijun_Buffer[Bars-i]=0;
      for(i=1;i<=a_begin;i++) { SpanA_Buffer[Bars-i]=0; SpanA2_Buffer[Bars-i]=0; }
      for(i=1;i<=Senkou;i++)  { SpanB_Buffer[Bars-i]=0; SpanB2_Buffer[Bars-i]=0; }
     }
//---- Tenkan Sen
   i=Bars-Tenkan;
   if(counted_bars>Tenkan) i=Bars-counted_bars-1;
   i=Bars;
   while(i>=0)
     {
      high2=higha[i]; low2=lowa[i]; k=i-1+Tenkan;
      while(k>=i)
        {
         price2=higha[k];
         if(high2<price2) high2=price2;
         price2=lowa[k];
         if(low2>price2)  low2=price2;
         k--;
        }
      Tenkan_Buffer[i]=(high2+low2)/2;
      i--;
     }
//---- Kijun Sen
   i=Bars-Kijun;
   if(counted_bars>Kijun) i=Bars-counted_bars-1;
   i=Bars;
   while(i>=0)
     {
      high2=higha[i]; low2=lowa[i]; k=i-1+Kijun;
      while(k>=i)
        {
         price2=higha[k];
         if(high2<price2) high2=price2;
         price2=lowa[k];
         if(low2>price2)  low2=price2;
         k--;
        }
      Kijun_Buffer[i]=(high2+low2)/2;
      i--;
     }
//---- Senkou Span A
   i=Bars-a_begin+1;
   if(counted_bars>a_begin-1) i=Bars-counted_bars-1;
   i=Bars;
   while(i>=0)
     {
      price2=(Kijun_Buffer[i]+Tenkan_Buffer[i])/2;
      SpanA_Buffer[i-Kijun]=price2;
      SpanA2_Buffer[i-Kijun]=price2;
      i--;
     }
//---- Senkou Span B
   i=Bars-Senkou;
   if(counted_bars>Senkou) i=Bars-counted_bars-1;
   i=Bars;
   while(i>=0)
     {
      high2=higha[i]; low2=lowa[i]; k=i-1+Senkou;
      while(k>=i)
        {
         price2=higha[k];
         if(high2<price2) high2=price2;
         price2=lowa[k];
         if(low2>price2)  low2=price2;
         k--;
        }
      price2=(high2+low2)/2;
      SpanB_Buffer[i-Kijun]=price2;
      SpanB2_Buffer[i-Kijun]=price2;
      i--;
     }
//---- Chinkou Span
   i=Bars-1;
   if(counted_bars>1) i=Bars-counted_bars-1;
   i=Bars;
   while(i>=0) { Chinkou_Buffer[i+Kijun]=closea[i]; i--; }
//----
   return(0);
//+------------------------------------------------------------------+

}




