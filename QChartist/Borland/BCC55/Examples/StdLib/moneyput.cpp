#include "stlexam.h"
#pragma hdrstop
/**************************************************************************
 *
 * moneyput.cpp - Example program for the money_put facet. 
 *                See Class Reference Section
 *
 ***************************************************************************
 *
 * (c) Copyright 1994, 1998 Rogue Wave Software, Inc.
 * ALL RIGHTS RESERVED
 *
 * The software and information contained herein are proprietary to, and
 * comprise valuable trade secrets of, Rogue Wave Software, Inc., which
 * intends to preserve as trade secrets such software and information.
 * This software is furnished pursuant to a written license agreement and
 * may be used, copied, transmitted, and stored only in accordance with
 * the terms of such license and with the inclusion of the above copyright
 * notice.  This software and information or any other copies thereof may
 * not be provided or otherwise made available to any other person.
 *
 * Notwithstanding any other lease or license that may pertain to, or
 * accompany the delivery of, this computer software and information, the
 * rights of the Government regarding its use, reproduction and disclosure
 * are as set forth in Section 52.227-19 of the FARS Computer
 * Software-Restricted Rights clause.
 * 
 * Use, duplication, or disclosure by the Government is subject to
 * restrictions as set forth in subparagraph (c)(1)(ii) of the Rights in
 * Technical Data and Computer Software clause at DFARS 252.227-7013.
 * Contractor/Manufacturer is Rogue Wave Software, Inc.,
 * P.O. Box 2328, Corvallis, Oregon 97339.
 *
 * This computer software and information is distributed with "restricted
 * rights."  Use, duplication or disclosure is subject to restrictions as
 * set forth in NASA FAR SUP 18-52.227-79 (April 1985) "Commercial
 * Computer Software-Restricted Rights (April 1985)."  If the Clause at
 * 18-52.227-74 "Rights in Data General" is specified in the contract,
 * then the "Alternate III" clause applies.
 *
 **************************************************************************/

#include <string>

#include <locale>
#include <iostream>

int main ()
{
#ifndef _RWSTD_NO_NAMESPACE
  using namespace std;
#endif

  typedef ostreambuf_iterator<char,char_traits<char> > iter_type;
  
  locale loc;
  string buffer("10002");
  long double ldval = 10002; 

  // Construct a ostreambuf_iterator on cout
  iter_type begin(cout);

  // Get a money put facet
  const money_put<char,iter_type>& mp = 
#ifndef _RWSTD_NO_TEMPLATE_ON_RETURN_TYPE
    use_facet<money_put<char,iter_type> >(loc);
#else
    use_facet(loc,(money_put<char,iter_type>*)0);
#endif

  // Put out the string representation of the monetary value
  cout << buffer << " --> ";
  mp.put(begin,false,cout,' ',buffer);

  // Put out the long double representation of the monetary value
  cout << endl << ldval << " --> ";
  mp.put(begin,false,cout,' ',ldval);

  cout <<  endl;

  return 0;
}

