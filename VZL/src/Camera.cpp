#include "Camera.h"
#include <cmath>
#include "Ray.h"
#include <iostream>

namespace vzl
{


Camera::Camera()
: m_tanHFOV2(0.0), m_tanVFOV2(0.0)
{
    CameraSetting camset;
    SetupCamera(camset);
    std::cout << "constructed camera\n";
}

Camera::Camera(const CameraSetting& camset)
 : m_Setting(camset), m_tanHFOV2(0.0), m_tanVFOV2(0.0)
{
    SetupCamera(camset);
}

void Camera::SetupCamera(const CameraSetting& camset)
{
    m_Setting = camset;
    const double PYEE = 3.14159265;
    m_tanHFOV2 = std::tan(m_Setting.FOV * 0.5 * PYEE / 180.0);
    m_tanVFOV2 = m_tanHFOV2 / m_Setting.aspectRatio;
    //std::cout << "tanhfov2: " << m_tanHFOV2 << ", tanVFOV2: " << m_tanVFOV2 << std::endl;

    m_Setting.viewDirection.normalize();

    m_Setting.upDirection = m_Setting.upDirection - (m_Setting.viewDirection * m_Setting.upDirection) * m_Setting.viewDirection;
    m_Setting.upDirection.normalize();

    m_Setting.rightDirection = m_Setting.viewDirection ^ m_Setting.upDirection;
    m_Setting.rightDirection.normalize();
}

const Vector Camera::View(double x, double y) const
{
    double xx = (2.0 * x - 1.0) * m_tanHFOV2;
    double yy = (2.0 * y - 1.0) * m_tanVFOV2;

    Vector X = xx * m_Setting.rightDirection + yy * m_Setting.upDirection;
    return (X + m_Setting.viewDirection).unitvector();
}


} // namespace vzl

