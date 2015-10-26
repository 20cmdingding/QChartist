char* bandssmacpp(char*);

static arrayofdoubles bandsmovingbuffer;
static arrayofdoubles bandsupperbuffer;
static arrayofdoubles bandslowerbuffer;
static arrayofdoubles bandssmabuffer;

char* bandscpp (char* period)
{
static char periodd[1000];
strncpy(periodd, period, 1000);
int bandsperiod=atoi(periodd);
double bandsdeviations=2; 
int i;
int k;
double deviation;
double sum;
double oldval;
double newres; 

if (bars<=bandsperiod) return 0;

int limit=1000;
bandssmacpp(periodd);
for (i=0 ; i<=limit-1;i++) {
    bandsmovingbuffer[i]=bandssmabuffer[i];
}

i=1000-bandsperiod+1;
while (i>=0) {
    sum=0;
    k=i+bandsperiod-1;
    oldval=bandsmovingbuffer[i];
    while (k>=i) {
        newres=closea[k]-oldval;
        sum+=newres*newres;
        k--;
        }
    deviation=bandsdeviations*sqrt(sum/bandsperiod);
    bandsupperbuffer[i]=oldval+deviation;
    bandslowerbuffer[i]=oldval-deviation;
    i--;
}
return 0;  
}



char* bandssmacpp(char* period)
{
	static char periodd[1000];
	strncpy(periodd, period, 1000);
    int bandsperiod=atoi(periodd);
    double sum=0;
    int i;
    int p;
    p=bars-1;
    p=1000;
    if (p<bandsperiod) p=bandsperiod;
    for (i=1;i<=bandsperiod-1;i++) {
        sum=sum+closea[p];
        p--;
                                   }
    while (p>=0) {
        sum=sum+closea[p];
        bandssmabuffer[p]=sum/bandsperiod;
        sum=sum-closea[p+bandsperiod-1];
        p--;
                 }
return 0;  
}

