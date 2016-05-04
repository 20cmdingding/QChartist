static arrayofdoubles WCCIExtMapBuffer1;
static arrayofdoubles WCCIExtMapBuffer2;
static arrayofdoubles WCCIExtMapBuffer3;
static arrayofdoubles WCCIExtMapBuffer4;
static arrayofdoubles WCCIExtMapBuffer5;
static arrayofdoubles WCCIExtMapBuffer6;
static arrayofdoubles WCCIExtMapBuffer7;
static arrayofdoubles WCCIExtMapBuffer8;

char* Weighted_WCCI (char* curtf)
{

static char curtff[1000];
    strncpy(curtff, curtf, 1000);
    int intcurtf=atoi(curtff);

    // Put your indicator C++ code here

//---- input parameters
int       TCCIp=7;
int       CCIp=13;
double    overbslevel=200.0;
double    triglevel=50.0;
double    weight=1.0;
//---- buffers


int limit=200;
   //if (limit>Bars-CCIp-1)limit=Bars-CCIp-1;
   //Comment(Bars+"    "+limit); 
   double Kw=0.0;
   int alt=0;
//---- 
int shift;
   for (shift = 0; shift<=limit;shift++)
   {  
   
      double CCI=icci(intcurtf,CCIp,PRICE_TYPICAL,shift);
      double TCCI=icci(intcurtf,TCCIp,PRICE_TYPICAL,shift);  
     
      if (weight==0) Kw=0; 
      else
      {  Kw=weight*iatr(intcurtf,7,shift)/iatr(intcurtf,49,shift);
         CCI=CCI*Kw;
         TCCI=TCCI*Kw;
      }
      if (TCCI>overbslevel+50) TCCI=overbslevel+50;
      if (CCI>overbslevel+50) CCI=overbslevel+50;
      if (CCI<-overbslevel-50) CCI=-overbslevel-50;
      if (TCCI<-overbslevel-50) TCCI=-overbslevel-50;
      WCCIExtMapBuffer1[shift]=TCCI;
      WCCIExtMapBuffer2[shift]=CCI;
      WCCIExtMapBuffer3[shift]=CCI;
      WCCIExtMapBuffer4[shift]=overbslevel;
      WCCIExtMapBuffer5[shift]=-overbslevel;
      WCCIExtMapBuffer6[shift]=triglevel;
      WCCIExtMapBuffer7[shift]=-triglevel;
      WCCIExtMapBuffer8[shift]=0;
      	
   }

return 0;
}
