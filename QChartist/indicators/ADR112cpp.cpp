static arrayofdoubles ADR112cppbuffer1; // This line of code must stay here.
static arrayofdoubles ADR112cppbuffer2;
static arrayofdoubles ADR112cppbuffer3;
static arrayofdoubles ADR112cppbuffer4;
static arrayofdoubles ADR112cppbuffer5;

char* ADR112cpp (char* period,char* tfbase)
{
    static char periodd[1000];
    strncpy(periodd, period, 1000);
    int intperiod=atoi(periodd);
    static char tfbasee[1000];
    strncpy(tfbasee, tfbase, 1000);
    int inttfbase=atoi(tfbasee);
    int adrperiod;
    adrperiod=intperiod;//14;
    int limit;
    limit=700;
    int iadr;
    int kadr;
    iadr=0;
    kadr=0;
    double adr;
    double open2;
    adr=0;
    open2=0;
    // Put your indicator C++ code here
        for (iadr=0;iadr<limit;iadr++)
        {
        for (kadr=1;kadr<=adrperiod;kadr++) {
            switch (inttfbase) {
            case 0:
            adr=adr+(high1440[kadr+ibarshift(1440,datetimeserial[iadr],20)]-low1440[kadr+ibarshift(1440,datetimeserial[iadr],20)]);
            break;
            case 1:
            adr=adr+(high10080[kadr+ibarshift(10080,datetimeserial[iadr],20)]-low10080[kadr+ibarshift(10080,datetimeserial[iadr],20)]);
            break;
	    case 2:
            adr=adr+(high43200[kadr+ibarshift(43200,datetimeserial[iadr],20)]-low43200[kadr+ibarshift(43200,datetimeserial[iadr],20)]);
            break;
                               }
                                            }
        adr=adr/adrperiod;
        switch (inttfbase) {
        case 0:
        open2=open1440[ibarshift(1440,datetimeserial[iadr],20)];
        break;
        case 1:
        open2=open10080[ibarshift(10080,datetimeserial[iadr],20)];
        break;
	case 2:
        open2=open43200[ibarshift(43200,datetimeserial[iadr],20)];
        break;
                           }        
        ADR112cppbuffer1[iadr]=open2+adr;
        ADR112cppbuffer2[iadr]=open2+adr/2;
        ADR112cppbuffer3[iadr]=open2;
        ADR112cppbuffer4[iadr]=open2-adr/2;
        ADR112cppbuffer5[iadr]=open2-adr;
        adr=0;
        }
return 0;
}