#include <advanlys.h>
#include <utility.h>
#include <formatio.h>
#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include "P1.h"

#define SAMPLE_RATE		0
#define NPOINTS			1

static int 		mainPanel;
static int 		frequencyPanel;

static int 		waveInfo[2]; //waveInfo[0] = sampleRate
				 			//waveInfo[1] = number of elements
static double 	sampleRate = 0.0;
static int		npoints = 0;
static double* 	waveData = 0;
static double* 	filterWave = 0;

static int 		start = 0, stop = 1;
WindowConst 	winConst;

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((mainPanel = LoadPanel (0, "P1.uir", Main_Panel)) < 0)
		return -1;
	if ((frequencyPanel = LoadPanel (0, "P1.uir", FRQ_Panel)) < 0)
		return -1;
	
	DisplayPanel (mainPanel);
	RunUserInterface ();
	DiscardPanel (mainPanel);
	
	return 0;
}

int CVICALLBACK OnMainPanel (int panel, int event, void *callbackData,
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

int CVICALLBACK OnLoadButtonCB (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			//executa script python pentru conversia unui fisierului .wav in .txt
			LaunchExecutable("python main.py");
			
			//astept sa fie generate cele doua fisiere (modificati timpul daca este necesar
			//Delay(1);
			
			//incarc informatiile privind rata de esantionare si numarul de valori
			FileToArray("waveInfo.txt", waveInfo, VAL_INTEGER, 2, 1, VAL_GROUPS_TOGETHER, VAL_GROUPS_AS_COLUMNS, VAL_ASCII);
			sampleRate = waveInfo[SAMPLE_RATE];
			npoints = waveInfo[NPOINTS];
			
			//alocare memorie pentru numarul de puncte
			waveData = (double *) calloc(npoints, sizeof(double));
			
			//incarcare din fisierul .txt in memorie (vector)
			FileToArray("waveData.txt", waveData, VAL_DOUBLE, npoints, 1, VAL_GROUPS_TOGETHER, VAL_GROUPS_AS_COLUMNS, VAL_ASCII);
	
			//afisare pe grapf
			PlotY(panel, Main_Panel_Graph_Panel, waveData, npoints, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, VAL_CONNECTED_POINTS, VAL_RED);
			double min = 0;
			double max = 0;
			double suma = 0;
			double dispersie;
			double median;
			
			for(int i = 0; i < waveInfo[1]; ++i){
				if(waveData[i] > max)
					max = waveData[i];
				if(waveData[i] < min)
					min = waveData[i];
				suma = suma + waveData[i];
				
			}
			int zero_crossing = 0;
			for(int i = 0 ;i<waveInfo[1] - 1;++i)
			{
				if(waveData[i] < 0 && waveData[i+1] > 0)
					zero_crossing++;
				if(waveData[i] > 0 && waveData[i+1] < 0)
					zero_crossing++;
					
			}
			
			SetCtrlVal(panel, Main_Panel_Zero_Crossing,zero_crossing);
			SetCtrlVal(panel,Main_Panel_Min_Numeric, min);
			SetCtrlVal(panel, Main_Panel_Max_Numeric, max);
			SetCtrlVal(panel, Main_Panel_Medie_Numeric, (suma/waveInfo[1]));
			Variance(waveData, waveInfo[1], &median, &dispersie);
			SetCtrlVal(panel, Main_Panel_Median_Numeric, median);
			SetCtrlVal(panel, Main_Panel_Dispersie_Numeric, dispersie);
			
			SetCtrlAttribute (panel, Main_Panel_Apply_Button, ATTR_DIMMED, 0);
			SetCtrlAttribute (panel, Main_Panel_IDC_SWITCH_PANEL, ATTR_DIMMED, 0);
			break;
	}
	return 0;
}

int CVICALLBACK OnLoadButtonCB2 (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	int N;
	double* autoSpectrum;
	double* convertedSpectrum, *nWave, *temp,*filtered, *convertedSpectrum_win, *convertedSpectrum_filter;
	double df, Freq_Peak, Power_Peak;
	int wind, filt;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(panel,FRQ_Panel_NUMERIC_PUNCTE, &N);
			nWave=(double*)malloc(N*sizeof(double));
			temp=(double*)malloc(N*sizeof(double));
			filtered=(double*)malloc(2*N*sizeof(double));
			autoSpectrum=(double*)malloc(N/2*sizeof(double));
			convertedSpectrum=(double*)malloc(N/2*sizeof(double));
			convertedSpectrum_win=(double*)malloc(N/2*sizeof(double));
			convertedSpectrum_filter=(double*)malloc(N/2*sizeof(double));
		
			
			GetCtrlVal(panel, FRQ_Panel_WINDOW_SWITCH, &wind);
			GetCtrlVal(panel, FRQ_Panel_FILTER_SWITCH, &filt);
			
			int a=0;
			while(a<npoints)
			{
				if(a+N<=npoints)
				{
					for(int i=0;i<N;i++)
					{
						nWave[i]=waveData[i+a];
						temp[i]=waveData[i+a];
					}
				}
				else
				{
					int rem=npoints-a;
					for(int i=0;i<rem;i++){
						nWave[i]=waveData[i+a];
						temp[i]=waveData[i+a];
					}
					for(int i=rem;i<N;i++){
						nWave[i]=0;
						temp[i]=0;
					}
				}
				ScaledWindowEx(nWave,N, RECTANGLE_, 0, &winConst);
			
				AutoPowerSpectrum(nWave,N, 1/sampleRate, autoSpectrum, &df);
			
				PowerFrequencyEstimate(autoSpectrum,N/2, -1 ,winConst,df,7, &Freq_Peak, &Power_Peak);
				SetCtrlVal(panel, FRQ_Panel_NUMERIC_FREQUENCY, Freq_Peak);
				SetCtrlVal(panel, FRQ_Panel_NUMERIC_POWER, Power_Peak);
				
				char Unit[32]="V";
			
				SpectrumUnitConversion(autoSpectrum,N/2,0,SCALING_MODE_LINEAR,DISPLAY_UNIT_VRMS,df, winConst, 
								   convertedSpectrum, Unit);
				switch(wind){
					case 0:
						ScaledWindowEx(nWave,N,RECTANGLE,0,&winConst);
						break;
					case 1:
						ScaledWindowEx(nWave,N,BLKMAN,0,&winConst);
						break;
				}
				
				AutoPowerSpectrum(nWave,N, 1/sampleRate, autoSpectrum, &df);
			
				PowerFrequencyEstimate(autoSpectrum,N/2, -1 ,winConst,df,7, &Freq_Peak, &Power_Peak);
				SpectrumUnitConversion(autoSpectrum,N/2,0,SCALING_MODE_LINEAR,DISPLAY_UNIT_VRMS,df, winConst, 
								   convertedSpectrum_win, Unit);
				
				switch(filt){
					case 0:
						double fs;
						double fc;
						double atten;
						double order;
								
						GetCtrlVal(frequencyPanel, FRQ_Panel_FS, &fs);
						GetCtrlVal(frequencyPanel, FRQ_Panel_FC, &fc);
						GetCtrlVal(frequencyPanel, FRQ_Panel_ATTEN, &atten);
						GetCtrlVal(frequencyPanel, FRQ_Panel_ORDER, &order);
										
						InvCh_LPF(nWave, N, sampleRate, N/3, atten, order, filtered); 
						break;
					case 1:
						SetCtrlAttribute (panel, Main_Panel_Apply_Button, ATTR_DIMMED, 0);
						filtered[0]=nWave[0]; filtered[1]=nWave[1];// wfm – semnalul dat, wfN rezultatul filtrarii
						double r; //se va citi de pe un control nou
						double ffreq = 2;
						double frequency= 1000;
						GetCtrlVal(frequencyPanel, FRQ_Panel_FFREQ, &ffreq);
						GetCtrlVal(frequencyPanel, FRQ_Panel_R, &r);
						double p=cos(2*3.14*ffreq/frequency);// ffreq – frecv. de taiere (normalizata)
						
						for(int i=2;i<sampleRate;i++)//dimensiunea bufferului =1024 sau se inlocuieste//cu numarul de esantioane
							filtered[i]= 2*r*p*filtered[i-1]-r*r*filtered[i-2]+nWave[i]-2*p*nWave[i-1]+nWave[i-2] ;
						
						break;
						
				}
				
				AutoPowerSpectrum(filtered,N, 1/sampleRate, autoSpectrum, &df);
			
				PowerFrequencyEstimate(autoSpectrum,N/2, -1 ,winConst,df,7, &Freq_Peak, &Power_Peak);
				SpectrumUnitConversion(autoSpectrum,N/2,0,SCALING_MODE_LINEAR,DISPLAY_UNIT_VRMS,df, winConst, 
								   convertedSpectrum_filter, Unit);
				
						
			
				PlotWaveform(panel, FRQ_Panel_GRAPH_SPECTRU, convertedSpectrum, N/2, VAL_DOUBLE, 1.0, 0.0, 0.0, df,
						 VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, 1, VAL_YELLOW);
				PlotWaveform(panel, FRQ_Panel_GRAPH_PANEL, temp, N/2, VAL_DOUBLE, 1.0, 0.0, 0.0, df,
						 VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, 1, VAL_YELLOW);
				
				PlotWaveform(panel, FRQ_Panel_GRAPH_PANEL_WINDOW, nWave, N/2, VAL_DOUBLE, 1.0, 0.0, 0.0, df,
						 	VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, 1, VAL_RED);
				PlotWaveform(panel, FRQ_Panel_GRAPH_SPECTRU_WINDOW, convertedSpectrum_win, N/2, VAL_DOUBLE, 1.0, 0.0, 0.0, df,
						 VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, 1, VAL_RED);
				
				PlotWaveform(panel, FRQ_Panel_GRAPH_PANEL_FILTER, filtered, N/2, VAL_DOUBLE, 1.0, 0.0, 0.0, df,
						 VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, 1, VAL_GREEN);
				PlotWaveform(panel, FRQ_Panel_GRAPH_SPECTRU_FILTER, convertedSpectrum_filter, N/2, VAL_DOUBLE, 1.0, 0.0, 0.0, df,
						 VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, 1, VAL_GREEN);
				
				a=a+N;
				
				Delay(2);
				DeleteGraphPlot(panel, FRQ_Panel_GRAPH_SPECTRU, -1, VAL_IMMEDIATE_DRAW);
				DeleteGraphPlot(panel, FRQ_Panel_GRAPH_PANEL, -1, VAL_IMMEDIATE_DRAW);
				
				DeleteGraphPlot(panel, FRQ_Panel_GRAPH_PANEL_WINDOW, -1, VAL_IMMEDIATE_DRAW);
				DeleteGraphPlot(panel, FRQ_Panel_GRAPH_SPECTRU_WINDOW, -1, VAL_IMMEDIATE_DRAW);
				
				DeleteGraphPlot(panel, FRQ_Panel_GRAPH_PANEL_FILTER, -1, VAL_IMMEDIATE_DRAW);
				DeleteGraphPlot(panel, FRQ_Panel_GRAPH_SPECTRU_FILTER, -1, VAL_IMMEDIATE_DRAW);
			}
			free(autoSpectrum);
			free(convertedSpectrum);
			free(nWave);
			free(filtered);
			free(convertedSpectrum_win);
			free(convertedSpectrum_filter);
			free(temp);
			
			autoSpectrum = 0;
			convertedSpectrum = 0;
			nWave = 0;
			temp =0;
			filtered = 0;
			convertedSpectrum_win = 0;
			convertedSpectrum_filter = 0;
			
			
			break;
	}
	return 0;
}

int CVICALLBACK OnApply (int panel, int control, int event,
						 void *callbackData, int eventData1, int eventData2)
{
	int filter;
	switch (event)
	{
		case EVENT_COMMIT:
			DeleteGraphPlot(panel, Main_Panel_Graph_Panel_Filter, -1, VAL_IMMEDIATE_DRAW);
			GetCtrlVal(panel, Main_Panel_Filter_Switch, &filter);
			if(filterWave!=0)
			{
				free(filterWave);
				filterWave = 0;
			}
			filterWave = (double *) calloc(npoints, sizeof(double));
			SetCtrlVal(panel, Main_Panel_Start_Numeric, 0);
			SetCtrlVal(panel, Main_Panel_Stop_Numeric, 1);
			
			if(filter == 0){
				int n;
				double sum0 = 0;
				GetCtrlVal(panel, Main_Panel_Median_Number_Switch, &n);
				for(int i = 0; i < n; i++)
					sum0 += waveData[i];
				for(int i = 0; i < n; i++)
					filterWave[i] = sum0/n;
				for(int i = n; i < waveInfo[1]; i++){
					sum0 -= waveData[i-n];
					sum0 += waveData[i];
					filterWave[i] = sum0/n;
				}
				PlotY(panel, Main_Panel_Graph_Panel_Filter, filterWave, npoints, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, VAL_CONNECTED_POINTS, VAL_GREEN);
			}
			else{
				
				double alpha;
				
				GetCtrlVal(panel, Main_Panel_Alpha_Numeric, &alpha);
				filterWave[0] = waveData[0];
				for(int i = 1; i < waveInfo[1]; i++)
					filterWave[i] = (1-alpha)*filterWave[i-1] + alpha*waveData[i];
				
				PlotY(panel, Main_Panel_Graph_Panel_Filter, filterWave, npoints, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, VAL_CONNECTED_POINTS, VAL_GREEN);
				
			}
			SetCtrlAttribute (panel, Main_Panel_Prev_Button, ATTR_DIMMED, 0);
			SetCtrlAttribute (panel, Main_Panel_Next_Button, ATTR_DIMMED, 0);
			
			break;
	}
	return 0;
}

int CVICALLBACK OnChangeSecond (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	double * temp;

	switch (event)
	{
		case EVENT_COMMIT:
	
			
			GetCtrlVal(panel,Main_Panel_Start_Numeric, &start);
			GetCtrlVal(panel, Main_Panel_Stop_Numeric, &stop);
			
			temp = (double *) calloc(npoints/6, sizeof(double));
			switch(control)
			{
				case Main_Panel_Next_Button:				
					if(stop<6)
					{
						DeleteGraphPlot(panel, Main_Panel_Graph_Panel_Filter, -1, VAL_IMMEDIATE_DRAW);
								
						++start;
						++stop;
						SetCtrlVal(panel, Main_Panel_Start_Numeric, start);
						SetCtrlVal(panel, Main_Panel_Stop_Numeric, stop);
							
						for(int i=0;i<npoints/6;++i)
								temp[i] = filterWave[start*npoints/6 + i ];
							
							PlotY(panel, Main_Panel_Graph_Panel_Filter, temp, npoints/6, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, VAL_CONNECTED_POINTS, VAL_RED);
							int id;
							GetCtrlDisplayBitmap(panel, Main_Panel_Graph_Panel_Filter, 0, &id);
							SaveBitmapToJPEGFile(id, "Poza.jpg", JPEG_PROGRESSIVE, 100);
					}
				break;	
				
				
				case Main_Panel_Prev_Button:
					if(stop>1){
								DeleteGraphPlot(panel, Main_Panel_Graph_Panel_Filter, -1, VAL_IMMEDIATE_DRAW);
								--start;
								--stop;
								SetCtrlVal(panel, Main_Panel_Start_Numeric, start);
								SetCtrlVal(panel, Main_Panel_Stop_Numeric, stop);
								
								for(int i=0;i<npoints/6;++i)
									temp[i] = filterWave[start*npoints/6 + i ];
								
								
								PlotY(panel, Main_Panel_Graph_Panel_Filter, temp, npoints/6, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, VAL_CONNECTED_POINTS, VAL_RED);
								int id;
								GetCtrlDisplayBitmap(panel, Main_Panel_Graph_Panel_Filter, 0, &id);
								SaveBitmapToJPEGFile(id, "Poza.jpg", JPEG_PROGRESSIVE, 100);
								
							}
						
				break;
				
			}
			free(temp);
			temp = 0;
			break;
	}
	return 0;
}


int CVICALLBACK OnSwitchPanelCB (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(panel == mainPanel)
			{
				SetCtrlVal(frequencyPanel, FRQ_Panel_IDC_SWITCH_PANEL, 1);
				DisplayPanel(frequencyPanel);
				HidePanel(panel);
			}
			else
			{
				SetCtrlVal(mainPanel, Main_Panel_IDC_SWITCH_PANEL, 0);
				DisplayPanel(mainPanel);
				HidePanel(panel);
			}
			break;
	}
	return 0;
}






