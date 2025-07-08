#include "Management/DataLoader.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

DataLoader::DataLoader(std::string pathToIndex) : m_pathToIndex(pathToIndex)
{
	parseDataIndex();
}

void DataLoader::parseDataIndex()
{
	std::ifstream file(m_pathToIndex);
	if(!file.is_open()) throw std::runtime_error("Failed to open file: " + m_pathToIndex);

	std::string line, token, type, path;
	//add a if not empty line clause and if path is not empty before adding to vector
	while (std::getline(file, line)) {
		std::stringstream ss(line);
		while (ss >> token) {
			if (token == "type:") ss >> type;
			else if (token == "file:") ss >> path;
		}
		if (type == "character" && !path.empty()) {
			std::cout << path << std::endl;
			m_datPaths.push_back(path);
		}
	}
}

void DataLoader::printPaths() const
{
	for (const std::string& path : m_datPaths) {
		std::cout << path << std::endl;
	}
}
