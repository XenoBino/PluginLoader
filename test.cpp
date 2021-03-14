#include <iostream>

#include "Plugin/PluginLoader.h"
#include "Test/API.h"

void show_usage();

int main(int argc, char **argv) {
	if (argc < 2) {
		show_usage();
		return 1;
	}

	unsigned int x = 5;
	API *API_Handle = new API();
	API_Handle->SetValue(x);

	PluginLoader loader((void *)API_Handle);
	loader.Load(argv[1]);

	std::shared_ptr<Plugin> test = loader.Get(0);
	if (!test->isValid()) {
		std::cerr << "Invalid Plugin" << std::endl;
		return 1;
	}


	std::cout << "value before call is " << API_Handle->GetValue() << std::endl;
	test->Start();
	std::cout << "value after call is " << API_Handle->GetValue() << std::endl;

	return 0;
}

void show_usage() {
	fputs("Usage: plugin [LIB_FILE]\n", stderr);
}
