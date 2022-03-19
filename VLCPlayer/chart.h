#ifndef CHART_H
#define CHART_H

#include <QWidget>

#include <QChartView>
#include <QChart>
#include <QSplineSeries>
#include <QHBoxLayout>
#include <QValueAxis>

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QValueAxis>

QT_CHARTS_USE_NAMESPACE

class Chart : public QWidget
{
    Q_OBJECT
public:
    explicit Chart(QString _yname, qreal _ymin, qreal _ymax, int _ytickc,QWidget *parent = nullptr);
    ~Chart();

    QChart *qchart;
    QChartView *chartview;

    QSplineSeries *series_1;


    QHBoxLayout *layout;
    QDateTimeAxis *axisX;
    QValueAxis *axisY;

    QString chartname;
    //坐标轴参数
    QString xname;
    qreal xmin;
    qreal xmax;
    int xtickc;
    QString yname;
    qreal ymin;
    qreal ymax;
    int ytickc;

public:
    void setAxis(QString _yname, qreal _ymin, qreal _ymax, int _ytickc);

    void buildChart(double x, qreal y);

};

#endif // CHART_H
