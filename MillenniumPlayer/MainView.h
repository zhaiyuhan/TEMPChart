#pragma once

#include <QtWidgets/QMainWindow>
#include <QPropertyAnimation>

#include <QSerialPort>
#include <QSerialPortInfo>
#include "3rdparty/QMW/Includes/qtmaterialiconbutton.h"
#include "3rdparty/QMW/Includes/qtmaterialslider.h"
#include "3rdparty/QMW/Includes/qtmaterialflatbutton.h"
#include "3rdparty/QMW/Includes/qtmaterialraisedbutton.h"
#include "3rdparty/QMW/Includes/qtmaterialcheckbox.h"
#include "Foundation/View/BaseView.h"
#include "Foundation/Control/ActionButton.h"
#include "Foundation/Control/StackedWidget.h"
#include "Foundation/Control/Chart.h"


class MainView : public BaseView
{
	Q_OBJECT

public:
	MainView(QWidget *parent = Q_NULLPTR);
	void init_SerialPort();
	
protected:
	void dragMoveEvent(QDragMoveEvent* event)
	{
		qDebug() << "drag move";
	}
	void dragEnterEvent(QDragEnterEvent* event);
	void dropEvent(QDropEvent* event);
	bool eventFilter(QObject* watched, QEvent* event)
	{
		if (watched == this) {
			if (event->type() == QEvent::MouseButtonDblClick)
			{
				if (Qt::WindowFullScreen == windowState())
					this->showNormal();
				if (Qt::WindowFullScreen != windowState())
					this->isMaximized() ? this->showNormal() : this->showMaximized();
			}
		}
		return QWidget::eventFilter(watched, event);
	}
	void setupUI();
	void initLayout()
	{
	
		
	}
	void initEvents();
	void initView();
	void resizeEvent(QResizeEvent *event);
	void contextMenuEvent(QContextMenuEvent *);
private:
	void openSerialPort();
	void closeSerialPort();
	void readData();
	QSerialPort *global_serialport;
	bool m_isOpenPort;
	
private:
	QLabel* m_label, *m_label2, *m_label3, *m_label4, *m_label5;
	QLabel* informationLabel;
	QComboBox* chooseportComboBox, * choosebaudrateComboBox, * choosedatabitsComboBox, * chooseparityComboBox,
		* choosestopbitsComboBox;
	QtMaterialFlatButton* sendButton;
	QtMaterialRaisedButton* openportButton;
	QtMaterialIconButton* downloadButton, * extraviewButton;
	QtMaterialCheckBox* sendbyhexCheckBox;
	QWidget* mainWidget,* titleWidget; 
	QTextEdit* inputTextEdit,*receiveTextEdit;
	Chart* mainChart;
	QMenu *menu;
	StackedWidget* mainStackedWidget;
};
