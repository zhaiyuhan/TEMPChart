 #pragma once

#include <QWidget>
#include <QChart>
#include <QChartView>
#include <QSplineSeries>
#include <QScatterSeries>

#include <QList>
#include <QDateTimeAxis>
#include <QValueAxis>
using namespace QtCharts;

class Chart : public QWidget
{
	Q_OBJECT

public:
	explicit Chart(QWidget *parent);
	~Chart();
    void setData(qreal value) 
    {
        newdata = value;
    }
protected:
    void timerEvent(QTimerEvent* event) Q_DECL_OVERRIDE;
    qreal getData()
    {
        return newdata;
    }
private:   
    void dataReceived(qreal value);
    int timerId;   
    qreal newdata;
    QChart* chart;
    QChartView* chartView;
    QDateTimeAxis* axisX;
    QValueAxis* axisY;
    QSplineSeries* splineSeries;//»­Ïß
    QScatterSeries* scatterSeries;//»­µã
};
