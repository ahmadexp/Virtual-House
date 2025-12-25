
#ifndef __FW_MACOSTIME_H__
#define __FW_MACOSTIME_H__

#include <sys/time.h>

#define _MICROSECS	1000000.0

class FWTimeVal;

// Time class
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

// Time value class. Time is stored in microseconds.
class FWTimeVal
{
public:
	inline				FWTimeVal()
	{
		mVal = 0;
	}

	inline				FWTimeVal(const FWTimeVal &val)
	{
		mVal = val.mVal;
	}

	inline				FWTimeVal(float secs)
	{
		mVal = (long long int)((double)secs * _MICROSECS);
	}

	inline				FWTimeVal(double secs)
	{
		mVal = (long long int)(secs * _MICROSECS);
	}

	inline FWTimeVal	operator+(const FWTimeVal &val) const
	{
		FWTimeVal ret;
		ret.mVal = mVal + val.mVal;
		return ret;
	}

	inline FWTimeVal	operator-(const FWTimeVal &val) const
	{
		FWTimeVal ret;
		ret.mVal = mVal - val.mVal;
		return ret;
	}

	inline FWTimeVal	operator*(float mul) const
	{
		FWTimeVal ret;
		ret.mVal = (long long int)((double)mVal * (double)mul);
		return ret;
	}

	inline FWTimeVal	operator/(float div) const
	{
		FWTimeVal ret;
		ret.mVal = (long long int)((double)mVal / (double)div);
		return ret;
	}

	inline double		operator/(const FWTimeVal &val) const
	{
		return (double)mVal / (double)val.mVal;
	}

	inline				operator float() const
	{
		return (float)((double)mVal / _MICROSECS);
	}

	inline				operator double() const
	{
		return (double)mVal / _MICROSECS;
	}

	inline FWTimeVal	&operator=(const FWTimeVal &val)
	{
		mVal = val.mVal;
		return *this;
	}

	inline bool			operator<(const FWTimeVal &val) const
	{
		return mVal < val.mVal;
	}

	inline bool			operator>(const FWTimeVal &val) const
	{
		return mVal > val.mVal;
	}

	inline bool			operator==(const FWTimeVal &val) const
	{
		return mVal == val.mVal;
	}

	inline bool			operator!=(const FWTimeVal &val) const
	{
		return mVal != val.mVal;
	}

	inline double		getMicroseconds() const
	{
		return (double)mVal;
	}

	inline double		getMilliseconds() const
	{
		return (double)mVal / 1000.0;
	}

	inline double		getSeconds() const
	{
		return (double)mVal / _MICROSECS;
	}

private:
	long long int		mVal;
	
	friend class		FWTime;
};

#endif//__FW_MACOSTIME_H__
