#include "Primitive.h"

namespace GL
{

Primitive::Primitive()
{
	if (!m_technique.Init())
        {
            printf("Error initializing the lighting technique\n");
        }
        m_technique.Enable();
        m_technique.SetTextureUnit(0);
}

}