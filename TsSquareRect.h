#ifndef _TSSQUARERECT
#define _TSSQUARERECT

#include "TsPoint.h"

template<class T>
class TsSquareRect
{
public:
	void SetRect(T,T,T,T);
	TsPoint<T> GetHorizonValue();
	TsPoint<T> GetVerticalValue();
	T GetLength();
	T GetHeight();
private:
	T minX;
	T maxX;
	T minY;
	T maxY;
};

template<class T>
T TsSquareRect<T>::GetHeight()
{
	return maxY - minY;
}

template<class T>
T TsSquareRect<T>::GetLength()
{
	return maxX - minX;
}

template<class T>
TsPoint<T> TsSquareRect<T>::GetVerticalValue()
{
	return TsPoint<T>(minY,maxY);
}

template<class T>
TsPoint<T> TsSquareRect<T>::GetHorizonValue()
{
	return TsPoint<T>(minX,maxX);
}

template<class T>
void TsSquareRect<T>::SetRect( T minX,T maxX,T minY,T maxY )
{
	this->minX = minX;
	this->maxX = maxX;
	this->minY = minY;
	this->maxY = maxY;
}

#endif