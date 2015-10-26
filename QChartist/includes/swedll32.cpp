// LOADING DLLS THE HARD(ER) WAY (Dynamic Loading)
#include <iostream>
// Need Windows.h for HINSTANCE and DLL Loading and Releasing functions.
#include <windows.h>
#include <string.h>
using namespace std;

// Function pointers that will be used for the DLL functions.
typedef double (*swe_juldayFunc)(int,int,int,double,int);
typedef int (*swe_date_conversionFunc)(int,int,int,double,char,double&);
typedef double (*swe_deltatFunc)(double);
typedef int (*swe_calcFunc)(double,int,int,double&,char*);
typedef int (*swe_get_planet_nameFunc)(int,char*);
typedef double (*swe_sidtimeFunc)(double);
typedef double (*swe_house_posFunc)(double,double,double,int,double&,char*);
typedef int (*swe_housesFunc)(double,double,double,int,double&,double&);
typedef int (*swe_houses_exFunc)(double,int,double,double,int,double&,double&);

char* swe_julday(char* parameters)
{
static char parameterss[1000];
strncpy(parameterss, parameters, 1000);

// Parameters decomposition
int year;
int month;
int day;
double hour;
int gregflg;

char * writable;

std::string linestr (parameterss);  
          
std::size_t found = linestr.find(";");        
std::string yearstr = linestr.substr (0,found);
writable = new char[yearstr.size() + 1];
std::copy(yearstr.begin(), yearstr.end(), writable);
writable[yearstr.size()] = '\0'; // don't forget the terminating 0           
year=atoi(writable);

linestr.assign(linestr.begin()+found+1,linestr.end());
found = linestr.find(";");
std::string monthstr = linestr.substr (0,found);
writable = new char[monthstr.size() + 1];
std::copy(monthstr.begin(), monthstr.end(), writable);
writable[monthstr.size()] = '\0'; // don't forget the terminating 0
month=atoi(writable);

linestr.assign(linestr.begin()+found+1,linestr.end());
found = linestr.find(";");
std::string daystr = linestr.substr (0,found);
writable = new char[daystr.size() + 1];
std::copy(daystr.begin(), daystr.end(), writable);
writable[daystr.size()] = '\0'; // don't forget the terminating 0
day=atoi(writable);

linestr.assign(linestr.begin()+found+1,linestr.end());
found = linestr.find(";");
std::string hourstr = linestr.substr (0,found);
writable = new char[hourstr.size() + 1];
std::copy(hourstr.begin(), hourstr.end(), writable);
writable[hourstr.size()] = '\0'; // don't forget the terminating 0
hour=atof(writable);

linestr.assign(linestr.begin()+found+1,linestr.end());
found = linestr.find(";");
std::string gregflgstr = linestr.substr (0,found);
writable = new char[gregflgstr.size() + 1];
std::copy(gregflgstr.begin(), gregflgstr.end(), writable);
writable[gregflgstr.size()] = '\0'; // don't forget the terminating 0
gregflg=atoi(writable);

// Typedef functions to hold what is in the DLL
swe_juldayFunc _swe_juldayFunc;

// The Instance of the DLL.
// LoadLibrary used to load a DLL
HINSTANCE hInstLibrary = LoadLibrary("C:\\qchartist\\includes\\swedll32.dll");

if (hInstLibrary)
	{

	// Our DLL is loaded and ready to go.

	// Set up our function pointers.
	_swe_juldayFunc = (swe_juldayFunc)GetProcAddress(hInstLibrary, "_swe_julday@24");

		// Check if _AddFunc is currently holding a function, if not don't run it.
		if (_swe_juldayFunc)
		{	
			//sprintf(debugmsg,"%f",_swe_juldayFunc(year,month,day,hour,gregflg));MessageBox( NULL, debugmsg,"Debug",MB_OK); //use this where you need to debug the program
			sprintf(debugmsg,"%f",_swe_juldayFunc(year,month,day,hour,gregflg));
			return debugmsg;
		}
		
	// We're done with the DLL so we need to release it from memory.
	FreeLibrary(hInstLibrary);
	}
	else
	{
		// Our DLL failed to load!
		sprintf(debugmsg,"%s","DLL Failed To Load!");MessageBox( NULL, debugmsg,"Debug",MB_OK); //use this where you need to debug the program
	}

	return 0;
}

char* swe_date_conversion(char* parameters)
{ 
static char parameterss[1000];
strncpy(parameterss, parameters, 1000);

// Parameters decomposition
int year;
int month;
int day;
double utime;
char cal;
double tjd;

char * writable;

std::string linestr (parameterss);  
          
std::size_t found = linestr.find(";");        
std::string yearstr = linestr.substr (0,found);
writable = new char[yearstr.size() + 1];
std::copy(yearstr.begin(), yearstr.end(), writable);
writable[yearstr.size()] = '\0'; // don't forget the terminating 0           
year=atoi(writable);

linestr.assign(linestr.begin()+found+1,linestr.end());
found = linestr.find(";");
std::string monthstr = linestr.substr (0,found);
writable = new char[monthstr.size() + 1];
std::copy(monthstr.begin(), monthstr.end(), writable);
writable[monthstr.size()] = '\0'; // don't forget the terminating 0
month=atoi(writable);

linestr.assign(linestr.begin()+found+1,linestr.end());
found = linestr.find(";");
std::string daystr = linestr.substr (0,found);
writable = new char[daystr.size() + 1];
std::copy(daystr.begin(), daystr.end(), writable);
writable[daystr.size()] = '\0'; // don't forget the terminating 0
day=atoi(writable);

linestr.assign(linestr.begin()+found+1,linestr.end());
found = linestr.find(";");
std::string utimestr = linestr.substr (0,found);
writable = new char[utimestr.size() + 1];
std::copy(utimestr.begin(), utimestr.end(), writable);
writable[utimestr.size()] = '\0'; // don't forget the terminating 0
utime=atof(writable);

linestr.assign(linestr.begin()+found+1,linestr.end());
found = linestr.find(";");
std::string calstr = linestr.substr (0,found);
writable = new char[calstr.size() + 1];
std::copy(calstr.begin(), calstr.end(), writable);
writable[calstr.size()] = '\0'; // don't forget the terminating 0
cal=writable[0];


linestr.assign(linestr.begin()+found+1,linestr.end());
found = linestr.find(";");
std::string tjdstr = linestr.substr (0,found);
writable = new char[tjdstr.size() + 1];
std::copy(tjdstr.begin(), tjdstr.end(), writable);
writable[tjdstr.size()] = '\0'; // don't forget the terminating 0
tjd=atof(writable);

// Typedef functions to hold what is in the DLL
swe_date_conversionFunc _swe_date_conversionFunc;

// The Instance of the DLL.
// LoadLibrary used to load a DLL
HINSTANCE hInstLibrary = LoadLibrary("C:\\qchartist\\includes\\swedll32.dll");

if (hInstLibrary)
	{

	// Our DLL is loaded and ready to go.

	// Set up our function pointers.
	_swe_date_conversionFunc = (swe_date_conversionFunc)GetProcAddress(hInstLibrary, "_swe_date_conversion@28");

		// Check if _AddFunc is currently holding a function, if not don't run it.
		if (_swe_date_conversionFunc)
		{	
			//sprintf(debugmsg,"%i",_swe_date_conversionFunc(year,month,day,utime,cal,tjd));MessageBox( NULL, debugmsg,"Debug",MB_OK); //use this where you need to debug the program			
			sprintf(debugmsg,"%i",_swe_date_conversionFunc(year,month,day,utime,cal,tjd));
			return debugmsg;
		}
		
	// We're done with the DLL so we need to release it from memory.
	FreeLibrary(hInstLibrary);
	}
	else
	{
		// Our DLL failed to load!
		sprintf(debugmsg,"%s","DLL Failed To Load!");MessageBox( NULL, debugmsg,"Debug",MB_OK); //use this where you need to debug the program
	}

	return 0;
}

char* swe_deltat(char* parameters)
{ 
static char parameterss[1000];
strncpy(parameterss, parameters, 1000);

// Parameters decomposition
double jd=atof(parameterss);

// Typedef functions to hold what is in the DLL
swe_deltatFunc _swe_deltatFunc;

// The Instance of the DLL.
// LoadLibrary used to load a DLL
HINSTANCE hInstLibrary = LoadLibrary("C:\\qchartist\\includes\\swedll32.dll");

if (hInstLibrary)
	{

	// Our DLL is loaded and ready to go.

	// Set up our function pointers.
	_swe_deltatFunc = (swe_deltatFunc)GetProcAddress(hInstLibrary, "_swe_deltat@8");

		// Check if _AddFunc is currently holding a function, if not don't run it.
		if (_swe_deltatFunc)
		{	
			//sprintf(debugmsg,"%f",_swe_juldayFunc(year,month,day,hour,gregflg));MessageBox( NULL, debugmsg,"Debug",MB_OK); //use this where you need to debug the program			
			sprintf(debugmsg,"%E",_swe_deltatFunc(jd));
			return debugmsg;
		}
		
	// We're done with the DLL so we need to release it from memory.
	FreeLibrary(hInstLibrary);
	}
	else
	{
		// Our DLL failed to load!
		sprintf(debugmsg,"%s","DLL Failed To Load!");MessageBox( NULL, debugmsg,"Debug",MB_OK); //use this where you need to debug the program
	}

	return 0;
}

char* swe_calc(char* parameters,double& x,char* serr)
{ 
static char parameterss[1000];
strncpy(parameterss, parameters, 1000);

// Parameters decomposition
double tjd;
int ipl;
int iflag;
//double x;
//char* serr;

char * writable;

std::string linestr (parameterss);  
          
std::size_t found = linestr.find(";");        
std::string tjdstr = linestr.substr (0,found);
writable = new char[tjdstr.size() + 1];
std::copy(tjdstr.begin(), tjdstr.end(), writable);
writable[tjdstr.size()] = '\0'; // don't forget the terminating 0           
tjd=atof(writable);

linestr.assign(linestr.begin()+found+1,linestr.end());
found = linestr.find(";");
std::string iplstr = linestr.substr (0,found);
writable = new char[iplstr.size() + 1];
std::copy(iplstr.begin(), iplstr.end(), writable);
writable[iplstr.size()] = '\0'; // don't forget the terminating 0
ipl=atoi(writable);

linestr.assign(linestr.begin()+found+1,linestr.end());
found = linestr.find(";");
std::string iflagstr = linestr.substr (0,found);
writable = new char[iflagstr.size() + 1];
std::copy(iflagstr.begin(), iflagstr.end(), writable);
writable[iflagstr.size()] = '\0'; // don't forget the terminating 0
iflag=atoi(writable);

// Typedef functions to hold what is in the DLL
swe_calcFunc _swe_calcFunc;

// The Instance of the DLL.
// LoadLibrary used to load a DLL
HINSTANCE hInstLibrary = LoadLibrary("C:\\qchartist\\includes\\swedll32.dll");

if (hInstLibrary)
	{

	// Our DLL is loaded and ready to go.

	// Set up our function pointers.
	_swe_calcFunc = (swe_calcFunc)GetProcAddress(hInstLibrary, "_swe_calc@24");

		// Check if _AddFunc is currently holding a function, if not don't run it.
		if (_swe_calcFunc)
		{	
			//sprintf(debugmsg,"%i",_swe_date_conversionFunc(year,month,day,utime,cal,tjd));MessageBox( NULL, debugmsg,"Debug",MB_OK); //use this where you need to debug the program			
			sprintf(debugmsg,"%i",_swe_calcFunc(tjd,ipl,iflag,x,serr));
			return debugmsg;
		}
		
	// We're done with the DLL so we need to release it from memory.
	FreeLibrary(hInstLibrary);
	}
	else
	{
		// Our DLL failed to load!
		sprintf(debugmsg,"%s","DLL Failed To Load!");MessageBox( NULL, debugmsg,"Debug",MB_OK); //use this where you need to debug the program
	}

	return 0;
}

char* swe_get_planet_name(char* parameters,char* pname)
{ 
static char parameterss[1000];
strncpy(parameterss, parameters, 1000);

// Parameters decomposition
int ipl;
//char* pname;

char * writable;

std::string linestr (parameterss);  
          
std::size_t found = linestr.find(";");        
std::string iplstr = linestr.substr (0,found);
writable = new char[iplstr.size() + 1];
std::copy(iplstr.begin(), iplstr.end(), writable);
writable[iplstr.size()] = '\0'; // don't forget the terminating 0           
ipl=atoi(writable);

// Typedef functions to hold what is in the DLL
swe_get_planet_nameFunc _swe_get_planet_nameFunc;

// The Instance of the DLL.
// LoadLibrary used to load a DLL
HINSTANCE hInstLibrary = LoadLibrary("C:\\qchartist\\includes\\swedll32.dll");

if (hInstLibrary)
	{

	// Our DLL is loaded and ready to go.

	// Set up our function pointers.
	_swe_get_planet_nameFunc = (swe_get_planet_nameFunc)GetProcAddress(hInstLibrary, "_swe_get_planet_name@8");

		// Check if _AddFunc is currently holding a function, if not don't run it.
		if (_swe_get_planet_nameFunc)
		{	
			//sprintf(debugmsg,"%i",_swe_date_conversionFunc(year,month,day,utime,cal,tjd));MessageBox( NULL, debugmsg,"Debug",MB_OK); //use this where you need to debug the program			
			sprintf(debugmsg,"%i",_swe_get_planet_nameFunc(ipl,pname));
			return debugmsg;
		}
		
	// We're done with the DLL so we need to release it from memory.
	FreeLibrary(hInstLibrary);
	}
	else
	{
		// Our DLL failed to load!
		sprintf(debugmsg,"%s","DLL Failed To Load!");MessageBox( NULL, debugmsg,"Debug",MB_OK); //use this where you need to debug the program
	}

	return 0;
}

char* swe_sidtime(char* parameters)
{ 
static char parameterss[1000];
strncpy(parameterss, parameters, 1000);

// Parameters decomposition
double tjd_ut=atof(parameterss);

// Typedef functions to hold what is in the DLL
swe_sidtimeFunc _swe_sidtimeFunc;

// The Instance of the DLL.
// LoadLibrary used to load a DLL
HINSTANCE hInstLibrary = LoadLibrary("C:\\qchartist\\includes\\swedll32.dll");

if (hInstLibrary)
	{

	// Our DLL is loaded and ready to go.

	// Set up our function pointers.
	_swe_sidtimeFunc = (swe_sidtimeFunc)GetProcAddress(hInstLibrary, "_swe_sidtime@8");

		// Check if _AddFunc is currently holding a function, if not don't run it.
		if (_swe_sidtimeFunc)
		{	
			//sprintf(debugmsg,"%f",_swe_juldayFunc(year,month,day,hour,gregflg));MessageBox( NULL, debugmsg,"Debug",MB_OK); //use this where you need to debug the program			
			sprintf(debugmsg,"%f",_swe_sidtimeFunc(tjd_ut));
			return debugmsg;
		}
		
	// We're done with the DLL so we need to release it from memory.
	FreeLibrary(hInstLibrary);
	}
	else
	{
		// Our DLL failed to load!
		sprintf(debugmsg,"%s","DLL Failed To Load!");MessageBox( NULL, debugmsg,"Debug",MB_OK); //use this where you need to debug the program
	}

	return 0;
}

char* swe_house_pos(char* parameters,double& xpin,char* serr)
{ 
static char parameterss[1000];
strncpy(parameterss, parameters, 1000);

// Parameters decomposition
double armc;
double geolat;
double eps;
int ihsy;
//double x;
//char* serr;

char * writable;

std::string linestr (parameterss);  
          
std::size_t found = linestr.find(";");        
std::string armcstr = linestr.substr (0,found);
writable = new char[armcstr.size() + 1];
std::copy(armcstr.begin(), armcstr.end(), writable);
writable[armcstr.size()] = '\0'; // don't forget the terminating 0           
armc=atof(writable);

linestr.assign(linestr.begin()+found+1,linestr.end());
found = linestr.find(";");
std::string geolatstr = linestr.substr (0,found);
writable = new char[geolatstr.size() + 1];
std::copy(geolatstr.begin(), geolatstr.end(), writable);
writable[geolatstr.size()] = '\0'; // don't forget the terminating 0
geolat=atof(writable);

linestr.assign(linestr.begin()+found+1,linestr.end());
found = linestr.find(";");
std::string epsstr = linestr.substr (0,found);
writable = new char[epsstr.size() + 1];
std::copy(epsstr.begin(), epsstr.end(), writable);
writable[epsstr.size()] = '\0'; // don't forget the terminating 0
eps=atof(writable);

linestr.assign(linestr.begin()+found+1,linestr.end());
found = linestr.find(";");
std::string ihsystr = linestr.substr (0,found);
writable = new char[ihsystr.size() + 1];
std::copy(ihsystr.begin(), ihsystr.end(), writable);
writable[ihsystr.size()] = '\0'; // don't forget the terminating 0
ihsy=atoi(writable);

// Typedef functions to hold what is in the DLL
swe_house_posFunc _swe_house_posFunc;

// The Instance of the DLL.
// LoadLibrary used to load a DLL
HINSTANCE hInstLibrary = LoadLibrary("C:\\qchartist\\includes\\swedll32.dll");

if (hInstLibrary)
	{

	// Our DLL is loaded and ready to go.

	// Set up our function pointers.
	_swe_house_posFunc = (swe_house_posFunc)GetProcAddress(hInstLibrary, "_swe_house_pos@36");

		// Check if _AddFunc is currently holding a function, if not don't run it.
		if (_swe_house_posFunc)
		{	
			//sprintf(debugmsg,"%i",_swe_date_conversionFunc(year,month,day,utime,cal,tjd));MessageBox( NULL, debugmsg,"Debug",MB_OK); //use this where you need to debug the program			
			sprintf(debugmsg,"%f",_swe_house_posFunc(armc,geolat,eps,ihsy,xpin,serr));
			return debugmsg;
		}
		
	// We're done with the DLL so we need to release it from memory.
	FreeLibrary(hInstLibrary);
	}
	else
	{
		// Our DLL failed to load!
		sprintf(debugmsg,"%s","DLL Failed To Load!");MessageBox( NULL, debugmsg,"Debug",MB_OK); //use this where you need to debug the program
	}

	return 0;
}

char* swe_houses(char* parameters,double& hcusps,double& ascmc)
{ 
static char parameterss[1000];
strncpy(parameterss, parameters, 1000);

// Parameters decomposition
double geolat;
double geolon;
double tjd_ut;
int ihsy;
//double x;
//char* serr;

char * writable;

std::string linestr (parameterss);  
          
std::size_t found = linestr.find(";");        
std::string geolatstr = linestr.substr (0,found);
writable = new char[geolatstr.size() + 1];
std::copy(geolatstr.begin(), geolatstr.end(), writable);
writable[geolatstr.size()] = '\0'; // don't forget the terminating 0           
geolat=atof(writable);

linestr.assign(linestr.begin()+found+1,linestr.end());
found = linestr.find(";");
std::string geolonstr = linestr.substr (0,found);
writable = new char[geolonstr.size() + 1];
std::copy(geolonstr.begin(), geolonstr.end(), writable);
writable[geolonstr.size()] = '\0'; // don't forget the terminating 0
geolon=atof(writable);

linestr.assign(linestr.begin()+found+1,linestr.end());
found = linestr.find(";");
std::string tjd_utstr = linestr.substr (0,found);
writable = new char[tjd_utstr.size() + 1];
std::copy(tjd_utstr.begin(), tjd_utstr.end(), writable);
writable[tjd_utstr.size()] = '\0'; // don't forget the terminating 0
tjd_ut=atof(writable);

linestr.assign(linestr.begin()+found+1,linestr.end());
found = linestr.find(";");
std::string ihsystr = linestr.substr (0,found);
writable = new char[ihsystr.size() + 1];
std::copy(ihsystr.begin(), ihsystr.end(), writable);
writable[ihsystr.size()] = '\0'; // don't forget the terminating 0
ihsy=atoi(writable);

// Typedef functions to hold what is in the DLL
swe_housesFunc _swe_housesFunc;

// The Instance of the DLL.
// LoadLibrary used to load a DLL
HINSTANCE hInstLibrary = LoadLibrary("C:\\qchartist\\includes\\swedll32.dll");

if (hInstLibrary)
	{

	// Our DLL is loaded and ready to go.

	// Set up our function pointers.
	_swe_housesFunc = (swe_housesFunc)GetProcAddress(hInstLibrary, "_swe_houses@36");

		// Check if _AddFunc is currently holding a function, if not don't run it.
		if (_swe_housesFunc)
		{	
			//sprintf(debugmsg,"%i",_swe_date_conversionFunc(year,month,day,utime,cal,tjd));MessageBox( NULL, debugmsg,"Debug",MB_OK); //use this where you need to debug the program			
			sprintf(debugmsg,"%i",_swe_housesFunc(tjd_ut,geolat,geolon,ihsy,hcusps,ascmc));
			return debugmsg;
		}
		
	// We're done with the DLL so we need to release it from memory.
	FreeLibrary(hInstLibrary);
	}
	else
	{
		// Our DLL failed to load!
		sprintf(debugmsg,"%s","DLL Failed To Load!");MessageBox( NULL, debugmsg,"Debug",MB_OK); //use this where you need to debug the program
	}

	return 0;
}

char* swe_houses_ex(char* parameters,double& hcusps,double& ascmc)
{ 
static char parameterss[1000];
strncpy(parameterss, parameters, 1000);

// Parameters decomposition
double geolat;
double geolon;
double tjd_ut;
int iflag;
int ihsy;
//double x;
//char* serr;

char * writable;

std::string linestr (parameterss);  
          
std::size_t found = linestr.find(";");        
std::string geolatstr = linestr.substr (0,found);
writable = new char[geolatstr.size() + 1];
std::copy(geolatstr.begin(), geolatstr.end(), writable);
writable[geolatstr.size()] = '\0'; // don't forget the terminating 0           
geolat=atof(writable);

linestr.assign(linestr.begin()+found+1,linestr.end());
found = linestr.find(";");
std::string geolonstr = linestr.substr (0,found);
writable = new char[geolonstr.size() + 1];
std::copy(geolonstr.begin(), geolonstr.end(), writable);
writable[geolonstr.size()] = '\0'; // don't forget the terminating 0
geolon=atof(writable);

linestr.assign(linestr.begin()+found+1,linestr.end());
found = linestr.find(";");
std::string tjd_utstr = linestr.substr (0,found);
writable = new char[tjd_utstr.size() + 1];
std::copy(tjd_utstr.begin(), tjd_utstr.end(), writable);
writable[tjd_utstr.size()] = '\0'; // don't forget the terminating 0
tjd_ut=atof(writable);

linestr.assign(linestr.begin()+found+1,linestr.end());
found = linestr.find(";");
std::string iflagstr = linestr.substr (0,found);
writable = new char[iflagstr.size() + 1];
std::copy(iflagstr.begin(), iflagstr.end(), writable);
writable[iflagstr.size()] = '\0'; // don't forget the terminating 0
iflag=atoi(writable);

linestr.assign(linestr.begin()+found+1,linestr.end());
found = linestr.find(";");
std::string ihsystr = linestr.substr (0,found);
writable = new char[ihsystr.size() + 1];
std::copy(ihsystr.begin(), ihsystr.end(), writable);
writable[ihsystr.size()] = '\0'; // don't forget the terminating 0
ihsy=atoi(writable);

// Typedef functions to hold what is in the DLL
swe_houses_exFunc _swe_houses_exFunc;

// The Instance of the DLL.
// LoadLibrary used to load a DLL
HINSTANCE hInstLibrary = LoadLibrary("C:\\qchartist\\includes\\swedll32.dll");

if (hInstLibrary)
	{

	// Our DLL is loaded and ready to go.

	// Set up our function pointers.
	_swe_houses_exFunc = (swe_houses_exFunc)GetProcAddress(hInstLibrary, "_swe_houses_ex@40");

		// Check if _AddFunc is currently holding a function, if not don't run it.
		if (_swe_houses_exFunc)
		{	
			//sprintf(debugmsg,"%i",_swe_date_conversionFunc(year,month,day,utime,cal,tjd));MessageBox( NULL, debugmsg,"Debug",MB_OK); //use this where you need to debug the program			
			sprintf(debugmsg,"%i",_swe_houses_exFunc(tjd_ut,iflag,geolat,geolon,ihsy,hcusps,ascmc));
			return debugmsg;
		}
		
	// We're done with the DLL so we need to release it from memory.
	FreeLibrary(hInstLibrary);
	}
	else
	{
		// Our DLL failed to load!
		sprintf(debugmsg,"%s","DLL Failed To Load!");MessageBox( NULL, debugmsg,"Debug",MB_OK); //use this where you need to debug the program
	}

	return 0;
}