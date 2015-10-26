//+------------------------------------------------------------------+
//|                                            Murrey_Math_MT_VG.mq4 |
//|                      Copyright © 2004, MetaQuotes Software Corp. |
//|                                        http://www.metaquotes.net |
//+------------------------------------------------------------------+
//#property copyright "Vladislav Goshkov (VG)."
//#property link      "4vg@mail.ru"

//#property indicator_chart_window

// ============================================================================================
// * Линии 8/8 и 0/8 (Окончательное сопротивление).
// * Эти линии самые сильные и оказывают сильнейшие сопротивления и поддержку.
// ============================================================================================
//* Линия 7/8  (Слабая, место для остановки и разворота). Weak, Stall and Reverse
//* Эта линия слаба. Если цена зашла слишком далеко и слишком быстро и если она остановилась около этой линии, 
//* значит она развернется быстро вниз. Если цена не остановилась около этой линии, она продолжит движение вверх к 8/8.
// ============================================================================================
//* Линия 1/8  (Слабая, место для остановки и разворота). Weak, Stall and Reverse
//* Эта линия слаба. Если цена зашла слишком далеко и слишком быстро и если она остановилась около этой линии, 
//* значит она развернется быстро вверх. Если цена не остановилась около этой линии, она продолжит движение вниз к 0/8.
// ============================================================================================
//* Линии 6/8 и 2/8 (Вращение, разворот). Pivot, Reverse
//* Эти две линии уступают в своей силе только 4/8 в своей способности полностью развернуть ценовое движение.
// ============================================================================================
//* Линия 5/8 (Верх торгового диапазона). Top of Trading Range
//* Цены всех рынков тратят 40% времени, на движение между 5/8 и 3/8 линиями. 
//* Если цена двигается около линии 5/8 и остается около нее в течении 10-12 дней, рынок сказал что следует 
//* продавать в этой «премиальной зоне», что и делают некоторые люди, но если цена сохраняет тенденцию оставаться 
//* выше 5/8, то она и останется выше нее. Если, однако, цена падает ниже 5/8, то она скорее всего продолжит 
//* падать далее до следующего уровня сопротивления.
// ============================================================================================
//* Линия 3/8 (Дно торгового диапазона). Bottom of Trading Range
//* Если цены ниже этой лини и двигаются вверх, то цене будет сложно пробить этот уровень. 
//* Если пробивают вверх эту линию и остаются выше нее в течении 10-12 дней, значит цены останутся выше этой линии 
//* и потратят 40% времени двигаясь между этой линией и 5/8 линией.
// ============================================================================================
//* Линия 4/8 (Главная линия сопротивления/поддержки). Major Support/Resistance
//* Эта линия обеспечивает наибольшее сопротивление/поддержку. Этот уровень является лучшим для новой покупки или продажи. 
//* Если цена находится выше 4/8, то это сильный уровень поддержки. Если цена находится ниже 4/8, то это прекрасный уровень 
//* сопротивления.
// ============================================================================================

/*
//+------------------------------------------------------------------+
//| Custom indicator initialization function                         |
//+------------------------------------------------------------------+
int init() {
//---- indicators
   
   ln_txt[0]  = "                                                        -2/8ExOverSold 2/8";// "extremely overshoot [-2/8]";// [-2/8]
   ln_txt[1]  = "                                                        -1/8OverSold -1/8";// "overshoot [-1/8]";// [-1/8]
   ln_txt[2]  = "                                                         0/8UltSupport 0/8";// "Ultimate Support - extremely oversold [0/8]";// [0/8]
   ln_txt[3]  = "                                                         1/8WeakStallReverse 1/8";// "Weak, Stall and Reverse - [1/8]";// [1/8]
   ln_txt[4]  = "                                                         2/8PivotReverse 2/8";// "Pivot, Reverse - major [2/8]";// [2/8]
   ln_txt[5]  = "                                                         3/8LWRtraderange 3/8";// "Bottom of Trading Range - [3/8], if 10-12 bars then 40% Time. BUY Premium Zone";//[3/8]
   ln_txt[6]  = "                                                         4/8MajorS&R 4/8";// "Major Support/Resistance Pivotal Point [4/8]- Best New BUY or SELL level";// [4/8]
   ln_txt[7]  = "                                                         5/8UPRtraderange 5/8";// "Top of Trading Range - [5/8], if 10-12 bars then 40% Time. SELL Premium Zone";//[5/8]
   ln_txt[8]  = "                                                         6/8PivotReverse 6/8";// "Pivot, Reverse - major [6/8]";// [6/8]
   ln_txt[9]  = "                                                         7/8WeakStallReverse 7/8";// "Weak, Stall and Reverse - [7/8]";// [7/8]
   ln_txt[10] = "                                                         8/8UltResistance 8/8";// "Ultimate Resistance - extremely overbought [8/8]";// [8/8]
   ln_txt[11] = "                                                        +1/8OverBought +1/8";// "overshoot [+1/8]";// [+1/8]
   ln_txt[12] = "                                                        +2/8ExtOverBought +2/8";// "extremely overshoot [+2/8]";// [+2/8]

   mml_shft = 3;
   mml_thk  = 3;

   // Начальная установка цветов уровней октав 
   mml_clr[0]  = Red;    // [-2]/8
   mml_clr[1]  = OrangeRed;  // [-1]/8
   mml_clr[2]  = DodgerBlue;  //  [0]/8
   mml_clr[3]  = Yellow;      //  [1]/8
   mml_clr[4]  = DeepPink;     //  [2]/8
   mml_clr[5]  = Lime;  //  [3]/8
   mml_clr[6]  = DodgerBlue;  //  [4]/8
   mml_clr[7]  = Lime;  //  [5]/8
   mml_clr[8]  = DeepPink;     //  [6]/8
   mml_clr[9]  = Yellow;      //  [7]/8
   mml_clr[10] = DodgerBlue;  //  [8]/8
   mml_clr[11] = OrangeRed;  // [+1]/8
   mml_clr[12] = Red;    // [+2]/8
//----
   return(0);
  }

//+------------------------------------------------------------------+
//| Custor indicator deinitialization function                       |
//+------------------------------------------------------------------+
int deinit() {
//---- TODO: add your code here
Comment(" ");   
for(i=0;i<OctLinesCnt;i++) {
    buff_str = "mml"+i;
    ObjectDelete(buff_str);
    buff_str = "mml_txt"+i;
    ObjectDelete(buff_str);
    }
//----
   return(0);
  }
*/

//+------------------------------------------------------------------+
//| Custom indicator iteration function                              |
//+------------------------------------------------------------------+

static arrayofdoubles Murrey_Mathbuffer1; // This line of code must stay here.
static arrayofdoubles Murrey_Mathbuffer2;
static arrayofdoubles Murrey_Mathbuffer3;
static arrayofdoubles Murrey_Mathbuffer4;
static arrayofdoubles Murrey_Mathbuffer5;
static arrayofdoubles Murrey_Mathbuffer6;
static arrayofdoubles Murrey_Mathbuffer7;
static arrayofdoubles Murrey_Mathbuffer8;
static arrayofdoubles Murrey_Mathbuffer9;
static arrayofdoubles Murrey_Mathbuffer10;
static arrayofdoubles Murrey_Mathbuffer11;
static arrayofdoubles Murrey_Mathbuffer12;
static arrayofdoubles Murrey_Mathbuffer13;

char* Murrey_Math (char* barsback) {

static char barsbackk[1000];
    strncpy(barsbackk, barsback, 1000);
    int intbarsback=atoi(barsbackk);

int limit=intbarsback;
int P = 64;
int StepBack = 0;

double  dmml = 0,
        dvtl = 0,
        sum  = 0,
        v1 = 0,
        v2 = 0,
        mn = 0,
        mx = 0,
        x1 = 0,
        x2 = 0,
        x3 = 0,
        x4 = 0,
        x5 = 0,
        x6 = 0,
        y1 = 0,
        y2 = 0,
        y3 = 0,
        y4 = 0,
        y5 = 0,
        y6 = 0,
        octave = 0,
        Octv = 0,
        fractal = 0,
        range   = 0,
        finalH  = 0,
        finalL  = 0,
        mml[13];

string  ln_txt[13],        
        buff_str = "";
        
int     bn_v1   = 0,
        bn_v2   = 0,
        OctLinesCnt = 13,
        mml_thk = 8,
        mml_clr[13],
        mml_shft = 3,
        nTime = 0,
        CurPeriod = 0,
        nDigits = 0,
        i = 0;

//---- TODO: add your code here

int ii;

for (ii=limit;ii>=0;ii--) {

if( (nTime != datetimeserial[ii]) || (CurPeriod != charttf[displayedfile] ) ) {
   
  //price
   bn_v1 = ilowest(charttf[displayedfile],MODE_CLOSE,P+StepBack,ii);
   bn_v2 = ihighest(charttf[displayedfile],MODE_CLOSE,P+StepBack,ii);

   v1 = lowa[bn_v1];
   v2 = higha[bn_v2];

//determine fractal.....
   if( v2<=250000 && v2>25000 )
    fractal=100000;
   else
     if( v2<=25000 && v2>2500 )
     fractal=10000;
     else
       if( v2<=2500 && v2>250 )
       fractal=1000;
       else
         if( v2<=250 && v2>25 )
         fractal=100;
         else
           if( v2<=25 && v2>12.5 )
           fractal=12.5;
           else
             if( v2<=12.5 && v2>6.25)
             fractal=12.5;
             else
               if( v2<=6.25 && v2>3.125 )
               fractal=6.25;
               else
                 if( v2<=3.125 && v2>1.5625 )
                 fractal=3.125;
                 else
                   if( v2<=1.5625 && v2>0.390625 )
                   fractal=1.5625;
                   else
                     if( v2<=0.390625 && v2>0)
                     fractal=0.1953125;
      
   range=(v2-v1);
   sum=floor(log(fractal/range)/log(2));
   octave=fractal*(pow(0.5,sum));
   mn=floor(v1/octave)*octave;
   if( (mn+octave)>v2 )
   mx=mn+octave;
   else
     mx=mn+(2*octave);


// calculating xx
//x2
    if( (v1>=(3*(mx-mn)/16+mn)) && (v2<=(9*(mx-mn)/16+mn)) )
    x2=mn+(mx-mn)/2; 
    else x2=0;
//x1
    if( (v1>=(mn-(mx-mn)/8))&& (v2<=(5*(mx-mn)/8+mn)) && (x2==0) )
    x1=mn+(mx-mn)/2; 
    else x1=0;

//x4
    if( (v1>=(mn+7*(mx-mn)/16))&& (v2<=(13*(mx-mn)/16+mn)) )
    x4=mn+3*(mx-mn)/4; 
    else x4=0;

//x5
    if( (v1>=(mn+3*(mx-mn)/8))&& (v2<=(9*(mx-mn)/8+mn))&& (x4==0) )
    x5=mx; 
    else  x5=0;

//x3
    if( (v1>=(mn+(mx-mn)/8))&& (v2<=(7*(mx-mn)/8+mn))&& (x1==0) && (x2==0) && (x4==0) && (x5==0) )
    x3=mn+3*(mx-mn)/4; 
    else x3=0;

//x6
    if( (x1+x2+x3+x4+x5) ==0 )
    x6=mx; 
    else x6=0;

     finalH = x1+x2+x3+x4+x5+x6;
// calculating yy
//y1
    if( x1>0 )
    y1=mn; 
    else y1=0;

//y2
    if( x2>0 )
    y2=mn+(mx-mn)/4; 
    else y2=0;

//y3
    if( x3>0 )
    y3=mn+(mx-mn)/4; 
    else y3=0;

//y4
    if( x4>0 )
    y4=mn+(mx-mn)/2; 
    else y4=0;

//y5
    if( x5>0 )
    y5=mn+(mx-mn)/2; 
    else y5=0;

//y6
    if( (finalH>0) && ((y1+y2+y3+y4+y5)==0) )
    y6=mn; 
    else y6=0;

    finalL = y1+y2+y3+y4+y5+y6;

    for( i=0; i<OctLinesCnt; i++) {
         mml[i] = 0;
         }
         
   dmml = (finalH-finalL)/8;
   Octv = finalH/(fractal/128);   
      
   mml[0] =(finalL-dmml*2); //-2/8
   for( i=1; i<OctLinesCnt; i++) {
        mml[i] = mml[i-1] + dmml;
        }

Murrey_Mathbuffer1[ii]=mml[0];
Murrey_Mathbuffer2[ii]=mml[1];
Murrey_Mathbuffer3[ii]=mml[2];
Murrey_Mathbuffer4[ii]=mml[3];
Murrey_Mathbuffer5[ii]=mml[4];
Murrey_Mathbuffer6[ii]=mml[5];
Murrey_Mathbuffer7[ii]=mml[6];
Murrey_Mathbuffer8[ii]=mml[7];
Murrey_Mathbuffer9[ii]=mml[8];
Murrey_Mathbuffer10[ii]=mml[9];
Murrey_Mathbuffer11[ii]=mml[10];
Murrey_Mathbuffer12[ii]=mml[11];
Murrey_Mathbuffer13[ii]=mml[12];

//   nTime    = datetimeserial[ii];
//   CurPeriod= charttf[displayedfile];

   }

}
 
//---- End Of Program
  return(0);
  }
//+------------------------------------------------------------------+