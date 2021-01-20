CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

project(PluginLoaderTest)

add_subdirectory(PluginLoader)
add_subdirectory(Test)

include_directories(
	"${PROJECT_SOURCE_DIR}/PluginLoader/include"
)

add_executable(PluginLoaderTest test.cpp)
target_link_libraries(PluginLoaderTest PluginLoader)
