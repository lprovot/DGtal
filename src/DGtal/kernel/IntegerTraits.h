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
 * @file IntegerTraits.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2010/07/03
 *
 * Header file for module IntegerTraits.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(IntegerTraits_RECURSES)
#error Recursive header files inclusion detected in IntegerTraits.h
#else // defined(IntegerTraits_RECURSES)
/** Prevents recursive inclusion of headers. */
#define IntegerTraits_RECURSES

#if !defined IntegerTraits_h
/** Prevents repeated inclusion of headers. */
#define IntegerTraits_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <limits>
#include <boost/integer_traits.hpp>
#include <boost/call_traits.hpp>
#include "DGtal/base/Common.h"

#ifdef WITH_GMP
#include <gmpxx.h>
#endif

//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  enum BoundEnum {BOUNDED = 0, UNBOUNDED = 1, BOUND_UNKNOWN = 2};
  enum SignEnum {SIGNED = 0, UNSIGNED = 1, SIGN_UNKNOWN = 2};


/////////////////////////////////////////////////////////////////////////////
// template class IntegerTraits
  /**
   * Description of template class 'IntegerTraits' <p>
   * \brief Aim: The traits class for all models of Cinteger.
   *
   * Since CInteger describes the concept Integer, this class is used
   * by models of CIinteger to specialize some definitions related to
   * Integer. For instance it defines whether a given Integer is
   * signed or not and what is signed/unsigned version.
   */
  template <typename T>
  struct IntegerTraits
  {
    // ----------------------- Associated types ------------------------------
    typedef TagUnknown IsBounded;
    typedef TagUnknown IsUnsigned;
    typedef TagUnknown IsSigned;
    typedef TagFalse IsSpecialized;
    typedef T SignedVersion;
    typedef T UnsignedVersion;
    typedef T ReturnType;

    //Defines a type that represents the "best" way to pass
    // a parameter of type T to a function.
    typedef typename boost::call_traits<T>::param_type ParamType;


    /**
     * Constant Zero.
     */

#if ( defined(WIN32))
    static const T ZERO;
#else
    static const T ZERO = T(0);
#endif

    /**
      * Constant One.
    */
#if (defined (WIN32))
    static const T ONE;
#else
    static const T ONE = T(1);
#endif

    /**
     * @return the zero of this integer.
     */
    static ReturnType zero();

    /**
     * @return the one of this integer.
     */
    static ReturnType one();

    /**
     * @return the minimum possible value for this type of integer or
     * ONE if not bounded or unknown.
     */
    static ReturnType min();

    /**
     * @return the maximum possible value for this type of integer or
     * ZERO if not bounded or unknown.
     */
    static ReturnType max();

    /**
     * @return the number of significant digits for this integer type,
     * or 0 if unbounded or unknown.
     */
    static unsigned int digits();

    /**
     * @return BOUNDED, UNBOUNDED, or BOUND_UNKNOWN.
     */
    static BoundEnum isBounded();
    /**
     * @return SIGNED, UNSIGNED or SIGN_UNKNOWN.
     */
    static SignEnum isSigned();
   
    /**
     * Cast method to DGtal::int64_t (for I/O or board export uses
     * only).
     */
    static DGtal::int64_t castToInt64_t(const T & aT)
    {
      return static_cast<DGtal::int64_t>(aT);
    }
    /**
     * Cast method to double (for I/O or board export uses
     * only).
     */
    static double castToDouble(const T & aT)
    {
      return static_cast<double>(aT);
    }


  }; // end of class IntegerTraits



// #if ( defined(WIN32)  )
// /// On VS2008, unsigned int and uint??_t are different
//   /**
//    * Specialization for <int>.
//    */
//   template <>
//   struct IntegerTraits<int>
//   {
//     typedef TagTrue IsBounded;
//     typedef TagFalse IsUnsigned;
//     typedef TagTrue IsSigned;
//     typedef TagTrue IsSpecialized;
//     typedef int SignedVersion;
//     typedef unsigned int UnsignedVersion;
//     typedef int ReturnType;
//     typedef boost::call_traits<int>::param_type ParamType;
//     static const int ZERO = 0;
//     static const int ONE = 1;
//     static ReturnType zero()
//     {
//       return 0;
//     }
//     static ReturnType one()
//     {
//       return 1;
//     }
//     static ReturnType min()
//     {
//       return boost::integer_traits<int>::const_min;
//     }
//     static ReturnType max()
//     {
//       return boost::integer_traits<int>::const_max;
//     }
//     static unsigned int digits()
//     {
//       return boost::integer_traits<int>::digits;
//     }
//     static BoundEnum isBounded()
//     {
//       return BOUNDED;
//     }
//     static SignEnum isSigned()
//     {
//       return SIGNED;
//     }
   
//     static DGtal::int64_t castToInt64_t(const int & aT)
//     {
//       return static_cast<DGtal::int64_t>(aT);
//     }

//     static double castToDouble(const int & aT)
//     {
//       return static_cast<double>(aT);
//     }

//   }; // end of class IntegerTraits<int>.

//   /**
//    * Specialization for <int>.
//    */
//   template <>
//   struct IntegerTraits<unsigned int>
//   {
//     typedef TagTrue IsBounded;
//     typedef TagTrue IsUnsigned;
//     typedef TagFalse isSigned;
//     typedef TagTrue IsSpecialized;
//     typedef int SignedVersion;
//     typedef unsigned int UnsignedVersion;
//     typedef int ReturnType;
//     typedef boost::call_traits<unsigned int>::param_type ParamType;
//     static const unsigned int ZERO = 0;
//     static const unsigned int ONE = 1;
//     static ReturnType zero()
//     {
//       return 0;
//     }
//     static ReturnType one()
//     {
//       return 1;
//     }
//     static ReturnType min()
//     {
//       return boost::integer_traits<unsigned int>::const_min;
//     }
//     static ReturnType max()
//     {
//       return boost::integer_traits<unsigned int>::const_max;
//     }
//     static unsigned int digits()
//     {
//       return boost::integer_traits<unsigned int>::digits;
//     }
//     static BoundEnum isBounded()
//     {
//       return BOUNDED;
//     }
//     static SignEnum isSigned()
//     {
//       return UNSIGNED;
//     }
//     static DGtal::int64_t castToInt64_t(const unsigned int & aT)
//     {
//       return static_cast<DGtal::int64_t>(aT);
//     }
//     /**
//      * Cast method to double (for I/O or board export uses
//      * only).
//      */
//     static double castToDouble(const unsigned int & aT)
//     {
//       return static_cast<double>(aT);
//     }

//   }; // end of class IntegerTraits<unsigned int>.

//   /**
//    * Specialization for <usigned char>.
//    */
//   template <>
//   struct IntegerTraits<unsigned char>
//   {
//     typedef TagTrue IsBounded;
//     typedef TagTrue IsUnsigned;
//     typedef TagFalse IsSigned;
//     typedef TagTrue IsSpecialized;
//     typedef char SignedVersion;
//     typedef unsigned char UnsignedVersion;
//     typedef unsigned char ReturnType;
//     typedef boost::call_traits<unsigned char>::param_type ParamType;
//     static const unsigned char ZERO = 0;
//     static const unsigned char ONE = 1;
//     static ReturnType zero()
//     {
//       return 0;
//     }
//     static ReturnType one()
//     {
//       return 1;
//     }
//     static ReturnType min()
//     {
//       return boost::integer_traits<unsigned char>::const_min;
//     }
//     static ReturnType max()
//     {
//       return boost::integer_traits<unsigned char>::const_max;
//     }
//     static unsigned int digits()
//     {
//       return boost::integer_traits<unsigned char>::digits;
//     }
//     static BoundEnum isBounded()
//     {
//       return BOUNDED;
//     }
//     static SignEnum isSigned()
//     {
//       return UNSIGNED;
//     }
//     static DGtal::int64_t castToInt64_t(const unsigned char & aT)
//     {
//       return static_cast<DGtal::int64_t>(aT);
//     }
//     /**
//      * Cast method to double (for I/O or board export uses
//      * only).
//      */
//     static double castToDouble(const unsigned char & aT)
//     {
//       return static_cast<double>(aT);
//     }

//   }; // end of class IntegerTraits<unsigned char>.

//   /**
//    * Specialization for <long int>.
//    */
//   template <>
//   struct IntegerTraits<long int>
//   {
//     typedef TagTrue IsBounded;
//     typedef TagFalse IsUnsigned;
//     typedef TagTrue IsSigned;
//     typedef TagTrue IsSpecialized;
//     typedef long int SignedVersion;
//     typedef unsigned long int UnsignedVersion;
//     typedef long int ReturnType;
//     typedef boost::call_traits<long int>::param_type ParamType;
//     static const long int ZERO = 0;
//     static const long int ONE = 1;
//     static ReturnType zero()
//     {
//       return 0;
//     }
//     static ReturnType one()
//     {
//       return 1;
//     }
//     static ReturnType min()
//     {
//       return boost::integer_traits<long int>::const_min;
//     }
//     static ReturnType max()
//     {
//       return boost::integer_traits<long int>::const_max;
//     }
//     static unsigned int digits()
//     {
//       return boost::integer_traits<long int>::digits;
//     }
//     static BoundEnum isBounded()
//     {
//       return BOUNDED;
//     }
//     static SignEnum isSigned()
//     {
//       return SIGNED;
//     }
   
//     static DGtal::int64_t castToInt64_t(const long int & aT)
//     {
//       return static_cast<DGtal::int64_t>(aT);
//     }

//     /**
//      * Cast method to double (for I/O or board export uses
//      * only).
//      */
//     static double castToDouble(const long int & aT)
//     {
//       return static_cast<double>(aT);
//     }

//   }; // end of class IntegerTraits<int>.



// #endif //WIN32
  
  
  /**
   * Specialization for <uint16_t>.
   */
  template <>
  struct IntegerTraits<uint16_t>
  {
    typedef TagTrue IsBounded;
    typedef TagTrue IsUnsigned;
    typedef TagFalse IsSigned;
    typedef TagTrue IsSpecialized;
    typedef int16_t SignedVersion;
    typedef uint16_t UnsignedVersion;
    typedef uint16_t ReturnType;
    typedef boost::call_traits<uint16_t>::param_type ParamType;
    static const uint16_t ZERO = 0;
    static const uint16_t ONE = 1;
    static ReturnType zero()
    {
      return 0;
    }
    static ReturnType one()
    {
      return 1;
    }
    static ReturnType min()
    {
      return boost::integer_traits<uint16_t>::const_min;
    }
    static ReturnType max()
    {
      return boost::integer_traits<uint16_t>::const_max;
    }
    static unsigned int digits()
    {
      return boost::integer_traits<uint16_t>::digits;
    }
    static BoundEnum isBounded()
    {
      return BOUNDED;
    }
    static SignEnum isSigned()
    {
      return UNSIGNED;
    }
    static DGtal::int64_t castToInt64_t(const uint16_t & aT)
    {
      return static_cast<DGtal::int64_t>(aT);
    }
    /**
     * Cast method to double (for I/O or board export uses
     * only).
     */
    static double castToDouble(const uint16_t & aT)
    {
      return static_cast<double>(aT);
    }

  }; // end of class IntegerTraits<uint16_t>.

  /**
   * Specialization for <int16_t>.
   */
  template <>
  struct IntegerTraits<int16_t>
  {
    typedef TagTrue IsBounded;
    typedef TagFalse IsUnsigned;
    typedef TagTrue IsSigned;
    typedef TagTrue IsSpecialized;
    typedef int16_t SignedVersion;
    typedef uint16_t UnsignedVersion;
    typedef int16_t ReturnType;
    typedef boost::call_traits<int16_t>::param_type ParamType;
    static const int16_t ZERO = 0;
    static const int16_t ONE = 1;
    static ReturnType zero()
    {
      return 0;
    }
    static ReturnType one()
    {
      return 1;
    }
    static ReturnType min()
    {
      return boost::integer_traits<int16_t>::const_min;
    }
    static ReturnType max()
    {
      return boost::integer_traits<int16_t>::const_max;
    }
    static unsigned int digits()
    {
      return boost::integer_traits<int16_t>::digits;
    }
    static BoundEnum isBounded()
    {
      return BOUNDED;
    }
    static SignEnum isSigned()
    {
      return SIGNED;
    }
   static DGtal::int64_t castToInt64_t(const int16_t & aT)
    {
      return static_cast<DGtal::int64_t>(aT);
    }
    /**
     * Cast method to double (for I/O or board export uses
     * only).
     */
    static double castToDouble(const int16_t & aT)
    {
      return static_cast<double>(aT);
    }
  }; // end of class IntegerTraits<int16_t>.
 

  /**
   * Specialization for <uint8_t>.
   */
  template <>
  struct IntegerTraits<uint8_t>
  {
    typedef TagTrue IsBounded;
    typedef TagTrue IsUnsigned;
    typedef TagFalse IsSigned;
    typedef TagTrue IsSpecialized;
    typedef int8_t SignedVersion;
    typedef uint8_t UnsignedVersion;
    typedef uint8_t ReturnType;
    typedef boost::call_traits<uint8_t>::param_type ParamType;
    static const uint8_t ZERO = 0;
    static const uint8_t ONE = 1;
    static ReturnType zero()
    {
      return 0;
    }
    static ReturnType one()
    {
      return 1;
    }
    static ReturnType min()
    {
      return boost::integer_traits<uint8_t>::const_min;
    }
    static ReturnType max()
    {
      return boost::integer_traits<uint8_t>::const_max;
    }
    static unsigned int digits()
    {
      return boost::integer_traits<uint8_t>::digits;
    }
    static BoundEnum isBounded()
    {
      return BOUNDED;
    }
    static SignEnum isSigned()
    {
      return UNSIGNED;
    }
    static DGtal::int64_t castToInt64_t(const uint8_t & aT)
    {
      return static_cast<DGtal::int64_t>(aT);
    }
    /**
     * Cast method to double (for I/O or board export uses
     * only).
     */
    static double castToDouble(const uint8_t & aT)
    {
      return static_cast<double>(aT);
    }

  }; // end of class IntegerTraits<uint8_t>.

  /**
   * Specialization for <int8_t>.
   */
  template <>
  struct IntegerTraits<int8_t>
  {
    typedef TagTrue IsBounded;
    typedef TagFalse IsUnsigned;
    typedef TagTrue IsSigned;
    typedef TagTrue IsSpecialized;
    typedef int8_t SignedVersion;
    typedef uint8_t UnsignedVersion;
    typedef int8_t ReturnType;
    typedef boost::call_traits<int8_t>::param_type ParamType;
    static const int8_t ZERO = 0;
    static const int8_t ONE = 1;
    static ReturnType zero()
    {
      return 0;
    }
    static ReturnType one()
    {
      return 1;
    }
    static ReturnType min()
    {
      return boost::integer_traits<int8_t>::const_min;
    }
    static ReturnType max()
    {
      return boost::integer_traits<int8_t>::const_max;
    }
    static unsigned int digits()
    {
      return boost::integer_traits<int8_t>::digits;
    }
    static BoundEnum isBounded()
    {
      return BOUNDED;
    }
    static SignEnum isSigned()
    {
      return SIGNED;
    }
   static DGtal::int64_t castToInt64_t(const int8_t & aT)
    {
      return static_cast<DGtal::int64_t>(aT);
    }
    /**
     * Cast method to double (for I/O or board export uses
     * only).
     */
    static double castToDouble(const int8_t & aT)
    {
      return static_cast<double>(aT);
    }
  }; // end of class IntegerTraits<int16_t>.

  /**
   * Specialization for <uint32_t>.
   */
  template <>
  struct IntegerTraits<uint32_t>
  {
    typedef TagTrue IsBounded;
    typedef TagTrue IsUnsigned;
    typedef TagFalse IsSigned;
    typedef TagTrue IsSpecialized;
    typedef int32_t SignedVersion;
    typedef uint32_t UnsignedVersion;
    typedef uint32_t ReturnType;
    typedef boost::call_traits<uint32_t>::param_type ParamType;
    static const uint32_t ZERO = 0;
    static const uint32_t ONE = 1;
    static ReturnType zero()
    {
      return 0;
    }
    static ReturnType one()
    {
      return 1;
    }
    static ReturnType min()
    {
      return boost::integer_traits<uint32_t>::const_min;
    }
    static ReturnType max()
    {
      return boost::integer_traits<uint32_t>::const_max;
    }
    static unsigned int digits()
    {
      return boost::integer_traits<uint32_t>::digits;
    }
    static BoundEnum isBounded()
    {
      return BOUNDED;
    }
    static SignEnum isSigned()
    {
      return UNSIGNED;
    }
   static DGtal::int64_t castToInt64_t(const uint32_t & aT)
    {
      return static_cast<DGtal::int64_t>(aT);
    }
    static double castToDouble(const uint32_t & aT)
    {
      return static_cast<double>(aT);
    }
  }; // end of class IntegerTraits<uint32_t>.

  /**
   * Specialization for <int32_t>.
   */
  template <>
  struct IntegerTraits<int32_t>
  {
    typedef TagTrue IsBounded;
    typedef TagFalse IsUnsigned;
    typedef TagTrue IsSigned;
    typedef TagTrue IsSpecialized;
    typedef int32_t SignedVersion;
    typedef uint32_t UnsignedVersion;
    typedef int32_t ReturnType;
    typedef boost::call_traits<int32_t>::param_type ParamType;
    static const int32_t ZERO = 0;
    static const int32_t ONE = 1;
    static ReturnType zero()
    {
      return 0;
    }
    static ReturnType one()
    {
      return 1;
    }
    static ReturnType min()
    {
      return boost::integer_traits<int32_t>::const_min;
    }
    static ReturnType max()
    {
      return boost::integer_traits<int32_t>::const_max;
    }
    static unsigned int digits()
    {
      return boost::integer_traits<int32_t>::digits;
    }
    static BoundEnum isBounded()
    {
      return BOUNDED;
    }
    static SignEnum isSigned()
    {
      return SIGNED;
    }
   static DGtal::int64_t castToInt64_t(const int32_t & aT)
    {
      return static_cast<DGtal::int64_t>(aT);
    }
    /**
     * Cast method to double (for I/O or board export uses
     * only).
     */
    static double castToDouble(const int32_t & aT)
    {
      return static_cast<double>(aT);
    }
  }; // end of class IntegerTraits<int32_t>.

  /**
   * Specialization for <uint64_t>.
   */
  template <>
  struct IntegerTraits<uint64_t>
  {
    typedef TagTrue IsBounded;
    typedef TagTrue IsUnsigned;
    typedef TagFalse IsSigned;
    typedef TagTrue IsSpecialized;
    typedef int64_t SignedVersion;
    typedef uint64_t UnsignedVersion;
    typedef uint64_t ReturnType;
    typedef boost::call_traits<uint64_t>::param_type ParamType;
    static const uint64_t ZERO = 0;
    static const uint64_t ONE = 1;
    static ReturnType zero()
    {
      return 0;
    }
    static ReturnType one()
    {
      return 1;
    }
    static ReturnType min()
    {
      return boost::integer_traits<uint64_t>::const_min;
    }
    static ReturnType max()
    {
      return boost::integer_traits<uint64_t>::const_max;
    }
    static unsigned int digits()
    {
      return boost::integer_traits<uint64_t>::digits;
    }
    static BoundEnum isBounded()
    {
      return BOUNDED;
    }
    static SignEnum isSigned()
    {
      return UNSIGNED;
    }
   static DGtal::int64_t castToInt64_t(const uint64_t & aT)
    {
      return static_cast<DGtal::int64_t>(aT);
    }
    /**
     * Cast method to double (for I/O or board export uses
     * only).
     */
    static double castToDouble(const uint64_t & aT)
    {
      return static_cast<double>(aT);
    }
  }; // end of class IntegerTraits<uint64_t>.

  /**
   * Specialization for <int64_t>.
   */
  template <>
  struct IntegerTraits<int64_t>
  {
    typedef TagTrue IsBounded;
    typedef TagFalse IsUnsigned;
    typedef TagTrue IsSigned;
    typedef TagTrue IsSpecialized;
    typedef int64_t SignedVersion;
    typedef uint64_t UnsignedVersion;
    typedef int64_t ReturnType;
    typedef boost::call_traits<int64_t>::param_type ParamType;
    static const int64_t ZERO = 0;
    static const int64_t ONE = 1;
    static ReturnType zero()
    {
      return 0;
    }
    static ReturnType one()
    {
      return 1;
    }
    static ReturnType min()
    {
      return boost::integer_traits<int64_t>::const_min;
    }
    static ReturnType max()
    {
      return boost::integer_traits<int64_t>::const_max;
    }
    static unsigned int digits()
    {
      return boost::integer_traits<int64_t>::digits;
    }
    static BoundEnum isBounded()
    {
      return BOUNDED;
    }
    static SignEnum isSigned()
    {
      return SIGNED;
    }
   static DGtal::int64_t castToInt64_t(const int64_t & aT)
    {
      return aT;
    }
    static double castToDouble(const int64_t & aT)
    {
      return static_cast<double>(aT);
    }
  }; // end of class IntegerTraits<int64_t>.

  
#ifdef WITH_GMP
  /**
   * Specialization for <mpz_class>.
   */
  template <>
  struct IntegerTraits<mpz_class>
  {
    typedef TagFalse IsBounded;
    typedef TagFalse IsUnsigned;
    typedef TagTrue IsSigned;
    typedef TagTrue IsSpecialized;
    typedef mpz_class SignedVersion;
    typedef mpz_class UnsignedVersion;
    typedef mpz_class ReturnType;
    typedef boost::call_traits<int64_t>::param_type ParamType;
    static mpz_class ZERO;//cf IntegerTraits.h
    static mpz_class ONE;//cf IntegerTraits.h
    static ReturnType zero()
    {
      return ZERO;
    }
    static ReturnType one()
    {
      return ONE;
    }
    static ReturnType min()
    {
      ASSERT2(false, "UnBounded interger type does not support min() function");
      return ZERO;
    }
    static ReturnType max()
    {
      ASSERT2(false, "UnBounded interger type does not support max() function");
      return ZERO;
    }

    static unsigned int digits()
    {
      ASSERT2(false, "UnBounded interger type does not support digits() function");
      return 0;
    }
    static BoundEnum isBounded()
    {
      return BOUNDED;
    }
    static SignEnum isSigned()
    {
      return SIGNED;
    }
    static DGtal::int64_t castToInt64_t(const mpz_class & aT)
    {
      return aT.get_si();
    }
    static double castToDouble(const mpz_class & aT)
    {
      return aT.get_d();
    }
  }; // end of class IntegerTraits<mpz_class>.
#endif


  class Warning_promote_trait_not_specialized_for_this_case { };

  template<class A, class B>
  struct promote_trait
  {
    typedef Warning_promote_trait_not_specialized_for_this_case promote_t;
  };

  template<>
  struct promote_trait<int32_t, int64_t>
  {
    typedef int64_t promote_t;
  };

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/kernel/IntegerTraits.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined IntegerTraits_h

#undef IntegerTraits_RECURSES
#endif // else defined(IntegerTraits_RECURSES)
