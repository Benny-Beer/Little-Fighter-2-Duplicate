#include<string>
#include<vector>

class DataLoader {
public:
	DataLoader(std::string pathToIndex);
	void parseDataIndex();
	void printPaths() const;
private:
	std::string m_pathToIndex;
	std::vector<std::string> m_datPaths;
};