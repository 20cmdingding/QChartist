// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2008-2008 - INRIA - Sylvestre Koumar
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- TEST WITH GRAPHIC -->

// <-- Non-regression test for bug 2914 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=2914
//
// <-- Short Description -->
// some values on polar axes have been removed (to compare with scilab 4.1.2)
// see help polarplot
// the same bug was reported for "contour()"

polarplot()
//contour()
a = gca();
 
function TextChildren(a)

    children = a.children;
	for k=1:size(children, 1)
		handle = children(k);
		if(handle.type == "Text") then
		  if(handle.clip_state <> "off") then pause, end
		end
        TextChildren(children(k));
	end	
	
endfunction

TextChildren(a);
