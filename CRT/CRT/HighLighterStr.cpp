#include "HighLighterStr.h"


CHighLighterStr::CHighLighterStr(QTextDocument *parent)
: QSyntaxHighlighter(parent)
{
	SHighLightingRule NewRule;

	QKeyStrFormat.setForeground(Qt::red);
	QString QkeyStrList;
	QkeyStrList = "^love";
	NewRule.Qpattern = QRegExp(QkeyStrList);
	NewRule.QFormat = QKeyStrFormat;
	QVSHighLightingRule.append(NewRule);
}


void CHighLighterStr::addnewRegExp(QString QSMatchStr)
{
	SHighLightingRule NewRule;

	QKeyStrFormat.setForeground(Qt::blue);
	QString QkeyStrList("^" + QSMatchStr);
	NewRule.Qpattern = QRegExp(QkeyStrList);
	NewRule.QFormat = QKeyStrFormat;
	QVSHighLightingRule.append(NewRule);
}
CHighLighterStr::~CHighLighterStr()
{
}


void CHighLighterStr::highlightBlock(const  QString &text)
{
	for each (const SHighLightingRule  &pQSrule in QVSHighLightingRule)
	{
		QRegExp  QRExpression(pQSrule.Qpattern);
		int index = QRExpression.indexIn(text);
		while (index >= 0)
		{
			int StrLength = QRExpression.matchedLength();
			setFormat(index, StrLength, pQSrule.QFormat);
			index = QRExpression.indexIn(text, index + StrLength);
		}
	}
}