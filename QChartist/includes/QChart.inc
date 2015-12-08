'******************************************************************************************
'======================= QChart:  A Charting Object for Rapid-Q ===========================
'====================== Copyright (c) 2003-2004  Michael J. Zito ==========================
'QChart provides a set of 2-D charting routines for Rapid-Q programmers.
'It generates histograms, bar charts, XY-scatter graphs, line graphs
'and box plots.  Each charting routine will calculate an appropriate scale
'and plot the data contained in the .Data component of the object.  The user may optionally
'specify the scaling as well as fonts, grids or other properties (see code)
'Once the data is formatted graphs can be called with very few lines of simple code:
'.Initialize
'.ChartType = ctXXXX
'.ChartStyle = csXXXX
'------->Change Desired Options Here
'------->Dimension .Data Grid Here
'------->Load Data Into .Data Grid Here
'.DrawChart (Overlay T or F)
'SEE QChartEx.rqb for examples of setting up and calling each chart type.
'
'NOTE: There is little error checking in this object.  It is up to the user
'to insure that the data is formatted properly before calling each routine.
'The .Data component is a non-visible QStringGrid which offers the user the
'ability to set the row and column count prior to filling the grid with data.
'The expected data formats for each chart type are listed below:
'
'Bar and Line Charts:  Data groups are in columns, data values are in each row
'Set .Data.ColCount to the number of groups
'Set .Data.RowCount to the number of data points in the largest group
'Row 0 is for legend text
'Col 0 is for X Axis Labels
'
'0   1   2  .   .   .   n
'0  Min <<======Legend======>>
'1   X   A1  B1 .   .   .   n1
'2   =   A2  B2 .   .   .   n2
'.   L   .   .  .   .   .   .
'.   b   .   .  .   .   .   .
'.   l   .   .  .   .   .   .
'n   s   An  Bn .   .   .   nn
'
'XY Scatter Charts:    Data pairs are in adjacent columns: Col1 = X val, Col2 = Y val
'Data values are in each row
'Set .Data.ColCount to the number of XY pairs * 2
'Set .Data.RowCount to the number of data points in the largest group
'Row 0 of the Y Col is for group labels / legend text
'Col 0 and Row 0 of the X Col are not used (*)
'Data for each pair should be in ascending order on the X value
'
'Pair 1      Pair 2        Pair n
'=======     =======       ======
'0    1     2     3     4  . . . m   n
'0   *    *    Lgd    *    Lgd       *  Lgd
'1   *   x11   y11   x21   y21 . . .xm1 yn1
'2   *   x12   y12   x22   y22 . . .xm2 yn2
'.   *    .     .     .     .  . . . .   .
'.   *    .     .     .     .  . . . .   .
'.   *    .     .     .     .  . . . .   .
'n   *   x1n   y1n   x2n   y2n . . .xmn ynn
'
'Box Plots:            Data groups are in columns, data values are in each row
'Set .Data.ColCount to the number of groups
'Set .Data.RowCount to 5
'Data must be set up with the highest value in row 1
'the lowest value in row 5 and intermediate values in
'descending order from row 1 to row 5.
'Row 0 is for legend text
'Col 0 is not used (*)
'
'Box Plots
'0   1   2  3   .   .   n
'0   *   <<=====Legend======>>
'1   *   Max
'2   *   3rd Quartile
'3   *   2nd Quartile (Median)
'4   *   1st Quartile
'5   *   Min
'
'Pie Charts            Data groups are in columns, data values are in Row 1
'Set .Data.ColCount to the number of groups
'Set .Data.RowCount to 1
'Row 0 is for legend text
'Col 0 is not used (*)
'
'Pie Charts
'0   1    2   3   .   .   n
'0   *   <<======Legend=======>>
'1   *   x1  x2  x3   .   .   xn
'
'******************************************************************************************

'----- Compiler Directives
$IFNDEF TRUE
    $DEFINE TRUE 1
$ENDIF
$IFNDEF FALSE
    $DEFINE FALSE 0
$ENDIF

'----- Win API Functions

'DECLARE FUNCTION CreatePen LIB "gdi32" ALIAS "CreatePen" (nPenStyle AS LONG, nWidth AS LONG, crColor AS LONG)_
'AS LONG
'DECLARE FUNCTION CreateSolidBrush LIB "gdi32" ALIAS "CreateSolidBrush" (ByVal crColor AS LONG) AS LONG
'DECLARE FUNCTION CreateHatchBrush LIB "gdi32" ALIAS "CreateHatchBrush" (nIndex AS LONG, crColor AS LONG) AS LONG
'DECLARE FUNCTION SelectObject LIB "gdi32" ALIAS "SelectObject" (hdc AS LONG,hObject AS LONG) AS LONG
'DECLARE FUNCTION DeleteObject LIB "gdi32" ALIAS "DeleteObject" (hObject AS LONG) AS LONG
'DECLARE FUNCTION SetBkColor LIB "gdi32" ALIAS "SetBkColor" (hdc AS LONG, crColor AS LONG) AS LONG
'DECLARE FUNCTION MoveToEx LIB "gdi32" ALIAS "MoveToEx" (hdc AS LONG,x AS LONG,y AS LONG, lpPoint AS LONG) AS LONG
'DECLARE FUNCTION LineTo LIB "gdi32" ALIAS "LineTo" (hdc AS LONG,x AS LONG,y AS LONG) AS LONG
'DECLARE FUNCTION Rectangle LIB "gdi32" ALIAS "Rectangle" (hdc AS LONG, X1 AS LONG, Y1 AS LONG, X2 AS LONG,_
'Y2 AS LONG) AS LONG
'DECLARE FUNCTION Pie LIB "gdi32" ALIAS "Pie" (ByVal hdc AS LONG, ByVal X1 AS LONG, ByVal Y1 AS LONG,_
'ByVal X2 AS LONG, ByVal Y2 AS LONG, ByVal X3 AS LONG,_
'ByVal Y3 AS LONG, ByVal X4 AS LONG, ByVal Y4 AS LONG)_
'AS LONG

'----- PRIVATE QChart FUNCTIONs
'DECLARE FUNCTION Log10 (Value AS SINGLE) AS SINGLE
DECLARE FUNCTION RowTotal(Row AS INTEGER) AS SINGLE

'----- PRIVATE QChart SUBs
DECLARE SUB ClearBuffer
DECLARE SUB SetSize
DECLARE SUB ScaleAxis(Mn AS DOUBLE , Mx AS DOUBLE , Axis AS INTEGER)
DECLARE SUB SetScale
DECLARE SUB SetSeries
DECLARE SUB DrawAxes
DECLARE SUB DrawTitles
DECLARE SUB DrawLabels
DECLARE SUB DrawMarker(x1 AS SINGLE , y1 AS SINGLE , MrkrStyle AS INTEGER , Color AS LONG)
DECLARE SUB DrawLegend
DECLARE SUB DrawBar(Overlay AS INTEGER)
DECLARE SUB DrawXY(Overlay AS INTEGER)
DECLARE SUB DrawLine(Overlay AS INTEGER)
DECLARE SUB DrawBox(Overlay AS INTEGER)
DECLARE SUB DrawPie(Overlay AS INTEGER)
DECLARE SUB drawp(TYPE AS INTEGER , xb AS INTEGER , yb AS INTEGER , xc AS INTEGER , yc AS INTEGER , xd AS INTEGER , yd AS INTEGER)
DECLARE SUB drawtrendline(xb AS SINGLE , yb AS SINGLE , xc AS SINGLE , yc AS SINGLE)
DECLARE SUB drawfibofan(xb AS SINGLE , yb AS SINGLE , xc AS SINGLE , yc AS SINGLE)
DEFSNG rad = 3.1415927 / 180  'to convert to radians

'----- PUBLIC QChart Methods
DECLARE SUB Initialize
DECLARE SUB PaintChart
DECLARE SUB ClearAll
DECLARE SUB DrawChart(Overlay AS INTEGER)
DECLARE SUB RedrawChart
DECLARE SUB SaveChart(FileNam AS STRING)
DECLARE SUB PrintChart(Prn AS INTEGER , Orient AS INTEGER , Margin AS INTEGER , _
    Copies AS INTEGER , Colr AS BYTE)
DECLARE SUB savebuffertmp
DECLARE SUB restorebuffertmpz
DECLARE SUB restorebuffertmp
DECLARE SUB savebuffertmpsimple
DECLARE SUB savebuffertmpsimplez
DECLARE SUB bufcntreset
DECLARE SUB firstbufcntreset

'----- PUBLIC variables
DIM spaceforwards AS INTEGER
spaceforwards = 0
DIM bufcnt AS INTEGER
bufcnt = 0
DIM firstbufcnt AS INTEGER
firstbufcnt = 0
DIM logamplitude AS DOUBLE
logamplitude = 5

'----- UDTs
TYPE AxisType
    LEN   AS SINGLE  'Axis length in pixels
    Ori   AS SINGLE  'Logical Origin in pixels
    Min   AS DOUBLE  'Minimum scale value
    Max   AS DOUBLE  'Maximum scale value
    Div   AS INTEGER  'Number of divisions on axis
    ScaleFactor AS SINGLE  'Factor for scaling values on axis
    AutoScale  AS INTEGER  'TRUE = QChart scales, FALSE = User supplies Min/Max
    Color   AS LONG  'Color of axis
    Grid   AS INTEGER  'TRUE = Draw Grid, FALSE = No Grid
    Labeled  AS INTEGER  'TRUE = Label the Axis, FALSE = No Axis Labels
    Zero   AS SINGLE  'Location of zero in Pixels
    DrawZero  AS INTEGER  'TRUE = Draw Zero Line, FALSE = No Zero Line
    ZeroColor  AS LONG  'Color of Zero Line
    Tics   AS INTEGER  'TRUE = Draw Tic Marks, FALSE = No Tic Marks
    MnrTics  AS INTEGER  'TRUE = Draw Minor Tic Marks, FALSE = No Tic Marks
    STEP   AS SINGLE  'Step increment value of each tic
    TicIntvl  AS SINGLE  'Distance between tics in world coordinates
    TicLen  AS SINGLE  'Size of tic mark in Pixels
    LogScale  AS INTEGER  'TRUE = Log Scalin, FALSE = Linear Scaling
END TYPE

TYPE TitleType
    Top   AS INTEGER
    Left   AS INTEGER
    Text   AS STRING * 70
END TYPE

TYPE SeriesType
    AutoColor  AS INTEGER  'Cycle available colors (T/F)
    Color   AS LONG  'Color to use
    AutoMark  AS INTEGER  'Cycle available markers (T/F)
    Marker  AS INTEGER  'Marker style to use
    HatchStyle AS LONG  'Hatch Pattern to Use for Bars and Boxes
    LineStyle  AS LONG  'Line Style to use
    LineWidth  AS LONG  'Line Width to use
END TYPE

'---- For logspiral
TYPE pointstype
    r AS DOUBLE
    x AS DOUBLE
    y AS DOUBLE
END TYPE

DIM points(0 TO 500) AS pointstype
'----

'----- Win API Constants
CONST lsSolid = 0  'line styles
CONST lsDash = 1
CONST lsDot = 2
CONST lsDashDot = 3
CONST lsDashDotDot = 4
'hatch styles
CONST hsHoriz = 0  '-----
CONST hsVert = 1  '|||||
CONST hsFDiag = 2  '\\\\\
CONST hsBDiag = 3  '/////
CONST hsCross = 4  '+++++
CONST hsXDiag = 5  'xxxxx
CONST hsSolid = - 1

'----- QChart Constants
CONST ctBar = 0  'Chart Type Flags
CONST ctLine = 1
CONST ctXY = 2
CONST ctBox = 3
CONST ctPie = 4

CONST csHisto = 0  'Bar Chart Style Flags
CONST csBar = 1
CONST csStacked = 2
CONST csPctStacked = 3

CONST csPoints = 4  'XY and Line Chart Style Flags
CONST csLines = 5
CONST csBoth = 6

CONST csWhisker = 7  'Box Plot Style Flags
CONST csHiLo = 8

CONST csPiePct = 9  'Pie Chart Style Flags
CONST csPieVal = 10

CONST msFillCircle = 1  'Marker Style Flags
CONST msFillSquare = 2
CONST msFillTriangleUp = 3
CONST msFillTriangleDown = 4
CONST msCircle = 5
CONST msSquare = 6
CONST msTriangleUp = 7
CONST msTriangleDown = 8

CONST MaxSeries = 1000  'Maximum Number of Series that can be plotted

'----- Begin Object Definition ***********************************************************

TYPE QChart EXTENDS QCANVAS

    '---- Properties
    PRIVATE :
    ChartExists   AS BYTE  'TRUE or FALSE
    Missing    AS STRING  'Value used to test for missing data
    Success    AS BYTE  'TRUE or FALSE; set in log routines
    Printing   AS BYTE  'TRUE or FALSE; Update w/o screen redraw
    hPen    AS LONG  'Handle to current pen
    OldPen    AS LONG  'Handle to last used pen
    hBrush    AS LONG  'Handle to current brush
    OldBrush   AS LONG  'Handle to last used brush
    Buffer    AS QBITMAP  'Hidden drawing buffer
    Buffertmp    AS QBITMAP  'Hidden drawing buffer
    buffertmpz AS QBITMAP
    buffertmpz2 AS QBITMAP
    firstbuffertmpz AS QBITMAP

    PUBLIC :
    DATA    AS QSTRINGGRID  'Data to be plotted (See header notes for formats)
    DATA_INDI   AS QSTRINGGRID  'Data to be plotted (See header notes for formats)    
    XAxis    AS AxisType  'X-axis options
    YAxis    AS AxisType  'Y-axis options
    bgColor    AS LONG  'background color
    fgColor    AS LONG  'foreground color
    ChartType   AS BYTE  'ctBar, ctXY, ctBox etc...
    ChartStyle   AS BYTE  'csHisto, csLines, csPoints, csBoth etc...
    MainTitle   AS TitleType  'MainTitle Text and Location
    arialfont as qfont
    MainFont   AS QFONT
    demofont AS QFONT
    demofont2 AS QFONT
    SubTitle   AS TitleType  'SubTitle Text and Location
    SubFont    AS QFONT
    XTitle    AS TitleType  'X Axis Title Text and Location
    YTitle    AS TitleType  'Y Axis Title Text and Location
    AxisLbl    AS TitleType  'Axis Label Text and Location
    AxisFont   AS QFONT
    DoLegend   AS BYTE  'TRUE = Draw Legend, FALSE = No Legend
    Legend    AS TitleType  'Legend Text and Location
    LegendFont   AS QFONT
    ChartBorder   AS BYTE  'TRUE = Draw Frame around entire chart, FALSE = No Frame
    AxisBorder   AS BYTE  'TRUE = Draw Frame around Plot Area, FALSE = No Frame
    Colors(24)  AS LONG  'Array of colors; QChart chooses colors from this array
    PlotAreaColor  AS LONG  'Color of plot area background
    GridColor   AS LONG  'Color of grid lines
    dlgSave    AS QSAVEDIALOG
    MarkerSize   AS SINGLE  'Sets size of drawn markers
    BW     AS BYTE  'TRUE = Use BW only, FALSE = Cycles Colors() array
    GreyScale   AS BYTE  'TRUE = Use GreyScale, FALSE = Cycles Colors() array
    Series(MaxSeries) AS SeriesType  'Series style info

    CONSTRUCTOR

        Parent =   QFORM
        Missing =   ""

        '--- Expand and/or Redefine any way you like
        Colors(0) = RGB(0 , 0 , 0) '-- Black
        Colors(1) = RGB(0 , 0 , 160) '-- Blue
        Colors(2) = RGB(160 , 0 , 0) '-- Red
        Colors(3) = RGB(0 , 160 , 0) '-- Green
        Colors(4) = RGB(0 , 160 , 160) '-- Cyan
        Colors(5) = RGB(160 , 0 , 160) '-- Magenta
        Colors(6) = RGB(192 , 192 , 0) '-- Yellow
        Colors(7) = RGB(0 , 0 , 255) '-- Light Blue
        Colors(8) = RGB(255 , 0 , 0) '-- Light Red
        Colors(9) = RGB(0 , 255 , 0) '-- Light Green
        Colors(10) = RGB(0 , 255 , 255) '-- Light Cyan
        Colors(11) = RGB(255 , 0 , 255) '-- Light Magenta
        Colors(12) = RGB(255 , 255 , 0) '-- Light Yellow
        Colors(13) = RGB(128 , 128 , 255) '-- Torquoise
        Colors(14) = RGB(240 , 128 , 128) '-- Rose Red
        Colors(15) = RGB(192 , 220 , 192) '-- Money Green
        Colors(16) = RGB(166 , 202 , 240) '-- Sky Blue
        Colors(17) = RGB(199 , 177 , 255) '-- Lavender
        Colors(18) = RGB(255 , 226 , 177) '-- Peach
        Colors(19) = RGB(255 , 153 , 51) '-- Orange
        Colors(20) = RGB(255 , 51 , 153) '-- Pink
        Colors(21) = RGB(80 , 80 , 80) '-- Dark Grey
        Colors(22) = RGB(128 , 128 , 128) '-- Med Grey
        Colors(23) = RGB(208 , 208 , 208) '-- Light Grey
        Colors(24) = RGB(255 , 255 , 255) '-- Bright White

    END CONSTRUCTOR

    '------------------------------------------------------------------------------------------
    '------------------------- Private Functions ----------------------------------------------
    '------------------------------------------------------------------------------------------
    PRIVATE :
    FUNCTION RowTotal(Row AS INTEGER) AS SINGLE

        DIM i AS INTEGER
        DIM Sum AS SINGLE

        WITH QChart
            Sum = 0
            FOR i = 1 TO .DATA.ColCount
                IF .DATA.Cell(i , Row) <> .Missing THEN
                    Sum = Sum + ABS(VAL(.DATA.Cell(i , Row)))
                END IF
            NEXT
        END WITH
        RowTotal = Sum

    END FUNCTION
    '------------------------------------------------------------------------------------------
    PRIVATE :
    FUNCTION Log10(Value AS SINGLE) AS SINGLE

        IF Value > 0 THEN
            Log10 = LOG(Value) / LOG(10)
        ELSE
            Log10 = 0
            'MESSAGEDLG("Log10: Log of Value <= 0 Undefined", 1, 4, 0)
            'QChart.Success = FALSE
            'EXIT FUNCTION
        END IF

    END FUNCTION
    '------------------------------------------------------------------------------------------
    PRIVATE :
    SUB ClearBuffer  'Erase off screen drawing buffer

        WITH QChart.Buffer
            .FillRect(0 , 0 , .Width , .Height , QChart.bgColor)
        END WITH
        QChart.ChartExists = FALSE  'Set flag

    END SUB
    '------------------------------------------------------------------------------------------

    private :
    SUB restorebuffertmp
        WITH QChart
            .buffer.BMP = .buffertmp.BMP
        END WITH
    END SUB

    '------------------------- Public Methods -------------------------------------------------
    '------------------------------------------------------------------------------------------
    PUBLIC :
    SUB Initialize  'Sets default values, make global changes here

        DIM i AS INTEGER  'Loop Counters
        DIM j AS INTEGER


        WITH QChart

            .Buffer.Width = .Width
            .Buffer.Height = .Height

            .bgColor =  .Colors(24) 'Bright White
            .fgColor =  .Colors(0) 'Black
            .PlotAreaColor = plotareacolor  '.Colors(23)   'Light Grey
            .GridColor = .Colors(21) 'Dark Grey


            .ChartExists =  FALSE
            .Success =   TRUE
            .ChartBorder =  TRUE
            .AxisBorder =  TRUE
            .MarkerSize =  3
            .BW =    FALSE
            .GreyScale =  FALSE
            .DoLegend =   TRUE
            .Printing =   FALSE

            .XAxis.Div =  10
            .XAxis.AutoScale = TRUE
            .XAxis.Labeled = TRUE
            .XAxis.Tics =  TRUE
            .XAxis.MnrTics = TRUE
            .XAxis.Grid =  TRUE
            .XAxis.DrawZero = TRUE
            .XAxis.LogScale = FALSE
            .XAxis.Color =  0
            .XAxis.ZeroColor = QChart.Colors(8) 'Red

            .YAxis.Div =  10
            .YAxis.AutoScale = TRUE
            .YAxis.Labeled = TRUE
            .YAxis.Tics =  TRUE
            .YAxis.MnrTics = TRUE
            .YAxis.Grid =  TRUE
            .YAxis.DrawZero = TRUE
            .YAxis.LogScale = FALSE
            .YAxis.Color =  0
            .YAxis.ZeroColor = QChart.Colors(8) 'Red

            .MainFont.Name = "Times New Roman"
            .MainFont.Size = 18
            .MainFont.Color = QChart.Colors(0)
            .MainFont.AddStyles(0) 'Bold

            .demofont.Name = "Arial"
            .demofont.Size = 36
            .demofont.Color = QChart.Colors(0)
            .demofont.AddStyles(0) 'Bold

            .demofont2.Name = "Arial"
            .demofont2.Size = 10
            .demofont2.Color = QChart.Colors(0)
            .demofont2.AddStyles(0) 'Bold
            
            .arialfont.Name = "Arial"
            .arialfont.Size = 9
            .arialfont.Color = QChart.Colors(0)

            .SubFont.Name =  "Times New Roman"
            .SubFont.Size =  12
            .SubFont.Color = QChart.Colors(0)
            .SubFont.AddStyles(0) 'Bold

            .AxisFont.Name = "Times New Roman"
            .AxisFont.Size = 8
            .AxisFont.Color = QChart.Colors(0)

            .LegendFont.Name = "Times New Roman"
            .LegendFont.Size = 9
            .LegendFont.Color = QChart.Colors(0)

            FOR i = 1 TO MaxSeries  'Set Series Defaults
                .Series(i).AutoColor = TRUE
                .Series(i).Color = .fgColor
                .Series(i).AutoMark = TRUE
                .Series(i).Marker =  msFillCircle
                .Series(i).HatchStyle = hsSolid
                .Series(i).LineStyle = lsSolid
                .Series(i).LineWidth = 1
                'doevents
            NEXT

            FOR i = 0 TO .DATA.ColCount  'Clear any residual data from last call
                FOR j = 0 TO .DATA.RowCount
                    .DATA.Cell(i , j) = ""
                    'doevents
                NEXT
                'doevents
            NEXT

            .MainTitle.Text = ""
            .SubTitle.Text = ""
            .XTitle.Text =  ""
            .YTitle.Text =  ""

            .DATA.ColCount = 1  'Set .Data to minimum size
            .DATA.RowCount = 1

            .ChartType = ctXY  'Set default chart type and style
            .ChartStyle = csPoints

        END WITH

    END SUB
    '------------------------------------------------------------------------------------------
    PUBLIC :
    SUB PaintChart  'Assign this to the QChart.OnPaint Event
        'Draws Buffer.BMP to Canvas
        WITH QChart
            .Draw(0 , 0 , .Buffertmp.BMP)
        END WITH

    END SUB
    '------------------------------------------------------------------------------------------
    PUBLIC :
    SUB ClearAll

        WITH QChart
            .Initialize
            .ClearBuffer
            .PaintChart
        END WITH

    END SUB
    '------------------------------------------------------------------------------------------
    '------------------------- Private Methods ------------------------------------------------
    '------------------------------------------------------------------------------------------
    PRIVATE :
    SUB SetSize

        DIM i AS INTEGER
        DIM LegendLen AS INTEGER

        WITH QChart  'Set Origin and Axis Lengths
            'relative to window and font sizes
            .Buffer.Font = .AxisFont
            .XAxis.Ori = .Buffer.TextWidth("8") * 16
            IF .ChartType = ctPie THEN  'Leave room for right wedge labels
                .Xaxis.Ori = .XAxis.Ori / 2
            END IF
            IF .DoLegend = FALSE THEN  'Make X Axis larger
                .XAxis.LEN = .Buffer.Width - .XAxis.Ori * 1.5 - spaceforwards
            ELSE  'Leave room for Legend
                .Buffer.Font = .LegendFont
                LegendLen = 0
                FOR i = 1 TO .DATA.ColCount  'Get the longest legend text
                    IF .Buffer.TextWidth(.DATA.Cell(i , 0)) > LegendLen THEN
                        LegendLen = .Buffer.TextWidth(.DATA.Cell(i , 0))
                    END IF
                NEXT i
                LegendLen = LegendLen + .Buffer.TextWidth("WWWWI") 'Pad for marker space
                .XAxis.LEN = .Buffer.Width - (.XAxis.Ori + LegendLen)
            END IF
            .Buffer.Font = .AxisFont
            .YAxis.Ori = .Buffer.Height - .Buffer.TextHeight(.XTitle.Text) * 5
            IF .ChartType = ctPie THEN
                .YAxis.Ori = .Buffer.Height - .Buffer.TextHeight(.XTitle.Text) * 3
            END IF
            .Buffer.Font = .MainFont
            .YAXis.LEN = (.YAxis.Ori - .Buffer.TextHeight(.MainTitle.Text) * 2) - 10

        END WITH

    END SUB
    '------------------------------------------------------------------------------------------
    PRIVATE :
    SUB ScaleAxis(Mn AS DOUBLE , Mx AS DOUBLE , Axis AS INTEGER)

        DIM prec AS DOUBLE
        DIM Incr AS DOUBLE
        DIM Div AS INTEGER
        DIM Range AS DOUBLE
        DIM i AS INTEGER
        DIM j AS DOUBLE
        DIM Test AS DOUBLE
        DIM pwr AS INTEGER
        DIM LMn1 AS DOUBLE
        DIM LMn2 AS DOUBLE
        DIM LMx1 AS DOUBLE
        DIM LMx2 AS DOUBLE
        DIM SclMn AS SINGLE
        DIM SclMx AS SINGLE

        WITH QChart

            IF Axis = 0 THEN Div = .XAxis.Div ELSE Div = .YAxis.Div  'Set values for desired axis

            IF Mx <= Mn THEN Mx = Mn + 1
            Range = Mx - Mn
            IF Mn >= 0 THEN
                Mn = 0
            ELSE
                Mn = Mn - Range * .01  'Prevent plotting points on chart border
            END IF
            IF Mx <= 0 THEN
                Mx = 0
            ELSE
                Mx = Mx + Range * .01  'Prevent plotting points on chart border
            END IF

            prec = .00002
            Range = (Mx - Mn) / Div
            pwr = FIX(.Log10(Range))
            IF Range < 1 THEN pwr = pwr - 1

            Incr = Range / (10^pwr) 'Calculate an even increment
            FOR j = 1 TO 5
                IF Incr < j + prec THEN EXIT FOR
            NEXT j

            FOR i = j TO 20  '10?
                Test = i * 10^pwr

                LMn1 = Mn / Test
                LMn2 = FIX(LMn1)
                IF LMn1 < 0 THEN LMn2 = LMn2 - 1
                IF ABS(LMn2 + 1 - LMn1) < prec THEN LMn2 = LMn2 + 1
                SclMn = LMn2 * Test

                LMx1 = Mx / Test
                LMx2 = FIX(LMx1 + 1)
                IF LMx1 < - 1 THEN LMx2 = LMx2 - 1
                IF ABS(LMx1 + 1 - LMx2) < prec THEN LMx2 = LMx2 - 1
                SclMx = LMx2 * Test

                Range = LMx2 - LMn2
                IF Range <= Div THEN EXIT FOR
            NEXT i

            Range = (Div - Range) / 2  'Set Scale min and max
            SclMn = SclMn - Range * Test
            SclMx = SclMn + Div * Test

            IF SclMn > Mn THEN SclMn = Mn  'Prevent errors
            IF SclMx < Mx THEN SclMx = Mx

            IF Mn >= 0 AND SclMn < 0 THEN  'Remove divisions where no data plotted
                SclMx = SclMx - SclMn  'so data takes up most of chart
                IF SclMx > Mx THEN
                    Range = SclMx / Div
                    WHILE SclMx > Mx + Range * 1.01
                        SclMx = SclMx - Range
                        Div = Div - 1
                    WEND
                END IF
                SclMn = 0
            END IF

            IF Mx <= 0 AND SclMx > 0 THEN
                SclMn = SclMn - SclMx
                IF SclMn < Mn THEN
                    Range = SclMn / Div
                    WHILE SclMn < Mn + Range * 1.01
                        SclMn = SclMn - Range
                        Div = Div - 1
                    WEND
                END IF
                SclMx = 0
            END IF

            IF SclMn * SclMx < 0 THEN
                Range = (SclMx - SclMn) / Div
                IF SclMn < Mn THEN
                    WHILE SclMn < Mn - Range * 1.01
                        SclMn = SclMn + Range
                        Div = Div - 1
                    WEND
                END IF
                IF SclMx > Mx THEN
                    WHILE SclMx > Mx + Range * 1.01
                        SclMx = SclMx - Range
                        Div = Div - 1
                    WEND
                END IF
            END IF

            SELECT CASE Axis
                CASE 0  'Assign values to the X Axis
                    .XAxis.Min = SclMn
                    .XAxis.Max = SclMx
                    .XAxis.Div = Div
                    .XAxis.STEP = (SclMx - SclMn) / Div
                CASE ELSE  'Assign values to the Y Axis
                    .YAxis.Min = SclMn
                    .YAxis.Max = SclMx
                    .YAxis.Div = Div
                    .YAxis.STEP = (SclMx - SclMn) / Div
            END SELECT

        END WITH

    END SUB
    '------------------------------------------------------------------------------------------
    PRIVATE :
    SUB SetScale

        DIM i AS INTEGER  'Loop counters...
        DIM j AS INTEGER
        DIM XMax AS SINGLE
        DIM XMin AS SINGLE
        DIM YMax AS SINGLE
        DIM YMin AS SINGLE
        DIM Test AS SINGLE
        XMax = - 1e35  'Start Small
        XMin = 1e35  'Start Big
        YMax = - 1e35  'Ditto
        YMin = 1e35

        WITH QChart

            SELECT CASE .ChartType
                CASE ctBar , ctLine
                    IF .YAxis.AutoScale = TRUE THEN  'Find Data Min and Max
                        SELECT CASE .ChartStyle
                            CASE csPctStacked
                                .YAxis.Min = 0
                                .YAxis.Max = 100
                                .YAxis.STEP = 10
                                .YAxis.ScaleFactor = .YAxis.LEN / 100
                                EXIT SUB
                            CASE csStacked
                                FOR i = 1 TO .DATA.RowCount
                                    Test = .RowTotal(i)
                                    IF Test < YMin THEN YMin = Test
                                    IF Test > YMax THEN YMax = Test
                                NEXT i
                            CASE ELSE
                                FOR i = 1 TO .DATA.ColCount
                                    FOR j = 1 TO .DATA.RowCount
                                        IF .DATA.Cell(i , j) <> .Missing THEN Test = VAL(.DATA.Cell(i , j))
                                        IF Test < YMin THEN YMin = Test
                                        IF Test > YMax THEN YMax = Test
                                    NEXT j
                                NEXT i

                        END SELECT
                    END IF

                CASE ctXY
                    IF .XAxis.AutoScale = TRUE THEN  'Find  X Data Min and Max
                        FOR i = 1 TO .DATA.ColCount - 1 STEP 2
                            FOR j = 1 TO .DATA.RowCount
                                IF .DATA.Cell(i , j) <> .Missing THEN Test = VAL(.DATA.Cell(i , j))
                                IF Test < XMin THEN XMin = Test
                                IF Test > XMax THEN XMax = Test
                            NEXT j
                        NEXT i
                    END IF

                    IF .YAxis.AutoScale = TRUE THEN  'Find Y Data Min and Max
                        FOR i = 2 TO .DATA.ColCount STEP 2
                            FOR j = 1 TO .DATA.RowCount
                                IF .DATA.Cell(i , j) <> .Missing THEN Test = VAL(.DATA.Cell(i , j))
                                IF Test < YMin THEN YMin = Test
                                IF Test > YMax THEN YMax = Test
                            NEXT j
                        NEXT i
                    END IF

                CASE ctBox
                    IF .YAxis.AutoScale = TRUE THEN  'Find Data Min and Max
                        FOR i = 1 TO .DATA.ColCount
                            IF .DATA.Cell(i , 5) <> .Missing THEN Test = VAL(.DATA.Cell(i , 5))
                            IF Test < YMin THEN YMin = Test
                            IF .DATA.Cell(i , 1) <> .Missing THEN Test = VAL(.DATA.Cell(i , 1))
                            IF Test > YMax THEN YMax = Test
                        NEXT i
                    END IF
            END SELECT

            SELECT CASE .YAxis.LogScale
                CASE FALSE
                    IF .YAxis.AutoScale = TRUE THEN
                        .ScaleAxis(YMin , YMax , 1)
                    ELSE
                        graphcursorpos2
                        .YAxis.Min=.YAxis.Min-ymingraphglobal
                        .YAxis.Max =.YAxis.Max + ymaxgraphglobal
                        IF .YAxis.Div < 1 THEN .YAxis.Div = 1
                        .YAxis.STEP = (.YAxis.Max - .YAxis.Min) / .YAxis.Div
                    END IF
                    .YAxis.ScaleFactor = .YAxis.LEN / (.YAxis.Max - .YAxis.Min)
                    'Print .YAxis.ScaleFactor
                    .YAxis.Zero = (.YAxis.Ori + .YAxis.Min * .YAxis.ScaleFactor)
                CASE TRUE  'See below for explanantion
                    '.YAxis.Min = FLOOR(.Log10(YMin))
                    '.YAxis.Max = CEIL(.Log10(YMax))
                    graphcursorpos2
                    .YAxis.Min = FLOOR(.Log10(graphvlow))
                    .YAxis.Max = CEIL(.Log10(graphvhigh))
                    .YAxis.Div = (.YAxis.Max - .YAxis.Min)
                    .YAxis.ScaleFactor = .YAxis.LEN / .YAxis.Div
                    .YAxis.TicIntvl = .YAxis.ScaleFactor

            END SELECT


            IF .ChartType <> ctXY THEN EXIT SUB  'If not XY no Values on X Axis so Bail!

            SELECT CASE .XAxis.LogScale
                CASE FALSE
                    IF .XAxis.AutoScale = TRUE THEN
                        .ScaleAxis(XMin , XMax , 0)
                    ELSE
                        IF .XAxis.Div < 1 THEN .XAxis.Div = 1
                        .XAxis.STEP = (.XAxis.Max - .XAxis.Min) / .XAxis.Div
                    END IF
                    .XAxis.ScaleFactor = .XAxis.LEN / (.XAxis.Max - .XAxis.Min)
                    'Print .XAxis.ScaleFactor
                    .XAxis.Zero = .XAxis.Ori - .XAxis.Min * .XAxis.ScaleFactor
                CASE TRUE  'Log Scale
                    .XAxis.Min = FLOOR(.Log10(XMin)) 'Set Min to Lower power of ten
                    .XAxis.Max = CEIL(.Log10(XMax)) 'Set Max to Greater power of ten
                    .XAxis.Div = (.XAxis.Max - .XAxis.Min) 'Div = # of Log Cycles
                    .XAxis.ScaleFactor = .XAxis.LEN / .XAxis.Div * 3
                    .XAxis.TicIntvl = .XAxis.ScaleFactor
            END SELECT


        END WITH

    END SUB
    '------------------------------------------------------------------------------------------
    PRIVATE :
    SUB SetSeries  'Set up series colors and marker types

        DIM i AS INTEGER
        DIM NumSeries AS INTEGER
        DIM Grey AS INTEGER
        DIM NumShades AS INTEGER
        DIM White AS INTEGER

        WITH QChart
            IF .ChartType = ctXY THEN
                NumSeries = .DATA.ColCount \ 2
            ELSE
                NumSeries = .DATA.ColCount
            END IF

            IF .ChartType = ctBar OR .ChartType = ctBox OR .ChartType = ctPie THEN
                NumShades = 5
                White = 1
            ELSE
                NumShades = 4
                White = - 1
            END IF

            FOR i = 1 TO NumSeries
                IF .Series(i).AutoMark = TRUE THEN .Series(i).Marker = (i - 1) MOD 8 + 1
                IF .Series(i).AutoColor = TRUE THEN
                    .Series(i).Color = .Colors((i) MOD (UBOUND(QChart.Colors) + White))
                END IF
                IF .GreyScale = TRUE THEN
                    Grey = ((i - 1) MOD NumShades) * 63
                    .Series(i).Color = RGB(Grey , Grey , Grey)
                END IF
                IF .BW = TRUE THEN .Series(i).Color = i  '0
                'doevents
            NEXT
        END WITH
    END SUB
    '---------------------------------------------------------------------------------------
    PRIVATE :
    SUB DrawAxes

        DIM i AS INTEGER  'Loop counters...
        DIM j AS INTEGER
        DIM x1 AS SINGLE  'for readability
        DIM y1 AS SINGLE
        DIM x2 AS SINGLE
        DIM y2 AS SINGLE

        WITH QChart

            x1 = 2  'Draw a frame around entire chart
            y1 = 2
            x2 = .Buffer.Width - 2
            y2 = .Buffer.Height - 2
            IF .ChartBorder = TRUE THEN .Buffer.Rectangle(x1 , y1 , x2 , y2 , .fgColor)

            IF .ChartType = ctPie THEN EXIT SUB  'No Axes for Pie Charts

            x1 = .XAxis.Ori  'Draw a box around Plot Area
            y1 = .YAxis.Ori
            x2 = .XAxis.Ori + .XAxis.LEN
            y2 = .YAxis.Ori - .YAxis.LEN
            IF .AxisBorder = TRUE THEN
                .Buffer.Rectangle(x1 , y1 , x2 + 1 , y2 , .GridColor)
                .Buffer.FillRect(x1 + 1 , y1 + 1 , x2 , y2 + 1 , .PlotAreaColor)
            END IF

            IF .XAxis.Tics = TRUE THEN  'Set Tic Size
                .XAxis.TicLen = .YAxis.LEN * .01
            ELSE
                .XAxis.TicLen = 0
            END IF

            IF .XAxis.Grid = TRUE THEN  'Draw a grid and tics
                y1 = .YAxis.Ori + .XAxis.TicLen
                y2 = .YAxis.Ori - .YAxis.LEN
            ELSE  'Draw Tics only
                y1 = .YAxis.Ori + .XAxis.TicLen
                y2 = .YAxis.Ori - .Xaxis.TicLen
            END IF

            IF .XAxis.LogScale = FALSE THEN  'draw linear grid lines
                IF .XAxis.Div < 1 THEN .XAxis.Div = 1  'Avoid division by zero
                .XAxis.TicIntvl = .XAxis.LEN / .XAxis.Div
                FOR i = 0 TO .XAxis.Div STEP 32
                    x1 = .XAxis.Ori + .XAxis.TicIntvl * i
                    x2 = x1
                    .Buffer.Line(x1 , y1 , x2 , y2 , .GridColor)
                    'doevents
                NEXT
                IF .ChartType = ctXY AND .XAxis.MnrTics = TRUE THEN
                    y1 = .YAxis.Ori - .XAxis.TicLen / 2
                    y2 = .YAxis.Ori + .XAxis.TicLen / 2
                    FOR i = 0 TO .XAxis.Div - 1
                        FOR j = 1 TO 4
                            x1 = .XAxis.Ori + .XAxis.TicIntvl * i + .XAxis.TicIntvl / 5 * j
                            x2 = x1
                            .Buffer.Line(x1 , y1 , x2 , y2 , .GridColor)
                            'doevents
                        NEXT
                        'doevents
                    NEXT
                END IF
            ELSEIF .XAxis.LogScale = TRUE THEN  'draw log grid lines
                FOR i = .XAxis.Min TO .XAxis.Max - 1
                    FOR j = 1 TO 9
                        x1 = .XAxis.Ori + (.Log10(10^i * j) - .XAxis.Min) * .XAxis.ScaleFactor
                        x2 = x1
                        .Buffer.Line(x1 , y1 , x2 , y2 , .GridColor)
                        'doevents
                    NEXT j
                    'doevents
                NEXT i
                .Buffer.Line(.XAxis.Ori + .XAxis.LEN , y1 , .XAxis.Ori + .XAxis.LEN , y2 , .GridColor)

            END IF

            IF .YAxis.Tics = TRUE THEN  'Set Tic Size
                .YAxis.TicLen = .XAxis.LEN * .01
            ELSE
                .YAxis.TicLen = 0
            END IF

            IF .YAxis.Grid = TRUE THEN  'Draw a grid and tics
                x1 = .XAxis.Ori - .YAxis.TicLen
                x2 = .XAxis.Ori + .XAxis.LEN
            ELSE  'Draw Tics only
                x1 = .XAxis.Ori - .YAxis.TicLen
                x2 = .XAxis.Ori + .YAxis.TicLen
            END IF

            IF .YAxis.LogScale = FALSE THEN  'draw linear grid lines
                IF .YAxis.Div < 1 THEN .YAxis.Div = 1  'Avoid division by zero
                .YAxis.TicIntvl = .YAxis.LEN / .YAxis.Div
                FOR i = 0 TO .YAxis.Div
                    y1 = .YAxis.Ori - .YAxis.TicIntvl * i
                    y2 = y1
                    '.Buffer.Line (x1,y1,x2,y2,.GridColor)     ' horizontal grid lines
                    .Buffer.Line(x1 , y1 , .XAxis.Ori + .YAxis.TicLen , y2 , .GridColor) 'y axis tics
                    'doevents
                NEXT
                IF .YAxis.MnrTics = TRUE THEN
                    x1 = .XAxis.Ori - .YAxis.TicLen / 2
                    x2 = .XAxis.Ori + .YAxis.TicLen / 2
                    FOR i = 0 TO .YAxis.Div - 1
                        FOR j = 1 TO 4
                            y1 = .YAxis.Ori - .YAxis.TicIntvl * i - .YAxis.TicIntvl / 5 * j
                            y2 = y1
                            .Buffer.Line(x1 , y1 , x2 , y2 , .GridColor)
                            'doevents
                        NEXT
                        'doevents
                    NEXT
                END IF


            ELSEIF .YAxis.LogScale = TRUE THEN  'draw log grid lines

                FOR i = .YAxis.Min TO .YAxis.Max - 1
                    FOR j = 1 TO 9
                        y1 = .YAxis.Ori - (.Log10(10^i * j) - .YAxis.Min) * .YAxis.ScaleFactor
                        y2 = y1
                        .Buffer.Line(x1 , y1 , x2 , y2 , .GridColor)
                        'doevents
                    NEXT j
                    'doevents
                NEXT i
                .Buffer.Line(x1 , .YAxis.Ori - .YAxis.LEN , x2 , .YAxis.Ori - .YAxis.LEN , .GridColor)


            END IF

            IF .XAxis.DrawZero = TRUE AND .XAxis.LogScale = FALSE THEN  'Draw the X Zero Line
                IF .XAxis.Min * .XAxis.Max < 0 THEN  'Data Spans zero
                    x1 = .XAxis.Zero
                    y1 = .YAxis.Ori
                    x2 = .XAxis.Zero
                    y2 = .YAxis.Ori - .YAxis.LEN + 1
                    .Buffer.Line(x1 , y1 , x2 , y2 , .XAxis.ZeroColor)
                END IF
            END IF

            IF .YAxis.DrawZero = TRUE AND .YAxis.LogScale = FALSE THEN  'Draw the Y Zero Line
                IF .YAxis.Min * .YAxis.Max < 0 THEN  'Data Spans zero
                    x1 = .XAxis.Ori
                    y1 = .YAxis.Zero
                    x2 = .XAxis.Ori + .XAxis.LEN - 1
                    y2 = .YAxis.Zero
                    .Buffer.Line(x1 , y1 , x2 , y2 , .YAxis.ZeroColor)
                END IF
            END IF

            x1 = .XAxis.Ori  'Overwrite XAxis in its color
            y1 = .YAxis.Ori
            x2 = .XAxis.Ori + .XAxis.LEN
            y2 = .YAxis.Ori
            .Buffer.Line(x1 , y1 , x2 , y2 , .XAxis.Color)

            x2 = .XAxis.Ori
            y2 = .YAxis.Ori - .YAxis.LEN  'Overwrite YAxis in its color
            .Buffer.Line(x1 , y1 , x2 , y2 , .YAxis.Color)

        END WITH

    END SUB
    '---------------------------------------------------------------------------------------
    PRIVATE :
    SUB DrawTitles

        DIM i AS INTEGER  'Loop counters...
        DIM j AS INTEGER
        DIM Spacer AS INTEGER

        WITH QChart
            '--- Main Title
            .Buffer.Font = .MainFont
            .MainTitle.Left = .XAxis.Ori + (.XAxis.LEN - .Buffer.TextWidth(RTRIM$(.MainTitle.Text))) / 2
            .MainTitle.Top = 3
            .Buffer.TextOut(.MainTitle.Left , .MainTitle.Top , RTRIM$(.MainTitle.Text) , _
                .MainFont.Color , .bgColor)

            '--- Sub Title
            Spacer = .Buffer.TextHeight(.MainTitle.Text) 'Calc this before Font is Changed
            .Buffer.Font = .SubFont
            .SubTitle.Left = .XAxis.Ori + (.XAxis.LEN - .Buffer.TextWidth(RTRIM$(.SubTitle.Text))) / 2
            .SubTitle.Top = .MainTitle.Top + Spacer
            .Buffer.TextOut(.SubTitle.Left , .SubTitle.Top , RTRIM$(.SubTitle.Text) , _
                .SubFont.Color , .bgColor)

            '--- X Axis Title
            .Buffer.Font = .AxisFont  'both x and y axis
            .XTitle.Left = .XAxis.Ori + (.XAxis.LEN - .Buffer.TextWidth(RTRIM$(.XTitle.Text))) / 2
            .XTitle.Top = .YAxis.Ori - 10 + .Buffer.TextHeight(.XTitle.Text) * 2.75
            .Buffer.TextOut(.XTitle.Left , .XTitle.Top , RTRIM$(.XTitle.Text) , _
                .AxisFont.Color , .bgColor)

            '--- Copyright mark
            .Buffer.Font = .AxisFont  'both x and y axis
            .XTitle.Left = .XAxis.Ori - 70
            .XTitle.Top = .YAxis.Ori - 10 + .Buffer.TextHeight(.XTitle.Text) * 2.75
            .Buffer.TextOut(.XTitle.Left , .XTitle.Top , RTRIM$("QChartist (c) 2010-2015 Julien Moog - http://www.qchartist.net") , _
                .AxisFont.Color , .bgColor)

            '--- Y Axis Title
            j = LEN(RTRIM$(.YTitle.Text))
            .YTitle.Left = .XAxis.Ori / 6
            .YTitle.Top = (.Buffer.Height - .Buffer.TextHeight(.YTitle.Text) * j) / 2
            FOR i = 1 TO j  '--- Draw Y label vertically
                .Buffer.TextOut(.YTitle.Left , .YTitle.Top , MID$(.YTitle.Text , i , 1) , _
                    .AxisFont.Color , .bgColor)
                .YTitle.Top = .YTitle.Top + .Buffer.TextHeight(.YTitle.Text)
                'doevents
            NEXT i

        END WITH

    END SUB
    '---------------------------------------------------------------------------------------
    PRIVATE :
    SUB DrawLabels

        DIM i AS INTEGER
        DIM TicVal AS SINGLE  'Value of tic label
        DIM LabelLen AS SINGLE  'Total length of Labels

        WITH QChart

            IF .XAxis.Labeled = FALSE AND .YAxis.Labeled = FALSE THEN EXIT SUB

            .Buffer.Font = .AxisFont  'Assign Legend font to buffer
            IF .XAxis.Div < 1 THEN .XAXis.Div = 1  'Avoid division by zero
            IF .YAxis.Div < 1 THEN .YAxis.Div = 1

            SELECT CASE .ChartType
                CASE ctXY
                    IF .XAxis.Labeled THEN

                        LabelLen = 0  'Get the total length of all labels
                        FOR i = 0 TO .XAxis.Div
                            TicVal = .XAxis.Min + .XAxis.STEP * i
                            LabelLen = LabelLen + .Buffer.TextWidth(FORMAT$("%-4.4g" , TicVal))
                            'doevents
                        NEXT

                        FOR i = 0 TO .XAxis.Div
                            IF .XAxis.LogScale = FALSE THEN
                                TicVal = .XAxis.Min + .XAxis.STEP * i  'below avoids precision artifact at 0
                                IF ABS((.XAxis.Ori + .XAxis.TicIntvl * i) - .XAxis.Zero) < 1 THEN TicVal = 0
                            ELSEIF .XAxis.LogScale = TRUE THEN  'Log Scale
                                TicVal = 10^(i + .XAxis.Min)

                            END IF
                            .AxisLbl.Text = FORMAT$("%-4.4g" , TicVal)
                            .AxisLbl.Top = .YAxis.Ori + .Buffer.TextHeight(.AxisLbl.Text) / 2
                            .AxisLbl.Left = .XAxis.Ori + .XAxis.TicIntvl * i - _
                                .Buffer.TextWidth(RTRIM$(.AxisLbl.Text)) / 2
                            IF LabelLen * 1.1 <= .XAxis.LEN THEN  'Label all tics
                                .Buffer.TextOut(.AxisLbl.Left , .AxisLbl.Top , RTRIM$(.AxisLbl.Text) , _
                                    .Buffer.Font.Color , .bgColor)
                            ELSE  'Label every other tic
                                IF i MOD 2 = 0 THEN .Buffer.TextOut(.AxisLbl.Left , .AxisLbl.Top , _
                                    RTRIM$(.AxisLbl.Text) , .Buffer.Font.Color , .bgColor)
                            END IF
                            'doevents
                        NEXT
                    END IF

                CASE ctBox  'Labels in Row 0 of of each Col
                    IF .XAxis.Labeled = TRUE THEN
                        .XAxis.TicIntvl = .XAxis.LEN / .DATA.ColCount

                        LabelLen = 0  'Get the total length of all labels
                        FOR i = 0 TO .DATA.ColCount
                            LabelLen = LabelLen + .Buffer.TextWidth(.DATA.Cell(i , 0))
                            'doevents
                        NEXT i

                        FOR i = 1 TO .DATA.ColCount STEP 32			
                            .AxisLbl.Text = .DATA.Cell(i , 0)
                            .AxisLbl.Left = .XAxis.Ori + (i - 1) * .Xaxis.TicIntvl + [.Xaxis.TicIntvl - _
                                .Buffer.TextWidth(RTRIM$(.AxisLbl.Text)) ] / 2

                            IF LabelLen * 1.1 <= .XAxis.LEN THEN
                                .AxisLbl.Top = .YAxis.Ori + .Buffer.TextHeight(.AxisLbl.Text) / 2
                            ELSE  'alternate up and down for room
                                .AxisLbl.Top = .YAxis.Ori + .Buffer.TextHeight(.AxisLbl.Text) * _
                                    (((i - 1) MOD 2) + .5)
                            END IF
                            .Buffer.TextOut(.AxisLbl.Left , .AxisLbl.Top , RTRIM$(.AxisLbl.Text) , _
                                .Buffer.Font.Color , .bgColor)                                
                            'doevents
			NEXT i
if scrollmode=0 then            
defint ii=0
FOR i = 1 TO .DATA.ColCount
' linking time with tic pixel position on axe
.AxisLbl.Text = .DATA.Cell(i , 0)
defstr year=mid$(.AxisLbl.Text,1,4)
defstr month=mid$(.AxisLbl.Text,6,2)
defstr day=mid$(.AxisLbl.Text,9,2)
defstr hour=mid$(.AxisLbl.Text,12,2)
defstr minute=mid$(.AxisLbl.Text,15,2)
defstr $mydate=year+";"+month+";"+day+";"+hour+";"+minute+";"+"00"
deflng myunixdate=val(varptr$(date_to_unix_time(varptr($mydate))))
deflng mypixelpos=.XAxis.Ori + (i - 1) * .Xaxis.TicIntvl
timechartpos(ii,0)=myunixdate
timechartpos(ii,1)=mypixelpos
ii++
'doevents
                        NEXT i
end if                        
                    END IF

                CASE ELSE  'Labels in Col 0 of each Row
                    IF .XAxis.Labeled = TRUE THEN
                        SELECT CASE .ChartType
                            CASE ctLine
                                .XAxis.TicIntvl = .XAxis.LEN / (.DATA.RowCount - 1)
                            CASE ELSE
                                .XAxis.TicIntvl = .XAxis.LEN / .DATA.RowCount
                        END SELECT

                        LabelLen = 0  'Get the total length of all labels
                        FOR i = 0 TO .DATA.RowCount
                            LabelLen = LabelLen + .Buffer.TextWidth(.DATA.Cell(0 , i))
                            'doevents
                        NEXT i

                        FOR i = 0 TO .DATA.RowCount
                            IF .ChartStyle = csHisto THEN  'Histo Min val in Col 0 of Row 0 ++
                                .AxisLbl.Text = .DATA.Cell(0 , i)
                            ELSE  'Labels stored in Col 0 of Row 1 ++
                                .AxisLbl.Text = .DATA.Cell(0 , i + 1)
                            END IF

                            IF .ChartType = ctLine OR .ChartStyle = csHisto THEN
                                .AxisLbl.Left = .XAxis.Ori + (i) * .Xaxis.TicIntvl - _
                                    .Buffer.TextWidth(RTRIM$(.AxisLbl.Text)) / 2
                            ELSE
                                .AxisLbl.Left = .XAxis.Ori + (i) * .Xaxis.TicIntvl + [.Xaxis.TicIntvl - _
                                    .Buffer.TextWidth(RTRIM$(.AxisLbl.Text)) ] / 2
                            END IF

                            IF LabelLen * 1.1 <= .XAxis.LEN THEN
                                .AxisLbl.Top = .YAxis.Ori + .Buffer.TextHeight(.AxisLbl.Text) / 2
                            ELSE  'alternate up and down for room
                                .AxisLbl.Top = .YAxis.Ori + .Buffer.TextHeight(.AxisLbl.Text) * _
                                    ((i MOD 2) + .5)
                            END IF
                            .Buffer.TextOut(.AxisLbl.Left , .AxisLbl.Top , RTRIM$(.AxisLbl.Text) , _
                                .Buffer.Font.Color , .bgColor)
                            'doevents
                        NEXT i
                    END IF
            END SELECT

            IF .YAxis.Labeled = TRUE THEN  'ALL Charts have values on the Y Axis

                FOR i = 0 TO .YAxis.Div
                    IF .YAXIS.LogScale = FALSE THEN

                        TicVal = .YAxis.Min + .YAxis.STEP * i  'below avoids precision artifact at 0
                        IF ABS((.YAxis.Ori - .YAxis.TicIntvl * i) - .YAxis.Zero) < 1 THEN TicVal = 0

                    ELSEIF .YAXIS.LogScale = TRUE THEN  'Log Scaling

                        TicVal = 10^(i + .YAxis.Min)


                    END IF


                    .AxisLbl.Text = FORMAT$("%-4.4g" , TicVal)
                    .AxisLbl.Top = .YAxis.Ori - .YAxis.TicIntvl * i_
                        - .Buffer.TextHeight(.AxisLbl.Text) / 2
                    .AxisLbl.Left = .XAxis.Ori - .Buffer.TextWidth(RTRIM$(.AxisLbl.Text)) - _
                        .Buffer.TextWidth("8")
                    .Buffer.TextOut(.AxisLbl.Left , .AxisLbl.Top , RTRIM$(.AxisLbl.Text) , _
                        .Buffer.Font.Color , .bgColor)

if scrollmode=0 then
' linking price with tic pixel position on axe
if i=0 then 
pricechartpos(0,0)=.YAxis.Min
pricechartpos(0,1)=.YAxis.Ori
end if
if i=.YAxis.Div then
pricechartpos(1,0)=.YAxis.Max
pricechartpos(1,1)=.YAxis.Ori - .YAxis.TicIntvl * i
end if
end if
                    'doevents

                NEXT
            END IF

        END WITH

    END SUB
    '---------------------------------------------------------------------------------------
    PRIVATE :
    SUB DrawMarker(x1 AS SINGLE , y1 AS SINGLE , MrkrStyle AS INTEGER , Color AS LONG)

        DIM x2 AS SINGLE
        DIM y2 AS SINGLE

        WITH QChart

            x1 = x1 - .MarkerSize  'MarkerSize is set in .Intitalize or
            y1 = y1 - .MarkerSize  'changed by user
            x2 = x1 + .MarkerSize * 2
            y2 = y1 + .MarkerSize * 2

            SELECT CASE MrkrStyle  'Sent by calling routine

                CASE msFillCircle
                    .Buffer.Circle(x1 , y1 , x2 , y2 , Color , Color)

                CASE msFillSquare
                    .Buffer.FillRect(x1 , y1 , x2 , y2 , Color)

                CASE msFillTriangleUp
                    .Buffer.Line(x1 , y2 , x2 , y2 , Color)
                    .Buffer.Line(x1 , y2 , x1 + .MarkerSize , y1 , Color)
                    .Buffer.Line(x2 , y2 , x1 + .MarkerSize , y1 , Color)
                    .Buffer.Paint(x1 + .MarkerSize , y1 + .MarkerSize , Color , Color)

                CASE msFillTriangleDown
                    y2 = y2 - .MarkerSize * 2
                    .Buffer.Line(x1 , y2 , x2 , y2 , Color)
                    .Buffer.Line(x1 , y2 , x1 + .MarkerSize , y1 + .MarkerSize * 2 , Color)
                    .Buffer.Line(x2 , y2 , x1 + .MarkerSize , y1 + .MarkerSize * 2 , Color)
                    .Buffer.Paint(x1 + .MarkerSize , y1 + .MarkerSize , Color , Color)

                CASE msCircle
                    .Buffer.Circle(x1 , y1 , x2 , y2 , Color , .bgColor)

                CASE msSquare
                    .Buffer.Rectangle(x1 , y1 , x2 , y2 , Color)
                    .Buffer.FillRect(x1 + 1 , y1 + 1.1 , x2 - 1 , y2 - 1.1 , .bgColor)

                CASE msTriangleUp
                    .Buffer.Line(x1 , y2 , x2 , y2 , Color)
                    .Buffer.Line(x1 , y2 , x1 + .MarkerSize , y1 , Color)
                    .Buffer.Line(x2 , y2 , x1 + .MarkerSize , y1 , Color)
                    .Buffer.Paint(x1 + .MarkerSize , y1 + .MarkerSize , .bgColor , Color)

                CASE msTriangleDown
                    y2 = y2 - .MarkerSize * 2
                    .Buffer.Line(x1 , y2 , x2 , y2 , Color)
                    .Buffer.Line(x1 , y2 , x1 + .MarkerSize , y1 + .MarkerSize * 2 , Color)
                    .Buffer.Line(x2 , y2 , x1 + .MarkerSize , y1 + .MarkerSize * 2 , Color)
                    .Buffer.Paint(x1 + .MarkerSize , y1 + .MarkerSize , .bgColor , Color)

            END SELECT

        END WITH

    END SUB
    '---------------------------------------------------------------------------------------
    PRIVATE :
    SUB DrawLegend

        DIM i AS INTEGER  'Loop counter...
        DIM x1 AS SINGLE  'for readability
        DIM y1 AS SINGLE
        DIM x2 AS SINGLE
        DIM y2 AS SINGLE
        DIM BorderHgt AS INTEGER
        DIM LineLen AS INTEGER
        DIM LMark AS INTEGER

        WITH QChart
            IF .DoLegend = FALSE THEN EXIT SUB  'Don't perform task

            .Buffer.Font = .LegendFont

            x1 = (.XAxis.Ori + .XAxis.LEN) + .Buffer.TextWidth("W") 'Draw a box for the legend
            x2 = .Buffer.Width - .Buffer.TextWidth("W")
            LineLen = x2 - x1 - .Buffer.TextWidth("W") * 2
            BorderHgt = .Buffer.TextHeight("W") * (.DATA.ColCount) + 5
            IF .ChartType = ctXY THEN  'Special Case
                BorderHgt = .Buffer.TextHeight("W") * (.DATA.ColCount / 2) + 5
            END IF
            IF .ChartStyle = csLines THEN BorderHgt = BorderHgt * 1.5  'Leave room for line styles
            y1 = .YAxis.Ori - (.YAxis.LEN + BorderHgt) / 2
            y2 = y1 + BorderHgt
            .Buffer.Rectangle(x1 , y1 , x2 , y2 , .fgColor)

            SELECT CASE .ChartType

                CASE ctXY
                    SetBkColor(.Buffer.Handle , .bgColor)

                    FOR i = 2 TO .DATA.ColCount STEP 2
                        .Legend.Text = .DATA.Cell(i , 0)
                        .Legend.Top = y1 + .Buffer.TextHeight(.Legend.Text) * (i \ 2 - 1) + 2
                        .Legend.Left = x1 + .Buffer.TextWidth("I")
                        x2 = .Legend.Left + .Buffer.TextHeight(.Legend.Text)
                        y2 = .Legend.Top + .Buffer.TextHeight(.Legend.Text)
                        IF .ChartStyle <> csLines THEN
                            LMark = .MarkerSize
                            .MarkerSize = .Buffer.TextHeight(.Legend.Text) / 3
                            .DrawMarker(.Legend.Left + .Buffer.TextHeight(.Legend.Text) / 3 , _
                                .Legend.Top + .Buffer.TextHeight(.Legend.Text) / 2 , _
                                .Series(i \ 2).Marker , .Series(i \ 2).Color)
                            .Buffer.TextOut(x2 + 2 , .Legend.Top , RTRIM$(.Legend.Text) , _
                                .LegendFont.Color , .bgColor)
                            .MarkerSize = LMark
                        ELSE
                            .Legend.Top = .Legend.Top + .Buffer.TextHeight(.Legend.Text) / 3 * (i \ 2 - 1)
                            .hPen = CreatePen(.Series(i \ 2).LineStyle , .Series(i \ 2).LineWidth , .Series(i \ 2).Color)
                            .OldPen = SelectObject(.Buffer.Handle , .hPen)
                            MoveToEx(.Buffer.Handle , .Legend.Left , y2 + .Buffer.TextHeight(.Legend.Text) / 2 * (i \ 2 - 1) , 0)
                            LineTo(.Buffer.Handle , x2 + LineLen , y2 + .Buffer.TextHeight(.Legend.Text) / 2 * (i \ 2 - 1))
                            DeleteObject(SelectObject(.Buffer.Handle , .OldPen))
                            .Buffer.TextOut(x2 - .Buffer.TextWidth("I") , .Legend.Top , RTRIM$(.Legend.Text) , _
                                .LegendFont.Color , .bgColor)
                        END IF
                        'doevents
                    NEXT

                CASE ELSE  'Below works for all other charts
                    SetBkColor(.Buffer.Handle , .bgColor)

                    .Buffer.Line(0 , 0 , 0 , 0 , 0) 'Reset Buffer's pen to Black
                    FOR i = 1 TO .DATA.ColCount
                        .Legend.Text = .DATA.Cell(i , 0)
                        .Legend.Top = y1 + .Buffer.TextHeight(.Legend.Text) * (i - 1) + 2
                        .Legend.Left = x1 + .Buffer.TextWidth("I")
                        x2 = .Legend.Left + .Buffer.TextHeight(.Legend.Text)
                        y2 = .Legend.Top + .Buffer.TextHeight(.Legend.Text)
                        IF .ChartType = ctLine THEN
                            IF .ChartStyle <> csLines THEN
                                LMark = .MarkerSize
                                .MarkerSize = .Buffer.TextHeight(.Legend.Text) / 3
                                .DrawMarker(.Legend.Left + .Buffer.TextHeight(.Legend.Text) / 3 , _
                                    .Legend.Top + .Buffer.TextHeight(.Legend.Text) / 2 , _
                                    .Series(i).Marker , .Series(i).Color)
                                .Buffer.TextOut(x2 + 2 , .Legend.Top , RTRIM$(.Legend.Text) , _
                                    .LegendFont.Color , .bgColor)
                                .MarkerSize = LMark
                            ELSE
                                .Legend.Top = .Legend.Top + .Buffer.TextHeight(.Legend.Text) / 2 * (i - 1)
                                .hPen = CreatePen(.Series(i).LineStyle , .Series(i).LineWidth , .Series(i).Color)
                                .OldPen = SelectObject(.Buffer.Handle , .hPen)
                                MoveToEx(.Buffer.Handle , .Legend.Left , y2 + .Buffer.TextHeight(.Legend.Text) / 2 * (i - 1) , 0)
                                LineTo(.Buffer.Handle , x2 + LineLen , y2 + .Buffer.TextHeight(.Legend.Text) / 2 * (i - 1))
                                DeleteObject(SelectObject(.Buffer.Handle , .OldPen))
                                .Buffer.TextOut(x2 - .Buffer.TextWidth("I") , .Legend.Top , RTRIM$(.Legend.Text) , _
                                    .LegendFont.Color , .bgColor)
                            END IF
                        ELSE
                            IF .Series(i).HatchStyle = hsSolid THEN
                                .hBrush = CreateSolidBrush(.Series(i).Color)
                            ELSE
                                .hBrush = CreateHatchBrush(.Series(i).HatchStyle , .Series(i).Color)
                            END IF
                            .OldBrush = SelectObject(.Buffer.Handle , .hBrush)
                            Rectangle(.Buffer.Handle , .Legend.Left , .Legend.Top + 2 , x2 , y2)
                            DeleteObject(SelectObject(.Buffer.Handle , .OldBrush))
                            .Buffer.TextOut(x2 + 2 , .Legend.Top , RTRIM$(.Legend.Text) , _
                                .LegendFont.Color , .bgColor)
                        END IF
                        'doevents

                    NEXT

            END SELECT
        END WITH

    END SUB
    '---------------------------------------------------------------------------------------
    PRIVATE :
    SUB DrawBar(Overlay AS INTEGER)

        'X Points are (OriX + VAL * XScaleFactor - XMin) (ScaleFactor = Axis.Len / Axis.Max)
        'Y Points are (OriY - VAL * YScaleFactor - YMin) (i.e.^^ = Pixels per Unit)

        DIM i AS INTEGER  'Loop counters...
        DIM j AS INTEGER
        DIM x1 AS SINGLE  'for readability
        DIM y1 AS SINGLE
        DIM x2 AS SINGLE
        DIM y2 AS SINGLE
        DIM GrpWidth AS SINGLE
        DIM BoxWidth AS SINGLE  'Width of bars in bar and box plots
        DIM Incr AS SINGLE  'Space between bars
        DIM Total AS SINGLE  'Row Total for % Stacked calcs

        IF Overlay = FALSE THEN
            WITH QChart  'Set up the chart window
                .ClearBuffer  'erase the current bitmap
                .SetSize
                .SetScale
                IF .Success = FALSE THEN  'Log Scaling failed
                    .ClearAll
                    EXIT SUB
                END IF
                .SetSeries
                .XAxis.Div = .DATA.RowCount  'Forces a grid line for each X Label
                .XAxis.DrawZero = FALSE  'No Values on the X
                .DrawAxes
                .DrawTitles
                .DrawLabels
                .DrawLegend
            END WITH
        END IF

        SELECT CASE QChart.ChartStyle

            CASE csHisto  'Histogram (no spaces between bars)
                WITH QChart  'Plot the data
                    BoxWidth = (.XAxis.LEN + .01) / .DATA.RowCount  'Leave some space at axis
                    FOR i = 1 TO .DATA.ColCount
                        IF .Series(i).HatchStyle = hsSolid THEN
                            .hBrush = CreateSolidBrush(.Series(i).Color)
                        ELSE
                            .hBrush = CreateHatchBrush(.Series(i).HatchStyle , .Series(i).Color)
                        END IF
                        .OldBrush = SelectObject(.Buffer.Handle , .hBrush)
                        Incr = BoxWidth * (i - 1) / (.DATA.ColCount + 1)
                        GrpWidth = BoxWidth - Incr
                        FOR j = 1 TO .DATA.RowCount
                            IF .DATA.Cell(i , j) = .Missing THEN GOTO NoPlotHisto
                            x1 = .XAxis.Ori + BoxWidth * (j - 1) + Incr / 2
                            x2 = x1 + GrpWidth + 1
                            IF .YAxis.LogScale = TRUE THEN
                                y1 = .YAxis.Ori
                                y2 = .YAxis.Ori - [.Log10(VAL(.DATA.Cell(i , j))) - .YAxis.Min] * .YAxis.ScaleFactor
                            ELSEIF .YAxis.Min >= 0 AND .YAxis.Max >= 0 THEN  'No Negative data
                                y1 = .YAxis.Ori
                                y2 = .YAxis.Ori - [VAL(.DATA.Cell(i , j)) - .YAxis.Min] * .YAxis.ScaleFactor
                            ELSE  'Have Negative values
                                y1 = .YAxis.Zero
                                IF VAL(.DATA.Cell(i , j)) < 0 AND .YAxis.Max <> 0 THEN y1 = y1 + 1  'let 0 line show
                                y2 = .YAxis.Zero - (VAL(.DATA.Cell(i , j)) * .YAxis.ScaleFactor) + 1
                            END IF
                            Rectangle(.Buffer.Handle , x1 , y1 , x2 , y2)
                            NoPlotHisto :
                        NEXT j
                        DeleteObject(SelectObject(.Buffer.Handle , .OldBrush))
                    NEXT i
                END WITH

            CASE csBar  'Grouped Bar Chart (spaces between bars)
                WITH QChart
                    GrpWidth = (.XAxis.LEN + .01) / .DATA.RowCount
                    BoxWidth = GrpWidth / (.DATA.ColCount + .5)
                    FOR i = 1 TO .DATA.ColCount
                        IF .Series(i).HatchStyle = hsSolid THEN
                            .hBrush = CreateSolidBrush(.Series(i).Color)
                        ELSE
                            .hBrush = CreateHatchBrush(.Series(i).HatchStyle , .Series(i).Color)
                        END IF
                        .OldBrush = SelectObject(.Buffer.Handle , .hBrush)
                        FOR j = 1 TO .DATA.RowCount
                            IF .DATA.Cell(i , j) = .Missing THEN GOTO NoPlotBar
                            x1 = (.XAxis.Ori + BoxWidth / 4) + GrpWidth * (j - 1) + BoxWidth * (i - 1)
                            x2 = x1 + BoxWidth + 1
                            IF .YAxis.LogScale = TRUE THEN
                                y1 = .YAxis.Ori
                                y2 = .YAxis.Ori - [.Log10(VAL(.DATA.Cell(i , j))) - .YAxis.Min] * .YAxis.ScaleFactor
                            ELSEIF .YAxis.Min >= 0 AND .YAxis.Max >= 0 THEN  'No Negative data
                                y1 = .YAxis.Ori
                                y2 = .YAxis.Ori - [VAL(.DATA.Cell(i , j)) - .YAxis.Min] * .YAxis.ScaleFactor
                            ELSE  'Have Negative values
                                y1 = .YAxis.Zero
                                IF VAL(.DATA.Cell(i , j)) < 0 AND .YAxis.Max <> 0 THEN y1 = y1 + 1  'let 0 line show
                                y2 = .YAxis.Zero - (VAL(.DATA.Cell(i , j)) * .YAxis.ScaleFactor) + 1
                            END IF
                            Rectangle(.Buffer.Handle , x1 , y1 , x2 , y2)
                            NoPlotBar :
                        NEXT j
                        DeleteObject(SelectObject(.Buffer.Handle , .OldBrush))
                    NEXT i
                END WITH

            CASE csStacked
                WITH QChart
                    BoxWidth = (.XAxis.LEN + .01) / (.DATA.RowCount + 1)
                    Incr = BoxWidth / .DATA.RowCount
                    FOR i = 1 TO .DATA.RowCount
                        FOR j = 1 TO .DATA.ColCount
                            IF .Series(j).HatchStyle = hsSolid THEN
                                .hBrush = CreateSolidBrush(.Series(j).Color)
                            ELSE
                                .hBrush = CreateHatchBrush(.Series(j).HatchStyle , .Series(j).Color)
                            END IF
                            .OldBrush = SelectObject(.Buffer.Handle , .hBrush)
                            x1 = (.XAxis.Ori + Incr / 2) + (BoxWidth + Incr) * (i - 1)
                            x2 = x1 + BoxWidth
                            IF j = 1 THEN y1 = .YAxis.Ori ELSE y1 = y2
                            y2 = y1 - (ABS(VAL(.DATA.Cell(j , i))) - .YAxis.Min) * .YAxis.ScaleFactor
                            Rectangle(.Buffer.Handle , x1 , y1 + 1 , x2 + 1 , y2)
                        NEXT j
                        DeleteObject(SelectObject(.Buffer.Handle , .OldBrush))
                    NEXT i
                END WITH

            CASE csPctStacked
                WITH QChart
                    BoxWidth = (.XAxis.LEN + .01) / (.DATA.RowCount + 1)
                    Incr = BoxWidth / .DATA.RowCount
                    FOR i = 1 TO .DATA.RowCount
                        Total = .RowTotal(i)
                        IF Total = 0 THEN
                            MESSAGEDLG("Division by Zero!" , 1 , 4 , 0)
                            .ClearAll
                            EXIT SUB
                        END IF
                        FOR j = 1 TO .DATA.ColCount
                            IF .Series(j).HatchStyle = hsSolid THEN
                                .hBrush = CreateSolidBrush(.Series(j).Color)
                            ELSE
                                .hBrush = CreateHatchBrush(.Series(j).HatchStyle , .Series(j).Color)
                            END IF
                            .OldBrush = SelectObject(.Buffer.Handle , .hBrush)
                            x1 = (.XAxis.Ori + Incr / 2) + (BoxWidth + Incr) * (i - 1)
                            x2 = x1 + BoxWidth
                            IF j = 1 THEN y1 = .YAxis.Ori ELSE y1 = y2
                            y2 = y1 - (100 * (ABS(VAL(.DATA.Cell(j , i))) / Total) * .YAxis.ScaleFactor)
                            Rectangle(.Buffer.Handle , x1 , y1 + 1 , x2 + 1 , y2)
                        NEXT j
                        DeleteObject(SelectObject(.Buffer.Handle , .OldBrush))
                    NEXT i
                END WITH

        END SELECT
        QChart.ChartExists = TRUE

    END SUB
    '---------------------------------------------------------------------------------------
    PRIVATE :
    SUB DrawXY(Overlay AS INTEGER)
        'X Points are (OriX + VAL * XScaleFactor - XMin) (ScaleFactor = Axis.Len / Axis.Max)
        'Y Points are (OriY - VAL * YScaleFactor - YMin) (i.e.^^ = Pixels per Unit)

        DIM i AS INTEGER  'Loop counters...
        DIM j AS INTEGER
        DIM x1 AS SINGLE  'for readability
        DIM y1 AS SINGLE
        DIM x2 AS SINGLE
        DIM y2 AS SINGLE

        IF Overlay = FALSE THEN
            WITH QChart  'Set up the chart window
                .ClearBuffer  'erase the current bitmap
                .SetSize
                .SetScale
                IF .Success = FALSE THEN  'Log Scaling failed
                    .ClearAll
                    EXIT SUB
                END IF
                .SetSeries
                .DrawAxes
                .DrawTitles
                .DrawLabels
                .DrawLegend
            END WITH
        END IF

        SELECT CASE QChart.ChartStyle

            CASE csPoints
                WITH QChart
                    FOR i = 2 TO .DATA.ColCount STEP 2
                        FOR j = 1 TO .DATA.RowCount

                            IF .DATA.Cell(i - 1 , j) = .Missing THEN GOTO NoPlotXYPt  'If data missing
                            IF .DATA.Cell(i , j) = .Missing THEN GOTO NoPlotXYPt

                            IF .XAxis.LogScale = FALSE THEN
                                x1 = .XAxis.Ori + [VAL(.DATA.Cell(i - 1 , j)) - .XAxis.Min] * .XAxis.ScaleFactor
                            ELSE
                                x1 = .XAxis.Ori + (.Log10(VAL(.DATA.Cell(i - 1 , j))) - .XAxis.Min) * _
                                    .XAxis.ScaleFactor
                            END IF

                            IF .YAxis.LogScale = FALSE THEN
                                y1 = .YAxis.Ori - [VAL(.DATA.Cell(i , j)) - .YAxis.Min] * .YAxis.ScaleFactor
                            ELSE
                                y1 = .YAxis.Ori - (.Log10(VAL(.DATA.Cell(i , j))) - .YAxis.Min) * _
                                    .YAxis.ScaleFactor
                            END IF
                            .DrawMarker(x1 , y1 , .Series(i \ 2).Marker , .Series(i \ 2).Color)
                            NoPlotXYPt :
                        NEXT j
                    NEXT i
                END WITH

            CASE csLines
                WITH QChart
                    SetBkColor(.Buffer.Handle , .PlotAreaColor)
                    FOR i = 2 TO .DATA.ColCount STEP 2
                        .hPen = CreatePen(.Series(i \ 2).LineStyle , .Series(i \ 2).LineWidth , .Series(i \ 2).Color)
                        .OldPen = SelectObject(.Buffer.Handle , .hPen)
                        FOR j = 1 TO .DATA.RowCount - 1

                            IF .DATA.Cell(i - 1 , j) = .Missing OR .DATA.Cell(i - 1 , j + 1) = .Missing _  'If data missing
                                THEN GOTO NoPlotXYLn
                            IF .DATA.Cell(i , j) = .Missing OR .DATA.Cell(i , j + 1) = .Missing _
                                THEN GOTO NoPlotXYLn

                            IF .XAxis.LogScale = FALSE THEN
                                x1 = [VAL(.DATA.Cell(i - 1 , j)) - .XAxis.Min] * .XAxis.ScaleFactor
                                x2 = [VAL(.DATA.Cell(i - 1 , j + 1)) - .XAxis.Min] * .XAxis.ScaleFactor
                            ELSE
                                x1 = [.Log10(VAL(.DATA.Cell(i - 1 , j))) - .XAxis.Min] * .XAxis.ScaleFactor
                                x2 = [.Log10(VAL(.DATA.Cell(i - 1 , j + 1))) - .XAxis.Min] * .XAxis.ScaleFactor
                            END IF

                            IF .YAxis.LogScale = FALSE THEN
                                y1 = [VAL(.DATA.Cell(i , j)) - .YAxis.Min] * .YAxis.ScaleFactor
                                y2 = [VAL(.DATA.Cell(i , j + 1)) - .YAxis.Min] * .YAxis.ScaleFactor
                            ELSE
                                y1 = [.Log10(VAL(.DATA.Cell(i , j))) - .YAxis.Min] * .YAxis.ScaleFactor
                                y2 = [.Log10(VAL(.DATA.Cell(i , j + 1))) - .YAxis.Min] * .YAxis.ScaleFactor
                            END IF

                            x1 = .XAxis.Ori + x1
                            y1 = .YAxis.Ori - y1
                            x2 = .XAxis.Ori + x2
                            y2 = .YAxis.Ori - y2

                            '--- Use API to draw lines
                            MoveToEx(.Buffer.Handle , x1 , y1 , 0)
                            LineTo(.Buffer.Handle , x2 , y2)
                            NoPlotXYLn :
                        NEXT j
                        DeleteObject(SelectObject(.Buffer.Handle , .OldPen))
                    NEXT i
                END WITH

            CASE csBoth
                WITH QChart
                    .ChartStyle = csPoints  'Draw Points
                    .DrawXY(FALSE) 'Draw Points (erase current)
                    .ChartStyle = csLines  'AND Lines
                    .DrawXY(TRUE) 'Overlay Lines (do NOT erase)
                    .ChartStyle = csBoth  'Reset ChartStyle for repaints
                END WITH

        END SELECT
        QChart.ChartExists = TRUE

    END SUB
    '---------------------------------------------------------------------------------------
    PRIVATE :
    SUB DrawLine(Overlay AS INTEGER)
        'X Points are (OriX + VAL * XScaleFactor - XMin) (ScaleFactor = Axis.Len / Axis.Max)
        'Y Points are (OriY - VAL * YScaleFactor - YMin) (i.e.^^ = Pixels per Unit)

        DIM i AS INTEGER  'Loop counters...
        DIM j AS INTEGER
        DIM x1 AS SINGLE  'for readability
        DIM y1 AS SINGLE
        DIM x2 AS SINGLE
        DIM y2 AS SINGLE

        IF Overlay = FALSE THEN
            WITH QChart  'Set up the chart window
                .ClearBuffer  'erase the current bitmap
                .SetSize
                .SetScale
                IF .Success = FALSE THEN  'Log Scaling failed
                    .ClearAll
                    EXIT SUB
                END IF
                .SetSeries
                .XAxis.Div = .DATA.RowCount - 1  'Forces a grid line for each X Label
                .XAxis.DrawZero = FALSE  'No Values on the X
                .DrawAxes  'in DrawAxes Sub
                .DrawTitles
                .DrawLabels
                .DrawLegend
            END WITH
        END IF

        SELECT CASE QChart.ChartStyle

            CASE csPoints
                WITH QChart
                    FOR i = 1 TO .DATA.ColCount
                        FOR j = 1 TO .DATA.RowCount

                            IF .DATA.Cell(i , j) = .Missing THEN GOTO NoPlotLinePt  'If data missing

                            x1 = .XAxis.Ori + (j - 1) * .Xaxis.TicIntvl
                            IF .YAxis.LogScale = FALSE THEN
                                y1 = .YAxis.Ori - [VAL(.DATA.Cell(i , j)) - .YAxis.Min] * .YAxis.ScaleFactor
                            ELSE
                                y1 = .YAxis.Ori - [.Log10(VAL(.DATA.Cell(i , j))) - .YAxis.Min] * .YAxis.ScaleFactor
                            END IF
                            .DrawMarker(x1 , y1 , .Series(i).Marker , .Series(i).Color)
                            NoPlotLinePt :
                        NEXT j
                    NEXT i
                END WITH

            CASE csLines
                WITH QChart
                    SetBkColor(.Buffer.Handle , .PlotAreaColor)
                    FOR i = 1 TO .DATA.ColCount
                        .hPen = CreatePen(.Series(i).LineStyle , .Series(i).LineWidth , .Series(i).Color)
                        .OldPen = SelectObject(.Buffer.Handle , .hPen)
                        FOR j = 1 TO .DATA.RowCount - 1

                            IF .DATA.Cell(i , j) = .Missing OR .DATA.Cell(i , j + 1) = .Missing _  'If data missing
                                THEN GOTO NoPlotLineLn

                            x1 = .XAxis.Ori + (j - 1) * .Xaxis.TicIntvl
                            x2 = .XAxis.Ori + (j) * .Xaxis.TicIntvl
                            IF .YAxis.LogScale = FALSE THEN
                                y1 = .YAxis.Ori - [VAL(.DATA.Cell(i , j)) - .YAxis.Min] * .YAxis.ScaleFactor
                                y2 = .YAxis.Ori - [VAL(.DATA.Cell(i , j + 1)) - .YAxis.Min] * .YAxis.ScaleFactor
                            ELSE
                                y1 = .YAxis.Ori - [.Log10(VAL(.DATA.Cell(i , j))) - .YAxis.Min] * .YAxis.ScaleFactor
                                y2 = .YAxis.Ori - [.Log10(VAL(.DATA.Cell(i , j + 1))) - .YAxis.Min] * .YAxis.ScaleFactor
                            END IF

                            '--- Use API to draw lines
                            MoveToEx(.Buffer.Handle , x1 , y1 , 0)
                            LineTo(.Buffer.Handle , x2 , y2)
                            NoPlotLineLn :
                        NEXT j
                        DeleteObject(SelectObject(.Buffer.Handle , .OldPen))
                    NEXT i

                END WITH

            CASE csBoth
                WITH QChart
                    .ChartStyle = csPoints  'Draw Points
                    .DrawLine(FALSE) 'Draw Points (erase current)
                    .ChartStyle = csLines  'AND Lines
                    .DrawLine(TRUE) 'Overlay Lines (do NOT erase)
                    .ChartStyle = csBoth  'Reset ChartStyle for repaints
                END WITH

        END SELECT
        QChart.ChartExists = TRUE

    END SUB
    '---------------------------------------------------------------------------------------
    PRIVATE :
    SUB DrawBox(Overlay AS INTEGER)

        'X Points are (OriX + VAL * XScaleFactor - XMin) (ScaleFactor = Axis.Len / Axis.Max)
        'Y Points are (OriY - VAL * YScaleFactor - YMin) (i.e.^^ = Pixels per Unit)

        DIM i AS INTEGER  'Loop counters...
        DIM j AS INTEGER
        DIM x1 AS SINGLE  'for readability
        DIM y1 AS SINGLE
        DIM x2 AS SINGLE
        DIM y2 AS SINGLE
        DIM open1 AS SINGLE
        DIM high1 AS SINGLE
        DIM low1 AS SINGLE
        DIM close1 AS SINGLE
        DIM volume1 AS SINGLE
        DIM open2 AS SINGLE
        DIM high2 AS SINGLE
        DIM low2 AS SINGLE
        DIM close2 AS SINGLE
        DIM volume2 AS SINGLE
        DIM XIntvl AS SINGLE  'Distance between plots
        DIM LinWidth AS LONG  'Width od Mid Line
        DIM LinColor AS LONG  'Change for Hi-Lo
        DIM BoxWidth AS LONG  'Width of bars

        IF Overlay = FALSE THEN
            WITH QChart  'Set up the chart window
                .ClearBuffer  'erase the current bitmap

                .SetSize
                .SetScale
                IF .Success = FALSE THEN  'Log Scaling failed
                    .ClearAll
                    EXIT SUB
                END IF
                .SetSeries
                .Xaxis.Div = .DATA.ColCount
                .XAxis.DrawZero = FALSE  'No Values on the X
                .DrawAxes
                .DrawTitles
                .DrawLabels
                .DrawLegend
            END WITH
        END IF

        WITH QChart

	    XIntvl = .XAxis.LEN / .DATA.ColCount
            LinWidth = XIntvl * .75            
            BoxWidth = LinWidth * .75 

            SELECT CASE charttypecomboindex

                CASE 0 :

                    FOR i = 1 TO .DATA.ColCount

                        '--- Draw Min - Max Line (Whiskers)
                        x1 = .XAxis.Ori + XIntvl * (i - 1)' + XIntvl / 2
                        x2 = x1
                        IF .YAxis.LogScale = FALSE THEN
                            y1 = .YAxis.Ori - [VAL(.DATA.Cell(i , 5)) - .YAxis.Min] * .YAxis.ScaleFactor  'Min
                            y2 = .YAxis.Ori - [VAL(.DATA.Cell(i , 1)) - .YAxis.Min] * .YAxis.ScaleFactor  'Max
                        ELSEIF .YAxis.LogScale = TRUE THEN
                            y1 = .YAxis.Ori - [.Log10(VAL(.DATA.Cell(i , 5))) - .YAxis.Min] * .YAxis.ScaleFactor  'Min
                            y2 = .YAxis.Ori - [.Log10(VAL(.DATA.Cell(i , 1))) - .YAxis.Min] * .YAxis.ScaleFactor  'Max

                        END IF

                        IF i = clickedbarnb THEN
                            .Buffer.Line(x1 , y1 , x2 , y2 , green)

                        ELSE
                            .Buffer.Line(x1 , y1 , x2 , y2 , .fgColor)
                        END IF
                        '.Buffer.Line (x1 - LinWidth / 4 , y1 , x2 + LinWidth / 4 , y1 , .fgColor)
                        '.Buffer.Line (x1 - LinWidth / 4 , y2 , x2 + LinWidth / 4 , y2 , .fgColor)

                        '--- Draw Quartile Box
                        x1 = x1 - BoxWidth/2
                        x2 = x1 + BoxWidth+1
                        IF .YAxis.LogScale = FALSE THEN
                            y1 = .YAxis.Ori - [VAL(.DATA.Cell(i , 4)) - .YAxis.Min] * .YAxis.ScaleFactor + 1  'Q1
                            y2 = .YAxis.Ori - [VAL(.DATA.Cell(i , 2)) - .YAxis.Min] * .YAxis.ScaleFactor  'Q3
                        ELSEIF .YAxis.LogScale = TRUE THEN
                            y1 = .YAxis.Ori - [.Log10(VAL(.DATA.Cell(i , 4))) - .YAxis.Min] * .YAxis.ScaleFactor + 1  'Q1
                            y2 = .YAxis.Ori - [.Log10(VAL(.DATA.Cell(i , 2))) - .YAxis.Min] * .YAxis.ScaleFactor  'Q3

                        END IF

                        IF .Series(i).HatchStyle = hsSolid THEN
                            .hBrush = CreateSolidBrush(.Series(i).Color)
                        ELSE
                            .hBrush = CreateHatchBrush(.Series(i).HatchStyle , .Series(i).Color)
                        END IF
                        .OldBrush = SelectObject(.Buffer.Handle , .hBrush)

                        Rectangle(.Buffer.Handle , x1 , y1 , x2+1 , y2)
                        if i=.DATA.ColCount then 
                        lastpricey=y2
                        lastpricex=x2+1
                        end if
                        DeleteObject(SelectObject(.Buffer.Handle , .OldBrush))

                        '--- Draw Median Line
                        'x1 = .XAxis.Ori + XIntvl * (i-1) + XIntvl / 2 - LinWidth / 2
                        'x2 = x1 + LinWidth + 1
                        'IF .YAxis.LogScale = FALSE THEN
                        'y1 = .YAxis.Ori -[VAL(.Data.Cell(i,3))-.YAxis.Min]* .YAxis.ScaleFactor          'Q2
                        'ELSE
                        'y1 = .YAxis.Ori -[.Log10(VAL(.Data.Cell(i,3)))-.YAxis.Min]* .YAxis.ScaleFactor  'Q2
                        'END IF

                        'y2 = y1
                        'IF .ChartStyle = csHiLo THEN LinColor = .Series(i).Color ELSE LinColor = .Colors(12)
                        'IF .GreyScale = TRUE THEN LinColor = .Colors(21)
                        'IF .Series(i).HatchStyle = hsSolid THEN
                        '.hBrush = CreateSolidBrush(LinColor)
                        'ELSE
                        '.hBrush = CreateHatchBrush(.Series(i).HatchStyle, LinColor)
                        'END IF
                        '.OldBrush = SelectObject(.Buffer.Handle, .hBrush)
                        'Rectangle (.Buffer.Handle,x1,y1+1,x2+1,y2-2)
                        'DeleteObject(SelectObject(.Buffer.Handle, .OldBrush))
                        'doevents
                    NEXT i

                CASE 1 :
                    FOR i = 1 TO .DATA.ColCount
                        '--- Draw Min - Max Line (Whiskers)
                        x1 = .XAxis.Ori + XIntvl * (i - 1) + XIntvl / 2
                        x2 = .XAxis.Ori + XIntvl * (i + 1 - 1) + XIntvl / 2
                        'IF .YAxis.LogScale = FALSE THEN
                        'y1 = .YAxis.Ori -[VAL(.Data.Cell(i,5))-.YAxis.Min]* .YAxis.ScaleFactor 'Min
                        'y2 = .YAxis.Ori -[VAL(.Data.Cell(i,1))-.YAxis.Min]* .YAxis.ScaleFactor 'Max
                        'ELSE
                        'y1 = .YAxis.Ori -[.Log10(VAL(.Data.Cell(i,5)))-.YAxis.Min]* .YAxis.ScaleFactor 'Min
                        'y2 = .YAxis.Ori -[.Log10(VAL(.Data.Cell(i,1)))-.YAxis.Min]* .YAxis.ScaleFactor 'Max
                        'END IF
                        '.Buffer.Line (x1 , y1 , x2 , y2 , .fgColor)
                        '.Buffer.Line (x1 - LinWidth / 4 , y1 , x2 + LinWidth / 4 , y1 , .fgColor)
                        '.Buffer.Line (x1 - LinWidth / 4 , y2 , x2 + LinWidth / 4 , y2 , .fgColor)

                        '--- Draw Quartile Box
                        'x1 = x1 - BoxWidth / 2
                        'x2 = x2 + BoxWidth + 1
                        IF .YAxis.LogScale = FALSE THEN
                            y1 = .YAxis.Ori - [VAL(.DATA.Cell(i , 4)) - .YAxis.Min] * .YAxis.ScaleFactor + 1  'Q1
                            y2 = .YAxis.Ori - [VAL(.DATA.Cell(i + 1 , 4)) - .YAxis.Min] * .YAxis.ScaleFactor  'Q3
                            'ELSE
                            'y1 = .YAxis.Ori -[.Log10(VAL(.Data.Cell(i,4)))-.YAxis.Min]* .YAxis.ScaleFactor + 1 'Q1
                            'y2 = .YAxis.Ori -[.Log10(VAL(.Data.Cell(i,2)))-.YAxis.Min]* .YAxis.ScaleFactor     'Q3
                        END IF
                        IF .Series(i).HatchStyle = hsSolid THEN
                            .hBrush = CreateSolidBrush(.Series(i).Color)
                        ELSE
                            .hBrush = CreateHatchBrush(.Series(i).HatchStyle , .Series(i).Color)
                        END IF
                        .OldBrush = SelectObject(.Buffer.Handle , .hBrush)
                        IF i < .DATA.ColCount THEN
                            .Buffer.Line(x1 , y1 , x2 , y2 , .fgColor)
                        END IF
                        'Rectangle (.Buffer.Handle,x1,y1,x2+1,y2)
                        DeleteObject(SelectObject(.Buffer.Handle , .OldBrush))

                        '--- Draw Median Line
                        'x1 = .XAxis.Ori + XIntvl * (i-1) + XIntvl / 2 - LinWidth / 2
                        'x2 = x1 + LinWidth + 1
                        'IF .YAxis.LogScale = FALSE THEN
                        'y1 = .YAxis.Ori -[VAL(.Data.Cell(i,3))-.YAxis.Min]* .YAxis.ScaleFactor          'Q2
                        'ELSE
                        'y1 = .YAxis.Ori -[.Log10(VAL(.Data.Cell(i,3)))-.YAxis.Min]* .YAxis.ScaleFactor  'Q2
                        'END IF
                        'y2 = y1
                        'IF .ChartStyle = csHiLo THEN LinColor = .Series(i).Color ELSE LinColor = .Colors(12)
                        'IF .GreyScale = TRUE THEN LinColor = .Colors(21)
                        'IF .Series(i).HatchStyle = hsSolid THEN
                        '.hBrush = CreateSolidBrush(LinColor)
                        'ELSE
                        '.hBrush = CreateHatchBrush(.Series(i).HatchStyle, LinColor)
                        'END IF
                        '.OldBrush = SelectObject(.Buffer.Handle, .hBrush)
                        ''Rectangle (.Buffer.Handle,x1,y1+1,x2+1,y2-2)
                        'DeleteObject(SelectObject(.Buffer.Handle, .OldBrush))
                        'doevents
                    NEXT i

                CASE 2 :
                    FOR i = 1 TO .DATA.ColCount
                        '--- Draw Min - Max Line (Whiskers)
                        x1 = .XAxis.Ori + XIntvl * (i - 1) + XIntvl / 2
                        'x2 = .XAxis.Ori + XIntvl * (i+1-1) + XIntvl / 2
                        'IF .YAxis.LogScale = FALSE THEN
                        'y1 = .YAxis.Ori -[VAL(.Data.Cell(i,5))-.YAxis.Min]* .YAxis.ScaleFactor 'Min
                        'y2 = .YAxis.Ori -[VAL(.Data.Cell(i,1))-.YAxis.Min]* .YAxis.ScaleFactor 'Max
                        'ELSE
                        'y1 = .YAxis.Ori -[.Log10(VAL(.Data.Cell(i,5)))-.YAxis.Min]* .YAxis.ScaleFactor 'Min
                        'y2 = .YAxis.Ori -[.Log10(VAL(.Data.Cell(i,1)))-.YAxis.Min]* .YAxis.ScaleFactor 'Max
                        'END IF
                        '.Buffer.Line (x1 , y1 , x2 , y2 , .fgColor)
                        '.Buffer.Line (x1 - LinWidth / 4 , y1 , x2 + LinWidth / 4 , y1 , .fgColor)
                        '.Buffer.Line (x1 - LinWidth / 4 , y2 , x2 + LinWidth / 4 , y2 , .fgColor)

                        '--- Draw Quartile Box
                        'x1 = x1 - BoxWidth / 2
                        'x2 = x2 + BoxWidth + 1
                        IF .YAxis.LogScale = FALSE THEN
                            y1 = .YAxis.Ori - [VAL(.DATA.Cell(i , 4)) - .YAxis.Min] * .YAxis.ScaleFactor + 1  'Q1
                            y2 = .YAxis.Ori - [VAL(.DATA.Cell(i + 1 , 4)) - .YAxis.Min] * .YAxis.ScaleFactor  'Q3
                            'ELSE
                            'y1 = .YAxis.Ori -[.Log10(VAL(.Data.Cell(i,4)))-.YAxis.Min]* .YAxis.ScaleFactor + 1 'Q1
                            'y2 = .YAxis.Ori -[.Log10(VAL(.Data.Cell(i,2)))-.YAxis.Min]* .YAxis.ScaleFactor     'Q3
                        END IF
                        IF .Series(i).HatchStyle = hsSolid THEN
                            .hBrush = CreateSolidBrush(.Series(i).Color)
                        ELSE
                            .hBrush = CreateHatchBrush(.Series(i).HatchStyle , .Series(i).Color)
                        END IF
                        .OldBrush = SelectObject(.Buffer.Handle , .hBrush)
                        .Buffer.Pset(x1 , y1 , .fgColor)
                        .Buffer.Pset(x1 - 1 , y1 , .fgColor)
                        .Buffer.Pset(x1 - 1 , y1 + 1 , .fgColor)
                        .Buffer.Pset(x1 , y1 + 1 , .fgColor)
                        .Buffer.Pset(x1 + 1 , y1 + 1 , .fgColor)
                        .Buffer.Pset(x1 + 1 , y1 , .fgColor)
                        .Buffer.Pset(x1 + 1 , y1 - 1 , .fgColor)
                        .Buffer.Pset(x1 , y1 - 1 , .fgColor)
                        .Buffer.Pset(x1 - 1 , y1 - 1 , .fgColor)
                        'Rectangle (.Buffer.Handle,x1,y1,x2+1,y2)
                        DeleteObject(SelectObject(.Buffer.Handle , .OldBrush))

                        '--- Draw Median Line
                        'x1 = .XAxis.Ori + XIntvl * (i-1) + XIntvl / 2 - LinWidth / 2
                        'x2 = x1 + LinWidth + 1
                        'IF .YAxis.LogScale = FALSE THEN
                        'y1 = .YAxis.Ori -[VAL(.Data.Cell(i,3))-.YAxis.Min]* .YAxis.ScaleFactor          'Q2
                        'ELSE
                        'y1 = .YAxis.Ori -[.Log10(VAL(.Data.Cell(i,3)))-.YAxis.Min]* .YAxis.ScaleFactor  'Q2
                        'END IF
                        'y2 = y1
                        'IF .ChartStyle = csHiLo THEN LinColor = .Series(i).Color ELSE LinColor = .Colors(12)
                        'IF .GreyScale = TRUE THEN LinColor = .Colors(21)
                        'IF .Series(i).HatchStyle = hsSolid THEN
                        '.hBrush = CreateSolidBrush(LinColor)
                        'ELSE
                        '.hBrush = CreateHatchBrush(.Series(i).HatchStyle, LinColor)
                        'END IF
                        '.OldBrush = SelectObject(.Buffer.Handle, .hBrush)
                        ''Rectangle (.Buffer.Handle,x1,y1+1,x2+1,y2-2)
                        'DeleteObject(SelectObject(.Buffer.Handle, .OldBrush))
                        'doevents
                    NEXT i

                CASE 3 :
                    FOR i = 1 TO .DATA.ColCount
                        '--- Draw Min - Max Line (Whiskers)
                        x1 = .XAxis.Ori + XIntvl * (i - 1) + XIntvl / 2
                        x2 = x1
                        IF .YAxis.LogScale = FALSE THEN
                            y1 = .YAxis.Ori - [VAL(.DATA.Cell(i , 5)) - .YAxis.Min] * .YAxis.ScaleFactor  'Min
                            y2 = .YAxis.Ori - [VAL(.DATA.Cell(i , 1)) - .YAxis.Min] * .YAxis.ScaleFactor  'Max
                        ELSE
                            y1 = .YAxis.Ori - [.Log10(VAL(.DATA.Cell(i , 5))) - .YAxis.Min] * .YAxis.ScaleFactor  'Min
                            y2 = .YAxis.Ori - [.Log10(VAL(.DATA.Cell(i , 1))) - .YAxis.Min] * .YAxis.ScaleFactor  'Max
                        END IF
                        .Buffer.Line(x1 , y1 , x2 , y2 , .fgColor)
                        '.Buffer.Line (x1 - LinWidth / 4 , y1 , x2 + LinWidth / 4 , y1 , .fgColor)
                        '.Buffer.Line (x1 - LinWidth / 4 , y2 , x2 + LinWidth / 4 , y2 , .fgColor)

                        '--- Draw Quartile Box
                        x1 = x1 - BoxWidth / 1.75
                        x2 = x1 + BoxWidth / 1.75
                        IF .YAxis.LogScale = FALSE THEN
                            y1 = .YAxis.Ori - [VAL(.DATA.Cell(i , 4)) - .YAxis.Min] * .YAxis.ScaleFactor + 1  'Q1
                            y2 = .YAxis.Ori - [VAL(.DATA.Cell(i , 2)) - .YAxis.Min] * .YAxis.ScaleFactor  'Q3
                        ELSE
                            y1 = .YAxis.Ori - [.Log10(VAL(.DATA.Cell(i , 4))) - .YAxis.Min] * .YAxis.ScaleFactor + 1  'Q1
                            y2 = .YAxis.Ori - [.Log10(VAL(.DATA.Cell(i , 2))) - .YAxis.Min] * .YAxis.ScaleFactor  'Q3
                        END IF
                        IF .Series(i).HatchStyle = hsSolid THEN
                            .hBrush = CreateSolidBrush(.Series(i).Color)
                        ELSE
                            .hBrush = CreateHatchBrush(.Series(i).HatchStyle , .Series(i).Color)
                        END IF
                        .OldBrush = SelectObject(.Buffer.Handle , .hBrush)
                        'Rectangle (.Buffer.Handle,x1,y1,x2+1,y2)
                        .buffer.Line(x1 , y1 , x2 , y1 , .fgColor)
                        .buffer.Line(x2 , y2 , x2 + BoxWidth / 1.75 , y2 , .fgColor)
                        DeleteObject(SelectObject(.Buffer.Handle , .OldBrush))

                        '--- Draw Median Line
                        'x1 = .XAxis.Ori + XIntvl * (i-1) + XIntvl / 2 - LinWidth / 2
                        'x2 = x1 + LinWidth + 1
                        'IF .YAxis.LogScale = FALSE THEN
                        'y1 = .YAxis.Ori -[VAL(.Data.Cell(i,3))-.YAxis.Min]* .YAxis.ScaleFactor          'Q2
                        'ELSE
                        'y1 = .YAxis.Ori -[.Log10(VAL(.Data.Cell(i,3)))-.YAxis.Min]* .YAxis.ScaleFactor  'Q2
                        'END IF
                        'y2 = y1
                        'IF .ChartStyle = csHiLo THEN LinColor = .Series(i).Color ELSE LinColor = .Colors(12)
                        'IF .GreyScale = TRUE THEN LinColor = .Colors(21)
                        'IF .Series(i).HatchStyle = hsSolid THEN
                        '.hBrush = CreateSolidBrush(LinColor)
                        'ELSE
                        '.hBrush = CreateHatchBrush(.Series(i).HatchStyle, LinColor)
                        'END IF
                        '.OldBrush = SelectObject(.Buffer.Handle, .hBrush)
                        'Rectangle (.Buffer.Handle,x1,y1+1,x2+1,y2-2)
                        'DeleteObject(SelectObject(.Buffer.Handle, .OldBrush))
                        'doevents
                    NEXT i

                CASE 4 :
                    FOR i = 1 TO .DATA.ColCount
                        '--- Draw Min - Max Line (Whiskers)
                        x1 = .XAxis.Ori + XIntvl * (i - 1) + XIntvl / 2
                        x2 = .XAxis.Ori + XIntvl * (i + 1 - 1) + XIntvl / 2
                        'IF .YAxis.LogScale = FALSE THEN
                        'y1 = .YAxis.Ori -[VAL(.Data.Cell(i,5))-.YAxis.Min]* .YAxis.ScaleFactor 'Min
                        'y2 = .YAxis.Ori -[VAL(.Data.Cell(i,1))-.YAxis.Min]* .YAxis.ScaleFactor 'Max
                        'ELSE
                        'y1 = .YAxis.Ori -[.Log10(VAL(.Data.Cell(i,5)))-.YAxis.Min]* .YAxis.ScaleFactor 'Min
                        'y2 = .YAxis.Ori -[.Log10(VAL(.Data.Cell(i,1)))-.YAxis.Min]* .YAxis.ScaleFactor 'Max
                        'END IF
                        '.Buffer.Line (x1 , y1 , x2 , y2 , .fgColor)
                        '.Buffer.Line (x1 - LinWidth / 4 , y1 , x2 + LinWidth / 4 , y1 , .fgColor)
                        '.Buffer.Line (x1 - LinWidth / 4 , y2 , x2 + LinWidth / 4 , y2 , .fgColor)

                        '--- Draw Quartile Box
                        'x1 = x1 - BoxWidth / 2
                        'x2 = x2 + BoxWidth + 1
                        IF .YAxis.LogScale = FALSE THEN
                            high1 = .YAxis.Ori - [VAL(.DATA.Cell(i , 1)) - .YAxis.Min] * .YAxis.ScaleFactor + 1  'Q1
                            high2 = .YAxis.Ori - [VAL(.DATA.Cell(i + 1 , 1)) - .YAxis.Min] * .YAxis.ScaleFactor  'Q3
                            low1 = .YAxis.Ori - [VAL(.DATA.Cell(i , 5)) - .YAxis.Min] * .YAxis.ScaleFactor + 1  'Q1
                            low2 = .YAxis.Ori - [VAL(.DATA.Cell(i + 1 , 5)) - .YAxis.Min] * .YAxis.ScaleFactor  'Q3
                            open1 = .YAxis.Ori - [VAL(.DATA.Cell(i , 2)) - .YAxis.Min] * .YAxis.ScaleFactor + 1  'Q1
                            open2 = .YAxis.Ori - [VAL(.DATA.Cell(i + 1 , 2)) - .YAxis.Min] * .YAxis.ScaleFactor  'Q3
                            close1 = .YAxis.Ori - [VAL(.DATA.Cell(i , 4)) - .YAxis.Min] * .YAxis.ScaleFactor + 1  'Q1
                            close2 = .YAxis.Ori - [VAL(.DATA.Cell(i + 1 , 4)) - .YAxis.Min] * .YAxis.ScaleFactor  'Q3
                            'ELSE
                            'y1 = .YAxis.Ori -[.Log10(VAL(.Data.Cell(i,4)))-.YAxis.Min]* .YAxis.ScaleFactor + 1 'Q1
                            'y2 = .YAxis.Ori -[.Log10(VAL(.Data.Cell(i,2)))-.YAxis.Min]* .YAxis.ScaleFactor     'Q3
                        END IF
                        IF .Series(i).HatchStyle = hsSolid THEN
                            .hBrush = CreateSolidBrush(.Series(i).Color)
                        ELSE
                            .hBrush = CreateHatchBrush(.Series(i).HatchStyle , .Series(i).Color)
                        END IF
                        .OldBrush = SelectObject(.Buffer.Handle , .hBrush)
                        IF i < .DATA.ColCount THEN
                            .Buffer.Line(x1 , high1 , x2 , high2 , .fgColor)
                            .Buffer.Line(x1 , low1 , x2 , low2 , .fgColor)
                            .Buffer.Line(x1 , open1 , x2 , open2 , .colors(3))
                            .Buffer.Line(x1 , close1 , x2 , close2 , .colors(2))
                        END IF
                        'Rectangle (.Buffer.Handle,x1,y1,x2+1,y2)
                        DeleteObject(SelectObject(.Buffer.Handle , .OldBrush))

                        '--- Draw Median Line
                        'x1 = .XAxis.Ori + XIntvl * (i-1) + XIntvl / 2 - LinWidth / 2
                        'x2 = x1 + LinWidth + 1
                        'IF .YAxis.LogScale = FALSE THEN
                        'y1 = .YAxis.Ori -[VAL(.Data.Cell(i,3))-.YAxis.Min]* .YAxis.ScaleFactor          'Q2
                        'ELSE
                        'y1 = .YAxis.Ori -[.Log10(VAL(.Data.Cell(i,3)))-.YAxis.Min]* .YAxis.ScaleFactor  'Q2
                        'END IF
                        'y2 = y1
                        'IF .ChartStyle = csHiLo THEN LinColor = .Series(i).Color ELSE LinColor = .Colors(12)
                        'IF .GreyScale = TRUE THEN LinColor = .Colors(21)
                        'IF .Series(i).HatchStyle = hsSolid THEN
                        '.hBrush = CreateSolidBrush(LinColor)
                        'ELSE
                        '.hBrush = CreateHatchBrush(.Series(i).HatchStyle, LinColor)
                        'END IF
                        '.OldBrush = SelectObject(.Buffer.Handle, .hBrush)
                        ''Rectangle (.Buffer.Handle,x1,y1+1,x2+1,y2-2)
                        'DeleteObject(SelectObject(.Buffer.Handle, .OldBrush))
                        'doevents
                    NEXT i

                CASE 5 :
                    FOR i = 1 TO .DATA.ColCount
                        '--- Draw Min - Max Line (Whiskers)
                        x1 = .XAxis.Ori + XIntvl * (i - 1) + XIntvl / 2
                        x2 = .XAxis.Ori + XIntvl * (i + 1 - 1) + XIntvl / 2
                        'IF .YAxis.LogScale = FALSE THEN
                        'y1 = .YAxis.Ori -[VAL(.Data.Cell(i,5))-.YAxis.Min]* .YAxis.ScaleFactor 'Min
                        'y2 = .YAxis.Ori -[VAL(.Data.Cell(i,1))-.YAxis.Min]* .YAxis.ScaleFactor 'Max
                        'ELSE
                        'y1 = .YAxis.Ori -[.Log10(VAL(.Data.Cell(i,5)))-.YAxis.Min]* .YAxis.ScaleFactor 'Min
                        'y2 = .YAxis.Ori -[.Log10(VAL(.Data.Cell(i,1)))-.YAxis.Min]* .YAxis.ScaleFactor 'Max
                        'END IF
                        '.Buffer.Line (x1 , y1 , x2 , y2 , .fgColor)
                        '.Buffer.Line (x1 - LinWidth / 4 , y1 , x2 + LinWidth / 4 , y1 , .fgColor)
                        '.Buffer.Line (x1 - LinWidth / 4 , y2 , x2 + LinWidth / 4 , y2 , .fgColor)

                        '--- Draw Quartile Box
                        'x1 = x1 - BoxWidth / 2
                        'x2 = x2 + BoxWidth + 1
                        IF .YAxis.LogScale = FALSE THEN
                            high1 = .YAxis.Ori - [VAL(.DATA.Cell(i , 1)) - .YAxis.Min] * .YAxis.ScaleFactor + 1  'Q1
                            'high2 = .YAxis.Ori -[VAL(.Data.Cell(i+1,1))-.YAxis.Min]* .YAxis.ScaleFactor     'Q3
                            low1 = .YAxis.Ori - [VAL(.DATA.Cell(i , 5)) - .YAxis.Min] * .YAxis.ScaleFactor + 1  'Q1
                            'low2 = .YAxis.Ori -[VAL(.Data.Cell(i+1,5))-.YAxis.Min]* .YAxis.ScaleFactor     'Q3
                            open1 = .YAxis.Ori - [VAL(.DATA.Cell(i , 2)) - .YAxis.Min] * .YAxis.ScaleFactor + 1  'Q1
                            'open2 = .YAxis.Ori -[VAL(.Data.Cell(i+1,2))-.YAxis.Min]* .YAxis.ScaleFactor     'Q3
                            close1 = .YAxis.Ori - [VAL(.DATA.Cell(i , 4)) - .YAxis.Min] * .YAxis.ScaleFactor + 1  'Q1
                            'close2 = .YAxis.Ori -[VAL(.Data.Cell(i+1,4))-.YAxis.Min]* .YAxis.ScaleFactor     'Q3
                            'ELSE
                            'y1 = .YAxis.Ori -[.Log10(VAL(.Data.Cell(i,4)))-.YAxis.Min]* .YAxis.ScaleFactor + 1 'Q1
                            'y2 = .YAxis.Ori -[.Log10(VAL(.Data.Cell(i,2)))-.YAxis.Min]* .YAxis.ScaleFactor     'Q3
                        END IF
                        IF .Series(i).HatchStyle = hsSolid THEN
                            .hBrush = CreateSolidBrush(.Series(i).Color)
                        ELSE
                            .hBrush = CreateHatchBrush(.Series(i).HatchStyle , .Series(i).Color)
                        END IF
                        .OldBrush = SelectObject(.Buffer.Handle , .hBrush)

                        .Buffer.Line(x1 , low1 , x1 , high1 , .fgColor)
                        .Buffer.Line(x1 - BoxWidth , close1 , x1 + BoxWidth , open1 , .fgColor)
                        IF open1 <= close1 THEN
                            .Buffer.Line(x1 - BoxWidth , close1 , x1 , low1 , .fgColor)
                            .Buffer.Line(x1 + BoxWidth , open1 , x1 , high1 , .fgColor)
                        END IF
                        IF open1 > close1 THEN
                            .Buffer.Line(x1 - BoxWidth , close1 , x1 , high1 , .fgColor)
                            .Buffer.Line(x1 + BoxWidth , open1 , x1 , low1 , .fgColor)
                        END IF

                        'Rectangle (.Buffer.Handle,x1,y1,x2+1,y2)
                        DeleteObject(SelectObject(.Buffer.Handle , .OldBrush))

                        '--- Draw Median Line
                        'x1 = .XAxis.Ori + XIntvl * (i-1) + XIntvl / 2 - LinWidth / 2
                        'x2 = x1 + LinWidth + 1
                        'IF .YAxis.LogScale = FALSE THEN
                        'y1 = .YAxis.Ori -[VAL(.Data.Cell(i,3))-.YAxis.Min]* .YAxis.ScaleFactor          'Q2
                        'ELSE
                        'y1 = .YAxis.Ori -[.Log10(VAL(.Data.Cell(i,3)))-.YAxis.Min]* .YAxis.ScaleFactor  'Q2
                        'END IF
                        'y2 = y1
                        'IF .ChartStyle = csHiLo THEN LinColor = .Series(i).Color ELSE LinColor = .Colors(12)
                        'IF .GreyScale = TRUE THEN LinColor = .Colors(21)
                        'IF .Series(i).HatchStyle = hsSolid THEN
                        '.hBrush = CreateSolidBrush(LinColor)
                        'ELSE
                        '.hBrush = CreateHatchBrush(.Series(i).HatchStyle, LinColor)
                        'END IF
                        '.OldBrush = SelectObject(.Buffer.Handle, .hBrush)
                        ''Rectangle (.Buffer.Handle,x1,y1+1,x2+1,y2-2)
                        'DeleteObject(SelectObject(.Buffer.Handle, .OldBrush))
                        'doevents
                    NEXT i

                CASE 6 :
                    FOR i = 1 TO .DATA.ColCount
                        '--- Draw Min - Max Line (Whiskers)
                        x1 = .XAxis.Ori + XIntvl * (i - 1) + XIntvl / 2
                        x2 = .XAxis.Ori + XIntvl * (i + 1 - 1) + XIntvl / 2
                        'IF .YAxis.LogScale = FALSE THEN
                        'y1 = .YAxis.Ori -[VAL(.Data.Cell(i,5))-.YAxis.Min]* .YAxis.ScaleFactor 'Min
                        'y2 = .YAxis.Ori -[VAL(.Data.Cell(i,1))-.YAxis.Min]* .YAxis.ScaleFactor 'Max
                        'ELSE
                        'y1 = .YAxis.Ori -[.Log10(VAL(.Data.Cell(i,5)))-.YAxis.Min]* .YAxis.ScaleFactor 'Min
                        'y2 = .YAxis.Ori -[.Log10(VAL(.Data.Cell(i,1)))-.YAxis.Min]* .YAxis.ScaleFactor 'Max
                        'END IF
                        '.Buffer.Line (x1 , y1 , x2 , y2 , .fgColor)
                        '.Buffer.Line (x1 - LinWidth / 4 , y1 , x2 + LinWidth / 4 , y1 , .fgColor)
                        '.Buffer.Line (x1 - LinWidth / 4 , y2 , x2 + LinWidth / 4 , y2 , .fgColor)

                        '--- Draw Quartile Box
                        'x1 = x1 - BoxWidth / 2
                        'x2 = x2 + BoxWidth + 1
                        IF .YAxis.LogScale = FALSE THEN
                            'high1 = .YAxis.Ori -[VAL(.Data.Cell(i,1))-.YAxis.Min]* .YAxis.ScaleFactor + 1 'Q1
                            'high2 = .YAxis.Ori -[VAL(.Data.Cell(i+1,1))-.YAxis.Min]* .YAxis.ScaleFactor     'Q3
                            'low1 = .YAxis.Ori -[VAL(.Data.Cell(i,5))-.YAxis.Min]* .YAxis.ScaleFactor + 1 'Q1
                            'low2 = .YAxis.Ori -[VAL(.Data.Cell(i+1,5))-.YAxis.Min]* .YAxis.ScaleFactor     'Q3
                            'open1 = .YAxis.Ori -[VAL(.Data.Cell(i,2))-.YAxis.Min]* .YAxis.ScaleFactor + 1 'Q1
                            'open2 = .YAxis.Ori -[VAL(.Data.Cell(i+1,2))-.YAxis.Min]* .YAxis.ScaleFactor     'Q3
                            close1 = .YAxis.Ori - [VAL(.DATA.Cell(i , 4)) - .YAxis.Min] * .YAxis.ScaleFactor + 1  'Q1
                            close2 = .YAxis.Ori - [VAL(.DATA.Cell(i - 1 , 4)) - .YAxis.Min] * .YAxis.ScaleFactor  'Q3
                            'ELSE
                            'y1 = .YAxis.Ori -[.Log10(VAL(.Data.Cell(i,4)))-.YAxis.Min]* .YAxis.ScaleFactor + 1 'Q1
                            'y2 = .YAxis.Ori -[.Log10(VAL(.Data.Cell(i,2)))-.YAxis.Min]* .YAxis.ScaleFactor     'Q3
                        END IF
                        IF .Series(i).HatchStyle = hsSolid THEN
                            .hBrush = CreateSolidBrush(.Series(i).Color)
                        ELSE
                            .hBrush = CreateHatchBrush(.Series(i).HatchStyle , .Series(i).Color)
                        END IF
                        .OldBrush = SelectObject(.Buffer.Handle , .hBrush)


                        .Buffer.Line(x1 - BoxWidth , close1 , x1 + BoxWidth , close1 , .fgColor)

                        .Buffer.Line(x1 - BoxWidth , close1 , x1 - BoxWidth , close2 , .fgColor)


                        'Rectangle (.Buffer.Handle,x1,y1,x2+1,y2)
                        DeleteObject(SelectObject(.Buffer.Handle , .OldBrush))

                        '--- Draw Median Line
                        'x1 = .XAxis.Ori + XIntvl * (i-1) + XIntvl / 2 - LinWidth / 2
                        'x2 = x1 + LinWidth + 1
                        'IF .YAxis.LogScale = FALSE THEN
                        'y1 = .YAxis.Ori -[VAL(.Data.Cell(i,3))-.YAxis.Min]* .YAxis.ScaleFactor          'Q2
                        'ELSE
                        'y1 = .YAxis.Ori -[.Log10(VAL(.Data.Cell(i,3)))-.YAxis.Min]* .YAxis.ScaleFactor  'Q2
                        'END IF
                        'y2 = y1
                        'IF .ChartStyle = csHiLo THEN LinColor = .Series(i).Color ELSE LinColor = .Colors(12)
                        'IF .GreyScale = TRUE THEN LinColor = .Colors(21)
                        'IF .Series(i).HatchStyle = hsSolid THEN
                        '.hBrush = CreateSolidBrush(LinColor)
                        'ELSE
                        '.hBrush = CreateHatchBrush(.Series(i).HatchStyle, LinColor)
                        'END IF
                        '.OldBrush = SelectObject(.Buffer.Handle, .hBrush)
                        ''Rectangle (.Buffer.Handle,x1,y1+1,x2+1,y2-2)
                        'DeleteObject(SelectObject(.Buffer.Handle, .OldBrush))
                        'doevents
                    NEXT i

                CASE 7 :
                    FOR i = 1 TO .DATA.ColCount
                        '--- Draw Min - Max Line (Whiskers)
                        x1 = .XAxis.Ori + XIntvl * (i - 1) + XIntvl / 2
                        x2 = .XAxis.Ori + XIntvl * (i + 1 - 1) + XIntvl / 2
                        'IF .YAxis.LogScale = FALSE THEN
                        'y1 = .YAxis.Ori -[VAL(.Data.Cell(i,5))-.YAxis.Min]* .YAxis.ScaleFactor 'Min
                        'y2 = .YAxis.Ori -[VAL(.Data.Cell(i,1))-.YAxis.Min]* .YAxis.ScaleFactor 'Max
                        'ELSE
                        'y1 = .YAxis.Ori -[.Log10(VAL(.Data.Cell(i,5)))-.YAxis.Min]* .YAxis.ScaleFactor 'Min
                        'y2 = .YAxis.Ori -[.Log10(VAL(.Data.Cell(i,1)))-.YAxis.Min]* .YAxis.ScaleFactor 'Max
                        'END IF
                        '.Buffer.Line (x1 , y1 , x2 , y2 , .fgColor)
                        '.Buffer.Line (x1 - LinWidth / 4 , y1 , x2 + LinWidth / 4 , y1 , .fgColor)
                        '.Buffer.Line (x1 - LinWidth / 4 , y2 , x2 + LinWidth / 4 , y2 , .fgColor)

                        '--- Draw Quartile Box
                        'x1 = x1 - BoxWidth / 2
                        'x2 = x2 + BoxWidth + 1
                        IF .YAxis.LogScale = FALSE THEN
                            'high1 = .YAxis.Ori -[VAL(.Data.Cell(i,1))-.YAxis.Min]* .YAxis.ScaleFactor + 1 'Q1
                            'high2 = .YAxis.Ori -[VAL(.Data.Cell(i+1,1))-.YAxis.Min]* .YAxis.ScaleFactor     'Q3
                            'low1 = .YAxis.Ori -[VAL(.Data.Cell(i,5))-.YAxis.Min]* .YAxis.ScaleFactor + 1 'Q1
                            'low2 = .YAxis.Ori -[VAL(.Data.Cell(i+1,5))-.YAxis.Min]* .YAxis.ScaleFactor     'Q3
                            'open1 = .YAxis.Ori -[VAL(.Data.Cell(i,2))-.YAxis.Min]* .YAxis.ScaleFactor + 1 'Q1
                            'open2 = .YAxis.Ori -[VAL(.Data.Cell(i+1,2))-.YAxis.Min]* .YAxis.ScaleFactor     'Q3
                            'close1 = .YAxis.Ori -[VAL(.Data.Cell(i,4))-.YAxis.Min]* .YAxis.ScaleFactor + 1 'Q1
                            'close2 = .YAxis.Ori -[VAL(.Data.Cell(i-1,4))-.YAxis.Min]* .YAxis.ScaleFactor     'Q3
                            'ELSE
                            'y1 = .YAxis.Ori -[.Log10(VAL(.Data.Cell(i,4)))-.YAxis.Min]* .YAxis.ScaleFactor + 1 'Q1
                            'y2 = .YAxis.Ori -[.Log10(VAL(.Data.Cell(i,2)))-.YAxis.Min]* .YAxis.ScaleFactor     'Q3
                        END IF
                        IF .Series(i).HatchStyle = hsSolid THEN
                            .hBrush = CreateSolidBrush(.Series(i).Color)
                        ELSE
                            .hBrush = CreateHatchBrush(.Series(i).HatchStyle , .Series(i).Color)
                        END IF
                        .OldBrush = SelectObject(.Buffer.Handle , .hBrush)


                        '.Buffer.Line (x1 - BoxWidth , close1 , x1 + BoxWidth , close1 , .fgColor)

                        '.Buffer.Line (x1 - BoxWidth , close1 , x1 - BoxWidth , close2 , .fgColor)


                        'Rectangle (.Buffer.Handle,x1,y1,x2+1,y2)
                        DeleteObject(SelectObject(.Buffer.Handle , .OldBrush))

                        '--- Draw Median Line
                        'x1 = .XAxis.Ori + XIntvl * (i-1) + XIntvl / 2 - LinWidth / 2
                        'x2 = x1 + LinWidth + 1
                        'IF .YAxis.LogScale = FALSE THEN
                        'y1 = .YAxis.Ori -[VAL(.Data.Cell(i,3))-.YAxis.Min]* .YAxis.ScaleFactor          'Q2
                        'ELSE
                        'y1 = .YAxis.Ori -[.Log10(VAL(.Data.Cell(i,3)))-.YAxis.Min]* .YAxis.ScaleFactor  'Q2
                        'END IF
                        'y2 = y1
                        'IF .ChartStyle = csHiLo THEN LinColor = .Series(i).Color ELSE LinColor = .Colors(12)
                        'IF .GreyScale = TRUE THEN LinColor = .Colors(21)
                        'IF .Series(i).HatchStyle = hsSolid THEN
                        '.hBrush = CreateSolidBrush(LinColor)
                        'ELSE
                        '.hBrush = CreateHatchBrush(.Series(i).HatchStyle, LinColor)
                        'END IF
                        '.OldBrush = SelectObject(.Buffer.Handle, .hBrush)
                        ''Rectangle (.Buffer.Handle,x1,y1+1,x2+1,y2-2)
                        'DeleteObject(SelectObject(.Buffer.Handle, .OldBrush))
                        'doevents
                    NEXT i

                    DIM angle AS DOUBLE , cs AS DOUBLE , sn AS DOUBLE , c AS DOUBLE
                    c = graphvspace * 0.5
                    'dim i as integer
                    DIM ratio AS DOUBLE
                    DIM x7 AS INTEGER
                    DIM y7 AS INTEGER
                    DIM closexarray(1 TO 1000) AS DOUBLE
                    DIM closeyarray(1 TO 1000) AS DOUBLE

                    i = 1

                    x7 = graphhbegin + graphhspace * 0.5
                    y7 = graphvbegin + graphvspace * 0.5

                    FOR angle = 0 TO 6.28 STEP 6.28 / .DATA.ColCount

                        IF (angle >= 1.57 AND angle < 3.14) THEN
                            'close1 = VAL(.Data.Cell(i-.Data.ColCount/4-1,4))
                            'ratio=(close1-graphvlow)/graphpricespace
                            close1 = .YAxis.Ori - [VAL(.DATA.Cell(i - .DATA.ColCount / 4 - 1 , 4)) - .YAxis.Min] * .YAxis.ScaleFactor + 1
                            ratio = (graphvspace - (close1 - graphvbegin)) / graphvspace
                            cs = c * ratio * COS(angle)
                            sn = c * ratio * SIN(angle)
                            '.buffer.line(x7,y7,x7-cs,y7-sn,pencolor)
                            closexarray(i) = x7 - cs
                            closeyarray(i) = y7 - sn
                            IF i - .DATA.ColCount / 4 - 1 > 1 THEN
                                .buffer.Line(closexarray(i) , closeyarray(i) , closexarray(i - 1) , closeyarray(i - 1) , pencolor)
                            END IF
                        END IF

                        i ++
                        'doevents
                    NEXT angle

                    i = 1

                    FOR angle = 6.28 TO 0 STEP - 6.28 / .DATA.ColCount

                        IF (angle >= 1.57 AND angle < 3.14) THEN
                            'close1 = VAL(.Data.Cell(i-.Data.ColCount/4-1,4))
                            'ratio=(close1-graphvlow)/graphpricespace
                            close1 = .YAxis.Ori - [VAL(.DATA.Cell(i - .DATA.ColCount / 4 - 1 , 4)) - .YAxis.Min] * .YAxis.ScaleFactor + 1
                            ratio = (graphvspace - (close1 - graphvbegin)) / graphvspace
                            cs = c * ratio * COS(angle)
                            sn = c * ratio * SIN(angle)
                            '.buffer.line(x7,y7,x7-cs,y7+sn,pencolor)
                            closexarray(i) = x7 - cs
                            closeyarray(i) = y7 + sn
                            .buffer.Line(closexarray(i) , closeyarray(i) , closexarray(i - 1) , closeyarray(i - 1) , pencolor)
                        END IF

                        i ++
                        'doevents
                    NEXT angle

                    i = 1

                    FOR angle = 6.28 TO 0 STEP - 6.28 / .DATA.ColCount

                        IF (angle >= 0 AND angle < 1.57) THEN
                            'close1 = VAL(.Data.Cell(i-.Data.ColCount/4-1,4))
                            'ratio=(close1-graphvlow)/graphpricespace
                            close1 = .YAxis.Ori - [VAL(.DATA.Cell(i - .DATA.ColCount / 4 - 1 , 4)) - .YAxis.Min] * .YAxis.ScaleFactor + 1
                            ratio = (graphvspace - (close1 - graphvbegin)) / graphvspace
                            cs = c * ratio * COS(angle)
                            sn = c * ratio * SIN(angle)
                            '.buffer.line(x7,y7,x7-cs,y7+sn,pencolor)
                            closexarray(i) = x7 - cs
                            closeyarray(i) = y7 + sn
                            .buffer.Line(closexarray(i) , closeyarray(i) , closexarray(i - 1) , closeyarray(i - 1) , pencolor)
                        END IF

                        i ++
                        'doevents
                    NEXT angle

                    i = 1

                    FOR angle = 0 TO 6.28 STEP 6.28 / .DATA.ColCount

                        IF (angle >= 0 AND angle < 1.57) THEN
                            'close1 = VAL(.Data.Cell(i+.Data.ColCount*0.75-1,4))
                            'ratio=(close1-graphvlow)/graphpricespace
                            close1 = .YAxis.Ori - [VAL(.DATA.Cell(i + .DATA.ColCount * 0.75 - 1 , 4)) - .YAxis.Min] * .YAxis.ScaleFactor + 1
                            ratio = (graphvspace - (close1 - graphvbegin)) / graphvspace
                            cs = c * ratio * COS(angle)
                            sn = c * ratio * SIN(angle)
                            '.buffer.line(x7,y7,x7-cs,y7-sn,pencolor)
                            closexarray(i) = x7 - cs
                            closeyarray(i) = y7 - sn
                            IF i + .DATA.ColCount * 0.75 - 1 = .DATA.ColCount * 0.75 THEN
                                .buffer.Line(closexarray(i) , closeyarray(i) , closexarray(.DATA.ColCount) , closeyarray(.DATA.ColCount) , pencolor)
                            END IF
                            IF i + .DATA.ColCount * 0.75 - 1 > .DATA.ColCount * 0.75 THEN
                                .buffer.Line(closexarray(i) , closeyarray(i) , closexarray(i - 1) , closeyarray(i - 1) , pencolor)
                            END IF
                        END IF

                        i ++
                        'doevents
                    NEXT angle

                    cs = c * COS(angle)
                    sn = c * SIN(angle)
                    FOR angle = 0 TO 1.57 STEP 0.001
                        'if cos(angle)<>0 and sin(angle)<>0 then
                        cs = c * COS(angle)
                        sn = c * SIN(angle)
                        .buffer.Pset(x7 + cs , y7 + sn , pencolor)
                        .buffer.Pset(x7 - cs , y7 + sn , pencolor)
                        .buffer.Pset(x7 + cs , y7 - sn , pencolor)
                        .buffer.Pset(x7 - cs , y7 - sn , pencolor)
                        'end if
                        'doevents
                    NEXT angle

                    .buffer.Pset(x7 , y7 , pencolor)
                    .buffer.Pset(x7 - 1 , y7 , pencolor)
                    .buffer.Pset(x7 - 1 , y7 + 1 , pencolor)
                    .buffer.Pset(x7 , y7 + 1 , pencolor)
                    .buffer.Pset(x7 + 1 , y7 + 1 , pencolor)
                    .buffer.Pset(x7 + 1 , y7 , pencolor)
                    .buffer.Pset(x7 + 1 , y7 - 1 , pencolor)
                    .buffer.Pset(x7 , y7 - 1 , pencolor)
                    .buffer.Pset(x7 - 1 , y7 - 1 , pencolor)
                    
            CASE 8 : ' Astro wheel
            
                    defstr usedquote
                    
                    if getquoteonoffbut.caption="Stop" then ' Realtime mode started
                    usedquote=currentquote
                    
                    defstr clockdateyear,clockdatemonth,clockdateday,clocktimehour,clocktimeminute,clocktimesecond
                    clockdatemonth=mid$(clockdate,1,2)
                    clockdateday=mid$(clockdate,4,2)
                    clockdateyear=mid$(clockdate,7,4)
                    clocktimehour=mid$(clocktime,1,2)
                    clocktimeminute=mid$(clocktime,4,2)
                    clocktimesecond=mid$(clocktime,7,2)
                    defdbl hourconv=val(clocktimehour)+val(clocktimeminute)/60+val(clocktimesecond)/60/60
                    'hourconv=hourconv+val(timezoneedit.text)

                    ' calculate date + timezone
                    defstr $mydate=clockdateyear+";"+clockdatemonth+";"+clockdateday+";"+clocktimehour+";"+clocktimeminute+";"+clocktimesecond
                    cpptmpfuncreturn=varptr$(date_to_unix_time(varptr($mydate)))
                    defdbl myunixtime=val(cpptmpfuncreturn)+(val(timezoneedit.text)*60*60)
                    if summertime.checked=1 then myunixtime=myunixtime-1*60*60
                    defstr myunixtimestr=Format$("%12.0f", myunixtime)
                    cpptmpfuncreturn=varptr$(unix_time_to_date(varptr(myunixtimestr)))
                    defstr newyear,newmonth,newday,newhour,newminute,newsecond
                    newyear=mid$(cpptmpfuncreturn,21,4)
                    newmonth=mid$(cpptmpfuncreturn,5,3)
                    newday=mid$(cpptmpfuncreturn,9,2)
                    newhour=mid$(cpptmpfuncreturn,12,2)
                    newminute=mid$(cpptmpfuncreturn,15,2)
                    newsecond=mid$(cpptmpfuncreturn,18,2)
                    newmonth=strtomonth(newmonth)                                        
                    defdbl newhourconv=val(newhour)+val(newminute)/60+val(newsecond)/60/60
                    
                    end if
                    
                    if getquoteonoffbut.caption="Start" then ' Use specified time
                    
                    DIM caldatey AS STRING
                    DIM caldatem AS STRING
                    DIM caldated AS STRING
                    DIM caldate AS STRING
                    DIM caldate2 AS STRING

                    caldatey = STR$(specifydatecal.y)
                    caldatem = STR$(specifydatecal.m)
                    caldated = STR$(specifydatecal.d)

                    i = 0
                    WHILE i < 4 - LEN(STR$(specifydatecal.y))
                        caldatey = "0" + caldatey
                        i ++
                    WEND

                    i = 0
                    WHILE i < 2 - LEN(STR$(specifydatecal.m))
                        caldatem = "0" + caldatem
                        i ++
                    WEND

                    i = 0
                    WHILE i < 2 - LEN(STR$(specifydatecal.d))
                        caldated = "0" + caldated
                        i ++
                    WEND
                    
                    if openedchartpriceradio.checked=1 then
                    
                    caldate = caldatey + "." + caldatem + "." + caldated
                    caldate2 = caldatey + "-" + caldatem + "-" + caldated

                    defint datefound=0
                     FOR i = 1 TO chartbars(displayedfile)
                            IF (like(Grid.Cell(rowgridoffset + 1 , i) , caldate) OR like(Grid.Cell(rowgridoffset + 1 , i) , caldate2)) AND _
                             like(Grid.Cell(rowgridoffset + 2 , i) , specifytimeedit.Text) THEN
                             usedquote=Grid.Cell(rowgridoffset + 3 , i) ' use open price of the bar
                             datefound=1
                             astrowheelmarketbar=i                                
                                EXIT FOR
                            END IF
                            'doevents
                     NEXT i
                     
                     if datefound=0 then usedquote="0"
                     
                     end if
                     
                     if specifypriceradio.checked=1 then usedquote=val(specifypriceedit.text)
                    
                    ' calculate date + timezone
                    $mydate=caldatey+";"+caldatem+";"+caldated+";"+mid$(specifytimeedit.Text,1,2)+";"+mid$(specifytimeedit.Text,4,2)+";"+"00"
                    cpptmpfuncreturn=varptr$(date_to_unix_time(varptr($mydate)))
                    myunixtime=val(cpptmpfuncreturn)+(val(timezoneedit.text)*60*60)
                    myunixtime=myunixtime+val(marketpostponement.text)*60*60
                    if summertime.checked=1 then myunixtime=myunixtime-1*60*60
                    myunixtimestr=Format$("%12.0f", myunixtime)
                    cpptmpfuncreturn=varptr$(unix_time_to_date(varptr(myunixtimestr)))
                    newyear=mid$(cpptmpfuncreturn,21,4)
                    newmonth=mid$(cpptmpfuncreturn,5,3)
                    newday=mid$(cpptmpfuncreturn,9,2)
                    newhour=mid$(cpptmpfuncreturn,12,2)
                    newminute=mid$(cpptmpfuncreturn,15,2)
                    newsecond=mid$(cpptmpfuncreturn,18,2)
                    newmonth=strtomonth(newmonth)                                        
                    newhourconv=val(newhour)+val(newminute)/60+val(newsecond)/60/60                    
                    
                    end if
            
                    .buffer.font=.arialfont
                                
                    FOR i = 1 TO .DATA.ColCount
                        '--- Draw Min - Max Line (Whiskers)
                        x1 = .XAxis.Ori + XIntvl * (i - 1) + XIntvl / 2
                        x2 = .XAxis.Ori + XIntvl * (i + 1 - 1) + XIntvl / 2

                        IF .Series(i).HatchStyle = hsSolid THEN
                            .hBrush = CreateSolidBrush(.Series(i).Color)
                        ELSE
                            .hBrush = CreateHatchBrush(.Series(i).HatchStyle , .Series(i).Color)
                        END IF
                        .OldBrush = SelectObject(.Buffer.Handle , .hBrush)

                        DeleteObject(SelectObject(.Buffer.Handle , .OldBrush))
                        'doevents
                    NEXT i                                        

                    ' Drawing price wheel
                    c = (pricechartpos(0,1)-pricechartpos(1,1))/2*0.85 ' Radius
                    defdbl c2=c
                    x7 = (timechartpos(.DATA.ColCount-1,1)-timechartpos(0,1))/2+timechartpos(0,1) ' x location
                    y7 = (pricechartpos(0,1)-pricechartpos(1,1))/2+pricechartpos(1,1) ' y location                   
                    cs = c * COS(angle)
                    sn = c * SIN(angle)
                    
                    FOR angle = 0 TO 1.57 STEP 0.001
                        cs = c * COS(angle)
                        sn = c * SIN(angle)
                        .buffer.Pset(x7 + cs , y7 + sn , black)
                        .buffer.Pset(x7 - cs , y7 + sn , black)
                        .buffer.Pset(x7 + cs , y7 - sn , black)
                        .buffer.Pset(x7 - cs , y7 - sn , black)
                        'doevents
                    NEXT angle
                    
                    ' drawing price graduations
                    defdbl gradtickx1,gradtickx2,gradticky1,gradticky2
                    defint graddeg
                    defdbl pricew0,pricew
                    
                    defdbl pricewdeg=(val(usedquote)/val(pointsper360degedit.text)-floor(val(usedquote)/val(pointsper360degedit.text)))*360
                    pricew0=floor(val(usedquote)/val(pointsper360degedit.text))*val(pointsper360degedit.text)
                    
                    for graddeg=0 to 345 step 15 ' 15 deg grads
                    gradtickx1=COS(graddeg * rad) * c + x7
                    gradtickx2=COS(graddeg * rad) * (c+3) + x7
                    gradticky1=y7 - SIN(graddeg * rad) * c
                    gradticky2=y7 - SIN(graddeg * rad) * (c+3)
                    .Buffer.Line(gradtickx1,gradticky1,gradtickx2,gradticky2, black)
                    gradtickx2=COS(graddeg * rad) * (c+40) + x7 - 3*len(Format$("%.4f", pricew))
                    gradticky2=y7 - SIN(graddeg * rad) * (c+40) - 8
                    pricew=pricew0+graddeg/360*val(pointsper360degedit.text)
                    .Buffer.TextOut(gradtickx2 , gradticky2 , Format$("%.4f", pricew) , black , plotareacolor)
                    'doevents
                    next graddeg
                    
                    
                    gradtickx1=COS(pricewdeg * rad) * c + x7
                    gradtickx2=COS(pricewdeg * rad) * (c+5) + x7
                    gradticky1=y7 - SIN(pricewdeg * rad) * c
                    gradticky2=y7 - SIN(pricewdeg * rad) * (c+5)
                    .Buffer.Line(gradtickx1,gradticky1,gradtickx2,gradticky2, green)
                    gradtickx2=COS(pricewdeg * rad) * (c+30) + x7 - 3*len(str$(pricewdeg))
                    gradticky2=y7 - SIN(pricewdeg * rad) * (c+30) - 8
                    .Buffer.TextOut(gradtickx2 , gradticky2 , usedquote , green , plotareacolor)
                    
                    ' Drawing degrees wheel
                    c = (pricechartpos(0,1)-pricechartpos(1,1))/2*0.73 ' Radius                    
                    defdbl c3=c
                    FOR angle = 0 TO 1.57 STEP 0.001
                        cs = c * COS(angle)
                        sn = c * SIN(angle)
                        .buffer.Pset(x7 + cs , y7 + sn , black)
                        .buffer.Pset(x7 - cs , y7 + sn , black)
                        .buffer.Pset(x7 + cs , y7 - sn , black)
                        .buffer.Pset(x7 - cs , y7 - sn , black)
                        'doevents
                    NEXT angle                                        
                    
                    c = (pricechartpos(0,1)-pricechartpos(1,1))/2*0.68 ' Radius
                    defdbl cdif=c2-c                                        
                    
                    FOR angle = 0 TO 1.57 STEP 0.001
                        cs = c * COS(angle)
                        sn = c * SIN(angle)
                        .buffer.Pset(x7 + cs , y7 + sn , black)
                        .buffer.Pset(x7 - cs , y7 + sn , black)
                        .buffer.Pset(x7 + cs , y7 - sn , black)
                        .buffer.Pset(x7 - cs , y7 - sn , black)
                        'doevents
                    NEXT angle
                    
                    ' drawing degrees graduations and symbols
                    dim astrofont as qfont
                    astrofont.name="Astro" 
                    astrofont.size=12                                       
                    'defdbl gradtickx1,gradtickx2,gradticky1,gradticky2
                    'defint graddeg
                    for graddeg=0 to 330 step 30 ' 30 deg grads
                    gradtickx1=COS(graddeg * rad) * c + x7
                    gradtickx2=COS(graddeg * rad) * (c+cdif*0.33) + x7
                    gradticky1=y7 - SIN(graddeg * rad) * c
                    gradticky2=y7 - SIN(graddeg * rad) * (c+cdif*0.33)
                    .Buffer.Line(gradtickx1,gradticky1,gradtickx2,gradticky2, black)
                    gradtickx2=COS(graddeg * rad) * (c+cdif*0.66) + x7 - 8
                    gradticky2=y7 - SIN(graddeg * rad) * (c+cdif*0.66) - 8
                    .buffer.font=.arialfont
                    .Buffer.TextOut(gradtickx2 , gradticky2 , str$(graddeg) , black , plotareacolor)
                    gradtickx2=COS((graddeg+15) * rad) * (c+cdif*0.6) + x7 - 5
                    gradticky2=y7 - SIN((graddeg+15) * rad) * (c+cdif*0.6) - 5
                    .buffer.font=astrofont
                    select case graddeg
                    case 0:
                    .Buffer.TextOut(gradtickx2 , gradticky2 , "A" , black , plotareacolor)
                    case 30:
                    .Buffer.TextOut(gradtickx2 , gradticky2 , "B" , black , plotareacolor)
                    case 60:
                    .Buffer.TextOut(gradtickx2 , gradticky2 , "C" , black , plotareacolor)
                    case 90:
                    .Buffer.TextOut(gradtickx2 , gradticky2 , "D" , black , plotareacolor)
                    case 120:
                    .Buffer.TextOut(gradtickx2 , gradticky2 , "E" , black , plotareacolor)
                    case 150:
                    .Buffer.TextOut(gradtickx2 , gradticky2 , "F" , black , plotareacolor)
                    case 180:
                    .Buffer.TextOut(gradtickx2 , gradticky2 , "G" , black , plotareacolor)
                    case 210:
                    .Buffer.TextOut(gradtickx2 , gradticky2 , "H" , black , plotareacolor)
                    case 240:
                    .Buffer.TextOut(gradtickx2 , gradticky2 , "I" , black , plotareacolor)
                    case 270:
                    .Buffer.TextOut(gradtickx2 , gradticky2 , "J" , black , plotareacolor)
                    case 300:
                    .Buffer.TextOut(gradtickx2 , gradticky2 , "K" , black , plotareacolor)
                    case 330:
                    .Buffer.TextOut(gradtickx2 , gradticky2 , "L" , black , plotareacolor)
                    end select
                    'doevents
                    next graddeg
                                                            
                    .buffer.font=.arialfont
                    
                    ' drawing planets                                        
                    
                    defdbl planetposx,planetposy,planetposx2,planetposy2
                    defint cc                    
                    defdbl planetdeg
                    
                    planetdeg=val(get_helio_longitude(SE_MERCURY,newyear,newmonth,newday,str$(newhourconv)))                    
                    planetposx=COS(planetdeg * rad) * (c*0.1) + x7
                    planetposy=y7 - SIN(planetdeg * rad) * (c*0.1)
                                        
                    for cc=0 to 2                                                          
                    FOR angle = 0 TO 1.57 STEP 0.001
                        cs = cc * COS(angle)
                        sn = cc * SIN(angle)
                        .buffer.Pset(planetposx + cs , planetposy + sn , orange)
                        .buffer.Pset(planetposx - cs , planetposy + sn , orange)
                        .buffer.Pset(planetposx + cs , planetposy - sn , orange)
                        .buffer.Pset(planetposx - cs , planetposy - sn , orange)
                        'doevents
                    NEXT angle                    
                    next cc
                    planetposx2=COS(planetdeg * rad) * c + x7
                    planetposy2=y7 - SIN(planetdeg * rad) * c
                    .buffer.line(planetposx,planetposy,planetposx2,planetposy2,orange)
                    
                    planetdeg=val(get_helio_longitude(SE_VENUS,newyear,newmonth,newday,str$(newhourconv)))                    
                    planetposx=COS(planetdeg * rad) * (c*0.2) + x7
                    planetposy=y7 - SIN(planetdeg * rad) * (c*0.2)
                                        
                    for cc=0 to 2                                                          
                    FOR angle = 0 TO 1.57 STEP 0.001
                        cs = cc * COS(angle)
                        sn = cc * SIN(angle)
                        .buffer.Pset(planetposx + cs , planetposy + sn , pink)
                        .buffer.Pset(planetposx - cs , planetposy + sn , pink)
                        .buffer.Pset(planetposx + cs , planetposy - sn , pink)
                        .buffer.Pset(planetposx - cs , planetposy - sn , pink)
                        'doevents
                    NEXT angle  
                    'doevents                  
                    next cc
                    planetposx2=COS(planetdeg * rad) * c + x7
                    planetposy2=y7 - SIN(planetdeg * rad) * c
                    .buffer.line(planetposx,planetposy,planetposx2,planetposy2,pink)
                    
                    planetdeg=val(get_helio_longitude(SE_EARTH,newyear,newmonth,newday,str$(newhourconv)))                    
                    planetposx=COS(planetdeg * rad) * (c*0.3) + x7
                    planetposy=y7 - SIN(planetdeg * rad) * (c*0.3)
                                        
                    for cc=0 to 2                                                          
                    FOR angle = 0 TO 1.57 STEP 0.001
                        cs = cc * COS(angle)
                        sn = cc * SIN(angle)
                        .buffer.Pset(planetposx + cs , planetposy + sn , blue)
                        .buffer.Pset(planetposx - cs , planetposy + sn , blue)
                        .buffer.Pset(planetposx + cs , planetposy - sn , blue)
                        .buffer.Pset(planetposx - cs , planetposy - sn , blue)
                        'doevents
                    NEXT angle
                    'doevents                    
                    next cc
                    planetposx2=COS(planetdeg * rad) * c + x7
                    planetposy2=y7 - SIN(planetdeg * rad) * c
                    .buffer.line(planetposx,planetposy,planetposx2,planetposy2,blue)
                    
                    planetdeg=val(get_helio_longitude(SE_MARS,newyear,newmonth,newday,str$(newhourconv)))                    
                    planetposx=COS(planetdeg * rad) * (c*0.4) + x7
                    planetposy=y7 - SIN(planetdeg * rad) * (c*0.4)
                                        
                    for cc=0 to 2                                                          
                    FOR angle = 0 TO 1.57 STEP 0.001
                        cs = cc * COS(angle)
                        sn = cc * SIN(angle)
                        .buffer.Pset(planetposx + cs , planetposy + sn , red)
                        .buffer.Pset(planetposx - cs , planetposy + sn , red)
                        .buffer.Pset(planetposx + cs , planetposy - sn , red)
                        .buffer.Pset(planetposx - cs , planetposy - sn , red)
                        'doevents
                    NEXT angle  
                    'doevents                  
                    next cc
                    planetposx2=COS(planetdeg * rad) * c + x7
                    planetposy2=y7 - SIN(planetdeg * rad) * c
                    .buffer.line(planetposx,planetposy,planetposx2,planetposy2,red)
                    
                    planetdeg=val(get_helio_longitude(SE_JUPITER,newyear,newmonth,newday,str$(newhourconv)))                    
                    planetposx=COS(planetdeg * rad) * (c*0.5) + x7
                    planetposy=y7 - SIN(planetdeg * rad) * (c*0.5)
                                        
                    for cc=0 to 2                                                          
                    FOR angle = 0 TO 1.57 STEP 0.001
                        cs = cc * COS(angle)
                        sn = cc * SIN(angle)
                        .buffer.Pset(planetposx + cs , planetposy + sn , olive)
                        .buffer.Pset(planetposx - cs , planetposy + sn , olive)
                        .buffer.Pset(planetposx + cs , planetposy - sn , olive)
                        .buffer.Pset(planetposx - cs , planetposy - sn , olive)
                        'doevents
                    NEXT angle  
                    'doevents                  
                    next cc
                    planetposx2=COS(planetdeg * rad) * c + x7
                    planetposy2=y7 - SIN(planetdeg * rad) * c
                    .buffer.line(planetposx,planetposy,planetposx2,planetposy2,olive)
                    
                    planetdeg=val(get_helio_longitude(SE_SATURN,newyear,newmonth,newday,str$(newhourconv)))                    
                    planetposx=COS(planetdeg * rad) * (c*0.6) + x7
                    planetposy=y7 - SIN(planetdeg * rad) * (c*0.6)
                                        
                    for cc=0 to 2                                                          
                    FOR angle = 0 TO 1.57 STEP 0.001
                        cs = cc * COS(angle)
                        sn = cc * SIN(angle)
                        .buffer.Pset(planetposx + cs , planetposy + sn , gray)
                        .buffer.Pset(planetposx - cs , planetposy + sn , gray)
                        .buffer.Pset(planetposx + cs , planetposy - sn , gray)
                        .buffer.Pset(planetposx - cs , planetposy - sn , gray)
                        'doevents
                    NEXT angle  
                    'doevents                  
                    next cc
                    planetposx2=COS(planetdeg * rad) * c + x7
                    planetposy2=y7 - SIN(planetdeg * rad) * c
                    .buffer.line(planetposx,planetposy,planetposx2,planetposy2,gray)
                    
                    planetdeg=val(get_helio_longitude(SE_URANUS,newyear,newmonth,newday,str$(newhourconv)))                    
                    planetposx=COS(planetdeg * rad) * (c*0.7) + x7
                    planetposy=y7 - SIN(planetdeg * rad) * (c*0.7)
                                        
                    for cc=0 to 2                                                          
                    FOR angle = 0 TO 1.57 STEP 0.001
                        cs = cc * COS(angle)
                        sn = cc * SIN(angle)
                        .buffer.Pset(planetposx + cs , planetposy + sn , lightblue)
                        .buffer.Pset(planetposx - cs , planetposy + sn , lightblue)
                        .buffer.Pset(planetposx + cs , planetposy - sn , lightblue)
                        .buffer.Pset(planetposx - cs , planetposy - sn , lightblue)
                        'doevents
                    NEXT angle  
                    'doevents                  
                    next cc
                    planetposx2=COS(planetdeg * rad) * c + x7
                    planetposy2=y7 - SIN(planetdeg * rad) * c
                    .buffer.line(planetposx,planetposy,planetposx2,planetposy2,lightblue)
                    
                    planetdeg=val(get_helio_longitude(SE_NEPTUNE,newyear,newmonth,newday,str$(newhourconv)))                    
                    planetposx=COS(planetdeg * rad) * (c*0.8) + x7
                    planetposy=y7 - SIN(planetdeg * rad) * (c*0.8)
                                        
                    for cc=0 to 2                                                          
                    FOR angle = 0 TO 1.57 STEP 0.001
                        cs = cc * COS(angle)
                        sn = cc * SIN(angle)
                        .buffer.Pset(planetposx + cs , planetposy + sn , purple)
                        .buffer.Pset(planetposx - cs , planetposy + sn , purple)
                        .buffer.Pset(planetposx + cs , planetposy - sn , purple)
                        .buffer.Pset(planetposx - cs , planetposy - sn , purple)
                        'doevents
                    NEXT angle  
                    'doevents                  
                    next cc
                    planetposx2=COS(planetdeg * rad) * c + x7
                    planetposy2=y7 - SIN(planetdeg * rad) * c
                    .buffer.line(planetposx,planetposy,planetposx2,planetposy2,purple)
                    
                    planetdeg=val(get_helio_longitude(SE_PLUTO,newyear,newmonth,newday,str$(newhourconv)))                    
                    planetposx=COS(planetdeg * rad) * (c*0.9) + x7
                    planetposy=y7 - SIN(planetdeg * rad) * (c*0.9)
                                        
                    for cc=0 to 2                                                          
                    FOR angle = 0 TO 1.57 STEP 0.001
                        cs = cc * COS(angle)
                        sn = cc * SIN(angle)
                        .buffer.Pset(planetposx + cs , planetposy + sn , black)
                        .buffer.Pset(planetposx - cs , planetposy + sn , black)
                        .buffer.Pset(planetposx + cs , planetposy - sn , black)
                        .buffer.Pset(planetposx - cs , planetposy - sn , black)
                        'doevents
                    NEXT angle  
                    'doevents                  
                    next cc
                    planetposx2=COS(planetdeg * rad) * c + x7
                    planetposy2=y7 - SIN(planetdeg * rad) * c
                    .buffer.line(planetposx,planetposy,planetposx2,planetposy2,black)                                        
                    
                    ' drawing ascendant                     
                    planetdeg=val(get_ascmc(val(latitudeedit.text),val(longitudeedit.text),newyear,newmonth,newday,str$(newhourconv),"asc"))
                    planetposx=COS(planetdeg * rad) * (c*0.95) + x7
                    planetposy=y7 - SIN(planetdeg * rad) * (c*0.95)
                                        
                    for cc=0 to 2                                                          
                    FOR angle = 0 TO 1.57 STEP 0.001
                        cs = cc * COS(angle)
                        sn = cc * SIN(angle)
                        .buffer.Pset(planetposx + cs , planetposy + sn , green)
                        .buffer.Pset(planetposx - cs , planetposy + sn , green)
                        .buffer.Pset(planetposx + cs , planetposy - sn , green)
                        .buffer.Pset(planetposx - cs , planetposy - sn , green)
                        'doevents
                    NEXT angle  
                    'doevents                  
                    next cc
                    
                    ' drawing midheaven                     
                    planetdeg=val(get_ascmc(val(latitudeedit.text),val(longitudeedit.text),newyear,newmonth,newday,str$(newhourconv),"mc"))
                    planetposx=COS(planetdeg * rad) * (c*0.95) + x7
                    planetposy=y7 - SIN(planetdeg * rad) * (c*0.95)
                                        
                    for cc=0 to 2                                                          
                    FOR angle = 0 TO 1.57 STEP 0.001
                        cs = cc * COS(angle)
                        sn = cc * SIN(angle)
                        .buffer.Pset(planetposx + cs , planetposy + sn , white)
                        .buffer.Pset(planetposx - cs , planetposy + sn , white)
                        .buffer.Pset(planetposx + cs , planetposy - sn , white)
                        .buffer.Pset(planetposx - cs , planetposy - sn , white)
                        'doevents
                    NEXT angle  
                    'doevents                  
                    next cc
                    
                    ' drawing graduations                    
                    for graddeg=0 to 360 step 5 ' 5 deg grads
                    gradtickx1=COS(graddeg * rad) * c + x7
                    gradtickx2=COS(graddeg * rad) * (c3) + x7
                    gradticky1=y7 - SIN(graddeg * rad) * c
                    gradticky2=y7 - SIN(graddeg * rad) * (c3)
                    .Buffer.Line(gradtickx1,gradticky1,gradtickx2,gradticky2, black)
                    'doevents
                    next graddeg
                    
                    ' Drawing central yellow dot (the sun)
                    for c=0 to 2                                                          
                    FOR angle = 0 TO 1.57 STEP 0.001
                        cs = c * COS(angle)
                        sn = c * SIN(angle)
                        .buffer.Pset(x7 + cs , y7 + sn , yellow)
                        .buffer.Pset(x7 - cs , y7 + sn , yellow)
                        .buffer.Pset(x7 + cs , y7 - sn , yellow)
                        .buffer.Pset(x7 - cs , y7 - sn , yellow)
                        'doevents
                    NEXT angle  
                    'doevents                  
                    next c
                    
                    ' Drawing legend
                    defdbl legendmargin=(timechartpos(.DATA.ColCount-1,1)-timechartpos(0,1))*4/5+timechartpos(0,1)
                    .Buffer.TextOut(legendmargin , pricechartpos(1,1)+20 , "Legend:" , black , plotareacolor)
                    defint incrpx=45
                    
                    for c=0 to 2                                                          
                    FOR angle = 0 TO 1.57 STEP 0.001
                        cs = c * COS(angle)
                        sn = c * SIN(angle)
                        .buffer.Pset(legendmargin + cs , pricechartpos(1,1)+incrpx + sn , yellow)
                        .buffer.Pset(legendmargin - cs , pricechartpos(1,1)+incrpx + sn , yellow)
                        .buffer.Pset(legendmargin + cs , pricechartpos(1,1)+incrpx - sn , yellow)
                        .buffer.Pset(legendmargin - cs , pricechartpos(1,1)+incrpx - sn , yellow)
                        'doevents
                    NEXT angle  
                    'doevents                  
                    next c
                    incrpx=incrpx-5
                    .Buffer.TextOut(legendmargin+10 , pricechartpos(1,1)+incrpx , "Sun" , black , plotareacolor)
                    
                    incrpx=incrpx+25
                    for c=0 to 2                                                          
                    FOR angle = 0 TO 1.57 STEP 0.001
                        cs = c * COS(angle)
                        sn = c * SIN(angle)
                        .buffer.Pset(legendmargin + cs , pricechartpos(1,1)+incrpx + sn , orange)
                        .buffer.Pset(legendmargin - cs , pricechartpos(1,1)+incrpx + sn , orange)
                        .buffer.Pset(legendmargin + cs , pricechartpos(1,1)+incrpx - sn , orange)
                        .buffer.Pset(legendmargin - cs , pricechartpos(1,1)+incrpx - sn , orange)
                        'doevents
                    NEXT angle
                    'doevents                    
                    next c
                    incrpx=incrpx-5
                    .Buffer.TextOut(legendmargin+10 , pricechartpos(1,1)+incrpx , "Mercury" , black , plotareacolor)
                    
                    incrpx=incrpx+25
                    for c=0 to 2                                                          
                    FOR angle = 0 TO 1.57 STEP 0.001
                        cs = c * COS(angle)
                        sn = c * SIN(angle)
                        .buffer.Pset(legendmargin + cs , pricechartpos(1,1)+incrpx + sn , pink)
                        .buffer.Pset(legendmargin - cs , pricechartpos(1,1)+incrpx + sn , pink)
                        .buffer.Pset(legendmargin + cs , pricechartpos(1,1)+incrpx - sn , pink)
                        .buffer.Pset(legendmargin - cs , pricechartpos(1,1)+incrpx - sn , pink)
                        'doevents
                    NEXT angle       
                    'doevents             
                    next c
                    incrpx=incrpx-5
                    .Buffer.TextOut(legendmargin+10 , pricechartpos(1,1)+incrpx , "Venus" , black , plotareacolor)
                    
                    incrpx=incrpx+25
                    for c=0 to 2                                                          
                    FOR angle = 0 TO 1.57 STEP 0.001
                        cs = c * COS(angle)
                        sn = c * SIN(angle)
                        .buffer.Pset(legendmargin + cs , pricechartpos(1,1)+incrpx + sn , blue)
                        .buffer.Pset(legendmargin - cs , pricechartpos(1,1)+incrpx + sn , blue)
                        .buffer.Pset(legendmargin + cs , pricechartpos(1,1)+incrpx - sn , blue)
                        .buffer.Pset(legendmargin - cs , pricechartpos(1,1)+incrpx - sn , blue)
                        'doevents
                    NEXT angle  
                    'doevents                  
                    next c
                    incrpx=incrpx-5
                    .Buffer.TextOut(legendmargin+10 , pricechartpos(1,1)+incrpx , "Earth" , black , plotareacolor)
                    
                    incrpx=incrpx+25
                    for c=0 to 2                                                          
                    FOR angle = 0 TO 1.57 STEP 0.001
                        cs = c * COS(angle)
                        sn = c * SIN(angle)
                        .buffer.Pset(legendmargin + cs , pricechartpos(1,1)+incrpx + sn , red)
                        .buffer.Pset(legendmargin - cs , pricechartpos(1,1)+incrpx + sn , red)
                        .buffer.Pset(legendmargin + cs , pricechartpos(1,1)+incrpx - sn , red)
                        .buffer.Pset(legendmargin - cs , pricechartpos(1,1)+incrpx - sn , red)
                        'doevents
                    NEXT angle  
                    'doevents                  
                    next c
                    incrpx=incrpx-5
                    .Buffer.TextOut(legendmargin+10 , pricechartpos(1,1)+incrpx , "Mars" , black , plotareacolor)
                    
                    incrpx=incrpx+25
                    for c=0 to 2                                                          
                    FOR angle = 0 TO 1.57 STEP 0.001
                        cs = c * COS(angle)
                        sn = c * SIN(angle)
                        .buffer.Pset(legendmargin + cs , pricechartpos(1,1)+incrpx + sn , olive)
                        .buffer.Pset(legendmargin - cs , pricechartpos(1,1)+incrpx + sn , olive)
                        .buffer.Pset(legendmargin + cs , pricechartpos(1,1)+incrpx - sn , olive)
                        .buffer.Pset(legendmargin - cs , pricechartpos(1,1)+incrpx - sn , olive)
                        'doevents
                    NEXT angle  
                    'doevents                  
                    next c
                    incrpx=incrpx-5
                    .Buffer.TextOut(legendmargin+10 , pricechartpos(1,1)+incrpx , "Jupiter" , black , plotareacolor)
                    
                    incrpx=incrpx+25
                    for c=0 to 2                                                          
                    FOR angle = 0 TO 1.57 STEP 0.001
                        cs = c * COS(angle)
                        sn = c * SIN(angle)
                        .buffer.Pset(legendmargin + cs , pricechartpos(1,1)+incrpx + sn , gray)
                        .buffer.Pset(legendmargin - cs , pricechartpos(1,1)+incrpx + sn , gray)
                        .buffer.Pset(legendmargin + cs , pricechartpos(1,1)+incrpx - sn , gray)
                        .buffer.Pset(legendmargin - cs , pricechartpos(1,1)+incrpx - sn , gray)
                        'doevents
                    NEXT angle  
                    'doevents                  
                    next c
                    incrpx=incrpx-5
                    .Buffer.TextOut(legendmargin+10 , pricechartpos(1,1)+incrpx , "Saturn" , black , plotareacolor)
                    
                    incrpx=incrpx+25
                    for c=0 to 2                                                          
                    FOR angle = 0 TO 1.57 STEP 0.001
                        cs = c * COS(angle)
                        sn = c * SIN(angle)
                        .buffer.Pset(legendmargin + cs , pricechartpos(1,1)+incrpx + sn , lightblue)
                        .buffer.Pset(legendmargin - cs , pricechartpos(1,1)+incrpx + sn , lightblue)
                        .buffer.Pset(legendmargin + cs , pricechartpos(1,1)+incrpx - sn , lightblue)
                        .buffer.Pset(legendmargin - cs , pricechartpos(1,1)+incrpx - sn , lightblue)
                        'doevents
                    NEXT angle  
                    'doevents                  
                    next c
                    incrpx=incrpx-5
                    .Buffer.TextOut(legendmargin+10 , pricechartpos(1,1)+incrpx , "Uranus" , black , plotareacolor)
                    
                    incrpx=incrpx+25
                    for c=0 to 2                                                          
                    FOR angle = 0 TO 1.57 STEP 0.001
                        cs = c * COS(angle)
                        sn = c * SIN(angle)
                        .buffer.Pset(legendmargin + cs , pricechartpos(1,1)+incrpx + sn , purple)
                        .buffer.Pset(legendmargin - cs , pricechartpos(1,1)+incrpx + sn , purple)
                        .buffer.Pset(legendmargin + cs , pricechartpos(1,1)+incrpx - sn , purple)
                        .buffer.Pset(legendmargin - cs , pricechartpos(1,1)+incrpx - sn , purple)
                        'doevents
                    NEXT angle  
                    'doevents                  
                    next c
                    incrpx=incrpx-5
                    .Buffer.TextOut(legendmargin+10 , pricechartpos(1,1)+incrpx , "Neptune" , black , plotareacolor)
                    
                    incrpx=incrpx+25
                    for c=0 to 2                                                          
                    FOR angle = 0 TO 1.57 STEP 0.001
                        cs = c * COS(angle)
                        sn = c * SIN(angle)
                        .buffer.Pset(legendmargin + cs , pricechartpos(1,1)+incrpx + sn , black)
                        .buffer.Pset(legendmargin - cs , pricechartpos(1,1)+incrpx + sn , black)
                        .buffer.Pset(legendmargin + cs , pricechartpos(1,1)+incrpx - sn , black)
                        .buffer.Pset(legendmargin - cs , pricechartpos(1,1)+incrpx - sn , black)
                        'doevents
                    NEXT angle  
                    'doevents                  
                    next c
                    incrpx=incrpx-5
                    .Buffer.TextOut(legendmargin+10 , pricechartpos(1,1)+incrpx , "Pluto" , black , plotareacolor)
                    
                    incrpx=incrpx+25
                    for c=0 to 2                                                          
                    FOR angle = 0 TO 1.57 STEP 0.001
                        cs = c * COS(angle)
                        sn = c * SIN(angle)
                        .buffer.Pset(legendmargin + cs , pricechartpos(1,1)+incrpx + sn , Green)
                        .buffer.Pset(legendmargin - cs , pricechartpos(1,1)+incrpx + sn , Green)
                        .buffer.Pset(legendmargin + cs , pricechartpos(1,1)+incrpx - sn , Green)
                        .buffer.Pset(legendmargin - cs , pricechartpos(1,1)+incrpx - sn , Green)
                        'doevents
                    NEXT angle  
                    'doevents                  
                    next c
                    incrpx=incrpx-5
                    .Buffer.TextOut(legendmargin+10 , pricechartpos(1,1)+incrpx , "Ascendant" , black , plotareacolor)
                    
                    incrpx=incrpx+25
                    for c=0 to 2                                                          
                    FOR angle = 0 TO 1.57 STEP 0.001
                        cs = c * COS(angle)
                        sn = c * SIN(angle)
                        .buffer.Pset(legendmargin + cs , pricechartpos(1,1)+incrpx + sn , White)
                        .buffer.Pset(legendmargin - cs , pricechartpos(1,1)+incrpx + sn , White)
                        .buffer.Pset(legendmargin + cs , pricechartpos(1,1)+incrpx - sn , White)
                        .buffer.Pset(legendmargin - cs , pricechartpos(1,1)+incrpx - sn , White)
                        'doevents
                    NEXT angle  
                    'doevents                  
                    next c
                    incrpx=incrpx-5
                    .Buffer.TextOut(legendmargin+10 , pricechartpos(1,1)+incrpx , "Midheaven" , black , plotareacolor)
                    
                    
                    ' Drawing Info
                    legendmargin=(timechartpos(.DATA.ColCount-1,1)-timechartpos(0,1))*1/50+timechartpos(0,1)
                    .Buffer.TextOut(legendmargin , pricechartpos(1,1)+20 , "Info:" , black , plotareacolor)
                    incrpx=40
                    
                    defstr mytext
                    
                    if getquoteonoffbut.caption="Stop" then ' Realtime mode started
                    
                    mytext="Time: "
                    mytext=mytext+clockdateyear+"-"+clockdatemonth+"-"+clockdateday+" "+clocktimehour+":"+clocktimeminute+":"+clocktimesecond                                        
                    .Buffer.TextOut(legendmargin , pricechartpos(1,1)+incrpx , mytext , black , plotareacolor)
                    
                    incrpx=incrpx+20
                    mytext="Symbol: "
                    mytext=mytext+symboledit.text                                       
                    .Buffer.TextOut(legendmargin , pricechartpos(1,1)+incrpx , mytext , black , plotareacolor)
                    
                    incrpx=incrpx+20
                    mytext="Price: "
                    mytext=mytext+usedquote                                       
                    .Buffer.TextOut(legendmargin , pricechartpos(1,1)+incrpx , mytext , black , plotareacolor)
                    
                    incrpx=incrpx+20
                    mytext="Latitude: "
                    mytext=mytext+latitudeedit.text                                       
                    .Buffer.TextOut(legendmargin , pricechartpos(1,1)+incrpx , mytext , black , plotareacolor)
                    
                    incrpx=incrpx+20
                    mytext="Longitude: "
                    mytext=mytext+longitudeedit.text                                      
                    .Buffer.TextOut(legendmargin , pricechartpos(1,1)+incrpx , mytext , black , plotareacolor)
                    
                    incrpx=incrpx+20
                    mytext="Time zone: "
                    mytext=mytext+timezoneedit.text                                      
                    .Buffer.TextOut(legendmargin , pricechartpos(1,1)+incrpx , mytext , black , plotareacolor)
                    
                    incrpx=incrpx+20
                    mytext="Summer time: "
                    if summertime.checked=1 then mytext=mytext+"yes" 
                    if summertime.checked=0 then mytext=mytext+"no"                                      
                    .Buffer.TextOut(legendmargin , pricechartpos(1,1)+incrpx , mytext , black , plotareacolor)
                    
                    end if
                    
                    if getquoteonoffbut.caption="Start" and (openedchartpriceradio.checked=1 or specifypriceradio.checked=1) then ' Realtime mode stopped
                    
                    mytext="Market time: "
                    mytext=mytext+caldatey+"-"+caldatem+"-"+caldated+" "+specifytimeedit.Text                                        
                    .Buffer.TextOut(legendmargin , pricechartpos(1,1)+incrpx , mytext , black , plotareacolor)
                    
                    incrpx=incrpx+20
                    mytext="Price: "
                    mytext=mytext+usedquote                                       
                    .Buffer.TextOut(legendmargin , pricechartpos(1,1)+incrpx , mytext , black , plotareacolor)
                    
                    incrpx=incrpx+20
                    mytext="Ephemeris time: "
                    $mydate=caldatey+";"+caldatem+";"+caldated+";"+mid$(specifytimeedit.Text,1,2)+";"+mid$(specifytimeedit.Text,4,2)+";"+"00"
cpptmpfuncreturn=varptr$(date_to_unix_time(varptr($mydate)))
myunixtime=val(cpptmpfuncreturn)+val(marketpostponement.text)*60*60
myunixtimestr=Format$("%12.0f", myunixtime)
cpptmpfuncreturn=varptr$(unix_time_to_date(varptr(myunixtimestr)))
                    mytext=mytext+cpptmpfuncreturn                                       
                    .Buffer.TextOut(legendmargin , pricechartpos(1,1)+incrpx , mytext , black , plotareacolor)
                    
                    incrpx=incrpx+20
                    mytext="Latitude: "
                    mytext=mytext+latitudeedit.text                                       
                    .Buffer.TextOut(legendmargin , pricechartpos(1,1)+incrpx , mytext , black , plotareacolor)
                    
                    incrpx=incrpx+20
                    mytext="Longitude: "
                    mytext=mytext+longitudeedit.text                                      
                    .Buffer.TextOut(legendmargin , pricechartpos(1,1)+incrpx , mytext , black , plotareacolor)
                    
                    incrpx=incrpx+20
                    mytext="Time zone: "
                    mytext=mytext+timezoneedit.text                                      
                    .Buffer.TextOut(legendmargin , pricechartpos(1,1)+incrpx , mytext , black , plotareacolor)
                    
                    incrpx=incrpx+20
                    mytext="Summer time: "
                    if summertime.checked=1 then mytext=mytext+"yes" 
                    if summertime.checked=0 then mytext=mytext+"no"                                      
                    .Buffer.TextOut(legendmargin , pricechartpos(1,1)+incrpx , mytext , black , plotareacolor)
                    
                    incrpx=incrpx+20
                    mytext="Postponement between market time and "
                    .Buffer.TextOut(legendmargin , pricechartpos(1,1)+incrpx , mytext , black , plotareacolor)
                    incrpx=incrpx+20
                    mytext="local time (ephemeris) in hours: "+marketpostponement.text                                  
                    .Buffer.TextOut(legendmargin , pricechartpos(1,1)+incrpx , mytext , black , plotareacolor)
                    
                    end if

            END SELECT

        END WITH
        QChart.ChartExists = TRUE

        'DRAWING INDICATORS ON CHART WINDOW
        IF useindi.Checked = 1 THEN
            WITH QChart

                .XAxis.ScaleFactor = .XAxis.LEN / .XAxis.Div

                SetBkColor(.Buffer.Handle , .PlotAreaColor)

                FOR i = 2 TO .DATA_INDI.ColCount STEP 2
                    .hPen = CreatePen(.Series(i \ 2).LineStyle , .Series(i \ 2).LineWidth , indicolor(i)) '.Series(i\2).Color)
                    .OldPen = SelectObject(.Buffer.Handle , .hPen)
                    FOR j = 1 TO .DATA_INDI.RowCount - 1

                        IF .DATA_INDI.Cell(i - 1 , j) = .Missing OR .DATA_INDI.Cell(i - 1 , j + 1) = .Missing _  'If data missing
                            THEN GOTO NoPlotXYLn
                        IF .DATA_INDI.Cell(i , j) = .Missing OR .DATA_INDI.Cell(i , j + 1) = .Missing _
                            THEN GOTO NoPlotXYLn
                        IF .XAxis.LogScale = FALSE THEN
                            x1 = [VAL(.DATA_INDI.Cell(i - 1 , j)) - .XAxis.Min] * .XAxis.ScaleFactor
                            x2 = [VAL(.DATA_INDI.Cell(i - 1 , j + 1)) - .XAxis.Min] * .XAxis.ScaleFactor
                        ELSE
                            x1 = [.Log10(VAL(.DATA_INDI.Cell(i - 1 , j))) - .XAxis.Min] * .XAxis.ScaleFactor
                            x2 = [.Log10(VAL(.DATA_INDI.Cell(i - 1 , j + 1))) - .XAxis.Min] * .XAxis.ScaleFactor
                        END IF

                        IF .YAxis.LogScale = FALSE THEN
                            y1 = [VAL(.DATA_INDI.Cell(i , j)) - .YAxis.Min] * .YAxis.ScaleFactor
                            y2 = [VAL(.DATA_INDI.Cell(i , j + 1)) - .YAxis.Min] * .YAxis.ScaleFactor
                        ELSE
                            y1 = [.Log10(VAL(.DATA_INDI.Cell(i , j))) - .YAxis.Min] * .YAxis.ScaleFactor
                            y2 = [.Log10(VAL(.DATA_INDI.Cell(i , j + 1))) - .YAxis.Min] * .YAxis.ScaleFactor
                        END IF

                        x1 = .XAxis.Ori + x1 - XIntvl
                        y1 = .YAxis.Ori - y1
                        x2 = .XAxis.Ori + x2 - XIntvl
                        y2 = .YAxis.Ori - y2

                        '--- Use API to draw lines
                        'MoveToEx(.Buffer.handle,x1,y1,0)
                        'LineTo(.Buffer.handle,x2,y2)
                        .Buffer.Line(x1 , y1 , x2 , y2 , indicolor(i))

                        NoPlotXYLn :
                        doevents
                    NEXT j
                    DeleteObject(SelectObject(.Buffer.Handle , .OldPen))
                    doevents
                NEXT i

            END WITH
        END IF
    END SUB

    private :
    SUB drawtrendline(xb , yb , xc , yc)

        DEFSNG x2 , y2 , x3 , y3
        x2 = xb
        y2 = yb
        x3 = xc
        y3 = yc

        WITH QChart
            .ClearBuffer
            .buffer.BMP = .buffertmpz.BMP
            'MoveToEx(.Buffer.handle,x2,y2,0)
            'LineTo(.Buffer.handle,x3,y3)
            .Buffer.Line(x2 , y2 , x3 , y3 , pencolor)
            .buffertmp.BMP = .buffer.BMP
            .PaintChart
            DIM a AS DOUBLE , b AS DOUBLE , c AS DOUBLE , ang_a AS DOUBLE
            a = x3 - x2
            b = y3 - y2
            c = SQR(a^2 + b^2)
            IF c <> 0 THEN
                ang_a = ACOS(a / c) * 180 / 3.1415927
                ang_a_pub=ang_a
                dispinfotext("Angle: " + STR$(ang_a) + CHR$(10) + _
                    "Length: " + STR$(c) _
                    + CHR$(10) + "x1: " + STR$(x2) _
                    + CHR$(10) + "y1: " + STR$(y2) _
                    + CHR$(10) + "x2: " + STR$(x3) _
                    + CHR$(10) + "y2: " + STR$(y3) _
                    )
            END IF

        END WITH

    END SUB
        
    private :
    SUB drawfibofan(xb , yb , xc , yc,xd,yd)
    
    if fibofanstandardradio.checked=1 and symetryfrompoint=0 then

        DEFSNG x2 , y2 , x3 , y3
        x2 = xb
        y2 = yb
        x3 = xc
        y3 = yc

        WITH QChart
            .ClearBuffer
            '.restorebuffertmp
            .buffer.BMP = .buffertmpz.BMP
            'MoveToEx(.Buffer.handle,x2,y2,0)
            'LineTo(.Buffer.handle,x3,y3)
            .Buffer.Line(x2 , y2 , x3 , y3 , pencolor)
            DIM a AS DOUBLE , b AS DOUBLE , c AS DOUBLE , ang_a AS DOUBLE
            a = x3 - x2
            b = y3 - y2
            c = SQR(a^2 + b^2)
            IF c <> 0 THEN
                ang_a = ACOS(a / c) * 180 / 3.1415927
		ang_a_pub=ang_a
                dispinfotext("Angle: " + STR$(ang_a) + CHR$(10) + _
                    "Length: " + STR$(c) _
                    + CHR$(10) + "x1: " + STR$(x2) _
                    + CHR$(10) + "y1: " + STR$(y2) _
                    + CHR$(10) + "x2: " + STR$(x3) _
                    + CHR$(10) + "y2: " + STR$(y3) _
                    )
            END IF
            DIM x4 AS DOUBLE
            x4 = x3 + (x3 - x2)
            'MoveToEx(.Buffer.handle,x2,y2,0)
            'LineTo(.Buffer.handle,x4,y3)
            .Buffer.Line(x2 , y2 , x4 , y3 , pencolor)
            .Buffer.TextOut(x4 - 40 , y3 , "50" , pencolor , &hffffff)
            x4 = x3 + (x3 - x2) * 0.618
            'MoveToEx(.Buffer.handle,x2,y2,0)
            'LineTo(.Buffer.handle,x4,y3)
            .Buffer.Line(x2 , y2 , x4 , y3 , pencolor)
            .Buffer.TextOut(x4 - 40 , y3 , "38.2" , pencolor , &hffffff)
            x4 = x3 + (x3 - x2) * 1.618
            'MoveToEx(.Buffer.handle,x2,y2,0)
            'LineTo(.Buffer.handle,x4,y3)
            .Buffer.Line(x2 , y2 , x4 , y3 , pencolor)
            .Buffer.TextOut(x4 - 40 , y3 , "61.8" , pencolor , &hffffff)
            .buffertmp.BMP = .buffer.BMP
            .PaintChart
        END WITH
        
        end if
        
        if fibofansymetryfrompointradio.checked=1 and symetryfrompoint=1 then
        
        fibofanangonce=0
        'DEFSNG x2 , y2 , x3 , y3 , x4 , y4
        'DEFSNG x4
        DEFSNG y4
        x2 = xb
        y2 = yb
        x3 = xc
        y3 = yc
        x4 = xd
        y4 = yd

        WITH QChart
            .ClearBuffer
            .buffer.BMP = .buffertmpz.BMP
            'MoveToEx(.Buffer.handle,x2,y2,0)
            'LineTo(.Buffer.handle,x2,y3)
            graphcursorpos2
            .Buffer.Line(x2 , y2-5 , x2 , y2+5 , pencolor)
            '.Buffer.TextOut(x3 , graphvspace + 45 , graphdateoncur , pencolor , &hffffff)
            .Buffer.Line(x2-5 , y2 , x2+5 , y2 , pencolor)
            '.Buffer.TextOut(0 , y3 , STR$(graphpriceoncur) , pencolor , &hffffff)
            .buffertmp.BMP = .buffer.BMP
            .PaintChart
            'DIM a AS DOUBLE , b AS DOUBLE , c AS DOUBLE , ang_a AS DOUBLE
            a = x3 - x2
            b = y3 - y2
            c = SQR(a^2 + b^2)
            IF c <> 0 THEN
                ang_a = ACOS(a / c) * 180 / 3.1415927
		ang_a_pub=ang_a
                dispinfotext("Angle: " + STR$(ang_a) + CHR$(10) + _
                    "Length: " + STR$(c) _
                    + CHR$(10) + "x1: " + STR$(x2) _
                    + CHR$(10) + "y1: " + STR$(y2) _
                    + CHR$(10) + "x2: " + STR$(x3) _
                    + CHR$(10) + "y2: " + STR$(y3) _
                    )
            END IF

        END WITH
        
        end if
       
       if fibofansymetryfrompointradio.checked=1 and symetryfrompoint=0 then
       
       'DEFSNG x2 , y2 , x3 , y3
        x2 = xb
        y2 = yb
        x3 = xc
        y3 = yc
        defsng x5,y5,x6,y6,x7,y7
        defdbl ang_a_tmp
        defsng y2_tmp,y3_tmp

        WITH QChart
            .ClearBuffer
            '.restorebuffertmp
            .buffer.BMP = .buffertmpz.BMP
            'MoveToEx(.Buffer.handle,x2,y2,0)
            'LineTo(.Buffer.handle,x3,y3)
            .Buffer.Line(x2 , y2 , x3 , y3 , pencolor)
            
            x5=x2-lastpointofsymetryx
            y5=y2-lastpointofsymetryy
            x6=x3-lastpointofsymetryx
            y6=y3-lastpointofsymetryy
            .Buffer.Line(lastpointofsymetryx-x5 , lastpointofsymetryy-y5 , lastpointofsymetryx-x6 , lastpointofsymetryy-y6 , pencolor)
            
            
            
            
            
            'DIM a AS DOUBLE , b AS DOUBLE , c AS DOUBLE , ang_a AS DOUBLE
            a = x3 - x2
            b = y3 - y2
            c = SQR(a^2 + b^2)
            IF c <> 0 THEN
                ang_a = ACOS(a / c) * 180 / 3.1415927
		ang_a_pub=ang_a
                if fibofanangonce=0 then 
                    ang_a_tmp=ang_a                
                    fibofanangonce=1
                    y2_tmp=y2
                    y3_tmp=y3
                end if
                dispinfotext("Angle: " + STR$(ang_a) + CHR$(10) + _
                    "Length: " + STR$(c) _
                    + CHR$(10) + "x1: " + STR$(x2) _
                    + CHR$(10) + "y1: " + STR$(y2) _
                    + CHR$(10) + "x2: " + STR$(x3) _
                    + CHR$(10) + "y2: " + STR$(y3) _
                    )
            END IF   
            
            
            
            '.Buffer.Line(lastpointofsymetryx-x5,lastpointofsymetryy-y5,x2,y2 , pencolor)
            defdbl a2,b2,c2,ang_z
            a2=x2-(lastpointofsymetryx-x5)
            b2=y2-(lastpointofsymetryy-y5)
            c2=SQR(a2^2+b2^2)
            IF c2 <> 0 THEN
                ang_z = ACOS(a2 / c2) * 180 / 3.1415927
            end if
            
            IF y2 > lastpointofsymetryy-y5 THEN
                ang_z = ang_z * - 1
            END IF
            
            defsng x8,y8,x9,y9
            x8=lastpointofsymetryx-x5
            y8=lastpointofsymetryy-y5            
            x7 = COS((ang_z - 90) * rad) * c2 * 0.5 + x2 - (x2 - x8) * 0.5
            y7 = y2 - (y2 - y8) * 0.5 - SIN((ang_z - 90) * rad) * c2 * 0.5
            x9 = COS((ang_z + 90) * rad) * c2 * 0.5 + x2 - (x2 - x8) * 0.5
            y9 = y2 - (y2 - y8) * 0.5 - SIN((ang_z + 90) * rad) * c2 * 0.5
            '.Buffer.Line(x2 - (x2 - x8) * 0.5 , y2 - (y2 - y8) * 0.5 , x7 , y7 , pencolor)
            '.Buffer.Line(x2 - (x2 - x8) * 0.5 , y2 - (y2 - y8) * 0.5 , x9 , y9 , pencolor)
            
            .Buffer.Line(x7 , y7 , x7-(y3-y2) , y7+(x3-x2) , pencolor)
            .Buffer.Line(x9 , y9 , x9+(y3-y2) , y9-(x3-x2) , pencolor)
            
            
            'x7 = COS((ang_a - 90) * rad) * c * 0.5 + x2 - (x2 - (lastpointofsymetryx-x5)) * 0.5
            'y7 = y2 - (y2 - (lastpointofsymetryy-y5)) * 0.5 - SIN((ang_a - 90) * rad) * c * 0.5
            '.Buffer.Line(x2 - (x2 - lastpointofsymetryx-x5) * 0.5 , y2 - (y2 - lastpointofsymetryy-y5) * 0.5 , x7 , y7 , pencolor)        
            
            'DIM x4 AS DOUBLE
            defdbl xx2
            x4 = x3 + (x3 - x2)
            'MoveToEx(.Buffer.handle,x2,y2,0)
            'LineTo(.Buffer.handle,x4,y3)
            .Buffer.Line(x2 , y2 , x4 , y3 , pencolor)
            .Buffer.TextOut(x4 - 40 , y3 , "50" , pencolor , &hffffff)
            
            x5=x2-lastpointofsymetryx
            y5=y2-lastpointofsymetryy
            x6=x4-lastpointofsymetryx
            y6=y3-lastpointofsymetryy
            .Buffer.Line(lastpointofsymetryx-x5 , lastpointofsymetryy-y5 , lastpointofsymetryx-x6 , lastpointofsymetryy-y6 , pencolor)
            
            xx2=(x7-(y3-y2))+((x7-(y3-y2))-x7)
            .Buffer.Line(x7 , y7 , xx2 , y7+(x3-x2) , pencolor)
            
            xx2=(x9+(y3-y2))+((x9+(y3-y2))-x9)
            .Buffer.Line(x9 , y9 , xx2 , y9-(x3-x2) , pencolor)
            
            '.Buffer.Line(lastpointofsymetryx-x5 , lastpointofsymetryy+y5 , lastpointofsymetryx-x6 , lastpointofsymetryy+y6 , pencolor)
            '.Buffer.Line(lastpointofsymetryx+x5 , lastpointofsymetryy-y5 , lastpointofsymetryx+x6 , lastpointofsymetryy-y6 , pencolor)
            
            x4 = x3 + (x3 - x2) * 0.618
            'MoveToEx(.Buffer.handle,x2,y2,0)
            'LineTo(.Buffer.handle,x4,y3)
            .Buffer.Line(x2 , y2 , x4 , y3 , pencolor)
            .Buffer.TextOut(x4 - 40 , y3 , "38.2" , pencolor , &hffffff)
            
            x5=x2-lastpointofsymetryx
            y5=y2-lastpointofsymetryy
            x6=x4-lastpointofsymetryx
            y6=y3-lastpointofsymetryy
            .Buffer.Line(lastpointofsymetryx-x5 , lastpointofsymetryy-y5 , lastpointofsymetryx-x6 , lastpointofsymetryy-y6 , pencolor)
            
            xx2=(x7-(y3-y2))+((x7-(y3-y2))-x7)*0.618
            .Buffer.Line(x7 , y7 , xx2 , y7+(x3-x2) , pencolor)
            
            xx2=(x9+(y3-y2))+((x9+(y3-y2))-x9)*0.618
            .Buffer.Line(x9 , y9 , xx2 , y9-(x3-x2) , pencolor)
            
            '.Buffer.Line(lastpointofsymetryx-x5 , lastpointofsymetryy+y5 , lastpointofsymetryx-x6 , lastpointofsymetryy+y6 , pencolor)
            '.Buffer.Line(lastpointofsymetryx+x5 , lastpointofsymetryy-y5 , lastpointofsymetryx+x6 , lastpointofsymetryy-y6 , pencolor)
            
            x4 = x3 + (x3 - x2) * 1.618
            'MoveToEx(.Buffer.handle,x2,y2,0)
            'LineTo(.Buffer.handle,x4,y3)
            .Buffer.Line(x2 , y2 , x4 , y3 , pencolor)
            .Buffer.TextOut(x4 - 40 , y3 , "61.8" , pencolor , &hffffff)
            
            x5=x2-lastpointofsymetryx
            y5=y2-lastpointofsymetryy
            x6=x4-lastpointofsymetryx
            y6=y3-lastpointofsymetryy
            .Buffer.Line(lastpointofsymetryx-x5 , lastpointofsymetryy-y5 , lastpointofsymetryx-x6 , lastpointofsymetryy-y6 , pencolor)
            
            xx2=(x7-(y3-y2))+((x7-(y3-y2))-x7)*1.618
            .Buffer.Line(x7 , y7 , xx2 , y7+(x3-x2) , pencolor)
            
            xx2=(x9+(y3-y2))+((x9+(y3-y2))-x9)*1.618
            .Buffer.Line(x9 , y9 , xx2 , y9-(x3-x2) , pencolor)
            
            '.Buffer.Line(lastpointofsymetryx-x5 , lastpointofsymetryy+y5 , lastpointofsymetryx-x6 , lastpointofsymetryy+y6 , pencolor)
            '.Buffer.Line(lastpointofsymetryx+x5 , lastpointofsymetryy-y5 , lastpointofsymetryx+x6 , lastpointofsymetryy-y6 , pencolor)
            
            .buffertmp.BMP = .buffer.BMP
            .PaintChart
        END WITH
       
       end if

    END SUB

    private :
    SUB drawfiboret(xb , yb , xc , yc)

        DEFSNG x2 , y2 , x3 , y3
        x2 = xb
        y2 = yb
        x3 = xc
        y3 = yc

        WITH QChart
            .ClearBuffer
            .buffer.BMP = .buffertmpz.BMP
            'MoveToEx(.Buffer.handle,x2,y2,0)
            'LineTo(.Buffer.handle,x3,y3)
            .Buffer.Line(x2 , y2 , x3 , y3 , pencolor)
            .Buffer.TextOut(x2 - 30 , y2 , "100" , pencolor , &hffffff)
            DIM a AS DOUBLE , b AS DOUBLE , c AS DOUBLE , ang_a AS DOUBLE
            a = x3 - x2
            b = y3 - y2
            c = SQR(a^2 + b^2)
            IF c <> 0 THEN
                ang_a = ACOS(a / c) * 180 / 3.1415927
		ang_a_pub=ang_a
                dispinfotext("Angle: " + STR$(ang_a) + CHR$(10) + _
                    "Length: " + STR$(c) _
                    + CHR$(10) + "x1: " + STR$(x2) _
                    + CHR$(10) + "y1: " + STR$(y2) _
                    + CHR$(10) + "x2: " + STR$(x3) _
                    + CHR$(10) + "y2: " + STR$(y3) _
                    )
            END IF
            'MoveToEx(.Buffer.handle,x2,y2,0)
            'LineTo(.Buffer.handle,x3,y2)
            'MoveToEx(.Buffer.handle,x2,y3,0)
            'LineTo(.Buffer.handle,x3,y3)
            .Buffer.Line(x2 , y2 , x3 , y2 , pencolor)
            .Buffer.Line(x2 , y3 , x3 , y3 , pencolor)
            .Buffer.TextOut(x2 - 30 , y3 , "0" , pencolor , &hffffff)
            DIM y4 AS DOUBLE
            y4 = y3 - (y3 - y2) * 0.236
            'MoveToEx(.Buffer.handle,x2,y4,0)
            'LineTo(.Buffer.handle,x3,y4)
            .Buffer.Line(x2 , y4 , x3 , y4 , pencolor)
            .Buffer.TextOut(x2 - 30 , y4 , "23.6" , pencolor , &hffffff)
            y4 = y3 - (y3 - y2) * 0.382
            'MoveToEx(.Buffer.handle,x2,y4,0)
            'LineTo(.Buffer.handle,x3,y4)
            .Buffer.Line(x2 , y4 , x3 , y4 , pencolor)
            .Buffer.TextOut(x2 - 30 , y4 , "38.2" , pencolor , &hffffff)
            y4 = y3 - (y3 - y2) * 0.5
            'MoveToEx(.Buffer.handle,x2,y4,0)
            'LineTo(.Buffer.handle,x3,y4)
            .Buffer.Line(x2 , y4 , x3 , y4 , pencolor)
            .Buffer.TextOut(x2 - 30 , y4 , "50" , pencolor , &hffffff)
            y4 = y3 - (y3 - y2) * 0.618
            'MoveToEx(.Buffer.handle,x2,y4,0)
            'LineTo(.Buffer.handle,x3,y4)
            .Buffer.Line(x2 , y4 , x3 , y4 , pencolor)
            .Buffer.TextOut(x2 - 30 , y4 , "61.8" , pencolor , &hffffff)
            .buffertmp.BMP = .buffer.BMP
            .PaintChart
        END WITH

    END SUB

    private :
    SUB drawpara(xb , yb , xc , yc , xd , yd)

        DEFSNG x2 , y2 , x3 , y3 , x4 , y4
        x2 = xb
        y2 = yb
        x3 = xc
        y3 = yc
        x4 = xd
        y4 = yd

        WITH QChart
            .ClearBuffer
            .buffer.BMP = .buffertmpz2.BMP
            'MoveToEx(.Buffer.handle,x3-1,y3,0)
            'LineTo(.Buffer.handle,x3+x4-x2,y3+y4-y2)
            .Buffer.Line(x3 , y3 , x3 + x4 - x2 , y3 + y4 - y2 , pencolor)
            .buffertmp.BMP = .buffer.BMP
            .PaintChart
            DIM a AS DOUBLE , b AS DOUBLE , c AS DOUBLE , ang_a AS DOUBLE
            a = x3 - x2
            b = y3 - y2
            c = SQR(a^2 + b^2)
            IF c <> 0 THEN
                ang_a = ACOS(a / c) * 180 / 3.1415927
		ang_a_pub=ang_a
                dispinfotext("Angle: " + STR$(ang_a) + CHR$(10) + _
                    "Length: " + STR$(c) _
                    + CHR$(10) + "x1: " + STR$(x2) _
                    + CHR$(10) + "y1: " + STR$(y2) _
                    + CHR$(10) + "x2: " + STR$(x3) _
                    + CHR$(10) + "y2: " + STR$(y3) _
                    )
            END IF

        END WITH

    END SUB

    private :
    SUB drawpitchfork(xb , yb , xc , yc , xd , yd)

        DEFSNG x2 , y2 , x3 , y3 , x4 , y4
        x2 = xb
        y2 = yb
        x3 = xc
        y3 = yc
        x4 = xd
        y4 = yd

        WITH QChart
            .ClearBuffer
            .buffer.BMP = .buffertmpz2.BMP
            'MoveToEx(.Buffer.handle,x3-1,y3,0)
            'LineTo(.Buffer.handle,x3+x4-x2,y3+y4-y2)
            DIM medx AS INTEGER , medy AS INTEGER
            medx = x4 + (x3 - x4) * 0.5
            medy = y4 + (y3 - y4) * 0.5
            .Buffer.Line(x2 , y2 , medx + (medx - x2) * 100 , medy + (medy - y2) * 100 , pencolor)
            .Buffer.Line(x4 , y4 , x4 + (medx - x2) * 100 , y4 + (medy - y2) * 100 , pencolor)
            .Buffer.Line(x3 , y3 , x3 + (medx - x2) * 100 , y3 + (medy - y2) * 100 , pencolor)
            .buffertmp.BMP = .buffer.BMP
            .PaintChart
            DIM a AS DOUBLE , b AS DOUBLE , c AS DOUBLE , ang_a AS DOUBLE
            a = x3 - x2
            b = y3 - y2
            c = SQR(a^2 + b^2)
            IF c <> 0 THEN
                ang_a = ACOS(a / c) * 180 / 3.1415927
		ang_a_pub=ang_a
                dispinfotext("Angle: " + STR$(ang_a) + CHR$(10) + _
                    "Length: " + STR$(c) _
                    + CHR$(10) + "x1: " + STR$(x2) _
                    + CHR$(10) + "y1: " + STR$(y2) _
                    + CHR$(10) + "x2: " + STR$(x3) _
                    + CHR$(10) + "y2: " + STR$(y3) _
                    )
            END IF

        END WITH

    END SUB

    private :
    SUB drawpriceext(xb , yb , xc , yc , xd , yd)

        DEFSNG x2 , y2 , x3 , y3 , x4 , y4
        x2 = xb
        y2 = yb
        x3 = xc
        y3 = yc
        x4 = xd
        y4 = yd

        WITH QChart
            .ClearBuffer
            .buffer.BMP = .buffertmpz2.BMP
            'MoveToEx(.Buffer.handle,x3-1,y3,0)
            'LineTo(.Buffer.handle,x3+x4-x2,y3+y4-y2)
            DIM quarter AS DOUBLE
            quarter = (y4 - y2) / 4
            .Buffer.Line(x3 , y3 , x3 + 500 , y3 , pencolor)
            .Buffer.TextOut(x3 - 40 , y3 , "0%" , pencolor , &hffffff)
            .Buffer.Line(x3 , y3 + quarter , x3 + 500 , y3 + quarter , pencolor)
            .Buffer.TextOut(x3 - 40 , y3 + quarter , "25%" , pencolor , &hffffff)
            .Buffer.Line(x3 , y3 + quarter * 2 , x3 + 500 , y3 + quarter * 2 , pencolor)
            .Buffer.TextOut(x3 - 40 , y3 + quarter * 2 , "50%" , pencolor , &hffffff)
            .Buffer.Line(x3 , y3 + 0.618*(y4 - y2) , x3 + 500 , y3 + 0.618*(y4 - y2) , pencolor)
            .Buffer.TextOut(x3 - 40 , y3 + 0.618*(y4 - y2) , "61.8%" , pencolor , &hffffff)
            .Buffer.Line(x3 , y3 + quarter * 3 , x3 + 500 , y3 + quarter * 3 , pencolor)
            .Buffer.TextOut(x3 - 40 , y3 + quarter * 3 , "75%" , pencolor , &hffffff)
            .Buffer.Line(x3 , y3 + quarter * 4 , x3 + 500 , y3 + quarter * 4 , pencolor)
            .Buffer.TextOut(x3 - 40 , y3 + quarter * 4 , "100%" , pencolor , &hffffff)

            .buffertmp.BMP = .buffer.BMP
            .PaintChart
            DIM a AS DOUBLE , b AS DOUBLE , c AS DOUBLE , ang_a AS DOUBLE
            a = x3 - x2
            b = y3 - y2
            c = SQR(a^2 + b^2)
            IF c <> 0 THEN
                ang_a = ACOS(a / c) * 180 / 3.1415927
		ang_a_pub=ang_a
                dispinfotext("Angle: " + STR$(ang_a) + CHR$(10) + _
                    "Length: " + STR$(c) _
                    + CHR$(10) + "x1: " + STR$(x2) _
                    + CHR$(10) + "y1: " + STR$(y2) _
                    + CHR$(10) + "x2: " + STR$(x3) _
                    + CHR$(10) + "y2: " + STR$(y3) _
                    )
            END IF

        END WITH

    END SUB

    private :
    SUB drawtimeext(xb , yb , xc , yc , xd , yd)

        DEFSNG x2 , y2 , x3 , y3 , x4 , y4
        x2 = xb
        y2 = yb
        x3 = xc
        y3 = yc
        x4 = xd
        y4 = yd

        WITH QChart
            .ClearBuffer
            .buffer.BMP = .buffertmpz2.BMP
            'MoveToEx(.Buffer.handle,x3-1,y3,0)
            'LineTo(.Buffer.handle,x3+x4-x2,y3+y4-y2)
            DIM quarter AS DOUBLE
            quarter = (x4 - x2) / 4
            .Buffer.Line(x3 , y3 , x3 , y3 + 500 , pencolor)
            .Buffer.TextOut(x3 , y3 - 40 , "0%" , pencolor , &hffffff)
            .Buffer.Line(x3 + quarter , y3 , x3 + quarter , y3 + 500 , pencolor)
            .Buffer.TextOut(x3 + quarter , y3 - 40 , "25%" , pencolor , &hffffff)
            .Buffer.Line(x3 + quarter * 2 , y3 , x3 + quarter * 2 , y3 + 500 , pencolor)
            .Buffer.TextOut(x3 + quarter * 2 , y3 - 40 , "50%" , pencolor , &hffffff)
            .Buffer.Line(x3 + 0.618*(x4-x2) , y3 , x3 + 0.618*(x4-x2) , y3 + 500 , pencolor)
            .Buffer.TextOut(x3 + 0.618*(x4-x2) , y3 - 40 , "61.8%" , pencolor , &hffffff)
            .Buffer.Line(x3 + quarter * 3 , y3 , x3 + quarter * 3 , y3 + 500 , pencolor)
            .Buffer.TextOut(x3 + quarter * 3 , y3 - 40 , "75%" , pencolor , &hffffff)
            .Buffer.Line(x3 + quarter * 4 , y3 , x3 + quarter * 4 , y3 + 500 , pencolor)
            .Buffer.TextOut(x3 + quarter * 4 , y3 - 40 , "100%" , pencolor , &hffffff)

            .buffertmp.BMP = .buffer.BMP
            .PaintChart
            DIM a AS DOUBLE , b AS DOUBLE , c AS DOUBLE , ang_a AS DOUBLE
            a = x3 - x2
            b = y3 - y2
            c = SQR(a^2 + b^2)
            IF c <> 0 THEN
                ang_a = ACOS(a / c) * 180 / 3.1415927
		ang_a_pub=ang_a
                dispinfotext("Angle: " + STR$(ang_a) + CHR$(10) + _
                    "Length: " + STR$(c) _
                    + CHR$(10) + "x1: " + STR$(x2) _
                    + CHR$(10) + "y1: " + STR$(y2) _
                    + CHR$(10) + "x2: " + STR$(x3) _
                    + CHR$(10) + "y2: " + STR$(y3) _
                    )
            END IF

        END WITH

    END SUB

    private :
    SUB drawhline(xb , yb , xc , yc)

        DEFSNG x2 , y2 , x3 , y3
        x2 = xb
        y2 = yb
        x3 = xc
        y3 = yc

        WITH QChart
            .ClearBuffer
            .buffer.BMP = .buffertmpz.BMP
            'MoveToEx(.Buffer.handle,x2,y2,0)
            'LineTo(.Buffer.handle,x3,y2)
            .Buffer.Line(x2 , y2 , x3 , y2 , pencolor)
            .buffertmp.BMP = .buffer.BMP
            .PaintChart
            DIM a AS DOUBLE , b AS DOUBLE , c AS DOUBLE , ang_a AS DOUBLE
            a = x3 - x2
            b = y3 - y2
            c = SQR(a^2 + b^2)
            IF c <> 0 THEN
                ang_a = ACOS(a / c) * 180 / 3.1415927
		ang_a_pub=ang_a
                dispinfotext("Angle: " + STR$(ang_a) + CHR$(10) + _
                    "Length: " + STR$(c) _
                    + CHR$(10) + "x1: " + STR$(x2) _
                    + CHR$(10) + "y1: " + STR$(y2) _
                    + CHR$(10) + "x2: " + STR$(x3) _
                    + CHR$(10) + "y2: " + STR$(y3) _
                    )
            END IF

        END WITH

    END SUB

    private :
    SUB drawvline(xb , yb , xc , yc)

        DEFSNG x2 , y2 , x3 , y3
        x2 = xb
        y2 = yb
        x3 = xc
        y3 = yc

        WITH QChart
            .ClearBuffer
            .buffer.BMP = .buffertmpz.BMP
            'MoveToEx(.Buffer.handle,x2,y2,0)
            'LineTo(.Buffer.handle,x2,y3)
            .Buffer.Line(x2 , y2 , x2 , y3 , pencolor)
            .buffertmp.BMP = .buffer.BMP
            .PaintChart
            DIM a AS DOUBLE , b AS DOUBLE , c AS DOUBLE , ang_a AS DOUBLE
            a = x3 - x2
            b = y3 - y2
            c = SQR(a^2 + b^2)
            IF c <> 0 THEN
                ang_a = ACOS(a / c) * 180 / 3.1415927
		ang_a_pub=ang_a
                dispinfotext("Angle: " + STR$(ang_a) + CHR$(10) + _
                    "Length: " + STR$(c) _
                    + CHR$(10) + "x1: " + STR$(x2) _
                    + CHR$(10) + "y1: " + STR$(y2) _
                    + CHR$(10) + "x2: " + STR$(x3) _
                    + CHR$(10) + "y2: " + STR$(y3) _
                    )
            END IF

        END WITH

    END SUB

    private :
    SUB drawsqr(xb , yb , xc , yc)

        DEFSNG x2 , y2 , x3 , y3
        x2 = xb
        y2 = yb
        x3 = xc
        y3 = yc

        WITH QChart
            .ClearBuffer
            .buffer.BMP = .buffertmpz.BMP
            'MoveToEx(.Buffer.handle,x2,y2,0)
            'LineTo(.Buffer.handle,x3,y3)
            .Buffer.Line(x2 , y2 , x3 , y3 , pencolor)
            DIM a AS DOUBLE , b AS DOUBLE , c AS DOUBLE , ang_a AS DOUBLE
            a = x3 - x2
            b = y3 - y2
            c = SQR(a^2 + b^2)
            IF c <> 0 THEN
                ang_a = ACOS(a / c) * 180 / 3.1415927
		ang_a_pub=ang_a
                dispinfotext("Angle: " + STR$(ang_a) + CHR$(10) + _
                    "Length: " + STR$(c) _
                    + CHR$(10) + "x1: " + STR$(x2) _
                    + CHR$(10) + "y1: " + STR$(y2) _
                    + CHR$(10) + "x2: " + STR$(x3) _
                    + CHR$(10) + "y2: " + STR$(y3) _
                    )
            END IF
            DIM x4 AS DOUBLE , y4 AS DOUBLE
            IF y3 > y2 THEN
                ang_a = ang_a * - 1
            END IF
            x4 = COS((ang_a - 90) * rad) * c + x3
            y4 = y3 - SIN((ang_a - 90) * rad) * c
            'MoveToEx(.Buffer.handle,x3,y3,0)
            'LineTo(.Buffer.handle,x4,y4)
            .Buffer.Line(x3 , y3 , x4 , y4 , pencolor)

            ang_a = ang_a - 90
            'MoveToEx(.Buffer.handle,x4,y4,0)
            .Buffer.Line(x4 , y4 , COS((ang_a - 90) * rad) * c + x4 , y4 - SIN((ang_a - 90) * rad) * c , pencolor)
            x4 = COS((ang_a - 90) * rad) * c + x4
            y4 = y4 - SIN((ang_a - 90) * rad) * c
            'LineTo(.Buffer.handle,x4,y4)

            ang_a = ang_a - 90
            .Buffer.Line(x4 , y4 , COS((ang_a - 90) * rad) * c + x4 , y4 - SIN((ang_a - 90) * rad) * c , pencolor)
            'MoveToEx(.Buffer.handle,x4,y4,0)
            'x4=cos((ang_a-90)*rad)*c+x4
            'y4=y4-sin((ang_a-90)*rad)*c
            'LineTo(.Buffer.handle,x4,y4)
            .buffertmp.BMP = .buffer.BMP
            .PaintChart

        END WITH

    END SUB

    private :
    SUB drawtri(xb , yb , xc , yc)

        DEFSNG x2 , y2 , x3 , y3
        x2 = xb
        y2 = yb
        x3 = xc
        y3 = yc

        WITH QChart
            .ClearBuffer
            .buffer.BMP = .buffertmpz.BMP
            'MoveToEx(.Buffer.handle,x2,y2,0)
            'LineTo(.Buffer.handle,x3,y3)
            .Buffer.Line(x2 , y2 , x3 , y3 , pencolor)
            DIM a AS DOUBLE , b AS DOUBLE , c AS DOUBLE , ang_a AS DOUBLE
            a = x3 - x2
            b = y3 - y2
            c = SQR(a^2 + b^2)
            IF c <> 0 THEN
                ang_a = ACOS(a / c) * 180 / 3.1415927
		ang_a_pub=ang_a
                dispinfotext("Angle: " + STR$(ang_a) + CHR$(10) + _
                    "Length: " + STR$(c) _
                    + CHR$(10) + "x1: " + STR$(x2) _
                    + CHR$(10) + "y1: " + STR$(y2) _
                    + CHR$(10) + "x2: " + STR$(x3) _
                    + CHR$(10) + "y2: " + STR$(y3) _
                    )
            END IF
            DIM x4 AS DOUBLE , y4 AS DOUBLE
            IF y3 > y2 THEN
                ang_a = ang_a * - 1
            END IF
            x4 = COS((ang_a - 120) * rad) * c + x3
            y4 = y3 - SIN((ang_a - 120) * rad) * c
            'MoveToEx(.Buffer.handle,x3,y3,0)
            'LineTo(.Buffer.handle,x4,y4)
            .Buffer.Line(x3 , y3 , x4 , y4 , pencolor)

            ang_a = ang_a - 120
            'MoveToEx(.Buffer.handle,x4,y4,0)
            .Buffer.Line(x4 , y4 , COS((ang_a - 120) * rad) * c + x4 , y4 - SIN((ang_a - 120) * rad) * c , pencolor)
            'x4=cos((ang_a-120)*rad)*c+x4
            'y4=y4-sin((ang_a-120)*rad)*c
            'LineTo(.Buffer.handle,x4,y4)
            .buffertmp.BMP = .buffer.BMP
            .PaintChart
        END WITH

    END SUB

    private :
    SUB drawcircle(xb , yb , xc , yc)

        DEFSNG x2 , y2 , x3 , y3
        x2 = xb
        y2 = yb
        x3 = xc
        y3 = yc

        WITH QChart
            .ClearBuffer
            .buffer.BMP = .buffertmpz.BMP
            DIM a AS DOUBLE , b AS DOUBLE , c AS DOUBLE , ang_a AS DOUBLE
            a = x3 - x2
            b = y3 - y2
            c = SQR(a^2 + b^2)
            IF c <> 0 THEN
                ang_a = ACOS(a / c) * 180 / 3.1415927
		ang_a_pub=ang_a
                dispinfotext("Angle: " + STR$(ang_a) + CHR$(10) + _
                    "Length: " + STR$(c) _
                    + CHR$(10) + "x1: " + STR$(x2) _
                    + CHR$(10) + "y1: " + STR$(y2) _
                    + CHR$(10) + "x2: " + STR$(x3) _
                    + CHR$(10) + "y2: " + STR$(y3) _
                    )
            END IF

            DIM angle AS DOUBLE , cs AS DOUBLE , sn AS DOUBLE
            FOR angle = 0 TO 1.57 STEP 0.001
                IF COS(angle) <> 0 AND SIN(angle) <> 0 THEN
                    cs = c * COS(angle)
                    sn = c * SIN(angle)
                    .buffer.Pset(x2 + cs , y2 + sn , pencolor)
                    .buffer.Pset(x2 - cs , y2 + sn , pencolor)
                    .buffer.Pset(x2 + cs , y2 - sn , pencolor)
                    .buffer.Pset(x2 - cs , y2 - sn , pencolor)
                END IF
            NEXT angle
            .buffertmp.BMP = .buffer.BMP
            .PaintChart
        END WITH

    END SUB

    private :
    SUB drawcross(xb , yb , xc , yc)

        DEFSNG x2 , y2 , x3 , y3
        x2 = xb
        y2 = yb
        x3 = xc
        y3 = yc

        WITH QChart
            .ClearBuffer
            .buffer.BMP = .buffertmpz.BMP
            'MoveToEx(.Buffer.handle,x2,y2,0)
            'LineTo(.Buffer.handle,x3,y3)
            .Buffer.Line(x2 , y2 , x3 , y3 , pencolor)
            DIM a AS DOUBLE , b AS DOUBLE , c AS DOUBLE , ang_a AS DOUBLE
            a = x3 - x2
            b = y3 - y2
            c = SQR(a^2 + b^2)
            IF c <> 0 THEN
                ang_a = ACOS(a / c) * 180 / 3.1415927
		ang_a_pub=ang_a
                dispinfotext("Angle: " + STR$(ang_a) + CHR$(10) + _
                    "Length: " + STR$(c) _
                    + CHR$(10) + "x1: " + STR$(x2) _
                    + CHR$(10) + "y1: " + STR$(y2) _
                    + CHR$(10) + "x2: " + STR$(x3) _
                    + CHR$(10) + "y2: " + STR$(y3) _
                    )
            END IF
            DIM x4 AS DOUBLE , y4 AS DOUBLE
            IF y3 > y2 THEN
                ang_a = ang_a * - 1
            END IF
            'MoveToEx(.Buffer.handle,x3-(x3-x2)/2,y3-(y3-y2)/2,0)
            'LineTo(.Buffer.handle,x4,y4)
            DIM ilcross AS INTEGER
            FOR ilcross = 0 TO crosslevelslist.ItemCount - 1
                x4 = COS((ang_a - 90) * rad) * c * 0.5 + x3 - (x3 - x2) * VAL(crosslevelslist.Item(ilcross))
                y4 = y3 - (y3 - y2) * VAL(crosslevelslist.Item(ilcross)) - SIN((ang_a - 90) * rad) * c * 0.5
                .Buffer.Line(x3 - (x3 - x2) * VAL(crosslevelslist.Item(ilcross)) , y3 - (y3 - y2) * VAL(crosslevelslist.Item(ilcross)) , x4 , y4 , pencolor)
            NEXT ilcross
            'MoveToEx(.Buffer.handle,x3-(x3-x2)/2,y3-(y3-y2)/2,0)
            'LineTo(.Buffer.handle,x4,y4)
            FOR ilcross = 0 TO crosslevelslist.ItemCount - 1
                x4 = COS((ang_a + 90) * rad) * c * 0.5 + x3 - (x3 - x2) * VAL(crosslevelslist.Item(ilcross))
                y4 = y3 - (y3 - y2) * VAL(crosslevelslist.Item(ilcross)) - SIN((ang_a + 90) * rad) * c * 0.5
                .Buffer.Line(x3 - (x3 - x2) * VAL(crosslevelslist.Item(ilcross)) , y3 - (y3 - y2) * VAL(crosslevelslist.Item(ilcross)) , x4 , y4 , pencolor)
            NEXT ilcross
            .buffertmp.BMP = .buffer.BMP
            .PaintChart
        END WITH

    END SUB

    private :
    SUB drawinvcircle(xb , yb , xc , yc)

        DEFSNG x2 , y2 , x3 , y3
        x2 = xb
        y2 = yb
        x3 = xc
        y3 = yc

        WITH QChart
            .ClearBuffer
            .buffer.BMP = .buffertmpz.BMP
            DIM a AS DOUBLE , b AS DOUBLE , c AS DOUBLE , ang_a AS DOUBLE
            a = x3 - x2
            b = y3 - y2
            c = SQR(a^2 + b^2)
            IF c <> 0 THEN
                ang_a = ACOS(a / c) * 180 / 3.1415927
		ang_a_pub=ang_a
                dispinfotext("Angle: " + STR$(ang_a) + CHR$(10) + _
                    "Length: " + STR$(c) _
                    + CHR$(10) + "x1: " + STR$(x2) _
                    + CHR$(10) + "y1: " + STR$(y2) _
                    + CHR$(10) + "x2: " + STR$(x3) _
                    + CHR$(10) + "y2: " + STR$(y3) _
                    )
            END IF

            DIM angle AS DOUBLE , cs AS DOUBLE , sn AS DOUBLE
            FOR angle = 0 TO 1.57 STEP 0.001
                IF COS(angle) <> 0 AND SIN(angle) <> 0 THEN
                    cs = c / COS(angle)
                    sn = c / SIN(angle)
                    .buffer.Pset(x2 + cs , y2 + sn , pencolor)
                    .buffer.Pset(x2 - cs , y2 + sn , pencolor)
                    .buffer.Pset(x2 + cs , y2 - sn , pencolor)
                    .buffer.Pset(x2 - cs , y2 - sn , pencolor)
                END IF
            NEXT angle
            .buffertmp.BMP = .buffer.BMP
            .PaintChart
        END WITH

    END SUB

    private :
    SUB drawaiming(xb , yb , xc , yc)

        DEFSNG x2 , y2 , x3 , y3
        x2 = xb
        y2 = yb
        x3 = xc
        y3 = yc

        WITH QChart
            .ClearBuffer
            .buffer.BMP = .buffertmpz.BMP
            'MoveToEx(.Buffer.handle,x2,y2,0)
            'LineTo(.Buffer.handle,x2,y3)
            graphcursorpos2
            .Buffer.Line(x3 , 0 , x3 , graph.Height , pencolor)
            .Buffer.TextOut(x3 - 45 , graphvspace + 45 , graphdateoncur , pencolor , &hffffff)
            .Buffer.Line(0 , y3 , graph.Width , y3 , pencolor)
            .Buffer.TextOut(0 , y3 , STR$(graphpriceoncur) , pencolor , &hffffff)
            .buffertmp.BMP = .buffer.BMP
            .PaintChart
            DIM a AS DOUBLE , b AS DOUBLE , c AS DOUBLE , ang_a AS DOUBLE
            a = x3 - x2
            b = y3 - y2
            c = SQR(a^2 + b^2)
            IF c <> 0 THEN
                ang_a = ACOS(a / c) * 180 / 3.1415927
		ang_a_pub=ang_a
                dispinfotext("Angle: " + STR$(ang_a) + CHR$(10) + _
                    "Length: " + STR$(c) _
                    + CHR$(10) + "x1: " + STR$(x2) _
                    + CHR$(10) + "y1: " + STR$(y2) _
                    + CHR$(10) + "x2: " + STR$(x3) _
                    + CHR$(10) + "y2: " + STR$(y3) _
                    )
            END IF

        END WITH

    END SUB

    private :
    SUB drawhand(xb , yb , xc , yc)

        DEFSNG x2 , y2 , x3 , y3
        x2 = xb
        y2 = yb
        x3 = xc
        y3 = yc

        WITH QChart
            '.ClearBuffer
            '.restorebuffertmp
            'MoveToEx(.Buffer.handle,x2,y2,0)
            'LineTo(.Buffer.handle,x3,y3)
            .Buffer.Pset(x3 , y3 , pencolor)
            .Buffer.Pset(x3 - 1 , y3 , pencolor)
            .Buffer.Pset(x3 - 1 , y3 - 1 , pencolor)
            .Buffer.Pset(x3 , y3 - 1 , pencolor)
            .Buffer.Pset(x3 + 1 , y3 - 1 , pencolor)
            .Buffer.Pset(x3 + 1 , y3 , pencolor)
            .Buffer.Pset(x3 + 1 , y3 + 1 , pencolor)
            .Buffer.Pset(x3 , y3 + 1 , pencolor)
            .Buffer.Pset(x3 - 1 , y3 + 1 , pencolor)
            .buffertmp.BMP = .buffer.BMP
            .PaintChart
            DIM a AS DOUBLE , b AS DOUBLE , c AS DOUBLE , ang_a AS DOUBLE
            a = x3 - x2
            b = y3 - y2
            c = SQR(a^2 + b^2)
            IF c <> 0 THEN
                ang_a = ACOS(a / c) * 180 / 3.1415927
		ang_a_pub=ang_a
                dispinfotext("Angle: " + STR$(ang_a) + CHR$(10) + _
                    "Length: " + STR$(c) _
                    + CHR$(10) + "x1: " + STR$(x2) _
                    + CHR$(10) + "y1: " + STR$(y2) _
                    + CHR$(10) + "x2: " + STR$(x3) _
                    + CHR$(10) + "y2: " + STR$(y3) _
                    )
            END IF

        END WITH

    END SUB

    private :
    SUB drawsin(xb , yb , xc , yc)

        DEFSNG x2 , y2 , x3 , y3
        x2 = xb
        y2 = yb
        x3 = xc
        y3 = yc

        WITH QChart
            .ClearBuffer
            .buffer.BMP = .buffertmpz.BMP
            DIM a AS DOUBLE , b AS DOUBLE , c AS DOUBLE , ang_a AS DOUBLE
            a = x3 - x2
            b = y3 - y2
            c = SQR(a^2 + b^2)
            IF c <> 0 THEN
                ang_a = ACOS(a / c) * 180 / 3.1415927
		ang_a_pub=ang_a
                dispinfotext("Angle: " + STR$(ang_a) + CHR$(10) + _
                    "Length: " + STR$(c) _
                    + CHR$(10) + "x1: " + STR$(x2) _
                    + CHR$(10) + "y1: " + STR$(y2) _
                    + CHR$(10) + "x2: " + STR$(x3) _
                    + CHR$(10) + "y2: " + STR$(y3) _
                    )
            END IF

            DIM angle AS DOUBLE , cs AS DOUBLE , sn AS DOUBLE
            FOR angle = 0 TO 50.24 STEP 0.005
                IF SIN(angle <> 0) THEN
                    .buffer.Pset(x2 + angle * a , y2 + b * SIN(angle) , pencolor)
                END IF
            NEXT angle
            .buffertmp.BMP = .buffer.BMP
            .PaintChart
        END WITH

    END SUB

    private :
    SUB drawlog(xb , yb , xc , yc)

        DEFSNG x2 , y2 , x3 , y3
        x2 = xb
        y2 = yb
        x3 = xc
        y3 = yc

        WITH QChart
            .ClearBuffer
            .buffer.BMP = .buffertmpz.BMP
            DIM a AS DOUBLE , b AS DOUBLE , c AS DOUBLE , ang_a AS DOUBLE
            a = x3 - x2
            b = y3 - y2
            c = SQR(a^2 + b^2)
            IF c <> 0 THEN
                ang_a = ACOS(a / c) * 180 / 3.1415927
		ang_a_pub=ang_a
                dispinfotext("Angle: " + STR$(ang_a) + CHR$(10) + _
                    "Length: " + STR$(c) _
                    + CHR$(10) + "x1: " + STR$(x2) _
                    + CHR$(10) + "y1: " + STR$(y2) _
                    + CHR$(10) + "x2: " + STR$(x3) _
                    + CHR$(10) + "y2: " + STR$(y3) _
                    )
            END IF

            DIM ilog AS DOUBLE , cs AS DOUBLE , sn AS DOUBLE
            FOR ilog = 1 TO 1000 STEP 0.1
                IF LOG(ilog) <> 0 THEN
                    IF reverse = 0 THEN
                        IF Flip = 0 THEN
                            .buffer.Pset(x3 + ilog , y3 - LOG(ilog) * logamplitude , pencolor)
                        ELSE
                            .buffer.Pset(x3 + ilog - 1001 , y3 - LOG(1001 - ilog) * logamplitude , pencolor)
                        END IF
                    ELSE
                        IF Flip = 0 THEN
                            .buffer.Pset(x3 + ilog , y3 + LOG(ilog) * logamplitude , pencolor)
                        ELSE
                            .buffer.Pset(x3 + ilog - 1001 , y3 + LOG(1001 - ilog) * logamplitude , pencolor)
                        END IF
                    END IF
                    'for ilog=0 to 21 step 0.003
                    'if exp(ilog)<>0 then
                    '.buffer.pset(x3+ilog*logamplitude,y3-exp(ilog),pencolor)
                END IF
            NEXT angle
            .buffertmp.BMP = .buffer.BMP
            .PaintChart
        END WITH

    END SUB

    private :
    SUB drawexp(xb , yb , xc , yc)

        DEFSNG x2 , y2 , x3 , y3
        x2 = xb
        y2 = yb
        x3 = xc
        y3 = yc

        WITH QChart
            .ClearBuffer
            .buffer.BMP = .buffertmpz.BMP
            DIM a AS DOUBLE , b AS DOUBLE , c AS DOUBLE , ang_a AS DOUBLE
            a = x3 - x2
            b = y3 - y2
            c = SQR(a^2 + b^2)
            IF c <> 0 THEN
                ang_a = ACOS(a / c) * 180 / 3.1415927
		ang_a_pub=ang_a
                dispinfotext("Angle: " + STR$(ang_a) + CHR$(10) + _
                    "Length: " + STR$(c) _
                    + CHR$(10) + "x1: " + STR$(x2) _
                    + CHR$(10) + "y1: " + STR$(y2) _
                    + CHR$(10) + "x2: " + STR$(x3) _
                    + CHR$(10) + "y2: " + STR$(y3) _
                    )
            END IF

            DIM ilog AS DOUBLE , cs AS DOUBLE , sn AS DOUBLE
            'for ilog=1 to 1000 step 0.1
            'if log(ilog)<>0 then
            '.buffer.pset(x3+ilog,y3-log(ilog)*logamplitude,pencolor)
            FOR ilog = 0 TO 21 STEP 0.003
                IF EXP(ilog) <> 0 THEN
                    IF reverse = 0 THEN
                        IF Flip = 0 THEN
                            .buffer.Pset(x3 + ilog * logamplitude , y3 - EXP(ilog) , pencolor)
                        ELSE
                            .buffer.Pset(x3 + (ilog - 21) * logamplitude , y3 - EXP(21 - ilog) , pencolor)
                        END IF
                    ELSE
                        IF Flip = 0 THEN
                            .buffer.Pset(x3 + ilog * logamplitude , y3 + EXP(ilog) , pencolor)
                        ELSE
                            .buffer.Pset(x3 + (ilog - 21) * logamplitude , y3 + EXP(21 - ilog) , pencolor)
                        END IF
                    END IF
                END IF
            NEXT angle
            .buffertmp.BMP = .buffer.BMP
            .PaintChart
        END WITH

    END SUB

    private :
    SUB drawellipse(xb , yb , xc , yc)

        DEFSNG x2 , y2 , x3 , y3
        x2 = xb
        y2 = yb
        x3 = xc
        y3 = yc

        WITH QChart
            .ClearBuffer
            .buffer.BMP = .buffertmpz.BMP
            DIM a AS DOUBLE , b AS DOUBLE , c AS DOUBLE , ang_a AS DOUBLE
            a = x3 - x2
            b = y3 - y2
            c = SQR(a^2 + b^2)
            IF c <> 0 THEN
                ang_a = ACOS(a / c) * 180 / 3.1415927
		ang_a_pub=ang_a
                dispinfotext("Angle: " + STR$(ang_a) + CHR$(10) + _
                    "Length: " + STR$(c) _
                    + CHR$(10) + "x1: " + STR$(x2) _
                    + CHR$(10) + "y1: " + STR$(y2) _
                    + CHR$(10) + "x2: " + STR$(x3) _
                    + CHR$(10) + "y2: " + STR$(y3) _
                    )
            END IF

            DIM angle AS DOUBLE , cs AS DOUBLE , sn AS DOUBLE
            FOR angle = 0 TO 1.57 STEP 0.001
                IF COS(angle) <> 0 AND SIN(angle) <> 0 THEN
                    cs = a * COS(angle)
                    sn = b * SIN(angle)
                    .buffer.Pset(x3 + cs , y2 + sn , pencolor)
                    .buffer.Pset(x3 - cs , y2 + sn , pencolor)
                    .buffer.Pset(x3 + cs , y2 - sn , pencolor)
                    .buffer.Pset(x3 - cs , y2 - sn , pencolor)
                END IF
            NEXT angle
            .buffertmp.BMP = .buffer.BMP
            .PaintChart
        END WITH

    END SUB

    private :
    SUB drawsq9f(xb , yb , xc , yc)

        DEFSNG x2 , y2 , x3 , y3
        x2 = xb
        y2 = yb
        x3 = xc
        y3 = yc

        WITH QChart
            .ClearBuffer
            .buffer.BMP = .buffertmpz.BMP
            'MoveToEx(.Buffer.handle,x2,y2,0)
            'LineTo(.Buffer.handle,x2,y3)
            graphcursorpos2
            '.Buffer.line(x3,0,x3,graph.height,pencolor)
            '.Buffer.textout(x3,graphvspace+45,graphdateoncur,pencolor,&hffffff)
            .Buffer.Line(0 , y3 , graph.Width , y3 , pencolor)
            '.Buffer.textout(0,y3,str$(graphpriceoncur),pencolor,&hffffff)
            DIM ydeg AS DOUBLE , sqfact AS INTEGER , stepdeg AS INTEGER , ydeg2 AS DOUBLE
            sqfact = 100
            stepdeg = 15
            FOR i = 1 TO 24
                IF sq9diredit.Text = "1" THEN
                    ydeg = (SQR(graphpriceoncur * VAL(sq9edit.Text)) + stepdeg / 360 * i) ^2 / VAL(sq9edit.Text)
                END IF
                IF sq9diredit.Text = "-1" THEN
                    ydeg = (SQR(graphpriceoncur * VAL(sq9edit.Text)) - stepdeg / 360 * i) ^2 / VAL(sq9edit.Text)
                END IF
                ydeg2 = (pricechartpos(1,0) - ydeg) / (pricechartpos(1,0)-pricechartpos(0,0)) * (pricechartpos(0,1)-pricechartpos(1,1)) + pricechartpos(1,1)
                .Buffer.Line(0 , ydeg2 , graph.Width , ydeg2 , pencolor)
            NEXT i
            .buffertmp.BMP = .buffer.BMP
            .PaintChart
            DIM a AS DOUBLE , b AS DOUBLE , c AS DOUBLE , ang_a AS DOUBLE
            a = x3 - x2
            b = y3 - y2
            c = SQR(a^2 + b^2)
            IF c <> 0 THEN
                ang_a = ACOS(a / c) * 180 / 3.1415927
		ang_a_pub=ang_a
                dispinfotext("Angle: " + STR$(ang_a) + CHR$(10) + _
                    "Length: " + STR$(c) _
                    + CHR$(10) + "x1: " + STR$(x2) _
                    + CHR$(10) + "y1: " + STR$(y2) _
                    + CHR$(10) + "x2: " + STR$(x3) _
                    + CHR$(10) + "y2: " + STR$(y3) _
                    )
            END IF

        END WITH

    END SUB

    private :
    SUB drawtsq9f(xb , yb , xc , yc)

        DEFSNG x2 , y2 , x3 , y3
        x2 = xb
        y2 = yb
        x3 = xc
        y3 = yc

        WITH QChart
            .ClearBuffer
            .buffer.BMP = .buffertmpz.BMP
            graphcursorpos2
            .Buffer.Line(x3 , 0 , x3 , graph.Height , pencolor)
            DIM ydeg AS DOUBLE , sqfact AS INTEGER , stepdeg AS INTEGER , ydeg2 AS DOUBLE
            sqfact = 100
            stepdeg = 15
            DIM savedtsq9fs AS INTEGER
            savedtsq9fs = graphserialdateoncur
            FOR i = 1 TO 24
                IF sq9diredit.Text = "1" THEN
                    ydeg = (SQR(graphjuliendateoncur * VAL(sq9edit.Text)) + stepdeg / 360 * i) ^2 / VAL(sq9edit.Text)
                END IF
                IF sq9diredit.Text = "-1" THEN
                    ydeg = (SQR(graphjuliendateoncur * VAL(sq9edit.Text)) - stepdeg / 360 * i) ^2 / VAL(sq9edit.Text)
                END IF
                'ydeg2=(graphvhigh-ydeg)/graphpricespace*graphvspace+graphvbegin
                DEFLNG yy , mm , dd , dayofweek
                DIM j AS INTEGER
                DIM sq9xval AS INTEGER
                FOR j = savedtsq9fs TO graphserialdateend
                    dayofweek = DateFromSerial(j , yy , mm , dd)
                    IF INT(ydeg) = juliandate(dd , mm , yy) + 1 THEN
                        sq9xval = (j - graphserialdatebegin) / graphserialdatespace * graphhspace + graphhbegin
                        .Buffer.Line(sq9xval , 0 , sq9xval , graph.Height , pencolor)
                        savedtsq9fs = j
                        EXIT FOR
                    END IF
                NEXT j
            NEXT i
            .buffertmp.BMP = .buffer.BMP
            .PaintChart
            DIM a AS DOUBLE , b AS DOUBLE , c AS DOUBLE , ang_a AS DOUBLE
            a = x3 - x2
            b = y3 - y2
            c = SQR(a^2 + b^2)
            IF c <> 0 THEN
                ang_a = ACOS(a / c) * 180 / 3.1415927
		ang_a_pub=ang_a
                dispinfotext("Angle: " + STR$(ang_a) + CHR$(10) + _
                    "Length: " + STR$(c) _
                    + CHR$(10) + "x1: " + STR$(x2) _
                    + CHR$(10) + "y1: " + STR$(y2) _
                    + CHR$(10) + "x2: " + STR$(x3) _
                    + CHR$(10) + "y2: " + STR$(y3) _
                    )
            END IF

        END WITH

    END SUB

    private :
    SUB drawsq144(xb , yb , xc , yc)

        DEFSNG x2 , y2 , x3 , y3
        x2 = xb
        y2 = yb
        x3 = xc
        y3 = yc

        WITH QChart
            .ClearBuffer
            .buffer.BMP = .buffertmpz.BMP
            graphcursorpos2
            .Buffer.Line(0 , y3 , graph.Width , y3 , pencolor)
            DIM ydeg AS DOUBLE , sqfact AS INTEGER , stepdeg AS INTEGER , ydeg2 AS DOUBLE
            sqfact = VAL(sq144edit.Text)
            stepdeg = 1
            FOR i = 1 TO 24
                ydeg = graphpriceoncur / sqfact / 4
                ydeg = ydeg * 5
                IF sq144diredit.Text = "1" THEN
                    ydeg = ydeg + i
                END IF
                IF sq144diredit.Text = "-1" THEN
                    ydeg = ydeg - i
                END IF
                ydeg = ydeg / 5
                ydeg = ydeg * sqfact * 4
                ydeg2 = (graphvhigh - ydeg) / graphpricespace * graphvspace + graphvbegin
                .Buffer.Line(0 , ydeg2 , graph.Width , ydeg2 , pencolor)
            NEXT i
            .buffertmp.BMP = .buffer.BMP
            .PaintChart
            DIM a AS DOUBLE , b AS DOUBLE , c AS DOUBLE , ang_a AS DOUBLE
            a = x3 - x2
            b = y3 - y2
            c = SQR(a^2 + b^2)
            IF c <> 0 THEN
                ang_a = ACOS(a / c) * 180 / 3.1415927
		ang_a_pub=ang_a
                dispinfotext("Angle: " + STR$(ang_a) + CHR$(10) + _
                    "Length: " + STR$(c) _
                    + CHR$(10) + "x1: " + STR$(x2) _
                    + CHR$(10) + "y1: " + STR$(y2) _
                    + CHR$(10) + "x2: " + STR$(x3) _
                    + CHR$(10) + "y2: " + STR$(y3) _
                    )
            END IF

        END WITH

    END SUB

    private :
    SUB drawtsq144(xb , yb , xc , yc)

        DEFSNG x2 , y2 , x3 , y3
        x2 = xb
        y2 = yb
        x3 = xc
        y3 = yc

        WITH QChart
            .ClearBuffer
            .buffer.BMP = .buffertmpz.BMP
            graphcursorpos2
            .Buffer.Line(x3 , 0 , x3 , graph.Height , pencolor)
            DIM ydeg AS DOUBLE , sqfact AS INTEGER , stepdeg AS INTEGER , ydeg2 AS DOUBLE
            sqfact = VAL(sq144edit.Text)
            stepdeg = 1
            DIM savedtsq9fs AS INTEGER
            savedtsq9fs = graphserialdateoncur
            FOR i = 1 TO 24
                ydeg = graphjuliendateoncur / sqfact / 4
                ydeg = ydeg * 5
                IF sq9diredit.Text = "1" THEN
                    ydeg = ydeg + i
                END IF
                IF sq9diredit.Text = "-1" THEN
                    ydeg = ydeg - i
                END IF
                ydeg = ydeg / 5
                ydeg = ydeg * sqfact * 4
                'ydeg2=(graphvhigh-ydeg)/graphpricespace*graphvspace+graphvbegin
                DEFLNG yy , mm , dd , dayofweek
                DIM j AS INTEGER
                DIM sq9xval AS INTEGER
                FOR j = savedtsq9fs TO graphserialdateend
                    dayofweek = DateFromSerial(j , yy , mm , dd)
                    IF INT(ydeg) = juliandate(dd , mm , yy) + 1 THEN
                        sq9xval = (j - graphserialdatebegin) / graphserialdatespace * graphhspace + graphhbegin
                        .Buffer.Line(sq9xval , 0 , sq9xval , graph.Height , pencolor)
                        savedtsq9fs = j
                        EXIT FOR
                    END IF
                NEXT j
            NEXT i
            .buffertmp.BMP = .buffer.BMP
            .PaintChart
            DIM a AS DOUBLE , b AS DOUBLE , c AS DOUBLE , ang_a AS DOUBLE
            a = x3 - x2
            b = y3 - y2
            c = SQR(a^2 + b^2)
            IF c <> 0 THEN
                ang_a = ACOS(a / c) * 180 / 3.1415927
		ang_a_pub=ang_a
                dispinfotext("Angle: " + STR$(ang_a) + CHR$(10) + _
                    "Length: " + STR$(c) _
                    + CHR$(10) + "x1: " + STR$(x2) _
                    + CHR$(10) + "y1: " + STR$(y2) _
                    + CHR$(10) + "x2: " + STR$(x3) _
                    + CHR$(10) + "y2: " + STR$(y3) _
                    )
            END IF

        END WITH

    END SUB

    private :
    SUB drawpricecycles(xb , yb , xc , yc)

        DEFSNG x2 , y2 , x3 , y3
        x2 = xb
        y2 = yb
        x3 = xc
        y3 = yc

        WITH QChart
            .ClearBuffer
            .buffer.BMP = .buffertmpz.BMP
            .Buffer.Line(x2 , y2 , x3 , y3 , pencolor)
            '.Buffer.textout(x2-30,y2,"100",pencolor,&hffffff)
            DIM a AS DOUBLE , b AS DOUBLE , c AS DOUBLE , ang_a AS DOUBLE
            a = x3 - x2
            b = y3 - y2
            c = SQR(a^2 + b^2)
            IF c <> 0 THEN
                ang_a = ACOS(a / c) * 180 / 3.1415927
		ang_a_pub=ang_a
                dispinfotext("Angle: " + STR$(ang_a) + CHR$(10) + _
                    "Length: " + STR$(c) _
                    + CHR$(10) + "x1: " + STR$(x2) _
                    + CHR$(10) + "y1: " + STR$(y2) _
                    + CHR$(10) + "x2: " + STR$(x3) _
                    + CHR$(10) + "y2: " + STR$(y3) _
                    )
            END IF
            .Buffer.Line(x2 , y2 , x3 , y2 , pencolor)
            .Buffer.Line(x2 , y3 , x3 , y3 , pencolor)
            '.Buffer.textout(x2-30,y3,"0",pencolor,&hffffff)
            DIM y4 AS INTEGER
            FOR i = 1 TO 8
                y4 = y3 + (y3 - y2) * i
                .Buffer.Line(x2 , y4 , x3 , y4 , pencolor)
            NEXT i
            .buffertmp.BMP = .buffer.BMP
            .PaintChart
        END WITH

    END SUB


    private :
    SUB drawtimecycles(xb , yb , xc , yc)

        DEFSNG x2 , y2 , x3 , y3
        x2 = xb
        y2 = yb
        x3 = xc
        y3 = yc

        WITH QChart
            .ClearBuffer
            .buffer.BMP = .buffertmpz.BMP
            .Buffer.Line(x2 , y2 , x3 , y3 , pencolor)
            '.Buffer.textout(x2-30,y2,"100",pencolor,&hffffff)
            DIM a AS DOUBLE , b AS DOUBLE , c AS DOUBLE , ang_a AS DOUBLE
            a = x3 - x2
            b = y3 - y2
            c = SQR(a^2 + b^2)
            IF c <> 0 THEN
                ang_a = ACOS(a / c) * 180 / 3.1415927
		ang_a_pub=ang_a
                dispinfotext("Angle: " + STR$(ang_a) + CHR$(10) + _
                    "Length: " + STR$(c) _
                    + CHR$(10) + "x1: " + STR$(x2) _
                    + CHR$(10) + "y1: " + STR$(y2) _
                    + CHR$(10) + "x2: " + STR$(x3) _
                    + CHR$(10) + "y2: " + STR$(y3) _
                    )
            END IF
            .Buffer.Line(x2 , y2 , x2 , y3 , pencolor)
            .Buffer.Line(x3 , y2 , x3 , y3 , pencolor)
            '.Buffer.textout(x2-30,y3,"0",pencolor,&hffffff)
            DIM x4 AS INTEGER
            FOR i = 1 TO 8
                x4 = x3 + (x3 - x2) * i
                .Buffer.Line(x4 , y2 , x4 , y3 , pencolor)
            NEXT i
            .buffertmp.BMP = .buffer.BMP
            .PaintChart
        END WITH

    END SUB


    private :

    SUB drawlogspiral(xb , yb , xc , yc)

        DEFSNG x2 , y2 , x3 , y3
        x2 = xb
        y2 = yb
        x3 = xc
        y3 = yc

        WITH QChart
            .ClearBuffer
            .buffer.BMP = .buffertmpz.BMP
            DIM a0 AS DOUBLE , b0 AS DOUBLE , c AS DOUBLE , ang_a AS DOUBLE
            a0 = x3 - x2
            b0 = y3 - y2
            c = SQR(a0^2 + b0^2)
            IF c <> 0 THEN
                ang_a = ACOS(a0 / c) * 180 / 3.1415927
		ang_a_pub=ang_a
                dispinfotext("Angle: " + STR$(ang_a) + CHR$(10) + _
                    "Length: " + STR$(c) _
                    + CHR$(10) + "x1: " + STR$(x2) _
                    + CHR$(10) + "y1: " + STR$(y2) _
                    + CHR$(10) + "x2: " + STR$(x3) _
                    + CHR$(10) + "y2: " + STR$(y3) _
                    )
            END IF

            DIM angrot AS DOUBLE
            angrot = ACOS(a0 / c)
            DIM distlogspi AS DOUBLE
            IF c > 0 THEN
                distlogspi = 1 / (ABS(c))
            ELSE
                distlogspi = 0
            END IF

            DIM b AS double : b = DegToRad(80)
            DIM a AS double : a = SQR(distlogspi) 'rotation
            DIM i AS INTEGER
            FOR i = 0 TO 500
                DIM t AS double : t = a * rqPI / 4
                DIM r AS double : r = EXP(t * cot(b + SQR(distlogspi)))
                points(i).r = r + x2
                points(i).x = r * COS(t) + x2
                points(i).y = r * SIN(t) + y2
                a + = 0.2
            NEXT i
            FOR i = 1 TO 500
                .buffer.Line(points(i - 1).x , points(i - 1).y , points(i).x , points(i).y , pencolor)
            NEXT i


            .buffertmp.BMP = .buffer.BMP
            .PaintChart
        END WITH

    END SUB
    
    private :
    SUB drawpentag(xb , yb , xc , yc)
    
        DEFSNG x2 , y2 , x3 , y3
        x2 = xb
        y2 = yb
        x3 = xc
        y3 = yc

        WITH QChart
            .ClearBuffer
            .buffer.BMP = .buffertmpz.BMP
            DIM a AS DOUBLE , b AS DOUBLE , c AS DOUBLE , ang_a AS DOUBLE
            a = x3 - x2
            b = y3 - y2
            c = SQR(a^2 + b^2)
            IF c <> 0 THEN
                ang_a = ACOS(a / c) * 180 / 3.1415927
		ang_a_pub=ang_a
                dispinfotext("Angle: " + STR$(ang_a) + CHR$(10) + _
                    "Length: " + STR$(c) _
                    + CHR$(10) + "x1: " + STR$(x2) _
                    + CHR$(10) + "y1: " + STR$(y2) _
                    + CHR$(10) + "x2: " + STR$(x3) _
                    + CHR$(10) + "y2: " + STR$(y3) _
                    )
            END IF

            DIM angle AS DOUBLE , cs AS DOUBLE , sn AS DOUBLE
            FOR angle = 0 TO 1.57 STEP 0.001
                IF COS(angle) <> 0 AND SIN(angle) <> 0 THEN
                    cs = c * COS(angle)
                    sn = c * SIN(angle)
                    .buffer.Pset(x2 + cs , y2 + sn , pencolor)
                    .buffer.Pset(x2 - cs , y2 + sn , pencolor)
                    .buffer.Pset(x2 + cs , y2 - sn , pencolor)
                    .buffer.Pset(x2 - cs , y2 - sn , pencolor)
                END IF
            NEXT angle
            DIM x4 AS DOUBLE , y4 AS DOUBLE
            DIM x5 AS DOUBLE , y5 AS DOUBLE
            DIM x6 AS DOUBLE , y6 AS DOUBLE
            DIM x7 AS DOUBLE , y7 AS DOUBLE
            DIM x8 AS DOUBLE , y8 AS DOUBLE
            DIM x9 AS DOUBLE , y9 AS DOUBLE
            DIM x10 AS DOUBLE , y10 AS DOUBLE
            IF y3 > y2 THEN
                ang_a = ang_a * - 1
            END IF            

            x4=COS((ang_a + 72) * rad) * c + x2
            y4=y2 - SIN((ang_a + 72) * rad) * c
            x5=COS((ang_a + 144) * rad) * c + x2
            y5=y2 - SIN((ang_a + 144) * rad) * c
            x6=COS((ang_a + 216) * rad) * c + x2
            y6=y2 - SIN((ang_a + 216) * rad) * c
            x7=COS((ang_a + 288) * rad) * c + x2
            y7=y2 - SIN((ang_a + 288) * rad) * c            
                        
            .Buffer.Line(x3,y3,x5,y5, pencolor)
            .Buffer.Line(x5,y5,x7,y7, pencolor)
            .Buffer.Line(x7,y7,x4,y4, pencolor)
            .Buffer.Line(x4,y4,x6,y6, pencolor)
            .Buffer.Line(x6,y6,x3,y3, pencolor)
                                   
            .buffertmp.BMP = .buffer.BMP
            .PaintChart
        END WITH
        

'        DEFSNG x2 , y2 , x3 , y3
'        x2 = xb
'        y2 = yb
'        x3 = xc
'        y3 = yc
'
'        WITH QChart
'            .ClearBuffer
'            .buffer.BMP = .buffertmpz.BMP
'            'MoveToEx(.Buffer.handle,x2,y2,0)
'            'LineTo(.Buffer.handle,x3,y3)
'            '.Buffer.Line(x2 , y2 , x3 , y3 , pencolor)
'            DIM a AS DOUBLE , b AS DOUBLE , c AS DOUBLE , ang_a AS DOUBLE
'            a = x3 - x2
'            b = y3 - y2
'            c = SQR(a^2 + b^2)
'            IF c <> 0 THEN
'                ang_a = ACOS(a / c) * 180 / 3.1415927
		ang_a_pub=ang_a
'                dispinfotext("Angle: " + STR$(ang_a) + CHR$(10) + _
'                    "Length: " + STR$(c) _
'                    + CHR$(10) + "x1: " + STR$(x2) _
'                    + CHR$(10) + "y1: " + STR$(y2) _
'                    + CHR$(10) + "x2: " + STR$(x3) _
'                    + CHR$(10) + "y2: " + STR$(y3) _
'                    )
'            END IF
'            DIM x4 AS DOUBLE , y4 AS DOUBLE
'            DIM x5 AS DOUBLE , y5 AS DOUBLE
'            DIM x6 AS DOUBLE , y6 AS DOUBLE
'            DIM x7 AS DOUBLE , y7 AS DOUBLE
'            IF y3 > y2 THEN
'               ang_a = ang_a * - 1
'            END IF
'            x4 = COS((ang_a - 72) * rad) * c + x3
'            y4 = y3 - SIN((ang_a - 72) * rad) * c
'            'MoveToEx(.Buffer.handle,x3,y3,0)
'            'LineTo(.Buffer.handle,x4,y4)
'            '.Buffer.Line(x3 , y3 , x4 , y4 , pencolor)
'
'            ang_a = ang_a - 72
'            'MoveToEx(.Buffer.handle,x4,y4,0)
'            '.Buffer.Line(x4 , y4 , COS((ang_a - 72) * rad) * c + x4 , y4 - SIN((ang_a - 72) * rad) * c , pencolor)
'            x5 = COS((ang_a - 72) * rad) * c + x4
'            y5 = y4 - SIN((ang_a - 72) * rad) * c
'            'LineTo(.Buffer.handle,x4,y4)
'
'            ang_a = ang_a - 72
'            '.Buffer.Line(x5 , y5 , COS((ang_a - 72) * rad) * c + x5 , y5 - SIN((ang_a - 72) * rad) * c , pencolor)
'            
'             x6 = COS((ang_a - 72) * rad) * c + x5
'            y6 = y5 - SIN((ang_a - 72) * rad) * c
'            
'            ang_a = ang_a - 72
'            '.Buffer.Line(x6 , y6 , COS((ang_a - 72) * rad) * c + x6 , y6 - SIN((ang_a - 72) * rad) * c , pencolor)
'            
'            'x7=COS((ang_a - 72) * rad) * c + x6
'            'y7=y6 - SIN((ang_a - 72) * rad) * c
'            
'            .Buffer.Line(x2,y2,x4,y4, pencolor)
'            .Buffer.Line(x4,y4,x6,y6, pencolor)
'            .Buffer.Line(x4,y4,x6,y6, pencolor)
'            .Buffer.Line(x6,y6,x3,y3, pencolor)
'            .Buffer.Line(x3,y3,x5,y5, pencolor)
'            .Buffer.Line(x5,y5,x2,y2, pencolor)
'            
'            'MoveToEx(.Buffer.handle,x4,y4,0)
'            'x4=cos((ang_a-90)*rad)*c+x4
'            'y4=y4-sin((ang_a-90)*rad)*c
'            'LineTo(.Buffer.handle,x4,y4)
'            .buffertmp.BMP = .buffer.BMP
'            .PaintChart
'
'        END WITH

    END SUB
    
    private :
    SUB draworcycles(xb , yb , xc , yc , xd , yd)

        DEFSNG x2 , y2 , x3 , y3 , x4 , y4
        x2 = xb
        y2 = yb
        x3 = xc
        y3 = yc
        x4 = xd
        y4 = yd

        WITH QChart
            .ClearBuffer
            .buffer.BMP = .buffertmpz2.BMP            
            
            DIM a AS DOUBLE , b AS DOUBLE , c AS DOUBLE , ang_a AS DOUBLE
            a = x3 - x2
            b = y3 - y2
            c = SQR(a^2 + b^2)
            IF c <> 0 THEN
                ang_a = ACOS(a / c) * 180 / rqpi
		ang_a_pub=ang_a
                dispinfotext("Angle: " + STR$(ang_a) + CHR$(10) + _
                    "Length: " + STR$(c) _
                    + CHR$(10) + "x1: " + STR$(x2) _
                    + CHR$(10) + "y1: " + STR$(y2) _
                    + CHR$(10) + "x2: " + STR$(x3) _
                    + CHR$(10) + "y2: " + STR$(y3) _
                    )
            END IF
            

            DIM y5 AS DOUBLE:DIM x5 AS DOUBLE
           
            dim aa as double,bb as double,cc as double,cc2 as double,ang_aa as double
            aa = x4 - x2
            bb = y4 - y2
            cc = SQR(aa^2 + bb^2)
            cc2 = SQR((x4-x3)^2 + (y4-y3)^2)
            IF cc <> 0 THEN ang_aa = ACOS(aa / cc) * 180 / rqpi
            IF y4 > y2 THEN
                ang_aa = ang_aa * - 1
            END IF
            x5 = COS((ang_aa - 90) * rad) * cc2 + x4
            y5 = y4 - SIN((ang_aa - 90) * rad) * cc2
            dim x6 as double,y6 as double
            dim aaa as double, bbb as double,ccc as double,ang_aaa as double
            aaa = x5 - x4
            bbb = y5 - y4
            ccc = SQR(aaa^2 + bbb^2)
            IF ccc <> 0 THEN ang_aaa = ACOS(aaa / ccc) * 180 / rqpi
            IF y5 > y4 THEN
                ang_aaa = ang_aaa * - 1
            END IF
            FOR i = 1 TO 8
            x6=COS((ang_aaa - 90) * rad) * cc + (COS((ang_aa - 90) * rad) * cc2*i + x4)
            y6=(y4 - SIN((ang_aa - 90) * rad) * cc2*i) - SIN((ang_aaa - 90) * rad) * cc
            .Buffer.Line((COS((ang_aa - 90) * rad) * cc2*i + x4),(y4 - SIN((ang_aa - 90) * rad) * cc2*i),x6,y6,pencolor)
            NEXT i
                                    
            .buffertmp.BMP = .buffer.BMP
            .PaintChart

        END WITH

    END SUB
    
    private :
    SUB drawpolyg(xb , yb , xc , yc)
    
        DEFSNG x2 , y2 , x3 , y3
        x2 = xb
        y2 = yb
        x3 = xc
        y3 = yc

        WITH QChart
            .ClearBuffer
            .buffer.BMP = .buffertmpz.BMP
            DIM a AS DOUBLE , b AS DOUBLE , c AS DOUBLE , ang_a AS DOUBLE
            a = x3 - x2
            b = y3 - y2
            c = SQR(a^2 + b^2)
            IF c <> 0 THEN
                ang_a = ACOS(a / c) * 180 / 3.1415927
		ang_a_pub=ang_a
                dispinfotext("Angle: " + STR$(ang_a) + CHR$(10) + _
                    "Length: " + STR$(c) _
                    + CHR$(10) + "x1: " + STR$(x2) _
                    + CHR$(10) + "y1: " + STR$(y2) _
                    + CHR$(10) + "x2: " + STR$(x3) _
                    + CHR$(10) + "y2: " + STR$(y3) _
                    )
            END IF

            DIM angle AS DOUBLE , cs AS DOUBLE , sn AS DOUBLE
            FOR angle = 0 TO 1.57 STEP 0.001
                IF COS(angle) <> 0 AND SIN(angle) <> 0 THEN
                    cs = c * COS(angle)
                    sn = c * SIN(angle)
                    '.buffer.Pset(x2 + cs , y2 + sn , pencolor)
                    '.buffer.Pset(x2 - cs , y2 + sn , pencolor)
                    '.buffer.Pset(x2 + cs , y2 - sn , pencolor)
                    '.buffer.Pset(x2 - cs , y2 - sn , pencolor)
                END IF
            NEXT angle
            DIM x4 AS DOUBLE , y4 AS DOUBLE
            DIM x5 AS DOUBLE , y5 AS DOUBLE
            DIM x6 AS DOUBLE , y6 AS DOUBLE
            DIM x7 AS DOUBLE , y7 AS DOUBLE
            DIM x8 AS DOUBLE , y8 AS DOUBLE
            DIM x9 AS DOUBLE , y9 AS DOUBLE
            DIM x10 AS DOUBLE , y10 AS DOUBLE
            IF y3 > y2 THEN
                ang_a = ang_a * - 1
            END IF  
            
            if pentagoneradio.checked=1 then          

            x4=COS((ang_a + 72) * rad) * c + x2
            y4=y2 - SIN((ang_a + 72) * rad) * c
            x5=COS((ang_a + 144) * rad) * c + x2
            y5=y2 - SIN((ang_a + 144) * rad) * c
            x6=COS((ang_a + 216) * rad) * c + x2
            y6=y2 - SIN((ang_a + 216) * rad) * c
            x7=COS((ang_a + 288) * rad) * c + x2
            y7=y2 - SIN((ang_a + 288) * rad) * c            
                        
            .Buffer.Line(x3,y3,x4,y4, pencolor)
            .Buffer.Line(x4,y4,x5,y5, pencolor)
            .Buffer.Line(x5,y5,x6,y6, pencolor)
            .Buffer.Line(x6,y6,x7,y7, pencolor)
            .Buffer.Line(x7,y7,x3,y3, pencolor)
            
            end if
            
            if hexagoneradio.checked=1 then          

            x4=COS((ang_a + 60) * rad) * c + x2
            y4=y2 - SIN((ang_a + 60) * rad) * c
            x5=COS((ang_a + 120) * rad) * c + x2
            y5=y2 - SIN((ang_a + 120) * rad) * c
            x6=COS((ang_a + 180) * rad) * c + x2
            y6=y2 - SIN((ang_a + 180) * rad) * c
            x7=COS((ang_a + 240) * rad) * c + x2
            y7=y2 - SIN((ang_a + 240) * rad) * c  
            x8=COS((ang_a + 300) * rad) * c + x2
            y8=y2 - SIN((ang_a + 300) * rad) * c          
                        
            .Buffer.Line(x3,y3,x4,y4, pencolor)
            .Buffer.Line(x4,y4,x5,y5, pencolor)
            .Buffer.Line(x5,y5,x6,y6, pencolor)
            .Buffer.Line(x6,y6,x7,y7, pencolor)
            .Buffer.Line(x7,y7,x8,y8, pencolor)
            .Buffer.Line(x8,y8,x3,y3, pencolor)
            
            end if
            
            if octogoneradio.checked=1 then          

            x4=COS((ang_a + 45) * rad) * c + x2
            y4=y2 - SIN((ang_a + 45) * rad) * c
            x5=COS((ang_a + 90) * rad) * c + x2
            y5=y2 - SIN((ang_a + 90) * rad) * c
            x6=COS((ang_a + 135) * rad) * c + x2
            y6=y2 - SIN((ang_a + 135) * rad) * c
            x7=COS((ang_a + 180) * rad) * c + x2
            y7=y2 - SIN((ang_a + 180) * rad) * c  
            x8=COS((ang_a + 225) * rad) * c + x2
            y8=y2 - SIN((ang_a + 225) * rad) * c      
            x9=COS((ang_a + 270) * rad) * c + x2
            y9=y2 - SIN((ang_a + 270) * rad) * c   
            x10=COS((ang_a + 315) * rad) * c + x2
            y10=y2 - SIN((ang_a + 315) * rad) * c  
                        
            .Buffer.Line(x3,y3,x4,y4, pencolor)
            .Buffer.Line(x4,y4,x5,y5, pencolor)
            .Buffer.Line(x5,y5,x6,y6, pencolor)
            .Buffer.Line(x6,y6,x7,y7, pencolor)
            .Buffer.Line(x7,y7,x8,y8, pencolor)
            .Buffer.Line(x8,y8,x9,y9, pencolor)
            .Buffer.Line(x9,y9,x10,y10, pencolor)
            .Buffer.Line(x10,y10,x3,y3, pencolor)
            
            end if
                                   
            .buffertmp.BMP = .buffer.BMP
            .PaintChart
        END WITH
        

'        DEFSNG x2 , y2 , x3 , y3
'        x2 = xb
'        y2 = yb
'        x3 = xc
'        y3 = yc
'
'        WITH QChart
'            .ClearBuffer
'            .buffer.BMP = .buffertmpz.BMP
'            'MoveToEx(.Buffer.handle,x2,y2,0)
'            'LineTo(.Buffer.handle,x3,y3)
'            '.Buffer.Line(x2 , y2 , x3 , y3 , pencolor)
'            DIM a AS DOUBLE , b AS DOUBLE , c AS DOUBLE , ang_a AS DOUBLE
'            a = x3 - x2
'            b = y3 - y2
'            c = SQR(a^2 + b^2)
'            IF c <> 0 THEN
'                ang_a = ACOS(a / c) * 180 / 3.1415927
'                dispinfotext("Angle: " + STR$(ang_a) + CHR$(10) + _
'                    "Length: " + STR$(c) _
'                    + CHR$(10) + "x1: " + STR$(x2) _
'                    + CHR$(10) + "y1: " + STR$(y2) _
'                    + CHR$(10) + "x2: " + STR$(x3) _
'                    + CHR$(10) + "y2: " + STR$(y3) _
'                    )
'            END IF
'            DIM x4 AS DOUBLE , y4 AS DOUBLE
'            DIM x5 AS DOUBLE , y5 AS DOUBLE
'            DIM x6 AS DOUBLE , y6 AS DOUBLE
'            DIM x7 AS DOUBLE , y7 AS DOUBLE
'            IF y3 > y2 THEN
'               ang_a = ang_a * - 1
'            END IF
'            x4 = COS((ang_a - 72) * rad) * c + x3
'            y4 = y3 - SIN((ang_a - 72) * rad) * c
'            'MoveToEx(.Buffer.handle,x3,y3,0)
'            'LineTo(.Buffer.handle,x4,y4)
'            '.Buffer.Line(x3 , y3 , x4 , y4 , pencolor)
'
'            ang_a = ang_a - 72
'            'MoveToEx(.Buffer.handle,x4,y4,0)
'            '.Buffer.Line(x4 , y4 , COS((ang_a - 72) * rad) * c + x4 , y4 - SIN((ang_a - 72) * rad) * c , pencolor)
'            x5 = COS((ang_a - 72) * rad) * c + x4
'            y5 = y4 - SIN((ang_a - 72) * rad) * c
'            'LineTo(.Buffer.handle,x4,y4)
'
'            ang_a = ang_a - 72
'            '.Buffer.Line(x5 , y5 , COS((ang_a - 72) * rad) * c + x5 , y5 - SIN((ang_a - 72) * rad) * c , pencolor)
'            
'             x6 = COS((ang_a - 72) * rad) * c + x5
'            y6 = y5 - SIN((ang_a - 72) * rad) * c
'            
'            ang_a = ang_a - 72
'            '.Buffer.Line(x6 , y6 , COS((ang_a - 72) * rad) * c + x6 , y6 - SIN((ang_a - 72) * rad) * c , pencolor)
'            
'            'x7=COS((ang_a - 72) * rad) * c + x6
'            'y7=y6 - SIN((ang_a - 72) * rad) * c
'            
'            .Buffer.Line(x2,y2,x4,y4, pencolor)
'            .Buffer.Line(x4,y4,x6,y6, pencolor)
'            .Buffer.Line(x4,y4,x6,y6, pencolor)
'            .Buffer.Line(x6,y6,x3,y3, pencolor)
'            .Buffer.Line(x3,y3,x5,y5, pencolor)
'            .Buffer.Line(x5,y5,x2,y2, pencolor)
'            
'            'MoveToEx(.Buffer.handle,x4,y4,0)
'            'x4=cos((ang_a-90)*rad)*c+x4
'            'y4=y4-sin((ang_a-90)*rad)*c
'            'LineTo(.Buffer.handle,x4,y4)
'            .buffertmp.BMP = .buffer.BMP
'            .PaintChart
'
'        END WITH

    END SUB
    
    private :
    SUB drawsinfromtrendline(xb , yb , xc , yc , xd , yd)

        DEFdbl x2 , y2 , x3 , y3 , x4 , y4
        x2 = xb
        y2 = yb
        x3 = xc
        y3 = yc
        x4 = xd
        y4 = yd

        WITH QChart
            .ClearBuffer
            .buffer.BMP = .buffertmpz2.BMP            
            
            DIM a AS DOUBLE , b AS DOUBLE , c AS DOUBLE , ang_a AS DOUBLE
            a = x3 - x2
            b = y3 - y2
            c = SQR(a^2 + b^2)
            IF c <> 0 THEN
                ang_a = ACOS(a / c) * 180 / rqpi
		ang_a_pub=ang_a
                dispinfotext("Angle: " + STR$(ang_a) + CHR$(10) + _
                    "Length: " + STR$(c) _
                    + CHR$(10) + "x1: " + STR$(x2) _
                    + CHR$(10) + "y1: " + STR$(y2) _
                    + CHR$(10) + "x2: " + STR$(x3) _
                    + CHR$(10) + "y2: " + STR$(y3) _
                    )
            END IF 
            
            defdbl aa,bb,cc,cc2
            aa = x4 - x2
            bb = y4 - y2
            cc = SQR(aa^2 + bb^2)
            cc2 = SQR((x4-x3)^2 + (y4-y3)^2)                                
            
            defdbl cx,cy,freq,amp,phase,mousex2,mousey2
            cx=x2
            cy=y2             
            freq=int(logamplitude/4) '8 
            amp=cc2'30 
            phase=0  
            mousex2=x4
            mousey2=y4
            
            defdbl x,y
            defdbl dx=mouseX2-cx 
             defdbl dy=mouseY2-cy 
             defdbl l=sqr(dx*dx+dy*dy) 
             
             phase+=0.1 
    
            'dx=dx/l 
             'dy=dy/l 
  
            'a=atn2(dy,dx)+rqPI/2 
             defdbl nx=amp*dy/l 'amp*cos(a) 
             defdbl ny=amp*(-dx)/l 'amp*sin(a) 
  
            'defdbl ox=nx*sin(phase) 
             'defdbl oy=ny*sin(phase) 
  

            defdbl tstep=1.0 / 1 
             defdbl t
             for t=0 to 1 step 0.0001 
               a=sin(phase+2*rqPI*t*freq) 
               'x=cx+t*l*dx+nx*a-ox 
               'y=cy+t*l*dy+ny*a-oy 
               x=cx+t*dx+nx*a
               y=cy+t*dy+ny*a
               .buffer.pset(x,y,pencolor)
             next t  
 
                                    
            .buffertmp.BMP = .buffer.BMP
            .PaintChart

        END WITH

    END SUB
    
    private :
    SUB drawsqr2(xb , yb , xc , yc)
    
        DEFSNG x2 , y2 , x3 , y3
        x2 = xb
        y2 = yb
        x3 = xc
        y3 = yc

        WITH QChart
            .ClearBuffer
            .buffer.BMP = .buffertmpz.BMP
            DIM a AS DOUBLE , b AS DOUBLE , c AS DOUBLE , ang_a AS DOUBLE
            a = x3 - x2
            b = y3 - y2
            c = SQR(a^2 + b^2)
            IF c <> 0 THEN
                ang_a = ACOS(a / c) * 180 / 3.1415927
        ang_a_pub=ang_a
                dispinfotext("Angle: " + STR$(ang_a) + CHR$(10) + _
                    "Length: " + STR$(c) _
                    + CHR$(10) + "x1: " + STR$(x2) _
                    + CHR$(10) + "y1: " + STR$(y2) _
                    + CHR$(10) + "x2: " + STR$(x3) _
                    + CHR$(10) + "y2: " + STR$(y3) _
                    )
            END IF

            DIM angle AS DOUBLE , cs AS DOUBLE , sn AS DOUBLE
            FOR angle = 0 TO 1.57 STEP 0.001
                IF COS(angle) <> 0 AND SIN(angle) <> 0 THEN
                    cs = c * COS(angle)
                    sn = c * SIN(angle)
                    '.buffer.Pset(x2 + cs , y2 + sn , pencolor)
                    '.buffer.Pset(x2 - cs , y2 + sn , pencolor)
                    '.buffer.Pset(x2 + cs , y2 - sn , pencolor)
                    '.buffer.Pset(x2 - cs , y2 - sn , pencolor)
                END IF
            NEXT angle
            DIM x4 AS DOUBLE , y4 AS DOUBLE
            DIM x5 AS DOUBLE , y5 AS DOUBLE
            DIM x6 AS DOUBLE , y6 AS DOUBLE
            DIM x7 AS DOUBLE , y7 AS DOUBLE
            DIM x8 AS DOUBLE , y8 AS DOUBLE
            DIM x9 AS DOUBLE , y9 AS DOUBLE
            DIM x10 AS DOUBLE , y10 AS DOUBLE
            IF y3 > y2 THEN
                ang_a = ang_a * - 1
            END IF  
            
                    

            x4=COS((ang_a + 90) * rad) * c + x2
            y4=y2 - SIN((ang_a + 90) * rad) * c
            x5=COS((ang_a + 180) * rad) * c + x2
            y5=y2 - SIN((ang_a + 180) * rad) * c
            x6=COS((ang_a + 270) * rad) * c + x2
            y6=y2 - SIN((ang_a + 270) * rad) * c            
                        
            .Buffer.Line(x3,y3,x4,y4, pencolor)
            .Buffer.Line(x4,y4,x5,y5, pencolor)
            .Buffer.Line(x5,y5,x6,y6, pencolor)
            .Buffer.Line(x6,y6,x3,y3, pencolor) 
            
            x4=COS((ang_a + 0) * rad) * c + x2
            y4=y2 - SIN((ang_a + 0) * rad) * c                              
            
            .buffer.fillrect(x4-3,y4-3,x4+3,y4+3,black)
                                   
            .buffertmp.BMP = .buffer.BMP
            .PaintChart
        END WITH
        
    END SUB
    
    private :
    SUB drawtri2(xb , yb , xc , yc)
    
        DEFSNG x2 , y2 , x3 , y3
        x2 = xb
        y2 = yb
        x3 = xc
        y3 = yc

        WITH QChart
            .ClearBuffer
            .buffer.BMP = .buffertmpz.BMP
            DIM a AS DOUBLE , b AS DOUBLE , c AS DOUBLE , ang_a AS DOUBLE
            a = x3 - x2
            b = y3 - y2
            c = SQR(a^2 + b^2)
            IF c <> 0 THEN
                ang_a = ACOS(a / c) * 180 / 3.1415927
        ang_a_pub=ang_a
                dispinfotext("Angle: " + STR$(ang_a) + CHR$(10) + _
                    "Length: " + STR$(c) _
                    + CHR$(10) + "x1: " + STR$(x2) _
                    + CHR$(10) + "y1: " + STR$(y2) _
                    + CHR$(10) + "x2: " + STR$(x3) _
                    + CHR$(10) + "y2: " + STR$(y3) _
                    )
            END IF

            DIM angle AS DOUBLE , cs AS DOUBLE , sn AS DOUBLE
            FOR angle = 0 TO 1.57 STEP 0.001
                IF COS(angle) <> 0 AND SIN(angle) <> 0 THEN
                    cs = c * COS(angle)
                    sn = c * SIN(angle)
                    '.buffer.Pset(x2 + cs , y2 + sn , pencolor)
                    '.buffer.Pset(x2 - cs , y2 + sn , pencolor)
                    '.buffer.Pset(x2 + cs , y2 - sn , pencolor)
                    '.buffer.Pset(x2 - cs , y2 - sn , pencolor)
                END IF
            NEXT angle
            DIM x4 AS DOUBLE , y4 AS DOUBLE
            DIM x5 AS DOUBLE , y5 AS DOUBLE
            DIM x6 AS DOUBLE , y6 AS DOUBLE
            DIM x7 AS DOUBLE , y7 AS DOUBLE
            DIM x8 AS DOUBLE , y8 AS DOUBLE
            DIM x9 AS DOUBLE , y9 AS DOUBLE
            DIM x10 AS DOUBLE , y10 AS DOUBLE
            IF y3 > y2 THEN
                ang_a = ang_a * - 1
            END IF  
            
                    

            x4=COS((ang_a + 120) * rad) * c + x2
            y4=y2 - SIN((ang_a + 120) * rad) * c
            x5=COS((ang_a + 240) * rad) * c + x2
            y5=y2 - SIN((ang_a + 240) * rad) * c            
                        
            .Buffer.Line(x3,y3,x4,y4, pencolor)
            .Buffer.Line(x4,y4,x5,y5, pencolor)
            .Buffer.Line(x5,y5,x3,y3, pencolor) 
            
            x4=COS((ang_a + 0) * rad) * c + x2
            y4=y2 - SIN((ang_a + 0) * rad) * c                              
            
            .buffer.fillrect(x4-3,y4-3,x4+3,y4+3,black)                               
                                   
            .buffertmp.BMP = .buffer.BMP
            .PaintChart
        END WITH
        
    END SUB
    
    private :
    SUB drawlastprice()
    
        WITH QChart
            .ClearBuffer
            .buffer.BMP = .buffertmpz.BMP            
            .Buffer.Line(0 , lastpricey , lastpricex , lastpricey , pencolor)
            .Buffer.TextOut(0 , lastpricey , Grid.Cell(rowgridoffset + 6 , chartbars(displayedfile)) , pencolor , &hffffff)
            .buffertmp.BMP = .buffer.BMP
            .PaintChart            
        END WITH
        
    END SUB
    
    private :
    SUB draworderbuy(xb , yb , xc , yc)
    
        DEFSNG x2 , y2 , x3 , y3
        x2 = xb
        y2 = yb
        x3 = xc
        y3 = yc

        WITH QChart
            .ClearBuffer
            .buffer.BMP = .buffertmpz.BMP                                                                  
                                                      
            
            .buffer.fillrect(x2-3,y2-3,x2+3,y2+3,green)
                                   
            .buffertmp.BMP = .buffer.BMP
            .PaintChart
        END WITH
        
    END SUB
    
    private :
    SUB drawordersell(xb , yb , xc , yc)
    
        DEFSNG x2 , y2 , x3 , y3
        x2 = xb
        y2 = yb
        x3 = xc
        y3 = yc

        WITH QChart
            .ClearBuffer
            .buffer.BMP = .buffertmpz.BMP                                                                  
                                                      
            
            .buffer.fillrect(x2-3,y2-3,x2+3,y2+3,red)
                                   
            .buffertmp.BMP = .buffer.BMP
            .PaintChart
        END WITH
        
    END SUB

    '------------------------------------------------------------------------------------------
    PRIVATE :
    SUB DrawPie(Overlay AS INTEGER)

        DIM i AS INTEGER  'Loop counters...
        DIM x1 AS LONG  'for readability
        DIM y1 AS LONG
        DIM x2 AS LONG
        DIM y2 AS LONG
        DIM Total AS SINGLE
        DIM pi2 AS SINGLE
        DIM pct AS SINGLE
        DIM Radius AS SINGLE
        DIM Cum AS SINGLE
        DIM xSize AS SINGLE
        DIM ySize AS SINGLE
        DIM xLeft AS LONG
        DIM xRight AS LONG
        DIM yTop AS LONG
        DIM yBottom AS LONG
        DIM TxtFactor AS SINGLE

        IF Overlay = FALSE THEN
            WITH QChart  'Set up the chart window
                .ClearBuffer  'erase the current bitmap
                .DoLegend = TRUE  'Force to calculate sizes based on Legend
                .SetSize
                .SetSeries
                .DrawAxes
                .DrawTitles
                .DrawLegend
            END WITH
        END IF

        WITH QChart
            .Buffer.Font = .AxisFont
            TxtFactor = .Buffer.TextHeight("I")
            xSize = .XAxis.LEN - TxtFactor
            ySize = .YAxis.LEN - TxtFactor
            Total = .RowTotal(1)
            IF Total = 0 THEN
                MESSAGEDLG("Division by Zero!" , 1 , 4 , 0)
                .ClearAll
                EXIT SUB
            END IF
            pi2 = 8 * ATN(1)
            Radius = ySize / 2.5
            xLeft = (.XAxis.Ori + xSize / 2) - Radius
            xRight = (.XAxis.Ori + xSize / 2) + Radius
            yTop = (.YAxis.Ori - ySize / 2) - Radius
            yBottom = (.YAxis.Ori - ySize / 2) + Radius

            x1 = xRight  'Set Start point for 1st wedge
            y1 = (yTop + yBottom) \ 2
            Cum = 0
            FOR i = 1 TO .DATA.ColCount
                IF .DATA.Cell(i , 1) <> "" THEN  'if data not missing

                    Cum = Cum + VAL(.DATA.Cell(i , 1)) 'Calculate wedge endpoint
                    x2 = .XAXis.Ori + xSize / 2 + Radius * COS(pi2 * Cum / Total)
                    y2 = .YAxis.Ori - ySize / 2 - Radius * SIN(pi2 * Cum / Total)

                    IF .Series(i).HatchStyle = hsSolid THEN  'Set brush color for wedge
                        .hBrush = CreateSolidBrush(.Series(i).Color)
                    ELSE
                        .hBrush = CreateHatchBrush(.Series(i).HatchStyle , .Series(i).Color)
                    END IF
                    .OldBrush = SelectObject(.Buffer.Handle , .hBrush)

                    Pie(.Buffer.Handle , xLeft , yTop , xRight , yBottom , x1 , y1 , x2 , y2) 'Draw the wedge

                    DeleteObject(SelectObject(.Buffer.Handle , .OldBrush))

                    SELECT CASE .ChartStyle  'Print labels at midpoint of wedge
                        CASE csPiePct
                            pct = VAL(.DATA.Cell(i , 1)) / Total * 100
                            .AxisLbl.Text = FORMAT$("%-3.1f" , pct) + " %"

                        CASE csPieVal
                            .AxisLbl.Text = FORMAT$("%-4.4g" , VAL(.DATA.Cell(i , 1)))

                        CASE ELSE
                            .AxisLbl.Text = ""
                    END SELECT

                    .AxisLbl.Left = .XAxis.Ori + xSize / 2 + (Radius + TxtFactor) * _
                        COS(pi2 * (Cum - VAL(.DATA.Cell(i , 1)) / 2) / Total)
                    .AxisLbl.Top = .YAxis.Ori - ySize / 2 - (Radius + TxtFactor) * _
                        SIN(pi2 * (Cum - VAL(.DATA.Cell(i , 1)) / 2) / Total)
                    IF COS(pi2 * (Cum - VAL(.DATA.Cell(i , 1)) / 2) / Total) < 0 THEN  'align left
                        .AxisLbl.Left = .AxisLbl.Left - .Buffer.TextWidth(RTRIM$(.AxisLbl.Text))
                    END IF
                    .Buffer.TextOut(.AxisLbl.Left , .AxisLbl.Top , RTRIM$(.AxisLbl.Text) , _
                        .Buffer.Font.Color , .bgColor)
                    x1 = x2  'Update wedge start position
                    y1 = y2

                END IF
            NEXT i

        END WITH
        QChart.ChartExists = TRUE

    END SUB
    '------------------------------------------------------------------------------------------
    '------------------------- Public Methods -------------------------------------------------
    '------------------------------------------------------------------------------------------
    PUBLIC :
    SUB DrawChart(Overlay AS INTEGER)

        WITH QChart
            SELECT CASE .ChartType
                CASE ctBar
                    .DrawBar(Overlay)
                CASE ctXY
                    .DrawXY(Overlay)
                CASE ctLine
                    .DrawLine(Overlay)
                CASE ctBox
                    .DrawBox(Overlay)
                CASE ctPie
                    .DrawPie(Overlay)
            END SELECT
            IF .Printing = FALSE THEN .PaintChart
        END WITH

    END SUB

    public :
    SUB bufcntreset
        bufcnt = 0
    END SUB

    public :
    SUB firstbufcntreset
        firstbufcnt = 0
    END SUB

    public :
    SUB savebuffertmp
        WITH QChart
            IF firstbufcnt = 0 THEN
                .firstbuffertmpz.BMP = .buffer.BMP
                firstbufcnt ++
            END IF
            IF bufcnt = 0 THEN
                .buffertmpz.BMP = .buffer.BMP
                bufcnt ++
            END IF
            .buffertmp.BMP = .buffer.BMP
        END WITH
    END SUB

    public :
    SUB savebuffertmpsimple
        WITH QChart
            .buffertmp.BMP = .buffer.BMP
        END WITH
    END SUB

    public :
    SUB savebuffertmpsimplez
        WITH QChart
            .buffertmpz2.BMP = .buffer.BMP
        END WITH
    END SUB

    public :
    SUB restorebuffertmpz
        WITH QChart
            .buffer.BMP = .buffertmpz.BMP
        END WITH
    END SUB

    public :
    SUB restorefirstbuffertmpz
        WITH QChart
            .buffer.BMP = .firstbuffertmpz.BMP
        END WITH
    END SUB

    PUBLIC :
    SUB drawp(TYPE , xb , yb , xc , yc , xd , yd)
        DEFINT x2 , y2 , x3 , y3 , x4 , y4
        DEFINT type2
        type2 = TYPE
        'print type2

        x2 = xb
        y2 = yb
        x3 = xc
        y3 = yc
        x4 = xd
        y4 = yd
        WITH QChart
            SELECT CASE type2
                CASE 0 :
                    .drawtrendline(x2 , y2 , x3 , y3)
                CASE 1 :
                    .drawfibofan(x2 , y2 , x3 , y3 , x4 , y4)
                CASE 2 :
                    .drawfiboret(x2 , y2 , x3 , y3)
                CASE 3 :
                    .drawpara(x2 , y2 , x3 , y3 , x4 , y4)
                CASE 4 :
                    .drawhline(x2 , y2 , x3 , y3)
                CASE 5 :
                    .drawvline(x2 , y2 , x3 , y3)
                CASE 6 :
                    .drawsqr(x2 , y2 , x3 , y3)
                CASE 7 :
                    .drawtri(x2 , y2 , x3 , y3)
                CASE 8 :
                    .drawcircle(x2 , y2 , x3 , y3)
                CASE 9 :
                    .drawcross(x2 , y2 , x3 , y3)
                CASE 10 :
                    .drawinvcircle(x2 , y2 , x3 , y3)
                CASE 11 :
                    .drawaiming(x2 , y2 , x3 , y3)
                CASE 12 :
                    .drawhand(x2 , y2 , x3 , y3)
                CASE 13 :
                    .drawsin(x2 , y2 , x3 , y3)
                CASE 14 :
                    .drawlog(x2 , y2 , x3 , y3)
                CASE 15 :
                    .drawexp(x2 , y2 , x3 , y3)
                CASE 16 :
                    .drawellipse(x2 , y2 , x3 , y3)
                CASE 17 :
                    .drawpitchfork(x2 , y2 , x3 , y3 , x4 , y4)
                CASE 18 :
                    .drawpriceext(x2 , y2 , x3 , y3 , x4 , y4)
                CASE 19 :
                    .drawsq9f(x2 , y2 , x3 , y3)
                CASE 20 :
                    .drawsq144(x2 , y2 , x3 , y3)
                CASE 21 :
                    .drawtimeext(x2 , y2 , x3 , y3 , x4 , y4)
                CASE 22
                    .drawtsq9f(x2 , y2 , x3 , y3)
                CASE 23 :
                    .drawtsq144(x2 , y2 , x3 , y3)
                CASE 24 :
                    .drawpricecycles(x2 , y2 , x3 , y3)
                CASE 25 :
                    .drawtimecycles(x2 , y2 , x3 , y3)
                CASE 26 :
                    .drawlogspiral(x2 , y2 , x3 , y3)
                CASE 27 :
                    .drawpentag(x2 , y2 , x3 , y3)
                CASE 28 :
                    .draworcycles(x2 , y2 , x3 , y3 , x4 , y4)
                CASE 29 :
                    .drawpolyg(x2 , y2 , x3 , y3)
                CASE 30 :
                    .drawsinfromtrendline(x2 , y2 , x3 , y3 , x4 , y4)
                CASE 31 :
                    .drawsqr2(x2 , y2 , x3 , y3)
                CASE 32 :
                    .drawtri2(x2 , y2 , x3 , y3)
                CASE 33 :
                    .drawlastprice()
                CASE 34 :
                    .draworderbuy(x2 , y2 , 0 , 0)
                CASE 35 :
                    .drawordersell(x2 , y2 , 0 , 0)
            END SELECT
        END WITH
    END SUB
    '-------------------------------------------------------------------------------------------
    PUBLIC :
    SUB RedrawChart  '<--- Call this SUB from your FORM.OnResize EVENT SUB

        WITH QChart
            .Buffer.Width = .Width  'recalc dimensions
            .Buffer.Height = .Height
            IF .ChartExists THEN .DrawChart(FALSE) 'only redraw if QChart.ChartExists
        END WITH

    END SUB
    '-------------------------------------------------------------------------------------------
    PUBLIC :
    SUB PrintChart(Prn AS INTEGER , Orient AS INTEGER , Margin AS INTEGER , _
            Copies AS INTEGER , Colr AS BYTE)
        'Prints copies of graph to a full page with a user specified margin and orientation
        'Colr is Boolean: TRUE = Use color for printing, FALSE = Use B&W for printing

        DIM Source AS QRECT
        DIM Page  AS QRECT
        DIM OldBW  AS BYTE

        IF QChart.ChartExists = FALSE THEN EXIT SUB  'Don't print nonexistent chart

        Printer.PrinterIndex = Prn
        Printer.Orientation = Orient

        WITH Page  'Set page size
            .Top = Margin
            .Left = Margin
            .Right = .Left + Printer.PageWidth - (Margin * 2)
            .Bottom = .Top + Printer.PageHeight - (Margin * 2)
        END WITH

        WITH QChart
            .MainFont.Size = .MainFont.Size * 3
            .SubFont.Size = .SubFont.Size * 3
            .AxisFont.Size = .AxisFont.Size * 3
            .LegendFont.Size = .LegendFont.Size * 3
            .MarkerSize = .MarkerSize * 3

            IF Orient = 0 THEN  'Portrait
                .Buffer.Width = 1920  'Scale to page size
                .Buffer.Height = 2400
            ELSE  'Landscape
                .Buffer.Width = 2560
                .Buffer.Height = 1920
            END IF

            .Printing = TRUE  'Prevent screen redraw

            IF Colr = FALSE THEN
                OldBW = .BW  'Remember BW setting
                .BW = TRUE  'Change to BW for Printing
            END IF

            IF .XAxis.AutoScale = TRUE THEN  'Keep same Axis Scales
                .XAxis.AutoScale = NOT .XAxis.AutoScale  'turn off Autoscale
            END IF
            IF .YAxis.AutoScale = TRUE THEN  'Keep same Axis Scales
                .YAxis.AutoScale = NOT .YAxis.AutoScale  'turn off Autoscale
            END IF
            .DrawChart(FALSE) 'Redraw at Page Size
            IF Colr = FALSE THEN .BW = OldBW  'Restore BW setting
        END WITH

        WITH Source
            .Top = 0
            .Left = 0
            .Right = .Left + QChart.Buffer.Width
            .Bottom = .Top + QChart.Buffer.Height
        END WITH

        WHILE Copies > 0
            doevents
            Printer.BeginDoc  'Print
            Printer.CopyRect(Page , QChart.Buffer , Source)
            Printer.EndDoc
            DEC(Copies)
        WEND

        WITH QChart
            .MainFont.Size = .MainFont.Size / 3  'Restore to screen size
            .SubFont.Size = .SubFont.Size / 3
            .AxisFont.Size = .AxisFont.Size / 3
            .LegendFont.Size = .LegendFont.Size / 3
            .MarkerSize = .MarkerSize / 3
            IF .XAxis.AutoScale = - 2 THEN  'AutoScale was changed
                .XAxis.AutoScale = NOT .XAxis.AutoScale  'Change it back
            END IF
            IF .YAxis.AutoScale = - 2 THEN  'AutoScale was changed
                .YAxis.AutoScale = NOT .YAxis.AutoScale  'Change it back
            END IF
            .RedrawChart  'Redraw at Screen size
            .Printing = FALSE  'Reset Flag
        END WITH

    END SUB
    '-------------------------------------------------------------------------------------------
    PUBLIC :
    SUB SaveChart(FileNam AS STRING)

        qcShowSave :
        WITH QChart
            .dlgSave.Caption = "Save Graph"
            .dlgSave.Filter = "Bitmap Files|*.bmp|All Files|*.*"
            .dlgSave.FilterIndex = 1
            IF LEN(FileNam) <> 0 THEN
                IF INSTR(UCASE$(FileNam) , ".BMP") = 0 THEN FileNam = FileNam + ".bmp"
                .dlgSave.FileName = FileNam
            ELSE
                .dlgSave.FileName = "*.bmp"
            END IF

            IF .dlgSave.Execute AND LEN(.dlgSave.FileName) <> 0 THEN
                IF FILEEXISTS(.dlgSave.FileName) THEN  'check if file exists
                    DIM Response AS INTEGER  'ask user for decision
                    Response = MESSAGEDLG("File Already Exists. Overwrite " + .dlgSave.FileName + "?" , _
                        0 , 1 OR 2 OR 8 , 0) 'Y OR N OR Cancel
                    SELECT CASE Response
                        CASE 7  'NO; don't overwrite, ask again
                            GOTO qcShowSave  '<--- Use of a local GOTO loop!
                        CASE 2  'CANCEL;don't overwrite, don't ask again
                            EXIT SUB
                    END SELECT
                END IF

                DIM File AS QFILESTREAM
                File.Open(.dlgSave.FileName , 65535) '65535 = fmCreate
                .Buffer.SaveToStream(File) 'save the data
                File.Close
            END IF
        END WITH

    END SUB

    '-------------------------------------------------------------------------------------------
    '-------------------------------------------------------------------------------------------
    PUBLIC :
    SUB autoSaveChart(FileNam AS STRING)

        qcShowSave :
        WITH QChart
            .dlgSave.Caption = "Save Graph"
            .dlgSave.Filter = "Bitmap Files|*.bmp|All Files|*.*"
            .dlgSave.FilterIndex = 1
            IF LEN(FileNam) <> 0 THEN
                IF INSTR(UCASE$(FileNam) , ".BMP") = 0 THEN FileNam = FileNam + ".bmp"
                .dlgSave.FileName = FileNam
            ELSE
                .dlgSave.FileName = "*.bmp"
            END IF

            'IF .dlgSave.Execute AND LEN(.dlgSave.FileName) <> 0 THEN
            'IF FILEEXISTS(.dlgSave.FileName) THEN             'check if file exists
            'DIM Response AS INTEGER                         'ask user for decision
            'Response =  MESSAGEDLG("File Already Exists. Overwrite " + .dlgSave.FileName + "?",_
            '0, 1 OR 2 OR 8, 0)      ' Y OR N OR Cancel
            'SELECT CASE Response
            'CASE 7                                        ' NO; don't overwrite, ask again
            'GOTO qcShowSave                             '<--- Use of a local GOTO loop!
            'CASE 2                                        'CANCEL;don't overwrite, don't ask again
            'EXIT SUB
            'END SELECT
            'END IF

            DIM File AS QFILESTREAM
            File.Open(.dlgSave.FileName , 65535) '65535 = fmCreate
            .Buffer.SaveToStream(File) 'save the data
            File.Close
            'END IF
        END WITH

    END SUB

    '-------------------------------------------------------------------------------------------
END TYPE  'QChart
'----- End Object Definition ***************************************************************
