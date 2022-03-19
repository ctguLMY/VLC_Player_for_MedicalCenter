#include "vlcplayer.h"
#include "vlc.h"
#include <QDebug>
#include <QOpenGLWidget>
#include <QApplication>
#include <QProcess> 
#include <QGridLayout>
#include "TCP_Server.h"

QT_CHARTS_USE_NAMESPACE

VLCPlayer::VLCPlayer(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setWindowTitle(QString::fromLocal8Bit("远程医疗信息服务平台"));


	QString prog = "run.bat";
	QProcess *myProcess = new QProcess(parent);
	myProcess->start(prog);

	Init_chart();
	Init_timer();

	//connect(ui.btnOpenFile, &QPushButton::clicked, this, &VLCPlayer::openFile);
	connect(ui.btnOpenURL, &QPushButton::clicked, this, &VLCPlayer::openURL);

	TCP_Server *tcp_recv = new TCP_Server();
	tcp_recv->TCP_init();
	connect(tcp_recv, SIGNAL(medical_data(const char*)), this, SLOT(display_data(const char *)), Qt::AutoConnection);
	//connect(ui.btnOpenURL, &QPushButton::clicked, this, &VLCPlayer::openURL);
	//connect(m_pSubWidgets, &QOpenGLWidget::mouseDoubleClickEvent, this, &VLCPlayer::test);

	QScreen *screen = QGuiApplication::primaryScreen();
	QRect mm = screen->availableGeometry();
	screen_width = mm.width();
	screen_height = mm.height();
	//m_pSubWidgets = ui.openGLWidget;
	m_pSubWidgets = new QOpenGLWidget(this);
	ui.gridLayout_video->addWidget(m_pSubWidgets);
}
	
void VLCPlayer::mouseDoubleClickEvent(QMouseEvent* e)
{
	qDebug() << "height:" << screen_height << "\n";
	qDebug() << "width:" << screen_width << "\n";
	
	if (isFullScreen()) {
		this->showNormal();
	}
	else {
		this->showFullScreen();
		m_pSubWidgets->resize(QSize(screen_width, screen_height));
	}
}

void VLCPlayer::display_data(const char* data) {
	const char *p1;
	int spo2;
	int heart;
	float temp;
	double t = QDateTime::currentDateTime().toMSecsSinceEpoch();
	ui.textBrowser_log->insertPlainText(data);
	if ((p1 = strstr(data, "maibo=")) != NULL) {
		heart = (*(p1 + 6)-'0') * 10 + (*(p1 + 7)-'0');
		ui.label_heart->setText(QString::number(heart));
		qchart2->buildChart(t, heart);
		
	}
	if ((p1 = strstr(data, "xueyang=")) != NULL) {
		spo2 = (*(p1 + 8) - '0') * 10 + (*(p1 + 9) - '0');
		ui.label_spo2->setText(QString::number(spo2));
		qchart3->buildChart(t,spo2);
		
	}
	if ((p1 = strstr(data, "ture=")) != NULL) {
		temp = (*(p1 + 5) - '0') * 10 + (*(p1 + 6) - '0')* 1.0 + (*(p1+8)-'0')*1.0/10;
		ui.label_temperature->setText(QString::number(temp));
		qchart1->buildChart(t,temp);
	}
	qDebug() << "data:" << data << "\n";
}
void VLCPlayer::test() {
	qDebug() << "height:" << screen_height << "\n";
	qDebug() << "width:" << screen_width << "\n";
}
void VLCPlayer::openFile()
{
	auto player = new VLC(m_pSubWidgets);
			// 打开成功
	if (player->OpenFile())
	{
		resizeEvent(NULL);
		m_pSubWidgets->show();
		m_pSubWidgets->raise();
	}
	else
	{
		delete player;
		delete m_pSubWidgets;
	}
			
}
	

void VLCPlayer::resizeEvent(QResizeEvent *e)
{
	//m_pSubWidgets->resize(this->width()*3/4, this->height()-35);

//	ui.lineEdit->resize(this->width() * 3 / 5, 25);
	//ui.lineEdit->move(0, this->height()-40);
	//ui.btnOpenFile->move(this->width() * 3 / 5+10, this->height()-32);
	//ui.btnOpenURL->move(this->width() * 3 / 5+100, this->height()-32);

	//m_pSubWidgets->resize(QSize(w, h));
	//m_pSubWidgets->move(0, 0);

	//QPoint pos = ui.btnOpenFile->pos();
	//pos.setY(height() - 24);
	//ui.btnOpenFile->move(pos);

	//pos = ui.btnOpenURL->pos();
	//pos.setY(height() - 24);
	//ui.btnOpenURL->move(pos);

	//pos = ui.lineEdit->pos();
	//pos.setY(height() - 24);
	//ui.lineEdit->move(pos);
}


void VLCPlayer::openURL()
{
	auto player = new VLC(m_pSubWidgets);
		// 打开成功
	if (player->OpenURL(ui.lineEdit->text().toUtf8().constData()))
	{
			resizeEvent(NULL);
			m_pSubWidgets->show();
	}
	else
	{
		delete player;
		delete m_pSubWidgets;
	}

}


void VLCPlayer::Init_chart() {

	qchart1 = new Chart("temperature", 20, 42, 5);


	qchart2 = new Chart("heart", 50, 120, 5);


	qchart3 = new Chart("spo2", 90, 100, 5);

	
	//ui.gridLayout1->addwidget(qchart1->chartview);
	ui.gridLayout_temp->addWidget(qchart1->chartview);
	ui.gridLayout_heart->addWidget(qchart2->chartview);
	ui.gridLayout_spo2->addWidget(qchart3->chartview);
	tip = 0;

}

void VLCPlayer::Init_timer() {
	timer = new QTimer();
	timer->setInterval(500);
	timer->start();
}