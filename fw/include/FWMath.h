
#ifndef __FW_MATH_H__
#define __FW_MATH_H__

#ifdef _WIN32
#define __attribute__(x)
#include <scalar/cpp/vectormath_aos.h>
#endif//_WIN32

#ifdef __linux__
#include <scalar/cpp/vectormath_aos.h>
#endif//__linux__

#ifdef __APPLE__
#define __attribute__(x)
#include <scalar/cpp/vectormath_aos.h>
#endif//__APPLE__

using namespace Vectormath::Aos;

#endif //__FW_MATH_H__
