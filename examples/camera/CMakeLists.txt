project(camera)

set(APPLICATION_NAME camera.app)
set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(SHD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/shaders)

set(SRC
	${SRC_DIR}/main.cpp
)

set(SHADER_SRC
	${SHD_DIR}/camera.frag
	${SHD_DIR}/camera.vert
)

include_directories(${INC_DIR})

set(EXECUTABLE_OUTPUT_PATH ${APPLICATION_OUTPUT_DIR}/examples)
add_definitions(-Wall -Werror -Wextra)
add_executable(${APPLICATION_NAME} ${SRC})

set_property(TARGET ${APPLICATION_NAME} PROPERTY CXX_STANDARD 11)
set_property(TARGET ${APPLICATION_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

target_link_libraries(${APPLICATION_NAME} ${OPENGL_gl_LIBRARY} glew oglu)

copy_files(${EXECUTABLE_OUTPUT_PATH}/shaders ${APPLICATION_NAME} "${SHADER_SRC}")
