SUB btnOnClick(SENDER AS QBUTTON)

    DIM i AS INTEGER  'Loop counters...
    DIM j AS INTEGER
    DIM k AS SINGLE  'A Scratch Variable
    DIM ii AS INTEGER
    STATIC ClickedBar AS INTEGER  'Keep track of button clicks
    STATIC ClickedXY AS INTEGER
    STATIC ClickedBox AS INTEGER
    STATIC ClickedLine AS INTEGER

    SELECT CASE Sender.Caption

        CASE "Import CSV"
            Form2.Visible = 1
            form2.WindowState = 0
            SetFocus(Form2.Handle)

        CASE "Export CSV"
            exportfile()
            'Form2.visible=1
            'form2.WindowState=0
            'SetFocus(Form2.Handle)

        CASE "Histogram"
            ClickedBar = ClickedBar + 1  'Adding new series to existing chart
            IF ClickedBar > 3 THEN ClickedBar = 1  'one by one
            WITH Graph
                .Initialize  'Set defaults
                .ChartType = ctBar  'Bar Chart
                .ChartStyle = csHisto  'Histogram
                .MainTitle.Text = "Histogram Example"  'Change desired options
                .SubTitle.Text = "No Axis Border, Add series with each click"
                .XTitle.Text = "Class Limits"
                .YTitle.Text = "Number"
                .AxisBorder = FALSE
                .XAxis.Grid = FALSE
                k = 10
                .DATA.ColCount = ClickedBar  'Set .Data dimensions based on ClickedBar
                .DATA.RowCount = 12
                RANDOMIZE  'Load the data
                .DATA.Cell(0 , 0) = "3"  'Col 0, Row 0 = data minimum
                FOR i = 1 TO .DATA.ColCount
                    .DATA.Cell(i , 0) = "Series " + STR$(i)
                    FOR j = i TO .DATA.RowCount - (i - 1)
                        .DATA.Cell(0 , j) = STR$(j * 3 + 3)
                        .DATA.Cell(i , j) = STR$(RND * k)
                    NEXT j
                NEXT i
                .DrawChart(FALSE) 'Draw it!
            END WITH

        CASE "Bar Graph"
            ClickedBar = ClickedBar + 1  'Adding new series to existing chart
            IF ClickedBar > 4 THEN ClickedBar = 1  'one by one
            WITH Graph
                .Initialize  'Set defaults
                .ChartType = ctBar  'Bar Chart
                .ChartStyle = csBar  'Grouped Bars
                .MainTitle.Text = "Bar Graph Example 1"  'change desired options
                .SubTitle.Text = "Standard Bar Graph"
                .XTitle.Text = "X Axis"
                .YTitle.Text = "Y Axis"
                IF ClickedBar = 2 THEN .YAxis.LogScale = TRUE
                .DATA.ColCount = 6  'Set .Data Grid dimensions
                .DATA.RowCount = 3
                k = 75  'Load the data
                RANDOMIZE
                FOR i = 1 TO .DATA.ColCount
                    .DATA.Cell(i , 0) = "Grp " + STR$(i) 'Legend in Row 0 of each Col
                    FOR j = 1 TO .DATA.RowCount
                        SELECT CASE ClickedBar
                            CASE 1 , 2
                                .DATA.Cell(i , j) = STR$(RND * k)
                            CASE 3
                                .DATA.Cell(i , j) = STR$(RND * - k)
                            CASE 4
                                .DATA.Cell(i , j) = STR$((RND - RND) * k)
                        END SELECT
                    NEXT j
                NEXT i
                FOR j = 1 TO .DATA.RowCount
                    .DATA.Cell(0 , j) = "Treatment " + STR$(j) 'X Labels in Col 0 of each Row
                NEXT j
                .DrawChart(FALSE) 'Draw it!
            END WITH

        CASE "Stacked Bar"
            WITH Graph
                .Initialize  'Set defaults
                .ChartType = ctBar  'Bar Chart
                .ChartStyle = csStacked  'Grouped Bars
                .MainTitle.Text = "Bar Graph Example 2"  'change desired options
                .SubTitle.Text = "Stacked Bar Graph"
                .XTitle.Text = "X Axis"
                .YTitle.Text = "Y Axis"
                .DATA.ColCount = 6  'Set .Data Grid dimensions
                .DATA.RowCount = 3
                k = 100  'Load the data
                RANDOMIZE
                FOR i = 1 TO .DATA.ColCount
                    .DATA.Cell(i , 0) = "Treatment " + STR$(i) 'Legend in Row 0 of each Col
                    FOR j = 1 TO .DATA.RowCount
                        .DATA.Cell(i , j) = STR$(RND * k + 1)
                    NEXT j
                NEXT i
                FOR j = 1 TO .DATA.RowCount
                    .DATA.Cell(0 , j) = "Group " + STR$(j) 'X Labels in Col 0 of each Row
                NEXT j
                .DrawChart(FALSE) 'Draw it!
            END WITH

        CASE "%Stacked Bar"
            WITH Graph
                .Initialize  'Set defaults
                .ChartType = ctBar  'Bar Chart
                .ChartStyle = csPctStacked  'Grouped Bars
                .MainTitle.Text = "Bar Graph Example 3"  'change desired options
                .SubTitle.Text = "Percent Stacked Bar Graph"
                .XTitle.Text = "X Axis"
                .YTitle.Text = "Y Axis"
                .DATA.ColCount = 6  'Set .Data Grid dimensions
                .DATA.RowCount = 2
                k = 25  'Load the data
                RANDOMIZE
                FOR i = 1 TO .DATA.ColCount
                    .DATA.Cell(i , 0) = "Long Legend Title " + STR$(i) 'Legend in Row 0 of each Col
                    FOR j = 1 TO .DATA.RowCount
                        .DATA.Cell(i , j) = STR$(RND * k)
                    NEXT j
                NEXT i
                FOR j = 1 TO .DATA.RowCount
                    .DATA.Cell(0 , j) = "Level " + STR$(j) 'X Labels in Col 0 of each Row
                NEXT j
                .DrawChart(FALSE) 'Draw it!
            END WITH

        CASE "Pie Chart"
            WITH Graph  'The minimum (2) required calls
                .Initialize  'Always call this first
                .ChartType = ctPie
                .ChartStyle = csPiePct  'Show % at wedges (csPieVal shows Values)
                .AxisFont.Size = 12
                .LegendFont.Size = 12
                .MainTitle.Text = "Pie Chart"
                .SubTitle.Text = "Click Again For New Data"
                .DATA.ColCount = 6  'Set .Data Grid dimensions
                .DATA.RowCount = 1
                k = 10000  'Load the data
                RANDOMIZE
                FOR i = 1 TO .DATA.ColCount
                    .DATA.Cell(i , 0) = "Group " + STR$(i) 'Labels in Row 0 of Each Col
                    .DATA.Cell(i , 1) = STR$(RND * k * i) 'Data in Row 1 of Each Col
                NEXT
                .DrawChart(FALSE) 'Always call this last
            END WITH

        CASE "XY Points"
            WITH Graph
                .Initialize  'Set defaults
                .ChartType = ctXY  'XY Scatter Chart
                .ChartStyle = csPoints  'Just the Points
                .MainTitle.Text = "Scatter Plot Example"  'change desired options
                .SubTitle.Text = "Data in All Four Quadrants"
                .XTitle.Text = "X Axis"
                .YTitle.Text = "Y Axis"
                .DATA.ColCount = 16  'Set .Data Grid dimensions
                .DATA.RowCount = 5
                k = 75  '<-- change k for large and small values
                RANDOMIZE  'Load the data
                FOR i = 2 TO .DATA.ColCount STEP 2  'for each col pair
                    .DATA.Cell(i , 0) = "Group " + STR$(i \ 2) 'Legend in 2nd Col (Y) of Pair, Row 0
                    FOR j = 1 TO .DATA.RowCount  'add data to each row
                        .DATA.Cell(i - 1 , j) = STR$(k * (RND - RND)) 'X Values in Col 1
                        .DATA.Cell(i , j) = STR$(k * (RND - RND)) 'Y Values in Col 2
                    NEXT j
                NEXT i
                .DrawChart(FALSE) 'Draw it!
            END WITH

        CASE "XY Lines"
            WITH Graph
                .Initialize  'Set defaults
                .ChartType = ctXY  'XY Scatter Chart
                .ChartStyle = csLines  'Just the Lines
                .MainTitle.Text = "Two Sine Curves"  'change desired options
                .SubTitle.Text = "Out of Phase"
                .XTitle.Text = "Radians"
                .YTitle.Text = "Sine of X"
                .YAxis.Div = 6
                .XAxis.AutoScale = FALSE  'Manually Scale
                .XAxis.Max = 2  'Set Max Manually
                .XAxis.Min = 0  'Set Min Manually
                .YAxis.AutoScale = FALSE  'Manually Scale
                .YAxis.Max = 1.5  'Set Max Manually
                .YAxis.Min = - 1.5  'Set Min Manually
                .DATA.ColCount = 4  'Set .Data Grid dimensions
                .DATA.RowCount = 21  'Load the data
                FOR i = 2 TO .DATA.ColCount STEP 2  'for each col pair
                    .DATA.Cell(i , 0) = "Group " + STR$(i \ 2) 'Legend in 2nd Col of Pair, Row 0
                    .Series(i \ 2).LineStyle = (i \ 2 - 1) MOD 5  'Cycle line styles
                    FOR j = 1 TO .DATA.RowCount  'add data to each row
                        .DATA.Cell(i - 1 , j) = STR$((j - 1) / 10) 'X Values in 1st Col of Pair
                        k = ((j - 1) / 10 + [(i - 2) * 4.75]) * 3.141592
                        .DATA.Cell(i , j) = STR$(SIN(k)) 'Y Values in 2nd Col of Pair
                    NEXT j
                NEXT i
                .DrawChart(FALSE) 'Draw it!
            END WITH

        CASE "XY Both"
            WITH Graph
                .Initialize  'Set defaults
                .ChartType = ctXY  'XY Scatter Chart
                .ChartStyle = csBoth  'Lines and Points
                .MarkerSize = 0
                .Series(1).LineWidth = 1
                .DATA.RowCount = 11
                .DATA.ColCount = 10  'Set .Data dimensions based on ClickedXY
                FOR j = 1 TO .DATA.RowCount  'add data to each row
                    .DATA.Cell(1 , j) = STR$(j) 'X Values in 1st Col of Pair
                    .DATA.Cell(2 , j) = STR$(j) 'Y Values in 2nd Col of Pair
                NEXT j
                FOR j = 1 TO .DATA.RowCount  'add data to each row
                    .DATA.Cell(3 , j) = STR$(j) 'X Values in 1st Col of Pair
                    .DATA.Cell(4 , j) = STR$(2 * j) 'Y Values in 2nd Col of Pair
                NEXT j
                FOR j = 1 TO .DATA.RowCount  'add data to each row
                    .DATA.Cell(5 , j) = STR$(j) 'X Values in 1st Col of Pair
                    .DATA.Cell(6 , j) = STR$(3 * j) 'Y Values in 2nd Col of Pair
                NEXT j
                FOR j = 1 TO .DATA.RowCount  'add data to each row
                    .DATA.Cell(7 , j) = STR$(j) 'X Values in 1st Col of Pair
                    .DATA.Cell(8 , j) = STR$(4 * j) 'Y Values in 2nd Col of Pair
                NEXT j
                FOR j = 1 TO .DATA.RowCount  'add data to each row
                    .DATA.Cell(9 , j) = STR$(j) 'X Values in 1st Col of Pair
                    .DATA.Cell(10 , j) = STR$(5 * j) 'Y Values in 2nd Col of Pair
                NEXT j

                .DrawChart(FALSE) 'Draw it!

            END WITH

        CASE "XY Logs"
            WITH Graph
                .Initialize  'Set defaults
                .ChartType = ctXY  'XY Scatter Chart
                .ChartStyle = csBoth  'Points and Lines
                .MainTitle.Text = "Log - Log Scaling"  'change desired options
                .SubTitle.Text = "Grid with no Tics"
                .XTitle.Text = "X Axis"
                .YTitle.Text = "Y Axis"
                .YAxis.Tics = FALSE
                .YAxis.LogScale = TRUE
                .XAxis.Tics = FALSE
                .XAxis.LogScale = TRUE
                .DoLegend = FALSE
                .DATA.ColCount = 2  'Set .Data Grid dimensions
                .DATA.RowCount = 10
                RANDOMIZE  'Load the data
                FOR i = 2 TO .DATA.ColCount STEP 2  'for each col pair
                    .DATA.Cell(i , 0) = "Group " + STR$(i \ 2) 'Legend in 2nd Col of Pair, Row 0
                    FOR j = 1 TO .DATA.RowCount  'add data to each row
                        .DATA.Cell(i - 1 , j) = STR$(j) 'X Values in 1st Col of Pair
                        .DATA.Cell(i , j) = STR$(RND * 10^(j / 5)) 'Y Values in 2nd Col of Pair
                    NEXT j
                NEXT i
                .DrawChart(TRUE) 'Draw it!
            END WITH

        CASE "Line Graph"
            WITH Graph
                .Initialize  'Set defaults
                .ChartType = ctLine  'Line Chart
                .ChartStyle = csLines  'Lines only
                .MainTitle.Text = "Simple Line Graph"  'change desired options
                .SubTitle.Text = "Five Available Line Styles"
                .XTitle.Text = "X Axis"
                .YTitle.Text = "Y Axis"
                .DATA.ColCount = 5  'Set .Data Grid dimensions
                .DATA.RowCount = 12
                k = 100  'Load the data
                RANDOMIZE
                FOR i = 1 TO .DATA.ColCount  'for each col
                    .Series(i).LineStyle = (i - 1) MOD 5  'Cycle line styles
                    .DATA.Cell(i , 0) = "Group " + STR$(i) 'Legend in Row 0 of Each Col
                    FOR j = 1 TO .DATA.RowCount  'add data to each row
                        .DATA.Cell(0 , j) = "Label " + STR$(j) 'X Labels
                        .DATA.Cell(i , j) = STR$(RND * k) 'Y Values
                    NEXT j
                NEXT i
                .DrawChart(FALSE) 'Draw it!
            END WITH

        CASE "Line w/Points"
            ClickedLine = ClickedLine + 1  'Change options on existing chart
            IF ClickedLine > 3 THEN ClickedLine = 1  'one by one
            WITH Graph
                .Initialize  'Set defaults
                .ChartType = ctLine  'Line Chart
                .ChartStyle = csBoth  'Points and Lines
                .MainTitle.Text = "Line Graph With Points"  'change desired options
                .SubTitle.Text = "Tics Only, Data Plotted in B&W, Custom Color Scheme"
                .XTitle.Text = "X Axis"
                .YTitle.Text = "Y Axis"
                IF ClickedLine = 2 THEN .YAxis.LogScale = TRUE
                IF ClickedLine = 3 THEN .ChartStyle = csPoints
                .BW = TRUE  'Data drawn in B&W
                .XAxis.Grid = FALSE  'Tics only
                .YAxis.Grid = FALSE
                .bgColor = .Colors(15) 'different colors
                .PlotAreaColor = .Colors(16)
                .MainFont.Color = .Colors(3)
                .SubFont.Color = .Colors(3)
                .AxisFont.Color = .Colors(7)
                .LegendFont.Color = .Colors(7)
                .Xaxis.Color = .Colors(7)
                .YAxis.Color = .Colors(7)
                .DATA.ColCount = 4  'Set .Data Grid dimensions
                .DATA.RowCount = 6
                k = 12  'Load the data
                RANDOMIZE
                FOR i = 1 TO .DATA.ColCount  'for each col
                    .DATA.Cell(i , 0) = "Group " + STR$(i) 'Legend in Row 0 of Each Col
                    FOR j = 1 TO .DATA.RowCount  'add data to each row
                        .DATA.Cell(0 , j) = "Lbl " + STR$(j) 'X Labels
                        .DATA.Cell(i , j) = STR$(RND * k) 'Y Values
                    NEXT j
                NEXT i
                .DrawChart(FALSE) 'Draw it!
            END WITH

            '-=============================== Case CandleSticks ==============================================-

        CASE "Candlesticks"

            frmmain.Caption = "QChartist - Please wait while loading chart..."
            Graph.Visible = 1
            split.Visible = 1
            splith.Visible = 1
            closedispchart.Visible = 1
            Scrollchart.Visible = 1
            pricescaleplusbtn.visible=1
            pricescaleminusbtn.visible=1
            addbarsbtn.visible=1

            IF showcanvas = 1 THEN
                'visible switch from 0 to 1 is necessary because of a "bug"
                canvas.Visible = 0
                canvas.Visible = 1
                closedispcanvas.Visible = 1
            END IF

            WITH Graph
                .Initialize  'Set defaults
                .ChartType = ctBox  'Box and Whisker Plot
                .ChartStyle = csWhisker
                .MainFont.Name = "Arial"
                .MainFont.Size = 10
                .MainTitle.Text = "File: " + importedfile(displayedfile) 'change desired options
                .XTitle.Text = "Time"
                .YTitle.Text = "Price"
                SELECT CASE axistypecomboitemindex
                    CASE 0 :
                        .YAxis.LogScale = FALSE
                        .XAxis.LogScale = FALSE

                    CASE 1 :
                        .YAxis.LogScale = TRUE
                        .XAxis.LogScale = FALSE


                END SELECT
                .YAxis.AutoScale = FALSE
                .XAxis.Grid = FALSE
                .XAxis.AutoScale = FALSE
                .plotareacolor = plotareacolor


                .DoLegend = FALSE
                .DATA.ColCount = numbars
                .DATA.RowCount = 50

                .MarkerSize = 0
                .Series(1).LineWidth = 1

                IF scrollmode = 0 THEN
                    .Data_Indi.RowCount = numbars
                    .Data_Indi.ColCount = 2000
                    canvas.separateindicator1.RowCount = 100
                    canvas.separateindicator1.ColCount = numbars
                ELSE
                    .Data_Indi.RowCount = 1
                    .Data_Indi.ColCount = 1
                    canvas.separateindicator1.RowCount = 1
                    canvas.separateindicator1.ColCount = 1
                END IF

                DIM l AS INTEGER
                l = - 1

                IF chartstart > chartbars(displayedfile) - numbars THEN
                    chartstart = chartbars(displayedfile) - numbars
                END IF


                IF useindi.Checked = 1 THEN
                    IF scrollmode = 0 THEN
                        REDIM Open(0 TO 0) AS DOUBLE
                        REDIM high(0 TO 0) AS DOUBLE
                        REDIM low(0 TO 0) AS DOUBLE
                        REDIM Close(0 TO 0) AS DOUBLE
                        REDIM volume(0 TO 0) AS INTEGER
                        'REDIM date(0 TO 0) AS STRING
                        'REDIM time(0 TO 0) AS STRING
                        'REDIM datetimeserial(0 TO 0) AS double

                        REDIM Open(1 TO 1000) AS DOUBLE
                        REDIM high(1 TO 1000) AS DOUBLE
                        REDIM low(1 TO 1000) AS DOUBLE
                        REDIM Close(1 TO 1000) AS DOUBLE
                        REDIM volume(1 TO 1000) AS INTEGER
                        'REDIM date(1 TO 1000) AS STRING
                        'REDIM time(1 TO 1000) AS STRING
                        'REDIM datetimeserial(1 TO 1000) AS double

                        DIM o AS INTEGER
                        o = 0
                        
                        dim year as integer,month as integer,day as integer, hour as integer,minute as integer,second as integer
                        defint ii2=chartbars(displayedfile) - VAL(cntbarsedit.Text)
                        if ii2<1 then ii2=1
                        cntbarseditstr=cntbarsedit.Text:cpptmpfuncreturn=varptr$(useindifunc(varptr(cntbarseditstr)))
                        
                        FOR i = chartbars(displayedfile) TO ii2 STEP - 1
                            date(o) = Grid.Cell(rowgridoffset + 1 , i)
                            date2(o) = Grid.Cell(rowgridoffset + 1 , i)                                                       
                            time(o) = Grid.Cell(rowgridoffset + 2 , i)
                            Open(o) = VAL(Grid.Cell(rowgridoffset + 3 , i))
                            high(o) = VAL(Grid.Cell(rowgridoffset + 4 , i))
                            low(o) = VAL(Grid.Cell(rowgridoffset + 5 , i))
                            Close(o) = VAL(Grid.Cell(rowgridoffset + 6 , i))
                            volume(o) = VAL(Grid.Cell(rowgridoffset + 7 , i))
                            year = VAL(MID$(date(o) , 0 , 4))
                            month = VAL(MID$(date(o) , 6 , 2))
                            day = VAL(MID$(date(o) , 9 , 2))
                            hour = VAL(MID$(time(o) , 0 , 2))
                            minute = VAL(MID$(time(o) , 4 , 2))
                            second=0
                            parameters=str$(year)+";"+str$(month)+";"+str$(day)+";"+str$(hour)+";"+str$(minute)+";"+str$(second)
                            datetimeserial(o)=val(varptr$(calculate_seconds_since_1_1_1970_cpp(varptr(parameters)))) 'DateSerial (year, month, day)
                            'datetimeserial(o)=datetimeserial(o)*24*60*60
                            'datetimeserial(o)=datetimeserial(o)+(hour*60*60)
                            'datetimeserial(o)=datetimeserial(o)+(minute*60) 
                            o ++                                                                                                                                            
                        NEXT i

                    END IF
                END IF    
                
                date(0) = Grid.Cell(rowgridoffset + 1 , chartbars(displayedfile)) ' Added this because of a bug
                date2(0) = Grid.Cell(rowgridoffset + 1 , chartbars(displayedfile)) ' Added this because of a bug                                                       
                time(0) = Grid.Cell(rowgridoffset + 2 , chartbars(displayedfile)) ' Added this because of a bug
                Open(0) = VAL(Grid.Cell(rowgridoffset + 3 , chartbars(displayedfile))) ' Added this because of a bug
                high(0) = VAL(Grid.Cell(rowgridoffset + 4 , chartbars(displayedfile))) ' Added this because of a bug
                low(0) = VAL(Grid.Cell(rowgridoffset + 5 , chartbars(displayedfile))) ' Added this because of a bug
                Close(0) = VAL(Grid.Cell(rowgridoffset + 6 , chartbars(displayedfile))) ' Added this because of a bug
                volume(0) = VAL(Grid.Cell(rowgridoffset + 7 , chartbars(displayedfile))) ' Added this because of a bug  
                year = VAL(MID$(date(0) , 0 , 4)) ' Added this because of a bug
                month = VAL(MID$(date(0) , 6 , 2)) ' Added this because of a bug
                day = VAL(MID$(date(0) , 9 , 2)) ' Added this because of a bug
                hour = VAL(MID$(time(0) , 0 , 2)) ' Added this because of a bug
                minute = VAL(MID$(time(0) , 4 , 2)) ' Added this because of a bug
                second=0 ' Added this because of a bug
                parameters=str$(year)+";"+str$(month)+";"+str$(day)+";"+str$(hour)+";"+str$(minute)+";"+str$(second) ' Added this because of a bug
                datetimeserial(0)=val(varptr$(calculate_seconds_since_1_1_1970_cpp(varptr(parameters)))) 'DateSerial (year, month, day) ' Added this because of a bug                                                                

                bars = chartbars(displayedfile)
                barsstr=str$(bars):cpptmpfuncreturn=varptr$(setbars(varptr(barsstr)))

                FOR i = chartstart TO chartstart + .DATA.ColCount  'for each col
                    l ++

                    .Series(l).AutoColor = FALSE

                    IF Grid.Cell(rowgridoffset + 6 , i) > Grid.Cell(rowgridoffset + 3 , i) THEN
                        .Series(l).Color = .Colors(1)
                    END IF
                    IF Grid.Cell(rowgridoffset + 6 , i) < Grid.Cell(rowgridoffset + 3 , i) THEN
                        .Series(l).Color = .Colors(2)
                    END IF
                    IF Grid.Cell(rowgridoffset + 6 , i) = Grid.Cell(rowgridoffset + 3 , i) THEN
                        .Series(l).Color = .Colors(0)
                    END IF

                    .DATA.Cell(l , 0) = Grid.Cell(rowgridoffset + 1 , i) + " " + Grid.Cell(rowgridoffset + 2 , i) 'Legend in Row 0 of Each Col
                    .DATA.Cell(l , 1) = Grid.Cell(rowgridoffset + 4 , i)
                    .DATA.Cell(l , 2) = Grid.Cell(rowgridoffset + 6 , i)
                    .DATA.Cell(l , 3) = STR$(0)
                    .DATA.Cell(l , 4) = Grid.Cell(rowgridoffset + 3 , i)
                    .DATA.Cell(l , 5) = Grid.Cell(rowgridoffset + 5 , i)
                                        

                    IF scrollmode = 0 THEN
                        '-================================= Indicators area ========================================-

                        DIM indicol AS INTEGER
                        indicol = 0
                        DIM barindex AS INTEGER
                        DIM barsback AS INTEGER
                        DIM period AS INTEGER
                        DIM ibar AS INTEGER
                        ibar = i
                        DIM lastbar AS INTEGER
                        lastbar = chartstart + .DATA.ColCount
                        DIM openx AS INTEGER
                        DIM highx AS INTEGER
                        DIM lowx AS INTEGER
                        DIM closex AS INTEGER
                        openx = rowgridoffset + 3
                        highx = rowgridoffset + 4
                        lowx = rowgridoffset + 5
                        closex = rowgridoffset + 6
                        DIM lbar AS INTEGER
                        lbar = ibar - chartstart
                        DIM offset AS INTEGER
                        dim bufnamestr as string
                        dim offsetstr as string
                        offset = chartbars(displayedfile) - ibar
                        offsetstr=str$(offset)
                        dim periodstr as string
                        dim barsbackstr as string
                        dim curtfstr as string
			dim tfbasestr as string
                        IF useindi.Checked = 1 THEN
                            DIM lo AS INTEGER
                            FOR lo = 1 TO .Data_Indi.RowCount STEP 2
                                .Data_Indi.Cell(lo , l) = STR$(l) 'Legend in Row 0 of Each Col
                            NEXT lo
                            FOR lo = 2 TO .Data_Indi.RowCount STEP 2
                                .Data_Indi.Cell(lo , l) = STR$(0)
                            NEXT lo
                        END IF

                        DIM drawid AS INTEGER
                        drawid = 2
                        DIM indiid AS INTEGER
                        indiid = - 1
                        DIM canvasid AS INTEGER

                        canvasid = 0
                          
'------------------------- ADR112 cpp -------------------------------------------------
indiid++
if indicatorslistsel.item(indiid)="x" then

if lbar=1 then
periodstr=ADR112cppperiodedit.text
tfbasestr=str$(ADR112cpptfbasecombo.itemindex)
cpptmpfuncreturn=varptr$(ADR112cpp(varptr(periodstr),varptr(tfbasestr)))
end if

barsback=700 '<--- can also be something like VAL(ADR112cppbarsbackedit.text)

if ibar>=lastbar-barsback then
    indicolor(drawid)=blue '<--- replace with your color
    bufnamestr="ADR112cppbuffer1"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
    indicolor(drawid)=lightblue '<--- replace with your color
    bufnamestr="ADR112cppbuffer2"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
    indicolor(drawid)=yellow '<--- replace with your color
    bufnamestr="ADR112cppbuffer3"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
    indicolor(drawid)=pink '<--- replace with your color
    bufnamestr="ADR112cppbuffer4"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
    indicolor(drawid)=red '<--- replace with your color
    bufnamestr="ADR112cppbuffer5"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
end if

end if
'------------------------- End ADR112 cpp -------------------------------------------------
'--------ATR Channels-------------------------------------------------------------
indiid++
        
                    if indicatorslistsel.item(indiid)="x" then 

                        if lbar=1 then     
                            atrchannels
                        end if

                         barsback=200 
                    

                        if ibar>=lastbar-barsback then
            
                            indicolor(drawid)=olive
				.Data_Indi.Cell(drawid,lbar)= STR$(ch3up_buffer5(offset))
				drawid=drawid+2
                            indicolor(drawid)=olive
				.Data_Indi.Cell(drawid,lbar)= STR$(ch3dn_buffer6(offset))
				drawid=drawid+2
                                                                                
                        end if                      
                                             
                    end if
        
        '--------End ATR Channels----------------------------------------------------------        		
'------------------------- balance_point_fibo -------------------------------------------------
indiid++
if indicatorslistsel.item(indiid)="x" then

if lbar=1 then
curtfstr=balance_point_fibocurtfedit.text
cpptmpfuncreturn=varptr$(balance_point_fibo(varptr(curtfstr)))
end if

barsback=200 '<--- can also be something like VAL(balance_point_fibobarsbackedit.text)

if ibar>=lastbar-barsback then
    indicolor(drawid)=lightblue '<--- replace with your color
    bufnamestr="dbp"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
indicolor(drawid)=red '<--- replace with your color
    bufnamestr="dbph"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
indicolor(drawid)=red '<--- replace with your color
    bufnamestr="dbpl"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
end if

end if
'------------------------- End balance_point_fibo -------------------------------------------------
'--------Bollinger Bands-------------------------------------------------------------
indiid++
        
                    if indicatorslistsel.item(indiid)="x" then 

                        if lbar=1 then     
                            bands
                        end if

                         barsback=val(bandsbarsbackedit.text)
                    

                        if ibar>=lastbar-barsback then
            
                            indicolor(drawid)=mediumseagreen
				.Data_Indi.Cell(drawid,lbar)= STR$(bandsmovingbuffer(offset))
				drawid=drawid+2
                            indicolor(drawid)=mediumseagreen
				.Data_Indi.Cell(drawid,lbar)= STR$(bandsupperbuffer(offset))
				drawid=drawid+2
                            indicolor(drawid)=mediumseagreen                                                                    
                            .Data_Indi.Cell(drawid,lbar)= STR$(bandslowerbuffer(offset))          
				drawid=drawid+2
                        end if                      
                                             
                    end if
        
        '--------End Bollinger Bands----------------------------------------------------------                    
'------------------------- bandscpp -------------------------------------------------
indiid++
if indicatorslistsel.item(indiid)="x" then

if lbar=1 then
periodstr=bandscppperiodedit.text
cpptmpfuncreturn=varptr$(bandscpp(varptr(periodstr)))
end if

barsback=200 '<--- can also be something like VAL(bandscppbarsbackedit.text)

if ibar>=lastbar-barsback then
    indicolor(drawid)=mediumseagreen '<--- replace with your color
    bufnamestr="bandsmovingbuffer"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
    indicolor(drawid)=mediumseagreen '<--- replace with your color
    bufnamestr="bandsupperbuffer"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
    indicolor(drawid)=mediumseagreen '<--- replace with your color
    bufnamestr="bandslowerbuffer"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
end if

end if
'------------------------- End bandscpp -------------------------------------------------
'--------BB - HL-------------------------------------------------------------
indiid++
        
                    if indicatorslistsel.item(indiid)="x" then 
            
                        if lbar=1 then     
                            bbhl                        
                        end if

                         barsback=VAL(bbhlbarsbackedit.text)                            

                        if ibar>=lastbar-barsback then
                            indicolor(drawid)=purple
                            .Data_Indi.Cell(drawid,lbar)= STR$(upperbandbuffer(offset))
				drawid=drawid+2
                            indicolor(drawid)=purple
                            .Data_Indi.Cell(drawid,lbar)= STR$(lowerbandbuffer(offset))
				drawid=drawid+2
            
                        end if                      
                     
                    end if			
        
        '--------End BB - HL----------------------------------------------------------       
'------------------------- BB - HL cpp -------------------------------------------------
indiid++
if indicatorslistsel.item(indiid)="x" then

if lbar=1 then
periodstr=bbhlcppperiodedit.text
barsbackstr=bbhlcppbarsbackedit.text
cpptmpfuncreturn=varptr$(bbhlcpp(varptr(periodstr),varptr(barsbackstr)))
end if

barsback=chartbars(displayedfile) '<--- can also be something like VAL(bbhlcppbarsbackedit.text)

if ibar>=lastbar-barsback then
    indicolor(drawid)=purple '<--- replace with your color
    bufnamestr="upperbandbuffer"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
    indicolor(drawid)=purple '<--- replace with your color
    bufnamestr="lowerbandbuffer"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
end if

end if
'------------------------- End BB - HL cpp -------------------------------------------------
'------------------------- bowels -------------------------------------------------
indiid++
if indicatorslistsel.item(indiid)="x" then

if lbar=1 then
periodstr=bowelsperiodedit.text
tfbasestr=str$(bowelstfbasecombo.itemindex)
cpptmpfuncreturn=varptr$(bowels(varptr(periodstr),varptr(tfbasestr)))
end if

barsback=200 '<--- can also be something like VAL(bowelsbarsbackedit.text)

if ibar>=lastbar-barsback then
    indicolor(drawid)=purple '<--- replace with your color
    bufnamestr="pivot"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
indicolor(drawid)=red '<--- replace with your color
    bufnamestr="r1"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
indicolor(drawid)=red '<--- replace with your color
    bufnamestr="r2"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
indicolor(drawid)=red '<--- replace with your color
    bufnamestr="r3"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
indicolor(drawid)=green '<--- replace with your color
    bufnamestr="s1"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
indicolor(drawid)=green '<--- replace with your color
    bufnamestr="s2"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
indicolor(drawid)=green '<--- replace with your color
    bufnamestr="s3"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
end if

end if
'------------------------- End bowels -------------------------------------------------
'--------Center Of Gravity-------------------------------------------------------------
indiid++
        
                    if indicatorslistsel.item(indiid)="x" then 

                        if lbar=1 then     
                            cog
                        end if

                         barsback=300 
                    
                        if ibar>=lastbar-barsback then
                            indicolor(drawid)=lightblue
				.Data_Indi.Cell(drawid,lbar)= STR$(fx(offset))
				drawid=drawid+2
                            indicolor(drawid)=red
				.Data_Indi.Cell(drawid,lbar)= STR$(sqh(offset))
				drawid=drawid+2
                            indicolor(drawid)=red
				.Data_Indi.Cell(drawid,lbar)= STR$(sql(offset))
				drawid=drawid+2
                            indicolor(drawid)=crimson
				.Data_Indi.Cell(drawid,lbar)= STR$(stdh(offset))
				drawid=drawid+2
                            indicolor(drawid)=crimson
				.Data_Indi.Cell(drawid,lbar)= STR$(stdl(offset))
				drawid=drawid+2
                                                                                                                                                                    
                        end if                                                          
         
                    end if
        
        '--------End Center Of Gravity----------------------------------------------------------   
'------------------------- COG of RSTL -------------------------------------------------
indiid++
if indicatorslistsel.item(indiid)="x" then

if lbar=1 then
barsbackstr=rstlcogcppbarsbackedit.text
defstr kstdstr=kstdedit.text
cpptmpfuncreturn=varptr$(rstlcogcpp(varptr(barsbackstr),varptr(kstdstr)))
end if

barsback=300 '<--- can also be something like VAL(RSTLCOGbarsbackedit.text)

if ibar>=lastbar-barsback then
indicolor(drawid)=lightblue
    bufnamestr="fx2"
                .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
                drawid=drawid+2
                            indicolor(drawid)=yellow
                            bufnamestr="sqh2"
                .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
                drawid=drawid+2
                            indicolor(drawid)=yellow
                            bufnamestr="sql2"
                .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
                drawid=drawid+2
                            indicolor(drawid)=yellow
                            bufnamestr="stdh2"
                .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
                drawid=drawid+2
                            indicolor(drawid)=yellow
                            bufnamestr="stdl2"
                .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
                drawid=drawid+2
end if

end if
'------------------------- End COG of RSTL -------------------------------------------------
'------------------------- Center Of Gravity cpp -------------------------------------------------
indiid++
if indicatorslistsel.item(indiid)="x" then

if lbar=1 then
barsbackstr=cogcppbarsbackedit.text
cpptmpfuncreturn=varptr$(cogcpp(varptr(barsbackstr)))
end if

barsback=300 '<--- can also be something like VAL(cogcppbarsbackedit.text)

if ibar>=lastbar-barsback then    
    indicolor(drawid)=lightblue
    bufnamestr="fx"
                .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
                drawid=drawid+2
                            indicolor(drawid)=red
                            bufnamestr="sqh"
                .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
                drawid=drawid+2
                            indicolor(drawid)=red
                            bufnamestr="sql"
                .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
                drawid=drawid+2
                            indicolor(drawid)=crimson
                            bufnamestr="stdh"
                .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
                drawid=drawid+2
                            indicolor(drawid)=crimson
                            bufnamestr="stdl"
                .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
                drawid=drawid+2
end if

end if
'------------------------- End Center Of Gravity cpp -------------------------------------------------
'------------------------- Din fibo high cpp -------------------------------------------------
indiid++
if indicatorslistsel.item(indiid)="x" then

if lbar=1 then
periodstr=Din_fibo_highperiodedit.text
curtfstr=Din_fibo_highcurtfedit.text
cpptmpfuncreturn=varptr$(dinfibohighcpp(varptr(curtfstr)))
end if

barsback=200 '<--- can also be something like VAL(Din_fibo_highbarsbackedit.text)

if ibar>=lastbar-barsback then
    indicolor(drawid)=blue '<--- replace with your color
    bufnamestr="dinfibohighbuffer1"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
indicolor(drawid)=yellow '<--- replace with your color
    bufnamestr="dinfibohighbuffer2"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
end if

end if
'------------------------- End Din fibo high cpp -------------------------------------------------
'------------------------- Enveloppes -------------------------------------------------
indiid++
if indicatorslistsel.item(indiid)="x" then

if lbar=1 then
envelop
end if

barsback=200 '<--- can also be something like VAL(envelopbarsbackedit.text)

if ibar>=lastbar-barsback then
    indicolor(drawid)=green '<--- replace with your color
    .Data_Indi.Cell(drawid,lbar)= STR$(ci(offset))
    drawid=drawid+2
	indicolor(drawid)=red '<--- replace with your color
    .Data_Indi.Cell(drawid,lbar)= STR$(UperBuffer (offset))
    drawid=drawid+2
	indicolor(drawid)=red '<--- replace with your color
    .Data_Indi.Cell(drawid,lbar)= STR$(DownBuffer (offset))
    drawid=drawid+2
end if

end if
'------------------------- End Enveloppes -------------------------------------------------
'------------------------- Levels -------------------------------------------------
indiid++
if indicatorslistsel.item(indiid)="x" then

if lbar=1 then
periodstr=Levelsperiodedit.text
cpptmpfuncreturn=varptr$(Levels(varptr(periodstr)))
end if

barsback=200 '<--- can also be something like VAL(Levelsbarsbackedit.text)

if ibar>=lastbar-barsback then
    indicolor(drawid)=blue '<--- replace with your color
    bufnamestr="sopr1"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
indicolor(drawid)=blue '<--- replace with your color
    bufnamestr="sopr2"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
indicolor(drawid)=blue '<--- replace with your color
    bufnamestr="sopr3"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
indicolor(drawid)=blue '<--- replace with your color
    bufnamestr="sopr4"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
indicolor(drawid)=blue '<--- replace with your color
    bufnamestr="sopr5"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
indicolor(drawid)=orange '<--- replace with your color
    bufnamestr="pod1"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
indicolor(drawid)=orange '<--- replace with your color
    bufnamestr="pod2"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
indicolor(drawid)=orange '<--- replace with your color
    bufnamestr="pod3"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
indicolor(drawid)=orange '<--- replace with your color
    bufnamestr="pod4"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
indicolor(drawid)=orange '<--- replace with your color
    bufnamestr="pod5"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
end if

end if
'------------------------- End Levels -------------------------------------------------

                   '--------Moving Average-------------------------------------------------------------
indiid++
        
                    if indicatorslistsel.item(indiid)="x" then 
            
                        if lbar=1 then     
      
                            sma(0)                        
                        end if

                        barsback=VAL(mabarsbackedit.text)                        

                        if ibar>=lastbar-barsback then
                           indicolor(drawid)=blue
                           .Data_Indi.Cell(drawid,lbar)= STR$(extmapbuffer(offset))
            			drawid=drawid+2
                       end if                      
                     
                    end if			
        
        '--------End Moving Average----------------------------------------------------------     
'------------------------- MA Chanels FiboEnv Mid -------------------------------------------------
indiid++
if indicatorslistsel.item(indiid)="x" then

if lbar=1 then
periodstr=MA_Chanels_FiboEnv_Midperiodedit.text
curtfstr=MA_Chanels_FiboEnv_Midcurtfedit.text
cpptmpfuncreturn=varptr$(MA_Chanels_FiboEnv_Mid(varptr(periodstr),varptr(curtfstr)))
end if

barsback=500 '<--- can also be something like VAL(MA_Chanels_FiboEnv_Midbarsbackedit.text)

if ibar>=lastbar-barsback then
    indicolor(drawid)=blue '<--- replace with your color
    bufnamestr="MA_Chanels_FiboEnv_Midbuffer1"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
indicolor(drawid)=blue '<--- replace with your color
    bufnamestr="MA_Chanels_FiboEnv_Midbuffer2"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
indicolor(drawid)=blue '<--- replace with your color
    bufnamestr="MA_Chanels_FiboEnv_Midbuffer3"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
indicolor(drawid)=blue '<--- replace with your color
    bufnamestr="MA_Chanels_FiboEnv_Midbuffer4"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
indicolor(drawid)=blue '<--- replace with your color
    bufnamestr="MA_Chanels_FiboEnv_Midbuffer5"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
indicolor(drawid)=blue '<--- replace with your color
    bufnamestr="MA_Chanels_FiboEnv_Midbuffer6"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
indicolor(drawid)=blue '<--- replace with your color
    bufnamestr="MA_Chanels_FiboEnv_Midbuffer7"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
end if

end if
'------------------------- End MA Chanels FiboEnv Mid -------------------------------------------------
'------------------------- Murrey_Math -------------------------------------------------
indiid++
if indicatorslistsel.item(indiid)="x" then

if lbar=1 then
barsbackstr=Murrey_Mathbarsbackedit.text
cpptmpfuncreturn=varptr$(Murrey_Math(varptr(barsbackstr)))
end if

barsback=val(barsbackstr) '<--- can also be something like VAL(Murrey_Mathbarsbackedit.text)

if ibar>=lastbar-barsback then
    indicolor(drawid)=red '<--- replace with your color
    bufnamestr="Murrey_Mathbuffer1"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2

indicolor(drawid)=orange '<--- replace with your color
    bufnamestr="Murrey_Mathbuffer2"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2

indicolor(drawid)=lightblue '<--- replace with your color
    bufnamestr="Murrey_Mathbuffer3"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2

indicolor(drawid)=yellow '<--- replace with your color
    bufnamestr="Murrey_Mathbuffer4"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2

indicolor(drawid)=pink '<--- replace with your color
    bufnamestr="Murrey_Mathbuffer5"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2

indicolor(drawid)=green '<--- replace with your color
    bufnamestr="Murrey_Mathbuffer6"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2

indicolor(drawid)=lightblue '<--- replace with your color
    bufnamestr="Murrey_Mathbuffer7"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2

indicolor(drawid)=green '<--- replace with your color
    bufnamestr="Murrey_Mathbuffer8"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2

indicolor(drawid)=pink '<--- replace with your color
    bufnamestr="Murrey_Mathbuffer9"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2

indicolor(drawid)=yellow '<--- replace with your color
    bufnamestr="Murrey_Mathbuffer10"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2

indicolor(drawid)=lightblue '<--- replace with your color
    bufnamestr="Murrey_Mathbuffer11"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2

indicolor(drawid)=orange '<--- replace with your color
    bufnamestr="Murrey_Mathbuffer12"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2

indicolor(drawid)=red '<--- replace with your color
    bufnamestr="Murrey_Mathbuffer13"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
end if

end if
'------------------------- End Murrey_Math -------------------------------------------------
'------------------------- Planetary lines -------------------------------------------------
indiid++
if indicatorslistsel.item(indiid)="x" then

if lbar=1 then
Planetary_lines
end if

barsback=val(barslimitedit.text) '<--- can also be something like VAL(Planetary_linesbarsbackedit.text)

if ibar>=lastbar-barsback then

if earth.checked=1 then
defint increarth
for increarth=0 to 12
    indicolor(drawid)=blue '<--- replace with your color
    .Data_Indi.Cell(drawid,lbar)= STR$(Planetary_lines_earthbuffer(increarth,offset))
    drawid=drawid+2
next increarth
end if

if jupiter.checked=1 then
defint incrjupiter
for incrjupiter=0 to 12
	indicolor(drawid)=olive '<--- replace with your color
    .Data_Indi.Cell(drawid,lbar)= STR$(Planetary_lines_jupiterbuffer(incrjupiter,offset))
    drawid=drawid+2
next incrjupiter
end if

if mars.checked=1 then
defint incrmars
for incrmars=0 to 12
indicolor(drawid)=red '<--- replace with your color	
    .Data_Indi.Cell(drawid,lbar)= STR$(Planetary_lines_marsbuffer(incrmars,offset))
    drawid=drawid+2
next incrmars
end if

if mercury.checked=1 then
defint incrmercury
for incrmercury=0 to 12
indicolor(drawid)=orange '<--- replace with your color	
    .Data_Indi.Cell(drawid,lbar)= STR$(Planetary_lines_mercurybuffer(incrmercury,offset))
    drawid=drawid+2
next incrmercury
end if

if neptune.checked=1 then
defint incrneptune
for incrneptune=0 to 12
indicolor(drawid)=purple '<--- replace with your color	
    .Data_Indi.Cell(drawid,lbar)= STR$(Planetary_lines_neptunebuffer(incrneptune,offset))
    drawid=drawid+2
next incrneptune
end if

if saturn.checked=1 then
defint incrsaturn
for incrsaturn=0 to 12
indicolor(drawid)=gray '<--- replace with your color	
    .Data_Indi.Cell(drawid,lbar)= STR$(Planetary_lines_saturnbuffer(incrsaturn,offset))
    drawid=drawid+2
next incrsaturn
end if

if uranus.checked=1 then
defint incruranus
for incruranus=0 to 12
indicolor(drawid)=lightblue '<--- replace with your color	
    .Data_Indi.Cell(drawid,lbar)= STR$(Planetary_lines_uranusbuffer(incruranus,offset))
    drawid=drawid+2
next incruranus
end if

if venus.checked=1 then
defint incrvenus
for incrvenus=0 to 12
indicolor(drawid)=pink '<--- replace with your color	
    .Data_Indi.Cell(drawid,lbar)= STR$(Planetary_lines_venusbuffer(incrvenus,offset))
    drawid=drawid+2
next incrvenus
end if

if sun.checked=1 then
defint incrsun
for incrsun=0 to 12
indicolor(drawid)=yellow '<--- replace with your color	
    .Data_Indi.Cell(drawid,lbar)= STR$(Planetary_lines_sunbuffer(incrsun,offset))
    drawid=drawid+2
next incrsun
end if

if moon.checked=1 then
defint incrmoon
for incrmoon=0 to 12
indicolor(drawid)=white '<--- replace with your color	
    .Data_Indi.Cell(drawid,lbar)= STR$(Planetary_lines_moonbuffer(incrmoon,offset))
    drawid=drawid+2
next incrmoon
end if

if pluto.checked=1 then
defint incrpluto
for incrpluto=0 to 12
indicolor(drawid)=black '<--- replace with your color	
    .Data_Indi.Cell(drawid,lbar)= STR$(Planetary_lines_plutobuffer(incrpluto,offset))
    drawid=drawid+2
next incrpluto
end if

if mean_node.checked=1 then
defint incrmean_node
for incrmean_node=0 to 12
indicolor(drawid)=green '<--- replace with your color	
    .Data_Indi.Cell(drawid,lbar)= STR$(Planetary_lines_mean_nodebuffer(incrmean_node,offset))
    drawid=drawid+2
next incrmean_node
end if

if true_node.checked=1 then
defint incrtrue_node
for incrtrue_node=0 to 12
indicolor(drawid)=red '<--- replace with your color	
    .Data_Indi.Cell(drawid,lbar)= STR$(Planetary_lines_true_nodebuffer(incrtrue_node,offset))
    drawid=drawid+2
next incrtrue_node
end if

if mean_apog.checked=1 then
defint incrmean_apog
for incrmean_apog=0 to 12
indicolor(drawid)=blue '<--- replace with your color	
    .Data_Indi.Cell(drawid,lbar)= STR$(Planetary_lines_mean_apogbuffer(incrmean_apog,offset))
    drawid=drawid+2
next incrmean_apog
end if

if oscu_apog.checked=1 then
defint incroscu_apog
for incroscu_apog=0 to 12
indicolor(drawid)=olive '<--- replace with your color	
    .Data_Indi.Cell(drawid,lbar)= STR$(Planetary_lines_oscu_apogbuffer(incroscu_apog,offset))
    drawid=drawid+2
next incroscu_apog
end if

if chiron.checked=1 then
defint incrchiron
for incrchiron=0 to 12
indicolor(drawid)=orange '<--- replace with your color	
    .Data_Indi.Cell(drawid,lbar)= STR$(Planetary_lines_chironbuffer(incrchiron,offset))
    drawid=drawid+2
next incrchiron
end if

if pholus.checked=1 then
defint incrpholus
for incrpholus=0 to 12
indicolor(drawid)=red '<--- replace with your color	
    .Data_Indi.Cell(drawid,lbar)= STR$(Planetary_lines_pholusbuffer(incrpholus,offset))
    drawid=drawid+2
next incrpholus
end if

if ceres.checked=1 then
defint incrceres
for incrceres=0 to 12
indicolor(drawid)=pink '<--- replace with your color	
    .Data_Indi.Cell(drawid,lbar)= STR$(Planetary_lines_ceresbuffer(incrceres,offset))
    drawid=drawid+2
next incrceres
end if

if pallas.checked=1 then
defint incrpallas
for incrpallas=0 to 12
indicolor(drawid)=gray '<--- replace with your color	
    .Data_Indi.Cell(drawid,lbar)= STR$(Planetary_lines_pallasbuffer(incrpallas,offset))
    drawid=drawid+2
next incrpallas
end if

if juno.checked=1 then
defint incrjuno
for incrjuno=0 to 12
indicolor(drawid)=purple '<--- replace with your color	
    .Data_Indi.Cell(drawid,lbar)= STR$(Planetary_lines_junobuffer(incrjuno,offset))
    drawid=drawid+2
next incrjuno
end if

if vesta.checked=1 then
defint incrvesta
for incrvesta=0 to 12
indicolor(drawid)=lightblue '<--- replace with your color	
    .Data_Indi.Cell(drawid,lbar)= STR$(Planetary_lines_vestabuffer(incrvesta,offset))
    drawid=drawid+2
next incrvesta
end if

if nplanets.checked=1 then
defint incrnplanets
for incrnplanets=0 to 12
indicolor(drawid)=white '<--- replace with your color	
    .Data_Indi.Cell(drawid,lbar)= STR$(Planetary_lines_nplanetsbuffer(incrnplanets,offset))
    drawid=drawid+2
next incrnplanets
end if

if ast_offset.checked=1 then
defint incrast_offset
for incrast_offset=0 to 12
indicolor(drawid)=yellow '<--- replace with your color	
    .Data_Indi.Cell(drawid,lbar)= STR$(Planetary_lines_ast_offsetbuffer(incrast_offset,offset))
    drawid=drawid+2
next incrast_offset
end if

if Planetary_average_checkbox.checked=1 then
defint incravg
for incravg=0 to 12
indicolor(drawid)=yellow '<--- replace with your color	
    .Data_Indi.Cell(drawid,lbar)= STR$(Planetary_lines_averagebuffer(incravg,offset))
    drawid=drawid+2
next incrvenus
end if

end if

end if
'------------------------- End Planetary lines -------------------------------------------------
'------------------------- priceclose1440 -------------------------------------------------
indiid++
if indicatorslistsel.item(indiid)="x" then

if lbar=1 then
priceclose1440
end if

barsback=200 '<--- can also be something like VAL(priceclose1440barsbackedit.text)

if ibar>=lastbar-barsback then
    indicolor(drawid)=blue '<--- replace with your color
    .Data_Indi.Cell(drawid,lbar)= STR$(priceclose1440buffer(offset))
    drawid=drawid+2
end if

end if
'------------------------- End priceclose1440 -------------------------------------------------
'------------------------- RSTL -------------------------------------------------
indiid++
if indicatorslistsel.item(indiid)="x" then

if lbar=1 then
periodstr=RSTLperiodedit.text
cpptmpfuncreturn=varptr$(RSTL(varptr(periodstr)))
end if

barsback=200 '<--- can also be something like VAL(RSTLbarsbackedit.text)

if ibar>=lastbar-barsback then
    indicolor(drawid)=purple '<--- replace with your color
    bufnamestr="RSTLbuffer"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
end if

end if
'------------------------- End RSTL -------------------------------------------------
'------------------------- Fibo MA Channels -------------------------------------------------
indiid++
if indicatorslistsel.item(indiid)="x" then

if lbar=1 then
smafibo
end if

barsback=200 '<--- can also be something like VAL(myindibarsbackedit.text)

if ibar>=lastbar-barsback then
    indicolor(drawid)=red '<--- replace with your color
    .Data_Indi.Cell(drawid,lbar)= STR$(fibobuffer1(offset)) '<--- replace myindibuffer with your indicator buffer name
    drawid=drawid+2
	indicolor(drawid)=orange '<--- replace with your color
    .Data_Indi.Cell(drawid,lbar)= STR$(fibobuffer2(offset)) '<--- replace myindibuffer with your indicator buffer name
    drawid=drawid+2
	indicolor(drawid)=yellow '<--- replace with your color
    .Data_Indi.Cell(drawid,lbar)= STR$(fibobuffer3(offset)) '<--- replace myindibuffer with your indicator buffer name
    drawid=drawid+2
	indicolor(drawid)=white '<--- replace with your color
    .Data_Indi.Cell(drawid,lbar)= STR$(fibobuffer4(offset)) '<--- replace myindibuffer with your indicator buffer name
    drawid=drawid+2
	indicolor(drawid)=white '<--- replace with your color
    .Data_Indi.Cell(drawid,lbar)= STR$(fibobuffer5(offset)) '<--- replace myindibuffer with your indicator buffer name
    drawid=drawid+2
	indicolor(drawid)=yellow '<--- replace with your color
    .Data_Indi.Cell(drawid,lbar)= STR$(fibobuffer6(offset)) '<--- replace myindibuffer with your indicator buffer name
    drawid=drawid+2
	indicolor(drawid)=orange '<--- replace with your color
    .Data_Indi.Cell(drawid,lbar)= STR$(fibobuffer7(offset)) '<--- replace myindibuffer with your indicator buffer name
    drawid=drawid+2
	indicolor(drawid)=red '<--- replace with your color
    .Data_Indi.Cell(drawid,lbar)= STR$(fibobuffer8(offset)) '<--- replace myindibuffer with your indicator buffer name
    drawid=drawid+2
end if

end if
'------------------------- End Fibo MA Channels -------------------------------------------------
'------------------------- Time Series Forecast -------------------------------------------------
indiid++
if indicatorslistsel.item(indiid)="x" then

if lbar=1 then
TSF
end if

barsback=VAL(TSFbarsback.text) '<--- can also be something like VAL(myindibarsbackedit.text)

if ibar>=lastbar-barsback then
    indicolor(drawid)=Green '<--- replace with your color
    .Data_Indi.Cell(drawid,lbar)= STR$(tsfbuffer(offset)) '<--- replace myindibuffer with your indicator buffer name
    drawid=drawid+2
end if

end if
'------------------------- End Time Series Forecast -------------------------------------------------
'--------Vegas-------------------------------------------------------------
indiid++
        
                    if indicatorslistsel.item(indiid)="x" then 

                        if lbar=1 then     
                            vegas
                        end if

                         barsback=VAL(vegasbarsbackedit.text)
                    
                        if ibar>=lastbar-barsback then
            
                            indicolor(drawid)=red
                            .Data_Indi.Cell(drawid,lbar)= STR$(vegasup(offset))
				drawid=drawid+2            
                            indicolor(drawid)=red
                            .Data_Indi.Cell(drawid,lbar)= STR$(vegasdn(offset))
				drawid=drawid+2
            
                        end if                                                          
         
                    end if
        
        '--------End Vegas----------------------------------------------------------        
'------------------------- Volatility Pivot -------------------------------------------------
indiid++
if indicatorslistsel.item(indiid)="x" then

if lbar=1 then
VolatilityPivot
end if

barsback=val(VolatilityPivotbarsbackedit.text) '<--- can also be something like VAL(myindibarsbackedit.text)

if ibar>=lastbar-barsback then
    indicolor(drawid)=lightblue '<--- replace with your color
    .Data_Indi.Cell(drawid,lbar)= STR$(volatilitypivottrstop(offset)) '<--- replace myindibuffer with your indicator buffer name
    drawid=drawid+2
end if

end if
'------------------------- End Volatility Pivot -------------------------------------------------
'------------------------- Volatility Stop -------------------------------------------------
indiid++
if indicatorslistsel.item(indiid)="x" then

if lbar=1 then
periodstr=VolatilityStopperiodedit.text
cpptmpfuncreturn=varptr$(VolatilityStop(varptr(periodstr)))
end if

barsback=200 '<--- can also be something like VAL(VolatilityStopbarsbackedit.text)

if ibar>=lastbar-barsback then
    'indicolor(drawid)=red '<--- replace with your color
    'bufnamestr="volatilitystopBuffer1"
    '.Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    'drawid=drawid+2
    indicolor(drawid)=blue '<--- replace with your color
    bufnamestr="volatilitystopBuffer2"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
end if

end if
'------------------------- End Volatility Stop -------------------------------------------------
'------------------------- WaterLevel cpp -------------------------------------------------
indiid++
if indicatorslistsel.item(indiid)="x" then

if lbar=1 then
periodstr=waterlevelcppperiodedit.text
curtfstr=waterlevelcppcurtfedit.text
cpptmpfuncreturn=varptr$(initwaterlevelcpp(varptr(curtfstr)))
cpptmpfuncreturn=varptr$(waterlevelcpp(varptr(periodstr),varptr(curtfstr)))
end if

barsback=200 '<--- can also be something like VAL(waterlevelcppbarsbackedit.text)

if ibar>=lastbar-barsback then
    indicolor(drawid)=gold '<--- replace with your color
    bufnamestr="TimeFrame1Level"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
    indicolor(drawid)=green '<--- replace with your color
    bufnamestr="TimeFrame2Level"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
    indicolor(drawid)=red '<--- replace with your color
    bufnamestr="SellPrice"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
    indicolor(drawid)=olive '<--- replace with your color
    bufnamestr="BuyPrice"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
    indicolor(drawid)=orange '<--- replace with your color
    bufnamestr="TimeFrame2AverageMA1"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
    indicolor(drawid)=sweetblue '<--- replace with your color
    bufnamestr="TimeFrame2AverageMA2"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
    indicolor(drawid)=pink '<--- replace with your color
    bufnamestr="TimeFrame2AverageMA3"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
    indicolor(drawid)=blue '<--- replace with your color
    bufnamestr="TimeFrame2AverageMA4"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
end if

end if
'------------------------- End WaterLevel cpp -------------------------------------------------
'------------------------- Weekly Pivot cpp -------------------------------------------------
indiid++
if indicatorslistsel.item(indiid)="x" then

if lbar=1 then
barsbackstr=weeklypivotcppbarsbackedit.text
cpptmpfuncreturn=varptr$(weeklypivotcpp(varptr(barsbackstr)))
end if

barsback=val(barsbackstr) '<--- can also be something like VAL(weeklypivotcppbarsbackedit.text)

if ibar>=lastbar-barsback then
    indicolor(drawid)=purple '<--- replace with your color
    bufnamestr="PBuffer"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
    indicolor(drawid)=blue '<--- replace with your color
    bufnamestr="S1Buffer"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
    indicolor(drawid)=red '<--- replace with your color
    bufnamestr="R1Buffer"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
    indicolor(drawid)=blue '<--- replace with your color
    bufnamestr="S2Buffer"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
    indicolor(drawid)=red '<--- replace with your color
    bufnamestr="R2Buffer"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
    indicolor(drawid)=green '<--- replace with your color
    bufnamestr="S3Buffer"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
    indicolor(drawid)=green '<--- replace with your color
    bufnamestr="R3Buffer"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
end if

end if
'------------------------- End Weekly Pivot cpp -------------------------------------------------
'------------------------- ZigZag -------------------------------------------------
indiid++
if indicatorslistsel.item(indiid)="x" then

if lbar=1 then
zigzag
end if

barsback=VAL(zigzagbarsbackedit.text) '<--- can also be something like VAL(myindibarsbackedit.text)

if ibar>=lastbar-barsback then
    indicolor(drawid)=purple '<--- replace with your color
    .Data_Indi.Cell(drawid,lbar)= STR$(zigzagbuffer(offset)) '<--- replace myindibuffer with your indicator buffer name
    drawid=drawid+2
end if

end if
'------------------------- End ZigZag -------------------------------------------------
'------------------------- ZigZag cpp -------------------------------------------------
indiid++
if indicatorslistsel.item(indiid)="x" then

if lbar=1 then
barsbackstr=zigzagcppbarsbackedit.text
defstr extdepthstr=zzcppextdepthedit.text
cpptmpfuncreturn=varptr$(zigzagcpp(varptr(barsbackstr),varptr(extdepthstr)))
end if

barsback=val(zigzagcppbarsbackedit.text) '<--- can also be something like VAL(zigzagcppbarsbackedit.text)

if ibar>=lastbar-barsback then
    indicolor(drawid)=purple '<--- replace with your color
    bufnamestr="zigzagbuffer"
    .Data_Indi.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
end if

end if
'------------------------- End ZigZag cpp -------------------------------------------------
'-================================= End indicators area ========================================-
END IF

IF l = 1 THEN
    valmin = VAL(Grid.Cell(rowgridoffset + 5 , i))
    valmax = VAL(Grid.Cell(rowgridoffset + 4 , i))
END IF

IF VAL(Grid.Cell(rowgridoffset + 5 , i)) < valmin THEN
    valmin = VAL(Grid.Cell(rowgridoffset + 5 , i))
END IF

IF VAL(Grid.Cell(rowgridoffset + 4 , i)) > valmax THEN
    valmax = VAL(Grid.Cell(rowgridoffset + 4 , i))
END IF


'-==================================== Separate indicators area ==============================-


IF scrollmode = 0 THEN
    IF useindi.Checked = 1 THEN

        FOR lo = 1 TO canvas.separateindicator1.RowCount STEP 2
            canvas.separateindicator1.Cell(lo , l) = STR$(l) 'Legend in Row 0 of Each Col
        NEXT lo
        FOR lo = 2 TO canvas.separateindicator1.RowCount STEP 2
            canvas.separateindicator1.Cell(lo , l) = STR$(0)
        NEXT lo
        
        defint histoincr
        for histoincr=0 to 100
        drawhisto(histoincr)=0
        next histoincr
        
    END IF

    drawid = 2        

    canvasid ++
    
    

'------------------------- Accelerator -------------------------------------------------
indiid++
if indicatorslistsel.item(indiid)="x" then

if lbar=1 then
Accelerator
end if

barsback=200 '<--- can also be something like VAL(myindibarsbackedit.text)

if ibar>=lastbar-barsback then
    sepindicolor(drawid)=lightblue '<--- replace with your color
    canvas.separateindicator1.Cell(drawid,lbar)= STR$(acceleratorbuffer0(offset)) '<--- replace myindibuffer with your indicator buffer name
    drawid=drawid+2
end if

end if
'------------------------- End Accelerator -------------------------------------------------
'------------------------- astro_retrograde -------------------------------------------------
indiid++
if indicatorslistsel.item(indiid)="x" then

if lbar=1 then
astro_retrograde
end if

barsback=200 '<--- can also be something like VAL(astro_retrogradebarsbackedit.text)

if ibar>=lastbar-barsback then

drawhisto(drawid)=1
sepindicolorhisto(drawid,lbar)=white
if astro_retrograde_mercurybuffer(offset)=1 then sepindicolorhisto(drawid,lbar)=orange
    canvas.separateindicator1.Cell(drawid,lbar)= "0"
    drawid=drawid+2

drawhisto(drawid)=1
sepindicolorhisto(drawid,lbar)=white
if astro_retrograde_venusbuffer(offset)=1 then sepindicolorhisto(drawid,lbar)=pink
    canvas.separateindicator1.Cell(drawid,lbar)= "10"
    drawid=drawid+2

drawhisto(drawid)=1
sepindicolorhisto(drawid,lbar)=white
if astro_retrograde_earthbuffer(offset)=1 then sepindicolorhisto(drawid,lbar)=blue
    canvas.separateindicator1.Cell(drawid,lbar)= "20"
    drawid=drawid+2

drawhisto(drawid)=1
sepindicolorhisto(drawid,lbar)=white
if astro_retrograde_marsbuffer(offset)=1 then sepindicolorhisto(drawid,lbar)=red
    canvas.separateindicator1.Cell(drawid,lbar)= "30"
    drawid=drawid+2

drawhisto(drawid)=1
sepindicolorhisto(drawid,lbar)=white
if astro_retrograde_jupiterbuffer(offset)=1 then sepindicolorhisto(drawid,lbar)=olive
    canvas.separateindicator1.Cell(drawid,lbar)= "40"
    drawid=drawid+2

drawhisto(drawid)=1
sepindicolorhisto(drawid,lbar)=white
if astro_retrograde_saturnbuffer(offset)=1 then sepindicolorhisto(drawid,lbar)=gray
    canvas.separateindicator1.Cell(drawid,lbar)= "50"
    drawid=drawid+2

drawhisto(drawid)=1
sepindicolorhisto(drawid,lbar)=white
if astro_retrograde_uranusbuffer(offset)=1 then sepindicolorhisto(drawid,lbar)=lightblue
    canvas.separateindicator1.Cell(drawid,lbar)= "60"
    drawid=drawid+2

drawhisto(drawid)=1
sepindicolorhisto(drawid,lbar)=white
if astro_retrograde_neptunebuffer(offset)=1 then sepindicolorhisto(drawid,lbar)=purple
    canvas.separateindicator1.Cell(drawid,lbar)= "70"
    drawid=drawid+2

drawhisto(drawid)=1
sepindicolorhisto(drawid,lbar)=white
if astro_retrograde_plutobuffer(offset)=1 then sepindicolorhisto(drawid,lbar)=black
    canvas.separateindicator1.Cell(drawid,lbar)= "80"
    drawid=drawid+2

end if

end if
'------------------------- End astro_retrograde -------------------------------------------------
'------------------------- Average True Range -------------------------------------------------
indiid++
         
                    if indicatorslistsel.item(indiid)="x" then 
            
                        if lbar=1 then           
                            atr(1)
                        end if

                         barsback=VAL(atrbarsbackedit.text)
                        
                    if ibar>=lastbar-barsback then
                        sepindicolor(drawid)=lightblue
                        canvas.separateindicator1.Cell(drawid,lbar)= STR$(atrbuffer(offset))
            		drawid=drawid+2
                    end if                      
                     
                end if                                  

        '------------------------- End Average True Range -------------------------------------------------
'------------------------- Candle Average -------------------------------------------------
indiid++
if indicatorslistsel.item(indiid)="x" then

if lbar=1 then
CandleAvg
end if

barsback=200 '<--- can also be something like VAL(myindibarsbackedit.text)

if ibar>=lastbar-barsback then
    sepindicolor(drawid)=lightblue '<--- replace with your color
    canvas.separateindicator1.Cell(drawid,lbar)= STR$(candleavgbuffer(offset)) '<--- replace myindibuffer with your indicator buffer name
    drawid=drawid+2
end if

end if
'------------------------- End Candle Average -------------------------------------------------
'------------------------- declination_system -------------------------------------------------
indiid++
if indicatorslistsel.item(indiid)="x" then

if lbar=1 then
declination_system
end if

barsback=300 '<--- can also be something like VAL(declination_systembarsbackedit.text)

if ibar>=lastbar-barsback then
    sepindicolor(drawid)=blue '<--- replace with your color
    canvas.separateindicator1.Cell(drawid,lbar)= STR$(declination_systembuffer(offset))
    drawid=drawid+2
end if

end if
'------------------------- End declination_system -------------------------------------------------
'------------------------- Ehlers fisher transform -------------------------------------------------
indiid++
if indicatorslistsel.item(indiid)="x" then

if lbar=1 then
periodstr=Ehlersfishertransformperiodedit.text
curtfstr=Ehlersfishertransformcurtfedit.text
cpptmpfuncreturn=varptr$(Ehlersfishertransform(varptr(periodstr),varptr(curtfstr)))
end if

barsback=200 '<--- can also be something like VAL(Ehlersfishertransformbarsbackedit.text)

if ibar>=lastbar-barsback then
    sepindicolor(drawid)=gray '<--- replace with your color
    bufnamestr="Ehlersfishertransformbuffer1"
    canvas.separateindicator1.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
sepindicolor(drawid)=mediumseagreen '<--- replace with your color
    bufnamestr="eftbandsmovingbuffer"
    canvas.separateindicator1.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
sepindicolor(drawid)=mediumseagreen '<--- replace with your color
    bufnamestr="eftbandsupperbuffer"
    canvas.separateindicator1.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
sepindicolor(drawid)=mediumseagreen '<--- replace with your color
    bufnamestr="eftbandslowerbuffer"
    canvas.separateindicator1.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
end if

end if
'------------------------- End Ehlers fisher transform -------------------------------------------------
'------------------------- fftspectro -------------------------------------------------
indiid++
if indicatorslistsel.item(indiid)="x" then

if lbar=1 then
fftspectro
end if

barsback=300 '<--- can also be something like VAL(fftspectrobarsbackedit.text)

if ibar>=lastbar-barsback then
    sepindicolor(drawid)=blue '<--- replace with your color
    canvas.separateindicator1.Cell(drawid,lbar)= STR$(fftspectrobuffer(1,offset))
    drawid=drawid+2

sepindicolor(drawid)=lightblue '<--- replace with your color
    canvas.separateindicator1.Cell(drawid,lbar)= STR$(fftspectrobuffer(2,offset))
    drawid=drawid+2

sepindicolor(drawid)=olive '<--- replace with your color
    canvas.separateindicator1.Cell(drawid,lbar)= STR$(fftspectrobuffer(3,offset))
    drawid=drawid+2

sepindicolor(drawid)=pink '<--- replace with your color
    canvas.separateindicator1.Cell(drawid,lbar)= STR$(fftspectrobuffer(4,offset))
    drawid=drawid+2

sepindicolor(drawid)=red '<--- replace with your color
    canvas.separateindicator1.Cell(drawid,lbar)= STR$(fftspectrobuffer(5,offset))
    drawid=drawid+2

sepindicolor(drawid)=yellow '<--- replace with your color
    canvas.separateindicator1.Cell(drawid,lbar)= STR$(fftspectrobuffer(6,offset))
    drawid=drawid+2

sepindicolor(drawid)=lightblue '<--- replace with your color
    canvas.separateindicator1.Cell(drawid,lbar)= STR$(fftspectrobuffer(7,offset))
    drawid=drawid+2

sepindicolor(drawid)=purple '<--- replace with your color
    canvas.separateindicator1.Cell(drawid,lbar)= STR$(fftspectrobuffer(8,offset))
    drawid=drawid+2

sepindicolor(drawid)=black '<--- replace with your color
    canvas.separateindicator1.Cell(drawid,lbar)= STR$(fftspectrobuffer(9,offset))
    drawid=drawid+2

end if

end if
'------------------------- End fftspectro -------------------------------------------------
'------------------------- Force Index -------------------------------------------------
indiid++
if indicatorslistsel.item(indiid)="x" then

if lbar=1 then
ForceIndex
end if

barsback=200 '<--- can also be something like VAL(myindibarsbackedit.text)

if ibar>=lastbar-barsback then
    sepindicolor(drawid)=lightblue '<--- replace with your color
    canvas.separateindicator1.Cell(drawid,lbar)= STR$(forceindexbuffer(offset)) '<--- replace myindibuffer with your indicator buffer name
    drawid=drawid+2
end if

end if
'------------------------- End Force Index -------------------------------------------------
'------------------------- Gauquelin_sector -------------------------------------------------
indiid++
if indicatorslistsel.item(indiid)="x" then

if lbar=1 then
Gauquelin_sector
end if

barsback=200 '<--- can also be something like VAL(Gauquelin_sectorbarsbackedit.text)

if ibar>=lastbar-barsback then

defdbl gauqrads

gauqrads=sin(deg2rad((Gauquelin_sector_mercurybuffer(offset)-1)*10))
'gauqrads=sin(deg2rad(360*(Gauquelin_sector_mercurybuffer(offset)-1)/11))
sepindicolor(drawid)=orange
canvas.separateindicator1.Cell(drawid,lbar)= str$(gauqrads)
'print str$(lbar)+" "+canvas.separateindicator1.Cell(drawid,lbar)
drawid=drawid+2

gauqrads=sin(deg2rad((Gauquelin_sector_venusbuffer(offset)-1)*10))
'gauqrads=sin(deg2rad(360*(Gauquelin_sector_venusbuffer(offset)-1)/11))
sepindicolor(drawid)=pink
canvas.separateindicator1.Cell(drawid,lbar)= str$(gauqrads)
'print str$(lbar)+" "+canvas.separateindicator1.Cell(drawid,lbar)
drawid=drawid+2

gauqrads=sin(deg2rad((Gauquelin_sector_earthbuffer(offset)-1)*10))
'gauqrads=sin(deg2rad(360*(Gauquelin_sector_earthbuffer(offset)-1)/11))
sepindicolor(drawid)=blue
canvas.separateindicator1.Cell(drawid,lbar)= str$(gauqrads)
'print str$(lbar)+" "+canvas.separateindicator1.Cell(drawid,lbar)
drawid=drawid+2

gauqrads=sin(deg2rad((Gauquelin_sector_marsbuffer(offset)-1)*10))
'gauqrads=sin(deg2rad(360*(Gauquelin_sector_marsbuffer(offset)-1)/11))
sepindicolor(drawid)=red
canvas.separateindicator1.Cell(drawid,lbar)= str$(gauqrads)
'print str$(lbar)+" "+canvas.separateindicator1.Cell(drawid,lbar)
drawid=drawid+2

gauqrads=sin(deg2rad((Gauquelin_sector_jupiterbuffer(offset)-1)*10))
'gauqrads=sin(deg2rad(360*(Gauquelin_sector_jupiterbuffer(offset)-1)/11))
sepindicolor(drawid)=olive
canvas.separateindicator1.Cell(drawid,lbar)= str$(gauqrads)
'print str$(lbar)+" "+canvas.separateindicator1.Cell(drawid,lbar)
drawid=drawid+2

gauqrads=sin(deg2rad((Gauquelin_sector_saturnbuffer(offset)-1)*10))
'gauqrads=sin(deg2rad(360*(Gauquelin_sector_saturnbuffer(offset)-1)/11))
sepindicolor(drawid)=gray
canvas.separateindicator1.Cell(drawid,lbar)= str$(gauqrads)
'print str$(lbar)+" "+canvas.separateindicator1.Cell(drawid,lbar)
drawid=drawid+2

gauqrads=sin(deg2rad((Gauquelin_sector_uranusbuffer(offset)-1)*10))
'gauqrads=sin(deg2rad(360*(Gauquelin_sector_uranusbuffer(offset)-1)/11))
sepindicolor(drawid)=lightblue
canvas.separateindicator1.Cell(drawid,lbar)= str$(gauqrads)
'print str$(lbar)+" "+canvas.separateindicator1.Cell(drawid,lbar)
drawid=drawid+2

gauqrads=sin(deg2rad((Gauquelin_sector_neptunebuffer(offset)-1)*10))
'gauqrads=sin(deg2rad(360*(Gauquelin_sector_neptunebuffer(offset)-1)/11))
sepindicolor(drawid)=purple
canvas.separateindicator1.Cell(drawid,lbar)= str$(gauqrads)
'print str$(lbar)+" "+canvas.separateindicator1.Cell(drawid,lbar)
drawid=drawid+2

gauqrads=sin(deg2rad((Gauquelin_sector_plutobuffer(offset)-1)*10))
'gauqrads=sin(deg2rad(360*(Gauquelin_sector_plutobuffer(offset)-1)/11))
sepindicolor(drawid)=black
canvas.separateindicator1.Cell(drawid,lbar)= str$(gauqrads)
'print str$(lbar)+" "+canvas.separateindicator1.Cell(drawid,lbar)
drawid=drawid+2

end if

end if
'------------------------- End Gauquelin_sector -------------------------------------------------
'------------------------- IVolume -------------------------------------------------
indiid++
if indicatorslistsel.item(indiid)="x" then

if lbar=1 then
IVolume
end if

barsback=200 '<--- can also be something like VAL(myindibarsbackedit.text)

if ibar>=lastbar-barsback then
    sepindicolor(drawid)=lightblue '<--- replace with your color
    canvas.separateindicator1.Cell(drawid,lbar)= STR$(volumebuffer(offset)) '<--- replace myindibuffer with your indicator buffer name
    drawid=drawid+2
end if

end if
'------------------------- End IVolume -------------------------------------------------
'------------------------- LSS Oscillator -------------------------------------------------
indiid++
if indicatorslistsel.item(indiid)="x" then

if lbar=1 then
LSS
end if

barsback=200 '<--- can also be something like VAL(LSSbarsbackedit.text)

if ibar>=lastbar-barsback then
    sepindicolor(drawid)=lightblue '<--- replace with your color
    canvas.separateindicator1.Cell(drawid,lbar)= STR$(LSSbuffer(offset))
    drawid=drawid+2
    sepindicolor(drawid)=gray '<--- replace with your color
    canvas.separateindicator1.Cell(drawid,lbar)= STR$(LSSbufferlevel1(offset))
    drawid=drawid+2
    sepindicolor(drawid)=gray '<--- replace with your color
    canvas.separateindicator1.Cell(drawid,lbar)= STR$(LSSbufferlevel2(offset))
    drawid=drawid+2
    sepindicolor(drawid)=gray '<--- replace with your color
    canvas.separateindicator1.Cell(drawid,lbar)= STR$(LSSbufferlevel3(offset))
    drawid=drawid+2
end if

end if
'------------------------- End LSS Oscillator -------------------------------------------------
'------------------------- Money Flow Index -------------------------------------------------
indiid++
         
                     if indicatorslistsel.item(indiid)="x" then 
            
                        if lbar=1 then           
                            mfi
                        end if

                         barsback=VAL(mfibarsbackedit.text)                        

                        if ibar>=lastbar-barsback then
                            sepindicolor(drawid)=lightblue
				canvas.separateindicator1.Cell(drawid,lbar)= STR$(extmfibuffer(offset))
				drawid=drawid+2
                            sepindicolor(drawid)=gray
				canvas.separateindicator1.Cell(drawid,lbar)= STR$(mfilevelup(offset))
				drawid=drawid+2
                            sepindicolor(drawid)=gray                                                        
                            canvas.separateindicator1.Cell(drawid,lbar)= STR$(mfileveldn(offset))
				drawid=drawid+2
                
                        end if  
                        if autoadjustsepindi.checked=1 then 
                            sepindivalminedit.text="-20"             
                            sepindivalmaxedit.text="20"        
                        end if           
                     
                    end if                                  

        '------------------------- End Money Flow Index -------------------------------------------------
'------------------------- planets_scale -------------------------------------------------
indiid++
if indicatorslistsel.item(indiid)="x" then

if lbar=1 then
planets_scale
end if

barsback=300 '<--- can also be something like VAL(planets_scalebarsbackedit.text)

if ibar>=lastbar-barsback then

defint incrplanet
for incrplanet=0 to 10
    sepindicolor(drawid)=olive '<--- replace with your color
    canvas.separateindicator1.Cell(drawid,lbar)= STR$(planets_scalebuffer(incrplanet,offset))
    drawid=drawid+2
next incrplanet

sepindicolor(drawid)=red '<--- replace with your color
    canvas.separateindicator1.Cell(drawid,lbar)= STR$(price_scalebuffer(offset))
    drawid=drawid+2

sepindicolor(drawid)=blue '<--- replace with your color
    canvas.separateindicator1.Cell(drawid,lbar)= STR$(price_scalebuffer2(offset))
    drawid=drawid+2
end if

end if
'------------------------- End planets_scale -------------------------------------------------
'------------------------- Close Price -------------------------------------------------
indiid++
         
                     if indicatorslistsel.item(indiid)="x" then 
            
                        if lbar=1 then           
                            closepriceindi                        
                        end if

                         barsback=VAL(mabarsbackedit.text)                        

                        if ibar>=lastbar-barsback then
                            sepindicolor(drawid)=blue
                            canvas.separateindicator1.Cell(drawid,lbar)= STR$(closepricebuffer(offset))
				drawid=drawid+2
            
                        end if                      
                     
                    end if                                  

        '------------------------- End Close Price -------------------------------------------------
'------------------------- Relative Strength Index -------------------------------------------------
indiid++
         
                     if indicatorslistsel.item(indiid)="x" then 
            
                        if lbar=1 then           
                            rsi
                        end if

                         barsback=VAL(rsibarsbackedit.text)                        

                        if ibar>=lastbar-barsback then
                            sepindicolor(drawid)=lightblue
				canvas.separateindicator1.Cell(drawid,lbar)= STR$(rsibuffer(offset))
				drawid=drawid+2
                            sepindicolor(drawid)=gray
				canvas.separateindicator1.Cell(drawid,lbar)= STR$(rsilevelup(offset))
				drawid=drawid+2
                            sepindicolor(drawid)=gray                                                        
                            canvas.separateindicator1.Cell(drawid,lbar)= STR$(rsileveldn(offset))
				drawid=drawid+2
                
                        end if  
                        if autoadjustsepindi.checked=1 then 
                            sepindivalminedit.text="-20"             
                            sepindivalmaxedit.text="20"        
                        end if           
                     
                    end if                                  

        '------------------------- End Relative Strength Index -------------------------------------------------
'------------------------- smFisherTransform3nr -------------------------------------------------
indiid++
if indicatorslistsel.item(indiid)="x" then

if lbar=1 then
periodstr=smFisherTransform3nrperiodedit.text
curtfstr=smFisherTransform3nrcurtfedit.text
cpptmpfuncreturn=varptr$(smFisherTransform3nr(varptr(periodstr),varptr(curtfstr)))
end if

barsback=200 '<--- can also be something like VAL(smFisherTransform3nrbarsbackedit.text)

if ibar>=lastbar-barsback then
    sepindicolor(drawid)=lightblue '<--- replace with your color
    bufnamestr="ExtBuffer0"
    canvas.separateindicator1.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2    
end if

end if
'------------------------- End smFisherTransform3nr -------------------------------------------------
'------------------------- spectrometer -------------------------------------------------
indiid++
if indicatorslistsel.item(indiid)="x" then

if lbar=1 then
periodstr=spectrometerperiodedit.text
curtfstr=spectrometercurtfedit.text
cpptmpfuncreturn=varptr$(spectrometer(varptr(periodstr),varptr(curtfstr)))
end if

barsback=500 '<--- can also be something like VAL(spectrometerbarsbackedit.text)

if ibar>=lastbar-barsback then
    sepindicolor(drawid)=red '<--- replace with your color
    bufnamestr="spectrometerbuffer1"
    canvas.separateindicator1.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
'sepindicolor(drawid)=orange '<--- replace with your color
'    bufnamestr="spectrometerbuffer2"
'    canvas.separateindicator1.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
'    drawid=drawid+2
'sepindicolor(drawid)=yellow '<--- replace with your color
'    bufnamestr="spectrometerbuffer3"
'    canvas.separateindicator1.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
'    drawid=drawid+2
'sepindicolor(drawid)=green '<--- replace with your color
'    bufnamestr="spectrometerbuffer4"
'    canvas.separateindicator1.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
'    drawid=drawid+2
'sepindicolor(drawid)=blue '<--- replace with your color
'    bufnamestr="spectrometerbuffer5"
'    canvas.separateindicator1.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
'    drawid=drawid+2
'sepindicolor(drawid)=lightblue '<--- replace with your color
'    bufnamestr="spectrometerbuffer6"
'    canvas.separateindicator1.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
'    drawid=drawid+2
'sepindicolor(drawid)=purple '<--- replace with your color
'    bufnamestr="spectrometerbuffer7"
'    canvas.separateindicator1.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
'    drawid=drawid+2
'sepindicolor(drawid)=gray '<--- replace with your color
'    bufnamestr="spectrometerbuffer8"
'    canvas.separateindicator1.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
'    drawid=drawid+2
end if

end if
'------------------------- End spectrometer -------------------------------------------------
'------------------------- stepftvcprdl -------------------------------------------------
indiid++
if indicatorslistsel.item(indiid)="x" then

if lbar=1 then
periodstr=stepftvcprdlperiodedit.text
cpptmpfuncreturn=varptr$(stepftvcprdl(varptr(periodstr)))
end if

barsback=chartbars(displayedfile) '<--- can also be something like VAL(ftvcprdlbarsbackedit.text)

if ibar>=lastbar-barsback then
    sepindicolor(drawid)=orange '<--- replace with your color
    bufnamestr="Line1Buffer"
    canvas.separateindicator1.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
    sepindicolor(drawid)=lightblue '<--- replace with your color
    bufnamestr="Line2Buffer"
    canvas.separateindicator1.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
    sepindicolor(drawid)=red '<--- replace with your color
    bufnamestr="Line3Buffer"
    canvas.separateindicator1.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
    sepindicolor(drawid)=gray '<--- replace with your color
    bufnamestr="steplevelup"
    canvas.separateindicator1.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
    sepindicolor(drawid)=gray '<--- replace with your color
    bufnamestr="stepleveldn"
    canvas.separateindicator1.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
end if

end if
'------------------------- End stepftvcprdl -------------------------------------------------
'------------------------- StepRSI -------------------------------------------------
indiid++
if indicatorslistsel.item(indiid)="x" then

if lbar=1 then
steprsi
end if

barsback=200 '<--- can also be something like VAL(myindibarsbackedit.text)

if ibar>=lastbar-barsback then
    sepindicolor(drawid)=orange '<--- replace with your color
    canvas.separateindicator1.Cell(drawid,lbar)= STR$(line1buffer(offset)) '<--- replace myindibuffer with your indicator buffer name
    drawid=drawid+2
    sepindicolor(drawid)=lightblue '<--- replace with your color
    canvas.separateindicator1.Cell(drawid,lbar)= STR$(line2buffer(offset)) '<--- replace myindibuffer with your indicator buffer name
    drawid=drawid+2
    sepindicolor(drawid)=purple '<--- replace with your color
    canvas.separateindicator1.Cell(drawid,lbar)= STR$(line3buffer(offset)) '<--- replace myindibuffer with your indicator buffer name
    drawid=drawid+2
    sepindicolor(drawid)=gray '<--- replace with your color
    canvas.separateindicator1.Cell(drawid,lbar)= STR$(steprsilevelup(offset)) '<--- replace myindibuffer with your indicator buffer name
    drawid=drawid+2
    sepindicolor(drawid)=gray '<--- replace with your color
    canvas.separateindicator1.Cell(drawid,lbar)= STR$(steprsileveldn(offset)) '<--- replace myindibuffer with your indicator buffer name
    drawid=drawid+2	
end if

if autoadjustsepindi.checked=1 then 
	sepindivalminedit.text="-20"             
	sepindivalmaxedit.text="20"        
end if  

end if
'------------------------- End StepRSI -------------------------------------------------
'------------------------- threeD Oscilator -------------------------------------------------
indiid++
if indicatorslistsel.item(indiid)="x" then

if lbar=1 then
periodstr=threeD_Oscilatorperiodedit.text
curtfstr=threeD_Oscilatorcurtfedit.text
cpptmpfuncreturn=varptr$(threeD_Oscilator(varptr(periodstr),varptr(curtfstr)))
end if

barsback=200 '<--- can also be something like VAL(threeD_Oscilatorbarsbackedit.text)

if ibar>=lastbar-barsback then
    sepindicolor(drawid)=blue '<--- replace with your color
    bufnamestr="sig1n"
    canvas.separateindicator1.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
    sepindicolor(drawid)=red '<--- replace with your color
    bufnamestr="sig2n"
    canvas.separateindicator1.Cell(drawid,lbar)= varptr$(getbufferdata(varptr(bufnamestr),varptr(offsetstr)))
    drawid=drawid+2
end if

end if
'------------------------- End threeD Oscilator -------------------------------------------------
'------------------------- Value Chart -------------------------------------------------
indiid++
         
                    if indicatorslistsel.item(indiid)="x" then 
            
                        if lbar=1 then           
                            valuechart
                        end if

                         barsback=VAL(valuechartbarsbackedit.text)
                        
                    if ibar>=lastbar-barsback then
                        sepindicolor(drawid)=green
                        canvas.separateindicator1.Cell(drawid,lbar)= STR$(vo(offset))
			drawid=drawid+2
			sepindicolor(drawid)=red
                        canvas.separateindicator1.Cell(drawid,lbar)= STR$(vh(offset))
			drawid=drawid+2
			sepindicolor(drawid)=red
                        canvas.separateindicator1.Cell(drawid,lbar)= STR$(vb(offset))
			drawid=drawid+2
			sepindicolor(drawid)=purple
                        canvas.separateindicator1.Cell(drawid,lbar)= STR$(vc(offset))
			drawid=drawid+2
			sepindicolor(drawid)=gray
                        canvas.separateindicator1.Cell(drawid,lbar)= STR$(valuechartlevelup1(offset))
			drawid=drawid+2
			sepindicolor(drawid)=gray
                        canvas.separateindicator1.Cell(drawid,lbar)= STR$(valuechartlevelup2(offset))
			drawid=drawid+2
			sepindicolor(drawid)=gray
                        canvas.separateindicator1.Cell(drawid,lbar)= STR$(valuechartleveldn1(offset))
			drawid=drawid+2
			sepindicolor(drawid)=gray
                        canvas.separateindicator1.Cell(drawid,lbar)= STR$(valuechartleveldn2(offset))
			drawid=drawid+2
                                                                                                                                                                                  
                    end if
                    if autoadjustsepindi.checked=1 then     
                        sepindivalminedit.text="-4"             
                        sepindivalmaxedit.text="4"                             
                    end if
         
                end if                                  

        '------------------------- End Value Chart -------------------------------------------------
        '------------------------- Value Chart of ATR Channels -------------------------------------------------
indiid++
         
                    if indicatorslistsel.item(indiid)="x" then 
            
                        if lbar=1 then           
                            valuechartofatrchannels
                        end if

                         barsback=VAL(vcatrcbarsbackedit.text)                       

                    if ibar>=lastbar-barsback then
                        sepindicolor(drawid)=green
			canvas.separateindicator1.Cell(drawid,lbar)= STR$(vo3(offset))
			drawid=drawid+2
                        sepindicolor(drawid)=red
			canvas.separateindicator1.Cell(drawid,lbar)= STR$(vh3(offset))
			drawid=drawid+2
                        sepindicolor(drawid)=red
			canvas.separateindicator1.Cell(drawid,lbar)= STR$(vb3(offset))
			drawid=drawid+2
                        sepindicolor(drawid)=purple
			canvas.separateindicator1.Cell(drawid,lbar)= STR$(vc3(offset))
			drawid=drawid+2
                        sepindicolor(drawid)=gray
			canvas.separateindicator1.Cell(drawid,lbar)= STR$(valuechart3levelup1(offset))
			drawid=drawid+2
                        sepindicolor(drawid)=gray
			canvas.separateindicator1.Cell(drawid,lbar)= STR$(valuechart3levelup2(offset))
			drawid=drawid+2
                        sepindicolor(drawid)=gray
			canvas.separateindicator1.Cell(drawid,lbar)= STR$(valuechart3leveldn1(offset))
			drawid=drawid+2
                        sepindicolor(drawid)=gray
			canvas.separateindicator1.Cell(drawid,lbar)= STR$(valuechart3leveldn2(offset))
			drawid=drawid+2
                                                                                                                                                                                                            
                    end if
                    if autoadjustsepindi.checked=1 then        
                        sepindivalminedit.text="-4"             
                        sepindivalmaxedit.text="4"              
                    end if
                     
                end if                                  

        '------------------------- End Value Chart of ATR Channels  ------------------------------------------------- 
'-==================================== End Separate indicators area ==============================-

IF l = 1 THEN
    sepindivalmin = VAL(canvas.separateindicator1.Cell(2 , lbar))
    sepindivalmax = VAL(canvas.separateindicator1.Cell(2 , lbar))
END IF

IF VAL(canvas.separateindicator1.Cell(2 , lbar)) < sepindivalmin THEN
    sepindivalmin = VAL(canvas.separateindicator1.Cell(2 , lbar))
END IF

IF VAL(canvas.separateindicator1.Cell(2 , lbar)) > sepindivalmax THEN
    sepindivalmax = VAL(canvas.separateindicator1.Cell(2 , lbar))
END IF

END IF
NEXT i

IF scrollmode = 0 THEN
    sepindivalmin = sepindivalmin + VAL(sepindivalminedit.Text)
    sepindivalmax = sepindivalmax + VAL(sepindivalmaxedit.Text)

    barsdisplayed2 = VAL(barsdisplayed.Text)
    canvas.initializechart2
    canvas.drawchart2
END IF


.YAxis.Min = valmin
.YAxis.Max = valmax

.DrawChart(FALSE) 'Draw it!

END WITH
graph.buffer.Font.Name = Font.Name
graph.buffer.Font.Size = Font.Size
canvas.BMP.Font.Name = Font.Name
canvas.BMP.Font.Size = Font.Size
scrollmodeofftimer.Enabled = TRUE
frmmain.Caption = "QChartist"

WITH graph
    .firstbufcntreset
    .savebuffertmp
    .paintchart
END WITH

IF scrollmode = 0 THEN

    graphcursorpos2

    DIM drawi AS INTEGER
    defdbl mytimeratio
    defdbl mypriceratio
    
    DIM graphhratio1 AS DOUBLE  
    DIM graphhratio2 AS DOUBLE
    DIM graphvratio1 AS DOUBLE 
    DIM graphvratio2 AS DOUBLE 

    FOR drawi = 1 TO 100

        IF (VAL(trendlinesdb.Cell(3 , drawi)) >= graphserialdatebegin AND VAL(trendlinesdb.Cell(3 , drawi)) <= graphserialdateend) AND _
            (VAL(trendlinesdb.Cell(4 , drawi)) >= graphserialdatebegin AND VAL(trendlinesdb.Cell(4 , drawi)) <= graphserialdateend) AND_
            (VAL(trendlinesdb.Cell(1 , drawi)) >= pricechartpos(0,0) AND VAL(trendlinesdb.Cell(1 , drawi)) <= pricechartpos(1,0)) AND_
            (VAL(trendlinesdb.Cell(2 , drawi)) >= pricechartpos(0,0) AND VAL(trendlinesdb.Cell(2 , drawi)) <= pricechartpos(1,0)) THEN

            graph.bufcntreset
            graph.savebuffertmp
                       
            for i=0 to 1000
            if VAL(trendlinesdb.Cell(3 , drawi))>=timechartpos(i,0) and VAL(trendlinesdb.Cell(3 , drawi))<=timechartpos(i+1,0) then
            mytimeratio=(VAL(trendlinesdb.Cell(3 , drawi))-timechartpos(i,0))/(timechartpos(i+1,0)-timechartpos(i,0))
            defint drawtrendlinex1=timechartpos(i,1)+round((timechartpos(i+1,1)-timechartpos(i,1))*mytimeratio)
            exit for
            end if
            next i
            
            for i=0 to 1000
            if VAL(trendlinesdb.Cell(4 , drawi))>=timechartpos(i,0) and VAL(trendlinesdb.Cell(4 , drawi))<=timechartpos(i+1,0) then
            mytimeratio=(VAL(trendlinesdb.Cell(4 , drawi))-timechartpos(i,0))/(timechartpos(i+1,0)-timechartpos(i,0))
            defint drawtrendlinex2=timechartpos(i,1)+round((timechartpos(i+1,1)-timechartpos(i,1))*mytimeratio)
            exit for
            end if
            next i
            
            mypriceratio=(VAL(trendlinesdb.Cell(1 , drawi))-pricechartpos(0,0))/(pricechartpos(1,0)-pricechartpos(0,0))
            defint drawtrendliney1=pricechartpos(0,1)-round((pricechartpos(0,1)-pricechartpos(1,1))*mypriceratio)
            
            mypriceratio=(VAL(trendlinesdb.Cell(2 , drawi))-pricechartpos(0,0))/(pricechartpos(1,0)-pricechartpos(0,0))
            defint drawtrendliney2=pricechartpos(0,1)-round((pricechartpos(0,1)-pricechartpos(1,1))*mypriceratio)

            graph.drawp(0 , drawtrendlinex1 , drawtrendliney1 , drawtrendlinex2 , drawtrendliney2 , 0 , 0)

            graph.savebuffertmp
            graph.paintchart

        END IF

        IF (VAL(fibofandb.Cell(3 , drawi)) >= graphserialdatebegin AND VAL(fibofandb.Cell(3 , drawi)) <= graphserialdateend) AND _
            (VAL(fibofandb.Cell(4 , drawi)) >= graphserialdatebegin AND VAL(fibofandb.Cell(4 , drawi)) <= graphserialdateend) AND_
            (VAL(fibofandb.Cell(1 , drawi)) >= pricechartpos(0,0) AND VAL(fibofandb.Cell(1 , drawi)) <= pricechartpos(1,0)) AND_
            (VAL(fibofandb.Cell(2 , drawi)) >= pricechartpos(0,0) AND VAL(fibofandb.Cell(2 , drawi)) <= pricechartpos(1,0)) THEN

            graph.bufcntreset
            graph.savebuffertmp

            for i=0 to 1000
            if VAL(fibofandb.Cell(3 , drawi))>=timechartpos(i,0) and VAL(fibofandb.Cell(3 , drawi))<=timechartpos(i+1,0) then
            mytimeratio=(VAL(fibofandb.Cell(3 , drawi))-timechartpos(i,0))/(timechartpos(i+1,0)-timechartpos(i,0))
            defint drawfibofanx1=timechartpos(i,1)+round((timechartpos(i+1,1)-timechartpos(i,1))*mytimeratio)
            exit for
            end if
            next i
            
            for i=0 to 1000
            if VAL(fibofandb.Cell(4 , drawi))>=timechartpos(i,0) and VAL(fibofandb.Cell(4 , drawi))<=timechartpos(i+1,0) then
            mytimeratio=(VAL(fibofandb.Cell(4 , drawi))-timechartpos(i,0))/(timechartpos(i+1,0)-timechartpos(i,0))
            defint drawfibofanx2=timechartpos(i,1)+round((timechartpos(i+1,1)-timechartpos(i,1))*mytimeratio)
            exit for
            end if
            next i
            
            mypriceratio=(VAL(fibofandb.Cell(1 , drawi))-pricechartpos(0,0))/(pricechartpos(1,0)-pricechartpos(0,0))
            defint drawfibofany1=pricechartpos(0,1)-round((pricechartpos(0,1)-pricechartpos(1,1))*mypriceratio)
            
            mypriceratio=(VAL(fibofandb.Cell(2 , drawi))-pricechartpos(0,0))/(pricechartpos(1,0)-pricechartpos(0,0))
            defint drawfibofany2=pricechartpos(0,1)-round((pricechartpos(0,1)-pricechartpos(1,1))*mypriceratio)

            graph.drawp(1 , drawfibofanx1 , drawfibofany1 , drawfibofanx2 , drawfibofany2 , 0 , 0)

            graph.savebuffertmp
            graph.paintchart

        END IF

        IF (VAL(fiboretdb.Cell(3 , drawi)) >= graphserialdatebegin AND VAL(fiboretdb.Cell(3 , drawi)) <= graphserialdateend) AND _
            (VAL(fiboretdb.Cell(4 , drawi)) >= graphserialdatebegin AND VAL(fiboretdb.Cell(4 , drawi)) <= graphserialdateend) AND_
            (VAL(fiboretdb.Cell(1 , drawi)) >= pricechartpos(0,0) AND VAL(fiboretdb.Cell(1 , drawi)) <= pricechartpos(1,0)) AND_
            (VAL(fiboretdb.Cell(2 , drawi)) >= pricechartpos(0,0) AND VAL(fiboretdb.Cell(2 , drawi)) <= pricechartpos(1,0)) THEN

            graph.bufcntreset
            graph.savebuffertmp

            for i=0 to 1000
            if VAL(fiboretdb.Cell(3 , drawi))>=timechartpos(i,0) and VAL(fiboretdb.Cell(3 , drawi))<=timechartpos(i+1,0) then
            mytimeratio=(VAL(fiboretdb.Cell(3 , drawi))-timechartpos(i,0))/(timechartpos(i+1,0)-timechartpos(i,0))
            defint drawfiboretx1=timechartpos(i,1)+round((timechartpos(i+1,1)-timechartpos(i,1))*mytimeratio)
            exit for
            end if
            next i
            
            for i=0 to 1000
            if VAL(fiboretdb.Cell(4 , drawi))>=timechartpos(i,0) and VAL(fiboretdb.Cell(4 , drawi))<=timechartpos(i+1,0) then
            mytimeratio=(VAL(fiboretdb.Cell(4 , drawi))-timechartpos(i,0))/(timechartpos(i+1,0)-timechartpos(i,0))
            defint drawfiboretx2=timechartpos(i,1)+round((timechartpos(i+1,1)-timechartpos(i,1))*mytimeratio)
            exit for
            end if
            next i
            
            mypriceratio=(VAL(fiboretdb.Cell(1 , drawi))-pricechartpos(0,0))/(pricechartpos(1,0)-pricechartpos(0,0))
            defint drawfiborety1=pricechartpos(0,1)-round((pricechartpos(0,1)-pricechartpos(1,1))*mypriceratio)
            
            mypriceratio=(VAL(fiboretdb.Cell(2 , drawi))-pricechartpos(0,0))/(pricechartpos(1,0)-pricechartpos(0,0))
            defint drawfiborety2=pricechartpos(0,1)-round((pricechartpos(0,1)-pricechartpos(1,1))*mypriceratio)

            graph.drawp(2 , drawfiboretx1 , drawfiborety1 , drawfiboretx2 , drawfiborety2 , 0 , 0)

            graph.savebuffertmp
            graph.paintchart

        END IF

        IF (VAL(paradb.Cell(4 , drawi)) >= graphserialdatebegin AND VAL(paradb.Cell(4 , drawi)) <= graphserialdateend) AND _
            (VAL(paradb.Cell(5 , drawi)) >= graphserialdatebegin AND VAL(paradb.Cell(5 , drawi)) <= graphserialdateend) AND_
            (VAL(paradb.Cell(1 , drawi)) >= pricechartpos(0,0) AND VAL(paradb.Cell(1 , drawi)) <= pricechartpos(1,0)) AND_
            (VAL(paradb.Cell(2 , drawi)) >= pricechartpos(0,0) AND VAL(paradb.Cell(2 , drawi)) <= pricechartpos(1,0)) THEN

            graph.bufcntreset
            graph.savebuffertmp

            for i=0 to 1000
            if VAL(paradb.Cell(4 , drawi))>=timechartpos(i,0) and VAL(paradb.Cell(4 , drawi))<=timechartpos(i+1,0) then
            mytimeratio=(VAL(paradb.Cell(4 , drawi))-timechartpos(i,0))/(timechartpos(i+1,0)-timechartpos(i,0))
            defint drawparax1=timechartpos(i,1)+round((timechartpos(i+1,1)-timechartpos(i,1))*mytimeratio)
            exit for
            end if
            next i
            
            for i=0 to 1000
            if VAL(paradb.Cell(5 , drawi))>=timechartpos(i,0) and VAL(paradb.Cell(5 , drawi))<=timechartpos(i+1,0) then
            mytimeratio=(VAL(paradb.Cell(5 , drawi))-timechartpos(i,0))/(timechartpos(i+1,0)-timechartpos(i,0))
            defint drawparax2=timechartpos(i,1)+round((timechartpos(i+1,1)-timechartpos(i,1))*mytimeratio)
            exit for
            end if
            next i
            
            for i=0 to 1000
            if VAL(paradb.Cell(6 , drawi))>=timechartpos(i,0) and VAL(paradb.Cell(6 , drawi))<=timechartpos(i+1,0) then
            mytimeratio=(VAL(paradb.Cell(6 , drawi))-timechartpos(i,0))/(timechartpos(i+1,0)-timechartpos(i,0))
            defint drawparax3=timechartpos(i,1)+round((timechartpos(i+1,1)-timechartpos(i,1))*mytimeratio)
            exit for
            end if
            next i
            
            mypriceratio=(VAL(paradb.Cell(1 , drawi))-pricechartpos(0,0))/(pricechartpos(1,0)-pricechartpos(0,0))
            defint drawparay1=pricechartpos(0,1)-round((pricechartpos(0,1)-pricechartpos(1,1))*mypriceratio)
            
            mypriceratio=(VAL(paradb.Cell(2 , drawi))-pricechartpos(0,0))/(pricechartpos(1,0)-pricechartpos(0,0))
            defint drawparay2=pricechartpos(0,1)-round((pricechartpos(0,1)-pricechartpos(1,1))*mypriceratio)
            
            mypriceratio=(VAL(paradb.Cell(3 , drawi))-pricechartpos(0,0))/(pricechartpos(1,0)-pricechartpos(0,0))
            defint drawparay3=pricechartpos(0,1)-round((pricechartpos(0,1)-pricechartpos(1,1))*mypriceratio)

            graph.drawp(0 , drawparax1 , drawparay1 , drawparax2 , drawparay2 , 0 , 0)
            Graph.savebuffertmpsimplez
            graph.drawp(3 , drawparax1 , drawparay1 , drawparax3 , drawparay3 , drawparax2 , drawparay2)

            graph.savebuffertmp
            graph.paintchart

        END IF

        IF (VAL(hlinedb.Cell(3 , drawi)) >= graphserialdatebegin AND VAL(hlinedb.Cell(3 , drawi)) <= graphserialdateend) AND _
            (VAL(hlinedb.Cell(4 , drawi)) >= graphserialdatebegin AND VAL(hlinedb.Cell(4 , drawi)) <= graphserialdateend) AND_
            (VAL(hlinedb.Cell(1 , drawi)) >= pricechartpos(0,0) AND VAL(hlinedb.Cell(1 , drawi)) <= pricechartpos(1,0)) AND_
            (VAL(hlinedb.Cell(2 , drawi)) >= pricechartpos(0,0) AND VAL(hlinedb.Cell(2 , drawi)) <= pricechartpos(1,0)) THEN

            graph.bufcntreset
            graph.savebuffertmp

            for i=0 to 1000
            if VAL(hlinedb.Cell(3 , drawi))>=timechartpos(i,0) and VAL(hlinedb.Cell(3 , drawi))<=timechartpos(i+1,0) then
            mytimeratio=(VAL(hlinedb.Cell(3 , drawi))-timechartpos(i,0))/(timechartpos(i+1,0)-timechartpos(i,0))
            defint drawhlinex1=timechartpos(i,1)+round((timechartpos(i+1,1)-timechartpos(i,1))*mytimeratio)
            exit for
            end if
            next i
            
            for i=0 to 1000
            if VAL(hlinedb.Cell(4 , drawi))>=timechartpos(i,0) and VAL(hlinedb.Cell(4 , drawi))<=timechartpos(i+1,0) then
            mytimeratio=(VAL(hlinedb.Cell(4 , drawi))-timechartpos(i,0))/(timechartpos(i+1,0)-timechartpos(i,0))
            defint drawhlinex2=timechartpos(i,1)+round((timechartpos(i+1,1)-timechartpos(i,1))*mytimeratio)
            exit for
            end if
            next i
            
            mypriceratio=(VAL(hlinedb.Cell(1 , drawi))-pricechartpos(0,0))/(pricechartpos(1,0)-pricechartpos(0,0))
            defint drawhliney1=pricechartpos(0,1)-round((pricechartpos(0,1)-pricechartpos(1,1))*mypriceratio)
            
            mypriceratio=(VAL(hlinedb.Cell(2 , drawi))-pricechartpos(0,0))/(pricechartpos(1,0)-pricechartpos(0,0))
            defint drawhliney2=pricechartpos(0,1)-round((pricechartpos(0,1)-pricechartpos(1,1))*mypriceratio)

            graph.drawp(4 , drawhlinex1 , drawhliney1 , drawhlinex2 , drawhliney2 , 0 , 0)

            graph.savebuffertmp
            graph.paintchart

        END IF

        IF (VAL(vlinedb.Cell(3 , drawi)) >= graphserialdatebegin AND VAL(vlinedb.Cell(3 , drawi)) <= graphserialdateend) AND _
            (VAL(vlinedb.Cell(4 , drawi)) >= graphserialdatebegin AND VAL(vlinedb.Cell(4 , drawi)) <= graphserialdateend) AND_
            (VAL(vlinedb.Cell(1 , drawi)) >= pricechartpos(0,0) AND VAL(vlinedb.Cell(1 , drawi)) <= pricechartpos(1,0)) AND_
            (VAL(vlinedb.Cell(2 , drawi)) >= pricechartpos(0,0) AND VAL(vlinedb.Cell(2 , drawi)) <= pricechartpos(1,0)) THEN

            graph.bufcntreset
            graph.savebuffertmp

            for i=0 to 1000
            if VAL(vlinedb.Cell(3 , drawi))>=timechartpos(i,0) and VAL(vlinedb.Cell(3 , drawi))<=timechartpos(i+1,0) then
            mytimeratio=(VAL(vlinedb.Cell(3 , drawi))-timechartpos(i,0))/(timechartpos(i+1,0)-timechartpos(i,0))
            defint drawvlinex1=timechartpos(i,1)+round((timechartpos(i+1,1)-timechartpos(i,1))*mytimeratio)
            exit for
            end if
            next i
            
            for i=0 to 1000
            if VAL(vlinedb.Cell(4 , drawi))>=timechartpos(i,0) and VAL(vlinedb.Cell(4 , drawi))<=timechartpos(i+1,0) then
            mytimeratio=(VAL(vlinedb.Cell(4 , drawi))-timechartpos(i,0))/(timechartpos(i+1,0)-timechartpos(i,0))
            defint drawvlinex2=timechartpos(i,1)+round((timechartpos(i+1,1)-timechartpos(i,1))*mytimeratio)
            exit for
            end if
            next i
            
            mypriceratio=(VAL(vlinedb.Cell(1 , drawi))-pricechartpos(0,0))/(pricechartpos(1,0)-pricechartpos(0,0))
            defint drawvliney1=pricechartpos(0,1)-round((pricechartpos(0,1)-pricechartpos(1,1))*mypriceratio)
            
            mypriceratio=(VAL(vlinedb.Cell(2 , drawi))-pricechartpos(0,0))/(pricechartpos(1,0)-pricechartpos(0,0))
            defint drawvliney2=pricechartpos(0,1)-round((pricechartpos(0,1)-pricechartpos(1,1))*mypriceratio)

            graph.drawp(5 , drawvlinex1 , drawvliney1 , drawvlinex2 , drawvliney2 , 0 , 0)

            graph.savebuffertmp
            graph.paintchart

        END IF

        IF (VAL(sqrdb.Cell(3 , drawi)) >= graphserialdatebegin AND VAL(sqrdb.Cell(3 , drawi)) <= graphserialdateend) AND _
            (VAL(sqrdb.Cell(4 , drawi)) >= graphserialdatebegin AND VAL(sqrdb.Cell(4 , drawi)) <= graphserialdateend) AND_
            (VAL(sqrdb.Cell(1 , drawi)) >= pricechartpos(0,0) AND VAL(sqrdb.Cell(1 , drawi)) <= pricechartpos(1,0)) AND_
            (VAL(sqrdb.Cell(2 , drawi)) >= pricechartpos(0,0) AND VAL(sqrdb.Cell(2 , drawi)) <= pricechartpos(1,0)) THEN

            graph.bufcntreset
            graph.savebuffertmp

            for i=0 to 1000
            if VAL(sqrdb.Cell(3 , drawi))>=timechartpos(i,0) and VAL(sqrdb.Cell(3 , drawi))<=timechartpos(i+1,0) then
            mytimeratio=(VAL(sqrdb.Cell(3 , drawi))-timechartpos(i,0))/(timechartpos(i+1,0)-timechartpos(i,0))
            defint drawsqrx1=timechartpos(i,1)+round((timechartpos(i+1,1)-timechartpos(i,1))*mytimeratio)
            exit for
            end if
            next i
            
            for i=0 to 1000
            if VAL(sqrdb.Cell(4 , drawi))>=timechartpos(i,0) and VAL(sqrdb.Cell(4 , drawi))<=timechartpos(i+1,0) then
            mytimeratio=(VAL(sqrdb.Cell(4 , drawi))-timechartpos(i,0))/(timechartpos(i+1,0)-timechartpos(i,0))
            defint drawsqrx2=timechartpos(i,1)+round((timechartpos(i+1,1)-timechartpos(i,1))*mytimeratio)
            exit for
            end if
            next i
            
            mypriceratio=(VAL(sqrdb.Cell(1 , drawi))-pricechartpos(0,0))/(pricechartpos(1,0)-pricechartpos(0,0))
            defint drawsqry1=pricechartpos(0,1)-round((pricechartpos(0,1)-pricechartpos(1,1))*mypriceratio)
            
            mypriceratio=(VAL(sqrdb.Cell(2 , drawi))-pricechartpos(0,0))/(pricechartpos(1,0)-pricechartpos(0,0))
            defint drawsqry2=pricechartpos(0,1)-round((pricechartpos(0,1)-pricechartpos(1,1))*mypriceratio)

            graph.drawp(6 , drawsqrx1 , drawsqry1 , drawsqrx2 , drawsqry2 , 0 , 0)

            graph.savebuffertmp
            graph.paintchart

        END IF

        IF (VAL(tridb.Cell(3 , drawi)) >= graphserialdatebegin AND VAL(tridb.Cell(3 , drawi)) <= graphserialdateend) AND _
            (VAL(tridb.Cell(4 , drawi)) >= graphserialdatebegin AND VAL(tridb.Cell(4 , drawi)) <= graphserialdateend) AND_
            (VAL(tridb.Cell(1 , drawi)) >= pricechartpos(0,0) AND VAL(tridb.Cell(1 , drawi)) <= pricechartpos(1,0)) AND_
            (VAL(tridb.Cell(2 , drawi)) >= pricechartpos(0,0) AND VAL(tridb.Cell(2 , drawi)) <= pricechartpos(1,0)) THEN

            graph.bufcntreset
            graph.savebuffertmp

            for i=0 to 1000
            if VAL(tridb.Cell(3 , drawi))>=timechartpos(i,0) and VAL(tridb.Cell(3 , drawi))<=timechartpos(i+1,0) then
            mytimeratio=(VAL(tridb.Cell(3 , drawi))-timechartpos(i,0))/(timechartpos(i+1,0)-timechartpos(i,0))
            defint drawtrix1=timechartpos(i,1)+round((timechartpos(i+1,1)-timechartpos(i,1))*mytimeratio)
            exit for
            end if
            next i
            
            for i=0 to 1000
            if VAL(tridb.Cell(4 , drawi))>=timechartpos(i,0) and VAL(tridb.Cell(4 , drawi))<=timechartpos(i+1,0) then
            mytimeratio=(VAL(tridb.Cell(4 , drawi))-timechartpos(i,0))/(timechartpos(i+1,0)-timechartpos(i,0))
            defint drawtrix2=timechartpos(i,1)+round((timechartpos(i+1,1)-timechartpos(i,1))*mytimeratio)
            exit for
            end if
            next i
            
            mypriceratio=(VAL(tridb.Cell(1 , drawi))-pricechartpos(0,0))/(pricechartpos(1,0)-pricechartpos(0,0))
            defint drawtriy1=pricechartpos(0,1)-round((pricechartpos(0,1)-pricechartpos(1,1))*mypriceratio)
            
            mypriceratio=(VAL(tridb.Cell(2 , drawi))-pricechartpos(0,0))/(pricechartpos(1,0)-pricechartpos(0,0))
            defint drawtriy2=pricechartpos(0,1)-round((pricechartpos(0,1)-pricechartpos(1,1))*mypriceratio)

            graph.drawp(7 , drawtrix1 , drawtriy1 , drawtrix2 , drawtriy2 , 0 , 0)

            graph.savebuffertmp
            graph.paintchart

        END IF

        IF (VAL(circledb.Cell(3 , drawi)) >= graphserialdatebegin AND VAL(circledb.Cell(3 , drawi)) <= graphserialdateend) AND _
            (VAL(circledb.Cell(4 , drawi)) >= graphserialdatebegin AND VAL(circledb.Cell(4 , drawi)) <= graphserialdateend) AND_
            (VAL(circledb.Cell(1 , drawi)) >= pricechartpos(0,0) AND VAL(circledb.Cell(1 , drawi)) <= pricechartpos(1,0)) AND_
            (VAL(circledb.Cell(2 , drawi)) >= pricechartpos(0,0) AND VAL(circledb.Cell(2 , drawi)) <= pricechartpos(1,0)) THEN

            graph.bufcntreset
            graph.savebuffertmp

            for i=0 to 1000
            if VAL(circledb.Cell(3 , drawi))>=timechartpos(i,0) and VAL(circledb.Cell(3 , drawi))<=timechartpos(i+1,0) then
            mytimeratio=(VAL(circledb.Cell(3 , drawi))-timechartpos(i,0))/(timechartpos(i+1,0)-timechartpos(i,0))
            defint drawcirclex1=timechartpos(i,1)+round((timechartpos(i+1,1)-timechartpos(i,1))*mytimeratio)
            exit for
            end if
            next i
            
            for i=0 to 1000
            if VAL(circledb.Cell(4 , drawi))>=timechartpos(i,0) and VAL(circledb.Cell(4 , drawi))<=timechartpos(i+1,0) then
            mytimeratio=(VAL(circledb.Cell(4 , drawi))-timechartpos(i,0))/(timechartpos(i+1,0)-timechartpos(i,0))
            defint drawcirclex2=timechartpos(i,1)+round((timechartpos(i+1,1)-timechartpos(i,1))*mytimeratio)
            exit for
            end if
            next i
            
            mypriceratio=(VAL(circledb.Cell(1 , drawi))-pricechartpos(0,0))/(pricechartpos(1,0)-pricechartpos(0,0))
            defint drawcircley1=pricechartpos(0,1)-round((pricechartpos(0,1)-pricechartpos(1,1))*mypriceratio)
            
            mypriceratio=(VAL(circledb.Cell(2 , drawi))-pricechartpos(0,0))/(pricechartpos(1,0)-pricechartpos(0,0))
            defint drawcircley2=pricechartpos(0,1)-round((pricechartpos(0,1)-pricechartpos(1,1))*mypriceratio)

            graph.drawp(8 , drawcirclex1 , drawcircley1 , drawcirclex2 , drawcircley2 , 0 , 0)

            graph.savebuffertmp
            graph.paintchart

        END IF

        IF (VAL(crossdb.Cell(3 , drawi)) >= graphserialdatebegin AND VAL(crossdb.Cell(3 , drawi)) <= graphserialdateend) AND _
            (VAL(crossdb.Cell(4 , drawi)) >= graphserialdatebegin AND VAL(crossdb.Cell(4 , drawi)) <= graphserialdateend) AND_
            (VAL(crossdb.Cell(1 , drawi)) >= pricechartpos(0,0) AND VAL(crossdb.Cell(1 , drawi)) <= pricechartpos(1,0)) AND_
            (VAL(crossdb.Cell(2 , drawi)) >= pricechartpos(0,0) AND VAL(crossdb.Cell(2 , drawi)) <= pricechartpos(1,0)) THEN

            graph.bufcntreset
            graph.savebuffertmp

            for i=0 to 1000
            if VAL(crossdb.Cell(3 , drawi))>=timechartpos(i,0) and VAL(crossdb.Cell(3 , drawi))<=timechartpos(i+1,0) then
            mytimeratio=(VAL(crossdb.Cell(3 , drawi))-timechartpos(i,0))/(timechartpos(i+1,0)-timechartpos(i,0))
            defint drawcrossx1=timechartpos(i,1)+round((timechartpos(i+1,1)-timechartpos(i,1))*mytimeratio)
            exit for
            end if
            next i
            
            for i=0 to 1000
            if VAL(crossdb.Cell(4 , drawi))>=timechartpos(i,0) and VAL(crossdb.Cell(4 , drawi))<=timechartpos(i+1,0) then
            mytimeratio=(VAL(crossdb.Cell(4 , drawi))-timechartpos(i,0))/(timechartpos(i+1,0)-timechartpos(i,0))
            defint drawcrossx2=timechartpos(i,1)+round((timechartpos(i+1,1)-timechartpos(i,1))*mytimeratio)
            exit for
            end if
            next i
            
            mypriceratio=(VAL(crossdb.Cell(1 , drawi))-pricechartpos(0,0))/(pricechartpos(1,0)-pricechartpos(0,0))
            defint drawcrossy1=pricechartpos(0,1)-round((pricechartpos(0,1)-pricechartpos(1,1))*mypriceratio)
            
            mypriceratio=(VAL(crossdb.Cell(2 , drawi))-pricechartpos(0,0))/(pricechartpos(1,0)-pricechartpos(0,0))
            defint drawcrossy2=pricechartpos(0,1)-round((pricechartpos(0,1)-pricechartpos(1,1))*mypriceratio)

            graph.drawp(9 , drawcrossx1 , drawcrossy1 , drawcrossx2 , drawcrossy2 , 0 , 0)

            graph.savebuffertmp
            graph.paintchart

        END IF

        IF (VAL(invcircledb.Cell(3 , drawi)) >= graphserialdatebegin AND VAL(invcircledb.Cell(3 , drawi)) <= graphserialdateend) AND _
            (VAL(invcircledb.Cell(4 , drawi)) >= graphserialdatebegin AND VAL(invcircledb.Cell(4 , drawi)) <= graphserialdateend) AND_
            (VAL(invcircledb.Cell(1 , drawi)) >= pricechartpos(0,0) AND VAL(invcircledb.Cell(1 , drawi)) <= pricechartpos(1,0)) AND_
            (VAL(invcircledb.Cell(2 , drawi)) >= pricechartpos(0,0) AND VAL(invcircledb.Cell(2 , drawi)) <= pricechartpos(1,0)) THEN

            graph.bufcntreset
            graph.savebuffertmp

            for i=0 to 1000
            if VAL(invcircledb.Cell(3 , drawi))>=timechartpos(i,0) and VAL(invcircledb.Cell(3 , drawi))<=timechartpos(i+1,0) then
            mytimeratio=(VAL(invcircledb.Cell(3 , drawi))-timechartpos(i,0))/(timechartpos(i+1,0)-timechartpos(i,0))
            defint drawinvcirclex1=timechartpos(i,1)+round((timechartpos(i+1,1)-timechartpos(i,1))*mytimeratio)
            exit for
            end if
            next i
            
            for i=0 to 1000
            if VAL(invcircledb.Cell(4 , drawi))>=timechartpos(i,0) and VAL(invcircledb.Cell(4 , drawi))<=timechartpos(i+1,0) then
            mytimeratio=(VAL(invcircledb.Cell(4 , drawi))-timechartpos(i,0))/(timechartpos(i+1,0)-timechartpos(i,0))
            defint drawinvcirclex2=timechartpos(i,1)+round((timechartpos(i+1,1)-timechartpos(i,1))*mytimeratio)
            exit for
            end if
            next i
            
            mypriceratio=(VAL(invcircledb.Cell(1 , drawi))-pricechartpos(0,0))/(pricechartpos(1,0)-pricechartpos(0,0))
            defint drawinvcircley1=pricechartpos(0,1)-round((pricechartpos(0,1)-pricechartpos(1,1))*mypriceratio)
            
            mypriceratio=(VAL(invcircledb.Cell(2 , drawi))-pricechartpos(0,0))/(pricechartpos(1,0)-pricechartpos(0,0))
            defint drawinvcircley2=pricechartpos(0,1)-round((pricechartpos(0,1)-pricechartpos(1,1))*mypriceratio)

            graph.drawp(10 , drawinvcirclex1 , drawinvcircley1 , drawinvcirclex2 , drawinvcircley2 , 0 , 0)

            graph.savebuffertmp
            graph.paintchart

        END IF

        IF (VAL(aimingdb.Cell(3 , drawi)) >= graphserialdatebegin AND VAL(aimingdb.Cell(3 , drawi)) <= graphserialdateend) AND _
            (VAL(aimingdb.Cell(4 , drawi)) >= graphserialdatebegin AND VAL(aimingdb.Cell(4 , drawi)) <= graphserialdateend) AND_
            (VAL(aimingdb.Cell(1 , drawi)) >= pricechartpos(0,0) AND VAL(aimingdb.Cell(1 , drawi)) <= pricechartpos(1,0)) AND_
            (VAL(aimingdb.Cell(2 , drawi)) >= pricechartpos(0,0) AND VAL(aimingdb.Cell(2 , drawi)) <= pricechartpos(1,0)) THEN

            graph.bufcntreset
            graph.savebuffertmp

            for i=0 to 1000
            if VAL(aimingdb.Cell(3 , drawi))>=timechartpos(i,0) and VAL(aimingdb.Cell(3 , drawi))<=timechartpos(i+1,0) then
            mytimeratio=(VAL(aimingdb.Cell(3 , drawi))-timechartpos(i,0))/(timechartpos(i+1,0)-timechartpos(i,0))
            defint drawaimingx1=timechartpos(i,1)+round((timechartpos(i+1,1)-timechartpos(i,1))*mytimeratio)
            exit for
            end if
            next i
            
            for i=0 to 1000
            if VAL(aimingdb.Cell(4 , drawi))>=timechartpos(i,0) and VAL(aimingdb.Cell(4 , drawi))<=timechartpos(i+1,0) then
            mytimeratio=(VAL(aimingdb.Cell(4 , drawi))-timechartpos(i,0))/(timechartpos(i+1,0)-timechartpos(i,0))
            defint drawaimingx2=timechartpos(i,1)+round((timechartpos(i+1,1)-timechartpos(i,1))*mytimeratio)
            exit for
            end if
            next i
            
            mypriceratio=(VAL(aimingdb.Cell(1 , drawi))-pricechartpos(0,0))/(pricechartpos(1,0)-pricechartpos(0,0))
            defint drawaimingy1=pricechartpos(0,1)-round((pricechartpos(0,1)-pricechartpos(1,1))*mypriceratio)
            
            mypriceratio=(VAL(aimingdb.Cell(2 , drawi))-pricechartpos(0,0))/(pricechartpos(1,0)-pricechartpos(0,0))
            defint drawaimingy2=pricechartpos(0,1)-round((pricechartpos(0,1)-pricechartpos(1,1))*mypriceratio)

            graph.drawp(11 , drawaimingx1 , drawaimingy1 , drawaimingx2 , drawaimingy2 , 0 , 0)

            graph.savebuffertmp
            graph.paintchart

        END IF

        IF (VAL(sindb.Cell(3 , drawi)) >= graphserialdatebegin AND VAL(sindb.Cell(3 , drawi)) <= graphserialdateend) AND _
            (VAL(sindb.Cell(4 , drawi)) >= graphserialdatebegin AND VAL(sindb.Cell(4 , drawi)) <= graphserialdateend) AND_
            (VAL(sindb.Cell(1 , drawi)) >= pricechartpos(0,0) AND VAL(sindb.Cell(1 , drawi)) <= pricechartpos(1,0)) AND_
            (VAL(sindb.Cell(2 , drawi)) >= pricechartpos(0,0) AND VAL(sindb.Cell(2 , drawi)) <= pricechartpos(1,0)) THEN

            graph.bufcntreset
            graph.savebuffertmp

            for i=0 to 1000
            if VAL(sindb.Cell(3 , drawi))>=timechartpos(i,0) and VAL(sindb.Cell(3 , drawi))<=timechartpos(i+1,0) then
            mytimeratio=(VAL(sindb.Cell(3 , drawi))-timechartpos(i,0))/(timechartpos(i+1,0)-timechartpos(i,0))
            defint drawsinx1=timechartpos(i,1)+round((timechartpos(i+1,1)-timechartpos(i,1))*mytimeratio)
            exit for
            end if
            next i
            
            for i=0 to 1000
            if VAL(sindb.Cell(4 , drawi))>=timechartpos(i,0) and VAL(sindb.Cell(4 , drawi))<=timechartpos(i+1,0) then
            mytimeratio=(VAL(sindb.Cell(4 , drawi))-timechartpos(i,0))/(timechartpos(i+1,0)-timechartpos(i,0))
            defint drawsinx2=timechartpos(i,1)+round((timechartpos(i+1,1)-timechartpos(i,1))*mytimeratio)
            exit for
            end if
            next i
            
            mypriceratio=(VAL(sindb.Cell(1 , drawi))-pricechartpos(0,0))/(pricechartpos(1,0)-pricechartpos(0,0))
            defint drawsiny1=pricechartpos(0,1)-round((pricechartpos(0,1)-pricechartpos(1,1))*mypriceratio)
            
            mypriceratio=(VAL(sindb.Cell(2 , drawi))-pricechartpos(0,0))/(pricechartpos(1,0)-pricechartpos(0,0))
            defint drawsiny2=pricechartpos(0,1)-round((pricechartpos(0,1)-pricechartpos(1,1))*mypriceratio)

            graph.drawp(13 , drawsinx1 , drawsiny1 , drawsinx2 , drawsiny2 , 0 , 0)

            graph.savebuffertmp
            graph.paintchart

        END IF

        IF (VAL(logdb.Cell(3 , drawi)) >= graphserialdatebegin AND VAL(logdb.Cell(3 , drawi)) <= graphserialdateend) AND _
            (VAL(logdb.Cell(4 , drawi)) >= graphserialdatebegin AND VAL(logdb.Cell(4 , drawi)) <= graphserialdateend) AND_
            (VAL(logdb.Cell(1 , drawi)) >= pricechartpos(0,0) AND VAL(logdb.Cell(1 , drawi)) <= pricechartpos(1,0)) AND_
            (VAL(logdb.Cell(2 , drawi)) >= pricechartpos(0,0) AND VAL(logdb.Cell(2 , drawi)) <= pricechartpos(1,0)) THEN

            graph.bufcntreset
            graph.savebuffertmp

            for i=0 to 1000
            if VAL(logdb.Cell(3 , drawi))>=timechartpos(i,0) and VAL(logdb.Cell(3 , drawi))<=timechartpos(i+1,0) then
            mytimeratio=(VAL(logdb.Cell(3 , drawi))-timechartpos(i,0))/(timechartpos(i+1,0)-timechartpos(i,0))
            defint drawlogx1=timechartpos(i,1)+round((timechartpos(i+1,1)-timechartpos(i,1))*mytimeratio)
            exit for
            end if
            next i
            
            for i=0 to 1000
            if VAL(logdb.Cell(4 , drawi))>=timechartpos(i,0) and VAL(logdb.Cell(4 , drawi))<=timechartpos(i+1,0) then
            mytimeratio=(VAL(logdb.Cell(4 , drawi))-timechartpos(i,0))/(timechartpos(i+1,0)-timechartpos(i,0))
            defint drawlogx2=timechartpos(i,1)+round((timechartpos(i+1,1)-timechartpos(i,1))*mytimeratio)
            exit for
            end if
            next i
            
            mypriceratio=(VAL(logdb.Cell(1 , drawi))-pricechartpos(0,0))/(pricechartpos(1,0)-pricechartpos(0,0))
            defint drawlogy1=pricechartpos(0,1)-round((pricechartpos(0,1)-pricechartpos(1,1))*mypriceratio)
            
            mypriceratio=(VAL(logdb.Cell(2 , drawi))-pricechartpos(0,0))/(pricechartpos(1,0)-pricechartpos(0,0))
            defint drawlogy2=pricechartpos(0,1)-round((pricechartpos(0,1)-pricechartpos(1,1))*mypriceratio)

            graph.drawp(14 , drawlogx1 , drawlogy1 , drawlogx2 , drawlogy2 , 0 , 0)

            graph.savebuffertmp
            graph.paintchart

        END IF

        IF (VAL(expdb.Cell(3 , drawi)) >= graphserialdatebegin AND VAL(expdb.Cell(3 , drawi)) <= graphserialdateend) AND _
            (VAL(expdb.Cell(4 , drawi)) >= graphserialdatebegin AND VAL(expdb.Cell(4 , drawi)) <= graphserialdateend) AND_
            (VAL(expdb.Cell(1 , drawi)) >= pricechartpos(0,0) AND VAL(expdb.Cell(1 , drawi)) <= pricechartpos(1,0)) AND_
            (VAL(expdb.Cell(2 , drawi)) >= pricechartpos(0,0) AND VAL(expdb.Cell(2 , drawi)) <= pricechartpos(1,0)) THEN

            graph.bufcntreset
            graph.savebuffertmp

            for i=0 to 1000
            if VAL(expdb.Cell(3 , drawi))>=timechartpos(i,0) and VAL(expdb.Cell(3 , drawi))<=timechartpos(i+1,0) then
            mytimeratio=(VAL(expdb.Cell(3 , drawi))-timechartpos(i,0))/(timechartpos(i+1,0)-timechartpos(i,0))
            defint drawexpx1=timechartpos(i,1)+round((timechartpos(i+1,1)-timechartpos(i,1))*mytimeratio)
            exit for
            end if
            next i
            
            for i=0 to 1000
            if VAL(expdb.Cell(4 , drawi))>=timechartpos(i,0) and VAL(expdb.Cell(4 , drawi))<=timechartpos(i+1,0) then
            mytimeratio=(VAL(expdb.Cell(4 , drawi))-timechartpos(i,0))/(timechartpos(i+1,0)-timechartpos(i,0))
            defint drawexpx2=timechartpos(i,1)+round((timechartpos(i+1,1)-timechartpos(i,1))*mytimeratio)
            exit for
            end if
            next i
            
            mypriceratio=(VAL(expdb.Cell(1 , drawi))-pricechartpos(0,0))/(pricechartpos(1,0)-pricechartpos(0,0))
            defint drawexpy1=pricechartpos(0,1)-round((pricechartpos(0,1)-pricechartpos(1,1))*mypriceratio)
            
            mypriceratio=(VAL(expdb.Cell(2 , drawi))-pricechartpos(0,0))/(pricechartpos(1,0)-pricechartpos(0,0))
            defint drawexpy2=pricechartpos(0,1)-round((pricechartpos(0,1)-pricechartpos(1,1))*mypriceratio)

            graph.drawp(15 , drawexpx1 , drawexpy1 , drawexpx2 , drawexpy2 , 0 , 0)

            graph.savebuffertmp
            graph.paintchart

        END IF

        IF (VAL(ellipsedb.Cell(3 , drawi)) >= graphserialdatebegin AND VAL(ellipsedb.Cell(3 , drawi)) <= graphserialdateend) AND _
            (VAL(ellipsedb.Cell(4 , drawi)) >= graphserialdatebegin AND VAL(ellipsedb.Cell(4 , drawi)) <= graphserialdateend) AND_
            (VAL(ellipsedb.Cell(1 , drawi)) >= pricechartpos(0,0) AND VAL(ellipsedb.Cell(1 , drawi)) <= pricechartpos(1,0)) AND_
            (VAL(ellipsedb.Cell(2 , drawi)) >= pricechartpos(0,0) AND VAL(ellipsedb.Cell(2 , drawi)) <= pricechartpos(1,0)) THEN

            graph.bufcntreset
            graph.savebuffertmp

            for i=0 to 1000
            if VAL(ellipsedb.Cell(3 , drawi))>=timechartpos(i,0) and VAL(ellipsedb.Cell(3 , drawi))<=timechartpos(i+1,0) then
            mytimeratio=(VAL(ellipsedb.Cell(3 , drawi))-timechartpos(i,0))/(timechartpos(i+1,0)-timechartpos(i,0))
            defint drawellipsex1=timechartpos(i,1)+round((timechartpos(i+1,1)-timechartpos(i,1))*mytimeratio)
            exit for
            end if
            next i
            
            for i=0 to 1000
            if VAL(ellipsedb.Cell(4 , drawi))>=timechartpos(i,0) and VAL(ellipsedb.Cell(4 , drawi))<=timechartpos(i+1,0) then
            mytimeratio=(VAL(ellipsedb.Cell(4 , drawi))-timechartpos(i,0))/(timechartpos(i+1,0)-timechartpos(i,0))
            defint drawellipsex2=timechartpos(i,1)+round((timechartpos(i+1,1)-timechartpos(i,1))*mytimeratio)
            exit for
            end if
            next i
            
            mypriceratio=(VAL(ellipsedb.Cell(1 , drawi))-pricechartpos(0,0))/(pricechartpos(1,0)-pricechartpos(0,0))
            defint drawellipsey1=pricechartpos(0,1)-round((pricechartpos(0,1)-pricechartpos(1,1))*mypriceratio)
            
            mypriceratio=(VAL(ellipsedb.Cell(2 , drawi))-pricechartpos(0,0))/(pricechartpos(1,0)-pricechartpos(0,0))
            defint drawellipsey2=pricechartpos(0,1)-round((pricechartpos(0,1)-pricechartpos(1,1))*mypriceratio)

            graph.drawp(16 , drawellipsex1 , drawellipsey1 , drawellipsex2 , drawellipsey2 , 0 , 0)

            graph.savebuffertmp
            graph.paintchart

        END IF
        
        IF (VAL(pentagdb.Cell(3 , drawi)) >= graphserialdatebegin AND VAL(pentagdb.Cell(3 , drawi)) <= graphserialdateend) AND _
            (VAL(pentagdb.Cell(4 , drawi)) >= graphserialdatebegin AND VAL(pentagdb.Cell(4 , drawi)) <= graphserialdateend) AND_
            (VAL(pentagdb.Cell(1 , drawi)) >= pricechartpos(0,0) AND VAL(pentagdb.Cell(1 , drawi)) <= pricechartpos(1,0)) AND_
            (VAL(pentagdb.Cell(2 , drawi)) >= pricechartpos(0,0) AND VAL(pentagdb.Cell(2 , drawi)) <= pricechartpos(1,0)) THEN

            graph.bufcntreset
            graph.savebuffertmp

            for i=0 to 1000
            if VAL(pentagdb.Cell(3 , drawi))>=timechartpos(i,0) and VAL(pentagdb.Cell(3 , drawi))<=timechartpos(i+1,0) then
            mytimeratio=(VAL(pentagdb.Cell(3 , drawi))-timechartpos(i,0))/(timechartpos(i+1,0)-timechartpos(i,0))
            defint drawpentagx1=timechartpos(i,1)+round((timechartpos(i+1,1)-timechartpos(i,1))*mytimeratio)
            exit for
            end if
            next i
            
            for i=0 to 1000
            if VAL(pentagdb.Cell(4 , drawi))>=timechartpos(i,0) and VAL(pentagdb.Cell(4 , drawi))<=timechartpos(i+1,0) then
            mytimeratio=(VAL(pentagdb.Cell(4 , drawi))-timechartpos(i,0))/(timechartpos(i+1,0)-timechartpos(i,0))
            defint drawpentagx2=timechartpos(i,1)+round((timechartpos(i+1,1)-timechartpos(i,1))*mytimeratio)
            exit for
            end if
            next i
            
            mypriceratio=(VAL(pentagdb.Cell(1 , drawi))-pricechartpos(0,0))/(pricechartpos(1,0)-pricechartpos(0,0))
            defint drawpentagy1=pricechartpos(0,1)-round((pricechartpos(0,1)-pricechartpos(1,1))*mypriceratio)
            
            mypriceratio=(VAL(pentagdb.Cell(2 , drawi))-pricechartpos(0,0))/(pricechartpos(1,0)-pricechartpos(0,0))
            defint drawpentagy2=pricechartpos(0,1)-round((pricechartpos(0,1)-pricechartpos(1,1))*mypriceratio)

            graph.drawp(27 , drawpentagx1 , drawpentagy1 , drawpentagx2 , drawpentagy2 , 0 , 0)

            graph.savebuffertmp
            graph.paintchart

        END IF
        
        IF (VAL(sq9fdb.Cell(3 , drawi)) >= graphserialdatebegin AND VAL(sq9fdb.Cell(3 , drawi)) <= graphserialdateend) AND _
            (VAL(sq9fdb.Cell(4 , drawi)) >= graphserialdatebegin AND VAL(sq9fdb.Cell(4 , drawi)) <= graphserialdateend) AND_
            (VAL(sq9fdb.Cell(1 , drawi)) >= pricechartpos(0,0) AND VAL(sq9fdb.Cell(1 , drawi)) <= pricechartpos(1,0)) AND_
            (VAL(sq9fdb.Cell(2 , drawi)) >= pricechartpos(0,0) AND VAL(sq9fdb.Cell(2 , drawi)) <= pricechartpos(1,0)) THEN

            graph.bufcntreset
            graph.savebuffertmp

            for i=0 to 1000
            if VAL(sq9fdb.Cell(3 , drawi))>=timechartpos(i,0) and VAL(sq9fdb.Cell(3 , drawi))<=timechartpos(i+1,0) then
            mytimeratio=(VAL(sq9fdb.Cell(3 , drawi))-timechartpos(i,0))/(timechartpos(i+1,0)-timechartpos(i,0))
            defint drawsq9fx1=timechartpos(i,1)+round((timechartpos(i+1,1)-timechartpos(i,1))*mytimeratio)
            exit for
            end if
            next i
            
            for i=0 to 1000
            if VAL(sq9fdb.Cell(4 , drawi))>=timechartpos(i,0) and VAL(sq9fdb.Cell(4 , drawi))<=timechartpos(i+1,0) then
            mytimeratio=(VAL(sq9fdb.Cell(4 , drawi))-timechartpos(i,0))/(timechartpos(i+1,0)-timechartpos(i,0))
            defint drawsq9fx2=timechartpos(i,1)+round((timechartpos(i+1,1)-timechartpos(i,1))*mytimeratio)
            exit for
            end if
            next i
            
            mypriceratio=(VAL(sq9fdb.Cell(1 , drawi))-pricechartpos(0,0))/(pricechartpos(1,0)-pricechartpos(0,0))
            defint drawsq9fy1=pricechartpos(0,1)-round((pricechartpos(0,1)-pricechartpos(1,1))*mypriceratio)
            
            mypriceratio=(VAL(sq9fdb.Cell(2 , drawi))-pricechartpos(0,0))/(pricechartpos(1,0)-pricechartpos(0,0))
            defint drawsq9fy2=pricechartpos(0,1)-round((pricechartpos(0,1)-pricechartpos(1,1))*mypriceratio)

            graph.drawp(19 , drawsq9fx1 , drawsq9fy1 , drawsq9fx2 , drawsq9fy2 , 0 , 0)

            graph.savebuffertmp
            graph.paintchart

        END IF
        
        IF (VAL(sqr2db.Cell(3 , drawi)) >= graphserialdatebegin AND VAL(sqr2db.Cell(3 , drawi)) <= graphserialdateend) AND _
            (VAL(sqr2db.Cell(4 , drawi)) >= graphserialdatebegin AND VAL(sqr2db.Cell(4 , drawi)) <= graphserialdateend) AND_
            (VAL(sqr2db.Cell(1 , drawi)) >= pricechartpos(0,0) AND VAL(sqr2db.Cell(1 , drawi)) <= pricechartpos(1,0)) AND_
            (VAL(sqr2db.Cell(2 , drawi)) >= pricechartpos(0,0) AND VAL(sqr2db.Cell(2 , drawi)) <= pricechartpos(1,0)) THEN

            graph.bufcntreset
            graph.savebuffertmp

            for i=0 to 1000
            if VAL(sqr2db.Cell(3 , drawi))>=timechartpos(i,0) and VAL(sqr2db.Cell(3 , drawi))<=timechartpos(i+1,0) then
            mytimeratio=(VAL(sqr2db.Cell(3 , drawi))-timechartpos(i,0))/(timechartpos(i+1,0)-timechartpos(i,0))
            defint drawsqr2x1=timechartpos(i,1)+round((timechartpos(i+1,1)-timechartpos(i,1))*mytimeratio)
            exit for
            end if
            next i
            
            for i=0 to 1000
            if VAL(sqr2db.Cell(4 , drawi))>=timechartpos(i,0) and VAL(sqr2db.Cell(4 , drawi))<=timechartpos(i+1,0) then
            mytimeratio=(VAL(sqr2db.Cell(4 , drawi))-timechartpos(i,0))/(timechartpos(i+1,0)-timechartpos(i,0))
            defint drawsqr2x2=timechartpos(i,1)+round((timechartpos(i+1,1)-timechartpos(i,1))*mytimeratio)
            exit for
            end if
            next i
            
            mypriceratio=(VAL(sqr2db.Cell(1 , drawi))-pricechartpos(0,0))/(pricechartpos(1,0)-pricechartpos(0,0))
            defint drawsqr2y1=pricechartpos(0,1)-round((pricechartpos(0,1)-pricechartpos(1,1))*mypriceratio)
            
            mypriceratio=(VAL(sqr2db.Cell(2 , drawi))-pricechartpos(0,0))/(pricechartpos(1,0)-pricechartpos(0,0))
            defint drawsqr2y2=pricechartpos(0,1)-round((pricechartpos(0,1)-pricechartpos(1,1))*mypriceratio)

            graph.drawp(31 , drawsqr2x1 , drawsqr2y1 , drawsqr2x2 , drawsqr2y2 , 0 , 0)

            graph.savebuffertmp
            graph.paintchart

        END IF

        IF (VAL(tri2db.Cell(3 , drawi)) >= graphserialdatebegin AND VAL(tri2db.Cell(3 , drawi)) <= graphserialdateend) AND _
            (VAL(tri2db.Cell(4 , drawi)) >= graphserialdatebegin AND VAL(tri2db.Cell(4 , drawi)) <= graphserialdateend) AND_
            (VAL(tri2db.Cell(1 , drawi)) >= pricechartpos(0,0) AND VAL(tri2db.Cell(1 , drawi)) <= pricechartpos(1,0)) AND_
            (VAL(tri2db.Cell(2 , drawi)) >= pricechartpos(0,0) AND VAL(tri2db.Cell(2 , drawi)) <= pricechartpos(1,0)) THEN

            graph.bufcntreset
            graph.savebuffertmp

            for i=0 to 1000
            if VAL(tri2db.Cell(3 , drawi))>=timechartpos(i,0) and VAL(tri2db.Cell(3 , drawi))<=timechartpos(i+1,0) then
            mytimeratio=(VAL(tri2db.Cell(3 , drawi))-timechartpos(i,0))/(timechartpos(i+1,0)-timechartpos(i,0))
            defint drawtri2x1=timechartpos(i,1)+round((timechartpos(i+1,1)-timechartpos(i,1))*mytimeratio)
            exit for
            end if
            next i
            
            for i=0 to 1000
            if VAL(tri2db.Cell(4 , drawi))>=timechartpos(i,0) and VAL(tri2db.Cell(4 , drawi))<=timechartpos(i+1,0) then
            mytimeratio=(VAL(tri2db.Cell(4 , drawi))-timechartpos(i,0))/(timechartpos(i+1,0)-timechartpos(i,0))
            defint drawtri2x2=timechartpos(i,1)+round((timechartpos(i+1,1)-timechartpos(i,1))*mytimeratio)
            exit for
            end if
            next i
            
            mypriceratio=(VAL(tri2db.Cell(1 , drawi))-pricechartpos(0,0))/(pricechartpos(1,0)-pricechartpos(0,0))
            defint drawtri2y1=pricechartpos(0,1)-round((pricechartpos(0,1)-pricechartpos(1,1))*mypriceratio)
            
            mypriceratio=(VAL(tri2db.Cell(2 , drawi))-pricechartpos(0,0))/(pricechartpos(1,0)-pricechartpos(0,0))
            defint drawtri2y2=pricechartpos(0,1)-round((pricechartpos(0,1)-pricechartpos(1,1))*mypriceratio)

            graph.drawp(32 , drawtri2x1 , drawtri2y1 , drawtri2x2 , drawtri2y2 , 0 , 0)

            graph.savebuffertmp
            graph.paintchart

        END IF

    NEXT drawi

END IF

IF showcanvas = 1 THEN
    WITH canvas
        .firstbufcntreset
        .savebuffertmp
        .Paint
    END WITH
END IF
CASE "HLC Style 1"
    'NOTE: If values for .Data.Cells 2, 3 and 4 are set equal,
    'Box routine will draw a Hi-Lo-Close antenna style graph
    WITH Graph
        .Initialize  'Set defaults
        .ChartType = ctBox  'Hi-Lo-Close Plot
        .ChartStyle = csHiLo
        .MainTitle.Text = "Hi-Lo-Close Plot"  'change desired options
        .SubTitle.Text = "Antenna Style"
        .XTitle.Text = "X Axis"
        .YTitle.Text = "Y Axis"
        .XAxis.Grid = FALSE
        .DoLegend = FALSE
        .DATA.ColCount = 12  'Set .Data Grid dimensions
        .DATA.RowCount = 5
        k = 10  'Load the data
        RANDOMIZE
        FOR i = 1 TO .DATA.ColCount  'for each col
            .Series(i).AutoColor = FALSE
            .Series(i).Color = .Colors(8)
            .DATA.Cell(i , 0) = "Grp " + STR$(i) 'Legend in Row 0 of Each Col
            .DATA.Cell(i , 1) = STR$(RND * k + 100) 'Hi Value
            .DATA.Cell(i , 2) = STR$(RND * k + 75) '<-- Set all Three to
            .DATA.Cell(i , 3) = .DATA.Cell(i , 2) '<-- the mid or "Close"
            .DATA.Cell(i , 4) = .DATA.Cell(i , 2) '<-- Value
            .DATA.Cell(i , 5) = STR$(RND * k + 50) 'Lo Value
        NEXT i
        .DrawChart(FALSE) 'Draw it!
    END WITH

CASE "HLC Style 2"
    'NOTE: If values for .Data.Cells 1 & 2 and 4 & 5 are set equal,
    'Box routine will draw a Hi-Lo-Close box style graph
    WITH Graph
        .Initialize  'Set defaults
        .ChartType = ctBox  'Hi-Lo-Close Plot
        .ChartStyle = csWhisker  'Whiskers are hidden :)
        .MainTitle.Text = "Hi-Lo-Close Plot"  'change desired options
        .SubTitle.Text = "Box Style"
        .XTitle.Text = "X Axis"
        .YTitle.Text = "Y Axis"
        .XAxis.Grid = FALSE
        .XAxis.Tics = FALSE
        .XAxis.Labeled = FALSE
        .DATA.ColCount = 12  'Set .Data Grid dimensions
        .DATA.RowCount = 5
        k = 10  'Load the data
        RANDOMIZE
        FOR i = 1 TO .DATA.ColCount  'for each col
            .DATA.Cell(i , 0) = "Group " + STR$(i) 'Legend in Row 0 of Each Col
            .DATA.Cell(i , 1) = STR$(RND * k + 75) 'Hi Value
            .DATA.Cell(i , 2) = .DATA.Cell(i , 1) '<-- Set = to Hi Value
            .DATA.Cell(i , 3) = STR$(RND * k + 50) 'Close Value
            .DATA.Cell(i , 4) = STR$(RND * k + 25) 'Lo Value
            .DATA.Cell(i , 5) = .DATA.Cell(i , 4) '<-- Set = Lo Value
        NEXT i
        .DrawChart(FALSE) 'Draw it!
    END WITH

CASE "Redraw"
    WITH Graph
        .MainFont.Name = "Times New Roman"  'Change some options
        .SubFont.Name = "Times New Roman"  'on the currently defined chart
        .PlotAreaColor = .Colors(24)
        SELECT CASE .SubFont.Size
            CASE .MainFont.Size
                .SubFont.Size = 12
            CASE ELSE
                .SubFont.Size = .MainFont.Size
        END SELECT
        SELECT CASE .DoLegend
            CASE TRUE
                .DoLegend = FALSE
            CASE FALSE
                .DoLegend = TRUE
        END SELECT
        SELECT CASE .GreyScale
            CASE TRUE
                .GreyScale = FALSE
            CASE FALSE
                .GreyScale = TRUE
        END SELECT
        .RedrawChart  'and redraw the chart
    END WITH

CASE "Default"
    WITH Graph  'The minimum (2) required calls
        .Initialize  'Always call this first
        .MainTitle.Text = "Default Chart Settings"  '(With one option changed)
        .DrawChart(FALSE) 'Always call this last
    END WITH

CASE "Save"
    IF openedfilesnb = 0 THEN
        EXIT SUB
    END IF
    Graph.SaveChart("")

CASE "Print"
    IF openedfilesnb = 0 THEN
        EXIT SUB
    END IF
    Graph.PrintChart(Printer.PrinterIndex , 1 , 40 , 1 , FALSE)

CASE "Exit"
    frmMain.Close

END SELECT

END SUB

'-------------------------------------------------------------------------------------------
