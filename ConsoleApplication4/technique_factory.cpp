#include <boost/make_shared.hpp>

#include "technique_factory.h"

namespace GL
{

TechniqueFactoryPtr TechniqueFactory::Instance()
{
	if (!m_static_this)
	{
		m_static_this == boost::make_shared<TechniqueFactory>();
	}
	return m_static_this;
}

TechniqueFactory::TechniqueFactory(void)
{
}



}