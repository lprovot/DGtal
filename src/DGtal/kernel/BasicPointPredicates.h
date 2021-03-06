/**
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 **/

#pragma once

/**
 * @file BasicPointPredicates.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2010/07/10
 *
 * This files contains several basic classes representing predicates
 * on points.
 *
 * This file is part of the DGtal library.
 */

#if defined(BasicPointPredicates_RECURSES)
#error Recursive header files inclusion detected in BasicPointPredicates.h
#else // defined(BasicPointPredicates_RECURSES)
/** Prevents recursive inclusion of headers. */
#define BasicPointPredicates_RECURSES

#if !defined BasicPointPredicates_h
/** Prevents repeated inclusion of headers. */
#define BasicPointPredicates_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/BasicBoolFunctions.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class ConstantPointPredicate
  /**
   * Description of template class 'ConstantPointPredicate' <p>
   * \brief Aim: The predicate that returns always the same value boolCst
   *
   * @tparam TPoint any point type
   * @tparam boolCst any boolean value
   */
  template <typename TPoint, bool boolCst>
  struct ConstantPointPredicate
  {
    typedef TPoint Point;

    /**
     * @param p any point.
     * @return the value of the predicate at this point.
     */
    bool operator()( const Point & p ) const;

  }; // end of class ConstantPointPredicates

  /////////////////////////////////////////////////////////////////////////////
  // template class TruePointPredicate
  /**
   * Description of template class 'TruePointPredicate' <p>
   * \brief Aim: The predicate that returns always true.
   *
   * @tparam TPoint any point type
   */
  template <typename TPoint>
  struct TruePointPredicate : ConstantPointPredicate<TPoint,true>
  {
      typedef TPoint Point;
  };

  /////////////////////////////////////////////////////////////////////////////
  // template class FalsePointPredicate
  /**
   * Description of template class 'FalsePointPredicate' <p>
   * \brief Aim: The predicate that returns always false.
   *
   * @tparam TPoint any point type
   */
  template <typename TPoint>
  struct FalsePointPredicate : ConstantPointPredicate<TPoint,false>
  {
      typedef TPoint Point;
  };

  /////////////////////////////////////////////////////////////////////////////
  // template class IsLowerPointPredicate
  /**
   * Description of template class 'IsLowerPointPredicate' <p> \brief
   * Aim: The predicate returns true when the point is below (or
   * equal) the given upper bound.
   *
   * @tparam TPoint any point type
   */
  template <typename TPoint>
  struct IsLowerPointPredicate
  {
    typedef TPoint Point;
    /**
     * Constructor from upper bound.
     */
    IsLowerPointPredicate( const Point & upperBound );

    /**
     * @param p any point.
     * @return the value of the predicate at this point.
     */
    bool operator()( const Point & p ) const;

    Point myUpperBound;
  };

  /////////////////////////////////////////////////////////////////////////////
  // template class IsUpperPointPredicate
  /**
   * Description of template class 'IsUpperPointPredicate' <p> \brief
   * Aim: The predicate returns true when the point is above (or
   * equal) the given lower bound.
   *
   * @tparam TPoint any point type
   */
  template <typename TPoint>
  struct IsUpperPointPredicate
  {
    typedef TPoint Point;
    /**
     * Constructor from lower bound.
     */
    IsUpperPointPredicate( const Point & lowerBound );

    /**
     * @param p any point.
     * @return the value of the predicate at this point.
     */
    bool operator()( const Point & p ) const;

    Point myLowerBound;
  };

  /////////////////////////////////////////////////////////////////////////////
  // template class IsWithinPointPredicate
  /**
   * Description of template class 'IsWithinPointPredicate' <p> \brief
   * Aim: The predicate returns true when the point is within the given bounds.
   *
   * @tparam TPoint any point type
   */
  template <typename TPoint>
  struct IsWithinPointPredicate
  {
    typedef TPoint Point;
    /**
     * Constructor from lower bound and upper bound.
     */
    IsWithinPointPredicate( const Point & lowerBound,
			    const Point & upperBound );

    /**
     * @param p any point.
     * @return the value of the predicate at this point.
     */
    bool operator()( const Point & p ) const;

    Point myLowerBound;
    Point myUpperBound;
  };

  /////////////////////////////////////////////////////////////////////////////
  // template class NotPointPredicate
  /**
   * Description of template class 'NotPointPredicate' <p> \brief
   * Aim: The predicate returns true when the point is within the given bounds.
   *
   * @tparam TPointPredicate the predicate type.
   */
  template <typename TPointPredicate>
  struct NotPointPredicate
  {
    typedef TPointPredicate PointPredicate;
    typedef typename PointPredicate::Point Point;

    /**
     * Constructor from predicates and bool Functor.
     */
    NotPointPredicate( const PointPredicate & pred );

    /**
     * @param p any point.
     * @return the value of the predicate at this point.
     */
    bool operator()( const Point & p ) const;

    const PointPredicate & myPred;
  };

  /////////////////////////////////////////////////////////////////////////////
  // template class BinaryPointPredicate
  /**
   * Description of template class 'BinaryPointPredicate' <p> \brief
   * Aim: The predicate returns true when the point is within the given bounds.
   *
   * @tparam PointPredicate1 the left predicate type.
   * @tparam PointPredicate2 the right predicate type.
   */
  template <typename TPointPredicate1, typename TPointPredicate2>
  struct BinaryPointPredicate
  {
    typedef TPointPredicate1 PointPredicate1;
    typedef TPointPredicate2 PointPredicate2;
    typedef typename PointPredicate1::Point Point;
    // should be the same.
    typedef typename PointPredicate2::Point Point2;

    /**
     * Constructor from predicates and bool Functor.
     */
    BinaryPointPredicate( const PointPredicate1 & pred1,
			  const PointPredicate2 & pred2,
			  const BoolFunction2 & boolFunctor );

    /**
     * @param p any point.
     * @return the value of the predicate at this point.
     */
    bool operator()( const Point & p ) const;

    const PointPredicate1 & myPred1;
    const PointPredicate2 & myPred2;
    BoolFunction2 myBoolFunctor;
  };

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/kernel/BasicPointPredicates.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined BasicPointPredicates_h

#undef BasicPointPredicates_RECURSES
#endif // else defined(BasicPointPredicates_RECURSES)
