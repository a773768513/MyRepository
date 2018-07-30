#ifndef QTGUIDER_H
#define QTGUIDER_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/qtextedit.h>
#include <QtWidgets/QStatusBar>

#include <QtWidgets/QTextEdit>
#include <QtWidgets\QComboBox>
#include <QtWidgets\QRadioButton>
#include <QtWidgets\QGroupBox>
#include <QtWidgets\QVBoxLayout>
#include <QtWidgets\QCheckBox>
#include <QtWidgets\QPushButton>
#include <qgridlayout.h>
#include <qdatetimeedit.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qtablewidget.h>
#include <qthread.h>

#ifndef __QSETTINGS_ARRAY_LENGTH__
#define __QSETTINGS_ARRAY_LENGTH__
#define QSETTINGS_ARRAY_LENGTH 7
#endif
class QtGuiderImpl;

class FlexWidget;
class DockWidget;
class CThreadQtextbrowser;
class CManageThreadObject;
class QtCentral;
class QtGuider : public QMainWindow
{
    Q_OBJECT
public:
    QtGuider(QWidget *parent = 0, Qt::WindowFlags flags = 0);
    ~QtGuider();

protected:
    void closeEvent(QCloseEvent* evt);

public:
    void openFile_N(int n);
    void openView_N(int n);
private:
	void FunctionConnectMainWindowsRequirementSlot();
	void AddMainMenuAction();
	///
	void CreateOpenFileChildWindows();
	void CreateHighlightingWindows();
	void CreateWriteFileWindow();

private slots:
    void on_actionEdit_Undo_triggered();
    void on_actionEdit_Redo_triggered();
    void on_actionFile_N_triggered();
   /// void on_actionView_N_triggered();
    void on_actionTool_N_triggered();

	public slots:
	bool eventFilter(QObject *, QEvent *);    //注意这里
signals:
	///tips for user
	void EmitQmessageInformation(QString QSInformation);
	///Open Serious Port in GUI request
	void emitOpenSeriousPortGUI(QString EmitOpenFilePath);
	///eimt close qwidgets request
	void emitCloseCurrentQtextbrowserGUI(int indexGUI);
	///emit the log data FILE pointer

	void emitLogDataFile(QString LogDataindex, char* fpLogDataFile);
	///stop Log

	void  emitStopLogGUI(int IndexStopLog);
private slots:
    void actionView_X_triggered();
    void actionFile_X_triggered();

	///
	/// main windows slot  action 
	void On_pQActionOpenFileDialog_triggered();
	void On_pQActionOpenHighlighterDialog_triggered();
	void On_pQActionOpenLogFileDialog_triggered();
	///
	///child window slots 
	void On_OpenFileChildDialogSelectFile_Clicked();
	void On_pQPushButttonOpenFileConfirm_Clicked();
	void On_pQPushButtonOpenFileCancel_Clicked();
	///
	///highlighter dialog slots 
	void On_pQHighlighterDialogConfirm_Triggered();
	void On_pQHighlighterDialogCancel_Triggered();
	void On_pQOpenColorDialog_Triggered();
	///LOG windows slots
	void On_pQWriteDialogFileButton_clicked();
	void On_pQWriteDialogConfirmButton_clicked();
	void On_pQWriteDialogCancelButton_clicked();
	void On_pQWriteDialogFileAddCheckBox_StateChange(int stats);
	void On_pQWriteDialogFileSuffixCheckBox_StateChange(int stats);

	///SLOT to qmessage to show user information 
	void QMessageBoxFailure(QString QSInformation);

	///
	///managethread slots
	void On_CreateGUIQTextbrowserManagethread_Triggered(QString Tabtitle);
	///append data to FUI (from managethread)
	void On_AppendDataManagethread_Triggered(int NumberWindowManage, char* pAppendDataPointerManage);
	///refresh the data speed in manage windows 
	void On_EmitRefreshReceivingRateManage_Triggered();
	///
	void On_emitCloseQtextbrowserRecordManage_triggered(int index);
	///user requset stop log
	void On_emitStopLogTextbrowser_Request();

	///delete triggerred
	void on_flexWidgetDestroying(FlexWidget*);
	void on_dockWidgetDestroying(DockWidget*);
	///
	void On_Textbrowser_emitFocuseInTextbrowser(QString focusWidgetsTitle);
private:
    friend class QtGuiderImpl;
private:

	///manage thread and object create
	CManageThreadObject  *pCManageThreadObject;
	QThread *pManagethread;

	QTableWidget* pQTableWidgetManageWidgets;
	void StartManageThread();
    QScopedPointer<QtGuiderImpl> impl;
	QVector<FlexWidget*> QvectorFlexWidgets;
	QVector<CThreadQtextbrowser*> QVectorThreadTextbrowser;
	///main qtablewidget
	QtCentral* pQtCentral;
	///windows GUI pointer 
	QComboBox *pShowFocusEvent;
	QTextEdit* pQTextEditCommandWindows;
	QWidget* pQWidgetCommandWindows;
	QGridLayout* pQGridLayoutCommandWindows;
	///
	///main windows action 
	QAction *pQActionOpenFileDialog;
	QAction *pQActionOpenHighlighterDialog;
	QAction *pQActionOpenLogFileDialog;
	QStatusBar *pQStatusBarMainWindows;
	QMenu *pQMenuMainwindows;
	///
	///OpenFileDialog Widget 
	QPushButton *pQPushButtonOpenFileCancel;
	QPushButton *pQPushButttonOpenFileConfirm;
	QPushButton *pQPushButtonOpenFilePath;
	QComboBox *pQTextEditOpenFilePath;
	QLabel *pQLabelOpenFilePath;
	QDialog *pDialogOpenFile;
	QGridLayout *pGridLayoutOpenFileDialog;

	///
	///Highlighting childDialog widgets
	QDialog* pQDialogHighlighter;
	QGridLayout* pQgridLayoutHighlighterDialog;
	QComboBox* pQComboBoxHighlighterDialogStr;
	QLabel* pQLabelSampleStr;
	QPushButton* pQOpenColorDialog;
	QPushButton* pQHighlighterDialogConfirm;
	QPushButton* pQHighlighterDialogCancel;
	QColor  *pQColorSelected;                           ///<record the Color selected
	///
	///Create WriteFileDialog widgets
	QDialog *pWriteDialog;
	QGridLayout *pWriteGridLayout;
	QComboBox *pQWriteDialogFileDirectory;

	QLineEdit *pQWriteDialogEdit;
	QCheckBox *pQWriteDialogFileAddCheckBox;
	QLineEdit *pQWriteDialogFileAdd;
	QCheckBox *pQWriteDialogFileSuffixCheckBox;
	QLineEdit *pQWriteDialogFileSuffix;
	QPushButton *pQWriteDialogFileButton;
	QPushButton *pQWriteDialogConfirmButton;
	QPushButton *pQWriteDialogCancelButton;
	///Automatic Log Dialog
	QGroupBox* pQGroupBoxAutomaticLog;
	QGridLayout* pQGridlayoutAutomaticLog;
	QGroupBox* pQGroupBoxLogTime;
	QVBoxLayout* pQVBoxLayoutRadioButton;
	QRadioButton* pQRadioButtonOnce;
	QRadioButton* pQRadioButtonDay;
	QRadioButton* pQRadioButtonWeekly;
	QGroupBox* pQGroupBoxDataTime;
	QVBoxLayout* pQVBoxLayoutDataTime;
	QDateTimeEdit* pQDateTimeEditStart;
	QDateTimeEdit* pQDateTimeEditEnd;
	///function to create the 
	QGroupBox* CreatepCombinationWindows();

	///function 


};

class QtCentral : public QWidget
{
    Q_OBJECT
public:
    QtCentral(QWidget* parent);
    void createOne();
    void createTwo();
    FlexWidget* content;

private slots:

void on_flexWidgetCreated(FlexWidget*);
void on_dockWidgetCreated(DockWidget*);


private:
	///main windows pointer 
	///command windows 


private:
    QWidget* _widget;
};

#endif // QTGUIDER_H
