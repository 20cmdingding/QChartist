static arrayofdoubles sig1n; // This line of code must stay here.
static arrayofdoubles sig2n; // This line of code must stay here.

//+------------------------------------------------------------------+
//|                                                 3D Oscilator.mq4 |
//|                                                                  |
//|                                                                  |
//+------------------------------------------------------------------+
//#property copyright "Author - Luis Damiani. Ramdass - Conversion only"

//---- input parameters

//+------------------------------------------------------------------+
//|   CCI_Woodies                                                    |
//+------------------------------------------------------------------+
char* threeD_Oscilator (char* period,char* curtf)
  {
    static char periodd[1000];
    strncpy(periodd, period, 1000);
    int intperiod=atoi(periodd);

static char curtff[1000];
    strncpy(curtff, curtf, 1000);
    int intcurtf=atoi(curtff);

int D1RSIPer = 13;
int D2StochPer = 8;
int D3tunnelPer = 8;
double hot = 0.4;
int sigsmooth = 4;
int Bars=200;

    int i, i2;
    double rsi, maxrsi, minrsi, storsi, E3D, sig1, sig2, sk, ss, sk2;
    double cs;
    int init = 1;
    //----
    cs = D1RSIPer + D2StochPer + D3tunnelPer + hot + sigsmooth;
    if(Bars<=cs) 
        return(0);
    //if (init)
    //{
    ss = sigsmooth;
    if(ss < 2) 
        ss=2;
    sk = 2 / (ss + 1);
    sk2 = 2 / (ss*0.8 + 1);
    init=0;
    //----
    i = Bars - cs - 1;
    while(i >= 0)
      {
        rsi = irsi(intcurtf, D1RSIPer, PRICE_CLOSE, i);
        maxrsi = rsi;
        minrsi = rsi;
        for(i2 = i + D2StochPer; i2 >= i; i2--)
          {
            rsi = irsi(intcurtf, D1RSIPer, PRICE_CLOSE, i2);
            if(rsi > maxrsi) 
                maxrsi=rsi;
            if(rsi < minrsi) 
                minrsi = rsi;
          }
        storsi = ((rsi - minrsi) / (maxrsi - minrsi)*200 - 100);
        E3D = hot*icci(intcurtf, D3tunnelPer, PRICE_TYPICAL, i) + (1 - hot)*storsi;
        sig1n[i] = sk*E3D + (1 - sk)*sig1;
        sig2n[i] = sk2*sig1 + (1 - sk2)*sig2;
        sig1 = sig1n[i];
        sig2 = sig2n[i];
        i--;
      }
    return(0);
  }
//+------------------------------------------------------------------+