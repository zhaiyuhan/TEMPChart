#pragma once

#include <QObject>

class STCDownloader : public QObject
{
	Q_OBJECT

public:
	STCDownloader(QObject *parent);
	~STCDownloader();
};
