#include "GUIElement.h"



GUIElement::GUIElement(bool visible) : visible(visible)
{
}



bool GUIElement::isVisible() const
{
	return visible;
}
