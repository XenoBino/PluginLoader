#!/usr/bin/bash

mkdir -p Build
cmake . -BBuild/
cmake --build Build/
echo -e "Build/PluginLoaderTest" > .type
