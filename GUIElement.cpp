#include "GUIElement.h"



GUIElement::GUIElement(bool visible) : m_visible(visible)
{
}



bool GUIElement::isVisible() const
{
	return m_visible;
}
