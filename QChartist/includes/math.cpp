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
#include <iterator>
//#include <cmath.h>
#include <math.h>
#define _POSIX_SOURCE
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
//#include <unistd.h>
#undef _POSIX_SOURCE

using namespace std;

// C++ to RapidQ Math Functions

// Maths Routines

char* rq_add(char* a, char* b)
{   
    char line [ 128 ];
    std::ostringstream o;
    o << atof(a)+atof(b);   
    strcpy(line,o.str().c_str());
    return line;   
}

char* rq_subtract(char* a, char* b)
{
    char line [ 128 ];
    std::ostringstream o;
    o << atof(a)-atof(b);   
    strcpy(line,o.str().c_str());
    return line; 
}

char* rq_multiply(char* a, char* b)
{
    char line [ 128 ];
    std::ostringstream o;
    o << atof(a)*atof(b);   
    strcpy(line,o.str().c_str());
    return line; 
}

char* rq_divide(char* a, char* b)
{
    char line [ 128 ];
    std::ostringstream o;
    o << atof(a)/atof(b);   
    strcpy(line,o.str().c_str());
    return line; 
}

char* rq_power(char* a, char* b)
{
    char line [ 128 ];
    std::ostringstream o;
    o << pow(atof(a),atof(b));   
    strcpy(line,o.str().c_str());
    return line; 
}

char* rq_abs(char* a)
{
    char line [ 128 ];
    std::ostringstream o;
    o << fabs(atof(a));   
    strcpy(line,o.str().c_str());
    return line;
}

char* rq_acos(char* a)
{
    char line [ 128 ];
    std::ostringstream o;
    o << acos(atof(a));   
    strcpy(line,o.str().c_str());
    return line;
}

char* rq_asin(char* a)
{
    char line [ 128 ];
    std::ostringstream o;
    o << asin(atof(a));   
    strcpy(line,o.str().c_str());
    return line;
}

char* rq_atan(char* a)
{
    char line [ 128 ];
    std::ostringstream o;
    o << atan(atof(a));   
    strcpy(line,o.str().c_str());
    return line;
}

char* rq_ceil(char* a)
{
    char line [ 128 ];
    std::ostringstream o;
    o << ceil(atof(a));   
    strcpy(line,o.str().c_str());
    return line;
}

char* rq_cos(char* a)
{
    char line [ 128 ];
    std::ostringstream o;
    o << cos(atof(a));   
    strcpy(line,o.str().c_str());
    return line;
}

char* rq_exp(char* a)
{
    char line [ 128 ];
    std::ostringstream o;
    o << exp(atof(a));   
    strcpy(line,o.str().c_str());
    return line;
}

char* rq_floor(char* a)
{
    char line [ 128 ];
    std::ostringstream o;
    o << floor(atof(a));   
    strcpy(line,o.str().c_str());
    return line;
}

char* rq_log(char* a)
{
    char line [ 128 ];
    std::ostringstream o;
    o << log(atof(a));   
    strcpy(line,o.str().c_str());
    return line;
}

char* rq_sin(char* a)
{
    char line [ 128 ];
    std::ostringstream o;
    o << sin(atof(a));   
    strcpy(line,o.str().c_str());
    return line;
}

char* rq_sqr(char* a)
{
    char line [ 128 ];
    std::ostringstream o;
    o << sqrt(atof(a));   
    strcpy(line,o.str().c_str());
    return line;
}

char* rq_tan(char* a)
{
    char line [ 128 ];
    std::ostringstream o;
    o << tan(atof(a));   
    strcpy(line,o.str().c_str());
    return line;
}

char* rq_atan2(char* a, char* b)
{
    char line [ 128 ];
    std::ostringstream o;
    o << atan2(atof(a),atof(b));   
    strcpy(line,o.str().c_str());
    return line;
}

char* rq_sinh(char* a)
{
    char line [ 128 ];
    std::ostringstream o;
    o << sinh(atof(a));   
    strcpy(line,o.str().c_str());
    return line;
}

char* rq_cosh(char* a)
{
    char line [ 128 ];
    std::ostringstream o;
    o << cosh(atof(a));   
    strcpy(line,o.str().c_str());
    return line;
}

char* rq_tanh(char* a)
{
    char line [ 128 ];
    std::ostringstream o;
    o << tanh(atof(a));   
    strcpy(line,o.str().c_str());
    return line;
}

char* rq_log10(char* a)
{
    char line [ 128 ];
    std::ostringstream o;
    o << log10(atof(a));   
    strcpy(line,o.str().c_str());
    return line;
}

char* bppcompute()
{

double X;
double Y;
int i;

Y = 0.5;
for (i = 1; i<=50000000; i++) {
  Y = Y / 1.1234;
  Y = Y * 1.1234;
  X = acos(Y);
  X = asin(Y);
  X = atan(Y);
  X = cos(Y);
  X = exp(Y);
  X = log(Y);
  X = sin(Y);
  X = sqrt(Y);
  X = tan(Y);
}
cout << Y;

}