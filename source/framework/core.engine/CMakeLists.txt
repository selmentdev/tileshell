cmake_minimum_required( VERSION 3.4 )

include_directories(${PROJECT_SOURCE_DIR}/source/framework/core.engine/include/)

file( GLOB_RECURSE GRAPHYTE_CORE_SOURCES "*.cxx" )
file( GLOB_RECURSE GRAPHYTE_CORE_HEADERS "*.hxx" )

add_library(core.engine ${LIB_TYPE}
    ${GRAPHYTE_CORE_SOURCES}
    ${GRAPHYTE_CORE_HEADERS}
)

if (WIN32)
    if (BUILD_SHARED_LIBS)
        target_link_libraries(
            ntdll
            dbghelp
            iphlpapi
            ws2_32
        )
    endif()
endif()

set_property(TARGET core.engine PROPERTY FOLDER "framework")
set_property(TARGET core.engine PROPERTY OUTPUT_NAME "core.engine")

if( BUILD_SHARED_LIBS )
    install(TARGETS core.engine RUNTIME DESTINATION ${PROJECT_BINARY_DIR}/bin)
endif()
