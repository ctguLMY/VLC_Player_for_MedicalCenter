#include "chart.h"
#include <QDateTime>
Chart::Chart( QString _yname, qreal _ymin, qreal _ymax, int _ytickc, QWidget* parent){
    setParent(parent);
    chartname = "xyz";

    series_1 = new QSplineSeries();


    series_1->setUseOpenGL(true);


    qchart = new QChart;
    chartview = new QChartView(qchart);
    layout = new QHBoxLayout(this);



    axisX = new QDateTimeAxis;
   // axisX->setTickCount(10);
    axisX->setFormat("mm:ss");
   // axisX->setTitleText("Time");

    axisY = new QValueAxis(this);

    qchart->addAxis(axisX, Qt::AlignBottom); //下：Qt::AlignBottom  上：Qt::AlignTop
    qchart->addAxis(axisY, Qt::AlignLeft);   //左：Qt::AlignLeft    右：Qt::AlignRight

    qchart->addSeries(series_1);
	qchart->legend()->hide(); //隐藏图例

    series_1->attachAxis(axisX);
    series_1->attachAxis(axisY);

    axisX->setGridLineVisible(true);   //网格线可见
    axisX->setTickCount(6);       //设置多少个大格



    axisY->setRange(_ymin, _ymax);
    axisY->setLabelFormat("%u");
    axisY->setGridLineVisible(true);
    axisY->setTickCount(_ytickc);
    axisY->setMinorTickCount(8);
   // axisY->setTitleText(_yname);

    chartview->setRenderHint(QPainter::Antialiasing);//防止图形走样
}

void Chart::setAxis(QString _yname, qreal _ymin, qreal _ymax, int _ytickc){

    yname = _yname; ymin = _ymin; ymax = _ymax; ytickc = _ytickc;

    //axisX->setRange(xmin, xmax);    //设置范围
    //axisX->setLabelFormat("%u");   //设置刻度的格式
    /************************************
        %u 无符号十进制整数
        %s 字符串
        %c 一个字符
        %d 有符号十进制整数
        %e 浮点数、e-记数法
        %f 浮点数、十进制记数法
        %s 字符串
    ****************************************/

}

void Chart::buildChart(double xt, qreal y)
{

    series_1->setPen(QPen(Qt::blue,3,Qt::SolidLine));
    series_1->append(xt, y);
        //series->clear();
    axisX->setRange(QDateTime::fromMSecsSinceEpoch(xt-5000), QDateTime::fromMSecsSinceEpoch(xt));
   // qchart->setTitle(chartname);
    qchart->setAnimationOptions(QChart::SeriesAnimations);//设置曲线动画模式
    qchart->legend()->hide(); //隐藏图例
   // qchart->addSeries(series);//输入数据
   // qchart->setAxisX(axisX, series);
    //qchart->setAxisY(axisY, series);
}

Chart::~Chart(){
    delete qchart;
}
