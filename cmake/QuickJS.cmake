project(quickjs LANGUAGES C)

if(APPLE OR WIN32)
file(RENAME
  "${CMAKE_CURRENT_SOURCE_DIR}/deps/quickjs/VERSION"
  "${CMAKE_CURRENT_SOURCE_DIR}/deps/quickjs/VERSION.txt"
)
set(VERSION_FILE "VERSION.txt")
else()
set(VERSION_FILE "VERSION")
endif()

file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/deps/quickjs/${VERSION_FILE}" QJS_VERSION)

set(QUICKJS_SRC 
    "${CMAKE_CURRENT_SOURCE_DIR}/deps/quickjs/quickjs.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/deps/quickjs/libbf.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/deps/quickjs/libunicode.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/deps/quickjs/libregexp.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/deps/quickjs/cutils.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/deps/quickjs/quickjs-libc.c"
)
set(QUICKJS_DEF CONFIG_VERSION="${QJS_VERSION}" _GNU_SOURCE CONFIG_BIGNUM)

add_library(quickjs ${QUICKJS_SRC})
add_library(QuickJS::QuickJS ALIAS quickjs)
target_compile_definitions(quickjs PRIVATE ${QUICKJS_DEF})
target_include_directories(quickjs INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)
set_target_properties(quickjs PROPERTIES
  INTERPROCEDURAL_OPTIMIZATION TRUE
)

if(UNIX OR MINGW)
  find_package(Threads)
  target_link_libraries(quickjs ${CMAKE_DL_LIBS} m Threads::Threads)
endif()
