/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*- */
/*
 *  Main authors:
 *     Christian Schulte <schulte@gecode.org>
 *
 *  Copyright:
 *     Christian Schulte, 2004
 *
 *  Last modified:
 *     $Date: 2016-05-23 22:18:23 +0200 (Mon, 23 May 2016) $ by $Author: schulte $
 *     $Revision: 15073 $
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

#include <gecode/int/element.hh>

namespace Gecode {

  void
  element(Home home, IntSharedArray c, IntVar x0, IntVar x1,
          IntPropLevel) {
    using namespace Int;
    if (c.size() == 0)
      throw TooFewArguments("Int::element");
    GECODE_POST;
    for (int i = c.size(); i--; )
      Limits::check(c[i],"Int::element");
    GECODE_ES_FAIL((Element::post_int<IntView,IntView>(home,c,x0,x1)));
  }

  void
  element(Home home, IntSharedArray c, IntVar x0, BoolVar x1,
          IntPropLevel) {
    using namespace Int;
    if (c.size() == 0)
      throw TooFewArguments("Int::element");
    GECODE_POST;
    for (int i = c.size(); i--; )
      Limits::check(c[i],"Int::element");
    GECODE_ES_FAIL((Element::post_int<IntView,BoolView>(home,c,x0,x1)));
  }

  void
  element(Home home, IntSharedArray c, IntVar x0, int x1,
          IntPropLevel) {
    using namespace Int;
    if (c.size() == 0)
      throw TooFewArguments("Int::element");
    Limits::check(x1,"Int::element");
    GECODE_POST;
    for (int i = c.size(); i--; )
      Limits::check(c[i],"Int::element");
    ConstIntView cx1(x1);
    GECODE_ES_FAIL(
                   (Element::post_int<IntView,ConstIntView>(home,c,x0,cx1)));
  }

  void
  element(Home home, const IntVarArgs& c, IntVar x0, IntVar x1,
          IntPropLevel ipl) {
    using namespace Int;
    if (c.size() == 0)
      throw TooFewArguments("Int::element");
    GECODE_POST;
    IdxViewArray<IntView> iv(home,c);
    if ((vbd(ipl) == IPL_DOM) || (vbd(ipl) == IPL_DEF)) {
      GECODE_ES_FAIL((Element::ViewDom<IntView,IntView,IntView>
                           ::post(home,iv,x0,x1)));
    } else {
      GECODE_ES_FAIL((Element::ViewBnd<IntView,IntView,IntView>
                           ::post(home,iv,x0,x1)));
    }
  }

  void
  element(Home home, const IntVarArgs& c, IntVar x0, int x1,
          IntPropLevel ipl) {
    using namespace Int;
    if (c.size() == 0)
      throw TooFewArguments("Int::element");
    Limits::check(x1,"Int::element");
    GECODE_POST;
    IdxViewArray<IntView> iv(home,c);
    ConstIntView v1(x1);
    if ((vbd(ipl) == IPL_DOM) || (vbd(ipl) == IPL_DEF)) {
      GECODE_ES_FAIL((Element::ViewDom<IntView,IntView,ConstIntView>
                           ::post(home,iv,x0,v1)));
    } else {
      GECODE_ES_FAIL((Element::ViewBnd<IntView,IntView,ConstIntView>
                           ::post(home,iv,x0,v1)));
    }
  }

  void
  element(Home home, const BoolVarArgs& c, IntVar x0, BoolVar x1,
          IntPropLevel) {
    using namespace Int;
    if (c.size() == 0)
      throw TooFewArguments("Int::element");
    GECODE_POST;
    IdxViewArray<BoolView> iv(home,c);
    GECODE_ES_FAIL((Element::ViewBnd<BoolView,IntView,BoolView>
                         ::post(home,iv,x0,x1)));
  }

  void
  element(Home home, const BoolVarArgs& c, IntVar x0, int x1,
          IntPropLevel) {
    using namespace Int;
    if (c.size() == 0)
      throw TooFewArguments("Int::element");
    Limits::check(x1,"Int::element");
    GECODE_POST;
    IdxViewArray<BoolView> iv(home,c);
    ConstIntView v1(x1);
    GECODE_ES_FAIL((Element::ViewBnd<BoolView,IntView,ConstIntView>
                         ::post(home,iv,x0,v1)));
  }

  namespace {
    IntVar
    pair(Home home, IntVar x, int w, IntVar y, int h) {
      IntVar xy(home,0,w*h-1);
      if (Int::Element::Pair::post(home,x,y,xy,w,h) != ES_OK)
        home.fail();
      return xy;
    }
  }

  void
  element(Home home, IntSharedArray a,
          IntVar x, int w, IntVar y, int h, IntVar z,
          IntPropLevel ipl) {
    using namespace Int;
    if (a.size() != w*h)
      throw Int::ArgumentSizeMismatch("Int::element");
    GECODE_POST;
    element(home, a, pair(home,x,w,y,h), z, ipl);
  }

  void
  element(Home home, IntSharedArray a,
          IntVar x, int w, IntVar y, int h, BoolVar z,
          IntPropLevel ipl) {
    using namespace Int;
    if (a.size() != w*h)
      throw Int::ArgumentSizeMismatch("Int::element");
    GECODE_POST;
    element(home, a, pair(home,x,w,y,h), z, ipl);
  }

  void
  element(Home home, const IntVarArgs& a,
          IntVar x, int w, IntVar y, int h, IntVar z,
          IntPropLevel ipl) {
    using namespace Int;
    if (a.size() != w*h)
      throw Int::ArgumentSizeMismatch("Int::element");
    GECODE_POST;
    element(home, a, pair(home,x,w,y,h), z, ipl);
  }

  void
  element(Home home, const BoolVarArgs& a,
          IntVar x, int w, IntVar y, int h, BoolVar z,
          IntPropLevel ipl) {
    using namespace Int;
    if (a.size() != w*h)
      throw Int::ArgumentSizeMismatch("Int::element");
    GECODE_POST;
    element(home, a, pair(home,x,w,y,h), z, ipl);
  }

}

// STATISTICS: int-post
