#include "Plugin/Plugin.h"

#include <iostream>	// cerr
#include <dlfcn.h>	// dlopen, dlsym

#include <cstdio>	// malloc
#include <cstring>	// memcpy, memset

bool LoadPROC(void *handle, void **proc, const char *name) {
	char *error;
	*proc = dlsym(handle, name);
	if ((error = dlerror()) != NULL) {
		std::cerr << "Error: " << error << std::endl;
		return false;
	}

	return true;
}

Plugin::Plugin(const char *file, void *API_Handle) : m_Valid(true), m_API_Handle(API_Handle) {
	m_Handle = dlopen(file, RTLD_LAZY);

	if (!m_Handle) {
		std::cerr << "Error: " << dlerror() << std::endl;
		m_Valid = false;
	}

	dlerror();

	// Load functions
	m_Valid = (
		LoadPROC(m_Handle, &m_OnInit_PROC, "OnInit") &&
		LoadPROC(m_Handle, &m_OnStart_PROC, "OnStart") &&
		LoadPROC(m_Handle, &m_OnDestroy_PROC, "OnDestroy")/* &&

		LoadPROC(m_Handle, &m_GetName_PROC, "GetName") &&
		LoadPROC(m_Handle, &m_GetVersion_PROC, "GetVersion") &&
		LoadPROC(m_Handle, &m_GetVersionString_PROC, "GetVersionString")*/
	);

	if (m_Valid) {
		// Execute the OnInit Function
		if (((bool(*)(void *))m_OnInit_PROC)(API_Handle)) {
			FillInfo();
		}
		else {
			m_Valid = false;
		}
	}

	size_t NameLength = strlen(file) + 1;
	m_SourceFile = (char *)malloc(NameLength);
	memset(m_SourceFile, 0x00, NameLength);
	memcpy(m_SourceFile, file, NameLength - 1);
}

Plugin::~Plugin() {
	(( void(*)() )m_OnDestroy_PROC) ();
	dlclose(m_Handle);
}

void Plugin::FillInfo() {
	void *tmp;
	if (LoadPROC(m_Handle, &tmp, "GetName"))
		m_Name = ( ( char *(*)() )tmp )();
	else
		m_Valid = false;

	if (LoadPROC(m_Handle, &tmp, "GetVersion"))
		m_Version = ( ( short int(*)() )tmp )();
	else
		m_Valid = false;

	if (LoadPROC(m_Handle, &tmp, "GetVersionString"))
		m_VersionString = ( ( char *(*)() )tmp)();
	else
		m_Valid = false;
}

const char *Plugin::GetName() const {
	return m_Name;
}

const char *Plugin::GetSource() const {
	return m_SourceFile;
}

bool Plugin::isValid() const {
	return m_Valid;
}

void Plugin::Start() const {
	if (m_Valid) {
		(( void(*)(void *) )m_OnStart_PROC) (m_API_Handle); // convert to `void OnStart(void *API)` then execute
	}
}
