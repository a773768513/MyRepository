#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Qtgrid.h"

#include "graph.h"

#define MAXNFILE    256                 // max number of solution files
#define MAXSTRBUFF  1024                // max length of stream buffer
#define MAXWAYPNT   99                  // max number of waypoints
#define MAXMAPPATH  4096                // max number of map paths
#define MAXMAPLAYER 12                  // max number of map layers

#define PRGNAME     "RTKPLOT-QT"           // program name

const QChar degreeChar(0260);           // character code of degree (UTF-8)
const QChar up2Char(0262);              // character code of ^2     (UTF-8)

#define DEFTSPAN    600.0               // default time span (s)
#define INTARROW    60.0                // direction arrow interval (s)
#define MAXTDIFF    60.0                // max differential time (s)
#define DOPLIM      30.0                // dop view limit
#define TTOL        DTTOL               // time-differnce tolerance (s)
#define TBRK        300.0               // time to recognize break (s)
#define THRESLIP    0.1                 // slip threshold of LG-jump (m)
#define SIZE_COMP   45                  // compass size (pixels)
#define SIZE_VELC   45                  // velocity circle size (pixels)
#define MIN_RANGE_GE 10.0               // min range for GE view

#define PLOT_TRK    0                   // plot-type: track-plot
#define PLOT_SOLP   1                   // plot-type: position-plot
#define PLOT_SOLV   2                   // plot-type: velocity-plot
#define PLOT_SOLA   3                   // plot-type: accel-plot
#define PLOT_NSAT   4                   // plot-type: number-of-satellite-plot
#define PLOT_RES    5                   // plot-type: residual-plot
#define PLOT_OBS    6                   // plot-type: observation-data-plot
#define PLOT_SKY    7                   // plot-type: sky-plot
#define PLOT_DOP    8                   // plot-type: dop-plot
#define PLOT_SNR    9                   // plot-type: snr/mp-plot
#define PLOT_SNRE   10                  // plot-type: snr/mp-el-plot
#define PLOT_MPS    11                  // plot-type: mp-skyplot

#define ORG_STARTPOS 0                  // plot-origin: start position
#define ORG_ENDPOS  1                   // plot-origin: end position
#define ORG_AVEPOS  2                   // plot-origin: average position
#define ORG_FITPOS  3                   // plot-origin: linear-fit position
#define ORG_REFPOS  4                   // plot-origin: reference position
#define ORG_LLHPOS  5                   // plot-origin: lat/lon/hgt position
#define ORG_AUTOPOS 6                   // plot-origin: auto-input position
#define ORG_IMGPOS  7                   // plot-origin: image-center position
#define ORG_MAPPOS  8                   // plot-origin: map center position
#define ORG_PNTPOS  9                   // plot-origin: way-point position

#define TRACEFILE   "rtkplot.trace"     // trace file
#define QCTMPFILE   "rtkplot_qc.temp"   // tempolary file for qc
#define QCERRFILE   "rtkplot_qc.err"    // error file for qc

#define SQR(x)      ((x)*(x))
#define SQRT(x)     ((x)<0.0||(x)!=(x)?0.0:sqrt(x))
#define MAX(x,y)    ((x)>(y)?(x):(y))
#define MIN(x,y)    ((x)<(y)?(x):(y))


class Qtgrid : public QMainWindow
{
	Q_OBJECT

public:
	Qtgrid(QWidget *parent = Q_NULLPTR);
	~Qtgrid();
	Graph * graphT;
	Ui::QtgridClass ui;

protected:
	void wheelEvent(QWheelEvent *event);
	void paintEvent(QPaintEvent *);
	void  resizeEvent(QResizeEvent *);
private:

	int Drag, Xn, Yn;
	double X0, Y0, Xc, Yc, Xs, Ys, Xcent, Xcent0;

	int FormWidth, FormHeight;     ///Save current window size information
	QPixmap Buff;         ///Canvas cache;
	QColor CColor[4];    /// {background,grid,text,line}

	void DrawTrk(QPainter &c, int level);

	void UpdateSize();
	void Refresh();
	void updategraph();
	void DrawMark(Graph *g, QPainter &c, const QPoint &p, int mark, const QColor &color,
		int size, int rot);
	void DrawLabel(Graph *g, QPainter &c, const QPoint &p, const QString &label, int ha, int va);
	public slots:

};
