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
 * @file ArithmeticalDSS3d.h @author Tristan Roussillon (\c
 * tristan.roussillon@liris.cnrs.fr ) Laboratoire d'InfoRmatique en
 * Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS,
 * France
 *
 * @date 2011/06/01
 *
 * Header file for module ArithmeticalDSS3d.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(ArithmeticalDSS3d_RECURSES)
#error Recursive header files inclusion detected in ArithmeticalDSS3d.h
#else // defined(ArithmeticalDSS3d_RECURSES)
/** Prevents recursive inclusion of headers. */
#define ArithmeticalDSS3d_RECURSES

#if !defined ArithmeticalDSS3d_h
/** Prevents repeated inclusion of headers. */
#define ArithmeticalDSS3d_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <list>
#include "DGtal/base/Exceptions.h"
#include "DGtal/base/Common.h"
#include "DGtal/kernel/PointVector.h"
#include "DGtal/kernel/CInteger.h"
#include "DGtal/geometry/2d/ArithmeticalDSS.h"
//////////////////////////////////////////////////////////////////////////////


namespace DGtal
{


  /////////////////////////////////////////////////////////////////////////////
  // class ArithmeticalDSS3d
  /**
   * Description of class 'ArithmeticalDSS3d' <p>
   * \brief Aim:
   * Dynamic recognition of a 3d-digital straight segment (DSS)
   * \todo

   * @endcode
   */
  template <typename TIterator, typename TInteger, int connectivity>
  class ArithmeticalDSS3d
  {


    // ----------------------- Types ------------------------------
  public:


    typedef TIterator Iterator;
		typedef std::reverse_iterator<Iterator> ReverseIterator;
		typedef ArithmeticalDSS3d<ReverseIterator,TInteger,connectivity> ReverseSegmentComputer; 

    //entier
    BOOST_CONCEPT_ASSERT(( CInteger<TInteger> ) );
    typedef TInteger Integer;



    //points and vectors
    typedef DGtal::PointVector<2,Integer> Point2d;
    typedef DGtal::PointVector<3,Integer> Point3d;
  


    //////////////////////////////////////////////////////////////////////////////
    // adapter for iterator
		template <typename TIt>
		class XYIteratorAdapter 
		{
			protected:
				TIt myIt;
			public:
				//constructors
				XYIteratorAdapter() {}
				XYIteratorAdapter(const TIt& it):myIt(it) {}
				//dereference operator
		    Point2d operator*() const {
					Point3d tmp = *myIt;
					return Point2d(tmp.at(0),tmp.at(1));
		    }
		};
		template <typename TIt>
		class XZIteratorAdapter
		{
			protected:
				TIt myIt;
			public:
				//constructors
				XZIteratorAdapter() {}
				XZIteratorAdapter(const TIt& it):myIt(it) {}
				//dereference operator
		    Point2d operator*() const {
					Point3d tmp = *myIt;
					return Point2d(tmp.at(0),tmp.at(2));
		    }
		};
		template <typename TIt>
		class YZIteratorAdapter 
		{
			protected:
				TIt myIt;
			public:
				//constructors
				YZIteratorAdapter() {}
				YZIteratorAdapter(const TIt& it):myIt(it) {}
				//dereference operator
		    Point2d operator*() const {
					Point3d tmp = *myIt;
					return Point2d(tmp.at(1),tmp.at(2));
		    }
		};

		//2d-arithmeticalDSS recognition algorithms
		typedef DGtal::ArithmeticalDSS<XYIteratorAdapter<TIterator>,
																		TInteger,
																		connectivity> XYArithmeticalDSS;
		typedef DGtal::ArithmeticalDSS<XZIteratorAdapter<TIterator>,
																		TInteger,
																		connectivity> XZArithmeticalDSS;
		typedef DGtal::ArithmeticalDSS<YZIteratorAdapter<TIterator>,
																		TInteger,
																		connectivity> YZArithmeticalDSS;

    // ----------------------- Standard services ------------------------------
  public:


    /**
     * Default constructor.
     * not valid
     */
    ArithmeticalDSS3d();

    /**
     * Constructor with initialisation
     * @param it an iterator on a sequence of points
     */
    ArithmeticalDSS3d(const Iterator& it);

    /**
     * Initialisation.
     * @param it an iterator on a sequence of points
     */
    void init(const Iterator& it);


    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    ArithmeticalDSS3d ( const ArithmeticalDSS3d & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     */
    ArithmeticalDSS3d & operator= ( const ArithmeticalDSS3d & other );

    /**
     * Equality operator.
     * @param other the object to compare with.
     * @return 'true' either if the leaning points perfectly match
     * or if the first leaning points match to the last ones
     * (same DSS scanned in the reverse way) 
     * and 'false' otherwise
     */
    bool operator==( const ArithmeticalDSS3d & other ) const;

    /**
     * Difference operator.
     * @param other the object to compare with.
     * @return 'false' if equal
     * 'true' otherwise
     */
    bool operator!=( const ArithmeticalDSS3d & other ) const;

    /**
     * Destructor.
     */
    ~ArithmeticalDSS3d(){};

    // ----------------------- Interface --------------------------------------
  public:
     

    /**
     * Tests whether the union between a point 
     * (adding to the front of the DSS 
     * with respect to the scan orientaion) 
     * and a DSS is a DSS. 
     * Computes the parameters of the new DSS 
     * with the adding point if true.
     * @param itf an iterator on a sequence of points
     * @return 'true' if the union is a DSS, 'false' otherwise.
     */
    bool extend(const Iterator & it);


    // ------------------------- Accessors ------------------------------

    /**
     * Checks the validity/consistency of the object.
     * @return 'true' if the object is valid, 'false' otherwise.
     */
    bool isValid() const;

    // ------------------ Display ------------------------------------------

  public:
    
    /**
     * @return the style name used for drawing this object.
     */
    std::string styleName() const;

    /**
     * Writes/Displays the object on an output stream.
     * @param out the output stream where the object is written.
     */
    void selfDisplay ( std::ostream & out ) ;

    
 
	#ifdef WITH_VISU3D_QGLVIEWER

    /**
     * Default drawing style object.
     * @return the dyn. alloc. default style for this object.
     */
    DrawableWithDGtalQGLViewer* defaultStyleQGL( std::string mode = "" ) const;

    /**
     * Draw the object with QGLViewer
     * @param viewer the output where the object is drawn.
     */
    void selfDrawQGL ( DGtalQGLViewer & viewer ) const;
    void selfDrawAsPavingQGL( DGtalQGLViewer & viewer ) const;
 
 #endif





    // ------------------------- Protected Datas ------------------------------
  protected:

		//2d-arithmeticalDSS recognition algorithms
		XYArithmeticalDSS myXYalgo;
		XZArithmeticalDSS myXZalgo;		
		YZArithmeticalDSS myYZalgo;	

    //first (at the front) and last (at the back) points of the DSS
    Iterator myF, myL;	

    // ------------------------- Private Datas --------------------------------
	
  private:





  }; // end of class ArithmeticalDSS3d

#ifdef WITH_VISU3D_QGLVIEWER
/*
  struct DrawPavingVoxel : public DrawableWithDGtalQGLViewer {
    void selfDrawQGL( DGtalQGLViewer & viewer ) const
    {
			viewer.myModes[ "ArithmeticalDSS3d" ] = "Paving";
    }
  };
  

  struct DefaultDrawStyleGrid3D : public DrawableWithDGtalQGLViewer {

    virtual void selfDrawQGL( DGtalQGLViewer & viewer ) const {}
  };
*/
#endif


  /**
   * Overloads 'operator<<' for displaying objects of class 'ArithmeticalDSS3d'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'ArithmeticalDSS3d' to write.
   * @return the output stream after the writing.
   */
  template <typename TIterator, typename TInteger, int connectivity>
  std::ostream&
  operator<< ( std::ostream & out,  ArithmeticalDSS3d<TIterator,TInteger,connectivity> & object )
  {
    object.selfDisplay( out);
    return out;
  }


} // namespace DGtal



///////////////////////////////////////////////////////////////////////////////
// Includes inline functions/methods if necessary.
#if defined(INLINE)
#include "DGtal/geometry/3d/ArithmeticalDSS3d.ih"
#endif

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined ArithmeticalDSS3d_h

#undef ArithmeticalDSS3d_RECURSES
#endif // else defined(ArithmeticalDSS3d_RECURSES)
