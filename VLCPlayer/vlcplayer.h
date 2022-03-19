#pragma once

#include <QtWidgets/QWidget>
#include <QLabel>
#include<QScreen>
#include "ui_vlcplayer.h"
#include <QTimer>

#include "chart.h"
#include "callout.h"
#include <QDateTime>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE




struct libvlc_media_player_t;

class VLCPlayer : public QWidget
{
	Q_OBJECT

public:
	VLCPlayer(QWidget *parent = Q_NULLPTR);
	//串口尺寸变化
	void resizeEvent(QResizeEvent* e);
	//双击全屏
	void mouseDoubleClickEvent(QMouseEvent* e);

	//桌面宽高信息
	int screen_width;
	int screen_height;


	void Init_timer();
	void Init_chart();

	Chart *qchart1;
	Chart *qchart2;
	Chart *qchart3;

	QTimer *timer;
	Callout *tip;

private slots:
	void openFile();
	void openURL();
	void test();
	void display_data(const char* data);
private:
	Ui::VLCPlayerClass ui;
	QWidget* m_pSubWidgets;
	//QLabel* label;
};


