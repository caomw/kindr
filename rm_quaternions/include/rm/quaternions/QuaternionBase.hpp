/*
 * QuaternionBase.hpp
 *
 *  Created on: Oct 28, 2013
 *      Author: remod
 */

#ifndef QUATERNIONBASE_HPP_
#define QUATERNIONBASE_HPP_


namespace rm {
/*!
 *  \addtogroup Quaternions
 *  @{
 */
//! Generic quaternion interface
namespace quaternions {
//! Internal stuff (only for developers)
namespace internal {

template<typename DEST, typename SOURCE>
class ConversionTraits {
  // DEST convert(const SOURCE & );
};

template<typename LEFT, typename RIGHT>
class MultiplicationTraits {
 public:
  inline static LEFT mult(const LEFT &l, const RIGHT &r){
    return LEFT(typename LEFT::Implementation(l.toImplementation() * r.toImplementation()));
  }
};

template<typename QUATERNION>
class ComparisonTraits {
// public:
//  inline static bool isequal(const QUATERNION & a, const QUATERNION & b) {
//    return a.toImplementation() == b.toImplemenentation();
//  }
};

} // namespace internal

//! Base class that defines the interface of a quaternion
/*!
 * \see rm::rotations::RotationQuaternionBase for quaternions that represent a rotation
 */
template<typename DERIVED>
class QuaternionBase {
 public:
  /*! \returns the inverse of the quaternion
    */
  DERIVED inverse() const;

  /*! \returns the conjugate of the quaternion
    */
  DERIVED conjugate() const;

  operator DERIVED & () {
    return static_cast<DERIVED &>(*this);
  }
  operator const DERIVED & () const {
    return static_cast<const DERIVED &>(*this);
  }

  const DERIVED & derived() const {
    return static_cast<const DERIVED &>(*this);
  }

//  template<typename OTHER_DERIVED>
//  DERIVED operator *(const QuaternionBase<OTHER_DERIVED> & other) const {
//    return internal::MultiplicationTraits<DERIVED, OTHER_DERIVED>::mult((DERIVED)*this, (DERIVED)other);
//  }

//  template<typename OTHER_DERIVED> // todo: ambiguous for eigen_implementation::UnitQuaternion (inheritance diamond)
//  bool operator ==(const QuaternionBase<OTHER_DERIVED> & other) const {
//    return internal::ComparisonTraits<DERIVED>::isequal((DERIVED)*this, (DERIVED)other); // cast to Quaternion
//  }

};


//! Base class that defines the interface of a unit quaternion
/*!
 * \see rm::rotations::RotationQuaternionBase for quaternions that represent a rotation
 */
template<typename DERIVED>
class UnitQuaternionBase : public QuaternionBase<DERIVED> {
 public:
  typedef QuaternionBase<DERIVED> Base;

//  todo: how is it possible to use this?
//  DERIVED conjugate() const {
//    return DERIVED::conjugate();
//  }
//
//  DERIVED inverse() const {
//    return DERIVED::conjugate();
//  }

};




} // namespace quaternions
/*! @} End of Doxygen Groups*/
} // namespace rm

#endif /* QUATERNIONBASE_HPP_ */
