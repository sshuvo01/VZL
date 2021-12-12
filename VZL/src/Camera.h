#ifndef _VZL_RAY_H_
#define _VZL_RAY_H_
#include "Vector.h"

namespace vzl
{

	struct CameraSetting
	{
		Vector position{0.0, 0.0, 0.0};
		Vector viewDirection{0.0, 0.0, 1.0};
		Vector upDirection{0.0, 1.0, 0.0};
		Vector rightDirection{1.0, 0.0, 0.0};
		double FOV = 90.0; // in degree or whatever 
		double aspectRatio = 1.3333;
	};


	class Camera
	{
	public:
		Camera();
		~Camera() { }
		Camera(const CameraSetting& camset);

		void SetupCamera(const CameraSetting& camset);
		inline CameraSetting GetCameraSetting() const { return m_Setting; } 
		inline const Vector GetPosition() const { return m_Setting.position; }
		inline double GetTanHFOV() const { return m_tanHFOV2; }
		inline double GetTanVFOV() const { return m_tanVFOV2; }

		const Vector View(double x, double y) const;
	private:
		CameraSetting m_Setting;
		double m_tanHFOV2, m_tanVFOV2;
	};


} // namespace vzl

#endif