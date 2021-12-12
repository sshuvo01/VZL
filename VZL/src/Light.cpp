#include "Light.h"

namespace vzl
{

const Vector& Light::GetPosition() const
{
    return m_Position;
}

const Color& Light::GetColor() const
{
    return m_Color;
}

void Light::SetPosition(const Vector& position)
{
    m_Position = position;
}

void Light::SetColor(const Color& color)
{
    m_Color = color;
}

} // namespace vzl