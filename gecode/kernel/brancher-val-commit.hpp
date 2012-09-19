/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*- */
/*
 *  Main author:
 *     Christian Schulte <schulte@gecode.org>
 *
 *  Copyright:
 *     Christian Schulte, 2012
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

namespace Gecode {

  /**
   * \defgroup TaskBranchValCommit Generic value commit for brancher based on view and value selection
   *
   * \ingroup TaskBranchViewVal
   */
  //@{
  /// Base class for value commit
  template<class _View, class _Val>
  class ValCommit {
  public:
    /// View type
    typedef _View View;
    /// Value type
    typedef _Val Val;
  public:
    /// Constructor for initialization
    ValCommit(Space& home, const ValBranch& vb);
    /// Constructor for cloning
    ValCommit(Space& home, bool shared, ValCommit<View,Val>& vs);
    /// Whether dispose must always be called (that is, notice is needed)
    bool notice(void) const;
    /// Delete value commit
    void dispose(Space& home);
  };

  /// Class for user-defined value commit
  template<class View>
  class ValCommitFunction : public 
  ValCommit<View,
            typename BranchTraits<typename View::VarType>::ValType> {
  public:
    /// The corresponding variable type
    typedef typename View::VarType Var;
    /// The corresponding commit function
    typedef typename BranchTraits<Var>::Commit CommitFunction;
  protected:
    /// The user-defined commit function
    CommitFunction c;
  public:
    /// Constructor for initialization
    ValCommitFunction(Space& home, const ValBranch& vb);
    /// Constructor for cloning during copying
    ValCommitFunction(Space& home, bool shared, ValCommitFunction& vc);
    /// Perform user-defined commit
    ModEvent commit(Space& home, unsigned int a, View x, Val n);
  };
  //@}

  // Baseclass for value commit
  template<class View, class Val>
  forceinline
  ValCommit<View,Val>::ValCommit(Space&, const ValBranch&) {}
  template<class View, class Val>
  forceinline
  ValCommit<View,Val>::ValCommit(Space&, bool, ValCommit<View,Val>&) {}
  template<class View, class Val>
  forceinline bool
  ValCommit<View,Val>::notice(void) const {
    return false;
  }
  template<class View, class Val>
  forceinline void
  ValCommit<View,Val>::dispose(Space&) {}


  // User-defined value selection
  template<class View>
  forceinline
  ValCommitFunction<View>::ValCommitFunction(Space& home, 
                                             const ValBranch& vb) 
    : ValCommit<View,Val>(home,vb),
      c(function_cast<CommitFunction>(vb.commit())) {}
  template<class View>
  forceinline
  ValCommitFunction<View>::ValCommitFunction(Space& home, bool shared, 
                                             ValCommitFunction<View>& vc) 
    : ValCommit<View,Val>(home,shared,vc), c(vc.c) {}
  template<class View>
  forceinline ModEvent
  ValCommitFunction<View>::commit(Space& home, unsigned int a, View x, Val n) {
    c(home,a,x,n);
    return home.failed() ? ES_FAILED : ES_OK;
  }

}

// STATISTICS: kernel-branch