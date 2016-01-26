'-================================= End indicators area ========================================-
END IF

drawidmaincanvas=drawid

IF l = 1 THEN
    valmin = VAL(Grid.Cell(rowgridoffset + 5 , i))
    valmax = VAL(Grid.Cell(rowgridoffset + 4 , i))
END IF

if i<=chartstart + .DATA.ColCount then

IF VAL(Grid.Cell(rowgridoffset + 5 , i)) < valmin THEN
    valmin = VAL(Grid.Cell(rowgridoffset + 5 , i))
END IF

IF VAL(Grid.Cell(rowgridoffset + 4 , i)) > valmax THEN
    valmax = VAL(Grid.Cell(rowgridoffset + 4 , i))
END IF

end if

'-==================================== Separate indicators area ==============================-


IF scrollmode = 0 THEN
    IF useindi.Checked = 1 THEN

        'FOR lo = 1 TO canvas.separateindicator1.RowCount STEP 2
        '    canvas.separateindicator1.Cell(lo , l) = STR$(l) 'Legend in Row 0 of Each Col
        '    doevents
        'NEXT lo
        'FOR lo = 2 TO canvas.separateindicator1.RowCount STEP 2
        '    canvas.separateindicator1.Cell(lo , l) = STR$(0)
        '    doevents
        'NEXT lo
        
        if i = chartstart then
            defint histoincr
            for histoincr=0 to 100
            drawhisto(histoincr)=0
            doevents
            next histoincr
        end if
        
    END IF

    drawid = 2        

    canvasid ++
    
    

