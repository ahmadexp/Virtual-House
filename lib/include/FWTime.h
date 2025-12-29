#ifndef __FW_TIME_H__
#define __FW_TIME_H__

#ifdef _WIN32
#include "win32/FWWin32Time.h"
#endif//_MSC_VER

#ifdef __linux__
// Linux uses GLFW time implementation
#include <stdint.h>

#define _MICROSECS 1000000.0

class FWTimeVal;

class FWTime
{
public:
	static void				init();
	static FWTimeVal		getCurrentTime();
	static void				startTime();
	static void				stopTime();
	static void				update();
	static FWTimeVal		sZero;

private:
	static FWTimeVal		sStoppedTime;
	static FWTimeVal		sCurrentTime;
	static bool				sIsStopped;

	friend class			FWTimeVal;
};

class FWTimeVal
{
public:
	inline					FWTimeVal() { mVal = 0; }
	inline					FWTimeVal(const FWTimeVal &val) { mVal = val.mVal; }
	inline					FWTimeVal(float secs) { mVal = (uint64_t)((double)secs * _MICROSECS); }
	inline					FWTimeVal(double secs) { mVal = (uint64_t)(secs * _MICROSECS); }

	inline FWTimeVal	operator+(const FWTimeVal &val) const { FWTimeVal ret; ret.mVal = mVal + val.mVal; return ret; }
	inline FWTimeVal	operator-(const FWTimeVal &val) const { FWTimeVal ret; ret.mVal = mVal - val.mVal; return ret; }
	inline FWTimeVal	operator*(float mul) const { FWTimeVal ret; ret.mVal = (uint64_t)((double)mVal * (double)mul); return ret; }
	inline FWTimeVal	operator/(float div) const { FWTimeVal ret; ret.mVal = (uint64_t)((double)mVal / (double)div); return ret; }
	inline double		operator/(const FWTimeVal &val) const { return (double)mVal / (double)val.mVal; }
	inline					operator float() const { return (float)((double)mVal / _MICROSECS); }
	inline					operator double() const { return (double)mVal / _MICROSECS; }
	inline FWTimeVal	&operator=(const FWTimeVal &val) { mVal = val.mVal; return *this; }
	inline FWTimeVal	&operator+=(const FWTimeVal &val) { mVal += val.mVal; return *this; }
	inline FWTimeVal	&operator-=(const FWTimeVal &val) { mVal -= val.mVal; return *this; }
	inline bool			operator>(const FWTimeVal &val) const { return mVal > val.mVal; }
	inline bool			operator<(const FWTimeVal &val) const { return mVal < val.mVal; }
	inline bool			operator>=(const FWTimeVal &val) const { return mVal >= val.mVal; }
	inline bool			operator<=(const FWTimeVal &val) const { return mVal <= val.mVal; }
	inline bool			operator==(const FWTimeVal &val) const { return mVal == val.mVal; }
	inline bool			operator!=(const FWTimeVal &val) const { return mVal != val.mVal; }

	uint64_t				mVal;

	friend class			FWTime;
};
#endif//__linux__

#ifdef __CELLOS_LV2__
#include "cell/FWCellTime.h"
#endif//__CELLOS_LV2__

#endif//__FW_TIME_H__
