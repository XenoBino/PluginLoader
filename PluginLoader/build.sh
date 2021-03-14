#!/usr/bin/bash

(mkdir -p Build/) && (cmake . -BBuild/ > /dev/null)\
&& (cmake --build Build/ > /dev/null) &&\
echo -e "\e[32mSuccefully built \e[33mPluginLoader \e[32min \e[33mBuild/libPluginLoader.so\e[0m" && \
exit 0

echo -e "\e[31mError: \e[0mFailed to build \e[33mPluginLoader\e[0m"
exit 1
