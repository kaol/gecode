/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*- */
/*
 *  Main authors:
 *     Christian Schulte <schulte@gecode.org>
 *
 *  Copyright:
 *     Christian Schulte, 2002
 *
 *  Last modified:
 *     $Date$ by $Author$
 *     $Revision$
 *
 *  This file is part of Gecode, the generic constraint
 *  development environment:
 *     http://www.gecode.org
 *
 *  Permission is hereby granted, free of charge, to any person obtaining
 *  a copy of this software and associated documentation files (the
 *  "Software"), to deal in the Software without restriction, including
 *  without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to
 *  permit persons to whom the Software is furnished to do so, subject to
 *  the following conditions:
 *
 *  The above copyright notice and this permission notice shall be
 *  included in all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 *  LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 *  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 *  WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#include "gecode/int.hh"

namespace Gecode {

  IntVarArray::IntVarArray(Space* home, int n, int min, int max)
    : VarArray<IntVar>(home,n) {
    if ((min < Limits::Int::int_min) || (max > Limits::Int::int_max))
      throw Int::VariableOutOfRangeDomain("IntVarArray");
    if (min > max)
      throw Int::VariableEmptyDomain("IntVarArray");
    for (int i = size(); i--; )
      x[i]._init(home,min,max);
  }

  IntVarArray::IntVarArray(Space* home, int n, const IntSet& s)
    : VarArray<IntVar>(home,n) {
    if ((s.min() < Limits::Int::int_min) || (s.max() > Limits::Int::int_max))
      throw Int::VariableOutOfRangeDomain("IntVarArray");
    if (s.size() == 0)
      throw Int::VariableEmptyDomain("IntVarArray");
    for (int i = size(); i--; )
      x[i]._init(home,s);
  }

  BoolVarArray::BoolVarArray(Space* home, int n, int min, int max)
    : VarArray<BoolVar>(home, n) {
    if ((min < 0) || (max > 1))
      throw Int::VariableOutOfRangeDomain("BoolVarArray");
    if (min > max)
      throw Int::VariableEmptyDomain("BoolVarArray");
    for (int i = size(); i--; )
      x[i]._init(home,min,max);
  }

}

// STATISTICS: int-post
