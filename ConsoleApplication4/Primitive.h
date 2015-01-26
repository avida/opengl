#pragma once
#include "pipeline.h"
#include "lighting_technique.h"

namespace GL
{
class Primitive
{
public:
	Primitive();
	virtual ~Primitive() {}

protected:
	LightingTechnique m_technique;

};

	
}