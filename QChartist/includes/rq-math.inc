'------------------------------------------------------------------
'>>>>>>   rq-math.inc   Version 1.1 (09-2000)<<<<<<<<<<<<<<<<<<<<
'------------------------------------------------------------------
'Rapid-Q Mathematics $Includes
'written by Bruno Schäfer <bup.schaefer@planet-interkom.de>
'------------------------------------------------------------------
'!!!!    All angles are in radiant !!!   ... but not in function DEG2RAD  :-)
'If an ERROR occurs in some functions there will be a Messagebox
'and the returned value is ZERO !!!!!
'
'Rapid-Q - http://www.basicguru.com/abc/rapidq/
'http://www.egroups.com/group/rapidq
'This .inc.-file  contains additional commonly used mathematical functions
'and utilities (in addition to the standard mathematical functions
'supported in William Yu's Rapid-Q)
'This is a work in progress, so don't expect too much.
'Many thanks for ideas and remarks:
'send an e-mail to (bup.schaefer@planet-interkom.de) or the egroup.
'planned functions in next versions:
'better trapping of ERRORs and of undefined values  ...and more functions:
'different round methods,' vectoroperations, derivation, integral-functions,
'more natural constants,scientific function,' arithmetical and statistical
'functions (perhaps in own $includes ???)...
'==============================================================================

$TYPECHECK off

CONST rqPI = 3.141592654  '(This is PI)
CONST rqE = 2.718281828  '(This is e)
CONST rqh = 6.62620 * 10^(- 34) '(J*S: Planck const.)
CONST rqc = 2.997925 * 10^8  '(m/s: velocity of light in vacuum)
const rqsnd = 331.46 '(m/s: sound speed in air)
const rqaog = 9.80665 '(m/s(+2): acceleration of gravity)
const rqat = 0.00002 '(Pa: audibility threshold)

'-------------------------------------------------------------------------------
'ACOSH() returns the hyperbolic areacosine of x
'-------------------------------------------------------------------------------
FUNCTION ACOSH(value AS DOUBLE) AS DOUBLE
    SELECT CASE value
        CASE IS < 1
            MESSAGEBOX("Invalid Argument !!!" , "ACOSH - Error" , 0)
        CASE IS >= 1
            ACOSH = (LOG(value + SQR(value^2 - 1)))
    END SELECT
END FUNCTION
'-------------------------------------------------------------------------------
'ACOT() returns the arccotangent of x
'-------------------------------------------------------------------------------
FUNCTION ACOT(value AS DOUBLE) AS DOUBLE
    ACOT = ((rqPI / 2) - ATAN(value))
END FUNCTION
'-------------------------------------------------------------------------------
'ACOTH() returns the hyperbolic areacotangent of x
'-------------------------------------------------------------------------------
FUNCTION ACOTH(value AS DOUBLE) AS DOUBLE
    SELECT CASE ABS(value)
        CASE IS > 1
            ACOTH = (LOG((value + 1) / (value - 1)) * 0.5)
        CASE ELSE
            MESSAGEBOX("ERROR: Invalid Argument !!!" , "ACOTH - Error" , 0)
    END SELECT
END FUNCTION
'-------------------------------------------------------------------------------
'ACOSEC() returns the arccosecans of x
'-------------------------------------------------------------------------------
FUNCTION ACOSEC(value AS DOUBLE) AS DOUBLE
    SELECT CASE ABS(value)
        CASE IS < 1
            MESSAGEBOX("Invalid Argument !!!" , "ACOSEC - Error" , 0)
        CASE ELSE
            ACOSEC = (ASIN(1 / value))
    END SELECT
END FUNCTION
'-------------------------------------------------------------------------------
'ASINH() returns the hyperbolic areasine of x
'-------------------------------------------------------------------------------
FUNCTION ASINH(value AS DOUBLE) AS DOUBLE
    ASINH = LOG(value + (SQR(value * value + 1)))
END FUNCTION
'-------------------------------------------------------------------------------
'ACOSECH() returns the hyperbolic arccosecans of x
'-------------------------------------------------------------------------------
FUNCTION ACOSECH(value AS DOUBLE) AS DOUBLE
    SELECT CASE ABS(value)
        CASE = 0
            MESSAGEBOX("Invalid Argument !!!" , "ACOSECH - Error" , 0)
        CASE ELSE
            ACOSECH = (ASINH(1 / value))
    END SELECT
END FUNCTION
'-------------------------------------------------------------------------------
'ADDZ() returns the sum of two complex numbers
'-------------------------------------------------------------------------------
FUNCTION ADDZ(Z() AS DOUBLE) AS DOUBLE
    re1 = Z(0)  :  im1 = Z(1)  :  re2 = Z(2)  :  im2 = Z(3)
    Z(0) = re1 + re2
    Z(1) = im1 + im2
    Z(2) = 0
    Z(3) = 0
    ADDZ = Z()
END FUNCTION
'-------------------------------------------------------------------------------
'ASEC() returns the arccosecans of x
'-------------------------------------------------------------------------------
FUNCTION ASEC(value AS DOUBLE) AS DOUBLE
    SELECT CASE ABS(value)
        CASE IS < 1
            MESSAGEBOX("ERROR:Invalid Argument !!!" , "ASEC - Error" , 0)
        CASE ELSE
            ASEC = (rqPI / 2 - ASIN(1 / value))
    END SELECT
END FUNCTION
'-------------------------------------------------------------------------------
'ASECH() returns the hyperbolic arccosecans of x
'-------------------------------------------------------------------------------
FUNCTION ASECH(value AS DOUBLE) AS DOUBLE
    SELECT CASE ABS(value)
        CASE IS > 1
            MESSAGEBOX("ERROR:Invalid Argument !!!" , "ASECH - Error" , 0)
        CASE IS <= 0
            MESSAGEBOX("ERROR:Invalid Argument !!!" , "ASECH - Error" , 0)
        CASE ELSE
            ASECH = (ACOSH(1 / value))
    END SELECT
END FUNCTION
'-------------------------------------------------------------------------------
'ATANH() returns the hyperbolic areatangent of x
'-------------------------------------------------------------------------------
FUNCTION ATANH(value AS DOUBLE) AS DOUBLE
    SELECT CASE ABS(value)
        CASE IS < 1
            ATANH = (LOG((1 + value) / (1 - value)) * 0.5)
        CASE 0
            ATANH = 1
        CASE ELSE
            MESSAGEBOX("ERROR:Invalid Argument !!!" , "ATANH - Error" , 0)
    END SELECT
END FUNCTION
'--------------------------------------------------------------------------------
'CONJZ() returns the conjugated complex number of a complex number
'--------------------------------------------------------------------------------
FUNCTION CONJZ(Z() AS DOUBLE) AS DOUBLE
    re = Z(0)  :  im = Z(1)
    Z(1) = im * (- 1)
    CONJZ = Z()
END FUNCTION
'-------------------------------------------------------------------------------
'COSEC() returns the cosecans of x
'-------------------------------------------------------------------------------
FUNCTION COSEC(value AS DOUBLE) AS DOUBLE
    COSEC = 1 / SIN(value)
END FUNCTION
'-------------------------------------------------------------------------------
'COSECH() returns the hyperbolic cosecans of x
'-------------------------------------------------------------------------------
FUNCTION COSECH(value AS DOUBLE) AS DOUBLE
    COSECH = (2 / (EXP(value) - EXP(value * - 1)))
END FUNCTION
'-------------------------------------------------------------------------------
'COSH() returns the hyperbolic cosine of x
'-------------------------------------------------------------------------------
FUNCTION COSH(value AS DOUBLE) AS DOUBLE
    COSH = (0.5 * (EXP(value) + EXP(value * - 1)))
    IF value = 0 THEN COSH = 1
END FUNCTION
'--------------------------------------------------------------------------------
'COSZ() returns the cosine of a complex number
'--------------------------------------------------------------------------------
FUNCTION COSZ(Z() AS DOUBLE) AS DOUBLE
    re = Z(0)  :  im = Z(1)
    Z(0) = COS(re) * COSH(im)
    Z(1) = SIN(re) * SINH(im)
    COSZ = Z()
END FUNCTION
'--------------------------------------------------------------------------------
'COSHZ() sine of a complex number
'--------------------------------------------------------------------------------
FUNCTION COSHZ(Z() AS DOUBLE) AS DOUBLE
    re = Z(0)  :  im = Z(1)
    Z(0) = COSH(re) * COS(im)
    Z(1) = SINH(re) * SIN(im)
    COSHZ = Z()
END FUNCTION
'-------------------------------------------------------------------------------
'COT() returns the cotangent of x
'-------------------------------------------------------------------------------
FUNCTION COT(value AS DOUBLE) AS DOUBLE
    COT = 1 / TAN(value)
END FUNCTION
'-------------------------------------------------------------------------------
'COTH() returns the hyperbolic cotangent of x
'-------------------------------------------------------------------------------
FUNCTION COTH(value AS DOUBLE) AS DOUBLE
    SELECT CASE value
        CASE 0
            MESSAGEBOX("ERROR: Invalid Argument !!!" , "COTH - Error" , 0)
        CASE ELSE
            COTH = COSH(value) / SINH(value)
    END SELECT
END FUNCTION
'-------------------------------------------------------------------------------
'DEG2RAD() returns radians instead of degrees
'-------------------------------------------------------------------------------
FUNCTION DEG2RAD(value AS DOUBLE) AS DOUBLE
    DEG2RAD = value * 0.017453
END FUNCTION
'--------------------------------------------------------------------------------
'DIVZ() returns the quotient of two complex numbers
'--------------------------------------------------------------------------------
'DIVZ() = Z1 / Z2
FUNCTION DIVZ(Z() AS DOUBLE) AS DOUBLE
    re1 = Z(0)  :  im1 = Z(1)  :  re2 = Z(2)  :  im2 = Z(3)
    Z(0) = (req * re2 + im1 * im2) / (re2 * re2 + im2 * im2)
    Z(1) = (- re1 * im2 + re2 * im1) / (re2 * re2 + im2 * im2)
    Z(2) = 0
    Z(3) = 0
    DIVZ = Z()
END FUNCTION
'--------------------------------------------------------------------------------
'EVEN() returns "1" (= true) if a number is even, else "0"
'--------------------------------------------------------------------------------
FUNCTION EVEN(value AS INTEGER) AS INTEGER
    IF FRAC(value / 2) = 0 THEN
        EVEN = 1
    ELSE
        EVEN = 0
    END IF
END FUNCTION
'--------------------------------------------------------------------------------
'EXPZ() returns the exponential value of a complex number (= e^z)
'--------------------------------------------------------------------------------
FUNCTION EXPZ(Z() AS DOUBLE) AS DOUBLE
    re = Z(0)  :  im = Z(1)  :  a = Z(3)
    Z(0) = EXP(re) * COS(im)
    Z(1) = EXP(re) * SIN(im)
    EXPZ = Z()
END FUNCTION
'-------------------------------------------------------------------------------
'FAC() returns the factorial of the integer x
'-------------------------------------------------------------------------------
FUNCTION FAC(value AS LONG) AS LONG
    SELECT CASE value
        CASE IS < 13
            N = value
            value = 1
            FOR I = 1 TO N
                value = value * I
            NEXT I
            FAC = value
        CASE IS > 12
            MESSAGEBOX("ERROR: Invalid Argument !!! Argument must <= 12!" , "FAC - Error" , 0)
    END SELECT
END FUNCTION
'--------------------------------------------------------------------------------
'FIX() truncates the argument to closest integer value towards zero
'--------------------------------------------------------------------------------


'-------------------------------------------------------------------------------
'GCD() returns the greatest common denominator of two integers
'based on the Euclidean algorithm
'-------------------------------------------------------------------------------
FUNCTION GCD(value1 AS DOUBLE , value2 AS DOUBLE) AS LONG
    ERROR% = 0
    SELECT CASE value1
        CASE IS <> INT(value1) 'Integer check
            ERROR% = 1
        CASE 0  'ZERO check
            ERROR% = 2
    END SELECT
    SELECT CASE value2
        CASE IS <> INT(value2) 'Integer check
            ERROR% = 1
        CASE 0  'ZERO Check
            ERROR% = 2
    END SELECT
    SELECT CASE ERROR%
        CASE 0
            value1 = ABS(value1)  :  value2 = ABS(value2) 'Euclidean algorithm
            DO
                Res = value1 - value2 * INT(value1 / value2)
                IF Res = 0 THEN GCD = value2
                value1 = value2
                value2 = Res
            LOOP UNTIL Res = 0
        CASE 1
            GCD = 0
            MESSAGEBOX("Invalid Argument (no INTEGER)!!!" , "GCD - Error" , 0)
        CASE 2
            GCD = 0
            MESSAGEBOX("Invalid Argument (ZERO)!!!" , "GCD - Error" , 0)
    END SELECT
END FUNCTION
'--------------------------------------------------------------------------------
'INVZ() returns the reciprocal value of a complex number
'--------------------------------------------------------------------------------
'INVZ(Z) = 1/Z
FUNCTION INVZ(Z() AS DOUBLE) AS DOUBLE
    re = Z(0)  :  im = Z(1)
    Z(0) = re / (re * re + im * im)
    Z(1) = im / (re * re + im * im)
    INVZ = Z()
END FUNCTION
'--------------------------------------------------------------------------------
'LOGZ() returns the natural logarithm of a complex number
'--------------------------------------------------------------------------------
FUNCTION LOGZ(Z() AS DOUBLE) AS DOUBLE
    re = Z(0)  :  im = Z(1)
    Z(0) = LOG(re / (re * re + im * im))
    Z(1) = im / (re * re + im * im)
    LOGZ = Z()
END FUNCTION
'--------------------------------------------------------------------------------
'LOG10() returns the base 10 log of x
'--------------------------------------------------------------------------------
FUNCTION LOG10(value AS DOUBLE) AS DOUBLE
    LOG10 = (LOG(value) * LOG(10 * rqE))
END FUNCTION
'--------------------------------------------------------------------------------
'LOG10Z() returns the 10-th logarithm of z (base is 10)
'--------------------------------------------------------------------------------
FUNCTION LOG10Z(Z() AS DOUBLE) AS DOUBLE
    re = Z(0)  :  im = Z(1)
    Z(0) = LOG(re / (re * re + im * im)) / LOG(10)
    Z(1) = im / (re * re + im * im) / LOG(10)
    LOG10Z = Z()
END FUNCTION
'--------------------------------------------------------------------------------
'LOGAZ() returns the a-th logarithm of z (base is a)
'--------------------------------------------------------------------------------
FUNCTION LOGAZ(Z() AS DOUBLE) AS DOUBLE
    re = Z(0)  :  im = Z(1)  :  a = Z(3)
    Z(0) = LOG(re / (re * re + im * im)) / LOG(a)
    Z(1) = im / (re * re + im * im) / LOG(a)
    LOGAZ = Z()
END FUNCTION
'--------------------------------------------------------------------------------
'MAGZ() returns the absolute value of a complex number
'--------------------------------------------------------------------------------
FUNCTION MAGZ(Z() AS DOUBLE) AS DOUBLE
    re = Z(0)  :  im = Z(1)
    Z(0) = SQR(re * re + im * im) '= |Z|
    Z(1) = 0
    MAGZ = Z()
END FUNCTION
'--------------------------------------------------------------------------------
'MULZ() returns the product of two complex numbers
'--------------------------------------------------------------------------------
FUNCTION MULZ(Z() AS DOUBLE) AS DOUBLE
    re1 = Z(0)  :  im1 = Z(1)  :  re2 = Z(2)  :  im2 = Z(3)
    Z(0) = re1 * re2 - im1 * im2
    Z(1) = re1 * im2 + re2 * im1
    Z(2) = 0
    Z(3) = 0
    MULZ = Z()
END FUNCTION
'--------------------------------------------------------------------------------
'NORZ() returns the normal form of a complex value
'--------------------------------------------------------------------------------
'Z = x + iy = re + i*im   =   r*e^i*theta
FUNCTION NORZ(Z() AS DOUBLE) AS DOUBLE
    re = Z(0)  :  im = Z(1)
    Z(0) = SQR(re * re + im * im) '= r = value
    Z(1) = ATAN(im / re) '= theta = argument
    NORZ = Z() 'Z() = (r,theta)
END FUNCTION
'--------------------------------------------------------------------------------
'ODD() returns "1" (=true) if a number(INTEGER) is odd
'--------------------------------------------------------------------------------
FUNCTION ODD(value AS INTEGER) AS INTEGER
    IF FRAC(value / 2) <> 0 THEN
        ODD = 1
    ELSE
        ODD = 0
    END IF
END FUNCTION
'--------------------------------------------------------------------------------
'POLZ() returns Z IN the polar coordinate system
'--------------------------------------------------------------------------------
'Transformation from    z = x + iy     to     z = r*cos((phi) + r*i*sin(phi)
FUNCTION POLZ(Z() AS DOUBLE) AS DOUBLE
    re = Z(0)  :  im = Z(1)
    Z(0) = SQR(re * re + im * im) * COS(ATAN(im / re))
    Z(1) = SQR(re * re + im * im) * SIN(ATAN(im / re))
    POLZ = Z()
END FUNCTION
'--------------------------------------------------------------------------------
'POWZ() returns the power n  of a complex number = (x+iy)^n = z^n
'--------------------------------------------------------------------------------
FUNCTION POWZ(Z() AS DOUBLE) AS DOUBLE
    re = Z(0)  :  im = Z(1)  :  expo = Z(2)
    Z(0) = (SQR(re * re + im * im)) ^expo * COS(expo * ATAN(im / re))
    Z(1) = (SQR(re * re + im * im)) ^expo * SIN(expo * ATAN(im / re))
    Z(2) = 0
    POWZ = Z()
END FUNCTION
'--------------------------------------------------------------------------------
'RAD2DEG() returns degrees instead of radians
'--------------------------------------------------------------------------------
FUNCTION RAD2DEG(value AS DOUBLE) AS DOUBLE
    RAD2DEG = value / 0.017453
END FUNCTION
'--------------------------------------------------------------------------------
'SEC() returns the secans of x
'--------------------------------------------------------------------------------
FUNCTION SEC(value AS DOUBLE) AS DOUBLE
    SEC = 1 / COS(value)
END FUNCTION
'--------------------------------------------------------------------------------
'SECH() returns the hyperbolic secans of x
'--------------------------------------------------------------------------------
FUNCTION SECH(value AS DOUBLE) AS DOUBLE
    SECH = (2 / (EXP(value) + EXP(value * - 1)))
    'SECH = 1/ COSH (value)
END FUNCTION
'--------------------------------------------------------------------------------
'SINH() returns the hyperbolic sine of x
'--------------------------------------------------------------------------------
FUNCTION SINH(value AS DOUBLE) AS DOUBLE
    SINH = (0.5 * (EXP(value) - EXP(value * - 1)))
    IF value = 0 THEN SINH = 0
END FUNCTION
'--------------------------------------------------------------------------------
'SINZ() sine of a complex number
'--------------------------------------------------------------------------------
FUNCTION SINZ(Z() AS DOUBLE) AS DOUBLE
    re = Z(0)  :  im = Z(1)
    Z(0) = SIN(re) * COSH(im)
    Z(1) = COS(re) * SINH(im)
    SINZ = Z()
END FUNCTION
'--------------------------------------------------------------------------------
'SINHZ() sine of a complex number
'--------------------------------------------------------------------------------
FUNCTION SINHZ(Z() AS DOUBLE) AS DOUBLE
    re = Z(0)  :  im = Z(1)
    Z(0) = SINH(re) * COS(im)
    Z(1) = COSH(re) * SIN(im)
    SINHZ = Z()
END FUNCTION
'--------------------------------------------------------------------------------
'SQRZ() returns the square root of acomplex number
'--------------------------------------------------------------------------------
FUNCTION SQRZ(Z() AS DOUBLE) AS DOUBLE
    re = Z(0)  :  im = Z(1)
    Z(0) = ((re + SQR(re * re + im * im)) * 0.5) ^0.5
    Z(1) = (((re * - 1) + SQR(re * re + im * im)) * 0.5) ^0.5
    SQRZ = Z()
END FUNCTION
'-------------------------------------------------------------------------------
'SUBZ() returns the difference of two complex numbers
'-------------------------------------------------------------------------------
FUNCTION SUBZ(Z() AS DOUBLE) AS DOUBLE
    re1 = Z(0)  :  im1 = Z(1)  :  re2 = Z(2)  :  im2 = Z(3)
    Z(0) = re1 - re2
    Z(1) = im1 - im2
    Z(2) = 0
    Z(3) = 0
    SUBZ = Z()
END FUNCTION
'--------------------------------------------------------------------------------
'TANH() returns the hyperbolic tangent of x
'--------------------------------------------------------------------------------
FUNCTION TANH(value AS DOUBLE) AS DOUBLE
    TANH = SINH(value) / COSH(value)
    IF value = 0 THEN TANH = 0
END FUNCTION
'--------------------------------------------------------------------------------
'TANZ() returns the tangent of a complex number
'--------------------------------------------------------------------------------
FUNCTION TANZ(Z() AS DOUBLE) AS DOUBLE
    re1 = Z(0)  :  im1 = Z(1)
    Z(0) = SIN(2 * re) / (COS(2 * re) + COSH(2 * im))
    Z(1) = SINH(2 * im) / (COS(2 * re) + COSH(2 * im))
    TANZ = Z()
END FUNCTION
'--------------------------------------------------------------------------------
'Exp10() returns the exponential base 10 of x
'--------------------------------------------------------------------------------
FUNCTION Exp10(Value AS DOUBLE) AS DOUBLE

    Exp10 = rqE^(value * LOG(10))

END FUNCTION

'=====================================================================================
'>>>>> reserved words  <<<<<<
'=====================================================================================
'ACOSH, ACOT, ACOSEC, ACOSECH, ADDZ*, ASEC, ASECH, ATANH,CONJZ*, COSEC, COSECH, COSH,
'COSZ*, COSHZ*, COT, COTH, DEG2RAD, DIVZ*,EVEN*,EXPZ*, FAC, GCD*, INVZ*  LOG10,LOG10Z*,
'LOGAZ*, LOGZ*, MAGZ*, MULZ*, NORZ*,ODD*, POLZ*, POWZ*, RAD2DEG, RQE, RQPI, SEC, SECH,
'SINH, SINZ*,SINHZ*, SQRZ*, SUBZ*,TANH, TANZ*
'*: new functions in this version

$TYPECHECK on

