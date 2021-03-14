#include "Plugin/PluginLoader.h"

#include <iostream>
#include <fstream>
#include <stdexcept>

PluginLoader::PluginLoader(void *API_Handle) : m_PluginCount(0), m_API_Handle(API_Handle) {}

void PluginLoader::Load(const char *ListFile) {
	m_ListFiles.push_back(ListFile);

	std::fstream file(ListFile);

	if (!file.is_open()) {
		perror(ListFile);
		exit(1);
	}

	std::string Line;

	while (std::getline(file, Line)) {
		if (Line == "")
			continue;

		m_Plugins.push_back(std::make_shared<Plugin>(Line.c_str(), m_API_Handle));
		Line = "";
	}

	file.close();
	m_PluginCount += m_Plugins.size();
}

std::shared_ptr<Plugin> PluginLoader::Get(size_t index) const {
	if (index >= m_Plugins.size())
		throw std::runtime_error("PluginLoader::Get(): Index out of range");
	return m_Plugins[index];
}

std::shared_ptr<Plugin> PluginLoader::operator[](size_t index) const {
	return Get(index);
}

size_t PluginLoader::size() const {
	return m_PluginCount;
}

bool PluginLoader::isEmpty() const {
	if (m_PluginCount == 0)
		return true;
	return false;
}

const std::shared_ptr<Plugin>* PluginLoader::begin() const {
	if (isEmpty())
		throw std::runtime_error("Calling PluginLoader::Begin with no plugins loaded");
	return &m_Plugins[0];
}

const std::shared_ptr<Plugin>* PluginLoader::end() const {
	if (isEmpty())
		throw std::runtime_error("Calling PluginLoader::End with no plugins loaded");
	return &m_Plugins[m_PluginCount];
}
