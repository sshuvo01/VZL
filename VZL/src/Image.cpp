#include <fstream>
#include <iostream>
#include "Image.h"
#include "Ray.h"
#include "Scene.h"
#include <cstring>
#include <string>
#include "ThingToHit.h"
#include "Sphere.h"

namespace vzl
{


	Image::Image(unsigned int width, unsigned int height, unsigned int nrChannel)
	 : m_Width(width), m_Height(height), m_NrChannel(nrChannel)
	{

	}

	Image::~Image()
	{

	}

	inline void DebugVector(const Vector& v, const std::string& msg)
	{
		std::cout << msg << ": " << v[0] << ", " << v[1] << ", " << v[2] << std::endl;
	}

	void Image::CaptureAndWriteImage(const Scene& scene, const std::string& filepath) const
	{
		std::cout << "Writing Image " << filepath << " \n";
		std::ofstream file(filepath);

		if (!file.is_open())
		{
			std::cout << "Failed to open the output file " << filepath << "\n";
		}

		file << "P3\n" << m_Width << " " << m_Height << "\n255\n";
		unsigned int counter = 0;

		for(unsigned int j = 0; j < m_Height; j++)
		{
			for(unsigned int i = 0; i < m_Width; i++)
			{
				double x = (double)i / (double) m_Width;
				double y = (double)j / (double) m_Height;

				Vector position = m_Camera.GetPosition();
				Vector direction = m_Camera.View(x, y);

				Ray theRay{ position, direction };

				Color theColor = Trace(theRay, scene);
            
				int r = (int)(theColor.red() * 255.0);
				int g = (int)(theColor.green() * 255.0);
				int b = (int)(theColor.blue() * 255.0);

				int ir = int(255.99 * std::sqrt(theColor.X()));
				int ig = int(255.99 * std::sqrt(theColor.Y()));
				int ib = int(255.99 * std::sqrt(theColor.Z()));

				if(r > 255) r = 255;
				if(g > 255) g = 255;
				if(b > 255) b = 255;

				file << r << " " << g << " " << b << "\n";
			}
		}
    
		std::cout << "Written to file " << filepath << "\n";

		file.close();
	}

	void Image::CaptureAndWriteImage(const std::vector<Light*>& lights, const TraceTree * theTree, const std::string & filepath) const
	{
		std::cout << "Writing Image " << filepath << " \n";
		std::ofstream file(filepath);

		if (!file.is_open())
		{
			std::cout << "Failed to open the output file " << filepath << "\n";
		}

		file << "P3\n" << m_Width << " " << m_Height << "\n255\n";
		unsigned int counter = 0;

		for (unsigned int j = 0; j < m_Height; j++)
		{
			for (unsigned int i = 0; i < m_Width; i++)
			{
				double x = (double)i / (double)m_Width;
				double y = (double)j / (double)m_Height;

				Vector position = m_Camera.GetPosition();
				Vector direction = m_Camera.View(x, y);

				Ray theRay{ position, direction };
				IntersectionData idata = theTree->intersect(theRay.GetPosition(), theRay.GetDirection());
				
				Color theColor = {};
				
				if (idata.t > 0.0)
				{
					//std::cout << "Hit\n";
					// hit!
					Vector point = theRay.GetPointOnRay(idata.t);

					for (size_t lightI = 0; lightI < lights.size(); lightI++)
					{
						theColor += idata.geom->Shade(point, *lights[lightI]);
					}

				}
				


				int r = (int)(theColor.red() * 255.0);
				int g = (int)(theColor.green() * 255.0);
				int b = (int)(theColor.blue() * 255.0);

				int ir = int(255.99 * std::sqrt(theColor.X()));
				int ig = int(255.99 * std::sqrt(theColor.Y()));
				int ib = int(255.99 * std::sqrt(theColor.Z()));

				if (r > 255) r = 255;
				if (g > 255) g = 255;
				if (b > 255) b = 255;

				file << r << " " << g << " " << b << "\n";
			}
		}

		std::cout << "Written to file " << filepath << "\n";

		file.close();
	}



	void Image::debugrgb()
	{

	}



} // namespace vzl
