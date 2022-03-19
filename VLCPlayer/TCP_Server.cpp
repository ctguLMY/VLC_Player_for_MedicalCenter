#include "TCP_Server.h"
#include <QDateTime>

TCP_Server::TCP_Server() {
	port = 10208;
	tcpServer = new QTcpServer();

}

TCP_Server::~TCP_Server() {
	
	delete tcpServer;
	delete tcpSocket;

}

bool TCP_Server::TCP_init() {

	
	bool ok = tcpServer->listen(QHostAddress::Any,port);
	if (ok) {
		connect(tcpServer, SIGNAL(newConnection()), this, SLOT(NewConnectionSlot()));
		return true;
	}
	else {
		tcpServer->close();
		return false;
	}
	
}

void TCP_Server::NewConnectionSlot() {

	tcpSocket = tcpServer->nextPendingConnection();
	connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(ReadData()));
	connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(disConnectionSlot()));
	qDebug() << "new connection accepted!!";
}

void TCP_Server::run() {

}

void TCP_Server::ReadData() {

	QByteArray ba;
	//qDebug() << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") << endl;
	ba = tcpSocket->readAll();		
	emit medical_data(ba.data());
}

void TCP_Server::disConnectionSlot() {
	qDebug() << "client disconnect" << endl;
}