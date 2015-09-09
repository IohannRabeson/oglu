find_package(Boost 1.55 REQUIRED COMPONENTS system unit_test_framework)

include_directories(include ${Boost_INCLUDE_DIR})

set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(TESTED_INC ${CMAKE_CURRENT_SOURCE_DIR}/../include)
set(TESTED_SRC ${CMAKE_CURRENT_SOURCE_DIR}/../src)

set(SRC
	${SRC_DIR}/main.cpp
)

# Put here hpp and cpp tested
set(SRC_TESTED
)

# Put here your hpp and cpp of tests
set(SRC_TEST
)

set(EXECUTABLE_OUTPUT_PATH ${APPLICATION_OUTPUT_DIR}/tests)

enable_testing()

foreach(SRC_FILE ${SRC_TEST})
        #Extract the filename without extension (NAME_WE)
        get_filename_component(TEST_NAME ${SRC_FILE} NAME_WE)

        add_executable(${TEST_NAME} ${SRC_FILE} ${SRC_TESTED} ${SRC})
		set_property(TARGET ${TEST_NAME} PROPERTY CXX_STANDARD 11)
		set_property(TARGET ${TEST_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

        #link to Boost libraries and other targets and dependencies
        target_link_libraries(${TEST_NAME} ${Boost_LIBRARIES})
		target_link_libraries(${TEST_NAME} oglu)

		#Finally add it to test execution - 
        #Notice the WORKING_DIRECTORY and COMMAND
        add_test(NAME ${TEST_NAME} 
                 WORKING_DIRECTORY ${EXECUTABLE_OUTPUT_PATH} 
                 COMMAND ${TEST_NAME}
        )
endforeach(SRC_FILE)
