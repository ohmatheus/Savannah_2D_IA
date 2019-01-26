#pragma once

#include <QMutex>
//----------------------------------------------------------

class	TScopedLock // non copyable
{
private:
	QMutex	&m_Lockable;
public:
	TScopedLock(QMutex &lockable) : m_Lockable(lockable) { m_Lockable.lock(); }
	~TScopedLock() { m_Lockable.unlock(); }
};

//----------------------------------------------------------

#define SCOPEDLOCK(__prim) TScopedLock GLUE(__local_lock_, __COUNTER__)(__prim);

//----------------------------------------------------------
