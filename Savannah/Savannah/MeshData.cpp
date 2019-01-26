#include "stdafx.h"

#include "MeshData.h"

//----------------------------------------------------------

MeshData::MeshData()
:	m_Vertices(nullptr)
,	m_VBO(0)
,	m_VAO(0)
{
}

//----------------------------------------------------------

MeshData::~MeshData()
{}

//----------------------------------------------------------

void	MeshData::SetVertices(float *vertices, uint verticeNbr, uint size, uint stride, uint mode)
{
	m_Vertices = (float*)malloc(verticeNbr);
	std::memcpy(m_Vertices, vertices, verticeNbr);
	m_Size = size;
	m_Stride = stride;
	m_Mode = mode;

	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);

	glBindVertexArray(m_VAO);
	// bind, 1 possible in the same time / buffer type
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	// copies data in the buffers memory
	// GL_STATIC_DRAW: the data will most likely not change at all or very rarely.
	// GL_DYNAMIC_DRAW : the data is likely to change a lot.
	// GL_STREAM_DRAW : the data will change every time it is drawn.
	glBufferData(GL_ARRAY_BUFFER, verticeNbr, m_Vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, m_Size, GL_FLOAT, GL_FALSE, m_Stride, (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

//----------------------------------------------------------

uint	MeshData::Mode()
{
	return m_Mode;
}

//----------------------------------------------------------
