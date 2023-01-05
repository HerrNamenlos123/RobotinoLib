cmake_minimum_required(VERSION 3.16)

project(RobotinoLib VERSION 1.0.0 LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose Release or Debug" FORCE)
endif()


if (WIN32 AND NOT MSVC)
message(FATAL_ERROR "This library only has MVSC binaries on Windows. Please use Visual Studio.")
endif ()


################
# Dependencies #
################

include(cmake/spdlog.cmake)

if (LINUX)
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
file(GLOB_RECURSE CMAKE_FILES CONFIGURE_DEPENDS "cmake/*")

add_library(${PROJECT_NAME} STATIC ${SRC_FILES} ${HEADER_FILES} ${CMAKE_FILES})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_EXTENSIONS OFF)

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

if (LINUX)
    target_include_directories(${PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/robotinoapi2/linux/include>
        $<INSTALL_INTERFACE:include>
    )
elseif (MSVC)
    target_include_directories(${PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/robotinoapi2/msvc/include>
        $<INSTALL_INTERFACE:include>
    )
endif ()




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
target_link_directories(${PROJECT_NAME} PUBLIC ${CMAKE_INSTALL_PREFIX}/lib)

target_link_libraries(${PROJECT_NAME} spdlog)

if (LINUX)
    target_link_libraries(${PROJECT_NAME} rec_robotino_rpc)
    target_link_libraries(${PROJECT_NAME} rec_rpc)
endif ()

target_link_libraries(${PROJECT_NAME} debug rec_robotino_api2d)
target_link_libraries(${PROJECT_NAME} optimized rec_robotino_api2)



#######
# IDE #
#######

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src" PREFIX "Source Files" FILES ${SRC_FILES})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${HEADER_FILES})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/cmake" PREFIX "cmake" FILES ${CMAKE_FILES})



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

if (LINUX)
    install(
        FILES 
            robotinoapi2/linux/bin/librec_robotino_api2.so
            robotinoapi2/linux/bin/librec_robotino_rpc.so
            robotinoapi2/linux/bin/librec_rpc.so
        DESTINATION bin
    )
    install(
        FILES cmake/RobotinoLib.conf
        DESTINATION /etc/ld.so.conf.d
    )
    install(CODE "execute_process(COMMAND ldconfig)")
elseif (MSVC)
    install(
        FILES
            robotinoapi2/msvc/bin/rec_robotino_api2.dll
            robotinoapi2/msvc/bin/rec_robotino_api2d.dll
            robotinoapi2/msvc/bin/rec_robotino_rpc.dll
            robotinoapi2/msvc/bin/rec_rpc.dll
        DESTINATION bin
    )
    install(
        FILES
            robotinoapi2/msvc/lib/rec_robotino_api2.lib
            robotinoapi2/msvc/lib/rec_robotino_api2d.lib
        DESTINATION lib
    )
endif ()

# Install headers
install(
    DIRECTORY include/
    DESTINATION "include"
    FILES_MATCHING PATTERN "*.h*"
)

if (LINUX)
    install(
        DIRECTORY robotinoapi2/linux/include/
        DESTINATION "include"
        FILES_MATCHING PATTERN "*.h*"
    )
elseif (MSVC)
    install(
        DIRECTORY robotinoapi2/msvc/include/
        DESTINATION "include"
        FILES_MATCHING PATTERN "*.h*"
    )
endif ()

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
