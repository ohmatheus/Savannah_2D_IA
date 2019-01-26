#pragma once

#include "glew.h"
#include "assert.h"

typedef	unsigned int		uint;
typedef	unsigned __int64	u64;


#define GL_CHECK_ERRORS assert(glGetError() == GL_NO_ERROR);

#define	ARRAY_COUNT(__arr)				(sizeof(__arr) / sizeof((__arr)[0]))

#ifndef GLUE
#	define	GLUE(a, b)			__GLUE(a, b)
#	define	__GLUE(a, b)		a ## b			// don't directly use this one
#endif // !GLUE

#if	!defined(__COUNTER__)
#	define	__COUNTER__		__LINE__
#endif

#define MAX(a, b) a > b ? a : b;
#define MIN(a, b) a < b ? a : b;

#define PI 3.14159265359f

#include "QScopedLock.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// leak detection
//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>
//#ifdef _DEBUG
//#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
//// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
//// allocations to be of _CLIENT_BLOCK type
//#else
//#define DBG_NEW new
//#endif
//
//#include <vld.h>

