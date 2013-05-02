#ifndef _H_TSFUNCTION_INCLUDED_
#define _H_TSFUNCTION_INCLUDED_

#include "TsRect.h"
#include "TsCenterRect.h"
#include "TsSquareRect.h"

class TsFunction
{
public:
	template<class T>
	static bool BeInLimitaion(T value,T lowBoundary,T upBoundary);
	template<class T>
	static T UpperBoundary(T value,T upBoundary);
	template<class T>
	static T LowerBoundary(T value,T lowBoundary);
	template<class T>
	static TsRect<T> TransferFromCenterRectToRect(TsCenterRect<T>);
	template<class T>
	static TsCenterRect<T> TransferFromRectToCenterRect(TsRect<T>);
	template<class T>
	static TsSquareRect<T> TransferFromRectToSquareRect(TsRect<T>);
	template<class T>
	static TsRect<T> TransferFromSquareToRect(TsSquareRect<T>);
	template<class T>
	static TsCenterRect<T> TransferFromSquareRectToCenterRect(TsSquareRect<T>);
	template<class T>
	static TsSquareRect<T> TransferFromCenterRectToSquareRect(TsCenterRect<T>);
	template<class T>
	static T SetValueBoundary(T,T);
	template<class T>
	static void ReleaseMemoryOfArray(T*);
	template<class T,class K>
	static void ReleaseMemeoryOfMatrix(T**,K);
};

template<class T>
static void TsFunction::ReleaseMemoryOfArray(T* val)
{
	if (val)
	{
		delete[] val;
		val = NULL;
	}
}

template<class T,class K>
static void TsFunction::ReleaseMemeoryOfMatrix(T** val,K length)
{
	if (val)
	{
		for (K i = 0;i < length;++i)
		{
			delete[] val[i];
		}
		delete[] val;
		val = NULL;
	}
}

template<class T>
static T TsFunction::UpperBoundary(T value,T upBoundary)
{
	if (value > upBoundary)
	{
		return upBoundary;
	}
	return value;
}

template<class T>
static T TsFunction::LowerBoundary(T value,T lowBoundary)
{
	if (value < lowBoundary)
	{
		return lowBoundary;
	}
	return value;
}

template<class T>
static T TsFunction::SetValueBoundary( T tmpHoriMove, T limitation ) 
{
	if (tmpHoriMove > limitation)
	{
		return limitation;
	}	
	if (tmpHoriMove < -limitation)
	{
		return -limitation;
	}
	return tmpHoriMove;
}

template<class T>
static TsSquareRect<T>
	TsFunction::TransferFromCenterRectToSquareRect( TsCenterRect<T> inputRect )
{
	TsSquareRect<T> returnValue;
	returnValue.SetRect(inputRect.GetCenter().x - inputRect.GetLength() / 2,
		inputRect.GetCenter().x + inputRect.GetLength() / 2,
		inputRect.GetCenter().y - inputRect.GetHeight() / 2,
		inputRect.GetCenter().y + inputRect.GetHeight() / 2);
	return returnValue;
}

template<class T>
static TsCenterRect<T>
	TsFunction::TransferFromSquareRectToCenterRect( TsSquareRect<T> inputRect )
{
	TsCenterRect<T> returnValue;
	returnValue.SetCenter(TsPoint<T>((inputRect.GetHorizonValue().x + inputRect.GetHorizonValue().y) / 2,
		(inputRect.GetVerticalValue().x + inputRect.GetVerticalValue().y) / 2));
	returnValue.SetLength(inputRect.GetLength());
	returnValue.SetHeight(inputRect.GetHeight());
	return returnValue;
}

template<class T>
static TsRect<T>
	TsFunction::TransferFromSquareToRect( TsSquareRect<T> inputRect)
{
	TsRect<T> returnValue;
	returnValue.SetLeftUpCorner(inputRect.GetHorizonValue().x,inputRect.GetVerticalValue().x);
	returnValue.SetLength(inputRect.GetLength());
	returnValue.SetHeight(inputRect.GetHeight());

	return returnValue;
}

template<class T>
static TsSquareRect<T>
	TsFunction::TransferFromRectToSquareRect( TsRect<T> inputRect )
{
	TsSquareRect<T> returnValue;

	returnValue.SetRect(inputRect.GetLeftUpCorner().x,inputRect.GetLeftUpCorner().x + inputRect.GetLength(),
		inputRect.GetLeftUpCorner().y,inputRect.GetLeftUpCorner().y + inputRect.GetHeight());

	return returnValue;
}

//************************************
// Method:    TransferFromCenterRectToRect
// FullName:  TsFunction<T>::TransferFromCenterRectToRect
// Access:    public static 
// Returns:   
// Qualifier: Transfer a region from (center,length,height) to (leftUpCorner,length,height)
// Parameter: TsCenterRect<T>
//************************************
template<class T>
static TsRect<T> TsFunction::TransferFromCenterRectToRect( TsCenterRect<T> inputRect)
{
	TsRect<T> returnValue;
	TsPoint<T> center = inputRect.GetCenter();
	T length = inputRect.GetLength();
	T height = inputRect.GetLength();
	returnValue.SetLeftUpCorner(TsPoint<int>(center.x - length / 2,center.y - height / 2));
	returnValue.SetLength(length);
	returnValue.SetHeight(height);
	return returnValue;
}

//************************************
// Method:    BeInLimitaion
// FullName:  TsFunction<T>::BeInLimitaion
// Access:    public static 
// Returns:   bool
// Qualifier: return true if value in [lowBoundary upBoundary]
// Parameter: T value
// Parameter: T lowBoundary
// Parameter: T upBoundary
//************************************
template<class T>
bool TsFunction::BeInLimitaion( T value,T lowBoundary,T upBoundary )
{
	return (value >= lowBoundary && value <= upBoundary);
}

//************************************
// Method:    TransferFromRectToCenterRect
// FullName:  TsFunction::TransferFromRectToCenterRect
// Access:    public static 
// Returns:   TsCenterRect<T>
// Qualifier: Transfer a region from (leftUpCorner,length,height) to (center,length,height)
// Parameter: TsRect<T>
//************************************
template<class T>
TsCenterRect<T> TsFunction::TransferFromRectToCenterRect( TsRect<T> inputRect )
{
	TsCenterRect<T> returnValue;
	TsPoint<T> leftUpCorner = inputRect.GetLeftUpCorner();
	T length = inputRect.GetLength();
	T height = inputRect.GetHeight();
	returnValue.SetCenter(leftUpCorner.x + length / 2,leftUpCorner.y + height / 2);
	returnValue.SetLength(length);
	returnValue.SetHeight(height);
	return returnValue;
}

#endif