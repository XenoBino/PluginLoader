#include "Plugin/Plugin.h"

#include <iostream>	// cerr
#include <dlfcn.h>	// dlopen, dlsym

#include <cstdio>	// malloc
#include <cstring>	// memcpy, memset

// ProcTypes
#define XENOPL_INIT_PROC                (bool(*)(void *))
#define XENOPL_START_PROC               (void(*)(void *))
#define XENOPL_DESTROY_PROC             (void(*)())
#define XENOPL_GETNAME_PROC             (char *(*)())
#define XENOPL_GETVERSION_PROC          (short int(*)())
#define XENOPL_GETVERSIONSTRING_PROC    (char *(*)())

#define XENOPL_EXEC(type, proc, ...) ((type)proc)(__VA_ARGS__))

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
	// Copy the name
	size_t NameLength = strlen(file) + 1;
	m_SourceFile = (char *)malloc(NameLength);
	memset(m_SourceFile, 0x00, NameLength);
	strncpy(m_SourceFile, file, NameLength - 1);

	// Open the library
	m_Handle = dlopen(file, RTLD_LAZY);

	if (!m_Handle) {
		std::cerr << "Error: " << dlerror() << std::endl;
		m_Valid = false;
		return;
	}

//	dlerror();

	// Load and check for errors
	if (!(LoadPROC(m_Handle, &m_OnInit_PROC, "OnInit") &&
		LoadPROC(m_Handle, &m_OnStart_PROC, "OnStart") &&
		LoadPROC(m_Handle, &m_OnDestroy_PROC, "OnDestroy")
	)) return;


	// Execute the OnInit Function
	// ((bool(*)(void *))m_OnInit_PROC)(API_Handle))
	if (XENOPL_EXEC((XENOPL_INIT_PROC), m_OnInit_PROC, API_Handle))
		FillInfo();
	else
		m_Valid = false;
}

Plugin::~Plugin() {
//	(( void(*)() )m_OnDestroy_PROC) ();
	XENOPL_EXEC(XENOPL_DESTROY_PROC, m_OnDestroy_PROC);
	dlclose(m_Handle);
}

void Plugin::FillInfo() {
	void *tmp;

	// Get plugin name
	if (LoadPROC(m_Handle, &tmp, "GetName"))
		m_Name = XENOPL_EXEC(XENOPL_GETNAME_PROC, tmp);
	else
		m_Valid = false;

	// Get plugin version
	if (LoadPROC(m_Handle, &tmp, "GetVersion"))
		m_Version = XENOPL_EXEC(XENOPL_GETNAME_PROC, tmp);
	else
		m_Valid = false;

	// Get plugin version string
	if (LoadPROC(m_Handle, &tmp, "GetVersionString"))
		m_VersionString = XENOPL_EXEC(XENOPL_GETVERSIONSTRING_PROC, tmp);
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
	if (m_Valid)
		XENOPL_EXEC(XENOPL_START_PROC, m_OnStart_PROC, m_API_Handle);
}
