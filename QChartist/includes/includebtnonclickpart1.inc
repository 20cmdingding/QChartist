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
            shiftchartbtn.visible=1

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
                            doevents                                                                                                                                         
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
                numbars_first=chartbars(displayedfile)-scrollchart.position+numbars-1
                numbars_last=chartbars(displayedfile)-scrollchart.position
                        
                
                FOR i = chartstart TO chartstart + .DATA.ColCount + val(generalsettingsfuturebarsedit.text)  'for each col
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
                        'IF useindi.Checked = 1 THEN
                            DIM lo AS INTEGER
                            'FOR lo = 1 TO .Data_Indi.RowCount STEP 2
                            '    .Data_Indi.Cell(lo , l) = STR$(l) 'Legend in Row 0 of Each Col
                            'NEXT lo
                            'FOR lo = 2 TO .Data_Indi.RowCount STEP 2
                            '    .Data_Indi.Cell(lo , l) = STR$(0)
                            'NEXT lo
                        'END IF

                        DIM drawid AS INTEGER
                        drawid = 2
                        DIM indiid AS INTEGER
                        indiid = - 1
                        DIM canvasid AS INTEGER

                        canvasid = 0
                          
