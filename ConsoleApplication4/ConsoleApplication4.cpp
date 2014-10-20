// ConsoleApplication4.cpp : Defines the entry point for the console application.
//
#include <math.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include <iostream>
#include "common/ogldev_util.h"
#include "pipeline.h"
#include "camera.h"
#include "common/ogldev_texture.h"
#include "lighting_technique.h"
#include "glut_backend.h"

#define MOUSE_DOWN 0
#define MOUSE_UP 1

#define WINDOW_WIDTH  1024
#define WINDOW_HEIGHT 768

#define CIRCLE_SCALE(x) x >= 1 ? x=0 : x=x

struct Vertex
{
    Vector3f m_pos;
    Vector2f m_tex;
    Vector3f m_normal;

    Vertex() {}

    Vertex(Vector3f pos, Vector2f tex)
    {
        m_pos = pos;
        m_tex = tex;
        m_normal = Vector3f(0.0f, 0.0f, 0.0f);
    }
}; 

class Tutorial17 : public ICallbacks
{
public:

    Tutorial17()
    {
        m_pGameCamera = NULL;
        m_pTexture = NULL;
        m_pEffect = NULL;
        m_scale = 0.0f;
		m_red_scale = 0.0f;
		m_green_scale = 0.0f;
		m_blue_scale = 0.0f;
        m_directionalLight.Color = Vector3f(1.0f, 1.0f, 1.0f);
        m_directionalLight.AmbientIntensity = 0.0f;
        m_directionalLight.DiffuseIntensity = 0.0f;
        m_directionalLight.Direction = Vector3f(1.0f, 0.0, 0.0);
    }

    ~Tutorial17()
    {
        delete m_pEffect;
        delete m_pGameCamera;
        delete m_pTexture;
    }

    bool Init()
    {
        Vector3f Pos(0.0f, 0.0f, -3.0f);
        Vector3f Target(0.0f, 0.0f, 1.0f);
        Vector3f Up(0.0, 1.0f, 0.0f);
        m_pGameCamera = new Camera(WINDOW_WIDTH, WINDOW_HEIGHT, Pos, Target, Up);

        unsigned int Indices[] = { 0, 3, 1,
                                   1, 3, 2,
                                   2, 3, 0,
                                   1, 2, 0,
								   4,5,6,
								   6,5,4
									};

        CreateIndexBuffer(Indices, sizeof(Indices));

        CreateVertexBuffer(Indices, ARRAY_SIZE_IN_ELEMENTS(Indices));
        
        m_pEffect = new LightingTechnique();

        if (!m_pEffect->Init())
        {
            printf("Error initializing the lighting technique\n");
            return false;
        }

        m_pEffect->Enable();

        m_pEffect->SetTextureUnit(0);

        m_pTexture = new Texture(GL_TEXTURE_2D, "test.png");

        if (!m_pTexture->Load()) {
            return false;
        }

        return true;
    }

    void Run()
    {
        GLUTBackendRun(this);
    }

    virtual void RenderSceneCB()
    {
        m_pGameCamera->OnRender();

        glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);
       
        m_scale += 0.01f;

        Pipeline p;
        p.Rotate(0.0f, m_scale, 0.0f);
        p.WorldPos(0.0f, 0.0f, 1.0f);
        p.SetCamera(m_pGameCamera->GetPos(), m_pGameCamera->GetTarget(), m_pGameCamera->GetUp());
        p.SetPerspectiveProj(60.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 1.0f, 100.0f);
        m_pEffect->SetWVP(p.GetWVPTrans());
        const Matrix4f& WorldTransformation = p.GetWorldTrans();
        m_pEffect->SetWorldMatrix(WorldTransformation);
        m_pEffect->SetDirectionalLight(m_directionalLight);

		m_pEffect->SetEyeWorldPos(m_pGameCamera->GetPos());
		m_pEffect->SetMatSpecularIntensity(1.0f);
		m_pEffect->SetMatSpecularPower(32);
        
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)20);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
        m_pTexture->Bind(GL_TEXTURE0);
        glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);

        glutSwapBuffers();
    }

    virtual void IdleCB()
    {
        RenderSceneCB();
    }

    virtual void SpecialKeyboardCB(int Key, int x, int y)
    {
        m_pGameCamera->OnKeyboard(Key);
    }


    virtual void KeyboardCB(unsigned char Key, int x, int y)
    {
        switch (Key) {
            case 'q':
                glutLeaveMainLoop();
                break;

            case 'a':
                m_directionalLight.AmbientIntensity += 0.05f;
                break;

            case 's':
                m_directionalLight.AmbientIntensity -= 0.05f;
                break;
		    case 'z':
                m_directionalLight.DiffuseIntensity += 0.05f;
                break;
            case 'x':
                m_directionalLight.DiffuseIntensity -= 0.05f;
                break;
        }
    }


    virtual void PassiveMouseCB(int x, int y)
    {

    }

	virtual void ActiveMouseCB(int x, int y)
	{
        m_pGameCamera->OnMouse(x, y);
	}

	virtual void MouseMove(int button, int state, int x,int y)
	{
		if (state == MOUSE_DOWN)
		{
			m_pGameCamera->OnMouseButtonDown(x,y);
		}
		else
		{
			m_pGameCamera->OnMouseButtonUp();
		}
	}
private:

    void CreateVertexBuffer(const unsigned int* pIndices, unsigned int IndexCount)
    {
        Vertex Vertices[7] = { Vertex(Vector3f(-1.0f, -1.0f, 0.5773f), Vector2f(0.0f, 0.0f)),
                               Vertex(Vector3f(0.0f, -1.0f, -1.15475f), Vector2f(0.5f, 0.0f)),
                               Vertex(Vector3f(1.0f, -1.0f, 0.5773f),  Vector2f(1.0f, 0.0f)),
                               Vertex(Vector3f(0.0f, 1.0f, 0.0f),      Vector2f(0.5f, 1.0f)),
							   Vertex(Vector3f(0.0f, 0.0f, 0.0f),	 Vector2f(0.0f, 0.0f)),
							   Vertex(Vector3f(2.0f, 0.0f, -2.0f),	 Vector2f(1.0f, 0.0f)),
							   Vertex(Vector3f(0.0f, 2.0f, -2.0f),	 Vector2f(0.0f, 1.0f))

								};
        
        unsigned int VertexCount = ARRAY_SIZE_IN_ELEMENTS(Vertices);

        CalcNormals(pIndices, IndexCount, Vertices, VertexCount);

        glGenBuffers(1, &m_VBO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
    }

    void CreateIndexBuffer(const unsigned int* pIndices, unsigned int SizeInBytes)
    {
        glGenBuffers(1, &m_IBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, SizeInBytes, pIndices, GL_STATIC_DRAW);
    }

	void CalcNormals(const unsigned int* pIndices, unsigned int IndexCount, Vertex* pVertices, unsigned int VertexCount)
	{
		for (unsigned int i = 0 ; i < IndexCount ; i += 3) {
			unsigned int Index0 = pIndices[i];
			unsigned int Index1 = pIndices[i + 1];
			unsigned int Index2 = pIndices[i + 2];
			Vector3f v1 = pVertices[Index1].m_pos - pVertices[Index0].m_pos;
			Vector3f v2 = pVertices[Index2].m_pos - pVertices[Index0].m_pos;
			Vector3f Normal = v1.Cross(v2);
			Normal.Normalize();

			pVertices[Index0].m_normal += Normal;
			pVertices[Index1].m_normal += Normal;
			pVertices[Index2].m_normal += Normal;
		}

		for (unsigned int i = 0 ; i < VertexCount ; i++) {
			pVertices[i].m_normal.Normalize();
		}
	} 
    GLuint m_VBO;
    GLuint m_IBO;
    LightingTechnique* m_pEffect;
    Texture* m_pTexture;
    Camera* m_pGameCamera;
    float m_scale;
	float m_red_scale;
	float m_green_scale;
	float m_blue_scale;
    DirectionalLight m_directionalLight;
};


int main(int argc, char** argv)
{
    GLUTBackendInit(argc, argv);

    if (!GLUTBackendCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, 32, false, "Tutorial 17")) {
        return 1;
    }

    Tutorial17* pApp = new Tutorial17();

    if (!pApp->Init()) {
        return 1;
    }

    pApp->Run();

    delete pApp;
 
    return 0;
}