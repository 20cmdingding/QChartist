static arrayofdoubles ema20buffer;
static arrayofdoubles extmapbuffer9;

char* ema20();

char* ema20()
{
    int per=20;

    double pr;
    pr=2/(per+1);
    int i;int p;
    p=bars-2;
    p=1000;
    while (p>=0) {
        if (p==1000) extmapbuffer9[p+1]=(higha[p+1]+lowa[p+1])/2;
        ema20buffer[p]=((higha[p]+lowa[p])/2)*pr+extmapbuffer9[p+1]*(1-pr);
        p--;
                 }
return 0;
}

char* stddev();

static arrayofdoubles stddevbuffer;

char* stddev()
{
    int stddivperiod=225;int shift=0;
    int i;int k;
    double deviation;double sum;double oldval;double newres;
    int limit;
    limit=1000;	
    ema20();
    for (i=0;i<=limit-1;i++) {
        stddevbuffer[i]=ema20buffer[i];
                               }
    i=1000;

    while (i>=0)
    {
        sum=0;
        k=i+stddivperiod-1;
        oldval=stddevbuffer[i];
        while (k>=i)
        {
            newres=closea[k]-oldval;
            sum=sum+newres*newres;
            k--;
        }
        deviation=sqrt(sum/stddivperiod);
        stddevbuffer[i]=deviation; // this line makes a bug with bar 0
        i--;
    }
return 0;
}

static arrayofdoubles  fx;static arrayofdoubles sqh;static arrayofdoubles sql;static arrayofdoubles stdh;static arrayofdoubles stdl;

char* cogcpp(char* barsback)
{

int bars_back;int m;double kstd;int sname;
boost::multi_array<double, 2> static ai(boost::extents[281][1000]);static arrayofdoubles b;static arrayofdoubles x;static arrayofdoubles sx;
double sum;
int ip;int p;int f;
double qq;double mm;double tt;
int ii;int jj;int kk;int ll;int nn;
double sq;double std;
int i;int j;int n;

bars_back=225;
m=4;
i=0;
kstd=2;
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
            if (mi==1) sum=sum+closea[n];
            else sum=sum+closea[n]*pow(double(n),double(mi-1));            
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
        fx[n]=x[1]+sum;
                         }

    sq=0;
    
    for (n=i;n<=i+p;n++) {
        sq=sq+pow((closea[n]-fx[n]),2);
                          }
    
    sq=sqrt(sq/(p+1))*kstd;
    //stddev();
    //std=stddevbuffer[i]*kstd;
    
    for (n=i;n<=i+p;n++) {
        sqh[n]=fx[n]+sq;
        sql[n]=fx[n]-sq;
        stdh[n]=fx[n]+sq; //std;
        stdl[n]=fx[n]-sq; //std;
                         }
return 0;    
}