#include <iostream>
#include "API.h"

extern "C" {
	void PluginEntry(void* API_Handle) {
		std::cout << "I am a test plugin and I am changing value to 8" << std::endl;
		((API*)API_Handle)->SetValue(8);
	}
}
