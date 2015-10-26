static arrayofdoubles  fx2;static arrayofdoubles sqh2;static arrayofdoubles sql2;static arrayofdoubles stdh2;static arrayofdoubles stdl2;

char* rstlcogcpp(char* barsback,char* kstdd)
{

static arrayofdoubles RSTLbuffertmp;
	int i=300;
        while(i>=0)
        {
RSTLbuffertmp[i]= 
-0.00514293*closea[i+0] 
-0.00398417*closea[i+1] 
-0.00262594*closea[i+2] 
-0.00107121*closea[i+3] 
+0.00066887*closea[i+4] 
+0.00258172*closea[i+5] 
+0.00465269*closea[i+6] 
+0.00686394*closea[i+7] 
+0.00919334*closea[i+8] 
+0.01161720*closea[i+9] 
+0.01411056*closea[i+10] 
+0.01664635*closea[i+11] 
+0.01919533*closea[i+12] 
+0.02172747*closea[i+13] 
+0.02421320*closea[i+14] 
+0.02662203*closea[i+15] 
+0.02892446*closea[i+16] 
+0.03109071*closea[i+17] 
+0.03309496*closea[i+18] 
+0.03490921*closea[i+19] 
+0.03651145*closea[i+20] 
+0.03788045*closea[i+21] 
+0.03899804*closea[i+22] 
+0.03984915*closea[i+23] 
+0.04042329*closea[i+24] 
+0.04071263*closea[i+25] 
+0.04071263*closea[i+26] 
+0.04042329*closea[i+27] 
+0.03984915*closea[i+28] 
+0.03899804*closea[i+29] 
+0.03788045*closea[i+30] 
+0.03651145*closea[i+31] 
+0.03490921*closea[i+32] 
+0.03309496*closea[i+33] 
+0.03109071*closea[i+34] 
+0.02892446*closea[i+35] 
+0.02662203*closea[i+36] 
+0.02421320*closea[i+37] 
+0.02172747*closea[i+38] 
+0.01919533*closea[i+39] 
+0.01664635*closea[i+40] 
+0.01411056*closea[i+41] 
+0.01161720*closea[i+42] 
+0.00919334*closea[i+43] 
+0.00686394*closea[i+44] 
+0.00465269*closea[i+45] 
+0.00258172*closea[i+46] 
+0.00066887*closea[i+47] 
-0.00107121*closea[i+48] 
-0.00262594*closea[i+49] 
-0.00398417*closea[i+50] 
-0.00514293*closea[i+51] 
-0.00609634*closea[i+52] 
-0.00684602*closea[i+53] 
-0.00739452*closea[i+54] 
-0.00774847*closea[i+55] 
-0.00791630*closea[i+56] 
-0.00790940*closea[i+57] 
-0.00774085*closea[i+58] 
-0.00742482*closea[i+59] 
-0.00697718*closea[i+60] 
-0.00641613*closea[i+61] 
-0.00576108*closea[i+62] 
-0.00502957*closea[i+63] 
-0.00423873*closea[i+64] 
-0.00340812*closea[i+65] 
-0.00255923*closea[i+66] 
-0.00170217*closea[i+67] 
-0.00085902*closea[i+68] 
-0.00004113*closea[i+69] 
+0.00073700*closea[i+70] 
+0.00146422*closea[i+71] 
+0.00213007*closea[i+72] 
+0.00272649*closea[i+73] 
+0.00324752*closea[i+74] 
+0.00368922*closea[i+75] 
+0.00405000*closea[i+76] 
+0.00433024*closea[i+77] 
+0.00453068*closea[i+78] 
+0.00465046*closea[i+79] 
+0.00469058*closea[i+80] 
+0.00466041*closea[i+81] 
+0.00457855*closea[i+82] 
+0.00442491*closea[i+83] 
+0.00423019*closea[i+84] 
+0.00399201*closea[i+85] 
+0.00372169*closea[i+86] 
+0.00342736*closea[i+87] 
+0.00311822*closea[i+88] 
+0.00280309*closea[i+89] 
+0.00249088*closea[i+90] 
+0.00219089*closea[i+91] 
+0.00191283*closea[i+92] 
+0.00166683*closea[i+93] 
+0.00146419*closea[i+94] 
+0.00131867*closea[i+95] 
+0.00124645*closea[i+96] 
+0.00126836*closea[i+97] 
-0.00401854*closea[i+98]; 
i--;         
}

int bars_back;int m;double kstd;int sname;
boost::multi_array<double, 2> static ai(boost::extents[281][1000]);static arrayofdoubles b;static arrayofdoubles x;static arrayofdoubles sx;
double sum;
int ip;int p;int f;
double qq;double mm;double tt;
int ii;int jj;int kk;int ll;int nn;
double sq;double std;
/*int i;*/int j;int n;

static char kstddd[1000];
strncpy(kstddd, kstdd, 1000);
int kstddint=atoi(kstddd);

bars_back=240;
m=2;
i=0;
kstd=kstddint;
sname=1102;
p=bars_back;
nn=m+1;
    
static char barsbackk[1000];
strncpy(barsbackk, barsback, 1000);
int barsbackint=atoi(barsbackk);
bars_back=barsbackint;
p=bars_back;
    int mi;
    
    p=bars_back;
    sx[1]=p+1;
    
    for (mi=1;mi<=nn*2-2;mi++) {
        sum=0;
        for (n=i;n<=i+p;n++) {
            sum=sum+pow(double(n),double(mi));
                               }
        sx[mi+1]=sum;
                               } 

    for (mi=1;mi<=nn;mi++) {
        sum=0;
        for (n=i;n<=i+p;n++) {
            if (mi==1) sum=sum+RSTLbuffertmp[n];
            else sum=sum+RSTLbuffertmp[n]*pow(double(n),double(mi-1));            
                             }
        b[mi]=sum;
                            }

    for (jj=1;jj<=nn;jj++) {
        for (ii=1;ii<=nn;ii++) {
            kk=ii+jj-1;
            ai[ii][jj]=sx[kk];
                                }
                           }
    
    for (kk=1;kk<=nn-1;kk++) {
        ll=0;mm=0;
        for (ii=kk;ii<=nn;ii++) {
            if (fabs(ai[ii][kk])>mm) {
                mm=fabs(ai[ii][kk]);
                ll=ii;
                                   }
                                 }
        
        if (ll==0) return 0;
        
        if (ll!=kk) {
            for (jj=1;jj<=nn;jj++) {
                tt=ai[kk][jj];
                ai[kk][jj]=ai[ll][jj];
                ai[ll][jj]=tt;
                                    }
            tt=b[kk];b[kk]=b[ll];b[ll]=tt;
                    }
        
        for (ii=kk+1;ii<=nn;ii++) {
            qq=ai[ii][kk]/ai[kk][kk];
            for (jj=1;jj<=nn;jj++) {
                if (jj==kk) ai[ii][jj]=0;
                else ai[ii][jj]=ai[ii][jj]-qq*ai[kk][jj];
                                   }
            b[ii]=b[ii]-qq*b[kk];
                                  }
                               }
    
    x[nn]=b[nn]/ai[nn][nn];
    
    for (ii=nn-1;ii>=1;ii--) {
        tt=0;
        for (jj=1;jj<=nn-ii;jj++) {
            tt=tt+ai[ii][ii+jj]*x[ii+jj];
            x[ii]=(1/ai[ii][ii])*(b[ii]-tt);
                                  }
                             }
    
    for (n=i;n<=i+p;n++) {
        sum=0;
        for (kk=1;kk<=m;kk++) {
            sum=sum+x[kk+1]*pow(double(n),double(kk));
                               }
        fx2[n]=x[1]+sum;

                         }
    
    sq=0;
    
    for (n=i;n<=i+p;n++) {
        sq=sq+pow((RSTLbuffertmp[n]-fx2[n]),2);
                          }
    
    sq=sqrt(sq/(p+1))*kstd;
    stddev();
    std=stddevbuffer[i]*kstd;
    
    for (n=i;n<=i+p;n++) {
        sqh2[n]=fx2[n]+sq;
        sql2[n]=fx2[n]-sq;
        stdh2[n]=fx2[n]+std;
        stdl2[n]=fx2[n]-std;
                         }
return 0;    
}