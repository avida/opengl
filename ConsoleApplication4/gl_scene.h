#pragma once

#include <list>

#include "mesh.h"
#include "camera.h"

namespace GL
{

typedef std::list<MeshPtr> GLMeshList;

class GLScene
{
public:
	void Render();
	GLScene(void);
	~GLScene(void);
	CameraPtr GetCamera() { return m_pGameCamera; };
private:
	GLMeshList m_meshes;
	CameraPtr m_pGameCamera;


};

}
