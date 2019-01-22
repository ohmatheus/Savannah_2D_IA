#pragma once

#include <QThread>

// QThread's queued slots and invoked methods will execute in the old thread.
//----------------------------------------------------------

class	QWorkerThread final : public QThread
{
	Q_OBJECT
public:
	using Super = QThread;
	QWorkerThread(QObject *parent = nullptr);
	virtual ~QWorkerThread();

	void run() override = 0;

private:
};

//----------------------------------------------------------
