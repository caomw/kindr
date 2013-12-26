/*
 * Copyright (c) 2013, Christian Gehring, Hannes Sommer, Paul Furgale, Remo Diethelm
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Autonomous Systems Lab, ETH Zurich nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Christian Gehring, Hannes Sommer, Paul Furgale,
 * Remo Diethelm BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
 * OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/

#ifndef COMMON_HPP_
#define COMMON_HPP_

#include <cmath>
#include <cassert>
#include <iostream>
#include <limits>



namespace kindr {
namespace common {

/*! \brief Floating-point modulo
 *
 * The result (the remainder) has same sign as the divisor.
 * Similar to matlab's mod(); Not similar to fmod():    floatingPointModulo(-3,4)= 1   fmod(-3,4)= -3
 */
template<typename T>
T floatingPointModulo(const T& x, const T& y)
{
    static_assert(!std::numeric_limits<T>::is_exact , "floatingPointModulo: floating-point type expected");

    if (y == 0.0)
        return x;

    double m= x - y * floor(x/y);

    // handle boundary cases resulted from floating-point cut off:

    if (y > 0)              // modulo range: [0..y)
    {
        if (m>=y)           // mod(-1e-16             , 360.    ): m= 360.
            return 0;

        if (m<0 )
        {
            if (y+m == y)
                return 0  ; // just in case...
            else
                return y+m; // Mod(106.81415022205296 , 2*M_PI ): m= -1.421e-14
        }
    }
    else                    // modulo range: (y..0]
    {
        if (m<=y)           // mod(1e-16              , -360.   ): m= -360.
            return 0;

        if (m>0 )
        {
            if (y+m == y)
                return 0  ; // just in case...
            else
                return y+m; // mod(-106.81415022205296, -2*M_PI): m= 1.421e-14
        }
    }

    return m;
}

//! wrap angle to [x1..x2)
template<typename T>
inline T wrapAngle(const T& angle, const T& x1, const T& x2)
{
    return floatingPointModulo(angle-x1, x2-x1) + x1;
}

//! wrap angle to [-PI..PI)
template<typename T>
inline T wrapPosNegPI(const T& angle)
{
    return floatingPointModulo(angle + M_PI, 2*M_PI) - M_PI;
}

//! wrap angle to [0..2*PI)
template<typename T>
inline T wrapTwoPI(const T& angle)
{
    return floatingPointModulo(angle, 2*M_PI);
}



template<typename T>
class GenericNumTraits {
 public:
  enum {
    IsInteger = std::numeric_limits<T>::is_integer,
    IsSigned = std::numeric_limits<T>::is_signed,
  };

  typedef T Scalar;


  static inline Scalar epsilon() { return std::numeric_limits<T>::epsilon(); }
  static inline Scalar dummy_precision()
  {
    // make sure to override this for floating-point types
    return Scalar(0);
  }
  static inline T highest() { return (std::numeric_limits<T>::max)(); }
  static inline T lowest()  { return IsInteger ? (std::numeric_limits<T>::min)() : (-(std::numeric_limits<T>::max)()); }

};

template<typename T>
class NumTraits : GenericNumTraits<T> {
 public:
};

template<>
class NumTraits<float>
  : GenericNumTraits<float>
{
 public:
  static inline float dummy_precision() { return 1e-5f; }
};

template<>
class NumTraits<double> : GenericNumTraits<double>
{
 public:
  static inline double dummy_precision() { return 1e-12; }
};

template<>
class NumTraits<long double>
  : GenericNumTraits<long double>
{
 public:
  static inline long double dummy_precision() { return 1e-15l; }
};


} // namespace common
} // namespace kindr


#endif /* COMMON_HPP_ */
