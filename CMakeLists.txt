project(rime-quickjs)
cmake_minimum_required(VERSION 3.10)

aux_source_directory(src quickjs_src)

add_library(rime-quickjs-objs OBJECT ${quickjs_src})
if(BUILD_SHARED_LIBS)
  set_target_properties(rime-quickjs-objs
    PROPERTIES
    POSITION_INDEPENDENT_CODE ON)
endif()

set(plugin_name rime-quickjs PARENT_SCOPE)
set(plugin_objs $<TARGET_OBJECTS:rime-quickjs-objs> PARENT_SCOPE)
set(plugin_deps ${rime_library} PARENT_SCOPE)
set(plugin_modules "quickjs" PARENT_SCOPE)
