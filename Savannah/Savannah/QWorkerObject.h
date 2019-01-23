#pragma once

#include <QObject>
#include <functional>

// QThread's queued slots and invoked methods will execute in the caller thread.
//----------------------------------------------------------

class	QWorkerObject final : public QObject
{
	Q_OBJECT
public:
	using Super = QObject;
	QWorkerObject(QObject *parent = nullptr);
	virtual ~QWorkerObject();

	void	SetFunc(const std::function<void()> &func);

public slots:
	void	Play();

signals:
	void	End();

private:
	std::function<void()>	m_Func;
};
//----------------------------------------------------------

