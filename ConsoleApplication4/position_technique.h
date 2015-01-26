#pragma once
#include "common\technique.h"
#include "math_3d.h"

namespace GL
{
class PositionTechnique :
	public Technique
{
public:
	PositionTechnique(void);
	~PositionTechnique(void);
	void SetWVP(const Matrix4f& WVP);
    void SetWorldMatrix(const Matrix4f& WVP);
    void SetTextureUnit(unsigned int TextureUnit);
	bool Init();
protected:
	GLuint m_WVPLocation;
    GLuint m_WorldMatrixLocation;
    GLuint m_samplerLocation;
};

}