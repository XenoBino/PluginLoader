#pragma once

class Plugin {
public:
	Plugin(const char *file, void *API_Handle);
	~Plugin();

	void Start() const;
	bool isValid() const;

	const char *GetName() const;
	const char *GetSource() const;
	const char *GetVersionString() const;

	short int GetVersion() const;

private:
	char *m_SourceFile;
	bool m_Valid;

	void *m_Handle; // Plugin executable handle
	void *m_API_Handle;

	char *m_Name, *m_VersionString;
	short int m_Version;

private:
	void FillInfo();

private: // Functions
	void *m_OnInit_PROC;	// Executed when the plugin is loaded
	void *m_OnStart_PROC;	// Plugin executable entry point (a.k.a main)
	void *m_OnDestroy_PROC;	// Executed when the plugin is destroyed
};
