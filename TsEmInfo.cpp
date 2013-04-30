#include "TsEmInfo.h"
#include "TsFunction.h"
#include "TsConstantVariable.h"
#include <math.h>

void TsEmInfo::Init(int grayScale,int clusterNum)
{
	x_em = new float[grayScale + 1]();
	histogram_em = new float[grayScale + 1]();
	mu_em = new float[clusterNum]();
	v_em = new float[clusterNum]();
	p_em = new float[clusterNum]();
	prb_em = new float*[grayScale + 1]();
	for (int i = 0; i < grayScale + 1;++i)
	{
		prb_em[i] = new float[clusterNum]();
	}
	scal_em = new float[grayScale + 1]();
	pp_em = new float[grayScale + 1]();
	c_em = new float[clusterNum]();
}

void TsEmInfo::Release()
{
	TsFunction::ReleaseMemoryOfArray<float>(x_em);
	TsFunction::ReleaseMemoryOfArray<float>(histogram_em);
	TsFunction::ReleaseMemoryOfArray<float>(mu_em);
	TsFunction::ReleaseMemoryOfArray<float>(v_em);
	TsFunction::ReleaseMemoryOfArray<float>(p_em);
	TsFunction::ReleaseMemoryOfArray<float>(scal_em);
	TsFunction::ReleaseMemoryOfArray<float>(pp_em);
	TsFunction::ReleaseMemoryOfArray<float>(c_em);

	TsFunction::ReleaseMemeoryOfMatrix<float,int>(prb_em,TsConstantVariable::kMaxGrayValue);
}

void TsEmInfo::ExecuteMaxiumStep(int grayScale,int clusterNum)
{
	for (int i = 0;i < clusterNum;++i)
	{
		float sumPP = 0.0;
		for (int j = 0;j < grayScale;++j)
		{
			if (scal_em[j] < 1e-10)
			{
				int a = 0;	
			}
			pp_em[j] = histogram_em[j] * prb_em[j][i] / scal_em[j];
			sumPP += pp_em[j];
		}
		p_em[i] = sumPP;

		float sumMu = 0.0;
		for (int j = 0;j < grayScale;++j)
		{
			sumMu += (x_em[j] * pp_em[j]);
		}
		mu_em[i] = sumMu / p_em[i];

		float sumV = 0.0;
		for (int j = 0;j < grayScale;++j)
		{
			sumV += (pp_em[j] * (x_em[j] - mu_em[i]) * (x_em[j] - mu_em[i]));
		}
		v_em[i] = sumV / p_em[i];
	}
}

void TsEmInfo::ExecuteEM(int grayScale,int clusterNum)
{
	float loglik = 0.0;
	float beforeLogLik = 0.0;
	int nStep = 0;

	while (1)
	{
		// E Step
		CalculateDistribution(grayScale, clusterNum, prb_em, mu_em, v_em, p_em, x_em);
		CalculateScal(grayScale, scal_em, clusterNum, prb_em);
		loglik = GetLogLikehood(grayScale, histogram_em, scal_em);

		// Exit
		if ((nStep> 0 && fabs(beforeLogLik - loglik) < 0.0001) || nStep > 40)
		{
			break;
		}

		// M Step
		ExecuteMaxiumStep(grayScale,clusterNum);

		beforeLogLik = loglik;
		++nStep;
	}
}

void TsEmInfo::CalculateDistribution( int grayScale, int clusterNum, float** prb, float*mu, float* v, float* p, float* x )
{
	for (int j = 0;j < clusterNum;++j)
	{
		for (int i = 0;i < grayScale;++i)
		{
			prb[i][j] = p[j] / (sqrt(2 * TsConstantVariable::kPI * v[j])) * exp(-0.5 * (x[i] - mu[j]) * (x[i] - mu[j]) / v[j]);
		}
	}
}

void TsEmInfo::CalculateScal( int grayScale, float* scal, int clusterNum, float** prb )
{
	for (int i = 0;i < grayScale;++i)
	{
		scal[i] = 0;
		for (int j = 0;j < clusterNum;++j)
		{
			scal[i] += prb[i][j];
		}
	}
}

float TsEmInfo::GetLogLikehood( int grayScale, float* histogram, float* scal )
{
	float loglik = 0.0;
	for (int i = 0;i < grayScale;++i)
	{
		loglik += (histogram[i] * log(scal[i]));
	}	
	return loglik;
}

void TsEmInfo::AddMeanInEM( int minGrayValue,int clusterNum )
{
	for (int i = 0;i < clusterNum;++i)
	{
		mu_em[i] += (minGrayValue - 1);
	}
}

void TsEmInfo::SetHistogramInfo(TsImageProcess m,TsPoint<int> grayBoundary)
{
	unsigned int** image = m.GetImage();
	unsigned int l = m.GetLength();
	unsigned int h = m.GetHeight();

	for (int i = 0;i < TsConstantVariable::kMaxGrayValue;++i)
	{
		histogram_em[i] = 0;
	}

	for (int i = 0;i < l;++i)
	{
		for (int j = 0;j < h;++j)
		{
			if (image[i][j] - grayBoundary.x < 0 || image[i][j] - grayBoundary.x > TsConstantVariable::kMaxGrayValue)
			{
				continue;
			}
			histogram_em[image[i][j] - grayBoundary.x] += 1;
		}
	}
}

void TsEmInfo::SetEmInfoInitialization(int l,int h,int grayScale,int clusterNum)
{
	for (int i = 0;i < grayScale;++i)
	{
		x_em[i] = i + 1;
		histogram_em[i] /=  (l * h);
	}

	for (int i = 0;i < clusterNum;++i)
	{
		mu_em[i] = static_cast<float>((i + 1)) * grayScale / (clusterNum + 1);
		v_em[i] = static_cast<float>(grayScale);
		p_em[i] = 1.0 / clusterNum;
	}
}

void TsEmInfo::SetMaskInImage(TsImageProcess& windowImage,TsImageProcess& windowMask,int clusterNum)
{
	int window_length = windowImage.GetLength();
	int window_height = windowImage.GetHeight();
	unsigned int** windowImg = windowImage.GetImage();

	for (int i = 0;i < window_length;++i)
	{
		for (int j = 0;j < window_height;++j)
		{
			float maxC = 0.0;
			int maxIndex = -1;
			for (int k = 0;k < clusterNum;++k)
			{
				c_em[k] = p_em[k] / (sqrt(2 * TsConstantVariable::kPI * v_em[k])) * exp(-0.5 * (windowImg[i][j] - mu_em[k]) * (windowImg[i][j] - mu_em[k]) / v_em[k]);
				if (c_em[k] > maxC)
				{
					maxC = c_em[k];
					maxIndex = k;
				}
			}

			windowMask.SetPointValueInImage(maxIndex,i,j);
		}
	}
}
