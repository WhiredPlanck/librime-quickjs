project(rime-quickjs)
cmake_minimum_required(VERSION 3.10)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

find_package(QuickJS REQUIRED)

aux_source_directory(src quickjs_src)

add_library(rime-quickjs-objs OBJECT ${quickjs_src})
if(BUILD_SHARED_LIBS)
  set_target_properties(rime-quickjs-objs
    PROPERTIES
    POSITION_INDEPENDENT_CODE ON)
endif()

add_library(rime-quickjs-deps INTERFACE)
target_link_libraries(rime-quickjs-deps INTERFACE QuickJS::QuickJS)

set(plugin_name rime-quickjs PARENT_SCOPE)
set(plugin_objs $<TARGET_OBJECTS:rime-quickjs-objs> PARENT_SCOPE)
set(plugin_deps ${rime_library} rime-quickjs-deps PARENT_SCOPE)
set(plugin_modules "quickjs" PARENT_SCOPE)
