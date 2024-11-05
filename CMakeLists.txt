cmake_minimum_required(VERSION 3.29)
project(dotenvloader)

# Enable export of compile commands for easier debugging
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Enable ccache for faster builds if available
find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
endif()

# Create a static library for dotenvloader
add_library(${PROJECT_NAME} STATIC
        include/dotenvloader.hpp
        src/dotenvloader.cpp
)

# Macro to set common target properties
macro(set_common_properties target)
    set_target_properties(${target} PROPERTIES
            CXX_STANDARD 20
            CXX_STANDARD_REQUIRED ON
            POSITION_INDEPENDENT_CODE ON
    )
endmacro()

# Set properties for the library
set_common_properties(${PROJECT_NAME})

# Include directories for the library
target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include
)

# Testing configuration
if(BUILD_TESTING)
    # Configure environment file for tests
    set(ENV_FILE_SOURCE ${CMAKE_SOURCE_DIR}/.env)
    set(ENV_FILE_DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/.env)
    if(EXISTS ${ENV_FILE_SOURCE})
        configure_file(${ENV_FILE_SOURCE} ${ENV_FILE_DESTINATION} COPYONLY)
    else()
        message(WARNING "Environment file ${ENV_FILE_SOURCE} not found.")
    endif()

    # Create the test executable
    add_executable(${PROJECT_NAME}_test test.cpp)
    target_link_libraries(${PROJECT_NAME}_test PRIVATE ${PROJECT_NAME})

    # Set properties for the test executable
    set_common_properties(${PROJECT_NAME}_test)
endif()

# Installation configuration
install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}Targets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)

# Install header files
install(DIRECTORY include/
        DESTINATION include
        FILES_MATCHING PATTERN "*.hpp"
)

# Define pkg-config variables
set(PKG_CONFIG_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/lib/pkgconfig)
set(PKG_CONFIG_FILE ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc)

# Create pkg-config file content
file(WRITE ${PKG_CONFIG_FILE} "prefix=${CMAKE_INSTALL_PREFIX}\n")
file(APPEND ${PKG_CONFIG_FILE} "exec_prefix=\${prefix}\n")
file(APPEND ${PKG_CONFIG_FILE} "libdir=\${exec_prefix}/lib\n")
file(APPEND ${PKG_CONFIG_FILE} "includedir=\${prefix}/include\n")
file(APPEND ${PKG_CONFIG_FILE} "Name: ${PROJECT_NAME}\n")
file(APPEND ${PKG_CONFIG_FILE} "Description: A library to load .env files\n")
file(APPEND ${PKG_CONFIG_FILE} "Version: 1.0.0\n")  # Adjust version as necessary
file(APPEND ${PKG_CONFIG_FILE} "Libs: -L\${libdir} -l${PROJECT_NAME}\n")
file(APPEND ${PKG_CONFIG_FILE} "Cflags: -I\${includedir}\n")

# Install pkg-config file
install(FILES ${PKG_CONFIG_FILE}
        DESTINATION ${PKG_CONFIG_INSTALL_DIR}
        RENAME ${PROJECT_NAME}.pc
)
