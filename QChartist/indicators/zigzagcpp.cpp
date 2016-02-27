static arrayofdoubles zigzagbuffer;
static arrayofdoubles highmapbuffer;
static arrayofdoubles lowmapbuffer;

char* zigzagcpp (char* barsback,char* extdepthf)
{ 
    static int intbarsback;
    static int intextdepth;
    static char barsbackk[1000];
    strncpy(barsbackk, barsback, 1000);
    intbarsback=atoi(barsbackk);        
    static char extdepthh[1000];
    strncpy(extdepthh, extdepthf, 1000);
    intextdepth=atoi(extdepthh);  
                  
        
int extdepth;int extdeviation;int extbackstep; int level;int downloadhistory;
extdepth=intextdepth;
extdeviation=5;
extbackstep=3;
level=3;
downloadhistory=0;
int i;int counted_bars;int p;
int limit;int counterZ;int whatlookfor;
int shift;int back;int lasthighpos;int lastlowpos;
double valzigzag;double res;
double curlow;double curhigh;double lasthigh;double lastlow;
double ARMin;double ARMax;
ARMin=0;
ARMax=0;
p=0;
int counterz=0;
whatlookfor=0;
shift=0;
back=0;
lasthighpos=0;
lastlowpos=0;
valzigzag=0;
res=0;
curlow=0;
curhigh=0;
lasthigh=0;
lastlow=0;

for (i=0;i<=numbars_last+numbars+1000;i++) {
zigzagbuffer[i]=0;
highmapbuffer[i]=0;
lowmapbuffer[i]=0;
                      }
                                            


while ((counterz<level) && (i<numbars_last+numbars+1000)) {
    res=zigzagbuffer[i];
    if (res!=0) counterz++;      
    i++;

                                         }
i--;
limit=i;

if (lowmapbuffer[i]!=0) {
    curlow=lowmapbuffer[i];
    whatlookfor=1;
                        }
else {                        
    curhigh=highmapbuffer[i];
    whatlookfor=-1;
     }
for (i=numbars_last+numbars+1000-1;i>=0;i--) {
    zigzagbuffer[i]=0;
    lowmapbuffer[i]=0;
    highmapbuffer[i]=0;
                         }

for (shift=numbars_last+numbars+1000;shift>=numbars_last;shift--) {

//find min element of array
//defint p

ARMin=lowa[shift];

for (p = shift;p<=shift+extdepth-1;p++) {
if (lowa[p] < ARMin) ARMin = lowa[p];
                                        }

valzigzag=ARMin;


//print valzigzag

    //valzigzag=low(ARRMin(low,shift,shift+extdepth-1))

    if (valzigzag==lastlow) valzigzag=0;
    else {
        lastlow=valzigzag;
        if (lowa[shift]-valzigzag>0.0001) valzigzag=0;
        else {
            for (back=1;back<=extbackstep;back++) {
                res=lowmapbuffer[shift+back];
                if ((res!=0) && (res>valzigzag)) lowmapbuffer[shift+back]=0;                
                                                  }
             }
         }
    if (lowa[shift]==valzigzag) lowmapbuffer[shift]=valzigzag;
    else lowmapbuffer[shift]=0;
    //valzigzag=high(ARRMax(high,shift,shift+extdepth-1))
    
    //find max element of array
//defint p

ARMax=higha[shift];

for (p = shift;p<=shift+extdepth-1;p++) {
if (higha[p] > ARMax) ARMax = higha[p];
                                        }

valzigzag=ARMax;

    if (valzigzag==lasthigh) valzigzag=0;
    else {
        lasthigh=valzigzag;
        if (valzigzag-higha[shift]>0.0001) valzigzag=0;
        else {
            for (back=1;back<=extbackstep;back++) {
                res=highmapbuffer[shift+back];
                if ((res!=0) && (res<valzigzag)) highmapbuffer[shift+back]=0;
                                                  }
             }
         }
    if (higha[shift]==valzigzag) highmapbuffer[shift]=valzigzag;
    else highmapbuffer[shift]=0;
                                   }

// final cutting
if (whatlookfor==0) {
    lastlow=0;
    lasthigh=0;
                    }
else {
    lastlow=curlow;
    lasthigh=curhigh;
     }
for (shift=numbars_last+numbars+1000;shift>=numbars_last;shift--) {
    res=0;
    switch (whatlookfor) {
        case 0:
            if ((lastlow==0) && (lasthigh==0)) {

                if (highmapbuffer[shift]!=0) {
                    lasthigh=higha[shift];
                    lasthighpos=shift;
                    whatlookfor=-1;
                    zigzagbuffer[shift]=lasthigh;
                    res=1;
                                             }
                if (lowmapbuffer[shift]!=0) {
                    lastlow=lowa[shift];
                    lastlowpos=shift;
                    whatlookfor=1;
                    zigzagbuffer[shift]=lastlow;
                    res=1;
                                            }
                                               }
            
        case 1:

            if ((lowmapbuffer[shift]!=0) && (lowmapbuffer[shift]<lastlow) && (highmapbuffer[shift]==0)) {
                zigzagbuffer[lastlowpos]=0;
                lastlowpos=shift;
                lastlow=lowmapbuffer[shift];
                zigzagbuffer[shift]=lastlow;
                res=1;
                                                                                                        }
            if ((highmapbuffer[shift]!=0) && (lowmapbuffer[shift]==0)) {
                lasthigh=highmapbuffer[shift];
                lasthighpos=shift;
                zigzagbuffer[shift]=lasthigh;
                whatlookfor=-1;
                res=1;
                                                                       }
            
        case -1:

            if ((highmapbuffer[shift]!=0) && (highmapbuffer[shift]>lasthigh) && (lowmapbuffer[shift]==0)) {
                zigzagbuffer[lasthighpos]=0;
                lasthighpos=shift;
                lasthigh=highmapbuffer[shift];
                zigzagbuffer[shift]=lasthigh;
                                                                                                          }
            if ((lowmapbuffer[shift]!=0) && (highmapbuffer[shift]==0)) {
                lastlow=lowmapbuffer[shift];
                lastlowpos=shift;
                zigzagbuffer[shift]=lastlow;
                whatlookfor=1;
                                                                       }
            
                         }


                                   }
        
        
        
return 0;
}
