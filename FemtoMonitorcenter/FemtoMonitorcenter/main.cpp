#include "CFemtoMonitorcenter.h"
#include <QtWidgets/QApplication>
#include <qfileinfo.h>
#include <qsettings.h>

static void associateFileTypes()
{
	/**
	QString displayName = QGuiApplication::applicationDisplayName();
	QString filePath = QCoreApplication::applicationFilePath();
	QString fileName = QFileInfo(filePath).fileName();

	QSettings settings("HKEY_CURRENT_USER\\Software\\Classes\\Applications\\" + fileName, QSettings::NativeFormat);
	settings.setValue("FriendlyAppName", displayName);

	settings.beginGroup("SupportedTypes");
	foreach(const QString& fileType, fileTypes)
		settings.setValue(fileType, QString());
	settings.endGroup();

	settings.beginGroup("shell");
	settings.beginGroup("open");
	settings.setValue("FriendlyAppName", displayName);
	settings.beginGroup("Command");
	settings.setValue(".", QChar('"') + QDir::toNativeSeparators(filePath) + QString("\" \"%1\""));
	**********/
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	CFemtoMonitorcenter w;
	w.show();
	return a.exec();
}
