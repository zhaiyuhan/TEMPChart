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
    chart->setTitle(QStringLiteral("单片机温度传感器数据"));
    axisX->setTickCount(10);                             //设置坐标轴格数
    axisY->setTickCount(6);
    axisX->setFormat("ss");                        //设置时间显示格式
    axisY->setMin(0);                                    //设置Y轴范围
    axisY->setMax(50);
    axisX->setTitleText(QStringLiteral("实时时间"));                       //设置X轴名称
    axisY->setLinePenColor(QColor(Qt::darkBlue));        //设置坐标轴颜色样式
    axisY->setGridLineColor(QColor(Qt::darkBlue));
    axisY->setGridLineVisible(false);                    //设置Y轴网格不显示
    axisY->setLinePen(penY);
    axisX->setLinePen(penY);

    chart->addAxis(axisX, Qt::AlignBottom);               //设置坐标轴位于chart中的位置
    chart->addAxis(axisY, Qt::AlignLeft);

    splineSeries->attachAxis(axisX);                           //把数据添加到坐标轴上
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
        axisX->setTitleText(QStringLiteral("现在的时间是").append(QDateTime::currentDateTime().toString("hh:mm")));
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