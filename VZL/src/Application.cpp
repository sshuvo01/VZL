#include <iostream>
#include <fstream>
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

int main()
{
	vzl::ObjLoader loader{ "res/mesh.obj", { 1.0, 0.0, 0.0, 1.0 } };
	vzl::Triangle triangle0{ {-1.8, 0.9, 5.0}, {-1.5, 0.6, 5.0}, {-1.7, 0.4, 5.0}, {245. / 255., 102. / 255., 0., 1.} };

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

	vzl::Light light1{ { -1.0, -1.0, 7.0 }, { 1.0, 1.0, 1.0, 1.0 } };
	std::vector<vzl::Light*> lights;
	lights.push_back(&light1);

	unsigned int d = 2;
	vzl::Image img{ 1920/d, 1080/d };
	vzl::CameraSetting camset = img.GetCameraSetting();
	camset.position = { 0.0, 0.0 , -10.0 };
	img.SetupCamera(camset);

	img.CaptureAndWriteImage(lights, &myTraceTree, "tree4.ppm");

	//PrintVector("LLC: ", aabb.LLC());
	//PrintVector("URC: ", aabb.URC());

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
	img.CaptureAndWriteImage(theScene, "output.ppm");


	std::cin.get();
	return 0;
}