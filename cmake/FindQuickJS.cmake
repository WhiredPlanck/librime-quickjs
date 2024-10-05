find_path(QUICKJS_INCLUDE_DIR NAMES quickjs/quickjs.h)
find_library(QUICKJS_LIBRARY NAMES quickjs PATH_SUFFIXES quickjs)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(QuickJS
    FOUND_VAR
        QUICKJS_FOUND
    REQUIRED_VARS
        QUICKJS_LIBRARY
        QUICKJS_INCLUDE_DIR
)

if(QUICKJS_FOUND AND NOT TARGET QuickJS::QuickJS)
    add_library(QuickJS::QuickJS UNKNOWN IMPORTED)
    set_target_properties(QuickJS::QuickJS PROPERTIES
        IMPORTED_LOCATION "${QUICKJS_LIBRARY}"
        INTERFACE_INCLUDE_DIRECTORIES "${QUICKJS_INCLUDE_DIR}"
    )
endif()

mark_as_advanced(QUICKJS_INCLUDE_DIR QUICKJS_LIBRARY)
