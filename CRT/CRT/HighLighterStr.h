#pragma once
#include <qsyntaxhighlighter.h>
#include <qtextformat.h>
class CHighLighterStr :
	public QSyntaxHighlighter
{
public:
	CHighLighterStr(QTextDocument *parent = 0);
	~CHighLighterStr();
	void addnewRegExp(QString QSMatchStr);
protected:
	virtual void  highlightBlock(const  QString &text);

private:
	struct SHighLightingRule
	{
		QRegExp Qpattern;
		QTextCharFormat QFormat;
	};
	QVector<SHighLightingRule>  QVSHighLightingRule;
	QTextCharFormat  QKeyStrFormat;

};

