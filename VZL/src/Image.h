#ifndef _VZL_IMAGE_H_
#define _VZL_IMAGE_H_
#include "Color.h"
#include "Vector.h"
#include "Camera.h"
#include <string>
#include "Ray.h"
#include "Scene.h"

namespace vzl
{

class Image
{
public:
	Image(unsigned int width = 1920, unsigned int height = 1080, unsigned int nrChannel = 3);

	Image() = delete;
	Image(const Image& copy) = delete;
	Image(const Image&& copy) = delete;
	Image& operator=(const Image& other) = delete;
	Image& operator=(const Image&& other) = delete;
	~Image();

	void CaptureAndWriteImage(const Scene& scene, const std::string& filename);
	void debugrgb();
private:
    Camera m_Camera;
	unsigned int m_Width, m_Height, m_NrChannel;
    /* private functions */
};

} // namespace vzl

#endif