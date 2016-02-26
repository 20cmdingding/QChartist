// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2008-2009 - INRIA - Michael Baudin
// Copyright (C) 2009-2010 - DIGITEO - Michael Baudin
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2.1-en.txt

//
// optimsimplex_getallx --
//   Returns all the coordinates of all the vertices.
//   The vertex #k is stored in x(1:n,k)
//   with k = 1 , nbve
// Arguments
//   <no arg>
//
function x = optimsimplex_getallx ( this )
    if typeof(this) <> "TSIMPLEX" then
        error(msprintf(gettext("%s: Wrong type for input argument #%d: TSIMPLEX expected.\n"), "optimsimplex_getallx", 1));
    end
    x = this.x ( 1:this.nbve , 1:this.n )
endfunction
