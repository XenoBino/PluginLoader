
# Variables for installation
INCLUDE_DIR=/usr/include/
LIB_DIR=/usr/lib/

all:
	@mkdir -p Build
	cmake . -BBuild/
	cmake --build Build/

clean:
	rm -rf Build/*

install: all
	sudo cp -r include/Plugin ${INCLUDE_DIR}
	sudo cp Build/libPluginLoader.so ${LIB_DIR}
