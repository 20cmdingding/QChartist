
- First examine FB_Tny.Bas, it the FB code of the Launcher

- edit   CompileFB_Tny_Bas.Bat   and adapt it to your FB
  directory configuration. It is set to
  c:\freebasic\fbc.exe -v -s gui -i c:\freebasic\inc -p c:\freebasic\lib Fb_Tny.Bas

- run   CompileFB_Tny_Bas.Bat   to Compile   FB_Tny.Exe   (20K)
  it's the ByteCode Launcher
  
- Compile a ByteCode to test your brand new ByteCode Launcher
  Use   CmdConTest.Bas  and compile it to  CmdConTest.Bc with
  Rc.Exe and the -B  option. Or use the CmdConTest.Bc already
  in the directory

- RapidQ Compile TinyBuilder.Bas as Usual with RQ
  Run it.
  
  Your Tiny executable have been Built as
        CmdConTest.Exe (23K)
  You can Run it.

---------------------------------------------

How to add an Icon
------------------

- Just create a text file named Icon.Rc containing a single line:

        FB_PROGRAM_ICON ICON Icon_1662.ico

  Icon_1662.Ico   is in the directory

- Recompile your Launcher  FB_Tny.Bas, so that it bears that icon, with

  c:\freebasic\fbc.exe -v -s gui -i c:\freebasic\inc -p c:\freebasic\lib Fb_Tny.Bas Icon.Rc

  That's what is in file         CompileFB_Tny_Bas_With_Icon.Bat
  You can run it instead

- Run again TinyBuilder.Exe to rebuild your Tiny.exe with the new Launcher
  wearing it's Icon

- And you will have  a  Console with a ?Beautifull ModArt Icon !

- You can now Run CmdConTest.Exe with arguments to check that it works.

It works as well with a GUI code.

---------------------------------------------


