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
 * @file PNMReader.h
 * @author Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 *
 * @date 2011/04/29
 *
 * Header file for module PNMReader.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(PNMReader_RECURSES)
#error Recursive header files inclusion detected in PNMReader.h
#else // defined(PNMReader_RECURSES)
/** Prevents recursive inclusion of headers. */
#define PNMReader_RECURSES

#if !defined PNMReader_h
/** Prevents repeated inclusion of headers. */
#define PNMReader_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

/////////////////////////////////////////////////////////////////////////////
// class PNMReader
/**
 * Description of class 'PNMReader' <p>
 * \brief Aim: Import a 2D or 3D using the Netpbm formats (ASCII mode).
 * - PPM: RGB 
 *  - PGM: grayscale
 *  - PPM3D: 3D variant of PPM
 *  - PGM3D: 3D variant of PGM
 * 
 *
 *  Simple example: (extract from test file testPNMReader.cpp)
 * 
 *  @code
 *  #include "DGtal/helpers/StdDefs.h"
 *  #include "DGtal/io/readers/PNMReader.h"
 *  #include "DGtal/kernel/images/ImageSelector.h"
 *  ...
 *  string filename = "test.pgm";
 *  typedef ImageSelector < Z2i::Domain, uint>::Type Image;
 *  Image image = PNMReader<Image>::importPGMImage( filename ); 
 *   @endcode
 *  You can then for instance display a threshold part of the image:
 *  @code 
 *  #include "DGtal/kernel/imagesSetsUtils/SetFromImage.h"  
 *  ...
 *  Z2i::DigitalSet set2d (image.domain());
 *  // Threshold all pixel in ]0, 255] in a DigitalSet   
 *  SetFromImage<Z2i::DigitalSet>::append<Image>(set2d, image, 0, 255);
 *  DGtalBoard board;
 *  board << image.domain() << set2d; // display domain and set   
 *  @endcode
 *
 *
 */
 template <typename TImageContainer>
  struct PNMReader
  {
    // ----------------------- Standard services ------------------------------
  public:

    typedef TImageContainer ImageContainer;
    typedef typename TImageContainer::Domain::Vector Vector;

    BOOST_STATIC_ASSERT( (ImageContainer::Domain::dimension == 2));


    /** 
     * Main method to import a Pgm (8bits) into an instance of the 
     * template parameter ImageContainer.
     * 
     * @param filename the file name to import.
     * @param extent the size of the raw data set.
     * @return an instance of the ImageContainer.
     */
    static ImageContainer importPGMImage(const std::string & filename) throw(DGtal::IOException);
    
    
    
 }; // end of class RawReader



} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions/methods if necessary.
#if defined(INLINE)
#include "DGtal/io-viewers/readers/PNMReader.ih"
#endif

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined PNMReader_h

#undef PNMReader_RECURSES
#endif // else defined(PNMReader_RECURSES)
