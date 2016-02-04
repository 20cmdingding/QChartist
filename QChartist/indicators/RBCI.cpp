//+------------------------------------------------------------------+ 
//| RBCI.mq4 
//| 
//+------------------------------------------------------------------+ 
/*
#property copyright "Copyright 2002, Finware.ru Ltd." 
#property link "http://www.finware.ru/" 

#property indicator_separate_window 
#property indicator_buffers 1 
#property indicator_color1 Blue 


//---- buffers 
double RBCIBuffer[]; 
//+------------------------------------------------------------------+ 
//| Custom indicator initialization function | 
//+------------------------------------------------------------------+ 
int init() 
{ 
string short_name; 
//---- indicator line 
SetIndexStyle(0,DRAW_LINE); 
SetIndexBuffer(0,RBCIBuffer); 
SetIndexDrawBegin(0,55); 
//---- 
return(0); 
} 
*/

static arrayofdoubles RBCIbuffer; // This line of code must stay here.

//+------------------------------------------------------------------+ 
//| RBCI | 
//+------------------------------------------------------------------+ 
char* RBCI (char* period)
{
    static char periodd[1000];
    strncpy(periodd, period, 1000);
    int intperiod=atoi(periodd);
int i,Bars;
Bars=333;
i=Bars-55-1; 
while(i>=0) 
{ 
RBCIbuffer[i]= 
-( 
-35.5241819400*closea[i+0] 
-29.3339896500*closea[i+1] 
-18.4277449600*closea[i+2] 
-5.3418475670*closea[i+3] 
+7.0231636950*closea[i+4] 
+16.1762815600*closea[i+5] 
+20.6566210400*closea[i+6] 
+20.3266115800*closea[i+7] 
+16.2702390600*closea[i+8] 
+10.3524012700*closea[i+9] 
+4.5964239920*closea[i+10] 
+0.5817527531*closea[i+11] 
-0.9559211961*closea[i+12] 
-0.2191111431*closea[i+13] 
+1.8617342810*closea[i+14] 
+4.0433304300*closea[i+15] 
+5.2342243280*closea[i+16] 
+4.8510862920*closea[i+17] 
+2.9604408870*closea[i+18] 
+0.1815496232*closea[i+19] 
-2.5919387010*closea[i+20] 
-4.5358834460*closea[i+21] 
-5.1808556950*closea[i+22] 
-4.5422535300*closea[i+23] 
-3.0671459820*closea[i+24] 
-1.4310126580*closea[i+25] 
-0.2740437883*closea[i+26] 
+0.0260722294*closea[i+27] 
-0.5359717954*closea[i+28] 
-1.6274916400*closea[i+29] 
-2.7322958560*closea[i+30] 
-3.3589596820*closea[i+31] 
-3.2216514550*closea[i+32] 
-2.3326257940*closea[i+33] 
-0.9760510577*closea[i+34] 
+0.4132650195*closea[i+35] 
+1.4202166770*closea[i+36] 
+1.7969987350*closea[i+37] 
+1.5412722800*closea[i+38] 
+0.8771442423*closea[i+39] 
+0.1561848839*closea[i+40] 
-0.2797065802*closea[i+41] 
-0.2245901578*closea[i+42] 
+0.3278853523*closea[i+43] 
+1.1887841480*closea[i+44] 
+2.0577410750*closea[i+45] 
+2.6270409820*closea[i+46] 
+2.6973742340*closea[i+47] 
+2.2289941280*closea[i+48] 
+1.3536792430*closea[i+49] 
+0.3089253193*closea[i+50] 
-0.6386689841*closea[i+51] 
-1.2766707670*closea[i+52] 
-1.5136918450*closea[i+53] 
-1.3775160780*closea[i+54] 
-1.6156173970*closea[i+55]); 


i--; 
} 
return(0); 
}