#include "stdafx.h"
#include "gl_scene.h"
#include "camera.h"
#include <boost/make_shared.hpp>

#define WINDOW_WIDTH  1024
#define WINDOW_HEIGHT 768

namespace GL
{
GLScene::GLScene(void)
{
	Vector3f Pos(0.0f, 0.0f, -3.0f);
	Vector3f Target(0.0f, 0.0f, 1.0f);
	Vector3f Up(0.0, 1.0f, 0.0f);
	m_pGameCamera = boost::make_shared<Camera>(WINDOW_WIDTH, WINDOW_HEIGHT, Pos, Target, Up);
}
                                                                            
GLScene::~GLScene(void)
{
}

void GLScene::Render()
{
}

}