cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

set(Target_Name TemplateUtilities)
message(<${Target_Name}>)

## vedgTools/CMakeModules path boilerplate.
include(vedgTools/CMakeLicense OPTIONAL RESULT_VARIABLE CMakeModulesWasIncluded)
if(CMakeModulesWasIncluded STREQUAL NOTFOUND)
    set(PATH_TO_CMAKE_MODULES ${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules)
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PATH_TO_CMAKE_MODULES})
    message("Including CMakeModules.")
    include(vedgTools/CMakeLicense)
endif()

include(vedgTools/LibraryHeadersOnlyInit)


include_directories(${${Target_Name}_PublicHeaders_Path})


include(vedgTools/FindQtForTesting)
if(ENABLE_TESTING)
    include(vedgTools/EnableAutomoc)
    include_directories(${PATH_TO_CMAKE_MODULES}/include)

    include(vedgTools/LibraryAddTest)
    libraryAddTest("ReserveTest" test/ReserveTest.cpp "")
    libraryAddTest("ResizeTest" test/ResizeTest.cpp "")
endif()


message(</${Target_Name}>)
