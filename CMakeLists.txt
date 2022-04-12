cmake_minimum_required(VERSION 3.16)

project(RobotinoLib VERSION 1.0.0 LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})


################
# Dependencies #
################

find_package(spdlog REQUIRED)

if (NOT WIN32)
    find_package(Qt5 COMPONENTS Core Network Xml REQUIRED)
endif ()



##################################
# Options: Library configuration #
##################################




#############################
# Static library definition #
#############################

file(GLOB_RECURSE HEADER_FILES CONFIGURE_DEPENDS "include/*")
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS "src/*")

add_library(${PROJECT_NAME} STATIC ${SRC_FILES} ${HEADER_FILES})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose Release or Debug" FORCE)
endif()

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/robotinoapi2/linux/include>
    $<INSTALL_INTERFACE:include>
)




############################
# Preprocessor definitions #
############################

if (WIN32)
    target_compile_definitions(${PROJECT_NAME} PRIVATE
       WIN32_LEAN_AND_MEAN      # Prevents Windows.h from adding unnecessary includes
       NOMINMAX                 # Prevents Windows.h from defining min/max as macros 
       _CRT_SECURE_NO_WARNINGS
    )
endif()





###########
# Linking #
###########

target_link_directories(${PROJECT_NAME} PUBLIC ${CMAKE_INSTALL_PREFIX}/bin)

target_link_libraries(${PROJECT_NAME} spdlog::spdlog)
target_link_libraries(${PROJECT_NAME} rec_robotino_api2)
target_link_libraries(${PROJECT_NAME} rec_robotino_rpc)
target_link_libraries(${PROJECT_NAME} rec_rpc)



#######
# IDE #
#######

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src" PREFIX "Source Files" FILES ${SRC_FILES})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${HEADER_FILES})



###########
# Install #
###########

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${PROJECT_NAME}ConfigVersion.cmake
    VERSION ${PACKAGE_VERSION}
    COMPATIBILITY AnyNewerVersion
)

# Install binaries
install(
    TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Targets
    LIBRARY DESTINATION "lib"
    ARCHIVE DESTINATION "lib"
    RUNTIME DESTINATION "bin"
    INCLUDES DESTINATION "include"
)

install(
    FILES 
        robotinoapi2/linux/bin/librec_robotino_api2.so
        robotinoapi2/linux/bin/librec_robotino_rpc.so
        robotinoapi2/linux/bin/librec_rpc.so
    DESTINATION bin
)

if (NOT WIN32)
    install(
        FILES cmake/RobotinoLib.conf
        DESTINATION /etc/ld.so.conf.d
    )
    install(CODE "execute_process(COMMAND ldconfig)")
endif ()

# Install headers
install(
    DIRECTORY include/
    DESTINATION "include"
    FILES_MATCHING PATTERN "*.h*"
)

install(
    DIRECTORY robotinoapi2/linux/include/
    DESTINATION "include"
    FILES_MATCHING PATTERN "*.h*"
)

install(
    EXPORT ${PROJECT_NAME}Targets 
    DESTINATION "lib/cmake/${PROJECT_NAME}"
    NAMESPACE ${PROJECT_NAME}::
)

# Install Targets
configure_file(cmake/${PROJECT_NAME}Config.cmake.in ${PROJECT_NAME}Config.cmake @ONLY)
install(
    FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
          "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION lib/cmake/${PROJECT_NAME}
)

# Set default install path on windows
if (WIN32)
    if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
        set (CMAKE_INSTALL_PREFIX "C:/dev" CACHE PATH "default install path" FORCE)
    endif ()
endif ()

