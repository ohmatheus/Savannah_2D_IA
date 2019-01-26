#pragma once

#include "IEntity.h"

//----------------------------------------------------------

class MeshData final
{
public:
	MeshData();
	~MeshData();

	uint	VAO() { return m_VAO; }
	uint	Mode();

	void	SetVertices(float *vertices, uint verticeNbr, uint size, uint stride, uint mode);

protected:
	uint	m_VBO;
	uint	m_VAO;
	uint	m_Size; // Specifies the number of components per generic vertex attribute.
	uint	m_Stride; // Specifies the byte offset between consecutive generic vertex attributes.
	uint	m_Mode; // Specifies what kind of primitives to render.
	float	*m_Vertices;
};

//----------------------------------------------------------
