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
 * @file ArithmeticalDSS.cpp
 * @ingroup Examples
 * @author Isabelle Sivignon (\c isabelle.sivignon@gipsa-lab.grenoble-inp.fr )
 * gipsa-lab Grenoble Images Parole Signal Automatique (CNRS, UMR 5216), CNRS, France
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France

 * @date 2010/11/30
 *
 * An example file named ArithmeticalDSS.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
///////////////////////////////////////////////////////////////////////////////

#include "DGtal/geometry/2d/ArithmeticalDSS.h"
#include "DGtal/geometry/2d/FreemanChain.h"
#include "DGtal/base/BasicTypes.h"
#include "DGtal/geometry/2d/GreedyDecomposition.h"
#include "DGtal/io-viewers/DGtalBoard.h"
#include "DGtal/helpers/StdDefs.h"

using namespace std;
using namespace DGtal;
using namespace Z2i;

///////////////////////////////////////////////////////////////////////////////

int main()
{
  

  /////////////////////////// DSS4 //////////////////////////////////
  {

    typedef PointVector<2,int> Point;
    typedef std::vector<Point> Sequence;
    typedef std::vector<Point>::iterator Iterator;
    typedef ArithmeticalDSS<Iterator,int,4> DSS4;  

    // Input points
    Sequence contour;
    contour.push_back(Point(0,0));
    contour.push_back(Point(1,0));
    contour.push_back(Point(1,1));
    contour.push_back(Point(2,1));
    contour.push_back(Point(3,1));
    contour.push_back(Point(3,2));
    contour.push_back(Point(4,2));
    contour.push_back(Point(5,2));
    contour.push_back(Point(6,2));
    contour.push_back(Point(6,3));
    contour.push_back(Point(6,4));

		
    // Add points while it is possible
    DSS4 theDSS4;		
    Iterator i = contour.begin();
    theDSS4.init(i);
    i++;
    while ( (i!=contour.end())
	    &&(theDSS4.extend(i)) ) {
      i++;
    }

    // Output parameters
    cout << theDSS4 << endl;

    // Draw the grid
    DGtalBoard board;
	
    Domain domain( Point(0,0), Point(8,8) );
    board << SetMode(domain.styleName(), "Grid")
	  << domain;		

    // Draw the points of the DSS
    board << SetMode("PointVector", "Grid")
	  << SetMode(theDSS4.styleName(), "Points") 
	  << theDSS4;
    // Draw the bounding box
    board << SetMode(theDSS4.styleName(), "BoundingBox") 
	  << theDSS4;
	
    board.saveSVG("DSS4.svg");
  }

  ////////////////////// DSS8 ///////////////////////////////
  {

    typedef PointVector<2,int> Point;
    typedef std::vector<Point> Sequence;
    typedef std::vector<Point>::iterator Iterator;
    typedef ArithmeticalDSS<Iterator,int,8> DSS8;  

    // Input points
    std::vector<Point> boundary;
    boundary.push_back(Point(0,0));
    boundary.push_back(Point(1,1));
    boundary.push_back(Point(2,1));
    boundary.push_back(Point(3,2));
    boundary.push_back(Point(4,2));
    boundary.push_back(Point(5,2));
    boundary.push_back(Point(6,3));
    boundary.push_back(Point(6,4));

    // Add points while it is possible
    DSS8 theDSS8;		
    Iterator i = boundary.begin();
    theDSS8.init(i);
    i++;
    while ( (i!=boundary.end())
	    &&(theDSS8.extend(i)) ) {
      i++;
    }

    // Output parameters
    cout << theDSS8 << endl;

    //Draw the pixels
    DGtalBoard board;
    Domain domain( Point(0,0), Point(8,8) );
    board << SetMode(domain.styleName(), "Paving")
	  << domain;		
	
    //Draw the points of the DSS
    board << SetMode("PointVector", "Both");
    board << SetMode(theDSS8.styleName(), "Points") 
	  << theDSS8;

    //Draw the bounding box of the DSS
    board << SetMode(theDSS8.styleName(), "BoundingBox") 
	  << theDSS8;
		
		
    board.saveSVG("DSS8.svg");

  }

  return 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
