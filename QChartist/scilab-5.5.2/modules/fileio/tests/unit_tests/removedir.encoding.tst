// ============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2008 - INRIA - Sylvestre Ledru
//
//  This file is distributed under the same license as the Scilab package.
// ============================================================================

// <-- JVM MANDATORY -->

// ============================================================================
// Unitary tests for removedir function
// ============================================================================

chdir(TMPDIR);

warning("off");
a = createdir("test_removedir");
if(a <> %T) then pause, end

cd("test_removedir");
exec(SCI+"/modules/localization/tests/unit_tests/CreateDir.sce", -1);

chdir(TMPDIR);
b = removedir("test_removedir");
if (b <> %T) then pause,end
if(isdir("test_removedir") <> %F) then pause, end

