#pragma once

#include <string>
#include <vector>
#include <memory>

#include "Plugin.h"

class PluginLoader {
public:
	PluginLoader(void *API_Handle);

	void Load(const char *ListFile);
	bool isEmpty() const;

public:
	std::shared_ptr<Plugin> Get(size_t index) const;
	std::shared_ptr<Plugin> operator[](size_t index) const;

	size_t size() const;
	const std::shared_ptr<Plugin>* begin() const;
	const std::shared_ptr<Plugin>* end() const;

private:
	std::vector<std::shared_ptr<Plugin>> m_Plugins;
	std::vector<const char *> m_ListFiles;

	void *m_API_Handle;

	std::string m_ListFile;
	size_t m_PluginCount;
};

