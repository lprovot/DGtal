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
 * @file SpaceND.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2010/05/14
 *
 * Header file for module SpaceND.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(SpaceND_RECURSES)
#error Recursive header files inclusion detected in SpaceND.h
#else // defined(SpaceND_RECURSES)
/** Prevents recursive inclusion of headers. */
#define SpaceND_RECURSES

#if !defined SpaceND_h
/** Prevents repeated inclusion of headers. */
#define SpaceND_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/kernel/CInteger.h"
#include "DGtal/kernel/CUnsignedInteger.h"
#include "DGtal/kernel/CSignedInteger.h"
#include "DGtal/kernel/PointVector.h"
#include "DGtal/kernel/RealPointVector.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // class SpaceND
  /**
   * Description of class 'SpaceND' <p>
   *
   * Aim: SpaceND defines the fundamental structure of a Digital Space in ND.
   *
   * This class just defines fundamental types associated to a digital
   * space in dimension n. For instance, it specifies the type of a
   * Point lying in this space, the type of a Vector or the type of subspace.
   * 
   * @tparam dim static constant of type DGtal::Dimension that
   * specifies the static  dimension of the space.
   * @tparam Integer specifies the integer number type to use as a
   * ring for the computations or as coordinates type. Integer must be
   * a model of CInteger and CSignedInteger concepts.  
   * 
   * Example of use:
   *@code
   
#include <DGtal/kernel/SpaceND.h>

//...

//We define the type of a digital domain on dimension 4 using the
//"int" arithmetic ring.

typedef SpaceND<4, int> Space4Int;
   
//We deduce the type to represent points in this space
typedef Space4::Point Point4Int;

//and we use it (see PointVector documentation).
Point4Int a= {2, 3 , -5 , 6};
   @endcode
   *
   **/

  template < Dimension dim,
	     typename TInteger = DGtal::int32_t >
  class SpaceND
  {
    //Integer must be a model of the concept CInteger.
    BOOST_CONCEPT_ASSERT(( CInteger<TInteger> ) );
 
   //Integer must be signed to characterize a ring.
    BOOST_CONCEPT_ASSERT(( CSignedInteger<TInteger> ) );

  public:
    ///Arithmetic ring induced by (+,-,*) and Integre numbers.
    typedef TInteger Integer;
    ///Unsigned version of the Integers.
    typedef typename IntegerTraits<Integer>::UnsignedVersion UnsignedInteger;
    
    ///Type used to represent sizes in the digital space.
    typedef UnsignedInteger Size;
    
    
    ///Points in DGtal::SpaceND.
    typedef PointVector<dim,Integer> Point;

    ///Vectors in DGtal::SpaceND.
    typedef PointVector<dim,Integer> Vector;

    ///Point with "double" as  coordinate type with the same dimension
    ///as SpaceND.
    typedef RealPointVector<dim> RealPoint;
    
    ///Point with "double" as  coordinate type with the same dimension
    ///as SpaceND.
    typedef RealPointVector<dim> RealVector;

    ///Type to denote the space itself.
    typedef SpaceND<dim, Integer> Space;

    ///Copy of the type used for the  dimension.
    typedef DGtal::Dimension Dimension;
    
    ///static constants to store the dimension.
    static const Dimension dimension = dim;

    ///Define the type of a sub co-Space
    template <Dimension codimension>
    struct Subcospace
    {
      typedef SpaceND < dim - codimension, Integer > Type;
    };
   
    ///Define the type of a subspace.
    template <Dimension subdimension>
    struct Subspace
    {
      typedef SpaceND<subdimension, Integer> Type;
    };


    // ----------------------- Standard services ------------------------------
  public:

    /**
     * Constructor
     *
     */
    SpaceND() {};

    /**
     * Destructor.
     */
    ~SpaceND() {};

    /**
     * @return the digital space of specified subdimension of this space.
     */
    template <Dimension subdimension>
    static
    typename Subspace<subdimension>::Type subspace()
    {
      ASSERT( subdimension <= dim );
      return SpaceND<subdimension, Integer>();
    }


    /**
     * @return the digital space of specified codimension of this space.
     */
    template <Dimension codimension>
    static
    typename Subcospace<codimension>::Type subcospace()
    {
      ASSERT( codimension <= dim );
      return SpaceND < dim - codimension, Integer > ();
    }


    // ----------------------- Interface --------------------------------------
  public:

    /**
     * Writes/Displays the object on an output stream.
     * @param out the output stream where the object is written.
     */
    static void selfDisplay( std::ostream & out )
    {
      out << "[SpaceND dim=" << dimension << " size of Integers=" << sizeof( Integer ) << " ]";
    }

  private:
    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     * Forbidden by default.
     */
    SpaceND & operator=( const SpaceND & other );

    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class SpaceND


  /**
   * Overloads 'operator<<' for displaying objects of class 'SpaceND'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'SpaceND' to write.
   * @return the output stream after the writing.
   */
  template <Dimension dim, typename Integer>
  static std::ostream&
  operator<<( std::ostream & out, const SpaceND<dim, Integer> & object )
  {
    object.selfDisplay( out );
    return out;
  }


} // namespace DGtal


//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined SpaceND_h

#undef SpaceND_RECURSES
#endif // else defined(SpaceND_RECURSES)
