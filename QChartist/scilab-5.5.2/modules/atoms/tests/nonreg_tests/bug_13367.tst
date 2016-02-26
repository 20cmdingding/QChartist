// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2014 - Scilab Enterprises - Bruno JOFRET
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- TEST WITH ATOMS -->
//
// <-- Non-regression test for bug 13367 -->
//
// <-- Bugzilla URL -->
// http://bugzilla.scilab.org/show_bug.cgi?id=13367
//
// <-- Short Description -->
// Wrong atoms default repository

defaultRepo = atomsRepositoryList();
v = getversion("scilab");

goodRepo = sprintf("http://atoms.scilab.org/%d.%d", v(1), v(2));

assert_checkequal(defaultRepo(1), goodRepo);