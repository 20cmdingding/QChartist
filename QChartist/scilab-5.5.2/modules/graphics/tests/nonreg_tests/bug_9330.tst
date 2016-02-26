// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2011 - DIGITEO - Vincent COUVERT
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- TEST WITH GRAPHIC -->

// <-- Non-regression test for bug 9330 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=9330
//
// <-- Short Description -->
// delete() called overloading instead of deleting the current graphic entity.

plot();
f = gcf();
delete();
delete();
delete();
assert_checkequal(is_handle_valid(f), %F);