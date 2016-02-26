// LOADING DLLS THE HARD(ER) WAY (Dynamic Loading)
#include <iostream>
// Need Windows.h for HINSTANCE and DLL Loading and Releasing functions.
#include <windows.h>
#include <string.h>
using namespace std;

// ============================================================================

#define MESSAGE_STACK_SIZE 5

// ============================================================================

typedef struct api_Err

{
	
	int iErr; /**< The error ID */
	
	int iMsgCount; /**< Error level */
	
	char* pstMsg[MESSAGE_STACK_SIZE]; /**< The error message */

} SciErr;
//=============================================================================

typedef struct api_Ctx

{
	
	char* pstName; /**< Function name */

} StrCtx, *pStrCtx;

// ============================================================================

static StrCtx* pvApiCtx = NULL;
// ============================================================================


//int Scilab_test(void);
/*
Yes, instead of
    BOOL StartScilab(char *SCIpath, char *ScilabStartup, int Stacksize);
we use
    int Call_ScilabOpen(char* SCIpath, BOOL advancedMode, char* ScilabStartup, int Stacksize);
and set the advancedMode argument to FALSE. (I tested this workaround
and it tackles the issue).
If you don't need the graphic features. Otherwise, you will have to wait
for a fix (or provide a patch ;)  
*/

// Function pointers that will be used for the DLL functions.
typedef bool (*StartScilabFunc)(char *, char *, int);
typedef int (*SendScilabJobFunc)(char *);
typedef bool (*TerminateScilabFunc)(char *);
typedef int (*Call_ScilabOpenFunc)(char*, bool, char*, int );
typedef SciErr (*readNamedMatrixOfStringFunc)(void*, char*,int*,int*,int*,char** );
typedef SciErr (*readNamedMatrixOfDoubleFunc)(void*, char*,int*,int*,double* );
typedef int (*printErrorFunc)(SciErr*, int );

int conic_section(char* parameters,double (&x)[10000],double (&y)[10000])
{

char parameterss[1000];
strncpy(parameterss, parameters, 1000);

// Parameters decomposition
FLOAT p0[3];
FLOAT p1[3];
FLOAT p2[3];
FLOAT p3[3];
FLOAT p4[3];
int height;
int width;

char * writable;

std::string linestr (parameterss);
std::string mystr;
          
std::size_t found = linestr.find(";");        
mystr = linestr.substr (0,found);
writable = new char[mystr.size() + 1];
std::copy(mystr.begin(), mystr.end(), writable);
writable[mystr.size()] = '\0'; // don't forget the terminating 0           
p0[0]=atof(writable);

linestr.assign(linestr.begin()+found+1,linestr.end());
found = linestr.find(";");
mystr = linestr.substr (0,found);
writable = new char[mystr.size() + 1];
std::copy(mystr.begin(), mystr.end(), writable);
writable[mystr.size()] = '\0'; // don't forget the terminating 0
p0[1]=atof(writable);

p0[2]=1;

linestr.assign(linestr.begin()+found+1,linestr.end());
found = linestr.find(";");
mystr = linestr.substr (0,found);
writable = new char[mystr.size() + 1];
std::copy(mystr.begin(), mystr.end(), writable);
writable[mystr.size()] = '\0'; // don't forget the terminating 0
p1[0]=atof(writable);

linestr.assign(linestr.begin()+found+1,linestr.end());
found = linestr.find(";");
mystr = linestr.substr (0,found);
writable = new char[mystr.size() + 1];
std::copy(mystr.begin(), mystr.end(), writable);
writable[mystr.size()] = '\0'; // don't forget the terminating 0
p1[1]=atof(writable);

p1[2]=1;

linestr.assign(linestr.begin()+found+1,linestr.end());
found = linestr.find(";");
mystr = linestr.substr (0,found);
writable = new char[mystr.size() + 1];
std::copy(mystr.begin(), mystr.end(), writable);
writable[mystr.size()] = '\0'; // don't forget the terminating 0
p2[0]=atof(writable);

linestr.assign(linestr.begin()+found+1,linestr.end());
found = linestr.find(";");
mystr = linestr.substr (0,found);
writable = new char[mystr.size() + 1];
std::copy(mystr.begin(), mystr.end(), writable);
writable[mystr.size()] = '\0'; // don't forget the terminating 0
p2[1]=atof(writable);

p2[2]=1;

linestr.assign(linestr.begin()+found+1,linestr.end());
found = linestr.find(";");
mystr = linestr.substr (0,found);
writable = new char[mystr.size() + 1];
std::copy(mystr.begin(), mystr.end(), writable);
writable[mystr.size()] = '\0'; // don't forget the terminating 0
p3[0]=atof(writable);

linestr.assign(linestr.begin()+found+1,linestr.end());
found = linestr.find(";");
mystr = linestr.substr (0,found);
writable = new char[mystr.size() + 1];
std::copy(mystr.begin(), mystr.end(), writable);
writable[mystr.size()] = '\0'; // don't forget the terminating 0
p3[1]=atof(writable);

p3[2]=1;

linestr.assign(linestr.begin()+found+1,linestr.end());
found = linestr.find(";");
mystr = linestr.substr (0,found);
writable = new char[mystr.size() + 1];
std::copy(mystr.begin(), mystr.end(), writable);
writable[mystr.size()] = '\0'; // don't forget the terminating 0
p4[0]=atof(writable);

linestr.assign(linestr.begin()+found+1,linestr.end());
found = linestr.find(";");
mystr = linestr.substr (0,found);
writable = new char[mystr.size() + 1];
std::copy(mystr.begin(), mystr.end(), writable);
writable[mystr.size()] = '\0'; // don't forget the terminating 0
p4[1]=atof(writable);

p4[2]=1;

linestr.assign(linestr.begin()+found+1,linestr.end());
found = linestr.find(";");
mystr = linestr.substr (0,found);
writable = new char[mystr.size() + 1];
std::copy(mystr.begin(), mystr.end(), writable);
writable[mystr.size()] = '\0'; // don't forget the terminating 0
height=atof(writable);

linestr.assign(linestr.begin()+found+1,linestr.end());
found = linestr.find(";");
mystr = linestr.substr (0,found);
writable = new char[mystr.size() + 1];
std::copy(mystr.begin(), mystr.end(), writable);
writable[mystr.size()] = '\0'; // don't forget the terminating 0
width=atof(writable);

FLOAT a, b, c, d, e, f;
int ret;

ret = toconic(p0, p1, p2, p3, p4, &a, &b, &c, &d, &e, &f);

chdir("C:\\qchartist\\scilab-5.5.2\\bin\\");
// Typedef functions to hold what is in the DLL
StartScilabFunc _StartScilabFunc;
SendScilabJobFunc _SendScilabJobFunc;
TerminateScilabFunc _TerminateScilabFunc;
Call_ScilabOpenFunc _Call_ScilabOpenFunc;
readNamedMatrixOfStringFunc _readNamedMatrixOfStringFunc;
readNamedMatrixOfDoubleFunc _readNamedMatrixOfDoubleFunc;
printErrorFunc _printErrorFunc;

// The Instance of the DLL.
// LoadLibrary used to load a DLL
HINSTANCE hInstLibrary_call_scilab = LoadLibrary("C:\\qchartist\\scilab-5.5.2\\bin\\call_scilab.dll");
HINSTANCE hInstLibrary_api_scilab = LoadLibrary("C:\\qchartist\\scilab-5.5.2\\bin\\api_scilab.dll");

if (hInstLibrary_call_scilab && hInstLibrary_api_scilab)
	{

	// Our DLL is loaded and ready to go.

	// Set up our function pointers.
	_StartScilabFunc = (StartScilabFunc)GetProcAddress(hInstLibrary_call_scilab, "StartScilab");
	_SendScilabJobFunc = (SendScilabJobFunc)GetProcAddress(hInstLibrary_call_scilab, "SendScilabJob");
	_TerminateScilabFunc = (TerminateScilabFunc)GetProcAddress(hInstLibrary_call_scilab, "TerminateScilab");
	_Call_ScilabOpenFunc = (Call_ScilabOpenFunc)GetProcAddress(hInstLibrary_call_scilab, "Call_ScilabOpen");
	_readNamedMatrixOfStringFunc = (readNamedMatrixOfStringFunc)GetProcAddress(hInstLibrary_api_scilab, "readNamedMatrixOfString");
	_readNamedMatrixOfDoubleFunc = (readNamedMatrixOfDoubleFunc)GetProcAddress(hInstLibrary_api_scilab, "readNamedMatrixOfDouble");
	_printErrorFunc = (printErrorFunc)GetProcAddress(hInstLibrary_api_scilab, "printError");

		// Check if _AddFunc is currently holding a function, if not don't run it.
		if (_Call_ScilabOpenFunc)
		{				
			/****** INITIALIZATION **********/
			#ifdef _MSC_VER
			 if ( _Call_ScilabOpenFunc(NULL,0,NULL,NULL) != 0 )
			#else
			 if ( _Call_ScilabOpenFunc(getenv("SCI"),0,NULL,NULL) != 0 )
			#endif
			  {
			   fprintf(stderr,"Error while calling StartScilab\n");
			   return -1;
			  }
		}

		if (_SendScilabJobFunc)
		{	

std::string conicfunction="function [z]=fct(x,y);"+std::string ("z=")+boost::lexical_cast<std::string>(a)+std::string ("*x*x+")+boost::lexical_cast<std::string>(b)+std::string("*x*y+")+boost::lexical_cast<std::string>(c)+std::string("*y*y+")+boost::lexical_cast<std::string>(d)+std::string("*x+")+boost::lexical_cast<std::string>(e)+std::string("*y+")+boost::lexical_cast<std::string>(f)+std::string(";endfunction;");
char * conicfunctionchar = new char [conicfunction.length()+1];
std::strcpy (conicfunctionchar, conicfunction.c_str());

std::string workingspace="x=0:"+boost::lexical_cast<std::string>(width)+";y="+boost::lexical_cast<std::string>(height)+":0;";
char * workingspacechar = new char [workingspace.length()+1];
std::strcpy (workingspacechar, workingspace.c_str());

			std::string myheight=boost::lexical_cast<std::string>(height);
			std::string mywidth=boost::lexical_cast<std::string>(width);

			std::string forline1="for i="+myheight+":1:0;rep=fsolve([0,i],coniques);n=n+1;a(n)=rep(1);b(n)=rep(2);end;";
			char * forline1char = new char [forline1.length()+1];
			std::strcpy (forline1char, forline1.c_str());

			std::string fsolveline="rep=fsolve(["+mywidth+",i],coniques);";  			
			
			std::string forline2="for i="+myheight+":1:0;"+fsolveline+"n=n+1;a(n)=rep(1);b(n)=rep(2);end;";
			char * forline2char = new char [forline2.length()+1];
			std::strcpy (forline2char, forline2.c_str());

			/****** ACTUAL Scilab TASKS *******/	
			_SendScilabJobFunc(conicfunctionchar);			
			_SendScilabJobFunc("function [z]=f(x,y);z=0*x*y;endfunction;");
			_SendScilabJobFunc(workingspacechar);
			_SendScilabJobFunc("function [Y]=coniques(X) , Y=[fct(X(1),X(2)),f(X(1),X(2))];endfunction");
			_SendScilabJobFunc("n=0;");
			_SendScilabJobFunc(forline1char);	
			_SendScilabJobFunc(forline2char);

		}

		if (_readNamedMatrixOfDoubleFunc && _printErrorFunc)
		{

/* Read the previously declared matrix of double */

int rowB_ = 0, colB_ = 0, lp_ = 0;
double *matrixOfDoubleB = NULL;
int i=0, j=0;
char variableToBeRetrievedB[] = "a";
SciErr sciErr;

/* First, retrieve the size of the matrix */
sciErr = _readNamedMatrixOfDoubleFunc(pvApiCtx, variableToBeRetrievedB, &rowB_, &colB_, NULL);
if(sciErr.iErr)
{
    _printErrorFunc(&sciErr, 0);
}

/* Alloc the memory */
matrixOfDoubleB = (double*)malloc((rowB_*colB_)*sizeof(double));

/* Load the matrix */
sciErr = _readNamedMatrixOfDoubleFunc(pvApiCtx, variableToBeRetrievedB, &rowB_, &colB_, matrixOfDoubleB);
if(sciErr.iErr)
{
    _printErrorFunc(&sciErr, 0);
}

//printf("\n");
//printf("Display from B formated (size: %d, %d):\n",rowB_, colB_);
for(j = 0 ; j < rowB_ ; j++)
 {
  for(i = 0 ; i < colB_ ; i++)
   {
    /* Display the formated matrix ... the way the user
     * expect */
    //printf("%5.2f ",matrixOfDoubleB[i * rowB_ + j]);
    x[i * rowB_ + j]=matrixOfDoubleB[i * rowB_ + j];
   }
  //printf("\n"); /* New row of the matrix */
 }

rowB_ = 0, colB_ = 0, lp_ = 0;
*matrixOfDoubleB = NULL;
i=0; j=0;
strcpy(variableToBeRetrievedB, "b");

/* First, retrieve the size of the matrix */
sciErr = _readNamedMatrixOfDoubleFunc(pvApiCtx, variableToBeRetrievedB, &rowB_, &colB_, NULL);
if(sciErr.iErr)
{
    _printErrorFunc(&sciErr, 0);
}

/* Alloc the memory */
matrixOfDoubleB = (double*)malloc((rowB_*colB_)*sizeof(double));

/* Load the matrix */
sciErr = _readNamedMatrixOfDoubleFunc(pvApiCtx, variableToBeRetrievedB, &rowB_, &colB_, matrixOfDoubleB);
if(sciErr.iErr)
{
    _printErrorFunc(&sciErr, 0);
}

//printf("\n");
//printf("Display from B formated (size: %d, %d):\n",rowB_, colB_);
for(j = 0 ; j < rowB_ ; j++)
 {
  for(i = 0 ; i < colB_ ; i++)
   {
    /* Display the formated matrix ... the way the user
     * expect */
    //printf("%5.2f ",matrixOfDoubleB[i * rowB_ + j]);
    y[i * rowB_ + j]=matrixOfDoubleB[i * rowB_ + j];
   }
  //printf("\n"); /* New row of the matrix */
 }

		}

		if (_TerminateScilabFunc)
		{				
			/****** TERMINATION **********/
 			if ( _TerminateScilabFunc(NULL) == FALSE ) {
  			fprintf(stderr,"Error while calling TerminateScilab\n");
  			return -2;
 			}
		}
		
	// We're done with the DLL so we need to release it from memory.
	FreeLibrary(hInstLibrary_call_scilab);
	FreeLibrary(hInstLibrary_api_scilab);
	}
	else
	{
		// Our DLL failed to load!
		sprintf(debugmsg,"%s","DLL Failed To Load!");MessageBox( NULL, debugmsg,"Debug",MB_OK); //use this where you need to debug the program
	}

chdir("C:\\qchartist\\");
	return 0;

}

int Scilab_test(void)
{

chdir("C:\\qchartist\\scilab-5.5.2\\bin\\");
// Typedef functions to hold what is in the DLL
StartScilabFunc _StartScilabFunc;
SendScilabJobFunc _SendScilabJobFunc;
TerminateScilabFunc _TerminateScilabFunc;
Call_ScilabOpenFunc _Call_ScilabOpenFunc;
readNamedMatrixOfStringFunc _readNamedMatrixOfStringFunc;
readNamedMatrixOfDoubleFunc _readNamedMatrixOfDoubleFunc;
printErrorFunc _printErrorFunc;

// The Instance of the DLL.
// LoadLibrary used to load a DLL
HINSTANCE hInstLibrary_call_scilab = LoadLibrary("C:\\qchartist\\scilab-5.5.2\\bin\\call_scilab.dll");
HINSTANCE hInstLibrary_api_scilab = LoadLibrary("C:\\qchartist\\scilab-5.5.2\\bin\\api_scilab.dll");

if (hInstLibrary_call_scilab && hInstLibrary_api_scilab)
	{

	// Our DLL is loaded and ready to go.

	// Set up our function pointers.
	_StartScilabFunc = (StartScilabFunc)GetProcAddress(hInstLibrary_call_scilab, "StartScilab");
	_SendScilabJobFunc = (SendScilabJobFunc)GetProcAddress(hInstLibrary_call_scilab, "SendScilabJob");
	_TerminateScilabFunc = (TerminateScilabFunc)GetProcAddress(hInstLibrary_call_scilab, "TerminateScilab");
	_Call_ScilabOpenFunc = (Call_ScilabOpenFunc)GetProcAddress(hInstLibrary_call_scilab, "Call_ScilabOpen");
	_readNamedMatrixOfStringFunc = (readNamedMatrixOfStringFunc)GetProcAddress(hInstLibrary_api_scilab, "readNamedMatrixOfString");
	_readNamedMatrixOfDoubleFunc = (readNamedMatrixOfDoubleFunc)GetProcAddress(hInstLibrary_api_scilab, "readNamedMatrixOfDouble");
	_printErrorFunc = (printErrorFunc)GetProcAddress(hInstLibrary_api_scilab, "printError");

		// Check if _AddFunc is currently holding a function, if not don't run it.
		if (_Call_ScilabOpenFunc)
		{				
			/****** INITIALIZATION **********/
			#ifdef _MSC_VER
			 if ( _Call_ScilabOpenFunc(NULL,0,NULL,NULL) != 0 )
			#else
			 if ( _Call_ScilabOpenFunc(getenv("SCI"),0,NULL,NULL) != 0 )
			#endif
			  {
			   fprintf(stderr,"Error while calling StartScilab\n");
			   return -1;
			  }
		}

		if (_SendScilabJobFunc)
		{		
			/****** ACTUAL Scilab TASKS *******/		
			_SendScilabJobFunc("myMatrix=['sample','for the help']");		
			//_SendScilabJobFunc("disp(myMatrix);"); // Will display !sample  for the help  !
			//_SendScilabJobFunc("disp([2,3]+[-44,39]);"); // Will display   - 42.    42.
			_SendScilabJobFunc("w=[1.1,2.2,3.3,4.4]");
		}

		if (_readNamedMatrixOfStringFunc && _printErrorFunc)
		{
/* Load the previously set variable A */
// See: modules/call_scilab/examples/basicExamples/readwritestring.c

char variableToBeRetrieved[]="myMatrix";
int iRows       = 0;
int iCols       = 0;
int i,j;
int* piAddr     = NULL;
int* piLen      = NULL;
char** pstData  = NULL;
SciErr sciErr;

//first call to retrieve dimensions
sciErr = _readNamedMatrixOfStringFunc(pvApiCtx,variableToBeRetrieved,&iRows, &iCols, NULL, NULL);
if(sciErr.iErr)
{
    _printErrorFunc(&sciErr, 0);
}

piLen = (int*)malloc(sizeof(int) * iRows * iCols);
//second call to retrieve length of each string
sciErr = _readNamedMatrixOfStringFunc(pvApiCtx,variableToBeRetrieved, &iRows, &iCols, piLen, NULL);
if(sciErr.iErr)
{
    _printErrorFunc(&sciErr, 0);
}

pstData = (char**)malloc(sizeof(char*) * iRows * iCols);
for(i = 0 ; i < iRows * iCols ; i++)
    {
        pstData[i] = (char*)malloc(sizeof(char) * (piLen[i] + 1));//+ 1 for null termination
    }
//third call to retrieve data
sciErr = _readNamedMatrixOfStringFunc(pvApiCtx, variableToBeRetrieved, &iRows, &iCols, piLen, pstData);
if(sciErr.iErr)
{
    _printErrorFunc(&sciErr, 0);
}

printf("\n");
printf("Load and display of A:\n");
for(j = 0 ; j < iCols ; j++)
{
    for(i = 0 ; i < iRows ; i++)
    {
        /* Display the formated matrix with same scilab indice */
        //printf("[%d,%d] = %s\n",j+1,i+1,pstData[j* iRows + i]);
sprintf(debugmsg,"%s",pstData[j* iRows + i]);
MessageBox( NULL, debugmsg,"Debug",MB_OK); //use this where you need to debug the program

    }
}

printf("\n");
free(piLen);
for(i = 0 ; i < iRows * iCols ; i++)
    {
        free(pstData[i]);
    }
free(pstData);
			  
		}


		if (_readNamedMatrixOfDoubleFunc && _printErrorFunc)
		{

/* Read the previously declared matrix of double B */
int rowB_ = 0, colB_ = 0, lp_ = 0;
double *matrixOfDoubleB = NULL;
int i = 0, j = 0;
char variableToBeRetrievedB[] = "w";
SciErr sciErr;

/* First, retrieve the size of the matrix */
sciErr = _readNamedMatrixOfDoubleFunc(pvApiCtx, variableToBeRetrievedB, &rowB_, &colB_, NULL);
if(sciErr.iErr)
{
    _printErrorFunc(&sciErr, 0);
}

/* 
 * Prior to Scilab 5.2:
 * C2F(cmatptr)(variableToBeRetrievedB, &rowB_, &colB_, &lp_, strlen(variableToBeRetrievedB));
 */

/* Alloc the memory */
matrixOfDoubleB = (double*)malloc((rowB_*colB_)*sizeof(double));

/* Load the matrix */
sciErr = _readNamedMatrixOfDoubleFunc(pvApiCtx, variableToBeRetrievedB, &rowB_, &colB_, matrixOfDoubleB);
if(sciErr.iErr)
{
    _printErrorFunc(&sciErr, 0);
}

/* 
 * Prior to Scilab 5.2:
 * C2F(creadmat)(variableToBeRetrievedB,&rowB_,&colB_,matrixOfDoubleB,strlen(variableToBeRetrievedB) );
 */

printf("\n");
printf("Display from B formated (size: %d, %d):\n",rowB_, colB_);
for(j = 0 ; j < rowB_ ; j++)
 {
  for(i = 0 ; i < colB_ ; i++)
   {
    /* Display the formated matrix ... the way the user
     * expect */
    //printf("%5.2f ",matrixOfDoubleB[i * rowB_ + j]);
sprintf(debugmsg,"%5.2f ",matrixOfDoubleB[i * rowB_ + j]);
MessageBox( NULL, debugmsg,"Debug",MB_OK); //use this where you need to debug the program
   }
  //printf("\n"); /* New row of the matrix */
 }

		}

		if (_TerminateScilabFunc)
		{				
			/****** TERMINATION **********/
 			if ( _TerminateScilabFunc(NULL) == FALSE ) {
  			fprintf(stderr,"Error while calling TerminateScilab\n");
  			return -2;
 			}
		}
		
	// We're done with the DLL so we need to release it from memory.
	FreeLibrary(hInstLibrary_call_scilab);
	FreeLibrary(hInstLibrary_api_scilab);
	}
	else
	{
		// Our DLL failed to load!
		sprintf(debugmsg,"%s","DLL Failed To Load!");MessageBox( NULL, debugmsg,"Debug",MB_OK); //use this where you need to debug the program
	}

chdir("C:\\qchartist\\");
	return 0;
}