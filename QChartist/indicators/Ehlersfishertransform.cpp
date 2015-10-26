//+----------------------------------------------------------+
//|                              Ehlers fisher transform.mq4 |
//|                                                   mladen |
//+----------------------------------------------------------+
//#property  copyright "mladen"
//#property  link      "mladenfx@gmail.com"

//#property  indicator_separate_window
//#property  indicator_buffers 5
//#property  indicator_color1  DimGray
//#property  indicator_color2  YellowGreen
//#property indicator_color3  Green
//#property indicator_color4  Green
//#property indicator_color5  Green
//#property  indicator_width1  2
//#property  indicator_style2  STYLE_DOT

static arrayofdoubles Ehlersfishertransformbuffer1;
static arrayofdoubles Ehlersfishertransformbuffer2;
static arrayofdoubles EhlersfishertransformPrices;
static arrayofdoubles EhlersfishertransformValues;
static arrayofdoubles Ehlersfishertransformbandup;
static arrayofdoubles Ehlersfishertransformbanddn;
static arrayofdoubles Ehlersfishertransformbandmd;
static arrayofdoubles eftbandsmovingbuffer;
static arrayofdoubles eftbandsupperbuffer;
static arrayofdoubles eftbandslowerbuffer;
static arrayofdoubles eftbandssmabuffer;

int eftArrayMaximum( int, int); 
int eftArrayMinimum( int, int);
int eftbandssmacpp(int);

//+----------------------------------------------------------+
//|                                                          |
//+----------------------------------------------------------+

char* Ehlersfishertransform (char* period,char* curtf)
{
    static char periodd[1000];
    strncpy(periodd, period, 1000);
    int intperiod=atoi(periodd);
static char curtff[1000];
    strncpy(curtff, curtf, 1000);
    int intcurtf=atoi(curtff);
int  period2         = 10;
int  PriceType      = PRICE_MEDIAN;
bool showSignalLine = true;
int bbperiod = 20;
int bbdev = 2;

   //int  counted_bars=IndicatorCounted();
   int  i,limit;

   //if(counted_bars < 0) return(-1);
   //if(counted_bars > 0) counted_bars--;
           limit = 100; //Bars-counted_bars;
         
   for(i=limit; i>=0; i--)
   {  
      EhlersfishertransformPrices[i] = ima(intcurtf,1,0,MODE_SMA,PriceType,i);
                  
         double MaxH = EhlersfishertransformPrices[eftArrayMaximum(period2,i)];
         double MinL = EhlersfishertransformPrices[eftArrayMinimum(period2,i)];
         if (MaxH!=MinL)
               EhlersfishertransformValues[i] = 0.33*2*((EhlersfishertransformPrices[i]-MinL)/(MaxH-MinL)-0.5)+0.67*EhlersfishertransformValues[i+1];
         else  EhlersfishertransformValues[i] = 0.00;
               EhlersfishertransformValues[i] = mathmin(mathmax(EhlersfishertransformValues[i],-0.999),0.999); 

      Ehlersfishertransformbuffer1[i] = 0.5*log((1+EhlersfishertransformValues[i])/(1-EhlersfishertransformValues[i]))+0.5*Ehlersfishertransformbuffer1[i+1];
      if (showSignalLine)
            Ehlersfishertransformbuffer2[i] = Ehlersfishertransformbuffer1[i+1];
   }

int bandsperiod=20;
double bandsdeviations=2; 
//int i;
int k;
double deviation;
double sum;
double oldval;
double newres; 

//if (bars<=bandsperiod) return 0;

limit=100;
eftbandssmacpp(bandsperiod);
for (i=0 ; i<=limit-1;i++) {
    eftbandsmovingbuffer[i]=eftbandssmabuffer[i];
}

i=100-bandsperiod+1;
while (i>=0) {
    sum=0;
    k=i+bandsperiod-1;
    oldval=eftbandsmovingbuffer[i];
    while (k>=i) {
        newres=Ehlersfishertransformbuffer1[k]-oldval;
        sum+=newres*newres;
        k--;
        }
    deviation=bandsdeviations*sqrt(sum/bandsperiod);
    eftbandsupperbuffer[i]=oldval+deviation;
    eftbandslowerbuffer[i]=oldval-deviation;
    i--;
}

   return(0);
}

int eftArrayMaximum( int count, int start)
{

double maxtmp=EhlersfishertransformPrices[start];
int i;

for (i=start;i<=start+count-1;i++)
	{
	if (EhlersfishertransformPrices[i]>maxtmp) maxtmp=EhlersfishertransformPrices[i];
	}
for (i=start;i<=start+count-1;i++)
	{
	if (maxtmp==EhlersfishertransformPrices[i]) {
		return i;		
		break;
		}
	}
}

int eftArrayMinimum( int count, int start)
{

double mintmp=EhlersfishertransformPrices[start];
int i;

for (i=start;i<=start+count-1;i++)
	{
	if (EhlersfishertransformPrices[i]<mintmp) mintmp=EhlersfishertransformPrices[i];
	}
for (i=start;i<=start+count-1;i++)
	{
	if (mintmp==EhlersfishertransformPrices[i]) {
		return i;		
		break;
		}
	}
}

int eftbandssmacpp(int period)
{
    int bandsperiod=period;
    double sum=0;
    int i;
    int p;
    p=bars-1;
    p=100;
    if (p<bandsperiod) p=bandsperiod;
    for (i=1;i<=bandsperiod-1;i++) {
        sum=sum+Ehlersfishertransformbuffer1[p];
        p--;
                                   }
    while (p>=0) {
        sum=sum+Ehlersfishertransformbuffer1[p];
        eftbandssmabuffer[p]=sum/bandsperiod;
        sum=sum-Ehlersfishertransformbuffer1[p+bandsperiod-1];
        p--;
                 }
return 0;  
}