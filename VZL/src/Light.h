#ifndef _VZL_LIGHT_H_
#define _VZL_LIGHT_H_
#include "Vector.h"
#include "Color.h"

namespace vzl
{

class Light
{
public:
    Light() : m_Position{0.0, 0.0, 0.0}, m_Color{1.0, 0.0, 0.0, 1.0} {}
    Light(const Vector& position, const Color& color) : m_Position(position), m_Color(color) { }
    ~Light() {}

    const Vector& GetPosition() const;
    const Color& GetColor() const;

    void SetPosition(const Vector& position);
    void SetColor(const Color& color);
private:
    Vector m_Position;
    Color m_Color;
};

} // namespace vzl

#endif