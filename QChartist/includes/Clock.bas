'*********************************************************
'****    A simple analog clock using QCanvas          ****' 
'****        10/07/07                                 ****'
'****    Use & enjoy freely & at your own risk        ****'
'**********************************************************

'$include "rapidq2.inc"
   
declare sub closeclock
declare sub tymclock
declare sub onshclock
declare sub paintclock
declare sub clockrun

dim timclock as qtimer
 timclock.enabled = 0
  timclock.ontimer = tymclock
   timclock.interval = 1000
   
'---------------------------------------------------------
create clock as qform
    visible=0
    left = 130              'Put it where you want it
    width = 130 
    height = 150
    borderstyle = 1
    color = &HFFFFFF        'set to background color
    onshow = onshclock
    onclick = closeclock
  create myc as qcanvas
    parent = clock
    top = 0
    left = 0
    height = 100
    width = 100
    color = &HFFFFFF
    onpaint = paintclock
    showhint = true
    onclick = closeclock
  end create
  create pleasewaitclocklabel as qlabel
  top=100
  left=20
  caption="Please wait"
  end create
end create
'-------------------------------------------------------
'clock.showmodal
'-------------------------------------------------------
sub tymclock
  clockrun
end sub

sub clockrun
  myc.repaint
  dim posit as integer            'Second hand
    posit = val(right$(time$,2))
  dim x as integer
    x = 50
  dim y as integer
    y = 0
  if posit < 16 then
    x = (sin(posit*0.10472)*40) + 50
    y = 50 - (cos(posit*0.10472)*40)
  end if
  if posit > 15 and posit < 31 then
    x = (cos((posit - 15)*0.10472)*40) + 50 +1
    y = (sin((posit - 15)*0.10472)*40) + 50
  end if
  if posit >30 and posit <46 then
    x = 50 - (sin((posit - 30)*0.10472)*40)
    y = 50 + (cos((posit - 30)*0.10472)*40) +1
  end if
  if posit >45 and posit <60 then
    x = 50 - (cos((posit - 45)*0.10472)*40)
    y = 50 - (sin((posit -45)*0.10472)*40 )
  end if
  myc.line(50,50,x,y,0)
  dim posot as integer                'Minute hand
    posot = val(mid$(time$,4,2))
  dim v as integer
    v = 50
  dim w as integer
    w = 0
  if posot < 16 then
    v = (sin(posot*0.10472)*33) + 50
    w = 50 - (cos(posot*0.10472)*33)
  end if
  if posot > 15 and posot < 31 then
    v = (cos((posot - 15)*0.10472)*33) + 50 +1
    w = (sin((posot - 15)*0.10472)*33) + 50
  end if
  if posot >30 and posot <46 then
    v = 50 - (sin((posot - 30)*0.10472)*33)
    w = 50 + (cos((posot - 30)*0.10472)*33) +1
  end if
  if posot >45 and posot <60 then
    v = 50 - (cos((posot - 45)*0.10472)*33)
    w = 50 - (sin((posot -45)*0.10472)*33 )
  end if
  myc.line(50,50,v,w,&H0000FF)
  dim posat as integer                    'Hour hand
    posat = val(left$(time$,2))
  if (val(left$(time$,2))) < 12 then
    posat = val(left$(time$,2))
  else
    posat = ((val(left$(time$,2))) - 12)
  end if
  dim s as integer
    s = 50
  dim t as integer
    t = 0
  if posat < 4 then
    s = (sin(posat*5*0.10472)*25) + 50
    t = 50 - (cos(posat*5*0.10472)*25)
  end if
  if posat > 3 and posat < 7 then
    s = 50 + (cos(((posat*5)-15)*0.10472)*28) +1 
    t = 50 + (sin(((posat*5)-15)*0.10472)*28) 
  end if
  if posat > 6 and posat < 10 then
    s = 50 - (sin(((posat*5) - 30)*0.10472)*25)
    t = 50 + (cos(((posat*5) - 30)*0.10472)*25) +1
  end if
  if posat > 9 and posat < 12 then
    s = 50 - (cos(((posat*5) - 45)*0.10472)*25)
    t = 50 - (sin(((posat*5) - 45)*0.10472)*25 )
  end if
  myc.line(50,50,s,t,&H563470)
  myc.hint = time$
end sub

sub paintclock
  myc.circle(0,0,100,100,0,&HD0D0D0)        'colours for
  myc.circle(5,5,95,95,&HFFFFFF,&H&HFFD0BE) 'the clock
  myc.circle(15,15,85,85,&HFFD09A,&HFFD09A) 'face
  myc.circle(45,45,55,55,&HFF0000,&HFFEFEF) '
  myc.line(50,5,50,0,0)          '0
  myc.line(50,10,50,5,&HFFFFFF)  '0         'Choose your
  myc.line(50,93,50,100,0)       '30        'colors here
  myc.line(50,88,50,93,&HFFFFFF) '30
  myc.line(0,50,5,50,0)          '45
  myc.line(5,50,10,50,&HFFFFFF)  '45
  myc.line(100,50,93,50,0)       '15
  myc.line(93,50,88,50,&HFFFFFF) '15
  myc.line(74,6,71,11,0)   '5
  myc.line(89,30,94,26,0)  '10
  myc.line(93,72,90,71,0)  '20
  myc.line(70,90,71,93,0)  '25
  myc.line(28,90,26,94,0)  '35
  myc.line(5,72,8,70,0)   '40
  myc.line(9,28,6,27,0)    '50
  myc.line(25,7,28,12,0)    '55
end sub

sub onshclock
  paintclock
end sub

sub closeclock
  clock.close
end sub