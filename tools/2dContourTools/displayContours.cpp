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
 * @file image2freeman.cpp
 * @ingroup Tools
 * @author Bertrand Kerautret (\c kerautre@loria.fr)
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 *
 * @date 2011/27/04
 *
 * DGtal convert grey scales image to fremann contour. 
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>

#include "DGtal/base/Common.h"

#include "DGtal/helpers/ShapeFactory.h"
#include "DGtal/helpers/Shapes.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/helpers/ContourHelper.h"

#include "DGtal/images/imagesSetsUtils/ImageFromSet.h"
#include "DGtal/images/imagesSetsUtils/SetFromImage.h"
#include "DGtal/images/ImageContainerBySTLVector.h"
#include "DGtal/images/ImageSelector.h"
#include "DGtal/io-viewers/readers/PointListReader.h"
#include "DGtal/io-viewers/DGtalBoard.h"

#include "DGtal/kernel/RealPointVector.h"

#ifdef WITH_MAGICK
#include "DGtal/io-viewers/readers/MagickReader.h"
#endif

#include "DGtal/geometry/2d/FreemanChain.h"


#include "DGtal/helpers/Surfaces.h"

#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>

#include <vector>
#include <string>

using namespace DGtal;




///////////////////////////////////////////////////////////////////////////////
namespace po = boost::program_options;

int main( int argc, char** argv )
{
  // parse command line ----------------------------------------------
  po::options_description general_opt("Allowed options are: ");
  general_opt.add_options()
    ("help,h", "display this message")
    ("FreemanChain,f", po::value<std::string>(), "FreemanChain file name")
    ("SDP", po::value<std::string>(), "Import a contour as a Sequence of Discrete Points (SDP format)")
    ("SFP", po::value<std::string>(), "Import a contour as a Sequence of Floating Points (SFP format)")
    ("drawContourPoint", po::value<double>(), "<size> display contour points as disk of radius <size>")    
    ("lineWidth", po::value<double>()->default_value(1.0), "Define the linewidth of the contour (SDP format)")    
    ("outputEPS", po::value<std::string>(), " <filename> specify eps format (default format output.eps)")
    ("outputSVG", po::value<std::string>(), " <filename> specify svg format.")
    ("outputFIG", po::value<std::string>(), " <filename> specify fig format.")
#ifdef WITH_CAIRO
    ("outputPDF", po::value<std::string>(), "outputPDF <filename> specify pdf format. ")
    ("outputPNG", po::value<std::string>(), "outputPNG <filename> specify png format.")
    ("invertYaxis", " invertYaxis invert the Y axis for display contours (used only with --SDP)")
#endif
    #ifdef WITH_MAGICK
    ("backgroundImage", po::value<std::string>(), "backgroundImage <filename> <alpha> : display image as background with transparency alpha (defaut 1) (transparency works only if cairo is available)")
    ("alphaBG", po::value<double>(), "alphaBG <value> 0-1.0 to display the background image in transparency (default 1.0)")
    #endif
    ("scale", po::value<double>(), "scale <value> 1: normal; >1 : larger ; <1 lower resolutions  )");
  
  
  
  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, general_opt), vm);  
  po::notify(vm);    
  if(vm.count("help")||argc<=1 || (not(vm.count("FreemanChain")) && not(vm.count("SDP")) && not(vm.count("SFP"))&&
				   not(vm.count("backgroundImage")) ) )
    {
      trace.info()<< "Display discrete contours. " <<std::endl << "Basic usage: "<<std::endl
		  << "\t displayContours [options] --FreemanChain  <fileName>  contours.fc --imageName image.png "<<std::endl
		  << general_opt << "\n";
      return 0;
    }
  
  
  
  double lineWidth=  vm["lineWidth"].as<double>();
  
  double scale=1.0;
  if(vm.count("scale")){
    scale = vm["scale"].as<double>();
  }
  
  DGtalBoard aBoard;
  aBoard.setUnit (0.05*scale, LibBoard::Board::UCentimeter);
  



#ifdef WITH_MAGICK
  double alpha=1.0;
  if(vm.count("alphaBG")){
   alpha = vm["alphaBG"].as<double>(); 
  }
  
if(vm.count("backgroundImage")){
  string imageName = vm["backgroundImage"].as<string>();
  typedef ImageSelector<Z2i::Domain, unsigned char>::Type Image;
    DGtal::MagickReader<Image> reader;
    Image img = reader.importImage( imageName );
    Z2i::Point ptInf = img.lowerBound(); 
    Z2i::Point ptSup = img.upperBound(); 
    unsigned int width = abs(ptSup.at(0)-ptInf.at(0)+1);
    unsigned int height = abs(ptSup.at(1)-ptInf.at(1)+1);
    
    aBoard.drawImage(imageName, 0-0.5,height-0.5, width, height, -1, alpha );
  }
#endif
 

 
 if(vm.count("FreemanChain")){
   string fileName = vm["FreemanChain"].as<string>();
   vector< FreemanChain<int> > vectFc =  PointListReader< Z2i::Point>:: getFreemanChainsFromFile<int> (fileName); 
   aBoard <<  SetMode( vectFc.at(0).styleName(), "InterGrid" );
   aBoard << CustomStyle( vectFc.at(0).styleName(), 
			  new CustomColors( DGtalBoard::Color::Red  ,  DGtalBoard::Color::None ) );    
   for(unsigned int i=0; i<vectFc.size(); i++){
     aBoard <<  vectFc.at(i) ;
   }
 }
 
 

if(vm.count("SDP") || vm.count("SFP")){
  bool drawPoints= vm.count("drawContourPoint");
  bool invertYaxis = vm.count("invertYaxis");
  double pointSize=1.0;
  if(drawPoints){
    pointSize = vm["drawContourPoint"].as<double>();
  }
  vector<LibBoard::Point> contourPt;
  if(vm.count("SDP")){
    string fileName = vm["SDP"].as<string>();
    vector< Z2i::Point >  contour = 
      PointListReader< Z2i::Point >::getPointsFromFile(fileName); 
    for(unsigned int j=0; j<contour.size(); j++){
      LibBoard::Point pt((double)(contour.at(j)[0]),
			 (invertYaxis? (double)(-contour.at(j)[1]+contour.at(0)[1]):(double)(contour.at(j)[1])));
      contourPt.push_back(pt);
      if(drawPoints){
	aBoard.fillCircle(pt.x, pt.y, pointSize);
      }
    }
  }
 
  if(vm.count("SFP")){
    string fileName = vm["SFP"].as<string>();
    vector<  RealPointVector<2>  >  contour = 
      PointListReader<  RealPointVector<2>  >::getPointsFromFile(fileName); 
    for(unsigned int j=0; j<contour.size(); j++){
      LibBoard::Point pt((double)(contour.at(j)[0]),
			 (invertYaxis? (double)(-contour.at(j)[1]+contour.at(0)[1]):(double)(contour.at(j)[1])));
      contourPt.push_back(pt);
      if(drawPoints){
	aBoard.fillCircle(pt.x, pt.y, pointSize);
      }
    }
  }
  
  
  aBoard.setPenColor(DGtalBoard::Color::Red);
  aBoard.setLineStyle (LibBoard::Shape::SolidStyle );
  aBoard.setLineWidth (lineWidth);
  aBoard.drawPolyline(contourPt);
  
  
 }

 


  string outputFileName= "output.eps";

  

  
  if (vm.count("outputSVG")){
    string outputFileName= vm["outputSVG"].as<string>();
    aBoard.saveSVG(outputFileName.c_str());
  }
  
  if (vm.count("outputFIG")){
    string outputFileName= vm["outputFIG"].as<string>();
    aBoard.saveFIG(outputFileName.c_str());
  }
#ifndef WITH_CAIRO
  if (vm.count("outputEPS")){
    string outputFileName= vm["outputEPS"].as<string>();
    aBoard.saveEPS(outputFileName.c_str());
  }  
#endif

#ifdef WITH_CAIRO
  if (vm.count("outputEPS")){
    string outputFileName= vm["outputEPS"].as<string>();
    aBoard.saveCairo(outputFileName.c_str(),DGtalBoard::CairoEPS );
  }
  if (vm.count("outputPDF")){
    string outputFileName= vm["outputPDF"].as<string>();
    aBoard.saveCairo(outputFileName.c_str(),DGtalBoard::CairoPDF );
  }
  if (vm.count("outputPNG")){
    string outputFileName= vm["outputPNG"].as<string>();
    aBoard.saveCairo(outputFileName.c_str(),DGtalBoard::CairoPNG );
  }
#endif


  

	
}

