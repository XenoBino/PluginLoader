/*

#include <string>
#include <vector>
#include <memory>

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


class PluginLoader {
public:
	PluginLoader();

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

	std::string m_ListFile;
	size_t m_PluginCount;
};
*/

#include "Plugin/PluginLoader.h"
#include <iostream>

void show_usage();

class API {
public:
	void SetValue(unsigned int v) {
		x = v;
	}

	unsigned int GetValue() const {
		return x;
	}
private:
	unsigned int x;
};

int main(int argc, char **argv) {
	if (argc < 2) {
		show_usage();
		return 1;
	}

	unsigned int x = 5;
	API *API_Handle = new API();
	API_Handle->SetValue(x);

	PluginLoader loader;
	loader.Load(argv[1]);

	std::shared_ptr<Plugin> test = loader.Get(0);
	if (!test->isValid()) {
		std::cerr << "Invalid Plugin" << std::endl;
		return 1;
	}


	std::cout << "value before call is " << API_Handle->GetValue() << std::endl;
	test->Start((void*)API_Handle);
	std::cout << "value after call is " << API_Handle->GetValue() << std::endl;

	return 0;
}

void show_usage() {
	fputs("Usage: plugin [LIB_FILE]\n", stderr);
}
