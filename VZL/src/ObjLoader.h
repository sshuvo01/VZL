#ifndef _VZL_OBJLOADER_H_
#define _VZL_OBJLOADER_H_
#include "Triangle.h"
#include <vector>
#include <string>

namespace vzl
{
	class ObjLoader
	{
	public:
		ObjLoader() = delete;
		ObjLoader(const std::string& filename, const Color& triangleColor = {});
		~ObjLoader();

		std::vector<Triangle> triangleList;
	private:
		std::string m_Filename;
		Color       m_Color;
		/*private functions*/
		void LoadObj();
		std::vector<std::string> GetWords(const std::string& line) const;
		std::vector<int> GetIndices(const std::string& word) const;
	};
}

#endif // !_VZL_OBJLOADER_H_
