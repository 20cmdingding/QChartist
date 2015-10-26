
---------------------------------------------------------------------
RQPC        ReadMeFirst.Txt              February 7th, 2007  Jacques
---------------------------------------------------------------------

- Unzip all the files of the distribution in a Directory named RQPC
- Run RQPC_Setup.Exe
- Run CheckInstall.Exe
- Run RQPC_IDE.Exe              to learn  how to use RQPC
- Optional, for more learning, run Tutorial/Make_RQPC.Bat and do the
  exercises

  The only real install ?difficulty? is to __FIRST__ copy RapidQ32.Dll
  in your Windows directory, copy RapidQ32.Dll to the directory of
  RQPC and rename it RQ32.DLL. Only the William original RapidQ32.Dll
  and Snakedile V107 and later work, preferably download V109 at
  http://www.freewebs.com/snakedile
  
  For copyright reasons, the RapidQ32.Dll included in this package is
  William's original.
  
---------------------------------------------------------------------
- to know more about RQPC, read file    Doc.Txt (it is included in
  RQPC.EXE and can be displayed by clicking HELP button in the
  RPQC output window)

- to know more about Tiny executable and ByteCode see
             ByteCode_Course\ByteCode_Course.Txt

- to include Fast Masm or FreeBasic or Gcc functions in your RapidQ
  code, read doc.txt and see the examples in the EXAMPLES directory.
  An easy Beginning is Examples/Fb/Minimum

- questions about RQPC can be posted at RapidQ_EX@yahoogroups.com
---------------------------------------------------------------------






If you have problems with installation, you can read the following

------- INSTALL (old doc somewhat usefull and obsolete) ---------------
- RQPC 0.2700 requires the installation of 5 files anywhere in a 
  single directory (all 5 files in the same directory), I suggest
  the same directory as RC.EXE:
   mandatory:
     RQPC.EXE                       from this package (in RQPC directory)
     RQPC.INI                       from this package (You must edit it and adjust values)
     ResHacker.Exe                  from http://www.angusj.com/
   optional:
     RQ32.DLL = RapidQ32.Dll (V109) from http://www.freewebs.com/snakedile
     Upx.Exe                        from http://upx.sourceforge.net/
------------------------------
- ResHacker.Exe  from Resource Hacker    mandatory, without it
  RQPC 0.2700 will not work.
  So, you MUST download it at        http://www.angusj.com/
  Resource Hacker from that source is trustable, it's used by
  thousands of developpers and the last version is from 2002.
  Just copy ResHacker.Exe (only the exe) in the directory of RQPC.Exe

- If you want to use the 'Upx' option, you must copy a version of
  Upx.exe (only the Exe) in the directory of RQPC.Exe
  Upx can be dopwnloaded at    http://upx.sourceforge.net/

- If you want to add the RapidQ32.Dll in your code to make them
  'stand alone', you need to copy RapidQ32.Dll in the Directory of
  RQPC.Exe and rename it RQ32.DLL  (RapidQ32.Dll V109 is better,
  at Paul's site: http://www.freewebs.com/snakedile/downloads.htm)

- In RQPC.INI, it's MANDATORY to modify the top three lines
  so they correspond to your RapidQ installation directories
        [RQPC]
	    ; CONFIGURED TO DO JUST AS RC.EXE DO
	    RQ_ROOT_DIR=c:\Rapid-Q\
	    RQ_LIBS_DIR=c:\Rapid-Q\Libs
        RQ_INC_DIR=c:\Rapid-Q\Includes

- To run Tiny executable the RapidQ DLL, Rapidq32.Dll must copied
  in a system directory (usually c:\Windows\, ...)

------- LEARNING ----------------------------------------------------

Once RQPC.INI is adapted to your RapidQ directory structure, simply

run    [X:\PathToRQPC\]RQPC.EXE [Y:\PathToYourBasCode\]YourCode.Bas

--------------------------

- RQPC WORKS WITHOUT ANY EXTERNAL COMPILER INSTALLED

    in      Tutorial\
	
	in Make_Rqpc.Bat adapt the path to your RQPC installation
      and run	Make_Rqpc.Bat
	
	or simply compile RqPrecompilerDemo.Bas  with RQPC

    and read the displayed text and DO the exercises. If it
	does not work, tell it in the RapidQ_Ex group.

        do the 'exercises' !

    and still forget about MASM, FB, GCC, BCC

- THEN if you know FB, GCC, MASM or BCC, no need to know all of
   them, only one is enough, and FB - close RapidQ - is very good
   start; use it when you need speed, if you dont have a speed
   issue you dont need them. The examples show what is possible.

- for more detail, read RQPC\Doc.Txt or the embedded RQPC doc.

Questions about RQPC can be posted at RapidQ_EX@yahoogroups.com

---------------------------------------------------------------------

To know more about Tiny executable and ByteCode see
   
       ByteCode_Course\ByteCode_Course.Txt


Jacques
--------------------------------------------------------------------
