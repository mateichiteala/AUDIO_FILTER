/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  FRQ_Panel                        1       /* callback function: OnFrequencyPanel */
#define  FRQ_Panel_IDC_SWITCH_PANEL       2       /* control type: binary, callback function: OnSwitchPanelCB */
#define  FRQ_Panel_GRAPH_SPECTRU_FILTER   3       /* control type: graph, callback function: (none) */
#define  FRQ_Panel_GRAPH_SPECTRU_WINDOW   4       /* control type: graph, callback function: (none) */
#define  FRQ_Panel_GRAPH_SPECTRU          5       /* control type: graph, callback function: (none) */
#define  FRQ_Panel_GRAPH_PANEL_FILTER     6       /* control type: graph, callback function: (none) */
#define  FRQ_Panel_GRAPH_PANEL_WINDOW     7       /* control type: graph, callback function: (none) */
#define  FRQ_Panel_FILTER_SWITCH          8       /* control type: binary, callback function: (none) */
#define  FRQ_Panel_FFREQ                  9       /* control type: numeric, callback function: (none) */
#define  FRQ_Panel_ATTEN                  10      /* control type: numeric, callback function: (none) */
#define  FRQ_Panel_ORDER                  11      /* control type: numeric, callback function: (none) */
#define  FRQ_Panel_FC                     12      /* control type: numeric, callback function: (none) */
#define  FRQ_Panel_R                      13      /* control type: numeric, callback function: (none) */
#define  FRQ_Panel_FS                     14      /* control type: numeric, callback function: (none) */
#define  FRQ_Panel_GRAPH_PANEL            15      /* control type: graph, callback function: (none) */
#define  FRQ_Panel_WINDOW_SWITCH          16      /* control type: binary, callback function: (none) */
#define  FRQ_Panel_NUMERIC_PUNCTE         17      /* control type: numeric, callback function: (none) */
#define  FRQ_Panel_Load_Button2           18      /* control type: command, callback function: OnLoadButtonCB2 */
#define  FRQ_Panel_NUMERIC_FREQUENCY      19      /* control type: numeric, callback function: (none) */
#define  FRQ_Panel_NUMERIC_POWER          20      /* control type: numeric, callback function: (none) */

#define  Main_Panel                       2       /* callback function: OnMainPanel */
#define  Main_Panel_IDC_SWITCH_PANEL      2       /* control type: binary, callback function: OnSwitchPanelCB */
#define  Main_Panel_Apply_Button          3       /* control type: command, callback function: OnApply */
#define  Main_Panel_Next_Button           4       /* control type: command, callback function: OnChangeSecond */
#define  Main_Panel_Prev_Button           5       /* control type: command, callback function: OnChangeSecond */
#define  Main_Panel_Load_Button           6       /* control type: command, callback function: OnLoadButtonCB */
#define  Main_Panel_Graph_Panel_Filter    7       /* control type: graph, callback function: (none) */
#define  Main_Panel_Graph_Panel           8       /* control type: graph, callback function: (none) */
#define  Main_Panel_Max_Numeric           9       /* control type: numeric, callback function: (none) */
#define  Main_Panel_Medie_Numeric         10      /* control type: numeric, callback function: (none) */
#define  Main_Panel_Dispersie_Numeric     11      /* control type: numeric, callback function: (none) */
#define  Main_Panel_Median_Numeric        12      /* control type: numeric, callback function: (none) */
#define  Main_Panel_Alpha_Numeric         13      /* control type: numeric, callback function: (none) */
#define  Main_Panel_Stop_Numeric          14      /* control type: numeric, callback function: (none) */
#define  Main_Panel_Start_Numeric         15      /* control type: numeric, callback function: (none) */
#define  Main_Panel_Zero_Crossing         16      /* control type: numeric, callback function: (none) */
#define  Main_Panel_Min_Numeric           17      /* control type: numeric, callback function: (none) */
#define  Main_Panel_Filter_Switch         18      /* control type: binary, callback function: (none) */
#define  Main_Panel_Median_Number_Switch  19      /* control type: binary, callback function: (none) */

#define  WIN_Panel                        3       /* callback function: OnWinPanel */
#define  WIN_Panel_IDC_SWITCH_PANEL       2       /* control type: binary, callback function: OnSwitchPanelCB */
#define  WIN_Panel_GRAPH_FILTER           3       /* control type: graph, callback function: (none) */
#define  WIN_Panel_GRAPH_WINDOW           4       /* control type: graph, callback function: (none) */
#define  WIN_Panel_Prev_Button            5       /* control type: command, callback function: OnChangeSecondWIN */
#define  WIN_Panel_Stop_Numeric           6       /* control type: numeric, callback function: (none) */
#define  WIN_Panel_NUMERIC_PUNCTE         7       /* control type: numeric, callback function: (none) */
#define  WIN_Panel_Start_Numeric          8       /* control type: numeric, callback function: (none) */
#define  WIN_Panel_GRAPH_SPECTRU_NEW      9       /* control type: graph, callback function: (none) */
#define  WIN_Panel_Next_Button            10      /* control type: command, callback function: OnChangeSecondWIN */
#define  WIN_Panel_FILTER_SWITCH          11      /* control type: binary, callback function: (none) */
#define  WIN_Panel_WINDOW_SWITCH          12      /* control type: binary, callback function: (none) */
#define  WIN_Panel_FFREQ                  13      /* control type: numeric, callback function: (none) */
#define  WIN_Panel_ATTEN                  14      /* control type: numeric, callback function: (none) */
#define  WIN_Panel_ORDER                  15      /* control type: numeric, callback function: (none) */
#define  WIN_Panel_FC                     16      /* control type: numeric, callback function: (none) */
#define  WIN_Panel_R                      17      /* control type: numeric, callback function: (none) */
#define  WIN_Panel_FS                     18      /* control type: numeric, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK OnApply(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnChangeSecond(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnChangeSecondWIN(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnFrequencyPanel(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnLoadButtonCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnLoadButtonCB2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnMainPanel(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnSwitchPanelCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnWinPanel(int panel, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif