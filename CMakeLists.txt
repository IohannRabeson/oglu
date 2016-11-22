#
# Main CMakeLists.txt of project Oglu.
#
cmake_minimum_required (VERSION 3.3)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/CreateOption.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/CopyFiles.cmake)

# Options
create_option(BOOL BUILD_DOCUMENTATION TRUE "Defines if the documentation is generated")
create_option(BOOL BUILD_TESTING TRUE "Defines if the tests are generated")
create_option(BOOL BUILD_EXAMPLES TRUE "Defines if the examples are generated")
create_option(STRING CMAKE_BUILD_TYPE "Debug" "Choose the build mode")
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS Release Debug)

project(oglu CXX)

include(CTest)

add_subdirectory(external)

# packages
find_package(OpenGL REQUIRED)
find_package(Glew REQUIRED)

# Controls
set(APPLICATION_NAME ${CMAKE_PROJECT_NAME})
set(CONF_APPLICATION_DISPLAY_NAME "Oglu")
set(CONF_APPLICATION_VERSION_MAJOR "0")
set(CONF_APPLICATION_VERSION_MINOR "0")
set(CONF_APPLICATION_VERSION_PATCH "0")
set(CONF_APPLICATION_VERSION "${CONF_APPLICATION_VERSION_MAJOR}.${CONF_APPLICATION_VERSION_MINOR}.${CONF_APPLICATION_VERSION_PATCH}")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/)
set(EXECUTABLE_OUTPUT_PATH output)
set(APPLICATION_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/output)
set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/Oglu)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/Oglu)

# Sources
set(SRC
    ${INC_DIR}/OpenGl/OpenGL.hpp
    ${INC_DIR}/OpenGl/OpenGlError.hpp
    ${INC_DIR}/OpenGl/OpenGlTypeTraits.hpp

    ${INC_DIR}/Generics/StrongInteger.hpp
    ${INC_DIR}/Generics/Type.hpp
    ${INC_DIR}/Generics/TypeList.hpp
    ${INC_DIR}/Generics/LazyCast.hpp

    ${INC_DIR}/Parsers/RadixTree.hpp
    ${INC_DIR}/Parsers/RadixTree.hxx
    ${INC_DIR}/Parsers/Parsers.hpp
    ${INC_DIR}/Parsers/Parsers.cpp

    ${INC_DIR}/Graphics/RgbaColor.hpp
    ${INC_DIR}/Graphics/Shader.hpp
    ${INC_DIR}/Graphics/AShaderLoader.hpp
    ${INC_DIR}/Graphics/Shader.hxx
    ${INC_DIR}/Graphics/ShaderCompilationException.hpp
    ${INC_DIR}/Graphics/Program.hpp
    ${INC_DIR}/Graphics/Program.hxx
    ${INC_DIR}/Graphics/ProgramLinkException.hpp
    ${INC_DIR}/Graphics/Camera.hpp
    ${INC_DIR}/Graphics/Mesh.hpp
    ${INC_DIR}/Graphics/Mesh.hxx
    ${INC_DIR}/Graphics/ObjMeshLoader.hpp
    ${INC_DIR}/Graphics/Transform.hpp

    ${INC_DIR}/Window/ContextSettings.hpp
    ${INC_DIR}/Window/Window.hpp
    ${INC_DIR}/Window/IKeyboardListener.hpp
    ${INC_DIR}/Window/IWindowListener.hpp

    ${SRC_DIR}/Graphics/RgbaColor.cpp
    ${SRC_DIR}/Graphics/Program.cpp
    ${SRC_DIR}/Graphics/AShaderLoader.cpp
    ${SRC_DIR}/Graphics/ShaderCompilationException.cpp
    ${SRC_DIR}/Graphics/ProgramLinkException.cpp
    ${SRC_DIR}/Graphics/Camera.cpp
    ${SRC_DIR}/Graphics/Transform.cpp
    ${SRC_DIR}/Graphics/ObjMeshLoader.cpp

    ${SRC_DIR}/Window/Window.cpp
    ${SRC_DIR}/Window/IKeyboardListener.cpp
    ${SRC_DIR}/Window/IWindowListener.cpp
    ${SRC_DIR}/Window/ContextSettings.cpp
)

# Includes
include_directories(include)
include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${GLEW_INCLUDE_DIRS})
include_directories(external/glm/)
include_directories(external/glfw/include)

# Defines
add_definitions(-Wextra -Werror -Wall)

# Build
add_library(${CMAKE_PROJECT_NAME} ${SRC})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_auto_type)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_constexpr)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_decltype)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_decltype_auto)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_decltype_incomplete_return_types)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_default_function_template_args)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_defaulted_functions)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_defaulted_move_initializers)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_delegating_constructors)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_deleted_functions)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_final)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_inheriting_constructors)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_lambdas)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_nullptr)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_range_for)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_rvalue_references)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_static_assert)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_strong_enums)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_template_template_parameters)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_variadic_templates)

target_link_libraries(${APPLICATION_NAME}
                      ${OPENGL_gl_LIBRARIES}
                      ${GLFW_LIBRARIES}
                      ${GLEW_LIBRARIES}
                      glfw)

if (BUILD_ALL OR BUILD_DOCUMENTATION)
        add_subdirectory(doc)
endif()

if (BUILD_ALL OR BUILD_TESTING)
        add_subdirectory(tests)
endif()

if (BUILD_ALL OR BUILD_EXAMPLES)
        add_subdirectory(examples)
endif()
