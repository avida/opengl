#include "stdafx.h"
#include "mesh.h"

namespace GL
{

Mesh::Mesh(Vertex *vertexes, int v_size, unsigned int *indexes, int i_size):
	m_vertexes(vertexes), m_vert_size(v_size), m_indexes(indexes), m_i_size(i_size)
{}

void Mesh::Init()
{
	CalcNormals();
	glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, m_vert_size * sizeof(Vertex), m_vertexes, GL_STATIC_DRAW);

	glGenBuffers(1, &m_IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_i_size * sizeof(GLuint), m_indexes, GL_STATIC_DRAW);

}

void Mesh::CalcNormals()
{
	for (unsigned int i = 0 ; i < m_i_size ; i += 3) {
		unsigned int Index0 = m_indexes[i];
		unsigned int Index1 = m_indexes[i + 1];
		unsigned int Index2 = m_indexes[i + 2];
		Vector3f v1 = m_vertexes[Index1].m_pos - m_vertexes[Index0].m_pos;
		Vector3f v2 = m_vertexes[Index2].m_pos - m_vertexes[Index0].m_pos;
		Vector3f Normal = v1.Cross(v2);
		Normal.Normalize();

		m_vertexes[Index0].m_normal += Normal;
		m_vertexes[Index1].m_normal += Normal;
		m_vertexes[Index2].m_normal += Normal;
	}

	for (unsigned int i = 0 ; i < m_vert_size ; i++) {
		m_vertexes[i].m_normal.Normalize();
	}
}

Mesh::~Mesh(void)
{
}
}