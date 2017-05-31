cmake_minimum_required( VERSION 3.4 )

include_directories(${PROJECT_SOURCE_DIR}/source/framework/tileshell/include/)

file( GLOB_RECURSE GRAPHYTE_CORE_SOURCES "*.cxx" )
file( GLOB_RECURSE GRAPHYTE_CORE_HEADERS "*.hxx" )

add_library(tileshell ${LIB_TYPE}
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

set_property(TARGET tileshell PROPERTY FOLDER "framework")
set_property(TARGET tileshell PROPERTY OUTPUT_NAME "tileshell")

if( BUILD_SHARED_LIBS )
    install(TARGETS tileshell RUNTIME DESTINATION ${PROJECT_BINARY_DIR}/bin)
endif()
