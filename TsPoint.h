#ifndef _H_TSPOINT_INCLUDED_
#define _H_TSPOINT_INCLUDED_

template<class T>
struct TsPoint
{
	T x;
	T y;

	TsPoint()
	{
		;
	}
	TsPoint(T _x,T _y)
	{
		x = _x;
		y = _y;
	}
};

#endif