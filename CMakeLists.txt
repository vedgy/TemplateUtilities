cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

set(Target_Name TemplateUtilities)
message(<${Target_Name}>)

## vedgTools/CMakeModules path boilerplate.
include(vedgTools/CMakeLicense OPTIONAL RESULT_VARIABLE CMakeModulesWasIncluded)
if(CMakeModulesWasIncluded STREQUAL NOTFOUND)
    set(CMAKE_MODULE_PATH
            "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules")
    message("Including CMakeModules.")
    include(vedgTools/CMakeLicense)
endif()

include(vedgTools/LibraryHeadersOnlyInit)


include_directories(${${Target_Name}_PublicHeaders_Path})


message(</${Target_Name}>)
