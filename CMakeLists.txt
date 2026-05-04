cmake_minimum_required(VERSION 3.10)
project(rime-quickjs)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

include(QuickJS)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

aux_source_directory(src quickjs_src)
aux_source_directory(src/lib quickjs_lib)
aux_source_directory(src/gear quickjs_gear)
aux_source_directory(src/extend quickjs_extend)
aux_source_directory(src/registry quickjs_registry)

add_library(rime-quickjs-objs OBJECT ${quickjs_src} ${quickjs_lib} ${quickjs_gear} ${quickjs_extend} ${quickjs_registry})
target_link_libraries(rime-quickjs-objs PRIVATE QuickJS::QuickJS)
target_include_directories(rime-quickjs-objs PRIVATE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)
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
