//+-----------------------------------------------------------------------------------------+
//|                                                                         WaterLevel.mq4  |
//|                                                              Original concept by Brijon |
//|                                       Ideas and helps by NorthPro, Pipo, Walter, Charvo |
//|                                                                   Coded by Pacific_trip |
//|                                              "Magnified Market Price" feature by Habeeb |
//|                                               Static buy/sell lines by Skyline & Hornet |
//|                                   Many thanks to ForexFactory members for their support |
//|     Ported from MT4 to QChartist by Julien Moog - julien.moog@laposte.net on 2014-07-16 |
//+-----------------------------------------------------------------------------------------+

static arrayofdoubles waterlevelcppbuffer; // This line of code must stay here.

//#property indicator_chart_window
//#property indicator_buffers 8

//#property indicator_color1 Gold
//#property indicator_color2 GreenYellow
//#property indicator_color3 Red
//#property indicator_color4 Lime

//#property indicator_color5 Khaki
//#property indicator_color6 LightSalmon
//#property indicator_color7 HotPink
//#property indicator_color8 MediumSlateBlue

string Time_Frame_value = "TimeFrame(0,M5,M15,M30,H1,H4,D1,W1,MN1)";
string Time_Frame = "D1";

int Calculate_From_Previous_Bar = 1;
bool Dynamic_BuySell_Price = true;

bool Show_Magnified_WL_Price = true;
int Magnified_WL_Price_Corner = 3;
string note2 = "Default Font Color";
//color  FontColor = SteelBlue;
string note3 = "Font Size";
int FontSize=14;
string note4 = "Font Type";
string FontType="Tahoma";

bool Show_Comment = false;
bool Show_MAs = false;
int Period_MA1 = 5;
int Period_MA2 = 7;
int Period_MA3 = 22;
int Period_MA4 = 34;

string MA_Type_value = "SMA, EMA, LWMA";
string MA_Type = "SMA";

double TimeFrame1CloseAverageMA1, TimeFrame1CloseAverageMA2, TimeFrame1CloseAverageMA3, TimeFrame1CloseAverageMA4;
double TimeFrame2CloseAverageMA1, TimeFrame2CloseAverageMA2, TimeFrame2CloseAverageMA3, TimeFrame2CloseAverageMA4;

double TimeFrame1HighestHighMA1, TimeFrame1LowestLowMA1, TimeFrame2HighestHighMA1, TimeFrame2LowestLowMA1;
double TimeFrame1HighestHighMA2, TimeFrame1LowestLowMA2, TimeFrame2HighestHighMA2, TimeFrame2LowestLowMA2;
double TimeFrame1HighestHighMA3, TimeFrame1LowestLowMA3, TimeFrame2HighestHighMA3, TimeFrame2LowestLowMA3;
double TimeFrame1HighestHighMA4, TimeFrame1LowestLowMA4, TimeFrame2HighestHighMA4, TimeFrame2LowestLowMA4;

double TimeFrame1HighestHighAverage, TimeFrame1LowestLowAverage;
double TimeFrame2HighestHighAverage, TimeFrame2LowestLowAverage;

double TimeFrame1HHLLAverageMA1, TimeFrame2HHLLAverageMA1;
double TimeFrame1HHLLAverageMA2, TimeFrame2HHLLAverageMA2;
double TimeFrame1HHLLAverageMA3, TimeFrame2HHLLAverageMA3;
double TimeFrame1HHLLAverageMA4, TimeFrame2HHLLAverageMA4;

double TimeFrame1HHLLAverages, TimeFrame2HHLLAverages;
static arrayofdoubles TimeFrame2AverageMA1, TimeFrame2AverageMA2, TimeFrame2AverageMA3, TimeFrame2AverageMA4;

static arrayofdoubles TimeFrame1Level, TimeFrame2Level;
static arrayofdoubles SellPrice, BuyPrice;

static int timeFrame1, timeFrame2, maType;
static string TimeFrame1String, TimeFrame2String;

int lastBarTime = -1;
double lastBarClose = 0;
string InfoDisplay = "";

char* initwaterlevelcpp(char* periodparam) {

static char periodparamm[1000];
    strncpy(periodparamm, periodparam, 1000);
    int intperiodparam=atoi(periodparamm);
    
   if (Time_Frame == "M1") {

      timeFrame1 = PERIOD_M1;
      TimeFrame1String = "M1";

   } else if (Time_Frame == "M5") {

      timeFrame1 = PERIOD_M5;
      TimeFrame1String = "M5";

   } else if (Time_Frame == "M15") {

      timeFrame1 = PERIOD_M15;
      TimeFrame1String = "M15";

   } else if (Time_Frame == "M30") {

      timeFrame1 = PERIOD_M30;
      TimeFrame1String = "M30";

   } else if (Time_Frame == "H1") {

      timeFrame1 = PERIOD_H1;
      TimeFrame1String = "H1";

   } else if (Time_Frame == "H4") {

      timeFrame1 = PERIOD_H4;
      TimeFrame1String = "H4";

   } else if (Time_Frame == "D1") {

      timeFrame1 = PERIOD_D1;
      TimeFrame1String = "D1";

   } else if (Time_Frame == "W1") {

      timeFrame1 = PERIOD_W1;
      TimeFrame1String = "W1";

   } else if (Time_Frame == "MN1") {

      timeFrame1 = PERIOD_MN1;
      TimeFrame1String = "MN1";

   } else {

      timeFrame1 = 0;

   }
   
   timeFrame2 = intperiodparam;//Period();
   
   if (timeFrame2 == PERIOD_M1) {
   
      TimeFrame2String = "M1";
   
   } else if (timeFrame2 == PERIOD_M5) {

      TimeFrame2String = "M5";
   
   } else if (timeFrame2 == PERIOD_M15) {

      TimeFrame2String = "M15";
   
   } else if (timeFrame2 == PERIOD_M30) {

      TimeFrame2String = "M30";
   
   } else if (timeFrame2 == PERIOD_H1) {

      TimeFrame2String = "H1";
   
   } else if (timeFrame2 == PERIOD_H4) {

      TimeFrame2String = "H4";
   
   } else if (timeFrame2 == PERIOD_D1) {

      TimeFrame2String = "D1";
   
   } else if (timeFrame2 == PERIOD_W1) {

      TimeFrame2String = "W1";
   
   } else if (timeFrame2 == PERIOD_MN1) {

      TimeFrame2String = "MN1";
   
   }

   if (MA_Type == "SMA") {

      maType = MODE_SMA;

   } else if (MA_Type == "EMA") {

      maType = MODE_EMA;

   } else if (MA_Type == "LWMA") {

      maType = MODE_LWMA;

   } else {

      maType = MODE_SMA;

   }

   if (timeFrame1 < timeFrame2) {

      //Alert("The timeframe must be higher than the current");
      sprintf(debugmsg,"%s","The timeframe must be higher than the current");MessageBox( NULL, debugmsg,"Debug",MB_OK);
      //deinit();
      return 0;

   }

   //SetIndexStyle(0,DRAW_LINE);
   //SetIndexBuffer(0,TimeFrame1Level);
   //SetIndexLabel(0,TimeFrame1String + " Level");
   //SetIndexStyle(1,DRAW_LINE);
   //SetIndexBuffer(1,TimeFrame2Level);
   //SetIndexLabel(1,TimeFrame2String + " Level");
   

   //SetIndexStyle(2,DRAW_LINE, STYLE_DOT);
   //SetIndexBuffer(2,SellPrice);
   //SetIndexLabel(2,"Sell Level");
   //SetIndexStyle(3,DRAW_LINE, STYLE_DOT);
   //SetIndexBuffer(3,BuyPrice);
   //SetIndexLabel(3,"Buy Level");

   //SetIndexStyle(4,DRAW_LINE, STYLE_DASHDOT);
   //SetIndexBuffer(4,TimeFrame2AverageMA1);
   //SetIndexLabel(4,"" + MA_Type + "(" + Period_MA1 + ")");
   //SetIndexStyle(5,DRAW_LINE, STYLE_DASHDOT);
   //SetIndexBuffer(5,TimeFrame2AverageMA2);
   //SetIndexLabel(5,"" + MA_Type + "(" + Period_MA2 + ")");
   //SetIndexStyle(6,DRAW_LINE, STYLE_DASHDOT);
   //SetIndexBuffer(6,TimeFrame2AverageMA3);
   //SetIndexLabel(6,"" + MA_Type + "(" + Period_MA3 + ")");
   //SetIndexStyle(7,DRAW_LINE, STYLE_DASHDOT);
   //SetIndexBuffer(7,TimeFrame2AverageMA4);
   //SetIndexLabel(7,"" + MA_Type + "(" + Period_MA4 + ")");   

   return(0);

}

char* waterlevelcpp (char* period,char* periodparam)
{
    static char periodd[1000];
    strncpy(periodd, period, 1000);
    int intperiod=atoi(periodd);
    static char periodparamm[1000];
    strncpy(periodparamm, periodparam, 1000);
    int intperiodparam=atoi(periodparamm);
    // Put your indicator C++ code here
int i, idx, counted_bars = cntbarsedit;//IndicatorCounted();
   // i = chartbars[displayedfile] - counted_bars - 1;//Bars - counted_bars - 1; // Bugs with this line
   i=200;
   double sum = 0;

   while (i >= 0) {
   
      int timeFrame1Index = ibarshift(timeFrame1, datetimeserial[i], 500,true);  
      // Calculate all values for timeframe1 which is greater than the timeframe1
      // Runs only once every timeframe1 bar
      if (lastBarTime != idatetimeserial(timeFrame1, timeFrame1Index)) {

         lastBarTime = idatetimeserial(timeFrame1, timeFrame1Index);

         // Averages of the selected timeframe
         TimeFrame1CloseAverageMA1 = ima(timeFrame1, Period_MA1, 0, maType, PRICE_CLOSE, timeFrame1Index+Calculate_From_Previous_Bar);
         TimeFrame1CloseAverageMA2 = ima(timeFrame1, Period_MA2, 0, maType, PRICE_CLOSE, timeFrame1Index+Calculate_From_Previous_Bar);
         TimeFrame1CloseAverageMA3 = ima(timeFrame1, Period_MA3, 0, maType, PRICE_CLOSE, timeFrame1Index+Calculate_From_Previous_Bar);
         TimeFrame1CloseAverageMA4 = ima(timeFrame1, Period_MA4, 0, maType, PRICE_CLOSE, timeFrame1Index+Calculate_From_Previous_Bar);

         // Highest Highs and Lowest Lows Averages of the selected timeframe
         TimeFrame1HighestHighMA1 = ihigh(timeFrame1, ihighest(timeFrame1, MODE_HIGH, Period_MA1, timeFrame1Index+Calculate_From_Previous_Bar));
         TimeFrame1LowestLowMA1 = ilow(timeFrame1, ilowest(timeFrame1, MODE_LOW, Period_MA1, timeFrame1Index+Calculate_From_Previous_Bar));

         TimeFrame1HighestHighMA2 = ihigh(timeFrame1, ihighest(timeFrame1, MODE_HIGH, Period_MA2, timeFrame1Index+Calculate_From_Previous_Bar));
         TimeFrame1LowestLowMA2 = ilow(timeFrame1, ilowest(timeFrame1, MODE_LOW, Period_MA2, timeFrame1Index+Calculate_From_Previous_Bar));

         TimeFrame1HighestHighMA3 = ihigh(timeFrame1, ihighest(timeFrame1, MODE_HIGH, Period_MA3, timeFrame1Index+Calculate_From_Previous_Bar));
         TimeFrame1LowestLowMA3 = ilow(timeFrame1, ilowest(timeFrame1, MODE_LOW, Period_MA3, timeFrame1Index+Calculate_From_Previous_Bar));

         TimeFrame1HighestHighMA4 = ihigh(timeFrame1, ihighest(timeFrame1, MODE_HIGH, Period_MA4, timeFrame1Index+Calculate_From_Previous_Bar));
         TimeFrame1LowestLowMA4 = ilow(timeFrame1, ilowest(timeFrame1, MODE_LOW, Period_MA4, timeFrame1Index+Calculate_From_Previous_Bar));

         // HH-LL averages of the selected timeframe
         TimeFrame1HHLLAverageMA1 = TimeFrame1HighestHighMA1 - TimeFrame1LowestLowMA1;
         TimeFrame1HHLLAverageMA2 = TimeFrame1HighestHighMA2 - TimeFrame1LowestLowMA2;
         TimeFrame1HHLLAverageMA3 = TimeFrame1HighestHighMA3 - TimeFrame1LowestLowMA3;
         TimeFrame1HHLLAverageMA4 = TimeFrame1HighestHighMA4 - TimeFrame1LowestLowMA4;

         if (Dynamic_BuySell_Price == false) {

            // Highest Highs and Lowest Lows Averages of the currently displayed timeframe
            TimeFrame2HighestHighMA1 = higha[ihighest(intperiodparam, MODE_HIGH, Period_MA1, i+Calculate_From_Previous_Bar)];
            TimeFrame2LowestLowMA1 = lowa[ilowest(intperiodparam, MODE_LOW, Period_MA1, i+Calculate_From_Previous_Bar)];

            TimeFrame2HighestHighMA2 = higha[ihighest(intperiodparam, MODE_HIGH, Period_MA2, i+Calculate_From_Previous_Bar)];
            TimeFrame2LowestLowMA2 = lowa[ilowest(intperiodparam, MODE_LOW, Period_MA2, i+Calculate_From_Previous_Bar)];

            TimeFrame2HighestHighMA3 = higha[ihighest(intperiodparam, MODE_HIGH, Period_MA3, i+Calculate_From_Previous_Bar)];
            TimeFrame2LowestLowMA3 = lowa[ilowest(intperiodparam, MODE_LOW, Period_MA3, i+Calculate_From_Previous_Bar)];

            TimeFrame2HighestHighMA4 = higha[ihighest(intperiodparam, MODE_HIGH, Period_MA4, i+Calculate_From_Previous_Bar)];
            TimeFrame2LowestLowMA4 = lowa[ilowest(intperiodparam, MODE_LOW, Period_MA4, i+Calculate_From_Previous_Bar)];

         }

      }

      lastBarClose = iclose(timeFrame1,timeFrame1Index+1);

      if (Dynamic_BuySell_Price == true) {

         // Highest Highs and Lowest Lows Averages of the currently displayed timeframe
         TimeFrame2HighestHighMA1 = higha[ihighest(intperiodparam, MODE_HIGH, Period_MA1, i+Calculate_From_Previous_Bar)];
         TimeFrame2LowestLowMA1 = lowa[ilowest(intperiodparam, MODE_LOW, Period_MA1, i+Calculate_From_Previous_Bar)];

         TimeFrame2HighestHighMA2 = higha[ihighest(intperiodparam, MODE_HIGH, Period_MA2, i+Calculate_From_Previous_Bar)];
         TimeFrame2LowestLowMA2 = lowa[ilowest(intperiodparam, MODE_LOW, Period_MA2, i+Calculate_From_Previous_Bar)];

         TimeFrame2HighestHighMA3 = higha[ihighest(intperiodparam, MODE_HIGH, Period_MA3, i+Calculate_From_Previous_Bar)];
         TimeFrame2LowestLowMA3 = lowa[ilowest(intperiodparam, MODE_LOW, Period_MA3, i+Calculate_From_Previous_Bar)];

         TimeFrame2HighestHighMA4 = higha[ihighest(intperiodparam, MODE_HIGH, Period_MA4, i+Calculate_From_Previous_Bar)];
         TimeFrame2LowestLowMA4 = lowa[ilowest(intperiodparam, MODE_LOW, Period_MA4, i+Calculate_From_Previous_Bar)];

      }

      // HH-LL averages of the currently displayed timeframe
      TimeFrame2HHLLAverageMA1 = TimeFrame2HighestHighMA1 - TimeFrame2LowestLowMA1;
      TimeFrame2HHLLAverageMA2 = TimeFrame2HighestHighMA2 - TimeFrame2LowestLowMA2;
      TimeFrame2HHLLAverageMA3 = TimeFrame2HighestHighMA3 - TimeFrame2LowestLowMA3;
      TimeFrame2HHLLAverageMA4 = TimeFrame2HighestHighMA4 - TimeFrame2LowestLowMA4;
         
      // Averages of the currently displayed timeframe
      TimeFrame2CloseAverageMA1 = ima(intperiodparam, Period_MA1, 0, maType, PRICE_CLOSE, i+Calculate_From_Previous_Bar);
      TimeFrame2CloseAverageMA2 = ima(intperiodparam, Period_MA2, 0, maType, PRICE_CLOSE, i+Calculate_From_Previous_Bar);
      TimeFrame2CloseAverageMA3 = ima(intperiodparam, Period_MA3, 0, maType, PRICE_CLOSE, i+Calculate_From_Previous_Bar);
      TimeFrame2CloseAverageMA4 = ima(intperiodparam, Period_MA4, 0, maType, PRICE_CLOSE, i+Calculate_From_Previous_Bar);

      /*if (Symbol() == "GBPUSD") {

         TimeFrame1Level[i] = (TimeFrame1CloseAverageMA1 + TimeFrame1CloseAverageMA2 + TimeFrame1CloseAverageMA3 + TimeFrame1CloseAverageMA4) / 4;
         TimeFrame2Level[i] = (TimeFrame2CloseAverageMA1 + TimeFrame2CloseAverageMA2 + TimeFrame2CloseAverageMA3 + TimeFrame2CloseAverageMA4) / 4;
         
         TimeFrame1HighestHighAverage = (TimeFrame1HighestHighMA1 + TimeFrame1HighestHighMA2 + TimeFrame1HighestHighMA3 + TimeFrame1HighestHighMA4) / 4;
         TimeFrame1LowestLowAverage = (TimeFrame1LowestLowMA1 + TimeFrame1LowestLowMA2 + TimeFrame1LowestLowMA3 + TimeFrame1LowestLowMA4) / 4;
         
         TimeFrame2HighestHighAverage = (TimeFrame2HighestHighMA1 + TimeFrame2HighestHighMA2 + TimeFrame2HighestHighMA3 + TimeFrame2HighestHighMA4) / 4;
         TimeFrame2LowestLowAverage = (TimeFrame2LowestLowMA1 + TimeFrame2LowestLowMA2 + TimeFrame2LowestLowMA3 + TimeFrame2LowestLowMA4) / 4;
         
         InfoDisplay = "*********** " + TimeFrame1String + " Levels ***********\n" + MA_Type + " Period(" + Period_MA1 + ")=" + TimeFrame1CloseAverageMA1 +
                      "\n" + MA_Type + " Period(" + Period_MA2 + ")=" + TimeFrame1CloseAverageMA2 +
                      "\n" + MA_Type + " Period(" + Period_MA3 + ")=" + TimeFrame1CloseAverageMA3 +
                      "\n" + MA_Type + " Period(" + Period_MA4 + ")=" + TimeFrame1CloseAverageMA4 +
                      "\nWaterLevel=" + TimeFrame1Level[i] +
                      "\n*********** " + TimeFrame2String + " Levels ***********\n" + MA_Type + " Period(" + Period_MA1 + ")=" + TimeFrame2CloseAverageMA1 +
                      "\n" + MA_Type + " Period(" + Period_MA2 + ")=" + TimeFrame2CloseAverageMA2 +
                      "\n" + MA_Type + " Period(" + Period_MA3 + ")=" + TimeFrame2CloseAverageMA3 +
                      "\n" + MA_Type + " Period(" + Period_MA4 + ")=" + TimeFrame2CloseAverageMA4 +
                      "\nWaterLevel=" + TimeFrame2Level[i];
                  
      } else {*/
      
         TimeFrame1Level[i] = (TimeFrame1CloseAverageMA1 + TimeFrame1CloseAverageMA2 + TimeFrame1CloseAverageMA3) / 3;
         TimeFrame2Level[i] = (TimeFrame2CloseAverageMA1 + TimeFrame2CloseAverageMA2 + TimeFrame2CloseAverageMA3) / 3;
         
         TimeFrame1HighestHighAverage = (TimeFrame1HighestHighMA1 + TimeFrame1HighestHighMA2 + TimeFrame1HighestHighMA3) / 3;
         TimeFrame1LowestLowAverage = (TimeFrame1LowestLowMA1 + TimeFrame1LowestLowMA2 + TimeFrame1LowestLowMA3) / 3;
         
         TimeFrame2HighestHighAverage = (TimeFrame2HighestHighMA1 + TimeFrame2HighestHighMA2 + TimeFrame2HighestHighMA3) / 3;
         TimeFrame2LowestLowAverage = (TimeFrame2LowestLowMA1 + TimeFrame2LowestLowMA2 + TimeFrame2LowestLowMA3) / 3;
         
         /*InfoDisplay = "*********** " + TimeFrame1String + " Levels ***********\n" + MA_Type + " Period(" + Period_MA1 + ")=" + TimeFrame1CloseAverageMA1 +
                      "\n" + MA_Type + " Period(" + Period_MA2 + ")=" + TimeFrame1CloseAverageMA2 +
                      "\n" + MA_Type + " Period(" + Period_MA3 + ")=" + TimeFrame1CloseAverageMA3 +
                      "\nWaterLevel=" + TimeFrame1Level[i] +
                      "\n*********** " + TimeFrame2String + " Levels ***********\n" + MA_Type + " Period(" + Period_MA1 + ")=" + TimeFrame2CloseAverageMA1 +
                      "\n" + MA_Type + " Period(" + Period_MA2 + ")=" + TimeFrame2CloseAverageMA2 +
                      "\n" + MA_Type + " Period(" + Period_MA3 + ")=" + TimeFrame2CloseAverageMA3 +
                      "\nWaterLevel=" + TimeFrame2Level[i];*/
     
      //}
 
      TimeFrame1HHLLAverages = ((TimeFrame1HHLLAverageMA1 + TimeFrame1HHLLAverageMA2 + TimeFrame1HHLLAverageMA3 + TimeFrame1HHLLAverageMA4) / 4) / 4;
      TimeFrame2HHLLAverages = ((TimeFrame2HHLLAverageMA1 + TimeFrame2HHLLAverageMA2 + TimeFrame2HHLLAverageMA3 + TimeFrame2HHLLAverageMA4) / 4) / 4;
     
      if (Show_Comment == false) {

         InfoDisplay = "";

      }
      
      //Comment(InfoDisplay);
      
      /*if (Show_Magnified_WL_Price == true){

         string Market_Price = DoubleToStr(Bid, Digits);
         string TimeFrame1WaterLevel = DoubleToStr(TimeFrame1Level[i], Digits);
         string TimeFrame2WaterLevel = DoubleToStr(TimeFrame2Level[i], Digits);

         ObjectCreate("Market_Price_Label", OBJ_LABEL, 0, 0, 0);
         ObjectSetText("Market_Price_Label", "P=" + Market_Price, FontSize, FontType, FontColor);
         ObjectSet("Market_Price_Label", OBJPROP_CORNER, Magnified_WL_Price_Corner);
         ObjectSet("Market_Price_Label", OBJPROP_XDISTANCE, 5);
         ObjectSet("Market_Price_Label", OBJPROP_YDISTANCE, FontSize*3+10);

         ObjectCreate("TimeFrame1_Level_Label", OBJ_LABEL, 0, 0, 0);
         ObjectSetText("TimeFrame1_Level_Label", TimeFrame1String + " WL=" + TimeFrame1WaterLevel, FontSize, FontType, FontColor);
         ObjectSet("TimeFrame1_Level_Label", OBJPROP_CORNER, Magnified_WL_Price_Corner);
         ObjectSet("TimeFrame1_Level_Label", OBJPROP_XDISTANCE, 5);
         ObjectSet("TimeFrame1_Level_Label", OBJPROP_YDISTANCE, FontSize*2+5);


         ObjectCreate("TimeFrame2_Level_Label", OBJ_LABEL, 0, 0, 0);
         ObjectSetText("TimeFrame2_Level_Label", TimeFrame2String + " WL=" + TimeFrame2WaterLevel, FontSize, FontType, FontColor);
         ObjectSet("TimeFrame2_Level_Label", OBJPROP_CORNER, Magnified_WL_Price_Corner);
         ObjectSet("TimeFrame2_Level_Label", OBJPROP_XDISTANCE, 5);
         ObjectSet("TimeFrame2_Level_Label", OBJPROP_YDISTANCE, FontSize);

      } else {

         ObjectDelete("Market_Price_Label");
         ObjectDelete("TimeFrame1_Level_Label");
         ObjectDelete("TimeFrame2_Level_Label");

      }*/

      SellPrice[i] = lastBarClose + (TimeFrame1HHLLAverages - TimeFrame2HHLLAverages);
      BuyPrice[i] = lastBarClose - (TimeFrame1HHLLAverages - TimeFrame2HHLLAverages);
      
      if (Show_MAs) {

         TimeFrame2AverageMA1[i] = TimeFrame2CloseAverageMA1;
         TimeFrame2AverageMA2[i] = TimeFrame2CloseAverageMA2;
         TimeFrame2AverageMA3[i] = TimeFrame2CloseAverageMA3;
         TimeFrame2AverageMA4[i] = TimeFrame2CloseAverageMA4;
         
      }

      TimeFrame2AverageMA1[i] = (SellPrice[i] + BuyPrice[i]) / 2;

      i--;

   }
return 0;
}

//+------------------------------------------------------------------+