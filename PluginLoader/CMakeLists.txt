CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

project(PluginLoader)

include_directories(
	"${PROJECT_SOURCE_DIR}/include"
)

file(GLOB SRCS
	"${PROJECT_SOURCE_DIR}/src/*.cpp"
)

add_compile_options(-D_DEBUG)
add_library(PluginLoader SHARED ${SRCS})
target_link_libraries(PluginLoader dl)
