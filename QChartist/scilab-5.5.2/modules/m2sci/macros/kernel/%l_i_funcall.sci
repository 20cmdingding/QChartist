// Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
// Copyright (C) 2002-2004 - INRIA - Vincent COUVERT
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2.1-en.txt

function funcall=%l_i_funcall(field,inslist,funcall)
    if field=="dims" then
        funcall.lhs(1).dims=inslist
    elseif field=="type" then
        funcall.lhs(1).type=inslist
    else
        error(gettext("Not yet implemented."))
    end
endfunction
