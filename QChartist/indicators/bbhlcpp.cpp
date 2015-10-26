static arrayofdoubles extmapbuffer2;

char* fsma();

static int intperiod;
static int intbarsback;

char* fsma()
{
    double sum=0;
    int i; int p=1000;
    //if (p<intperiod) {
    //    p=intperiod;
    //                 }
    for (i=1; i<=intperiod-1;i++) {
        sum=sum+(higha[p]+lowa[p])/2;
        p--;
                                  }
    while (p>=0) {
        sum=sum+(higha[p]+lowa[p])/2;
        extmapbuffer2[p]=sum/intperiod;
        sum=sum-(higha[p+intperiod-1]+lowa[p+intperiod-1])/2;
        p--;
                 }
return 0;
}

static arrayofdoubles mabuffer;static arrayofdoubles upperbandbuffer;static arrayofdoubles lowerbandbuffer;static arrayofdoubles devsbuffer;

char* bbhlcpp (char* period,char* barsback)
{
    static char periodd[1000];
    strncpy(periodd, period, 1000);
    intperiod=atoi(periodd);
    static char barsbackk[1000];
    strncpy(barsbackk, barsback, 1000);
    intbarsback=atoi(barsbackk);
    int per=intperiod;    
    int limit;
    double d1;double d2;double ma;
    limit=intbarsback;
    fsma();
    int i;
    for (i=limit;i>=0;i--) {
        ma=extmapbuffer2[i];
        d1=higha[i]-ma;
        d1=d1*d1;
        d2=lowa[i]-ma;
        d2=d2*d2;
        mabuffer[i]=ma;    
        if (d1>d2) devsbuffer[i]=d1;
        if (d1<d2) devsbuffer[i]=d2;
        if (d1==d2) devsbuffer[i]=d1;
                           }

    upperbandbuffer[limit]=0;
    lowerbandbuffer[limit]=0;

    int j;
    
    for (i=limit;i>=0;i--) {
        d1=0;
        for (j=i;j<=i+per-1;j++) {
            d1=d1+devsbuffer[j];
                             }
        d1=d1/per;
        d2=2*sqrt(d1);
        ma=mabuffer[i];
        upperbandbuffer[i]=ma+d2;
        lowerbandbuffer[i]=ma-d2;
                           }
return 0;
}
