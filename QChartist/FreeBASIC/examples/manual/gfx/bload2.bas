'' examples/manual/gfx/bload2.bas
''
'' NOTICE: This file is part of the FreeBASIC Compiler package and can't
''         be included in other distributions without authorization.
''
'' See Also: http://www.freebasic.net/wiki/wikka.php?wakka=KeyPgBload
'' --------

'Load a 48x48 bitmap into an array
Screen 18, 32
Dim myImage As Any Ptr = ImageCreate( 48, 48 )
BLoad "picture.bmp", myImage
Put (10,10), myImage
ImageDestroy( myImage )
Sleep
