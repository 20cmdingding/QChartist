'-==================================== End Separate indicators area ==============================-

drawidseparatecanvas=drawid

IF l = 1 THEN
    sepindivalmin = VAL(canvas.separateindicator1.Cell(2 , lbar))
    sepindivalmax = VAL(canvas.separateindicator1.Cell(2 , lbar))
END IF

if i<=chartstart + .DATA.ColCount then

IF VAL(canvas.separateindicator1.Cell(2 , lbar)) < sepindivalmin THEN
    sepindivalmin = VAL(canvas.separateindicator1.Cell(2 , lbar))
END IF

IF VAL(canvas.separateindicator1.Cell(2 , lbar)) > sepindivalmax THEN
    sepindivalmax = VAL(canvas.separateindicator1.Cell(2 , lbar))
END IF

end if

END IF
'doevents
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
        
        IF (VAL(orderbuydb.Cell(3 , drawi)) >= graphserialdatebegin AND VAL(orderbuydb.Cell(3 , drawi)) <= graphserialdateend+charttf(displayedfile)*60) AND _            
            (VAL(orderbuydb.Cell(1 , drawi)) >= pricechartpos(0,0) AND VAL(orderbuydb.Cell(1 , drawi)) <= pricechartpos(1,0)) THEN

            graph.bufcntreset
            graph.savebuffertmp
                       
            for i=0 to 1000
            if VAL(orderbuydb.Cell(3 , drawi))>=timechartpos(i,0) and VAL(orderbuydb.Cell(3 , drawi))<=timechartpos(i+1,0)+charttf(displayedfile)*60 then
            mytimeratio=(VAL(orderbuydb.Cell(3 , drawi))-timechartpos(i,0))/(timechartpos(i+1,0)-timechartpos(i,0))
            defint draworderbuyx1=timechartpos(i,1)+round((timechartpos(i+1,1)-timechartpos(i,1))*mytimeratio)
            exit for
            end if
            next i            
            
            mypriceratio=(VAL(orderbuydb.Cell(1 , drawi))-pricechartpos(0,0))/(pricechartpos(1,0)-pricechartpos(0,0))
            defint draworderbuyy1=pricechartpos(0,1)-round((pricechartpos(0,1)-pricechartpos(1,1))*mypriceratio)            

            graph.drawp(34 , draworderbuyx1 , draworderbuyy1 , 0 , 0 , 0 , 0)

            graph.savebuffertmp
            graph.paintchart

        END IF
        
        IF (VAL(orderselldb.Cell(3 , drawi)) >= graphserialdatebegin AND VAL(orderselldb.Cell(3 , drawi)) <= graphserialdateend+charttf(displayedfile)*60) AND _            
            (VAL(orderselldb.Cell(1 , drawi)) >= pricechartpos(0,0) AND VAL(orderselldb.Cell(1 , drawi)) <= pricechartpos(1,0)) THEN

            graph.bufcntreset
            graph.savebuffertmp
                       
            for i=0 to 1000
            if VAL(orderselldb.Cell(3 , drawi))>=timechartpos(i,0) and VAL(orderselldb.Cell(3 , drawi))<=timechartpos(i+1,0)+charttf(displayedfile)*60 then
            mytimeratio=(VAL(orderselldb.Cell(3 , drawi))-timechartpos(i,0))/(timechartpos(i+1,0)-timechartpos(i,0))
            defint drawordersellx1=timechartpos(i,1)+round((timechartpos(i+1,1)-timechartpos(i,1))*mytimeratio)
            exit for
            end if
            next i            
            
            mypriceratio=(VAL(orderselldb.Cell(1 , drawi))-pricechartpos(0,0))/(pricechartpos(1,0)-pricechartpos(0,0))
            defint draworderselly1=pricechartpos(0,1)-round((pricechartpos(0,1)-pricechartpos(1,1))*mypriceratio)            

            graph.drawp(35 , drawordersellx1 , draworderselly1 , 0 , 0 , 0 , 0)

            graph.savebuffertmp
            graph.paintchart

        END IF
        
        IF (VAL(textlabelsdb.Cell(2 , drawi)) >= graphserialdatebegin AND VAL(textlabelsdb.Cell(2 , drawi)) <= graphserialdateend+charttf(displayedfile)*60) AND _            
            (VAL(textlabelsdb.Cell(1 , drawi)) >= pricechartpos(0,0) AND VAL(textlabelsdb.Cell(1 , drawi)) <= pricechartpos(1,0)) THEN

            graph.bufcntreset
            graph.savebuffertmp
                       
            for i=0 to 1000
            if VAL(textlabelsdb.Cell(2 , drawi))>=timechartpos(i,0) and VAL(textlabelsdb.Cell(2 , drawi))<=timechartpos(i+1,0)+charttf(displayedfile)*60 then
            mytimeratio=(VAL(textlabelsdb.Cell(2 , drawi))-timechartpos(i,0))/(timechartpos(i+1,0)-timechartpos(i,0))
            defint drawtextlabelsx1=timechartpos(i,1)+round((timechartpos(i+1,1)-timechartpos(i,1))*mytimeratio)
            exit for
            end if
            next i            
            
            mypriceratio=(VAL(textlabelsdb.Cell(1 , drawi))-pricechartpos(0,0))/(pricechartpos(1,0)-pricechartpos(0,0))
            defint drawtextlabelsy1=pricechartpos(0,1)-round((pricechartpos(0,1)-pricechartpos(1,1))*mypriceratio)            

            Graph.buffer.TextOut(drawtextlabelsx1 , drawtextlabelsy1 , textlabelsdb.Cell(3 , drawi) , val(textlabelsdb.Cell(4 , drawi)) , val(textlabelsdb.Cell(6 , drawi)))

            graph.savebuffertmp
            graph.paintchart

        END IF
        
        
        doevents
    NEXT drawi
    
IF (googlerealtimecheckbox.checked=1) THEN

            graph.bufcntreset
            graph.savebuffertmp

            graph.drawp(33 , 0 , 0 , 0 , 0 , 0 , 0)

            graph.savebuffertmp
            graph.paintchart

        END IF    

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
