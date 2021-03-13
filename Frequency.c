#include <advanlys.h>
#include <userint.h>
#include "P1.h"

//==============================================================================
//
// Title:		Frequency.c
// Purpose:		A short description of the implementation.
//
// Created on:	19/11/2020 at 14:12:30 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

//#include "Frequency.h"

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables

//==============================================================================
// Static functions

//==============================================================================
// Global variables

//==============================================================================
// Global functions

/// HIFN  What does your function do?
/// HIPAR x/What inputs does your function expect?
/// HIRET What does your function return?







int CVICALLBACK OnFrequencyPanel (int panel, int event, void *callbackData,
								  int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			QuitUserInterface(0);
			break;
	}
	return 0;
}

/*
int CVICALLBACK OnLoadButtonCB2 (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	double freq_peak, power_peak; freq, amp;
	double autospectrum[npoints/2];
	double df;
	double spectrum[npoints/2];
	switch (event)
	{
		case EVENT_COMMIT:
			ScaledWindowEx (waveData, npoints, windowType, RECTANGLE_, &winConst);
			AutoPowerSpectrum(waveData, npoints, 1/sampleRate, autospectrum,&df);
			
			PowerFrequencyEstimate(autospectrum, npoints/2,1.0,"..."  ,df,7,&freq_peak,&power_peak);
			
			SpectrumUnitConversion(autospectrum, npoints/2, 0, SCALING_MODE_LINEAR, DISPLAY_UNIT_VPK, df,"..." ,spectrum,
								   "V");
			
			PlotXY(FRQ_Panel, FRQ_Panel_GRAPH_SPECTRU,spectrum, npoints/2,VAL_DOUBLE, 1.0, 0.0, 0.0, 1.0,VAL_THIN_LINE,
				  VAL_EMPTY_SQUARE, VAL_SOLID, 1, VAL_GREEN);
			

			break;
	}
	return 0;
}
*/

