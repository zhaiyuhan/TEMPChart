#include "stdafx.h"
#include "Chart.h"


Chart::Chart(QWidget *parent)
	: QWidget(parent)
{
    
    QPen penY(QColor(48, 110, 237), 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    

    splineSeries = new QSplineSeries();
    scatterSeries = new QScatterSeries();
    scatterSeries->setMarkerSize(8);

    chart = new QChart();
    
    axisX = new QDateTimeAxis();
    axisY = new QValueAxis();
    chart->addSeries(splineSeries);
    chart->addSeries(scatterSeries);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->legend()->hide();
    chart->setTitle(QStringLiteral("��Ƭ���¶ȴ���������"));
    axisX->setTickCount(10);                             //�������������
    axisY->setTickCount(6);
    axisX->setFormat("ss");                        //����ʱ����ʾ��ʽ
    axisY->setMin(0);                                    //����Y�᷶Χ
    axisY->setMax(50);
    axisX->setTitleText(QStringLiteral("ʵʱʱ��"));                       //����X������
    axisY->setLinePenColor(QColor(Qt::darkBlue));        //������������ɫ��ʽ
    axisY->setGridLineColor(QColor(Qt::darkBlue));
    axisY->setGridLineVisible(false);                    //����Y��������ʾ
    axisY->setLinePen(penY);
    axisX->setLinePen(penY);

    chart->addAxis(axisX, Qt::AlignBottom);               //����������λ��chart�е�λ��
    chart->addAxis(axisY, Qt::AlignLeft);

    splineSeries->attachAxis(axisX);                           //��������ӵ���������
    splineSeries->attachAxis(axisY);
    splineSeries->setUseOpenGL(true);
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setStyleSheet("background-color: #333333");
    chart->setBackgroundRoundness(10);
    QHBoxLayout* layout = new QHBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(chartView);
    setLayout(layout);

    timerId = startTimer(1000);
    
}

Chart::~Chart()
{
}


void Chart::timerEvent(QTimerEvent* event) {
    if (event->timerId() == timerId) {  
        dataReceived(newdata);
        //qDebug() << newdata;
        axisX->setTitleText(QStringLiteral("���ڵ�ʱ����").append(QDateTime::currentDateTime().toString("hh:mm")));
        if (event->timerId() == 10000)
        {
            scatterSeries->append(QDateTime::currentDateTime().toMSecsSinceEpoch(), newdata);
        }
    }
}

void Chart::dataReceived(qreal value) {
    
    if (isVisible()) {       
        QDateTime currentTime = QDateTime::currentDateTime();
        chart->axisX()->setMin(QDateTime::currentDateTime().addSecs(-60 * 1));             
        chart->axisX()->setMax(QDateTime::currentDateTime().addSecs(0));       
        splineSeries->append(currentTime.toMSecsSinceEpoch(), newdata);      
    }
}