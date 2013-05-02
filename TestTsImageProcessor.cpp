#include "TestHarness.h"
#include "TsImageProcessor.h"
#include "TsTracker.h"
#include "DLL_MISSILE_DECISION.h"

#include <stdlib.h>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

TEST( TsImageProcess, init)
{
	TsImageProcess m(10,20);
	LONGS_EQUAL(10,m.GetLength());
	LONGS_EQUAL(5,m.GetHeight());
}

TEST( TsTracker,Track )
{
	int id = 1;

	// Expected result
	char buffer[20];
	itoa(id,buffer,10);
	string buffer_s = buffer;
	string imgFilename = "测试数据/OriginalImage" + buffer_s + ".bmp";
	TsImageProcess m(10,10);
	//if (m.GetImage() == NULL)
	//{
	//	CHECK(false);
	//}
	TsTracker t;
	DLL_MISSILE_DECISION missileDecisionExpected = t.Track(m.GetImage(),m.GetLength(),m.GetHeight());

	// Actual result from file
	DLL_MISSILE_DECISION missileDecisionActual;
	string resultFilename = "测试数据/TestInfo.txt";
	ifstream fin(resultFilename);
	//if (!fin)
	//{
	//	CHECK(false);
	//}
	int k = 1;
	char str[100];
	while (k < id)
	{
		fin.getline(str,100);
		++k;
	}
	fin >> missileDecisionActual.btrack >> missileDecisionActual.bWindow >> missileDecisionActual.hori_move
		>> missileDecisionActual.track_height >> missileDecisionActual.track_left >> missileDecisionActual.track_top
		>> missileDecisionActual.track_width >> missileDecisionActual.verti_move >> missileDecisionActual.window_height
		>> missileDecisionActual.window_left >> missileDecisionActual.window_top >> missileDecisionActual.window_width;
	fin.close();

	LONGS_EQUAL(missileDecisionExpected.btrack,missileDecisionActual.btrack);
	LONGS_EQUAL(missileDecisionExpected.bWindow,missileDecisionActual.bWindow);
	LONGS_EQUAL(missileDecisionExpected.hori_move,missileDecisionActual.hori_move);
	LONGS_EQUAL(missileDecisionExpected.track_height,missileDecisionActual.track_height);
	LONGS_EQUAL(missileDecisionExpected.track_left,missileDecisionActual.track_left);
	LONGS_EQUAL(missileDecisionExpected.track_top,missileDecisionActual.track_top);
	LONGS_EQUAL(missileDecisionExpected.track_width,missileDecisionActual.track_width);
	LONGS_EQUAL(missileDecisionExpected.verti_move,missileDecisionActual.verti_move);
	LONGS_EQUAL(missileDecisionExpected.window_height,missileDecisionActual.window_height);
	LONGS_EQUAL(missileDecisionExpected.window_left,missileDecisionActual.window_left);
	LONGS_EQUAL(missileDecisionExpected.window_top,missileDecisionActual.window_top);
	LONGS_EQUAL(missileDecisionExpected.window_width,missileDecisionActual.window_width);
}


TEST( TsTracker,track_init )
{
	TsImageProcess m(320,256);
	m.LoadMatrix("测试数据/OriginalImage1.txt");
	TsTracker t;
	t.Track(m.GetImage(),m.GetLength(),m.GetHeight());
}