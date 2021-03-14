#pragma once

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
