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
    
    

