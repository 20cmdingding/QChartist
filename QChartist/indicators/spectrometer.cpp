//---- buffers
static arrayofdoubles spectrometerbuffer1;
static arrayofdoubles spectrometerbuffer2;
static arrayofdoubles spectrometerbuffer3;
static arrayofdoubles spectrometerbuffer4;
static arrayofdoubles spectrometerbuffer5;
static arrayofdoubles spectrometerbuffer6;
static arrayofdoubles spectrometerbuffer7;
static arrayofdoubles spectrometerbuffer8;

int fLinearRegressionAll2(int,int, int, int&, double&, double&, double& , double& , double& , double& ,arrayofdoubles&,int );
int fFurie(arrayofdoubles,arrayofdoubles&,arrayofdoubles&,arrayofdoubles&, arrayofdoubles&);
double fMyArcTan(double,double);

//+------------------------------------------------------------------+
//| Custom indicator iteration function                              |
//+------------------------------------------------------------------+

char* spectrometer (char* period, char* curtf)
{

static char curtff[1000];
    strncpy(curtff, curtf, 1000);
    int intcurtf=atoi(curtff);

//---- input parameters

int iPeriod;
iPeriod=240;
int iStartFrom;
iStartFrom=1; 
string AddToObjName;
AddToObjName="1";
//extern color     HandlerColor=DarkSlateGray;
//extern color     TextColor=DarkGray; 
 
string ObjNPref;
ObjNPref="Spectrometr";
string ShortName;

int LastTime;
static arrayofdoubles A;
static arrayofdoubles B;
static arrayofdoubles R;
static arrayofdoubles F;

int LastLeftBar;
int LastRightBar;
int LastLeftTime;
int LastRightTime;
int LastStartFrom;
int LastiStartFrom;
int LastiPeriod;

string ObjName;
ObjName=ObjNPref+"zero line";
/*         
         if(ObjectFind(ObjName)!=WindowFind(ShortName)){
            LastStartFrom=iStartFrom;//
            LastLeftBar=iStartFrom+iPeriod-1;
            LastRightBar=iStartFrom;            
            LastLeftTime=Time[LastLeftBar];
            LastRightTime=Time[LastRightBar];         
            fObjTrendLine(ObjName,LastLeftTime,0,LastRightTime,0,false,HandlerColor,3,WindowFind(ShortName),0,true);
         }
*/
/*         
      int NowLeftTime=ObjectGet(ObjName,OBJPROP_TIME1);
      int NowRightTime=ObjectGet(ObjName,OBJPROP_TIME2); 
      if(NowRightTime>Time[1])NowRightTime=Time[1];
*/      
      int NowLeftBar=iStartFrom+iPeriod-1; //iBarShift(NULL,0,NowLeftTime,false);
      int NowRightBar=iStartFrom; //iBarShift(NULL,0,NowRightTime,false);  
      //iPeriod=NowLeftBar-NowRightBar+1; 
      //int LastStartFromTime=iBarShift(NULL,0,LastRightTime,false);  
      //iStartFrom=(NowRightBar-LastStartFromTime)+LastStartFrom; 
      
      LastStartFrom=iStartFrom;
      LastLeftBar=iStartFrom+iPeriod-1;
      LastRightBar=iStartFrom;            
      //LastLeftTime=timeb[LastLeftBar];
      //LastRightTime=timeb[LastRightBar];         
      //fObjTrendLine(ObjName,LastLeftTime,0,LastRightTime,0,false,HandlerColor,3,WindowFind(ShortName),0,true);
            
      ObjName=ObjNPref+"iPeriod";
      //fObjLabel(ObjName,100,5,"Period: "+iPeriod,3,TextColor,8,WindowFind(ShortName),"Arial Black",false);
      ObjName=ObjNPref+"iStartFrom";      
      //fObjLabel(ObjName,10,5,"StartFrom: "+iStartFrom,3,TextColor,8,WindowFind(ShortName),"Arial Black",false);
      
      
   //=====================================================================================================    

      static int LastBars=0;

      //if(iStartFrom==LastiStartFrom && iPeriod==LastiPeriod)if(Bars<LastBars+1)return(0);
      LastiStartFrom=iStartFrom;
      LastiPeriod=iPeriod;
      LastBars=500; //Bars;
         
      //ArrayInitialize(ExtMapBuffer1,EMPTY_VALUE);
      //ArrayInitialize(ExtMapBuffer2,EMPTY_VALUE);
      //ArrayInitialize(ExtMapBuffer3,EMPTY_VALUE);
      //ArrayInitialize(ExtMapBuffer4,EMPTY_VALUE);
      //ArrayInitialize(ExtMapBuffer5,EMPTY_VALUE);
      //ArrayInitialize(ExtMapBuffer6,EMPTY_VALUE);
      //ArrayInitialize(ExtMapBuffer7,EMPTY_VALUE);
      //ArrayInitialize(ExtMapBuffer8,EMPTY_VALUE);
   
   //=====================================================================================================    

      int tPeriod; 
      double tVal_0=0;
      double tVal_1=0;
      double tB=0;
      double tMaxDev=0;
      double tStdError=0; 
      double tRSquared=0;
      //double Arr[];
      //double Arr= new double[240];
      //double Arr[];
      static arrayofdoubles Arr;

      fLinearRegressionAll2(iStartFrom,iStartFrom+iPeriod-1,0,tPeriod,tVal_0,tVal_1,tB,tMaxDev,tStdError,tRSquared,Arr,intcurtf);

   //======================================================================================================      
         
      fFurie(Arr,A,B,R,F);

   //======================================================================================================      
         
      //int N=ArraySize(Arr);
      int N=iPeriod; //Arr.size();

         for(int i=0;i<N;i++){
            int ii=i+iStartFrom;
            spectrometerbuffer1[ii]=A[1]*sin(1*6.28*i/(N-1))+B[1]*cos(1*6.28*i/(N-1));
            spectrometerbuffer2[ii]=A[2]*sin(2*6.28*i/(N-1))+B[2]*cos(2*6.28*i/(N-1));               
            spectrometerbuffer3[ii]=A[3]*sin(3*6.28*i/(N-1))+B[3]*cos(3*6.28*i/(N-1));
            spectrometerbuffer4[ii]=A[4]*sin(4*6.28*i/(N-1))+B[4]*cos(4*6.28*i/(N-1));               
            spectrometerbuffer5[ii]=A[5]*sin(5*6.28*i/(N-1))+B[5]*cos(5*6.28*i/(N-1));               
            spectrometerbuffer6[ii]=A[6]*sin(6*6.28*i/(N-1))+B[6]*cos(6*6.28*i/(N-1));
            spectrometerbuffer7[ii]=A[7]*sin(7*6.28*i/(N-1))+B[7]*cos(7*6.28*i/(N-1));               
            spectrometerbuffer8[ii]=A[8]*sin(8*6.28*i/(N-1))+B[8]*cos(8*6.28*i/(N-1));                 
         }

   //======================================================================================================      
                                   //линии справа
      /*fObjTrendLine(ObjNPref+"1",Time[0]+Period()*60*3,R[1],Time[0]+Period()*60*3,-R[1],false,indicator_color1,8,WindowFind(ShortName),0,false);
      fObjTrendLine(ObjNPref+"2",Time[0]+Period()*60*5,R[2],Time[0]+Period()*60*5,-R[2],false,indicator_color2,8,WindowFind(ShortName),0,false);
      fObjTrendLine(ObjNPref+"3",Time[0]+Period()*60*7,R[3],Time[0]+Period()*60*7,-R[3],false,indicator_color3,8,WindowFind(ShortName),0,false);
      fObjTrendLine(ObjNPref+"4",Time[0]+Period()*60*9,R[4],Time[0]+Period()*60*9,-R[4],false,indicator_color4,8,WindowFind(ShortName),0,false);
      fObjTrendLine(ObjNPref+"5",Time[0]+Period()*60*11,R[5],Time[0]+Period()*60*11,-R[5],false,indicator_color5,8,WindowFind(ShortName),0,false);
      fObjTrendLine(ObjNPref+"6",Time[0]+Period()*60*13,R[6],Time[0]+Period()*60*13,-R[6],false,indicator_color6,8,WindowFind(ShortName),0,false);
      fObjTrendLine(ObjNPref+"7",Time[0]+Period()*60*15,R[7],Time[0]+Period()*60*15,-R[7],false,indicator_color7,8,WindowFind(ShortName),0,false);
      fObjTrendLine(ObjNPref+"8",Time[0]+Period()*60*17,R[8],Time[0]+Period()*60*17,-R[8],false,indicator_color8,8,WindowFind(ShortName),0,false);
      
      fObjTrendLine(ObjNPref+"1pos",Time[50],R[1],Time[0],R[1],false,indicator_color1,1,WindowFind(ShortName),0,false);
      fObjTrendLine(ObjNPref+"1neg",Time[50],-R[1],Time[0],-R[1],false,indicator_color1,1,WindowFind(ShortName),0,false);
      fObjTrendLine(ObjNPref+"2pos",Time[50],R[2],Time[0],R[2],false,indicator_color2,1,WindowFind(ShortName),0,false);
      fObjTrendLine(ObjNPref+"2neg",Time[50],-R[2],Time[0],-R[2],false,indicator_color2,1,WindowFind(ShortName),0,false);
*/
ObjName=ObjNPref+"iupdn1";
double percent1=fabs(roundf(100*spectrometerbuffer1[1]/R[1]));
double percent2=fabs(roundf(100*spectrometerbuffer2[1]/R[2]));
/*
if (spectrometerbuffer1[1]>spectrometerbuffer1[2]) fObjLabel(ObjName,200,5,"Red: up "+percent1+"%",3,TextColor,8,WindowFind(ShortName),"Arial Black",false);
if (spectrometerbuffer1[1]<spectrometerbuffer1[2]) fObjLabel(ObjName,200,5,"Red: down "+percent1+"%",3,TextColor,8,WindowFind(ShortName),"Arial Black",false);
if (spectrometerbuffer1[1]==spectrometerbuffer1[2]) fObjLabel(ObjName,200,5,"Red: flat "+percent1+"%",3,TextColor,8,WindowFind(ShortName),"Arial Black",false);
*/
ObjName=ObjNPref+"iupdn2";
/*
if (ExtMapBuffer2[1]>ExtMapBuffer2[2]) fObjLabel(ObjName,300,5,"Orange: up "+percent2+"%",3,TextColor,8,WindowFind(ShortName),"Arial Black",false);
if (ExtMapBuffer2[1]<ExtMapBuffer2[2]) fObjLabel(ObjName,300,5,"Orange: down "+percent2+"%",3,TextColor,8,WindowFind(ShortName),"Arial Black",false);
if (ExtMapBuffer2[1]==ExtMapBuffer2[2]) fObjLabel(ObjName,300,5,"Orange: flat "+percent2+"%",3,TextColor,8,WindowFind(ShortName),"Arial Black",false);
 */
        
   return(0);
}

int fLinearRegressionAll2(int i0,int i1, int aPrice, int & aPeriod, double & aVal_0, double & aVal_1, double & aB, double & aMaxDev, double & aStdError, double & aRSquared,arrayofdoubles & aArr,int intcurtf){

int i;
   int rRetError=0;
   double x,y,y1,y2,sumy,sumx,sumxy,sumx2,sumy2,sumx22,sumy22,div1,div2;   
   aPeriod=i1-i0+1;
   sumy=0.0;sumx=0.0;sumxy=0.0;sumx2=0.0;sumy2=0.0;
      for(i=0; i<aPeriod; i++){
         y=ima(intcurtf,1,0,0,aPrice,i0+i);
         x=i;
         sumy+=y;
         sumxy+=y*i;
         sumx+=x;
         sumx2+=pow(x,2);  
         sumy2+=pow(y,2);         
      } 
   sumx22=pow(sumx,2);  
   sumy22=pow(sumy,2);      
   div1=sumx2*aPeriod-sumx22;
   div2=sqrt((aPeriod*sumx2-sumx22)*(aPeriod*sumy2-sumy22)); 

   //---- regression line ----
   
      if(div1!=0.0){
         aB=(sumxy*aPeriod-sumx*sumy)/div1;
         aVal_0=(sumy-sumx*aB)/aPeriod;
         aVal_1=aVal_0+aB*(aPeriod-1);
         rRetError+=-1;
      }
      else{
         rRetError+=-1;      
      }

   //--- stderr & maxdev

   aMaxDev=0;aStdError=0;
   
      for(i=0;i<aPeriod;i++){
         y1=ima(intcurtf,1,0,0,aPrice,i0+i);
         y2=aVal_0+aB*i;
         aMaxDev=max(fabs(y1-y2),aMaxDev);
         aStdError+=pow(y1-y2,2);
      }
      
   aStdError=sqrt(aStdError/aPeriod);

   //--- rsquared ---

      if(div2!=0){
         aRSquared=pow((aPeriod*sumxy-sumx*sumy)/div2,2); 

      }   
      else{
         rRetError+=-2;
      }
   
   //----
   
   //ArrayResize(aArr,aPeriod);

      for(i=0; i<aPeriod; i++){
         y=ima(intcurtf,1,0,0,aPrice,i0+i);
         x=aVal_0+i*(aVal_1-aVal_0)/aPeriod;
         aArr[i]=y-x;
      } 

   return(rRetError);   
}

int fFurie(arrayofdoubles aArr,arrayofdoubles & aA,arrayofdoubles & aB,arrayofdoubles & aR, arrayofdoubles & aF){
 
   //int tN=aArr.size();
  
   //int tM=tN/2;

   int tN=240;
   int tM=tN/2; 



   //ArrayResize(aA,tM);

   //ArrayResize(aB,tM);
  
   //ArrayResize(aR,tM);
 
   //ArrayResize(aF,tM);                           
   
      for (int ti=1;ti<tM;ti++){
         aA[ti]=0;
         aB[ti]=0;
            for(int tj=0;tj<tN;tj++){
               aA[ti]+=aArr[tj]*sin(ti*6.28*tj/tN);
               aB[ti]+=aArr[tj]*cos(ti*6.28*tj/tN);
            }
         aA[ti]=2*aA[ti]/tN;
         aB[ti]=2*aB[ti]/tN;  
         aR[ti]=sqrt(pow(aA[ti],2)+pow(aB[ti],2));
         aF[ti]=atan2(aB[ti],aA[ti]);
      }

return 0;
       
}

double fMyArcTan(double aS,double aC){
   if(aS==0){
      return(0);   
   }
   if(aC==0){
      if(aS>0){
         return(atan(1)*2);
      }
      else{
         if(aS<0){
            return(atan(1)*6);         
         }
      }
   }
   else{
      if(aS>0){
         if(aC>0){
            return(atan(aS/aC));  
         }
         else{
            return(atan(aS/aC)+atan(1)*4);          
         }   
      }
      else{
         if(aC>0){
            return(atan(aS/aC)+atan(1)*8);           
         }
         else{
            return(atan(aS/aC)+atan(1)*4);           
         }      
      }
   }

return 0;

}


/*
void fObjDeleteByPrefix(string aPrefix){
   for(int i=ObjectsTotal()-1;i>=0;i--){
      if(StringFind(ObjectName(i),aPrefix,0)==0){
         ObjectDelete(ObjectName(i));
      }
   }
}

*/