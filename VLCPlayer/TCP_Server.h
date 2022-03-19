#pragma once
#include <QtcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QObject>
#include <QThread>

#include <QByteArray>

class TCP_Server:public QThread
{
	Q_OBJECT
	QTcpSocket *tcpSocket;  //Ì×½Ó×Ö

	QTcpServer *tcpServer;

	int port;

public:
	TCP_Server();

	~TCP_Server();

	bool TCP_init();

	void run() override;

private slots:

	void NewConnectionSlot();

	void disConnectionSlot();

	void ReadData();

signals:
	void medical_data(const char*);

};

