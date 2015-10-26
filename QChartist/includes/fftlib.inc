'Fast Fourier Transform routines for power of 2 data sets 
DECLARE SUB fft lib "fftlib" alias "fft@16"(BYREF lpxr AS SINGLE, BYREF lpyi AS SINGLE, BYVAL n AS INTEGER, BYVAL inverse AS INTEGER)
DECLARE SUB FFTMagnitude lib "fftlib" alias "FFTMagnitude@16"(BYREF lpxr AS SINGLE, BYREF lpyi AS SINGLE, BYVAL n AS INTEGER, BYREF lpOut AS SINGLE)
DECLARE SUB FFTPhase lib "fftlib" alias "FFTPhase@16"(BYREF xr AS SINGLE, BYREF yi AS SINGLE, BYVAL n AS INTEGER, BYREF ph AS SINGLE)
DECLARE SUB FFTFrequency lib "fftlib" alias "FFTFrequency@12" (BYREF lpHz AS SINGLE, BYVAL samplefreq AS SINGLE, BYVAL n AS INTEGER)
DECLARE SUB FFT2DCalc  lib "fftlib" alias "FFT2DCalc@20"(BYREF lpxreal AS SINGLE, BYREF lpyImag AS SINGLE, BYVAL c AS INTEGER, BYVAL r AS INTEGER, BYVAL flag AS INTEGER)
DECLARE SUB PowerSpectrumCalc  lib "fftlib" alias "PowerSpectrumCalc@16"(BYREF lpxreal AS SINGLE, BYREF lpyimag AS SINGLE, BYVAL numdat AS INTEGER, BYVAL delta AS SINGLE)

'Discrete Fourier routines for non-power of 2 data sets 
DECLARE SUB DFT lib "fftlib" alias "DFT@16"(BYREF lpReal AS SINGLE, BYREF lpImag AS SINGLE, BYVAL Sample_N AS INTEGER, BYVAL inverse AS INTEGER)
DECLARE SUB DFTMagnitude lib "fftlib" alias "DFTMagnitude@16"(BYREF lpReal AS SINGLE, BYREF lpImag AS SINGLE, BYVAL Sample_N AS INTEGER, BYREF lpAmp AS SINGLE)
DECLARE SUB DFTPhase lib "fftlib" alias "DFTPhase@16"(BYREF lpReal AS SINGLE, BYREF lpImag AS SINGLE, BYVAL Sample_N AS INTEGER, BYREF lpPhase AS SINGLE)

'helper functions 
DECLARE SUB Convolve  lib "fftlib" alias "Convolve@20"(BYREF lpfiltcoef AS SINGLE, BYREF lpIn AS SINGLE, BYREF lpOut AS SINGLE, BYVAL filtLen AS INTEGER, BYVAL aLen AS INTEGER)
DECLARE SUB WindowData  lib "fftlib" alias "WindowData@12"(BYREF lpx AS SINGLE, numdat AS INTEGER, wind AS INTEGER)
DECLARE FUNCTION ExactBlackman   lib "fftlib" alias "ExactBlackman@8"(n AS INTEGER, j AS INTEGER) AS SINGLE
DECLARE FUNCTION Hamming  lib "fftlib" alias "Hamming@8"(n AS INTEGER, j AS INTEGER) AS SINGLE
DECLARE FUNCTION Hanning  lib "fftlib" alias "Hanning@8"(n AS INTEGER, j AS INTEGER) AS SINGLE
DECLARE FUNCTION Parzen  lib "fftlib" alias "Parzen@8"(n AS INTEGER, j AS INTEGER) AS SINGLE
DECLARE FUNCTION SigmaGauss  lib "fftlib" alias "SigmaGauss@8"(n AS INTEGER, j AS INTEGER) AS SINGLE
DECLARE FUNCTION Welch  lib "fftlib" alias "Welch@8"(n AS INTEGER, j AS INTEGER) AS SINGLE
DECLARE FUNCTION CheckPowerOfTwo  lib "fftlib" alias "CheckPowerOfTwo@4"(X As Long) AS INTEGER 
DECLARE FUNCTION SquareAndSum  lib "fftlib" alias "SquareAndSum@8"(BYVAL a AS SINGLE, BYVAL b AS SINGLE) AS SINGLE
DECLARE SUB RealFFT2 (xr() AS SINGLE, sinc() AS SINGLE, n AS INTEGER, inverse AS INTEGER)
DECLARE Sub CalcFrequency  lib "fftlib" alias "CalcFrequency@24"(BYVAL NumberOfSamples As Long, BYVAL FrequencyIndex As Long, BYREF lpRealIn AS SINGLE, BYREF lpImagIn AS SINGLE, BYREF RealOut AS SINGLE, BYREF ImagOut AS SINGLE)