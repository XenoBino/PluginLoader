
.PHONY: all clean

all:
	@mkdir -p Build
	cmake . -BBuild/
	cmake --build Build/
	@echo -e "Build/PluginTest" > .type

clean:
	rm -rf Build/*
