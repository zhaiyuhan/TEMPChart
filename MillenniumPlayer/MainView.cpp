#include "stdafx.h"
#include "MainView.h"
#include <QPalette>

QString devicdescription;
MainView::MainView(QWidget* parent)
	: BaseView(parent)
{
	setMinimumSize(1024, 768);
	EnableBackgroundColor(QColor(0xff, 0xff, 0xff, 90));//
	EnableAnimation(true);
	EnableGaussianBlur(true);
	EnableWindowShadow(true);
	QFile qss(":/MainView/Resources/mainTheme.qss");
	if (qss.open(QFile::ReadOnly))
	{
		QString style = QLatin1String(qss.readAll());
		this->setStyleSheet(style);
		qss.close();
	}

	initView();
	setWindowIcon(QIcon(":/logo.ico"));
	setAcceptDrops(true);
	this->installEventFilter(this);

	init_SerialPort();
	
}

void MainView::init_SerialPort()
{
	foreach(const QSerialPortInfo & info, QSerialPortInfo::availablePorts())
	{

		QSerialPort serial;
		serial.setPort(info);
		if (serial.open(QIODevice::ReadWrite))
		{
			chooseportComboBox->addItem(info.portName());
			devicdescription = info.description();
			serial.close();
		}
	}


}

void MainView::dragEnterEvent(QDragEnterEvent* event)
{
}

void MainView::dropEvent(QDropEvent* event)
{

}



void MainView::initView()
{
	setupUI();

	initLayout();
	initEvents();
}

void MainView::setupUI()
{
	downloadButton = new QtMaterialIconButton(QIcon(":/Icons/download.svg"), this);

	downloadButton->setFixedSize(32, 32);



	m_label = new QLabel(this);
	m_label->setStyleSheet("color:rgba(0,0,0,90%);");
	m_label->setFont(QFont("Microsoft YaHei", 14, 50));
	m_label->setText(QStringLiteral("串口号"));

	chooseportComboBox = new QComboBox(this);
	chooseportComboBox->setFixedSize(100, 28);

	chooseportComboBox->setView(new  QListView());
	//
	m_label2 = new QLabel(this);
	m_label2->setStyleSheet("color:rgba(0,0,0,90%);");
	m_label2->setFont(QFont("Microsoft YaHei", 14, 50));
	m_label2->setText(QStringLiteral("波特率"));

	choosebaudrateComboBox = new QComboBox(this);
	choosebaudrateComboBox->setFixedSize(100, 28);
	QStringList strList2;
	strList2 << "1200" << "2400" << "4800" << "9600" << "14400" << "19200";
	choosebaudrateComboBox->addItems(strList2);
	choosebaudrateComboBox->setCurrentIndex(3);
	choosebaudrateComboBox->setView(new  QListView());
	//

	m_label3 = new QLabel(this);
	m_label3->setStyleSheet("color:rgba(0,0,0,90%);");
	m_label3->setFont(QFont("Microsoft YaHei", 14, 50));
	m_label3->setText(QStringLiteral("数据位"));

	choosedatabitsComboBox = new QComboBox(this);
	choosedatabitsComboBox->setFixedSize(100, 28);
	QStringList strList3;
	strList3 << "8" << "7" << "6" << "5";
	choosedatabitsComboBox->addItems(strList3);
	choosedatabitsComboBox->setView(new  QListView());

	m_label4 = new QLabel(this);
	m_label4->setStyleSheet("color:rgba(0,0,0,90%);");
	m_label4->setFont(QFont("Microsoft YaHei", 14, 50));
	m_label4->setText(QStringLiteral("校验位"));

	chooseparityComboBox = new QComboBox(this);
	chooseparityComboBox->setFixedSize(100, 28);
	QStringList strList4;
	strList4 << "None" << "Even" << "Odd" << "Space" << "Mark";
	chooseparityComboBox->addItems(strList4);
	chooseparityComboBox->setView(new  QListView());


	m_label5 = new QLabel(this);
	m_label5->setStyleSheet("color:rgba(0,0,0,90%);");
	m_label5->setFont(QFont("Microsoft YaHei", 14, 50));
	m_label5->setText(QStringLiteral("停止位"));
	choosestopbitsComboBox = new QComboBox(this);
	choosestopbitsComboBox->setFixedSize(100, 28);
	QStringList strList5;
	strList5 << "1" << "1.5" << "2";
	choosestopbitsComboBox->addItems(strList5);
	choosestopbitsComboBox->setView(new  QListView());

	openportButton = new QtMaterialRaisedButton(QStringLiteral("打开串口"), this);
	openportButton->setCornerRadius(6.0);
	openportButton->setFixedSize(200, 35);
	openportButton->setUseThemeColors(false);
	openportButton->setBackgroundColor(QColor(48, 110, 237));
	openportButton->setForegroundColor(QColor(255, 255, 255));
	openportButton->setCheckable(true);



	mainWidget = new QWidget(this);
	mainWidget->setAttribute(Qt::WA_StyledBackground, true);
	mainWidget->setStyleSheet("background-color: rgb(255, 255, 255)");

	titleWidget = new QWidget(this);
	titleWidget->setAttribute(Qt::WA_StyledBackground, true);
	titleWidget->setStyleSheet("background-color: rgb(234,234,232);border-radius: 8px;");


	informationLabel = new QLabel(titleWidget);
	informationLabel->setText(QStringLiteral("成功启动程序 <b>Succeeded</b> | Today at ").append(QDateTime::currentDateTime().toString("hh:mm:ss")));
	informationLabel->setStyleSheet("color:rgba(0,0,0,90%);");
	informationLabel->setFont(QFont("Microsoft YaHei", 10));
	informationLabel->setGeometry(5, 10, 2000, 25);




	inputTextEdit = new QTextEdit(this);
	receiveTextEdit = new QTextEdit(this);
	receiveTextEdit->setStyleSheet("border-radius:10px");
	sendButton = new QtMaterialFlatButton(this);
	sendButton->setFixedSize(100, 40);
	sendButton->setText(QStringLiteral("发送"));

	extraviewButton = new QtMaterialIconButton(QIcon(":/Icons/rightview.svg"), this);
	extraviewButton->setIconSize(QSize(32, 32));
	//extraviewButton->setFixedSize(32, 32);

	sendbyhexCheckBox = new QtMaterialCheckBox(this);
	sendbyhexCheckBox->setChecked(false);
	sendbyhexCheckBox->setUseThemeColors(false);
	sendbyhexCheckBox->setCheckedColor(QColor(48, 110, 237));
	sendbyhexCheckBox->setText(QStringLiteral("以十六进制发送"));
	mainChart = new Chart(this);
	mainChart->setStyleSheet("border-radius:10px");
	mainStackedWidget = new StackedWidget(this);
	mainStackedWidget->insertWidget(0, receiveTextEdit);
	mainStackedWidget->insertWidget(1, mainChart);
	mainStackedWidget->setSpeed(1000);
	mainStackedWidget->setDirectonMode(DirectionMode::Wrap);

	CustomShadowEffect* bodyShadow = new CustomShadowEffect();
	bodyShadow->setBlurRadius(15.0);
	bodyShadow->setDistance(4.0);
	bodyShadow->setColor(QColor(21, 25, 30, 60));
	mainStackedWidget->setGraphicsEffect(bodyShadow);
}

void MainView::initEvents()
{
	connect(openportButton, &QPushButton::clicked, this,
		[=]() {
			if(!chooseportComboBox->currentText().isEmpty())
			switch (openportButton->isChecked())
			{
			case true:
				openportButton->setText(QStringLiteral("关闭串口"));
				m_isOpenPort = true;
				openSerialPort();
				break;
			case false:
				openportButton->setText(QStringLiteral("打开串口"));
				m_isOpenPort = false;
				closeSerialPort();
				break;
			}
		});
	connect(sendButton, &QPushButton::clicked, this,
		[=]() {
			if (global_serialport->isOpen() == false)
			{
				informationLabel->setText(QStringLiteral("当前没有可使用的串口"));
				return;
			}
			else {
				QByteArray sendData;
				if (!sendbyhexCheckBox->isChecked())
				{
					sendData = inputTextEdit->toPlainText().toUtf8();
					if (!sendData.isEmpty() && !sendData.isNull()) {
						global_serialport->write(sendData);
					}
				}
				else {
					QString dataStr = inputTextEdit->toPlainText();
					if (dataStr.length() % 2) {
						dataStr.insert(dataStr.length() - 1, '0');
					}
					QByteArray sendData = dataStr.toLatin1().toHex();
					global_serialport->write(sendData);
				}
				sendData.clear();
			}
		});
	connect(extraviewButton, &QPushButton::clicked, this, [=]()
		{
			switch (mainStackedWidget->currentIndex())
			{
			case 0:
				mainStackedWidget->slideInNext();
				break;
			case 1:
				mainStackedWidget->slideInPrev();
				break;
			}

		});


}

void MainView::readData()
{
	
	QByteArray buf= global_serialport->readAll();
	
	if (!buf.isEmpty())
	{
		QString receiveData = QString::fromLocal8Bit(buf);
		mainChart->setData(buf.toDouble());
		receiveTextEdit->insertPlainText(receiveData);
	}

	buf.clear();

}
void MainView::resizeEvent(QResizeEvent* event)
{

	downloadButton->move(200, 12);
	m_label->move(25, 100);
	chooseportComboBox->move(130, 100);
	m_label2->move(25, 160);
	choosebaudrateComboBox->move(130, 160);
	m_label3->move(25, 220);
	choosedatabitsComboBox->move(130, 220);
	m_label4->move(25, 280);
	chooseparityComboBox->move(130, 280);
	m_label5->move(25, 340);
	choosestopbitsComboBox->move(130, 340);

	openportButton->move(25, 460);

	mainWidget->resize((event->size().width() - 250),
		event->size().height()
	);

	mainWidget->move(
		(event->size().width() - mainWidget->width()),
		0
	);

	titleWidget->resize((event->size().width() - 500),
		40
	);
	titleWidget->move(
		event->size().width() - mainWidget->width() +
		(mainWidget->width() - titleWidget->width()) / 2,
		10
	);



	inputTextEdit->resize(mainWidget->width() - 20, 120);
	inputTextEdit->move(event->size().width() - mainWidget->width() +
		(mainWidget->width() - inputTextEdit->width()) / 2,
		event->size().height() - inputTextEdit->height() - 40);
	mainStackedWidget->resize(mainWidget->width() - 20,
		mainWidget->height() - inputTextEdit->height() - 180);
	mainStackedWidget->move(event->size().width() - mainWidget->width() +
		(mainWidget->width() - mainStackedWidget->width()) / 2,
		100);
	sendbyhexCheckBox->move(event->size().width() - mainWidget->width() +
		(mainWidget->width() - mainStackedWidget->width()) / 2,
		event->size().height() - 80 - inputTextEdit->height());
	sendButton->move(event->size().width() - 110, event->size().height() - 40);

	extraviewButton->move(event->size().width() - 50, 12);
	//extraviewButton->raise();
	BaseView::resizeEvent();
}

void MainView::contextMenuEvent(QContextMenuEvent*)
{
	QCursor cur = this->cursor();
	menu = new Menu(this);

	QAction* HiddenAction = new QAction(tr("Hidden"), this);
	
	QAction* deleteAction = new QAction(tr("Exit"), this);
	deleteAction->setObjectName("done");

	menu->addAction(HiddenAction);

	
	menu->addSeparator();
	menu->addAction(deleteAction);
	connect(deleteAction, &QAction::triggered, this,
		[=]() { qApp->exit(); });
	menu->exec(cur.pos());
}

void MainView::openSerialPort()
{   
	global_serialport = new QSerialPort(this);
	global_serialport->setPortName(chooseportComboBox->currentText());
	// 打开串口
	if (global_serialport->open(QIODevice::ReadWrite))
	{
		// 设置波特率
		global_serialport->setBaudRate(choosebaudrateComboBox->currentText().toInt());
		//设置数据位数
		switch (choosedatabitsComboBox->currentIndex())
		{
		case 0: global_serialport->setDataBits(QSerialPort::Data8); break;
		case 1: global_serialport->setDataBits(QSerialPort::Data7); break;
		case 2: global_serialport->setDataBits(QSerialPort::Data6); break;
		case 3: global_serialport->setDataBits(QSerialPort::Data5); break;
		default: break;
		}
		// 设置校验位
		switch (chooseparityComboBox->currentIndex())
		{
		case 0: global_serialport->setParity(QSerialPort::NoParity); break;
		case 1: global_serialport->setParity(QSerialPort::OddParity); break;
		case 2: global_serialport->setParity(QSerialPort::EvenParity); break;
		case 3: global_serialport->setParity(QSerialPort::SpaceParity); break;
		case 4: global_serialport->setParity(QSerialPort::MarkParity); break;
		default: break;
		}
		// 设置流控制
		global_serialport->setFlowControl(QSerialPort::NoFlowControl);
		//设置停止位
		switch (choosestopbitsComboBox->currentIndex())
		{
		case 0: global_serialport->setStopBits(QSerialPort::OneStop); break;
		case 1: global_serialport->setStopBits(QSerialPort::OneAndHalfStop); break;
		case 2: global_serialport->setStopBits(QSerialPort::TwoStop); break;
		default: break;
		}
		informationLabel->setText(QString("").append(devicdescription).append(QStringLiteral(" 成功打开 <b>Succeeded</b> | Today at ")).append(QDateTime::currentDateTime().toString("hh:mm:ss")));
		QObject::connect(global_serialport, &QSerialPort::readyRead, this, &MainView::readData);
		//由于此时才有了global_serialport，所以只有在这里装载事件
	}
	//打开串口
	else
	{
 		informationLabel->setText(QStringLiteral("串口无法打开\r\n不存在或已被占用 Failed | "));
		return;
	}
}

void MainView::closeSerialPort()
{
	informationLabel->setText(QStringLiteral("串口已经关闭 <b>Succeeded</b> | Today at ").append(QDateTime::currentDateTime().toString("hh:mm:ss")));
	global_serialport->close();
}