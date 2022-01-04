#define _CRT_OBSOLETE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <algorithm>
#include "Date.h"
#include "Camera.h"
#include "Image.h"
#include "Sphere.h"
#include "Scene.h"
#include "Plane.h"
#include "Triangle.h"
#include "ObjLoader.h"
#include "TraceTree.h"

static void PrintVector(const std::string& msg = "", const vzl::Vector& vec = {})
{
	std::cout << msg << vec.X() << ", " << vec.Y() << ", " << vec.Z() << std::endl;
}

static const std::string GetDateTime()
{
	auto start = std::chrono::system_clock::now();
	auto end = std::chrono::system_clock::now();

	std::chrono::duration<double> elapsed_seconds = end - start;
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);

	std::string datetime = std::ctime(&end_time);
	datetime.erase(datetime.end() - 1);

	std::replace(datetime.begin(), datetime.end(), ':', '_');
	std::replace(datetime.begin(), datetime.end(), ' ', '_');
	return datetime;
}

int main()
{
	vzl::ObjLoader loader{ "res/mesh.obj", { 1.0, 0.0, 0.0, 1.0 } };

	if (loader.triangleList.size() == 0)
	{
		std::cout << "No triangle!" << std::endl;
		return -1;
	}

	vzl::AABB aabb = loader.triangleList[0].aabb();

	for (size_t i = 1; i < loader.triangleList.size(); i++)
	{
		aabb = aabb.Union(loader.triangleList[i].aabb());
	}
	
	vzl::TraceTree myTraceTree = { aabb.LLC(), aabb.URC(), 1, 20, 1 };
	
	for (size_t i = 0; i < loader.triangleList.size(); i++)
	{
		vzl::ThingToHit* ttoh = dynamic_cast<vzl::ThingToHit*>(&loader.triangleList[i]);
		if (!ttoh)
		{
			std::cout << "Failed to cast\n";
			return -1;
		}
		myTraceTree.addObject(ttoh);
	}

	myTraceTree.Divide();

	vzl::Light light1{ { -3.0, -1.0, 2.0 }, { 1.0, 1.0, 1.0, 1.0 } };

	unsigned int d = 1;
	vzl::Image img{ 1920/d, 1080/d };
	vzl::CameraSetting camset = img.GetCameraSetting();
	camset.aspectRatio = img.GetAspectRatio();
	camset.position = { 0.0, 0.0 , -10.0 };
	img.SetupCamera(camset);

	vzl::Scene theScene;
	theScene.AddLight(&light1);
	
	theScene.AddObject(&myTraceTree);
	
	vzl::Sphere aSphere{ { 1.1, 1.25, 7.0 }, 1.0, {0.5, 0.5, 1.0, 1.0} };
	vzl::Sphere aSphere2{ { -1.1, -1.25, 6.0 }, 1.2, {0.0, 1.0, 1.0, 1.0} };
	vzl::Sphere aSphere3{ { 3.1, -1.25, 6.0 }, 1.5, {0.2, 0.4, 1.0, 1.0} };
	vzl::Sphere aSphere4{ { 6.1, 1.25, 5.0 }, 1.5, {0.2, 0.4, 1.0, 1.0} };
	
	theScene.AddObject(&aSphere);
	theScene.AddObject(&aSphere2);
	theScene.AddObject(&aSphere3);
	theScene.AddObject(&aSphere4);

	//
	std::string foldername = "res/outputimg/"; 
	std::string appendname = "test";
	std::string filename = foldername + GetDateTime() + "_" + appendname + ".ppm";
	vzl::Color backgroundColor{ 0.2, 0.22, 0.1, 1.0 };
	img.CaptureAndWriteImage(theScene, filename, backgroundColor);

	return 0;
}

int main2()
{
	/*objects*/
	vzl::Sphere aSphere{ { 1.1, 1.25, 7. }, 1.0, {0.5, 0.5, 1.0, 1.0} };

	vzl::Plane plane0{ {0., -1., 0.}, {0., 2., 0.}, {1., 1., 1., 1.} };
	vzl::Plane plane1{ {0., 1., 0.}, {0., -2., 0.}, {1., 1., 1., 1.} };
	vzl::Plane plane2{ {1., 0., 0.}, {-2., 0.0, 0.0}, {1., 0., 0., 1.} };
	vzl::Plane plane3{ {-1., 0., 0.}, {2., 0.0, 0.0}, {0., 1., 0., 1.} };
	vzl::Plane plane4{ {0., 0., -1.}, {0.0, 0.0, 10.0}, {1., 1., 1., 1.} };

	vzl::Triangle triangle0{ {-1.8, 0.9, 5.0}, {-1.5, 0.6, 5.0}, {-1.7, 0.4, 5.0}, {245. / 255., 102. / 255., 0., 1.} };
	vzl::Triangle triangle1{ {-1.7, 0.4, 5.0},  {-1.8, 0.9, 5.0}, {1.1, 3.25, 3.0}, {245. / 255., 102. / 255., 0., 1.} };
	vzl::Triangle triangle2{ {1.1, 3.25, 3.0}, {-1.7, 0.4, 5.0}, {-1.5, 0.6, 5.0}, {0., 245. / 255., 102. / 255., 1.} };
	vzl::Triangle triangle3{ {1.1, 3.25, 3.}, {-1.5, 0.6, 5.}, {-1.8, 0.9, 5.}, {102. / 255., 0., 245. / 255., 1.} };

	/*lights*/
	vzl::Light light1{ { -1.0, -1.0, 7.0 }, { 1.0, 1.0, 1.0, 1.0 } };
	vzl::Scene theScene;

	theScene.AddObject(&aSphere);

	theScene.AddObject(&plane0);
	theScene.AddObject(&plane1);
	theScene.AddObject(&plane2);
	theScene.AddObject(&plane3);
	theScene.AddObject(&plane4);

	theScene.AddObject(&triangle0);
	theScene.AddObject(&triangle1);
	theScene.AddObject(&triangle2);
	theScene.AddObject(&triangle3);

	theScene.AddLight(&light1);

	std::cout << "Added things" << "\n";

	unsigned int d = 1;
	vzl::Image img{ 1024 / d, 768 / d };
	img.CaptureAndWriteImage(theScene, "lal.ppm");


	std::cin.get();
	return 0;
}