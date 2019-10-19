project(simple_triangle)

set(APPLICATION_NAME simple_triangle.app)
set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(SHD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/shaders)

set(SRC
        ${SRC_DIR}/main.cpp
)

set(SHADER_SRC
        ${SHD_DIR}/simple_triangle.frag
        ${SHD_DIR}/simple_triangle.vert
)

include_directories(${INC_DIR})

set(EXECUTABLE_OUTPUT_PATH ${APPLICATION_OUTPUT_DIR}/examples)
add_definitions(-Wall -Werror -Wextra)
add_executable(${APPLICATION_NAME} ${SRC} ${SHADER_SRC})

set_property(TARGET ${APPLICATION_NAME} PROPERTY CXX_STANDARD 11)
set_property(TARGET ${APPLICATION_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

target_link_libraries(${APPLICATION_NAME} ${OPENGL_gl_LIBRARY} glfw ${GLFW_LIBRARIES} ${GLEW_STATIC_LIBRARIES} oglu)

if (XCODE OR MSVC)
        set(DESTINATION_SHADER ${EXECUTABLE_OUTPUT_PATH}/${CMAKE_BUILD_TYPE}/shaders)
else()
        set(DESTINATION_SHADER ${EXECUTABLE_OUTPUT_PATH}/shaders)
endif()

copy_files(${DESTINATION_SHADER} ${APPLICATION_NAME} "${SHADER_SRC}")
