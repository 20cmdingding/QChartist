#define NDEBUG // disable assertion messages for boost multi_arrays
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <iostream.h>
//#include <fcntl.h>
#include <io.h>
#include <sstream>
#include <algorithm>    // std::copy
#include <boost/array.hpp>
#include <boost/multi_array.hpp>
#include <boost/lexical_cast.hpp>
//#include <cassert>
#include <iterator>
#define _POSIX_SOURCE
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
//#include <unistd.h>
#undef _POSIX_SOURCE
#include <windows.h>
#include <math.h>
#include <map>
#include <time.h>

using namespace std;

// sprintf(debugmsg,"%u",chartbars[displayedfile]);MessageBox( NULL, debugmsg,"Debug",MB_OK); use this where you need to debug the program
static char debugmsg[1000];

char* writetofile ( char*,int );
long dateserial (long,long,long);
long isleapyear(long);
int ibarshift (int,long,int,bool);
char* idate(int,int);
char* itime(int,int);
double iopen(int,int);
double ihigh(int,int);
double ilow(int,int);
double iclose(int,int);
int ivolume(int,int);
long idatetimeserial(int,int);
double iapplied_price(int,int,int);
double itype(int,int,int);
double ima(int,int,int,int,int,int);
double irsi(int,int,int,int);
double icci(int,int,int,int);
int ihighest(int,int,int,int);
int ilowest(int,int,int,int);
long calculate_seconds_since_1_1_1970(long,long,long, int, int, int);
long timeb(int);
double timeminute(double);
double timehour(double);
int timedayofweek(double);
double mathmax(double,double);
double mathmin(double,double);
long itimeb(int,int);
char* ut_to_date(long);
void DoEvents();

typedef boost::array<char*,5000> arrayofchars;
typedef boost::array<double,5000> arrayofdoubles;
typedef boost::array<int,5000> arrayofints;
typedef boost::array<long,5000> arrayoflongs;
boost::multi_array<char*, 2> static grid(boost::extents[281][10000]);
boost::multi_array<char*, 2> static gridtmp(boost::extents[281][10000]);

double imaonarray(arrayofdoubles&,int,int,int,int,int);

static arrayofchars datea;
static arrayofchars date1;
static arrayofchars date5;
static arrayofchars date15;
static arrayofchars date30;
static arrayofchars date60;
static arrayofchars date240;
static arrayofchars date1440;
static arrayofchars date10080;
static arrayofchars date43200;
static arrayofchars timea;
static arrayofchars time1;
static arrayofchars time5;
static arrayofchars time15;
static arrayofchars time30;
static arrayofchars time60;
static arrayofchars time240;
static arrayofchars time1440;
static arrayofchars time10080;
static arrayofchars time43200;
static arrayofdoubles opena;
static arrayofdoubles open1;
static arrayofdoubles open5;
static arrayofdoubles open15;
static arrayofdoubles open30;
static arrayofdoubles open60;
static arrayofdoubles open240;
static arrayofdoubles open1440;
static arrayofdoubles open10080;
static arrayofdoubles open43200;
static arrayofdoubles higha;
static arrayofdoubles high1;
static arrayofdoubles high5;
static arrayofdoubles high15;
static arrayofdoubles high30;
static arrayofdoubles high60;
static arrayofdoubles high240;
static arrayofdoubles high1440;
static arrayofdoubles high10080;
static arrayofdoubles high43200;
static arrayofdoubles lowa;
static arrayofdoubles low1;
static arrayofdoubles low5;
static arrayofdoubles low15;
static arrayofdoubles low30;
static arrayofdoubles low60;
static arrayofdoubles low240;
static arrayofdoubles low1440;
static arrayofdoubles low10080;
static arrayofdoubles low43200;
static arrayofdoubles closea;
static arrayofdoubles close1;
static arrayofdoubles close5;
static arrayofdoubles close15;
static arrayofdoubles close30;
static arrayofdoubles close60;
static arrayofdoubles close240;
static arrayofdoubles close1440;
static arrayofdoubles close10080;
static arrayofdoubles close43200;
static arrayofints volumea; 
static arrayofints volume1;
static arrayofints volume5;
static arrayofints volume15;
static arrayofints volume30;
static arrayofints volume60;
static arrayofints volume240;
static arrayofints volume1440;
static arrayofints volume10080;
static arrayofints volume43200;
static arrayoflongs datetimeserial; 
static arrayoflongs datetimeserial1;
static arrayoflongs datetimeserial5;
static arrayoflongs datetimeserial15;
static arrayoflongs datetimeserial30;
static arrayoflongs datetimeserial60;
static arrayoflongs datetimeserial240;
static arrayoflongs datetimeserial1440;
static arrayoflongs datetimeserial10080;
static arrayoflongs datetimeserial43200;
static arrayofchars datef;
static arrayofchars timef;
static arrayofdoubles openf;
static arrayofdoubles highf;
static arrayofdoubles lowf;
static arrayofdoubles closef;
static arrayofints volumef;
static arrayofints chartbars;
static arrayofints chartbarstmp;
static arrayofints charttf;
static int displayedfile;
static int rowgridoffset=0;
static int openedfilesnb=0;
static int bars;  
static arrayofchars importedfile; 
static int cntbarsedit=2000;  
const int PERIOD_M1=1;
const int PERIOD_M5=5;
const int PERIOD_M15=15;
const int PERIOD_M30=30;
const int PERIOD_H1=60;
const int PERIOD_H4=240;
const int PERIOD_D1=1440;
const int PERIOD_W1=10080;
const int PERIOD_MN1=43200;
const int MODE_SMA=0;
const int MODE_EMA=1;
const int MODE_SMMA=2;
const int MODE_LWMA=3;
const int PRICE_CLOSE=0;
const int PRICE_OPEN=1;
const int PRICE_HIGH=2;
const int PRICE_LOW=3;
const int PRICE_MEDIAN=4;
const int PRICE_TYPICAL=5;
const int PRICE_WEIGHTED=6;
const int MODE_OPEN=0;
const int MODE_LOW=1;
const int MODE_HIGH=2;
const int MODE_CLOSE=3;
const int MODE_VOLUME=4;
const int MODE_TIME=5;
const bool True=1;
const bool False=0;

std::string replaceSubstring(const std::string& string1,const std::string& string2,const std::string& string3)
{
    std::string newString;
    for (size_t i=0;i<string1.length();i++)
    {
        if (string1.substr(i,string2.length())==string2)
        {
            newString+=string3;
            i+=string2.length()-1; //skip other matched characters
        }
        else newString+=string1[i];
    }
    return newString;
}

inline int mypow(int a, int b)
{
    if (b==0) return 1;
    if (a==0) return 0;
    return a*mypow(a, b-1);
}

char* filegetline ( int linenb, char* flnme )
{
   static char filename[1000];
   strncpy(filename, flnme, 1000);
   FILE *file;
	int fd;
	fd = open(filename,O_RDONLY);
if(fd<0){
    printf("open call fail");
    //return -1;
 }
   file = fdopen ( fd, "r" );
//file = fopen ( filename, "r" );
	//printf("%d\n", fileno(file));
   int lineinc=0;        
   if ( file != NULL )
   {      
        
      char line [ 128 ]; /* or other suitable maximum line size */
      while ( fgets ( line, sizeof line, file ) != NULL ) /* read a line */
      {
        lineinc++;
        if (lineinc==linenb)
        {  
            fclose ( file );
            close (fd);
            return line;
            break;
        }
      }
      	
   }
   else
   {
      perror ( filename ); /* why didn't the file open? */
	strerror(errno);
   }
   //return 0; 
   
}

char* filegetalllines ( char* flnme,char* reinit )
{    
    static long int i;
    static char reinitt[1000];
   strncpy(reinitt,reinit,1000);
   if (atoi(reinitt)==1) 
    { 
    i=0;
    return ""; 
    }
   static char filename[1000];
   strncpy(filename, flnme, 1000);      
   
   FILE *file;
	int fd;
	fd = open(filename,O_RDONLY);
if(fd<0){
    printf("open call fail");
    //return -1;
 }
   file = fdopen ( fd, "r" );
//file = fopen ( filename, "r" );
	//printf("%d\n", fileno(file));
   int lineinc=0;        
   if ( file != NULL )
   {      	       

      fseek ( file ,i  , SEEK_SET );  
      char line [ 128 ]; /* or other suitable maximum line size */
      while ( fgets ( line, sizeof line, file ) != NULL ) /* read a line */
      {
        lineinc++;
        if (lineinc==1)
        {  
            
            i=ftell(file);
            fclose ( file );
            close (fd);          
            return line;
            break;
        }
      }
      	
   }
   else
   {
      perror ( filename ); /* why didn't the file open? */
	strerror(errno);
   }
   //return 0; 
   
}

int filegetlinecount(char* flnme )
{
   static char filename[1000];
   strncpy(filename, flnme, 1000);
   FILE *file = fopen ( filename, "r" );
   int lineinc=0;
   if ( file != NULL )
   {
      char line [ 128 ]; /* or other suitable maximum line size */
      while ( fgets ( line, sizeof line, file ) != NULL ) /* read a line */
      {
         //fputs ( line, stdout ); /* write the line */
	std::string linestr (line);  
        if (linestr.size()>1) lineinc++;
      }
      fclose ( file );
      return lineinc;
      
   }
   else
   {
      //perror ( filename ); /* why didn't the file open? */
	strerror(errno);
   }
   //return 0; 
}

char* filegetlinesarray ( char* flnme )
{  
       
   static char filename[1000];
   strncpy(filename, flnme, 1000);      
   FILE *file;
	int fd;
	fd = open(filename,O_RDONLY);
if(fd<0){
    printf("open call fail");
    //return -1;
 }
   file = fdopen ( fd, "r" );
//file = fopen ( filename, "r" );
	//printf("%d\n", fileno(file));
          
   if ( file != NULL )
   {      
      int i=0;  
      char line [ 128 ]; /* or other suitable maximum line size */ 
      char * writable;   
      while ( fgets ( line, sizeof line, file ) != NULL ) /* read a line */
      {
        
        std::string linestr (line);  
        if (linestr.size()>1) {          
        std::size_t found = linestr.find(",");        
        std::string datestr = linestr.substr (0,found);
        writable = new char[datestr.size() + 1];
        std::copy(datestr.begin(), datestr.end(), writable);
        writable[datestr.size()] = '\0'; // don't forget the terminating 0           
        //datef[i]=writable;
        grid[rowgridoffset+1][i+1]=writable;
        
        linestr.assign(linestr.begin()+found+1,linestr.end());
        found = linestr.find(",");
        std::string timestr = linestr.substr (0,found);
        writable = new char[timestr.size() + 1];
        std::copy(timestr.begin(), timestr.end(), writable);
        writable[timestr.size()] = '\0'; // don't forget the terminating 0
        //timef[i]=writable;
        grid[rowgridoffset+2][i+1]=writable;
        
        linestr.assign(linestr.begin()+found+1,linestr.end());
        found = linestr.find(",");
        std::string openstr = linestr.substr (0,found);
        writable = new char[openstr.size() + 1];
        std::copy(openstr.begin(), openstr.end(), writable);
        writable[openstr.size()] = '\0'; // don't forget the terminating 0
        //openf[i]=atof(writable);
        grid[rowgridoffset+3][i+1]=writable;
        
        linestr.assign(linestr.begin()+found+1,linestr.end());
        found = linestr.find(",");
        std::string highstr = linestr.substr (0,found);
        writable = new char[highstr.size() + 1];
        std::copy(highstr.begin(), highstr.end(), writable);
        writable[highstr.size()] = '\0'; // don't forget the terminating 0
        //highf[i]=atof(writable);
        grid[rowgridoffset+4][i+1]=writable;
        
        linestr.assign(linestr.begin()+found+1,linestr.end());
        found = linestr.find(",");
        std::string lowstr = linestr.substr (0,found);
        writable = new char[lowstr.size() + 1];
        std::copy(lowstr.begin(), lowstr.end(), writable);
        writable[lowstr.size()] = '\0'; // don't forget the terminating 0
        //lowf[i]=atof(writable); 
        grid[rowgridoffset+5][i+1]=writable;
        
        linestr.assign(linestr.begin()+found+1,linestr.end());
        found = linestr.find(",");
        std::string closestr = linestr.substr (0,found);
        writable = new char[closestr.size() + 1];
        std::copy(closestr.begin(), closestr.end(), writable);
        writable[closestr.size()] = '\0'; // don't forget the terminating 0
        //closef[i]=atof(writable);
        grid[rowgridoffset+6][i+1]=writable;
        
        linestr.assign(linestr.begin()+found+1,linestr.end());
        found = linestr.find(",");
        std::string volumestr = linestr.substr (0,found);
        writable = new char[volumestr.size() + 1];
        std::copy(volumestr.begin(), volumestr.end(), writable);
        writable[volumestr.size()] = '\0'; // don't forget the terminating 0
        //volumef[i]=atoi(writable);  
        grid[rowgridoffset+7][i+1]=writable;  
        
        gridtmp[rowgridoffset+1][i+1]=grid[rowgridoffset+1][i+1];  
        gridtmp[rowgridoffset+2][i+1]=grid[rowgridoffset+2][i+1];  
        gridtmp[rowgridoffset+3][i+1]=grid[rowgridoffset+3][i+1];  
        gridtmp[rowgridoffset+4][i+1]=grid[rowgridoffset+4][i+1];  
        gridtmp[rowgridoffset+5][i+1]=grid[rowgridoffset+5][i+1];  
        gridtmp[rowgridoffset+6][i+1]=grid[rowgridoffset+6][i+1];  
        gridtmp[rowgridoffset+7][i+1]=grid[rowgridoffset+7][i+1];  
    
        //cout << datef[i] << " " << timef[i] << " " << openf[i] << " " << highf[i] << " " << lowf[i] << " " << closef[i] << " " << volumef[i] << "\n";
        delete[] writable;
       i++;  
  
                         }
      }
      
   fclose ( file );
   close (fd); 
      	
   }
   else
   {
      perror ( filename ); /* why didn't the file open? */
	strerror(errno);
   }
   return 0; 
   
}

char* useindifunc (char* cntbarsedit)
{ 
static char cntbarseditt[1000];
strncpy(cntbarseditt, cntbarsedit, 1000);
int o=0;
                        
long year;long month;long day;int hour;int minute;int second;
int ii=chartbars[displayedfile] - atoi(cntbarseditt);
if (ii<1) ii=1;


                        for (int i = chartbars[displayedfile];i>= ii;i--)
                        {
                            datea[o] = grid[rowgridoffset + 1][i];
                            timea[o] = grid[rowgridoffset +  2][i];
                            opena[o] = atof(grid[rowgridoffset +  3][i]);
                            higha[o] = atof(grid[rowgridoffset +  4][i]);
                            lowa[o] = atof(grid[rowgridoffset +  5][i]);
                            closea[o] = atof(grid[rowgridoffset +  6][i]);
                            volumea[o] = atoi(grid[rowgridoffset +  7][i]);
                            std::string dateastr (datea[o]);
                            std::string timeastr (timea[o]);
                            std::string yearstr = dateastr.substr (0,4);
                            std::string monthstr = dateastr.substr (5,2);
                            std::string daystr = dateastr.substr (8,2);
                            std::string hourstr = timeastr.substr (0,2);
                            std::string minutestr = timeastr.substr (3,2);                            
                            year=atol(yearstr.c_str());                            
                            month=atol(monthstr.c_str());                            
                            day=atol(daystr.c_str());                            
                            hour=atoi(hourstr.c_str());                            
                            minute=atoi(minutestr.c_str());
			    second=0;

                            //year = VAL(MID$(date(o) , 0 , 4))
                            //month = VAL(MID$(date(o) , 6 , 2))
                            //day = VAL(MID$(date(o) , 9 , 2))
                            //hour = VAL(MID$(time(o) , 0 , 2))
                            //minute = VAL(MID$(time(o) , 4 , 2))
                            datetimeserial[o]=calculate_seconds_since_1_1_1970(year,month,day,hour,minute,second); //dateserial (year, month, day);
                            //datetimeserial[o]=datetimeserial[o]*24*60*60;
                            //datetimeserial[o]=datetimeserial[o]+(hour*60*60);
                            //datetimeserial[o]=datetimeserial[o]+(minute*60);                           
                            o++;
				DoEvents();
                        }
return 0;                        
}

char* writetofile ( char* flnme,int arrsize )
{  

static char filename[1000];
   strncpy(filename, flnme, 1000);
   FILE *file;
	int fd;
	if ((fd = creat(filename, S_IWUSR)) < 0)
    perror("creat() error");  
  else 
  {
  file = fdopen ( fd, "a" );
//file = fopen ( filename, "r" );
	//printf("%d\n", fileno(file));
          
   if ( file != NULL )
   {      
    int i;
    char catline[1000];
    for (i=0;i<=arrsize;i++)
      {
       fputs(datea[i], file);
       fputs(",", file);
       fputs(timea[i], file);
       fputs(",", file);       
       sprintf(catline,"%f",opena[i]);
       fputs(catline, file);
       fputs(",", file);       
       sprintf(catline,"%f",higha[i]);
       fputs(catline, file);
       fputs(",", file);       
       sprintf(catline,"%f",lowa[i]);
       fputs(catline, file);
       fputs(",", file);       
       sprintf(catline,"%f",closea[i]);
       fputs(catline, file);
       fputs(",", file);       
       sprintf(catline,"%u",volumea[i]);
       fputs(catline, file);
       fputs("\n", file);
      }    
      
            
   fclose ( file ); 
   close (fd);
       	
   }
   else
   {
      perror ( filename ); /* why didn't the file open? */
	strerror(errno);
   }
   //return 0;
   
   } 
return 0;
}

int delfile(char* flnme )
{
   static char filename[1000];
   strncpy(filename, flnme, 1000);
   if( remove( filename ) != 0 ) perror( "Error deleting file" );
  //else
    //puts( "File successfully deleted" );
  return 0;
}

char* displayedfileminusone ()
{  
displayedfile--;
return 0;
}

char* openedfilesnbminusone ()
{  
openedfilesnb--;
return 0;
}

char* openedfilesnbplusone ()
{  
openedfilesnb++;
return 0;
}

char* displayedfileplusone ()
{  
displayedfile++;
return 0;
}

char* setdisplayedfile (char* displayedfileint)
{  
static char displayedfileintt[1000];
strncpy(displayedfileintt, displayedfileint, 1000);
displayedfile=atoi(displayedfileintt);
return 0;
}

char* setchartbars (char* chartbarsdisplayedfileint,char* chartbarsoffset)
{  
static char chartbarsdisplayedfileintt[1000];
strncpy(chartbarsdisplayedfileintt, chartbarsdisplayedfileint, 1000);
static char chartbarsoffsett[1000];
strncpy(chartbarsoffsett, chartbarsoffset, 1000);
chartbars[atoi(chartbarsoffsett)]=atoi(chartbarsdisplayedfileintt);
return 0;
}

char* setchartbarstmp (char* chartbarstmpdisplayedfileint,char* chartbarstmpoffset)
{  
static char chartbarstmpdisplayedfileintt[1000];
strncpy(chartbarstmpdisplayedfileintt, chartbarstmpdisplayedfileint, 1000);
static char chartbarstmpoffsett[1000];
strncpy(chartbarstmpoffsett, chartbarstmpoffset, 1000);
chartbarstmp[atoi(chartbarstmpoffsett)]=atoi(chartbarstmpdisplayedfileintt);
return 0;
}

char* setcharttf (char* charttfdisplayedfileint,char* charttfoffset)
{  
static char charttfdisplayedfileintt[1000];
strncpy(charttfdisplayedfileintt, charttfdisplayedfileint, 1000);
static char charttfoffsett[1000];
strncpy(charttfoffsett, charttfoffset, 1000);
charttf[atoi(charttfoffsett)]=atoi(charttfdisplayedfileintt);
return 0;
}

char* setrowgridoffset (char* rowgridoffsetint)
{  
static char rowgridoffsetintt[1000];
strncpy(rowgridoffsetintt, rowgridoffsetint, 1000);
rowgridoffset=atoi(rowgridoffsetintt);
return 0;
}

char* setbars (char* barsint)
{  
static char barsintt[1000];
strncpy(barsintt, barsint, 1000);
bars=atoi(barsintt);
return 0;
}

char* setcntbarsedit (char* barsint)
{  
static char barsintt[1000];
strncpy(barsintt, barsint, 1000);
cntbarsedit=atoi(barsintt);
return 0;
}

char* setimportedfile (char* importedfilechar,char* importedfileoffset)
{  
static char importedfilecharr[1000];
strncpy(importedfilecharr, importedfilechar, 1000);
static char importedfileoffsett[1000];
strncpy(importedfileoffsett, importedfileoffset, 1000);
importedfile[atoi(importedfileoffsett)]=importedfilecharr;
return 0;
}

char* shiftgridsonebackward ()
{  
int i;int j;
        for (i = displayedfile;i<=openedfilesnb;i++) {
            for (j = 1; j<= chartbars[i+1];j++) {
                grid[7 * (i - 1) + 1 ][ j] = grid[7 * (i) + 1][j];
                grid[7 * (i - 1) + 2][j] = grid[7 * (i) + 2][j];
                grid[7 * (i - 1) + 3][j] = grid[7 * (i) + 3][j];
                grid[7 * (i - 1) + 4][j] = grid[7 * (i) + 4][j];
                grid[7 * (i - 1) + 5][j] = grid[7 * (i) + 5][j];
                grid[7 * (i - 1) + 6][j] = grid[7 * (i) + 6][j];
                grid[7 * (i - 1) + 7][j] = grid[7 * (i) + 7][j];
                gridtmp[7 * (i - 1) + 1 ][ j] = grid[7 * (i) + 1][j];
                gridtmp[7 * (i - 1) + 2][j] = grid[7 * (i) + 2][j];
                gridtmp[7 * (i - 1) + 3][j] = grid[7 * (i) + 3][j];
                gridtmp[7 * (i - 1) + 4][j] = grid[7 * (i) + 4][j];
                gridtmp[7 * (i - 1) + 5][j] = grid[7 * (i) + 5][j];
                gridtmp[7 * (i - 1) + 6][j] = grid[7 * (i) + 6][j];
                gridtmp[7 * (i - 1) + 7][j] = grid[7 * (i) + 7][j];
                //mixgrid.Cell(j - 1 , i) = mixgrid.Cell(j - 1 , i + 1)
                //mixgrid2.Cell(j - 1 , i) = mixgrid2.Cell(j - 1 , i + 1)
                //mixgrid3.Cell(j - 1 , i) = mixgrid3.Cell(j - 1 , i + 1)
                //mixgrid4.Cell(j - 1 , i) = mixgrid4.Cell(j - 1 , i + 1)
                                      }
            importedfile[i] = importedfile[i + 1];
            chartbars[i] = chartbars[i + 1];
            //mixgridcolcount(i) = mixgridcolcount(i + 1)
            //mixgridcolcount2(i) = mixgridcolcount2(i + 1)
            //mixgridcolcount3(i) = mixgridcolcount3(i + 1)
            //mixgridcolcount4(i) = mixgridcolcount4(i + 1)
                                                     }                                      
return 0;
}

char* reversebarscomputesubbcpp (char* graphbarnboncurstaticchar)
{ 
    static char referencialkk[1000];
    strncpy(referencialkk, graphbarnboncurstaticchar, 1000);
    int refk=atoi(referencialkk);
    int i;int j;


    //numbars = VAL(barsdisplayed.Text)

    int k;int l;int m;int incr;
    m = 1;
    incr = 0;

    double kbarlow;double kbarlowprev;
    double kbarhigh;double kbarhighprev;
    double kbaropen;double kbaropenprev;
    double kbarclose;double kbarcloseprev;
    double distcloseopen;double distclosehigh;double distcloselow;
    double distopenclose;double distopenhigh;double distopenlow;

    //char catline[1000];

    for (k = refk;k<=chartbars[displayedfile];k++) {


        kbarlow = atof(gridtmp[rowgridoffset + 5][k]);
        kbarhigh = atof(gridtmp[rowgridoffset + 4][k]);
        kbaropen = atof(gridtmp[rowgridoffset + 3][k]);
        kbarlowprev = atof(gridtmp[rowgridoffset + 5][refk - 1]);
        kbarhighprev = atof(gridtmp[rowgridoffset + 4][refk - 1]);
        kbaropenprev = atof(gridtmp[rowgridoffset + 3][refk - 1]);
        kbarclose = atof(gridtmp[rowgridoffset + 6][k]);
        kbarcloseprev = atof(gridtmp[rowgridoffset + 6][refk - 1]);

        if (kbaropen >= kbarclose) distopenclose = kbaropen - kbarclose;

        if (kbaropen < kbarclose) distopenclose = - 1 * (kbarclose - kbaropen);


        if (kbarhigh >= kbaropen) distopenhigh = - 1 * (kbarhigh - kbaropen);

        if (kbarhigh < kbaropen) distopenhigh = kbaropen - kbarhigh;


        if (kbarlow > kbaropen) distopenlow = - 1 * (kbarlow - kbaropen);

        if (kbarlow <= kbaropen) distopenlow = kbaropen - kbarlow;                               

        if (kbaropen > kbarcloseprev) sprintf(gridtmp[rowgridoffset + 3][k],"%f",kbarcloseprev - (kbaropen - kbarcloseprev));
            //gridtmp[rowgridoffset + 3][k] = catline;
                                      

        if (kbaropen < kbarcloseprev) sprintf(gridtmp[rowgridoffset + 3][k],"%f",kbarcloseprev + (kbarcloseprev - kbaropen));
            //gridtmp[rowgridoffset + 3][k] = catline;
                                      


        //gridtmp[rowgridoffset + 6][k] = ftoa(atof(gridtmp[rowgridoffset + 3][k]) + distopenclose);
        //gridtmp[rowgridoffset + 4][k] = ftoa(atof(gridtmp[rowgridoffset + 3][k]) + distopenlow);
        //gridtmp[rowgridoffset + 5][k] = ftoa(atof(gridtmp[rowgridoffset + 3][k]) + distopenhigh);
        
        sprintf(gridtmp[rowgridoffset + 6][k],"%f",atof(gridtmp[rowgridoffset + 3][k]) + distopenclose);
        sprintf(gridtmp[rowgridoffset + 4][k],"%f",atof(gridtmp[rowgridoffset + 3][k]) + distopenlow);
        sprintf(gridtmp[rowgridoffset + 5][k],"%f",atof(gridtmp[rowgridoffset + 3][k]) + distopenhigh);

        //writealive
                                                           }


    chartbarstmp[displayedfile] = chartbars[displayedfile];
    //chartbarstmpdisplayedfilestr=str$(chartbarstmp(displayedfile)):displayedfilestr=str$(displayedfile):cpptmpfuncreturn=varptr$(setchartbarstmp(varptr(chartbarstmpdisplayedfilestr),varptr(displayedfilestr)))

return 0;
}

char* refreshgridscpp()
{ 
    if (openedfilesnb == 0) return 0;

    int i;
    chartbars[displayedfile] = chartbarstmp[displayedfile];
    //chartbarsdisplayedfilestr=str$(chartbars(displayedfile)):displayedfilestr=str$(displayedfile):cpptmpfuncreturn=varptr$(setchartbars(varptr(chartbarsdisplayedfilestr),varptr(displayedfilestr)))

    for (i = 1;i<=chartbars[displayedfile];i++) {
        grid[rowgridoffset + 1][i] = gridtmp[rowgridoffset + 1][i];
        grid[rowgridoffset + 2][i] = gridtmp[rowgridoffset + 2][i];
        grid[rowgridoffset + 3][i] = gridtmp[rowgridoffset + 3][i];
        grid[rowgridoffset + 4][i] = gridtmp[rowgridoffset + 4][i];
        grid[rowgridoffset + 5][i] = gridtmp[rowgridoffset + 5][i];
        grid[rowgridoffset + 6][i] = gridtmp[rowgridoffset + 6][i];
        grid[rowgridoffset + 7][i] = gridtmp[rowgridoffset + 7][i];
        //writealive
                                                }
    //justrefreshchart
    
    return 0;
}

char* getdatagrid (char* rowgridoffset,char* offset)
{  
static char rowgridoffsett[1000];
strncpy(rowgridoffsett, rowgridoffset, 1000);
static char offsett[1000];
strncpy(offsett, offset, 1000);
return grid[atoi(rowgridoffsett)][atoi(offset)];
}

char* setdatagrid (char* rowgridoffset,char* offset,char* dataval)
{  
static char rowgridoffsett[1000];
strncpy(rowgridoffsett, rowgridoffset, 1000);
static char offsett[1000];
strncpy(offsett, offset, 1000);
static char datavall[1000];
strncpy(datavall, dataval, 1000);
grid[atoi(rowgridoffsett)][atoi(offset)]=datavall;
}

char* getchartbars (char* chartnb)
{  
static char chartnbb[1000];
strncpy(chartnbb, chartnb, 1000);
int chartnbint=atoi(chartnbb);
char catline[1000];
sprintf(catline,"%u",chartbars[chartnbint]);
return catline;
}

char* getchartbarstmp (char* chartnbtmp)
{  
static char chartnbb[1000];
strncpy(chartnbb, chartnbtmp, 1000);
int chartnbint=atoi(chartnbb);
char catline[1000];
sprintf(catline,"%u",chartbarstmp[chartnbint]);
return catline;
}

char* tfmultok_clickcpp(char* tfmult)
{
    static char tfmultt[1000];
strncpy(tfmultt, tfmult, 1000);
int tfmultint=atoi(tfmultt);
    if (openedfilesnb==0) return 0;

    int i;
    int j;
    double high;
    double low;
    int vol;
    int lines;
    lines = 1;    
    chartbars[displayedfile] = chartbarstmp[displayedfile];

    for (i = 1;i<=chartbars[displayedfile];i++) {
        grid[rowgridoffset + 1][i]=gridtmp[rowgridoffset + 1][i];
        grid[rowgridoffset + 2][i]=gridtmp[rowgridoffset + 2][i];
        grid[rowgridoffset + 3][i]=gridtmp[rowgridoffset + 3][i];
        grid[rowgridoffset + 4][i]=gridtmp[rowgridoffset + 4][i];
        grid[rowgridoffset + 5][i]=gridtmp[rowgridoffset + 5][i];
        grid[rowgridoffset + 6][i]=gridtmp[rowgridoffset + 6][i];
        grid[rowgridoffset + 7][i]=gridtmp[rowgridoffset + 7][i];
                                                } 
    for (j = 1;j<=chartbars[displayedfile];j=j+tfmultint) {
        if (j <= (chartbars[displayedfile] - tfmultint + 1)) {
            high = atof(grid[rowgridoffset + 4][j]);
            low = atof(grid[rowgridoffset + 5][j]);
            vol = 0;
            for (i = 1;i<=tfmultint;i++) {
                if (atof(grid[rowgridoffset + 4][j+i-1]) > high) high = atof(grid[rowgridoffset + 4][j+i-1]);
                if (atof(grid[rowgridoffset + 5][j+i-1]) < low) low = atof(grid[rowgridoffset + 5][j+i-1]);
                vol = vol + atoi(grid[rowgridoffset + 7][j+i-1]);
                                         }
            sprintf(grid[rowgridoffset + 4][lines],"%f",high);
            sprintf(grid[rowgridoffset + 5][lines],"%f",low);
            grid[rowgridoffset + 3][lines] = grid[rowgridoffset + 3][j];
            grid[rowgridoffset + 6][lines] = grid[rowgridoffset + 6][j + tfmultint - 1];
            sprintf(grid[rowgridoffset + 7][lines],"%u",vol);
            lines ++;
                                                             }
        if (j > (chartbars[displayedfile] - tfmultint + 1)) {
            high = atof(grid[rowgridoffset + 4][j]);
            low = atof(grid[rowgridoffset + 5][j]);
            vol = 0;
            for (i = 1 ;i<= chartbars[displayedfile] - j + 1;i++) {
                if (atof(grid[rowgridoffset + 4][j+i-1]) > high) high = atof(grid[rowgridoffset + 4][j+i-1]);
                if (atof(grid[rowgridoffset + 5][j+i-1]) < low) low = atof(grid[rowgridoffset + 5][j+i-1]);
                vol = vol + atoi(grid[rowgridoffset + 7][j+i-1]);
                                                                  }
            sprintf(grid[rowgridoffset + 4][lines],"%f",high);
            sprintf(grid[rowgridoffset + 5][lines],"%f",low);
            grid[rowgridoffset + 3][lines] = grid[rowgridoffset + 3][j];
            grid[rowgridoffset + 6][lines] = grid[rowgridoffset + 6][chartbars[displayedfile]];
            sprintf(grid[rowgridoffset + 7][lines],"%u",vol);
            lines ++;
                                                          }
                                                          }
    chartbars[displayedfile] = lines - 1;
    
return 0;    
}

char* savegridtmpcpp()
{

    for (int i = 1;i<=chartbars[displayedfile];i++) {
        gridtmp[rowgridoffset + 1][i] = grid[rowgridoffset + 1][i];
        gridtmp[rowgridoffset + 2][i] = grid[rowgridoffset + 2][i];
        gridtmp[rowgridoffset + 3][i] = grid[rowgridoffset + 3][i];
        gridtmp[rowgridoffset + 4][i] = grid[rowgridoffset + 4][i];
        gridtmp[rowgridoffset + 5][i] = grid[rowgridoffset + 5][i];
        gridtmp[rowgridoffset + 6][i] = grid[rowgridoffset + 6][i];
        gridtmp[rowgridoffset + 7][i] = grid[rowgridoffset + 7][i];
                                                    }
return 0;                                                    
}

long dateserial(long y,long m,long d)
{
    //declare
    long dayscount;long dayofmonth;long year;long month;

    //initialize
    dayscount = d;

    //process
    if (m > 1) {
        month = m;
        dayofmonth = 1040154527;
        if (((month > 2) && isleapyear(y))==1) dayofmonth = (dayofmonth + 32);
        do {
            dayscount = dayscount + (dayofmonth & 31);
            if (month == 2) break;
            month--;
            dayofmonth = trunc(round(dayofmonth) / 32);
            if (dayofmonth == 0) dayofmonth = 1072692223;
           }
        while (1==1);
               }

    //exit
    year = (y - 1);
    return (dayscount + (trunc(year) * 365) + (trunc(round(year) / 4)) - (trunc(round(year) / 100)) + (trunc(round(year) / 400)));
}

long isleapyear(long year)
{
    if ( ( (year % 4) == 0) && ( (year % 100) > 0) || ( (year % 400) == 0) ) return 1;
    else return 0;
}

int ibarshift (int timeframe,long datetimeserial,int limit,bool exact=0)
{
int i;
arrayofdoubles proxiarray;
double proxihighest;double proxilowest;

switch (exact) {
    case 0:
    proxihighest = 0;
    for (i = 0;i<=limit;i++) {
        proxiarray[i]=static_cast<double>(idatetimeserial(timeframe,i))/static_cast<double>(datetimeserial);
        if (proxiarray[i]>=1) proxiarray[i]=proxiarray[i]-1;
        else proxiarray[i]=1-proxiarray[i];        
        if (proxiarray[i] > proxihighest) proxihighest = proxiarray[i];           
    }
    proxilowest = proxihighest;
    for (i = 0;i<=limit;i++) {
            if (proxiarray[i] < proxilowest) proxilowest = proxiarray[i];            
        }
    for (i = 0;i<=limit;i++) {
            if (proxiarray[i]==proxilowest) {
                return i;
                break;
                                            }
        }   
        break;
        
    case 1:    
    for (i = 0;i<=limit;i++) {
	    long nextdatetimeserial=idatetimeserial(timeframe,i)+timeframe*60;
            if ((datetimeserial>=idatetimeserial(timeframe,i)) && (datetimeserial<nextdatetimeserial)) {	    
                return i;
                break;
                                            }
        }
        return -1;   
        break;
  
             }    
return 0;    
}

char* writetfcpp (char* tftowrite)
{
    
 if (openedfilesnb == 0) return 0;

 static char tftowritee[1000];
 strncpy(tftowritee, tftowrite, 1000);
 int tftowriteint=atoi(tftowritee);
 int o;int i;
 char * writable; 
 long year;long month;long day;int hour;int minute; int second;
 int ii=chartbars[displayedfile] - cntbarsedit; 
 if (ii<1) ii=1;

 switch (tftowriteint)
 {
     
     case 1:


                        
                        o = 0;                        

                        for (i = chartbars[displayedfile];i>=ii;i--) {
                            date1[o] = grid[rowgridoffset + 1][i];
                            time1[o] = grid[rowgridoffset + 2][i];
                            open1[o] = atof(grid[rowgridoffset + 3][i]);
                            high1[o] = atof(grid[rowgridoffset + 4][i]);
                            low1[o] = atof(grid[rowgridoffset + 5][i]);
                            close1[o] = atof(grid[rowgridoffset + 6][i]);
                            volume1[o] = atoi(grid[rowgridoffset + 7][i]);
                            std::string dateastr (date1[o]);
                            std::string timeastr (time1[o]);
                            std::string yearstr = dateastr.substr (0,4);
                            std::string monthstr = dateastr.substr (5,2);
                            std::string daystr = dateastr.substr (8,2);
                            std::string hourstr = timeastr.substr (0,2);
                            std::string minutestr = timeastr.substr (3,2);
                            year=atol(yearstr.c_str());                                                                             
                            month=atol(monthstr.c_str());                            
                            day=atol(daystr.c_str());                            
                            hour=atoi(hourstr.c_str());                            
                            minute=atoi(minutestr.c_str());
                second=0;
                datetimeserial1[o]=calculate_seconds_since_1_1_1970(year,month,day,hour,minute,second); //dateserial (year, month, day);
                            //datetimeserial5[o]=dateserial (year, month, day);
                            //datetimeserial5[o]=datetimeserial5[o]*24*60*60;
                            //datetimeserial5[o]=datetimeserial5[o]+(hour*60*60);
                            //datetimeserial5[o]=datetimeserial5[o]+(minute*60);
                            o ++;
                        }
                        break;
     
     case 5:


                        
                        o = 0;                        

                        for (i = chartbars[displayedfile];i>=ii;i--) {
                            date5[o] = grid[rowgridoffset + 1][i];
                            time5[o] = grid[rowgridoffset + 2][i];
                            open5[o] = atof(grid[rowgridoffset + 3][i]);
                            high5[o] = atof(grid[rowgridoffset + 4][i]);
                            low5[o] = atof(grid[rowgridoffset + 5][i]);
                            close5[o] = atof(grid[rowgridoffset + 6][i]);
                            volume5[o] = atoi(grid[rowgridoffset + 7][i]);
                            std::string dateastr (date5[o]);
                            std::string timeastr (time5[o]);
                            std::string yearstr = dateastr.substr (0,4);
                            std::string monthstr = dateastr.substr (5,2);
                            std::string daystr = dateastr.substr (8,2);
                            std::string hourstr = timeastr.substr (0,2);
                            std::string minutestr = timeastr.substr (3,2);
                            year=atol(yearstr.c_str());                                                                             
                            month=atol(monthstr.c_str());                            
                            day=atol(daystr.c_str());                            
                            hour=atoi(hourstr.c_str());                            
                            minute=atoi(minutestr.c_str());
			    second=0;
			    datetimeserial5[o]=calculate_seconds_since_1_1_1970(year,month,day,hour,minute,second); //dateserial (year, month, day);
                            //datetimeserial5[o]=dateserial (year, month, day);
                            //datetimeserial5[o]=datetimeserial5[o]*24*60*60;
                            //datetimeserial5[o]=datetimeserial5[o]+(hour*60*60);
                            //datetimeserial5[o]=datetimeserial5[o]+(minute*60);
                            o ++;
                        }
                        break;
        case 15:


                        
                        o = 0;

                        for (i = chartbars[displayedfile];i>=ii;i--) {
                            date15[o] = grid[rowgridoffset + 1][i];
                            time15[o] = grid[rowgridoffset + 2][i];
                            open15[o] = atof(grid[rowgridoffset + 3][i]);
                            high15[o] = atof(grid[rowgridoffset + 4][i]);
                            low15[o] = atof(grid[rowgridoffset + 5][i]);
                            close15[o] = atof(grid[rowgridoffset + 6][i]);
                            volume15[o] = atoi(grid[rowgridoffset + 7][i]);
                            std::string dateastr (date15[o]);
                            std::string timeastr (time15[o]);
                            std::string yearstr = dateastr.substr (0,4);
                            std::string monthstr = dateastr.substr (5,2);
                            std::string daystr = dateastr.substr (8,2);
                            std::string hourstr = timeastr.substr (0,2);
                            std::string minutestr = timeastr.substr (3,2);
                            year=atol(yearstr.c_str());                                                                             
                            month=atol(monthstr.c_str());                            
                            day=atol(daystr.c_str());                            
                            hour=atoi(hourstr.c_str());                            
                            minute=atoi(minutestr.c_str());
			    second=0;
			    datetimeserial15[o]=calculate_seconds_since_1_1_1970(year,month,day,hour,minute,second); //dateserial (year, month, day);
                            //datetimeserial15[o]=dateserial (year, month, day);
                            //datetimeserial15[o]=datetimeserial15[o]*24*60*60;
                            //datetimeserial15[o]=datetimeserial15[o]+(hour*60*60);
                            //datetimeserial15[o]=datetimeserial15[o]+(minute*60);
                            o ++;
                        }
                        break;
        case 30:


                        
                        o = 0;

                        for (i = chartbars[displayedfile];i>=ii;i--) {
                            date30[o] = grid[rowgridoffset + 1][i];
                            time30[o] = grid[rowgridoffset + 2][i];
                            open30[o] = atof(grid[rowgridoffset + 3][i]);
                            high30[o] = atof(grid[rowgridoffset + 4][i]);
                            low30[o] = atof(grid[rowgridoffset + 5][i]);
                            close30[o] = atof(grid[rowgridoffset + 6][i]);
                            volume30[o] = atoi(grid[rowgridoffset + 7][i]);
                            std::string dateastr (date30[o]);
                            std::string timeastr (time30[o]);
                            std::string yearstr = dateastr.substr (0,4);
                            std::string monthstr = dateastr.substr (5,2);
                            std::string daystr = dateastr.substr (8,2);
                            std::string hourstr = timeastr.substr (0,2);
                            std::string minutestr = timeastr.substr (3,2);
                            year=atol(yearstr.c_str());                                                                             
                            month=atol(monthstr.c_str());                            
                            day=atol(daystr.c_str());                            
                            hour=atoi(hourstr.c_str());                            
                            minute=atoi(minutestr.c_str());
			    second=0;
			    datetimeserial30[o]=calculate_seconds_since_1_1_1970(year,month,day,hour,minute,second); //dateserial (year, month, day);
                            //datetimeserial30[o]=dateserial (year, month, day);
                            //datetimeserial30[o]=datetimeserial30[o]*24*60*60;
                            //datetimeserial30[o]=datetimeserial30[o]+(hour*60*60);
                            //datetimeserial30[o]=datetimeserial30[o]+(minute*60);
                            o ++;
                        }
                        break;
        case 60:


                        
                        o = 0;

                        for (i = chartbars[displayedfile];i>=ii;i--) {
                            date60[o] = grid[rowgridoffset + 1][i];
                            time60[o] = grid[rowgridoffset + 2][i];
                            open60[o] = atof(grid[rowgridoffset + 3][i]);
                            high60[o] = atof(grid[rowgridoffset + 4][i]);
                            low60[o] = atof(grid[rowgridoffset + 5][i]);
                            close60[o] = atof(grid[rowgridoffset + 6][i]);
                            volume60[o] = atoi(grid[rowgridoffset + 7][i]);
                            std::string dateastr (date60[o]);
                            std::string timeastr (time60[o]);
                            std::string yearstr = dateastr.substr (0,4);
                            std::string monthstr = dateastr.substr (5,2);
                            std::string daystr = dateastr.substr (8,2);
                            std::string hourstr = timeastr.substr (0,2);
                            std::string minutestr = timeastr.substr (3,2);
                            year=atol(yearstr.c_str());                                                                             
                            month=atol(monthstr.c_str());                            
                            day=atol(daystr.c_str());                            
                            hour=atoi(hourstr.c_str());                            
                            minute=atoi(minutestr.c_str());
			    second=0;
			    datetimeserial60[o]=calculate_seconds_since_1_1_1970(year,month,day,hour,minute,second); //dateserial (year, month, day);
                            //datetimeserial60[o]=dateserial (year, month, day);
                            //datetimeserial60[o]=datetimeserial60[o]*24*60*60;
                            //datetimeserial60[o]=datetimeserial60[o]+(hour*60*60);
                            //datetimeserial60[o]=datetimeserial60[o]+(minute*60);
                            o ++;
                        }
                        break;
        case 240:


                        
                        o = 0;

                        for (i = chartbars[displayedfile];i>=ii;i--) {
                            date240[o] = grid[rowgridoffset + 1][i];
                            time240[o] = grid[rowgridoffset + 2][i];
                            open240[o] = atof(grid[rowgridoffset + 3][i]);
                            high240[o] = atof(grid[rowgridoffset + 4][i]);
                            low240[o] = atof(grid[rowgridoffset + 5][i]);
                            close240[o] = atof(grid[rowgridoffset + 6][i]);
                            volume240[o] = atoi(grid[rowgridoffset + 7][i]);
                            std::string dateastr (date240[o]);
                            std::string timeastr (time240[o]);
                            std::string yearstr = dateastr.substr (0,4);
                            std::string monthstr = dateastr.substr (5,2);
                            std::string daystr = dateastr.substr (8,2);
                            std::string hourstr = timeastr.substr (0,2);
                            std::string minutestr = timeastr.substr (3,2);
                            year=atol(yearstr.c_str());                                                                             
                            month=atol(monthstr.c_str());                            
                            day=atol(daystr.c_str());                            
                            hour=atoi(hourstr.c_str());                            
                            minute=atoi(minutestr.c_str());
			    second=0;
			    datetimeserial240[o]=calculate_seconds_since_1_1_1970(year,month,day,hour,minute,second); //dateserial (year, month, day);
                            //datetimeserial240[o]=dateserial (year, month, day);
                            //datetimeserial240[o]=datetimeserial240[o]*24*60*60;
                            //datetimeserial240[o]=datetimeserial240[o]+(hour*60*60);
                            //datetimeserial240[o]=datetimeserial240[o]+(minute*60);
                            o ++;
                        }
                        break;
        case 1440:

                        
                        o = 0;

                        for (i = chartbars[displayedfile];i>=ii;i--) {
                            date1440[o] = grid[rowgridoffset + 1][i];
                            time1440[o] = grid[rowgridoffset + 2][i];
                            open1440[o] = atof(grid[rowgridoffset + 3][i]);
                            high1440[o] = atof(grid[rowgridoffset + 4][i]);
                            low1440[o] = atof(grid[rowgridoffset + 5][i]);
                            close1440[o] = atof(grid[rowgridoffset + 6][i]);
                            volume1440[o] = atoi(grid[rowgridoffset + 7][i]);
                            std::string dateastr (date1440[o]);
                            std::string timeastr (time1440[o]);
                            std::string yearstr = dateastr.substr (0,4);
                            std::string monthstr = dateastr.substr (5,2);
                            std::string daystr = dateastr.substr (8,2);
                            std::string hourstr = timeastr.substr (0,2);
                            std::string minutestr = timeastr.substr (3,2);
                            year=atol(yearstr.c_str());                                                                             
                            month=atol(monthstr.c_str());                            
                            day=atol(daystr.c_str());                            
                            hour=atoi(hourstr.c_str());                            
                            minute=atoi(minutestr.c_str());
			    second=0;
			    datetimeserial1440[o]=calculate_seconds_since_1_1_1970(year,month,day,hour,minute,second); //dateserial (year, month, day);
                            //datetimeserial1440[o]=dateserial (year, month, day);
                            //datetimeserial1440[o]=datetimeserial1440[o]*24*60*60;
                            //datetimeserial1440[o]=datetimeserial1440[o]+(hour*60*60);
                            //datetimeserial1440[o]=datetimeserial1440[o]+(minute*60);
                            o ++;
                        }
                        break;
        case 10080:

                        
                        o = 0;
                       

                        for (i = chartbars[displayedfile];i>=ii;i--) {                            
                            date10080[o] = grid[rowgridoffset + 1][i];
                            time10080[o] = grid[rowgridoffset + 2][i];
                            open10080[o] = atof(grid[rowgridoffset + 3][i]);
                            high10080[o] = atof(grid[rowgridoffset + 4][i]);
                            low10080[o] = atof(grid[rowgridoffset + 5][i]);
                            close10080[o] = atof(grid[rowgridoffset + 6][i]);
                            volume10080[o] = atoi(grid[rowgridoffset + 7][i]);                       
                            std::string dateastr (date10080[o]);
                            std::string timeastr (time10080[o]);
                            std::string yearstr = dateastr.substr (0,4);
                            std::string monthstr = dateastr.substr (5,2);
                            std::string daystr = dateastr.substr (8,2);
                            std::string hourstr = timeastr.substr (0,2);
                            std::string minutestr = timeastr.substr (3,2);                                                                                                                                                                    
                            year=atol(yearstr.c_str());                                                                             
                            month=atol(monthstr.c_str());                            
                            day=atol(daystr.c_str());                            
                            hour=atoi(hourstr.c_str());                            
                            minute=atoi(minutestr.c_str());
			    second=0;
			    datetimeserial10080[o]=calculate_seconds_since_1_1_1970(year,month,day,hour,minute,second); //dateserial (year, month, day);
                            //datetimeserial10080[o]=dateserial (year, month, day);
                            //datetimeserial10080[o]=datetimeserial10080[o]*24*60*60;
                            //datetimeserial10080[o]=datetimeserial10080[o]+(hour*60*60);
                            //datetimeserial10080[o]=datetimeserial10080[o]+(minute*60);
                            o ++;
                        }
                        break;
        case 43200:


                        
                        o = 0;

                        for (i = chartbars[displayedfile];i>=ii;i--) {
                            date43200[o] = grid[rowgridoffset + 1][i];
                            time43200[o] = grid[rowgridoffset + 2][i];
                            open43200[o] = atof(grid[rowgridoffset + 3][i]);
                            high43200[o] = atof(grid[rowgridoffset + 4][i]);
                            low43200[o] = atof(grid[rowgridoffset + 5][i]);
                            close43200[o] = atof(grid[rowgridoffset + 6][i]);
                            volume43200[o] = atoi(grid[rowgridoffset + 7][i]);
                            std::string dateastr (date43200[o]);
                            std::string timeastr (time43200[o]);
                            std::string yearstr = dateastr.substr (0,4);
                            std::string monthstr = dateastr.substr (5,2);
                            std::string daystr = dateastr.substr (8,2);
                            std::string hourstr = timeastr.substr (0,2);
                            std::string minutestr = timeastr.substr (3,2);
                            year=atol(yearstr.c_str());                                                                             
                            month=atol(monthstr.c_str());                            
                            day=atol(daystr.c_str());                            
                            hour=atoi(hourstr.c_str());                            
                            minute=atoi(minutestr.c_str());
			    second=0;
			    datetimeserial43200[o]=calculate_seconds_since_1_1_1970(year,month,day,hour,minute,second); //dateserial (year, month, day);
                            //datetimeserial43200[o]=dateserial (year, month, day);
                            //datetimeserial43200[o]=datetimeserial43200[o]*24*60*60;
                            //datetimeserial43200[o]=datetimeserial43200[o]+(hour*60*60);
                            //datetimeserial43200[o]=datetimeserial43200[o]+(minute*60);
                            o ++;
                        }
                        break;
 }

 return 0;
}

char* idate(int timeframe,int shift)
{
switch (timeframe) {
    case 1:
    return  date1[shift];
    break;
    case 5:
    return  date5[shift];
    break;
    case 15:
    return  date15[shift];
    break;
    case 30:
    return  date30[shift];
    break;
    case 60:
    return  date60[shift];
    break;
    case 240:
    return  date240[shift];
    break;
    case 1440:
    return  date1440[shift];
    break;
    case 10080:
    return  date10080[shift];
    break;
    case 43200:
    return  date43200[shift];
    break;
                   }
return 0;                   
}

char* itime(int timeframe,int shift)
{
switch (timeframe) {
    case 1:
    return  time1[shift];
    break;
    case 5:
    return  time5[shift];
    break;
    case 15:
    return  time15[shift];
    break;
    case 30:
    return  time30[shift];
    break;
    case 60:
    return  time60[shift];
    break;
    case 240:
    return  time240[shift];
    break;
    case 1440:
    return  time1440[shift];
    break;
    case 10080:
    return  time10080[shift];
    break;
    case 43200:
    return  time43200[shift];
    break;
                   }
return 0;                   
}    

double iopen(int timeframe,int shift)
{
switch (timeframe) {
    case 1:
    return  open1[shift];
    break;
    case 5:
    return  open5[shift];
    break;
    case 15:
    return  open15[shift];
    break;
    case 30:
    return  open30[shift];
    break;
    case 60:
    return  open60[shift];
    break;
    case 240:
    return  open240[shift];
    break;
    case 1440:
    return  open1440[shift];
    break;
    case 10080:
    return  open10080[shift];
    break;
    case 43200:
    return  open43200[shift];
    break;
                   }
return 0;                   
}

double ihigh(int timeframe,int shift)
{
switch (timeframe) {
    case 1:
    return  high1[shift];
    break;
    case 5:
    return  high5[shift];
    break;
    case 15:
    return  high15[shift];
    break;
    case 30:
    return  high30[shift];
    break;
    case 60:
    return  high60[shift];
    break;
    case 240:
    return  high240[shift];
    break;
    case 1440:
    return  high1440[shift];
    break;
    case 10080:
    return  high10080[shift];
    break;
    case 43200:
    return  high43200[shift];
    break;
                   }
return 0;                   
}

double ilow(int timeframe,int shift)
{
switch (timeframe) {
    case 1:
    return  low1[shift];
    break;
    case 5:
    return  low5[shift];
    break;
    case 15:
    return  low15[shift];
    break;
    case 30:
    return  low30[shift];
    break;
    case 60:
    return  low60[shift];
    break;
    case 240:
    return  low240[shift];
    break;
    case 1440:
    return  low1440[shift];
    break;
    case 10080:
    return  low10080[shift];
    break;
    case 43200:
    return  low43200[shift];
    break;
                   }
return 0;                   
}

double iclose(int timeframe,int shift)
{
switch (timeframe) {
    case 1:
    return  close1[shift];
    break;
    case 5:
    return  close5[shift];
    break;
    case 15:
    return  close15[shift];
    break;
    case 30:
    return  close30[shift];
    break;
    case 60:
    return  close60[shift];
    break;
    case 240:
    return  close240[shift];
    break;
    case 1440:
    return  close1440[shift];
    break;
    case 10080:
    return  close10080[shift];
    break;
    case 43200:
    return  close43200[shift];
    break;
                   }
return 0;                   
}

int ivolume(int timeframe,int shift)
{
switch (timeframe) {
    case 1:
    return  volume1[shift];
    break;
    case 5:
    return  volume5[shift];
    break;
    case 15:
    return  volume15[shift];
    break;
    case 30:
    return  volume30[shift];
    break;
    case 60:
    return  volume60[shift];
    break;
    case 240:
    return  volume240[shift];
    break;
    case 1440:
    return  volume1440[shift];
    break;
    case 10080:
    return  volume10080[shift];
    break;
    case 43200:
    return  volume43200[shift];
    break;
                   }
return 0;                   
}

long idatetimeserial(int timeframe,int shift)
{
switch (timeframe) {
    case 1:
    return  datetimeserial1[shift];
    break;
    case 5:
    return  datetimeserial5[shift];
    break;
    case 15:
    return  datetimeserial15[shift];
    break;
    case 30:
    return  datetimeserial30[shift];
    break;
    case 60:
    return  datetimeserial60[shift];
    break;
    case 240:
    return  datetimeserial240[shift];
    break;
    case 1440:
    return  datetimeserial1440[shift];
    break;
    case 10080:
    return  datetimeserial10080[shift];
    break;
    case 43200:
    return  datetimeserial43200[shift];
    break;
                   }
return 0;                   
}

double iapplied_price(int applied_price,int timeframe,int shift)
{
switch (applied_price) {
    case 0: //PRICE_CLOSE
    return  iclose(timeframe,shift);
    break;
    case 1: //PRICE_OPEN
    return  iopen(timeframe,shift);
    break;
    case 2: //PRICE_HIGH
    return  ihigh(timeframe,shift);
    break;
    case 3: //PRICE_LOW
    return  ilow(timeframe,shift);
    break;
    case 4: //PRICE_MEDIAN
    return  (ihigh(timeframe,shift)+ilow(timeframe,shift))/2;
    break;
    case 5: //PRICE_TYPICAL
    return  (ihigh(timeframe,shift)+ilow(timeframe,shift)+iclose(timeframe,shift))/3;
    break;
    case 6: //PRICE_WEIGHTED
    return  (ihigh(timeframe,shift)+ilow(timeframe,shift)+iclose(timeframe,shift)+iclose(timeframe,shift))/4;
    break;
                   }
return 0;                   
}

double itype(int mode,int timeframe,int shift)
{
switch (mode) {
    case 0: //MODE_OPEN
    return  iopen(timeframe,shift);
    break;
    case 1: //MODE_LOW
    return  ilow(timeframe,shift);
    break;
    case 2: //MODE_HIGH
    return  ihigh(timeframe,shift);
    break;
    case 3: //MODE_CLOSE
    return  iclose(timeframe,shift);
    break;
    //case 4: //MODE_VOLUME
    //return  ivolume(timeframe,shift);
    //break;
    //case 5: //MODE_TIME
    //return  itime(timeframe,shift);
    //break;
                   }
return 0;                   
}

double ima(int timeframe,int period,int ma_shift,int ma_method,int applied_price,int shift)
{
int p=1000;
arrayofdoubles ExtMapBuffer;
double sum;
int i,k;

switch(ma_method)
     {
      case 0 : 
      // SMA      
    int per;
    sum=0;    
    if (p<period) p=period;
    per=period;

    for (i=1;i<=per-1;i++) {
        sum=sum+iapplied_price(applied_price,timeframe,p);
        p--;
                           }
    while (p>=0) {
        sum=sum+iapplied_price(applied_price,timeframe,p);
        if (p==shift+ma_shift) { return sum/per; break; }
        sum=sum-iapplied_price(applied_price,timeframe,p+per-1);
        p--;
                 }
      break;

      case 1 : // Exponential Moving Average  
	double pr;
	pr=2.0/(period+1);
	//---- main calculation loop
   	while(p>=0)
     	{
      	if(p==1000) ExtMapBuffer[p+1]=iapplied_price(applied_price,timeframe,p+1);
      	ExtMapBuffer[p]=iapplied_price(applied_price,timeframe,p)*pr+ExtMapBuffer[p+1]*(1-pr);
	if (p==shift+ma_shift) { return ExtMapBuffer[p]; break; }
 	   p--;
     	}	
	break;

      case 2 : // Smoothed Moving Average 
	sum=0;	   
	//---- main calculation loop
	   while(p>=0)
	     {
	      if(p==1000)
	        {
	         //---- initial accumulation
	         for(i=0,k=p;i<period;i++,k++)
	           {
	            sum+=iapplied_price(applied_price,timeframe,k);
	            //---- zero initial bars
	            ExtMapBuffer[k]=0;
	           }
	        }
	      else sum=ExtMapBuffer[p+1]*(period-1)+iapplied_price(applied_price,timeframe,p);
	      ExtMapBuffer[p]=sum/period;
		if (p==shift+ma_shift) { return ExtMapBuffer[p]; break; }
	 	p--;
	     }
	break;

      case 3 : // Linear Weighted Moving Average
	sum=0.0; double lsum=0.0;
	   double price;
	   int    weight=0;
	//---- initial accumulation
	   if(p<period) p=period;
	   for(i=1;i<=period;i++,p--)
	     {
	      price=iapplied_price(applied_price,timeframe,p);
	      sum+=price*i;
	      lsum+=price;
	      weight+=i;
	     }
	//---- main calculation loop
	   p++;
	   i=p+period;
	   while(p>=0)
	     {
	      ExtMapBuffer[p]=sum/weight;
		if (p==shift+ma_shift) { return ExtMapBuffer[p]; break; }
	      if(p==0) break;
	      p--;
	      i--;
	      price=iapplied_price(applied_price,timeframe,p);
	      sum=sum-lsum+price*period;
	      lsum-=iapplied_price(applied_price,timeframe,i);
	      lsum+=price;
	     }
	break;
     }

    
return 0;
}

double irsi(int timeframe,int period,int applied_price,int shift)
{
int RSIPeriod=period;
//---- buffers
static arrayofdoubles RSIBuffer;
static arrayofdoubles PosBuffer;
static arrayofdoubles NegBuffer;
int Bars=200;

int    i;
   double rel,negative,positive;

//----
   i=Bars-RSIPeriod-1;

   while(i>=0)
     {
      double sumn=0.0,sump=0.0;
      if(i==Bars-RSIPeriod-1)
        {
         int k=Bars-2;
         //---- initial accumulation
         while(k>=i)
           {
            rel=closea[k]-closea[k+1];
            if(rel>0) sump+=rel;
            else      sumn-=rel;
            k--;
           }
         positive=sump/RSIPeriod;
         negative=sumn/RSIPeriod;
        }
      else
        {
         //---- smoothed moving average
         rel=closea[i]-closea[i+1];
         if(rel>0) sump=rel;
         else      sumn=-rel;
         positive=(PosBuffer[i+1]*(RSIPeriod-1)+sump)/RSIPeriod;
         negative=(NegBuffer[i+1]*(RSIPeriod-1)+sumn)/RSIPeriod;
        }
      PosBuffer[i]=positive;
      NegBuffer[i]=negative;
      if(negative==0.0) RSIBuffer[i]=0.0;
      else RSIBuffer[i]=100.0-100.0/(1+positive/negative);
      if (i==shift) { return RSIBuffer[i]; break; }
      i--;
     }
//----
   return(0);
}

double icci(int timeframe,int period,int applied_price,int shift)
{
int CCIPeriod = period;
int Bars=200;
//---- buffers
static arrayofdoubles CCIBuffer;
static arrayofdoubles RelBuffer;
static arrayofdoubles DevBuffer;
static arrayofdoubles MovBuffer;

int    i, k;
   double price, sum, mul; 
   if(CCIPeriod <= 1)
       return(0);
   if(Bars <= CCIPeriod) 
       return(0);
//---- last counted bar will be recounted
   int limit = Bars;

//---- moving average
   for(i = 0; i < limit; i++)
       MovBuffer[i] = ima(timeframe, CCIPeriod, 0, MODE_SMA, PRICE_TYPICAL, i);
//---- standard deviations
   i = Bars - CCIPeriod + 1;
 
   mul = 0.015 / CCIPeriod;
   while(i >= 0)
     {
       sum = 0.0;
       k = i + CCIPeriod - 1;
       while(k >= i)
        {
          price =(higha[k] + lowa[k] + closea[k]) / 3;
          sum += fabs(price - MovBuffer[i]);
          k--;
        }
       DevBuffer[i] = sum*mul;
       i--;
     }
   i = Bars - CCIPeriod + 1;

   while(i >= 0)
     {
       price = (higha[i] + lowa[i] + closea[i]) / 3;
       RelBuffer[i] = price - MovBuffer[i];
       i--;
     }
//---- cci counting
   i = Bars - CCIPeriod + 1;

   while(i >= 0)
     {
       if(DevBuffer[i] == 0.0) 
           CCIBuffer[i] = 0.0;
       else 
           CCIBuffer[i] = RelBuffer[i] / DevBuffer[i];
	if (i==shift) { return (CCIBuffer[i]); break; }
       i--;
     }
//----
   return(0);
}

int ihighest(int timeframe,int type,int count,int start=0)
{
    
int i;
arrayofdoubles array;
double highest;

    highest = 0;
    for (i = start;i<=start+count-1;i++) {
        array[i]=itype(type,timeframe,i);        
        if (array[i] > highest) highest = array[i];           
    }

    for (i = start;i<=start+count-1;i++) {
            if (array[i]==highest) {
                return i;
                break;
                                  }
        }           
return 0;    
}

int ilowest(int timeframe,int type,int count,int start=0)
{
    
int i;
arrayofdoubles array;
double lowest;

    lowest = itype(type,timeframe,start);;
    for (i = start;i<=start+count-1;i++) {
        array[i]=itype(type,timeframe,i);        
        if (array[i] < lowest) lowest = array[i];           
    }
    for (i = start;i<=start+count-1;i++) {
            if (array[i]==lowest) {
                return i;
                break;
                                  }
        }           
return 0;           
    
}

char* playsoundcpp ( char* sndfreq,char* snddur )
{  
static char sndfreqq[1000];
strncpy(sndfreqq, sndfreq, 1000);
int sndfreqint=atoi(sndfreqq);
static char snddurr[1000];
strncpy(snddurr, snddur, 1000);
int snddurint=atoi(snddurr);
Beep(sndfreqint,snddurint); // hertz, milliseconds     
//cin.get(); // wait 
return 0; 
}

long calculate_seconds_since_1_1_1970(long Y1,long M1,long D1,int H1,int m1,int S1)
{

long dayssince111970;
dayssince111970=dateserial(1970,1,1);

long dayssincespecified;
dayssincespecified=dateserial(Y1,M1,D1);

long daysdif=dayssincespecified-dayssince111970;

long inseconds=daysdif*24*60*60;
inseconds+=H1*60*60+m1*60+S1;

return inseconds;
}

char* timecpp(char* bar)
{
static char barr[1000];
strncpy(barr, bar, 1000);
int barint=atoi(barr);

int year;int month;int day;int hour;int minute;
std::string dateastr (datea[barint]);
std::string timeastr (timea[barint]);
std::string yearstr = dateastr.substr (0,4);
std::string monthstr = dateastr.substr (5,2);
std::string daystr = dateastr.substr (8,2);
std::string hourstr = timeastr.substr (0,2);
std::string minutestr = timeastr.substr (3,2);
year=atoi(yearstr.c_str());                                                                             
month=atoi(monthstr.c_str());                            
day=atoi(daystr.c_str());                            
hour=atoi(hourstr.c_str());                            
minute=atoi(minutestr.c_str());

char catline[1000];
sprintf(catline,"%f",calculate_seconds_since_1_1_1970(year,month,day,hour,minute,0));
return catline;
}

long timeb(int bar)
{

int year;int month;int day;int hour;int minute;
std::string dateastr (datea[bar]);
std::string timeastr (timea[bar]);
std::string yearstr = dateastr.substr (0,4);
std::string monthstr = dateastr.substr (5,2);
std::string daystr = dateastr.substr (8,2);
std::string hourstr = timeastr.substr (0,2);
std::string minutestr = timeastr.substr (3,2);
year=atoi(yearstr.c_str());                                                                             
month=atoi(monthstr.c_str());                            
day=atoi(daystr.c_str());                            
hour=atoi(hourstr.c_str());                            
minute=atoi(minutestr.c_str());

return calculate_seconds_since_1_1_1970(year,month,day,hour,minute,0);
}

double timeminute(double seconds)
{
double inhours=seconds/60/60;
double minutes=(inhours-trunc(inhours))*60;
return minutes;
}

double timehour(double seconds)
{
double indays=seconds/60/60/24;
double hours=(indays-trunc(indays))*24;
return hours;
}

int timedayofweek(long timeb)
{
//double result;
//result= fmod (static_cast<double>(timeb),7);

/*
if (result==0) return 4;
if (result==1) return 3;
if (result==2) return 2;
if (result==3) return 1;
if (result==4) return 0;
if (result==5) return 6;
if (result==6) return 5;
*/

char* mydate;
mydate=ut_to_date(timeb);
char * writable;

std::string mydatestr (mydate);                 
std::string daystr = mydatestr.substr (0,3);
writable = new char[daystr.size() + 1];
std::copy(daystr.begin(), daystr.end(), writable);
writable[daystr.size()] = '\0'; // don't forget the terminating 0           

if (strcmp(writable,"Mon")==0) { return 1; }
if (strcmp(writable,"Tue")==0) { return 2; }
if (strcmp(writable,"Wed")==0) { return 3; }
if (strcmp(writable,"Thu")==0) { return 4; }
if (strcmp(writable,"Fri")==0) { return 5; }
if (strcmp(writable,"Sat")==0) { return 6; }
if (strcmp(writable,"Sun")==0) { return 0; }

}

double mathmax(double value1,double value2)
{

if (value1>value2) return value1;
if (value2>value1) return value2;
if (value1==value2) return value1;

}

double mathmin(double value1,double value2)
{

if (value1<value2) return value1;
if (value2<value1) return value2;
if (value1==value2) return value1;

}

long itimeb(int period,int bar)
{

int year;int month;int day;int hour;int minute;
std::string dateastr;
std::string timeastr;
switch (period)
{

case 1:
dateastr= (date1[bar]);
timeastr= (time1[bar]);
break;    
    
case 5:
dateastr= (date5[bar]);
timeastr= (time5[bar]);
break;

case 15:
dateastr= (date15[bar]);
timeastr= (time15[bar]);
break;

case 30:
dateastr= (date30[bar]);
timeastr= (time30[bar]);
break;

case 60:
dateastr= (date60[bar]);
timeastr= (time60[bar]);
break;

case 240:
dateastr= (date240[bar]);
timeastr= (time240[bar]);
break;

case 1440:
dateastr= (date1440[bar]);
timeastr= (time1440[bar]);
break;

case 10080:
dateastr= (date10080[bar]);
timeastr= (time10080[bar]);
break;

case 43200:
dateastr= (date43200[bar]);
timeastr= (time43200[bar]);
break;
}
std::string yearstr = dateastr.substr (0,4);
std::string monthstr = dateastr.substr (5,2);
std::string daystr = dateastr.substr (8,2);
std::string hourstr = timeastr.substr (0,2);
std::string minutestr = timeastr.substr (3,2);
year=atoi(yearstr.c_str());                                                                             
month=atoi(monthstr.c_str());                            
day=atoi(daystr.c_str());                            
hour=atoi(hourstr.c_str());                            
minute=atoi(minutestr.c_str());

return calculate_seconds_since_1_1_1970(year,month,day,hour,minute,0);
}

char* unix_time_to_date(char* unix_time)
{
static char unix_timee[1000];
strncpy(unix_timee, unix_time, 1000);

	//const char time_as_str[] = "1296575549:573352";
	time_t t = atoi(unix_timee); // convert to time_t, ignores msec
	char asctimechar[1000];
	sprintf(asctimechar,"%s",asctime(gmtime(&t)));
	return asctimechar;
}

char* date_to_unix_time(char* parameters)
{

static char parameterss[1000];
strncpy(parameterss, parameters, 1000);

// Parameters decomposition
long Y1;
long M1;
long D1;
int H1;
int m1;
int S1;

char * writable;

std::string linestr (parameterss);  
          
std::size_t found = linestr.find(";");        
std::string Y1str = linestr.substr (0,found);
writable = new char[Y1str.size() + 1];
std::copy(Y1str.begin(), Y1str.end(), writable);
writable[Y1str.size()] = '\0'; // don't forget the terminating 0           
Y1=atol(writable);

linestr.assign(linestr.begin()+found+1,linestr.end());
found = linestr.find(";");
std::string M1str = linestr.substr (0,found);
writable = new char[M1str.size() + 1];
std::copy(M1str.begin(), M1str.end(), writable);
writable[M1str.size()] = '\0'; // don't forget the terminating 0
M1=atol(writable);

linestr.assign(linestr.begin()+found+1,linestr.end());
found = linestr.find(";");
std::string D1str = linestr.substr (0,found);
writable = new char[D1str.size() + 1];
std::copy(D1str.begin(), D1str.end(), writable);
writable[D1str.size()] = '\0'; // don't forget the terminating 0
D1=atol(writable);

linestr.assign(linestr.begin()+found+1,linestr.end());
found = linestr.find(";");
std::string H1str = linestr.substr (0,found);
writable = new char[H1str.size() + 1];
std::copy(H1str.begin(), H1str.end(), writable);
writable[H1str.size()] = '\0'; // don't forget the terminating 0
H1=atoi(writable);

linestr.assign(linestr.begin()+found+1,linestr.end());
found = linestr.find(";");
std::string m1str = linestr.substr (0,found);
writable = new char[m1str.size() + 1];
std::copy(m1str.begin(), m1str.end(), writable);
writable[m1str.size()] = '\0'; // don't forget the terminating 0
m1=atoi(writable);

linestr.assign(linestr.begin()+found+1,linestr.end());
found = linestr.find(";");
std::string S1str = linestr.substr (0,found);
writable = new char[S1str.size() + 1];
std::copy(S1str.begin(), S1str.end(), writable);
writable[S1str.size()] = '\0'; // don't forget the terminating 0
S1=atoi(writable);

double dayssince111970;
dayssince111970=dateserial(1970,1,1);

double dayssincespecified;
dayssincespecified=dateserial(Y1,M1,D1);

double daysdif=dayssincespecified-dayssince111970;

double inseconds=daysdif*24*60*60;
inseconds+=H1*60*60+m1*60+S1;
//inseconds-=3600;

char catline[1000];
sprintf(catline,"%f",inseconds);

return catline;
}

char* timebcpp(int* bar)
{

//static char barr[1000];
//strncpy(barr, bar, 1000);
//int barint=atoi(barr);

long timebar=timeb(*bar);

char catline[1000];
sprintf(catline,"%i",timebar);

return catline;

}

char* calculate_seconds_since_1_1_1970_cpp(char* parameters)
{

static char parameterss[1000];
strncpy(parameterss, parameters, 1000);

// Parameters decomposition
long Y1;
long M1;
long D1;
int H1;
int m1;
int S1;
//double x;
//char* serr;

char * writable;

std::string linestr (parameterss);  
          
std::size_t found = linestr.find(";");        
std::string Y1str = linestr.substr (0,found);
writable = new char[Y1str.size() + 1];
std::copy(Y1str.begin(), Y1str.end(), writable);
writable[Y1str.size()] = '\0'; // don't forget the terminating 0           
Y1=atol(writable);

linestr.assign(linestr.begin()+found+1,linestr.end());
found = linestr.find(";");
std::string M1str = linestr.substr (0,found);
writable = new char[M1str.size() + 1];
std::copy(M1str.begin(), M1str.end(), writable);
writable[M1str.size()] = '\0'; // don't forget the terminating 0
M1=atol(writable);

linestr.assign(linestr.begin()+found+1,linestr.end());
found = linestr.find(";");
std::string D1str = linestr.substr (0,found);
writable = new char[D1str.size() + 1];
std::copy(D1str.begin(), D1str.end(), writable);
writable[D1str.size()] = '\0'; // don't forget the terminating 0
D1=atol(writable);

linestr.assign(linestr.begin()+found+1,linestr.end());
found = linestr.find(";");
std::string H1str = linestr.substr (0,found);
writable = new char[H1str.size() + 1];
std::copy(H1str.begin(), H1str.end(), writable);
writable[H1str.size()] = '\0'; // don't forget the terminating 0
H1=atoi(writable);

linestr.assign(linestr.begin()+found+1,linestr.end());
found = linestr.find(";");
std::string m1str = linestr.substr (0,found);
writable = new char[m1str.size() + 1];
std::copy(m1str.begin(), m1str.end(), writable);
writable[m1str.size()] = '\0'; // don't forget the terminating 0
m1=atoi(writable);

linestr.assign(linestr.begin()+found+1,linestr.end());
found = linestr.find(";");
std::string S1str = linestr.substr (0,found);
writable = new char[S1str.size() + 1];
std::copy(S1str.begin(), S1str.end(), writable);
writable[S1str.size()] = '\0'; // don't forget the terminating 0
S1=atoi(writable);

long dayssince111970;
dayssince111970=dateserial(1970,1,1);

long dayssincespecified;
dayssincespecified=dateserial(Y1,M1,D1);

long daysdif=dayssincespecified-dayssince111970;

double inseconds=daysdif*24*60*60;
inseconds+=H1*60*60+m1*60+S1;

char catline[1000];
sprintf(catline,"%f",inseconds);

return catline;
}

char* ut_to_date(long unix_time)
{

	time_t t = unix_time; // convert to time_t, ignores msec
	char asctimechar[1000];
	sprintf(asctimechar,"%s",asctime(gmtime(&t)));
	return asctimechar;
}

char* current_time()
{

    long int t = static_cast<long int>(time(NULL));
    char timechar[1000];
    sprintf(timechar,"%i",t);
    return timechar;
}

void DoEvents()
{
    MSG msg;
    BOOL result;

    while ( ::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE ) )
    {
        result = ::GetMessage(&msg, NULL, 0, 0);
        if (result == 0) // WM_QUIT
        {                
            ::PostQuitMessage(msg.wParam);
            break;
        }
        else if (result == -1)
        {
             // Handle errors/exit application, etc.
        }
        else 
        {
            ::TranslateMessage(&msg);
            :: DispatchMessage(&msg);
        }
    }
}

double imaonarray(arrayofdoubles& array,int total,int period,int ma_shift,int ma_method,int shift)
{

switch(ma_method)
     {
      case 0 : 
      // SMA
      double sum;
    int per;
    sum=0;
    int i;int p;
    p=total;
    if (p<period) p=period;
    per=period;

    for (i=1;i<=per-1;i++) {
        sum=sum+array[p];
        p--;
                           }
    while (p>=0) {
        sum=sum+array[p];
        if (p==shift+ma_shift) { return sum/per; break; }
        sum=sum-array[p+per-1];
        p--;
                 }
      break;
      case 1 : /*ema not implemented yet*/ break;
      case 2 : /*smma not implemented yet*/ break;
      case 3 : /*lwma not implemented yet*/ break;
     }

    
return 0;
}