#pragma once
#include "primitive.h"
#include "geometry.h"
#include <boost/shared_ptr.hpp>

namespace GL
{
class Mesh;

typedef boost::shared_ptr<Mesh> MeshPtr;

class Mesh :
	public Primitive
{
public:
	Mesh(Vertex *vertexes, int v_size, unsigned int *indexes, int i_size);
	virtual ~Mesh(void);
protected:
	void Init();
	void CalcNormals();
	Pipeline m_pipeline;
	Vertex *m_vertexes;
	int m_vert_size;
	unsigned int *m_indexes;
	int m_i_size;

	GLuint m_VBO;
	GLuint m_IBO;
};
}
