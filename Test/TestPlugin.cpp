#include <iostream>
#include "API.h"

void *API_Handle;

extern "C" {
	short int GetVersion() {
		return 100;
	}

	const char *GetName() {
		return "Test Plugin";
	}

	const char *GetVersionString() {
		return "1.0.0";
	}

	bool OnInit(void* l_API_Handle) {
		std::cout << "Hello, World!" << std::endl;
		API_Handle = l_API_Handle;
		return true;
	}

	void OnStart() {
		std::cout << "I am a test plugin and I am changing value to 8" << std::endl;
		((API*)API_Handle)->SetValue(8);
	}

	void OnDestroy() {
		std::cout << "Goodbye!" << std::endl;
	}
}
