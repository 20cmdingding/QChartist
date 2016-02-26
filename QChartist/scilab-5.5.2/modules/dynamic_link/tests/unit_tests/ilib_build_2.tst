// =============================================================================
// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2008 - DIGITEO - Allan CORNET
// Copyright (C) 2009 - DIGITEO
//
//  This file is distributed under the same license as the Scilab package.
// =============================================================================

// <-- ENGLISH IMPOSED -->
// <-- CLI SHELL MODE -->

if getos() == 'Windows' then
  TMP_OS_DIR = getenv('TMP','err');
  if (TMP_OS_DIR == 'err') then pause,end;
else
  TMP_OS_DIR = '/tmp';
  if ~isdir(TMP_OS_DIR) then pause,end;
end

TMP_DIR = TMP_OS_DIR+filesep()+'ilib_build_2';

rmdir(TMP_DIR,'s');
mkdir(TMP_OS_DIR,'ilib_build_2');


if ~isdir(TMP_DIR) then pause,end;


//Here with give a complete example on adding new primitive to Scilab
//create the procedure files

f1=['void c_sum(double *a,double *b, double *sum)'
    '{*sum=*a + *b;}'];

mputl(f1,TMP_DIR+filesep()+'c_sum.c');

f2=['void c_sub(double *a,double *b, double *sub)'
    '{*sub=*a - *b;}'];
mputl(f2,TMP_DIR+filesep()+'c_sub.c');

//creating the interface file
i=['#define __USE_DEPRECATED_STACK_FUNCTIONS__'
   '#include ""stack-c.h""'
   'extern void c_sum(double *a,double *b, double *sum);'
   'int sci_csum(char *fname)' 
   '{'
   '  int m1 = 0, n1 = 0, l1 = 0;'
   '  int m2 = 0, n2 = 0, l2 = 0;'
   '  int m3 = 0, n3 = 0, l3 = 0;'
   '  CheckRhs(1,2);'
   '  CheckLhs(1,1);'
   '  GetRhsVar(1, ""d"", &m1, &n1, &l1);'
   '  GetRhsVar(2, ""d"", &m2, &n2, &l2);'
   '  m3=1;n3=1;'
   '  CreateVar(Rhs+1,""d"",&m3,&n3,&l3);'
   '  c_sum(stk(l1),stk(l2),stk(l3));'
   '  LhsVar(1) = Rhs+1;'
   '  return 0;'
   '}'];
mputl(i,TMP_DIR+filesep()+'sci_csum.c');

//creating the interface file
j=['#define __USE_DEPRECATED_STACK_FUNCTIONS__'
   '#include ""stack-c.h""'
   'extern void c_sub(double *a,double *b, double *sum);'
   'int sci_csub(char *fname)' 
   '{'
   '  int m1 = 0, n1 = 0, l1 = 0;'
   '  int m2 = 0, n2 = 0, l2 = 0;'
   '  int m3 = 0, n3 = 0, l3 = 0;'
   '  CheckRhs(1,2);'
   '  CheckLhs(1,1);'
   '  GetRhsVar(1, ""d"", &m1, &n1, &l1);'
   '  GetRhsVar(2, ""d"", &m2, &n2, &l2);'
   '  m3=1;n3=1;'
   '  CreateVar(Rhs+1,""d"",&m3,&n3,&l3);'
   '  c_sub(stk(l1),stk(l2),stk(l3));'
   '  LhsVar(1) = Rhs+1;'
   '  return 0;'
   '}'];
mputl(j,TMP_DIR+filesep()+'sci_csub.c');


cur_dir = pwd();
chdir(TMP_DIR);

//creating the shared library (a gateway, a Makefile and a loader are 
//generated. 

files=['c_sub.c','sci_csub.c','c_sum.c','sci_csum.c'];
ilib_build('foo',['c_sum','sci_csum';'c_sub','sci_csub'],files,[]);


// load the shared library 
exec loader.sce;

if c_sum(3,5) <> 8 then pause,end
if c_sub(3,5) <> -2 then pause,end

chdir(cur_dir);

// ulink() all libraries
ulink();


//remove TMP_DIR
rmdir(TMP_DIR,'s');
