#include <iostream>

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

extern "C" {
	void PluginEntry(void* API_Handle) {
		std::cout << "I am a test plugin and I am changing value to 8" << std::endl;
		((API*)API_Handle)->SetValue(8);
	}
}
