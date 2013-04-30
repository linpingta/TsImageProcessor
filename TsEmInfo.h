#ifndef _TSEMINFO_
#define _TSEMINFO_

#include "TsImageProcessor.h"

class TsEmInfo
{
public:
	void Init(int grayScale,int clusterNum);
	void Release();
	void ExecuteEM(int grayScale,int clusterNum);
	void ExecuteMaxiumStep(int grayScale,int clusterNum);
	void CalculateDistribution( int grayScale, int clusterNum, float** prb, float*mu, float* v, float* p, float* x );
	void CalculateScal( int grayScale, float* scal, int clusterNum, float** prb );
	float GetLogLikehood( int grayScale, float* histogram, float* scal );
	void AddMeanInEM(int minGrayValue,int clusterNum);
	void SetHistogramInfo(TsImageProcess,TsPoint<int>);
	void SetEmInfoInitialization(int,int,int,int);
	void SetMaskInImage(TsImageProcess&,TsImageProcess&,int);
private:
	float* x_em;
	float* histogram_em;
	float* mu_em;
	float* v_em;
	float* p_em;
	float** prb_em;
	float* scal_em;
	float* pp_em;
	float* c_em;
};

#endif