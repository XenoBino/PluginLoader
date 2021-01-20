#include "Plugin/Plugin.h"
#include <iostream>
#include <dlfcn.h>

Plugin::Plugin(const char *file) : m_File(file), m_Valid(true) {
	m_Handle = dlopen(file, RTLD_LAZY);

	if (!m_Handle) {
		std::cerr << "Error: " << dlerror() << std::endl;
		m_Valid = false;
	}

	dlerror();

	char *error;
	m_Entry = dlsym(m_Handle, "PluginEntry");
	if ((error = dlerror()) != NULL) {
		std::cerr << file << ": Error: " << error << std::endl;
		m_Valid = false;
	}
}

Plugin::~Plugin() {
	dlclose(m_Handle);
}

const char *Plugin::GetFile() const {
	return m_File.c_str();
}

bool Plugin::isValid() const {
	return m_Valid;
}

void Plugin::Start(void *API_Handle) const {
	if (m_Valid) {
		((void(*)(void *))m_Entry)(API_Handle);
	}
}
