// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2012 - DIGITEO - Vincent COUVERT
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- TEST WITH GRAPHIC -->

// Create a default figure
function resizeMe()
  disp("resize");
endfunction

f = scf();
assert_checkequal(f.resizefcn, "");
f.resizefcn = "resizeMe()";
assert_checkequal(f.resizefcn, "resizeMe()");

// Try with wrong values
refMsg = msprintf(_("Wrong type for ''%s'' property: String expected.\n"), "resizefcn");
assert_checkerror("f = gcf();f.resizefcn = 10;", refMsg);
refMsg = msprintf(_("%s: Wrong size for input argument #%d: A single string expected.\n"), "set", 3);
assert_checkerror("f = gcf();f.resizefcn = [""resizeMe()"" ""resizeMe()""];", refMsg);

// Test for other handles
refMsg = msprintf(_("''%s'' property does not exist for this handle.\n"), "resizefcn");
assert_checkerror("a = gca();a.resizefcn = ""resizeMe()""", refMsg); // set
assert_checkerror("a = gca();v = a.resizefcn;", refMsg); // get

// Save/Load (V5)
warning("off");
save(TMPDIR + "/figure.resizefcn.bin", f);
warning("on");
delete(f);
clear f
load(TMPDIR + "/figure.resizefcn.bin");
assert_checkequal(f.resizefcn, "resizeMe()");

// Save/Load (SOD)
save(TMPDIR + "/figure.resizefcn.bin", "f");
delete(f);
clear f
load(TMPDIR + "/figure.resizefcn.bin");
assert_checkequal(f.resizefcn, "resizeMe()");
