#include "ObjLoader.h"
#include <fstream>
#include <iostream>

namespace vzl
{
	ObjLoader::ObjLoader(const std::string & filename, const Color & triangleColor)
		:m_Filename(filename), m_Color(triangleColor)
	{
		LoadObj();
	}

	ObjLoader::~ObjLoader()
	{

	}

	void ObjLoader::LoadObj()
	{
		std::vector<Vector> vertices;

		std::ifstream stream(m_Filename);
		std::string line;
		std::vector<std::string> wordVec;
		if (!stream.is_open())
		{
			std::cout << "Could not open " << m_Filename << std::endl;
			return;
		}

		std::cout << "Reading from " << m_Filename << std::endl;

		while (std::getline(stream, line))
		{
			if (line.size() != 0 && line[0] == '#') continue;
			if (line.find("v") != std::string::npos)
			{
				if (!(line[0] == 'v' && line[1] == ' ')) continue;
				// a vertex
				wordVec = GetWords(line);

				float x = std::stod(wordVec[1]);
				float y = std::stod(wordVec[2]);
				float z = std::stod(wordVec[3]);

				vertices.push_back(Vector(x, y, z));
			}
			else if (line.find("f") != std::string::npos)
			{
				if (!(line[0] == 'f' && line[1] == ' ')) continue;
				// a face is separated by '/'
				wordVec = GetWords(line);

				int idx[4];
				for (int i = 1; i <= 3; i++)
				{
					std::string indexString = wordVec[i];
					idx[i] = GetIndices(indexString)[0];
				}
				triangleList.push_back({ vertices[idx[1] - 1], vertices[idx[2] - 1], vertices[idx[3] - 1], m_Color });
			}
		}

		for (int i = 0; i < triangleList.size(); i++)
		{
			triangleList[i].PrintInfo();
			std::cout << std::endl;
		}

		std::cout << "Number of vertices: " << vertices.size() << std::endl;
		std::cout << "Number of triangles: " << triangleList.size() << std::endl;
		stream.close();
	}

	std::vector<int> ObjLoader::GetIndices(const std::string& word) const
	{
		std::vector<int> indices;
		std::string s = word;
		std::string delimiter = "/";

		size_t pos = 0;
		std::string token;
		while ((pos = s.find(delimiter)) != std::string::npos)
		{
			token = s.substr(0, pos);
			//std::cout << token << std::endl;
			indices.push_back(std::stoi(token));
			s.erase(0, pos + delimiter.length());
		}

		//std::cout << s << std::endl;
		return indices;
	}

	std::vector<std::string> ObjLoader::GetWords(const std::string& line) const
	{
		std::string word = "";
		std::vector<std::string> wordVec;

		for (char ch : line)
		{
			if (ch == ' ' && word != "")
			{
				wordVec.push_back(word);
				word = "";
				continue;
			}
			if (ch != ' ') word += ch;
		}
		if (word != "") wordVec.push_back(word);

		return wordVec;
	}
}