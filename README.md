# Plugin Loader
An open source plugin loader for linux by Ahmed Al-Shoqanebi also known as XenoBino ;-)

## Features
- Loading of a single plugin
- Loading of multiple plugins from a list file

## Compile
#### Requirements
 - make (if you are a beginner in building from source)
 - cmake
 - c++ compiler

to install the requirements simply execute:

    sudo apt install make cmake g++ -y

### Compilation
To compile the library simply execute:

    cd PluginLoader
    make

You will have **Build/libPluginLoader.so** and **include/** inside **PluginLoader/** to use in your projects. Or read the **Installation** section
### Installation
If you wish to install the library execute:

    cd PluginLoader
    make install

## Documentation

The library defines these headers:
- PluginLoader/Plugin.h
  - **class Plugin**: a class that holds one plugin.
      - **Constructor**: Takes a path to dynamic library(plugin).
      - **void Start()**: Takes a (nullable) void * handle to app API and passes it to plugin entry point.
- PluginLoader/PluginLoader.h
  -  class **PluginLoader**: a class that loads a list of plugins from file.
      -  **Constructor**: Takes nothing
      -  **void Load()**: Takes a path to list file (can be called multiple times to load multiple files).
      -  **bool isEmpty()**: returns false if no plugin is loaded (Invalid plugins are counted).
      -  **size(), begin(), end()** which adds support for foreach
      -  **operator[], Get()**: takes an index and returns a **_std::shared_ptr<Plugin>_** if the index is valid.


## Examples
To build and run the example, in the root of the git repo do:

    make
    Build/PluginLoaderTest Test/PluginList.txt

An example of library usage can be found at **test.cpp**.
An example of a plugin can be found at **Test/test.cpp**.

## Notes
The whole project was only tested on **Kali linux WSL 1 Windows 10 1909** and **termux on samsung android 9.0 armv8l**.
Support for windows might be added in the feature. (Windows API is hard :-( ).