// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2008 - INRIA - Pierre MARECHAL <pierre.marechal@scilab.org>
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================
// <-- NO CHECK ERROR OUTPUT -->
// <-- NEED JVM -->

// xmltops

// TEST 1 (french help and english help are complete)
// =============================================================================

tmpPath = TMPDIR + "/examples";
copyfile("SCI/modules/helptools/examples", tmpPath);
my_module_path = pathconvert(tmpPath + "/example_1",%f,%f);

// Build the french help

setlanguage("fr_FR");
my_french_help_dir    =  my_module_path+"/help/fr_FR";
my_french_help_title  =  "TEST 1 [fr_FR]";
xmltops(my_french_help_dir,my_french_help_title,"fr_FR");

ps_info =  fileinfo(my_module_path+"/ps/scilab_fr_FR_help.ps");
if ps_info == [] then pause, end       // file existence
if ps_info(1) < 30000 then pause, end   // file size

clean_help(my_french_help_dir);

// Build the english help

setlanguage("en_US");
my_english_help_dir    =  my_module_path+"/help/en_US";
my_english_help_title  =  "TEST 1 [en_US]";
xmltops(my_english_help_dir,my_english_help_title,'en_US');

ps_info =  fileinfo(my_module_path+"/ps/scilab_en_US_help.ps");
if ps_info == [] then pause, end       // file existence
if ps_info(1) < 30000 then pause, end   // file size

clean_help(my_english_help_dir);



// TEST 2 (example_2_function_2 and example_2_function_4 are missing in the
//         french help)
// =============================================================================

my_module_path = pathconvert(tmpPath + "/example_2",%f,%f);

// Build the french help

setlanguage("fr_FR");
my_french_help_dir    =  my_module_path+"/help/fr_FR";
my_french_help_title  =  "TEST 2 [fr_FR]";
xmltops(my_french_help_dir,my_french_help_title,'fr_FR');

ps_info =  fileinfo(my_module_path+"/ps/scilab_fr_FR_help.ps");
if ps_info == [] then pause, end       // file existence
if ps_info(1) < 30000 then pause, end   // file size

clean_help(my_french_help_dir);

// Build the english help

setlanguage("en_US");
my_english_help_dir    =  my_module_path+"/help/en_US";
my_english_help_title  =  "TEST 2 [en_US]";
xmltops(my_english_help_dir,my_english_help_title,'en_US');

ps_info =  fileinfo(my_module_path+"/ps/scilab_en_US_help.ps");
if ps_info == [] then pause, end       // file existence
if ps_info(1) < 30000 then pause, end   // file size

clean_help(my_english_help_dir);



// TEST 3 (example_3_function_3 and example_3_function_4 are missing in the
//         english help)
// =============================================================================

my_module_path = pathconvert(tmpPath + "/example_3",%f,%f);

// Build the french help

setlanguage("fr_FR");
my_french_help_dir    =  my_module_path+"/help/fr_FR";
my_french_help_title  =  "TEST 3 [fr_FR]";
xmltops(my_french_help_dir,my_french_help_title,"fr_FR");

ps_info =  fileinfo(my_module_path+"/ps/scilab_fr_FR_help.ps");
if ps_info == [] then pause, end       // file existence
if ps_info(1) < 30000 then pause, end   // file size

clean_help(my_french_help_dir);

// Build the english help

setlanguage("en_US");
my_english_help_dir    =  my_module_path+"/help/en_US";
my_english_help_title  =  "TEST 3 [en_US]";
xmltops(my_english_help_dir,my_english_help_title,"en_US","fr_FR");

ps_info =  fileinfo(my_module_path+"/ps/scilab_en_US_help.ps");
if ps_info == [] then pause, end       // file existence
if ps_info(1) < 30000 then pause, end   // file size

clean_help(my_english_help_dir);
