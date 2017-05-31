cmake_minimum_required( VERSION 3.4 )

include_directories(${PROJECT_SOURCE_DIR}/source/framework/core.engine/include/)
include_directories(${PROJECT_SOURCE_DIR}/source/apps/app.demo/include/)

file( GLOB_RECURSE APP_DEMO_SOURCES "*.cxx" )
file( GLOB_RECURSE APP_DEMO_HEADERS "*.hxx" )

add_executable(app.demo
    ${APP_DEMO_SOURCES}
    ${APP_DEMO_HEADERS}
)

set_property(
    TARGET
        app.demo
    PROPERTY
        FOLDER "apps"
)

#
# This application shouldn't preallocate console window in Windows.
#
if(WIN32 AND MSVC)
   set_target_properties(app.demo PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")
endif()

target_link_libraries(
    app.demo
    core.engine
)

install(
    TARGETS
        app.demo
    RUNTIME DESTINATION
        ${PROJECT_BINARY_DIR}/bin
)