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
 * @file OpInSTLContainers.h
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2010/10/29
 *
 * Implementation of an adapter for erase and insert 
 * methods of STL containers so that they not only 
 * work for iterator type, but also for reverse_iterator type.  
 *
 * Header file for module OpInSTLContainers.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(OpInSTLContainers_RECURSES)
#error Recursive header files inclusion detected in OpInSTLContainers.h
#else // defined(OpInSTLContainers_RECURSES)
/** Prevents recursive inclusion of headers. */
#define OpInSTLContainers_RECURSES

#if !defined OpInSTLContainers_h
/** Prevents repeated inclusion of headers. */
#define OpInSTLContainers_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <list>
#include "DGtal/base/Common.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

//////////////////////////////////////////////////////////////////////////////
// generic classes for operations in STL containers
// that cannot be performed with a reverse_iterator type

		//default (iterator type)
		template <typename Container, typename Iterator>
		struct OpInSTLContainers 
		{
			static Iterator erase(Container& aContainer,Iterator& anIterator) 
			{
				return aContainer.erase(anIterator);
			}

			static Iterator insert(Container& aContainer,Iterator& anIterator) 
			{
				return aContainer.insert(anIterator);
			}

		};

		//specialisation for reverse_iterator type
		template <typename Container>
		struct OpInSTLContainers<
			Container, 
			std::reverse_iterator<typename Container::iterator> > 
		{
			typedef std::reverse_iterator<typename Container::iterator> reverseIterator;
			static reverseIterator erase(
									Container& aContainer,
									reverseIterator& anIterator) 
			{
				aContainer.erase((++anIterator).base());
				return anIterator;
			}

			static reverseIterator insert(
									Container& aContainer,
									reverseIterator& anIterator) 
			{
				aContainer.insert(anIterator.base());
				return --anIterator;
			}
		};

} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined OpInSTLContainers_h

#undef OpInSTLContainers_RECURSES
#endif // else defined(OpInSTLContainers_RECURSES)
