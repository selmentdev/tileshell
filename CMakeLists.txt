cmake_minimum_required( VERSION 3.4 )

#include(${CMAKE_BINARY_DIR}/CMakeTools/CMakeToolsHelpers.cmake)

project( graphyte-engine VERSION 1.0.0.0)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#message("-- CMAKE_SYSTEM_INFO_FILE: ${CMAKE_SYSTEM_INFO_FILE}")
#message("-- CMAKE_SYSTEM_NAME:      ${CMAKE_SYSTEM_NAME}")
#message("-- CMAKE_SYSTEM_PROCESSOR: ${CMAKE_SYSTEM_PROCESSOR}")
#message("-- CMAKE_SYSTEM:           ${CMAKE_SYSTEM}")

option(BUILD_SHARED_LIBS "Build Shared Libraries" OFF)

set( LIB_TYPE STATIC )
if( BUILD_SHARED_LIBS )
    set( LIB_TYPE SHARED )
else()
    add_definitions( -DGRAPHYTE_API_LINK_STATIC )
endif()

message("-- building ${LIB_TYPE} libraries")

#
# When on Windows / MSVC
#
if( MSVC )

    add_compile_options(
        /GF                 # Enable string pooling
        /W4                 # Warning level 4
        /std:c++latest      # Latest C++ standard support
        /sdl                # SDL checks
        /MP                 # Multiprocessor compilation
        /Oi                 # Enable intrinsics
        #/arch:SSE2          # SSE2 optimizations (note: disabled for AMD64 by default)
    )

    set( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Ox" )
    set( CMAKE_CXX_FLAGS_RELWITHDEBINFO  "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /Ox" )

    #set( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /LTCG" )
    #set( CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /LTCG" )
endif()

add_definitions( -D__STDC_WANT_LIB_EXT1__=1 )

add_definitions( -D__STDINT_MACROS )
add_definitions( -D__STDINT_LIMITS )
add_definitions( -D__STDC_CONSTANT_MACROS )
add_definitions( -D__STDC_FORMAT_MACROS )
add_definitions( -D__STDC_LIMIT_MACROS )

add_definitions( -DGRAPHYTE_COMPILER_NAME="${CMAKE_CXX_COMPILER_ID}" )
add_definitions( -DGRAPHYTE_BUILD_OS="${CMAKE_SYSTEM}" )
add_definitions( -DGRAPHYTE_BUILD_OS_NAME="${CMAKE_SYSTEM_NAME}" )
add_definitions( -DGRAPHYTE_BUILD_TYPE=CMAKE_BUILD_TYPE )

#
# Detect platform
#
if( WIN32 )
    message("WINDOWS")
    #
    # We target for at least windows8
    #

    add_definitions( -DGRAPHYTE_LITTLE_ENDIAN )

    add_definitions( -DGRAPHYTE_PLATFORM_WINDOWS )
    add_definitions( -DGRAPHYTE_PLATFORM_NAME="Windows" )
    add_definitions( -DGRAPHYTE_PLATFORM_ID="windows" )
    add_definitions( -DGRAPHYTE_PLATFORM_TYPE_DESKTOP )

    add_definitions( -DGRAPHYTE_PLATFORM_TYPE_NAME="Desktop" )
    add_definitions( -DGRAPHYTE_PLATFORM_TYPE_ID="desktop" )

    add_definitions( -DGRAPHYTE_PLATFORM_HAS_FEATURE_EXCEPTIONS )
    add_definitions( -DGRAPHYTE_PLATFORM_HAS_FEATURE_SEH_EXCEPTIONS )
    add_definitions( -DGRAPHYTE_PLATFORM_HAS_FEATURE_CPUID )

    add_definitions( -DGRAPHYTE_PLATFORM_HAS_FEATURE_UNALIGNED_ACCESS )

    add_definitions( -DGRAPHYTE_PLATFORM_HAS_FEATURE_SSE_STREAMING )
    add_definitions( -DGRAPHYTE_PLATFORM_HAS_FEATURE_SSE )
    add_definitions( -DGRAPHYTE_PLATFORM_HAS_FEATURE_SSE2 )
    add_definitions( -DGRAPHYTE_PLATFORM_HAS_FEATURE_SSE3 )
    add_definitions( -DGRAPHYTE_PLATFORM_HAS_FEATURE_SSSE3 )
    add_definitions( -DGRAPHYTE_PLATFORM_HAS_FEATURE_SSE4 )
    add_definitions( -DGRAPHYTE_PLATFORM_HAS_FEATURE_SSE4_1 )
    add_definitions( -DGRAPHYTE_PLATFORM_HAS_FEATURE_SSE4_2 )
    #add_definitions( -DGRAPHYTE_PLATFORM_HAS_FEATURE_SSE5 )
    #add_definitions( -DGRAPHYTE_PLATFORM_HAS_FEATURE_FMA3 )
    #add_definitions( -DGRAPHYTE_PLATFORM_HAS_FEATURE_FMA4 )
    #add_definitions( -DGRAPHYTE_PLATFORM_HAS_FEATURE_F16C )
    #add_definitions( -DGRAPHYTE_PLATFORM_HAS_FEATURE_AVX )
    #add_definitions( -DGRAPHYTE_PLATFORM_HAS_FEATURE_AESNI )
    #add_definitions( -DGRAPHYTE_PLATFORM_HAS_FEATURE_SHA )

    if( MSVC )
        message("MSVC")
        add_definitions( -DGRAPHYTE_PLATFORM_HAS_FEATURE_VECTORCALL )
        add_definitions( -DNTDDI_VERSION=NTDDI_WIN10 )
        add_definitions( -DWINVER=_WIN32_WINNT_WIN10 )
        add_definitions( -D_WIN32_WINNT=_WIN32_WINNT_WIN10 )
    else()
        message("GNU")
        add_definitions( -DNTDDI_VERSION=NTDDI_WIN8 )
        add_definitions( -DWINVER=_WIN32_WINNT_WIN8 )
        add_definitions( -D_WIN32_WINNT=_WIN32_WINNT_WIN8 )
    endif()

elseif( UNIX AND NOT APPLE )
    message("LINUX")

    add_definitions( -DGRAPHYTE_PLATFORM_LINUX )
    add_definitions( -DGRAPHYTE_PLATFORM_POSIX )
    add_definitions( -DGRAPHYTE_PLATFORM_HAS_PTHREADS )

    add_definitions( -DGRAPHYTE_PLATFORM_HAS_FEATURE_SSE )
    add_definitions( -DGRAPHYTE_PLATFORM_HAS_FEATURE_SSE2 )
    add_definitions( -DGRAPHYTE_PLATFORM_HAS_FEATURE_SSE3 )
    add_definitions( -DGRAPHYTE_PLATFORM_HAS_FEATURE_SSSE3 )
    add_definitions( -DGRAPHYTE_PLATFORM_HAS_FEATURE_SSE4 )
    add_definitions( -DGRAPHYTE_PLATFORM_HAS_FEATURE_SSE4_1 )
    add_definitions( -DGRAPHYTE_PLATFORM_HAS_FEATURE_SSE4_2 )
    add_definitions( -DGRAPHYTE_PLATFORM_HAS_FEATURE_SSE_STREAMING )
    
    add_definitions( -DGRAPHYTE_PLATFORM_HAS_FEATURE_UNALIGNED_ACCESS )

elseif( APPLE )
    message("APPLE")
    add_definitions( -DGRAPHYTE_PLATFORM_APPLE )

endif()

if( CMAKE_SIZEOF_VOID_P EQUAL 8 )

    add_definitions( -DGRAPHYTE_SIZEOF_VOID_P=8 )
    add_definitions( -DGRAPHYTE_ARCH_X64 )
    add_definitions( -DGRAPHYTE_ARCH_ID="amd64")

else()

    add_definitions( -DGRAPHYTE_SIZEOF_VOID_P=4 )
    add_definitions( -DGRAPHYTE_ARCH_X86 )
    add_definitions( -DGRAPHYTE_ARCH_ID="x86")

endif()


add_subdirectory( source )

set(
    LIBRARY_OUTPUT_PATH     ${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}
    CACHE PATH              "Library output path"
)

set(
    EXECUTABLE_OUTPUT_PATH  ${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}
    CACHE PATH              "Executable output path"
)
