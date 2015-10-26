'****************************************************************************************
'ProbDists.rqb is a collection of functions that calculate the integrals and inverses for
'the commonly used Normal, t, F and Chi-Square probability distributions.
'The algorithms used are from the CACM and are accurate to 6 decimals.
'All algorithms except the t distribution and it's inverse were translated into
'C by Gary Perlman and translated from that C code to BASIC by Michael J. Zito, 2003
'The t Distribution functions were coded by Michael J. Zito, 2003
'
'IMPORTANT: The algorithms in this module are interdependent on each other therefore
'           the ENTIRE FILE MUST BE INCLUDED AS A UNIT
'
'****************************************************************************************


'----- Compiler Directives
$TYPECHECK ON
$IFNDEF True
  $DEFINE True 1
$ENDIF
$IFNDEF False
  $DEFINE False 0
$ENDIF

'----- Stat Distribution Functions
DECLARE FUNCTION zDist (z AS DOUBLE) AS DOUBLE
DECLARE FUNCTION zDistInv (p AS DOUBLE) AS DOUBLE
DECLARE FUNCTION Chi (x2 AS DOUBLE, df AS INTEGER) AS DOUBLE
DECLARE FUNCTION ChiInv (p AS DOUBLE, df AS INTEGER) AS DOUBLE
DECLARE FUNCTION fDist (f AS DOUBLE, df1 AS INTEGER, df2 AS INTEGER) AS DOUBLE
DECLARE FUNCTION fDistInv (p AS DOUBLE, df1 AS INTEGER, df2 AS INTEGER) AS DOUBLE
DECLARE FUNCTION tDist (t AS DOUBLE, df AS DOUBLE, tail AS INTEGER) AS DOUBLE
DECLARE FUNCTION tDistInv (p AS DOUBLE, df AS DOUBLE, tail AS INTEGER) AS DOUBLE

CONST prec = .000001 'algorithms only accurate to 6 decimals

'----------------------------------------------------------------------------------------------------

  FUNCTION zDist (z AS DOUBLE) AS DOUBLE
  'Computes approximations to Normal z distribution probabilities
  'Returns the integral from -oo to z
  'Adapted from a polynomial approximation in:
  '       Ibetson, D Algorithm 209
  '       Collected algorithms of the CACM 1963 p 616
  '       Translated to C by Gary Perlman
  '       Translated C to BASIC by Michael Zito 2003
  'NOTE: Accurate to 6 digits.  For z values > 6 returns 0.0

    DIM w AS DOUBLE
    DIM x AS DOUBLE
    DIM y AS DOUBLE

    IF z = 0 THEN
      x = 0
    ELSE
      y = 0.5 * ABS(z)
        IF y >= 3 THEN
          x = 1.0
        ELSEIF y < 1.0 THEN
          w = y * y
          x = ((((((((0.000124818987 * w - 0.001075204047) * w_
              + 0.005198775019) * w - 0.019198292004) * w_
              + 0.059054035642) * w - 0.151968751364) * w_
              + 0.319152932694) * w - 0.531923007300) * w_
              + 0.797884560593) * y * 2
        ELSE
          y = y - 2
          x = (((((((((((((-0.000045255659 * y_
              + 0.000152529290) * y - 0.000019538132) * y_
              - 0.000676904986) * y + 0.001390604284) * y_
              - 0.000794620820) * y - 0.002034254874) * y_
              + 0.006549791214) * y - 0.010557625006) * y_
              + 0.011630447319) * y - 0.009279453341) * y_
              + 0.005353579108) * y - 0.002141268741) * y_
              + 0.000535310849) * y + 0.999936657524
        END IF
     END IF

    IF z > 0 THEN
      y = (x + 1) * 0.5
    ELSE
      y = (1 - x) * 0.5
    END IF

    zDist = y

  END FUNCTION
'----------------------------------------------------------------------------------------------------

  FUNCTION zDistInv (p AS DOUBLE) AS DOUBLE
  'Computes approximations to Normal z distribution probabilities
  'Returns the z value for a given probability
  'Adapted from a polynomial approximation in:
  '       Ibetson, D Algorithm 209
  '       Collected algorithms of the CACM 1963 p 616
  '       Translated to C by Gary Perlman
  '       Translated C to BASIC by Michael Zito 2003
  'NOTE: Accurate to 6 digits.  For z values > 6 returns 0.0

    DIM Minz AS DOUBLE
    DIM Maxz AS DOUBLE
    DIM zVal AS DOUBLE
    DIM pVal AS DOUBLE

    Minz = -6.0
    Maxz = 6.0
    zVal = 0.0

    IF p <= 0 OR p >= 1.0 THEN zVal = 0 : EXIT FUNCTION

    WHILE Maxz - Minz > Prec
      pVal = zDist(zVal)
      IF pVal > p THEN
        Maxz = zVal
      ELSE
        Minz = zVal
      END IF
      zVal = (Maxz + Minz) * 0.5
    WEND

    zDistInv = zVal

  END FUNCTION
'----------------------------------------------------------------------------------------------------

  FUNCTION Chi (x2 AS DOUBLE, df AS INTEGER) AS DOUBLE
  'Computes approximations to Chi Square distribution probabilities
  'Returns the tail probability for a given Chi Square Value
  'Adapted from:
  '       Hill, I.D. and Pike, M.C. Algorithm 299
  '       Collected algorithms of the CACM
  '       Translated to C by Gary Perlman
  '       Translated C to BASIC by Michael Zito 2003

    DIM a AS DOUBLE
    DIM y AS DOUBLE
    DIM s AS DOUBLE
    DIM e AS DOUBLE
    DIM c AS DOUBLE
    DIM z AS DOUBLE
    DIM r AS DOUBLE
    DIM even AS INTEGER
    DIM BigX AS DOUBLE
    DIM LogSqrtPi AS DOUBLE
    DIM ISqrtPi AS DOUBLE

    BigX = 20.0
    LogSqrtPi = 0.5723649429247000870717135
    ISqrtPi = 0.5641895835477562869480795

    IF x2 <= 0 OR df < 1 THEN Chi = 1.0 : EXIT FUNCTION

    a = 0.5 * x2
    IF (2 * (df\2)) = df THEN even = True ELSE even = False
    IF df > 1 THEN
      IF -a < -BigX THEN y = 0 ELSE y = EXP(-a)
    END IF
    IF even = True THEN
      s = y
    ELSE
      s = 2.0 * zDist(-SQR(x2))
    END IF
    IF df > 2 THEN
      x2 = 0.5 * (df - 1.0)
      IF even = True THEN z = 1.0 ELSE z = 0.5
      IF a > BigX THEN
        IF even = True THEN e = 0 ELSE e = LogSqrtPi
        c = LOG(a)
        WHILE z <= x2
          e = log(z) + e
          r = c*z-a-e
          IF r < -BigX THEN r = 0 ELSE r = EXP(r)
          s = s + r
          z = z + 1.0
        WEND
        Chi = s
      ELSE
        IF even = True THEN e = 1.0 ELSE e = ISqrtPi/SQR(a)
        c = 0.0
        WHILE z <= x2
          e = e * (a / z)
          c = c + e
          z = z + 1.0
        WEND
        Chi = (c * y + s)
      END IF
    ELSE
      Chi = s
    END IF
  END FUNCTION
'----------------------------------------------------------------------------------------------------

  FUNCTION ChiInv (p AS DOUBLE, df AS INTEGER) AS DOUBLE
  'Computes approximations to Chi Square distribution probabilities
  'Returns the Critical Chi Square value for a given tail probability
  'Adapted from:
  '       Hill, I.D. and Pike, M.C. Algorithm 299
  '       Collected algorithms of the CACM
  '       Translated to C by Gary Perlman
  '       Translated C to BASIC by Michael Zito 2003

    DIM MinChi AS DOUBLE
    DIM MaxChi AS DOUBLE
    DIM ChiVal AS DOUBLE

    MinChi = 0.0
    MaxChi = 99999.0

    IF p <= 0.0 THEN ChiInv = MaxChi : EXIT FUNCTION
    IF p >= 1.0 THEN ChiInv = 0.0 : EXIT FUNCTION

    ChiVal = df / SQR(p)
    WHILE MaxChi - MinChi > Prec
      IF Chi(ChiVal, df) < p THEN
        MaxChi = ChiVal
      ELSE
        MinChi = ChiVal
      END IF
      ChiVal = (MaxChi + MinChi) * 0.5
    WEND
    ChiInv = ChiVal

  END FUNCTION

'----------------------------------------------------------------------------------------------------

  FUNCTION fDist (f AS DOUBLE, df1 AS INTEGER, df2 AS INTEGER) AS DOUBLE
  'Computes approximations to F distribution probabilities
  'Returns the tail probability for a given F Value
  'df1 = numerator df, df2 = denominator df
  'Adapted from:
  '       Dorrer, Egon Algorithm 322
  '       Collected algorithms of the CACM
  '       Translated to C by Gary Perlman
  '       Translated C to BASIC by Michael Zito 2003
  
    DIM i AS INTEGER
    DIM j AS INTEGER
    DIM a AS INTEGER
    DIM b AS INTEGER
    DIM w AS DOUBLE
    DIM y AS DOUBLE
    DIM z AS DOUBLE
    DIM d AS DOUBLE
    DIM p AS DOUBLE
    DIM IPi AS DOUBLE

    IPi = 0.3183098861837906715377675

    IF F < prec OR df1 < 1 OR df2 < 1 THEN fDist = 1.0 : EXIT FUNCTION
    IF df1 MOD 2 <> 0 THEN a = 1 ELSE a = 2
    IF df2 MOD 2 <> 0 THEN b = 1 ELSE b = 2

    w = (f * df1) / df2
    z = 1.0 / (1.0 + w)
    IF a = 1 THEN
      IF b = 1 THEN
        p = SQR(w)
        y = IPi
        d = y * z / p
        p = 2.0 * y * ATAN(p)
      ELSE
        p = SQR(w * z)
        d = 0.5 * p * z / w
      END IF
    ELSEIF b = 1 THEN
      p = SQR(z)
      d = 0.5 * z * p
      p = 1.0 - p
    ELSE
      d = z * z
      p = w * z
    END IF
    y = 2.0 * w / z
    FOR j = (b + 2) TO df2 STEP 2
      d = d * (1.0 + a / (j - 2.0)) * z
      IF a = 1 THEN
        p = p + d * y / (j - 1.0)
      ELSE
        p = (p + w) * z
      END IF
    NEXT
    y = w * z
    z = 2.0 / z
    b = df2 - 2
    FOR i = (a + 2) TO df1 STEP 2
      j = i + b
      d = d * y * j / (i - 2)
      p = p - z * d / j
    NEXT
    IF p < 0 THEN p = 0
    IF p > 1.0 THEN p = 1.0

    fDist = (1.0 - p)

  END FUNCTION
'----------------------------------------------------------------------------------------------------

  FUNCTION fDistInv (p AS DOUBLE, df1 AS INTEGER, df2 AS INTEGER) AS DOUBLE
  'Computes approximations to F distribution probabilities
  'Returns the critical F value for a given probability
  'df1 = numerator df, df2 = denominator df
  'Adapted from:
  '       Dorrer, Egon Algorithm 322
  '       Collected algorithms of the CACM
  '       Translated to C by Gary Perlman
  '       Translated C to BASIC by Michael Zito 2003

    DIM fVal AS DOUBLE
    DIM MaxF AS DOUBLE
    DIM MinF AS DOUBLE

    MaxF = 9999.0
    MinF = 0.0

    IF p <= 0 OR p >= 1.0 THEN fDistInv = 0.0 : EXIT FUNCTION

    fVal = 1.0 / p

    WHILE ABS(MaxF - MinF) > prec
      IF fDist(fVal, df1, df2) < p THEN
        MaxF = fVal
      ELSE
        MinF = fVal
      END IF
      fVal = (MaxF + MinF) * 0.5
    WEND

    fDistInv = fVal
  
  END FUNCTION
'----------------------------------------------------------------------------------------------------

  FUNCTION tDist (t AS DOUBLE, df AS DOUBLE, tail AS INTEGER) AS DOUBLE
  'Uses the fDist functions and the relationship t(n)^2 = F(1,n) to
  'compute approximations of tail probabilities for the Student's t Distribution
  'Tail is a flag:
  '     Tail = 1 computes one tail probabilities
  '     Tail = 2 computes two tail probabilities
  '     Coded by Michael Zito 2003

    DIM p AS DOUBLE

    p = fDist(t * t, 1, df)

    IF tail = 1 THEN tDist = p / 2 ELSE tDist = p

  END FUNCTION
'----------------------------------------------------------------------------------------------------

  FUNCTION tDistInv (p AS DOUBLE, df AS DOUBLE, tail AS INTEGER) AS DOUBLE
  'Uses the fDist functions and the relationship t(n)^2 = F(1,n) to
  'compute critical  t values for a given probability
  'Tail is a flag:
  '     Tail = 1 computes one tail probabilities
  '     Tail = 2 computes two tail probabilities
  '     Coded by Michael Zito 2003

    DIM t AS DOUBLE

    IF tail = 1 THEN p = p * 2

    t = fDistInv(p, 1, df)

    IF t = 0 THEN tDistInv = 0 ELSE tDistInv = SQR(t)


  END FUNCTION
'----------------------------------------------------------------------------------------------------
