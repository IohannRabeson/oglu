project(loaders)

set(APPLICATION_NAME loaders.app)
set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(SHD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/shaders)
set(MODELS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/models)

set(SRC
    ${SRC_DIR}/main.cpp
)

set(MODEL_SRC
    ${MODELS_DIR}/susan.obj
    ${MODELS_DIR}/susan_smooth.obj
    ${MODELS_DIR}/cube.obj
    ${MODELS_DIR}/susan_color.ply
)

set(SHADER_SRC
    ${SHD_DIR}/loaders.frag
    ${SHD_DIR}/loaders.vert
)

include_directories(${INC_DIR})

set(EXECUTABLE_OUTPUT_PATH ${APPLICATION_OUTPUT_DIR}/examples)
add_definitions(-Wall -Werror -Wextra)
add_executable(${APPLICATION_NAME} ${SRC} ${SHADER_SRC})

set_property(TARGET ${APPLICATION_NAME} PROPERTY CXX_STANDARD 11)
set_property(TARGET ${APPLICATION_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

target_link_libraries(${APPLICATION_NAME} ${OPENGL_gl_LIBRARY} glfw ${GLFW_LIBRARIES} ${GLEW_LIBRARIES} oglu)

if (XCODE OR MSVC)
    set(DESTINATION_SHADER ${EXECUTABLE_OUTPUT_PATH}/${CMAKE_BUILD_TYPE}/shaders)
    set(DESTINATION_MODELS ${EXECUTABLE_OUTPUT_PATH}/${CMAKE_BUILD_TYPE}/models)
else()
    set(DESTINATION_SHADER ${EXECUTABLE_OUTPUT_PATH}/shaders)
    set(DESTINATION_MODELS ${EXECUTABLE_OUTPUT_PATH}/models)
endif()

copy_files(${DESTINATION_SHADER} ${APPLICATION_NAME} "${SHADER_SRC}")
copy_files(${DESTINATION_MODELS} ${APPLICATION_NAME} "${MODEL_SRC}")