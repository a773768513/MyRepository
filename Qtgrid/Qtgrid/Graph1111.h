#pragma once
#include <QString>
#include <QColor>
#include <QPoint>
#include <QLabel>


class Graph
{
public:
	Graph(QPaintDevice *parent);
	~Graph();

	QPaintDevice *Parent;

	int mark_, size_, rot_;
	int X, Y, Width, Height;
	double XCent, YCent, XScale, YScale, XTick, YTick;
public:
	void DrawGrid();
	void DrawAxis();
	void DrawLabel();
	void DrawBox();
};

