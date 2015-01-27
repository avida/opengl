#pragma once
#include <boost/shared_ptr.hpp>
#include "lighting_technique.h"

namespace GL
{
	
class TechniqueFactory;

typedef boost::shared_ptr<TechniqueFactory> TechniqueFactoryPtr;

class TechniqueFactory
{
public:
	static TechniqueFactoryPtr Instance();
	void CreateTechnique();
private:
	TechniqueFactory(void);
	static TechniqueFactoryPtr m_static_this;
	LightingTechnique m_light_tech;

};
}