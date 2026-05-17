cmake_minimum_required(VERSION 3.10)
project(rime-quickjs)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

option(QJS_ENABLE_INSTALL "" OFF)
option(QJS_BUILD_LIBC "" ON)
set(_rime_quickjs_build_shared_libs ${BUILD_SHARED_LIBS})
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
add_subdirectory(deps/quickjs-ng)
set(BUILD_SHARED_LIBS ${_rime_quickjs_build_shared_libs} CACHE BOOL "" FORCE)

aux_source_directory(src quickjs_src)
aux_source_directory(src/lib quickjs_lib)
aux_source_directory(src/gear quickjs_gear)
aux_source_directory(src/extend quickjs_extend)
aux_source_directory(src/registry quickjs_registry)

add_library(rime-quickjs-objs OBJECT ${quickjs_src} ${quickjs_lib} ${quickjs_gear} ${quickjs_extend} ${quickjs_registry})
target_link_libraries(rime-quickjs-objs PRIVATE qjs)
target_include_directories(rime-quickjs-objs PRIVATE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)
if(BUILD_SHARED_LIBS)
  set_target_properties(rime-quickjs-objs
    PROPERTIES
    POSITION_INDEPENDENT_CODE ON)
endif()

add_library(rime-quickjs-deps INTERFACE)
target_link_libraries(rime-quickjs-deps INTERFACE qjs)

set(plugin_name rime-quickjs PARENT_SCOPE)
set(plugin_objs $<TARGET_OBJECTS:rime-quickjs-objs> PARENT_SCOPE)
set(plugin_deps ${rime_library} rime-quickjs-deps PARENT_SCOPE)
set(plugin_modules "quickjs" PARENT_SCOPE)
