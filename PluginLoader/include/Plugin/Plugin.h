#pragma once

#include <string>

class Plugin {
public:
	Plugin(const char *file);
	~Plugin();

	void Start(void *API_Handle) const;
	bool isValid() const;
	const char *GetFile() const;
private:
	void *m_Handle;
	void *m_Entry;

	bool m_Valid;
	std::string m_File;
};
