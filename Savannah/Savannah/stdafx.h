#pragma once

#include "glew.h"
#include "assert.h"

typedef	unsigned int uint;

#define GL_CHECK_ERRORS assert(glGetError() == GL_NO_ERROR);

#define	ARRAY_COUNT(__arr)				(sizeof(__arr) / sizeof((__arr)[0]))

#ifndef GLUE
#	define	GLUE(a, b)			__GLUE(a, b)
#	define	__GLUE(a, b)		a ## b			// don't directly use this one
#endif // !GLUE

#if	!defined(__COUNTER__)
#	define	__COUNTER__		__LINE__
#endif

#define PI 3.14159265359f

#include "QScopedLock.h"

