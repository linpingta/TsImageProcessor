#ifndef _H_TSFUNCTION_INCLUDED_
#define _H_TSFUNCTION_INCLUDED_

class TsFunction
{
public:
	template<class T>
	static bool BeInLimitaion(T value,T lowBoundary,T upBoundary);
};

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

#endif