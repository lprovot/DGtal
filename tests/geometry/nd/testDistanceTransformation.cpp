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

/**
 * @file testDistanceTransformation.cpp
 * @ingroup Tests
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2010/09/30
 *
 * Functions for testing class DistanceTransformation.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <iomanip>
#include "DGtal/base/Common.h"


#include "DGtal/base/Common.h"
#include "DGtal/kernel/SpaceND.h"
#include "DGtal/kernel/domains/HyperRectDomain.h"
#include "DGtal/images/ImageSelector.h"
#include "DGtal/geometry/nd/volumetric/DistanceTransformation.h"
#include "DGtal/io-viewers/colormaps/HueShadeColorMap.h"
#include "DGtal/io-viewers/colormaps/GrayScaleColorMap.h"
#include "DGtal/helpers/Shapes.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/helpers/ShapeFactory.h"
#include "DGtal/io-viewers/DGtalBoard.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class DistanceTransformation.
///////////////////////////////////////////////////////////////////////////////

template<typename Image>
void randomSeeds(Image &input, const unsigned int nb, const int value)
{
  typename Image::Point p, low = input.lowerBound();
  typename Image::Vector ext;

  ext = input.extent();

  for (unsigned int k = 0 ; k < nb; k++)
  {
    for (unsigned int dim = 0; dim < Image::dimension; dim++)
    {
      p[dim] = rand() % (ext[dim]) +  low[dim];
    }
    input.setValue(p, value);
  }
}



/**
 * Example of a test. To be completed.
 *
 */
bool testDistanceTransformation()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;

  trace.beginBlock ( "Testing the whole DT computation" );

  typedef SpaceND<2> TSpace;
  typedef TSpace::Point Point;
  typedef HyperRectDomain<TSpace> Domain;
  typedef HueShadeColorMap<unsigned char, 2> HueTwice;
  typedef GrayscaleColorMap<unsigned char> Gray;
  Point a ( 2, 2 );
  Point b ( 15, 15 );
  typedef ImageSelector<Domain, unsigned int>::Type Image;
  Image image ( a, b );

  for ( unsigned k = 0; k < 49; k++ )
  {
    a[0] = ( k / 7 ) + 5;
    a[1] = ( k % 7 ) + 5;
    image.setValue ( a, 128 );
  }



  DistanceTransformation<Image, 2> dt;
  typedef DistanceTransformation<Image, 2>::OutputImage ImageLong;

  dt.checkTypesValidity ( image );

  DGtalBoard board;
  board.setUnit ( LibBoard::Board::UCentimeter );
  image.selfDraw<Gray> ( board, 0, 255 );
  board.saveSVG ( "image-preDT.svg" );
  //We just iterate on the Domain points and print out the point coordinates.
  std::copy ( image.begin(),
	      image.end(),
	      std::ostream_iterator<unsigned int> ( std::cout, " " ) );
  
  
  
  ImageLong result = dt.compute ( image );
  
  trace.warning() << result << endl;
  //We just iterate on the Domain points and print out the point coordinates.
  ImageLong::ConstIterator it = result.begin();
  for (unsigned int y = 2; y < 16; y++)
  {
    for (unsigned int x = 2; x < 16; x++)
    {
      std::cout << result(it) << " ";
      ++it;
    }
    std::cout << std::endl;
  }



  board.clear();
  result.selfDraw<Gray> ( board, 0, 16 );
  board.saveSVG ( "image-postDT.svg" );


  trace.info() << result << endl;

  trace.endBlock();

  return nbok == nb;
}
/**
 * Example of a test. To be completed.
 *
 */
bool testDistanceTransformationNeg()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;

  trace.beginBlock ( "Testing the whole DT computation" );

  typedef SpaceND<2> TSpace;
  typedef TSpace::Point Point;
  typedef HyperRectDomain<TSpace> Domain;
  typedef HueShadeColorMap<unsigned char, 2> HueTwice;
  typedef GrayscaleColorMap<unsigned char> Gray;
  Point a ( -10, -10 );
  Point b ( 10, 10 );
  typedef ImageSelector<Domain, unsigned int>::Type Image;
  Image image ( a, b );

  for(int y=-10; y<=10;y++) 
    for(int x=-10; x<=10;x++)
      {
	if ((abs(x)<7) && (abs(y)<5))
	  image.setValue(Point(x,y),1);
	else
	  image.setValue(Point(x,y),0);
      }
  
  DistanceTransformation<Image, 2> dt;
  typedef DistanceTransformation<Image, 2>::OutputImage ImageLong;

  dt.checkTypesValidity ( image );

  DGtalBoard board;
  board.setUnit ( LibBoard::Board::UCentimeter );
  image.selfDraw<Gray> ( board, 0, 1 );
  board.saveSVG ( "image-preDT-neg.svg" );


  for(int y=-10; y<=10;y++) 
    {
      for(int x=-10; x<=10;x++)
	{
	  std::cout<<image(Point(x,y))<<"  ";
	}
      std::cout<<std::endl;
    }
  

  ImageLong result = dt.compute ( image );
  
  DGtal::uint64_t maxv=0;
  for(ImageLong::Iterator it = result.begin(), itend = result.end();
      it != itend ; ++it)
    if (result(it) > maxv)
      maxv = result(it);

  for(int y=-10; y<=10;y++) 
    {
      for(int x=-10; x<=10;x++)
	{
	  std::cout<<result(Point(x,y))<<"  ";
	}
      std::cout<<std::endl;
    }
  


  trace.warning() << result << endl;

  board.clear();
  result.selfDraw<Gray> ( board, 0, maxv );
  board.saveSVG ( "image-postDT-neg.svg" );


  trace.info() << result << endl;

  trace.endBlock();

  return nbok == nb;
}


bool testDTFromSet()
{
unsigned int nbok = 0;
  unsigned int nb = 0;

  trace.beginBlock ( "Testing the whole DT computation from a Set" );

  typedef SpaceND<2> TSpace;
  typedef TSpace::Point Point;
  typedef HyperRectDomain<TSpace> Domain;
  typedef HueShadeColorMap<unsigned char, 2> HueTwice;
  typedef ImageSelector<Domain, unsigned int>::Type Image;

  DistanceTransformation<Image, 2> dt;
  typedef DistanceTransformation<Image, 2>::OutputImage ImageLong;
  
  DGtalBoard board;

  Ball2D<Z2i::Space> flower(Z2i::Point(0,0), 10);
  Z2i::Domain domain(flower.getLowerBound(), flower.getUpperBound());
  Z2i::DigitalSet aSet(domain);
  
  Shapes<Z2i::Domain>::shaper(aSet, flower);

  ImageLong result = dt.compute ( aSet );
  
  trace.warning() << result << endl;
  typedef GrayscaleColorMap<ImageLong::Value> Gray;
 
  DGtal::uint64_t maxv = 0;
  for ( ImageLong::Iterator it = result.begin(), itend = result.end();
	it != itend; ++it)
    if ( (*it) > maxv)
      maxv = (*it);
  
  for(int y=-11; y<11; y++)
    {
      for(int x=-11; x<11; x++)
	{
	  Point a(x,y);
	  std::cout<<result(a)<<" ";
	}
      std::cout<<std::endl;
    }

  trace.error() << "MaxV="<<maxv<<std::endl;

  result.selfDraw<Gray> ( board, 0, maxv);
  board.saveSVG ( "image-postDTFromSet.svg" );
  

  trace.endBlock();

  return nbok == nb;
}

/**
 * Example of a test. To be completed.
 *
 */
bool testDistanceTransformationBorder()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;

  trace.beginBlock ( "Testing DT computation with Infinity values at the first step" );

  typedef SpaceND<2> TSpace;
  typedef TSpace::Point Point;
  typedef HyperRectDomain<TSpace> Domain;
  typedef HueShadeColorMap<DGtal::uint64_t, 2> Hue;
  typedef GrayscaleColorMap<DGtal::uint64_t> Gray;

  Point a (0, 0 );
  Point b ( 128, 128 );

  typedef ImageSelector<Domain, unsigned int>::Type Image;
  Image image ( a, b );

  for ( Image::Iterator it = image.begin(), itend = image.end();it != itend; ++it)
    image.setValue ( it, 128 );


  randomSeeds(image, 19, 0);

 
  DistanceTransformation<Image, 2> dt;
  typedef DistanceTransformation<Image, 2>::OutputImage ImageLong;

  dt.checkTypesValidity ( image );

  DGtalBoard board;
  board.setUnit ( LibBoard::Board::UCentimeter );
  image.selfDraw<Hue> ( board, 0, 150 );
  board.saveSVG ( "image-preDT-border.svg" );


  ImageLong result = dt.compute ( image );

  DGtal::uint64_t maxv = 0;
  for ( ImageLong::Iterator it = result.begin(), itend = result.end();it != itend; ++it)
    if ( (*it) > maxv)
      maxv = (*it);

  ImageLong::ConstIterator it = result.begin();
  for (unsigned int y = 0; y < 33; y++)
  {
    for (unsigned int x = 0; x < 33; x++)
    {
      std::cout << std::setw(4) << result(it) << " ";
      ++it;
    }
    std::cout << std::endl;
  }

  trace.warning() << result << "MaxV = " << maxv << endl;


  board.clear();
  result.selfDraw<Hue> ( board, 0, maxv + 1);
  board.saveSVG ( "image-postDT-border.svg" );


  trace.info() << result << endl;

  trace.endBlock();

  return nbok == nb;
}


/**
 * Example of a test. To be completed.
 *
 */
bool testDistanceTransformation3D()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;

  trace.beginBlock ( "Testing 3D DT computation" );

  typedef SpaceND<3> TSpace;
  typedef TSpace::Point Point;
  typedef HyperRectDomain<TSpace> Domain;
  typedef HueShadeColorMap<unsigned char, 2> HueTwice;
  typedef GrayscaleColorMap<unsigned char> Gray;
  Point a ( 0, 0, 0 );
  Point b ( 15, 15, 15 );
  typedef ImageSelector<Domain, unsigned int>::Type Image;
  Image image ( a, b );
  Point c(8, 8, 8);
  Domain dom(a, b);

  for (Domain::ConstIterator it = dom.range().begin(),
	 itend = dom.range().end(); it != itend; ++it)
  {
    if ( ((*it) - c).norm() < 7)
      image.setValue ( *it, 128 );
  }

  DistanceTransformation<Image, 2> dt;
  typedef DistanceTransformation<Image, 2>::OutputImage ImageLong;

  dt.checkTypesValidity ( image );

  ImageLong result = dt.compute ( image );

  //We display the values on a 2D slice
  for (unsigned int y = 0; y < 16; y++)
  {
    for (unsigned int x = 0; x < 16; x++)
    {
      Point p(x, y, 8);
      std::cout << result(p) << "   ";
    }
    std::cout << std::endl;
  }


  trace.warning() << result << endl;

  trace.endBlock();

  return nbok == nb;
}

/**
 * Example of a test. To be completed.
 *
 */
bool testTypeValidity()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;

  trace.beginBlock ( "Testing type checker" );

  typedef SpaceND<2> TSpace;
  typedef TSpace::Point Point;
  typedef HyperRectDomain<TSpace> Domain;

  Point a ( 0, 0 );
  Point b ( 15, 15 );
  typedef ImageSelector<Domain, unsigned int>::Type Image;
  Image image ( a, b );
 
  DistanceTransformation<Image, 2> dt;
  typedef DistanceTransformation<Image, 2>::OutputImage ImageLong;

  //No problem should be reported on the std:cerr.
  dt.checkTypesValidity ( image );

  DistanceTransformation<Image, 34> dt34;

  //Type problem should be reported.
  dt34.checkTypesValidity ( image );

  trace.endBlock();
  return nbok == nb;
}


bool testChessboard()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;

  trace.beginBlock ( "Testing DT computation with Infinity values at the first step" );

  typedef SpaceND<2> TSpace;
  typedef TSpace::Point Point;
  typedef HyperRectDomain<TSpace> Domain;
  typedef HueShadeColorMap<DGtal::uint64_t, 2> Hue;
  typedef GrayscaleColorMap<DGtal::uint64_t> Gray;

  Point a (0, 0 );
  Point b ( 128, 128 );

  typedef ImageSelector<Domain, unsigned int>::Type Image;
  Image image ( a, b );

  for ( Image::Iterator it = image.begin(), itend = image.end();it != itend; ++it)
    image.setValue ( it, 128 );


  randomSeeds(image, 19, 0);

  typedef ImageSelector<Domain, long int>::Type ImageLong;

  //L_infinity metric
  typedef DistanceTransformation<Image, 0> DT;
  DT dt;
  
  //L_1 metric
  typedef DistanceTransformation<Image, 1> DT1;
  DT1 dt1;
  
  dt.checkTypesValidity ( image );

  DT::OutputImage result = dt.compute ( image );
  DT1::OutputImage result1 = dt1.compute ( image );

  DGtal::uint64_t maxv = 0;
  for ( DT::OutputImage::Iterator it = result.begin(), itend = result.end();it != itend; ++it)
    if ( (*it) > maxv)
      maxv = (*it);

  DT::OutputImage::ConstIterator it = result.begin();

  trace.warning() << result << "MaxV = " << maxv << endl;
  //We display the values on a 2D slice
  for (unsigned int y = 0; y < 16; y++)
  {
    for (unsigned int x = 0; x < 16; x++)
    {
      Point p(x, y);
      std::cout << std::setw(4) << result(p) << " ";
    }
    std::cout << std::endl;
  }

  trace.info()<< "Exporting to SVG"<<endl;

  DGtalBoard board;
  board.setUnit ( LibBoard::Board::UCentimeter );
  result.selfDraw<Hue> ( board, 0, maxv + 1);
  board.saveSVG ( "image-DT-linfty.svg" );
  trace.info()<< "done"<<endl;



  trace.info()<< "max  L1"<<endl;
  maxv = 0;
  for ( DT1::OutputImage::Iterator it2 = result1.begin(), itend = result1.end();
	it2 != itend; ++it2)
    {
      if ( result1(it2) > maxv)
	maxv = (*it2);
    }

  trace.info()<< "Exporting to SVG L1"<<endl;
  board.clear();
  result1.selfDraw<Hue> ( board, 0, maxv + 1);
  board.saveSVG ( "image-DT-l1.svg" );
  trace.info()<< "done"<<endl;


  trace.info() << result << endl;

  trace.endBlock();

  return nbok == nb;
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main ( int argc, char** argv )
{
  trace.beginBlock ( "Testing class DistanceTransformation" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res =  testTypeValidity() && testDistanceTransformation() && testDistanceTransformationNeg() 
    && testDTFromSet()  
    && testDistanceTransformationBorder() 
    && testDistanceTransformation3D()
    && testChessboard()
    && testDTFromSet();
  //&& ... other tests
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
