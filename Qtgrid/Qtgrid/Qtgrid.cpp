#include "Qtgrid.h"
#include <QColor>
#include <QPainter>
#include "graph.h"
#include <QShowEvent>
#include <QCloseEvent>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QFocusEvent>
#include <QKeyEvent>
#include <QWheelEvent>
#include <QPaintEvent>
#include <QDebug>
#include <QToolBar>
#include <QScreen>
#include <QtGlobal>
#include <QFileInfo>

#include <QFileInfo>
#include <QCommandLineParser>
#include <QFileDialog>
#include <QClipboard>
#include <QSettings>
#include <QFont>
#include <QMimeData>

Qtgrid::Qtgrid(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	
	CColor[0] =  (Qt::white);
	CColor[1] = QColor(0xc0, 0xc0, 0xc0);
	CColor[2] =  Qt::black;
	CColor[3] = QColor(0xc0, 0xc0, 0xc0);



	ui.label->setAttribute(Qt::WA_TransparentForMouseEvents);
	ui.label->setAttribute(Qt::WA_OpaquePaintEvent);
	setMouseTracking(true);
	

	graphT = new Graph(ui.label);
	graphT->Fit = 0;
	
}

Qtgrid::~Qtgrid()
{
	delete graphT;

}
void Qtgrid::updategraph()
{
	
	Buff = QPixmap(ui.label->size());
	if (Buff.isNull()) return;
	Buff.fill(CColor[0]);

	QPainter c(&Buff);

	c.setFont(ui.label->font());
	c.setPen(CColor[0]);
	c.setBrush(CColor[0]);
	DrawTrk(c, 1);


	ui.label->setPixmap(Buff);

	ui.label->update();
}
void Qtgrid::DrawMark(Graph *g, QPainter &c, const QPoint &p, int mark, const QColor &color,
	int size, int rot)
{
	g->DrawMark(c, p, mark, color, CColor[0], size, rot);
}
// draw label with hemming --------------------------------------------------
void Qtgrid::DrawLabel(Graph *g, QPainter &c, const QPoint &p, const QString &label, int ha, int va)
{
	
	g->DrawText(c, p, label, CColor[2], CColor[0], ha, va, 0);
}
void Qtgrid::DrawTrk(QPainter &c, int level)
{
	
	QString label, header;

	QPoint p1, p2;
	double xt, yt, sx, sy, opos[3], pnt[3], rr[3], enu[3], cent[3];

	graphT->GetPos(p1, p2);
	p1.rx() = (p1.x() + p2.x()) / 2;
	p1.ry() = (p1.y() + p2.y()) / 2;
	DrawMark(graphT, c, p1, 5, CColor[1], 20, 0);
	
	graphT->XLPos = 2; graphT->YLPos = 4;
	graphT->DrawAxis(c, 1, 1 == 2);
	
	///label
	graphT->GetPos(p1, p2);
	graphT->GetTick(xt, yt);
	graphT->GetScale(sx, sy);
	p2.rx() -= 70;
	p2.ry() -= 25;
	DrawMark(graphT, c, p2, 11, CColor[2], static_cast<int>(xt / sx + 0.5), 0);
	p2.ry() -= 3;
	if (xt<0.01) label = QString("%1 mm").arg(xt*1000.0, 0, 'f', 0);
	else if (xt<1.0) label = QString("%1 cm").arg(xt*100.0, 0, 'f', 0);
	else if (xt<1000.0) label = QString("%1 m").arg(xt, 0, 'f', 0);
	else                label = QString("%1 km").arg(xt / 1000.0, 0, 'f', 0);
	DrawLabel(graphT, c, p2, label, 0, 1);
	
	
}

void Qtgrid::paintEvent(QPaintEvent *)
{
	updategraph();
}
void Qtgrid::wheelEvent(QWheelEvent *event)
{

	QPoint p(Xn, Yn);
	double xs, ys, ds = pow(2.0, -event->angleDelta().y() / 1200.0);
	event->accept();
	if (Xn<0 || Yn<0) return;

	if (graphT == nullptr) { // track-plot
		return;
	}
	
		graphT->GetScale(xs, ys);
		graphT->SetScale(xs*ds, ys*ds);



		Refresh();
}

void Qtgrid::resizeEvent(QResizeEvent *)
{
	

	// suppress repeated resize callback
	if (FormWidth == width() && FormHeight == height()) return;

	UpdateSize();
	Refresh();

	FormWidth = width();
	FormHeight = height();
}
void Qtgrid::UpdateSize()
{

	graphT->resize();
}

void Qtgrid::Refresh()
{
	updategraph();
}
