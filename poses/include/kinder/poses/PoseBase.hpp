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
#ifndef KINDER_POSESBASE_HPP_
#define KINDER_POSESBASE_HPP_


#include "kinder/common/common.hpp"


namespace kinder {
//! Generic pose interface
/*! \ingroup poses
 */
namespace poses {
//! Internal stuff (only for developers)
namespace internal {

template<typename POSE>
class TransformationTraits {
 public:
//  inline static Position transform(const Pose & pose, const Position & position);
//  inline static Position inverseTransform(const Pose & pose, const Position & position);
};

template<typename POSE>
class get_position {
 public:
//  typedef typename positions::eigen_implementation::Position3D Position;
};

} // namespace internal



template<typename DERIVED>
class PoseBase {
 public:
  /*! \brief Standard constructor.
    *  Creates an empty generic pose object
    */
  PoseBase() = default;

  /*! \brief Constructor from derived pose.
   *  This constructor has been deleted because the abstract class does not contain any data.
   */
  PoseBase(const DERIVED &) = delete; // on purpose!!

  /*! \brief Gets the derived pose.
   *  (only for advanced users)
   *  \returns the derived pose
   */
  operator DERIVED & () {
    return static_cast<DERIVED &>(*this);
  }

  /*! \brief Gets the derived pose.
   *  (only for advanced users)
   *  \returns the derived pose
   */
  operator const DERIVED & () const {
    return static_cast<const DERIVED &>(*this);
  }

  /*! \brief Gets the derived pose.
   *  (only for advanced users)
   *  \returns the derived pose
   */
  const DERIVED & derived() const {
    return static_cast<const DERIVED &>(*this);
  }


  /*! \brief Transforms a position
   *  \returns the transformed position
   */
  typename internal::get_position<DERIVED>::Position transform(typename internal::get_position<DERIVED>::Position & position) const {
    return internal::TransformationTraits<DERIVED>::transform(this->derived(), position);
  }

  /*! \brief Transforms a position
   *  \returns the transformed position
   */
  typename internal::get_position<DERIVED>::Position inverseTransform(typename internal::get_position<DERIVED>::Position & position) const {
    return internal::TransformationTraits<DERIVED>::inverseTransform(this->derived(), position);
  }


};

template<typename DERIVED>
class HomogeneousTransformationBase : public PoseBase<DERIVED> {
 public:

  template<typename OTHER_DERIVED>
  HomogeneousTransformationBase & operator =(const HomogeneousTransformationBase<OTHER_DERIVED> & other) {
    return *this;
  }

};


} // namespace internal

namespace internal {

} // namespace poses
} // namespace kinder


#endif /* KINDER_POSESBASE_HPP_ */
