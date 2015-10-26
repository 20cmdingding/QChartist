' Swiss Ephemeris Release 1.60  9-jan-2000
'
' Declarations for Visual Basic 5.0
' The DLL file must exist in the same directory as the VB executable, or in a system
' directory where it can be found at runtime
'
Type orient
    i As Long
    s As String * 16
    End Type
'
' Declarations for Visual Basic 5.0
' The DLL file must exist in the same directory as the VB executable, or in a system
' directory where it can be found at runtime
'

' values for gregflag in swe_julday() and swe_revjul()
 Const SE_JUL_CAL As Integer = 0
 Const SE_GREG_CAL As Integer = 1

' planet and body numbers (parameter ipl) for swe_calc()
 Const SE_SUN As Integer = 0
 Const SE_MOON As Integer = 1
 Const SE_MERCURY As Integer = 2
 Const SE_VENUS As Integer = 3
 Const SE_MARS As Integer = 4
 Const SE_JUPITER As Integer = 5
 Const SE_SATURN As Integer = 6
 Const SE_URANUS As Integer = 7
 Const SE_NEPTUNE As Integer = 8
 Const SE_PLUTO   As Integer = 9
 Const SE_MEAN_NODE As Integer = 10
 Const SE_TRUE_NODE As Integer = 11
 Const SE_MEAN_APOG As Integer = 12
 Const SE_OSCU_APOG As Integer = 13
 Const SE_EARTH     As Integer = 14
 Const SE_CHIRON    As Integer = 15
 Const SE_PHOLUS    As Integer = 16
 Const SE_CERES     As Integer = 17
 Const SE_PALLAS    As Integer = 18
 Const SE_JUNO      As Integer = 19
 Const SE_VESTA     As Integer = 20
  
 Const SE_NPLANETS  As Integer = 21
 Const SE_AST_OFFSET  As Integer = 10000

' Hamburger or Uranian ficticious "planets"
 Const SE_FICT_OFFSET As Integer = 40
 Const SE_FICT_MAX  As Integer = 999 'maximum number for ficticious planets
                                     'if taken from file seorbel.txt
 Const SE_NFICT_ELEM  As Integer = 15 'number of built-in ficticious planets
 Const SE_CUPIDO As Integer = 40
 Const SE_HADES As Integer = 41
 Const SE_ZEUS As Integer = 42
 Const SE_KRONOS As Integer = 43
 Const SE_APOLLON As Integer = 44
 Const SE_ADMETOS As Integer = 45
 Const SE_VULKANUS As Integer = 46
 Const SE_POSEIDON As Integer = 47
' other ficticious bodies
 Const SE_ISIS As Integer = 48
 Const SE_NIBIRU As Integer = 49
 Const SE_HARRINGTON As Integer = 50
 Const SE_NEPTUNE_LEVERRIER As Integer = 51
 Const SE_NEPTUNE_ADAMS As Integer = 52
 Const SE_PLUTO_LOWELL As Integer = 53
 Const SE_PLUTO_PICKERING As Integer = 54

' points returned by swe_houses() and swe_houses_armc()
' in array ascmc(0...10)
 Const SE_ASC       As Integer = 0
 Const SE_MC        As Integer = 1
 Const SE_ARMC      As Integer = 2
 Const SE_VERTEX    As Integer = 3
 Const SE_EQUASC    As Integer = 4  ' "equatorial ascendant"
 Const SE_NASCMC    As Integer = 5  ' number of such points
 
' iflag values for swe_calc()/swe_calc_ut() and swe_fixstar()/swe_fixstar_ut()
Const SEFLG_JPLEPH As Long = 1
Const SEFLG_SWIEPH As Long = 2
Const SEFLG_MOSEPH As Long = 4
Const SEFLG_SPEED As Long = 256
Const SEFLG_HELCTR As Long = 8
Const SEFLG_TRUEPOS As Long = 16
Const SEFLG_J2000 As Long = 32
Const SEFLG_NONUT As Long = 64
Const SEFLG_NOGDEFL As Long = 512
Const SEFLG_NOABERR As Long = 1024
Const SEFLG_EQUATORIAL As Long = 2048
Const SEFLG_XYZ As Long = 4096
Const SEFLG_RADIANS As Long = 8192
Const SEFLG_BARYCTR As Long = 16384
Const SEFLG_TOPOCTR As Long = 32768
Const SEFLG_SIDEREAL As Long = 65536

'eclipse codes
Const SE_ECL_NUT As Long = -1
Const SE_ECL_CENTRAL As Long = 1
Const SE_ECL_NONCENTRAL As Long = 2
Const SE_ECL_TOTAL As Long = 4
Const SE_ECL_ANNULAR As Long = 8
Const SE_ECL_PARTIAL As Long = 16
Const SE_ECL_ANNULAR_TOTAL As Long = 32
Const SE_ECL_PENUMBRAL As Long = 64
Const SE_ECL_VISIBLE As Long = 128
Const SE_ECL_MAX_VISIBLE As Long = 256
Const SE_ECL_1ST_VISIBLE As Long = 512
Const SE_ECL_2ND_VISIBLE As Long = 1024
Const SE_ECL_3RD_VISIBLE As Long = 2048
Const SE_ECL_4TH_VISIBLE As Long = 4096

'sidereal modes, for swe_set_sid_mode()
Const SE_SIDM_FAGAN_BRADLEY    As Long = 0
Const SE_SIDM_LAHIRI           As Long = 1
Const SE_SIDM_DELUCE           As Long = 2
Const SE_SIDM_RAMAN            As Long = 3
Const SE_SIDM_USHASHASHI       As Long = 4
Const SE_SIDM_KRISHNAMURTI     As Long = 5
Const SE_SIDM_DJWHAL_KHUL      As Long = 6
Const SE_SIDM_YUKTESHWAR       As Long = 7
Const SE_SIDM_JN_BHASIN        As Long = 8
Const SE_SIDM_BABYL_KUGLER1    As Long = 9
Const SE_SIDM_BABYL_KUGLER2   As Long = 10
Const SE_SIDM_BABYL_KUGLER3   As Long = 11
Const SE_SIDM_BABYL_HUBER     As Long = 12
Const SE_SIDM_BABYL_ETPSC     As Long = 13
Const SE_SIDM_ALDEBARAN_15TAU As Long = 14
Const SE_SIDM_HIPPARCHOS      As Long = 15
Const SE_SIDM_SASSANIAN       As Long = 16
Const SE_SIDM_GALCENT_0SAG    As Long = 17
Const SE_SIDM_J2000           As Long = 18
Const SE_SIDM_J1900           As Long = 19
Const SE_SIDM_B1950           As Long = 20
Const SE_SIDM_USER            As Long = 255

Const SE_NSIDM_PREDEF         As Long = 21

Const SE_SIDBITS              As Long = 256
'for projection onto ecliptic of t0
Const SE_SIDBIT_ECL_T0        As Long = 256
'for projection onto solar system plane
Const SE_SIDBIT_SSY_PLANE     As Long = 512

' modes for planetary nodes/apsides, swe_nod_aps(), swe_nod_aps_ut()
Const SE_NODBIT_MEAN        As Long = 1
Const SE_NODBIT_OSCU        As Long = 2
Const SE_NODBIT_OSCU_BAR    As Long = 3
Const SE_NODBIT_FOPOINT     As Long = 256

' indices for swe_rise_trans()
Const SE_CALC_RISE      As Long = 1
Const SE_CALC_SET       As Long = 2
Const SE_CALC_MTRANSIT      As Long = 4
Const SE_CALC_ITRANSIT      As Long = 8
Const SE_BIT_DISC_CENTER        As Long = 256 '/* to be added to SE_CALC_RISE/SET */
                    '/* if rise or set of disc center is */
                    '/* requried */
Const SE_BIT_NO_REFRACTION      As Long = 512 '/* to be added to SE_CALC_RISE/SET, */
                    '/* if refraction is not to be considered */

' bits for data conversion with swe_azalt() and swe_azalt_rev()
Const SE_ECL2HOR        As Long = 0
Const SE_EQU2HOR        As Long = 1
Const SE_HOR2ECL        As Long = 0
Const SE_HOR2EQU        As Long = 1

' for swe_refrac()
Const SE_TRUE_TO_APP        As Long = 0
Const SE_APP_TO_TRUE        As Long = 1