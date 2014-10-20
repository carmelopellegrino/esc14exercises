#ifndef Vect_H
#define Vect_H

#include "Vector3D.h"


#include "VecFun.h"


namespace vect3d {
  struct ZERO{
    operator Vector3D<float>() const { float zerol=0.; return Vector3D<float>(zerol,zerol,zerol); }
    operator Vector3D<double>() const { double zerol=0.; return Vector3D<double>(zerol,zerol,zerol); }
  };
}

#endif
