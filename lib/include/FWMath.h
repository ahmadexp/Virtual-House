
#ifndef __FW_MATH_H__
#define __FW_MATH_H__

#ifdef _WIN32
#define __attribute__(x)
#include <scalar/cpp/vectormath_aos.h>
#endif//_WIN32

#ifdef __linux__
#include <scalar/cpp/vectormath_aos.h>
#endif//__linux__

#ifdef __CELLOS_LV2__
#include <vectormath/cpp/vectormath_aos.h>
#endif//__CELLOS_LV2__

using namespace Vectormath::Aos;

#endif //__FW_MATH_H__
