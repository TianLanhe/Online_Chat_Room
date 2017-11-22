#ifndef DEFAULT_CONFIGURE_READER_HPP
#define DEFAULT_CONFIGURE_READER_HPP

#include "ConfigureReader.hpp"
#include <map>

#define conver(type,name) type _conv##name(const std::string&)

class DefaultConfigureReader : public ConfigureReader {
public:
	DefaultConfigureReader(const std::string& str = std::string()) :m_file(str) { _updateMap(); }
	~DefaultConfigureReader() {}

	std::string GetConfigureFile() { return m_file; }
	void SetConfigureFile(const std::string& file) {
		m_file = file;
		m_map.clear();
		_updateMap();
	}

	bool Contains(const std::string& key) { return m_map.find(key) != m_map.end(); }

	funcget(int, Int);
	funcget(double, Double);
	funcget(std::string, String);
	funcget(bool, Bool);

	funcget(std::vector<int>, VectorInt);
	funcget(std::vector<double>, VectorDouble);
	funcget(std::vector<std::string>, VectorString);

private:
	void _updateMap();
	void _removeComment(std::string&);
	void _trim(std::string&);
	std::vector<std::string> _split(const std::string&);

	conver(int, Int);
	conver(double, Double);

	std::string m_file;
	std::map<std::string, std::string> m_map;
};

#endif
