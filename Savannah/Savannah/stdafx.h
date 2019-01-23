#pragma once

#include "glew.h"
#include "assert.h"

typedef	unsigned int uint;

#define GL_CHECK_ERRORS assert(glGetError() == GL_NO_ERROR);

#define	ARRAY_COUNT(__arr)				(sizeof(__arr) / sizeof((__arr)[0]))

