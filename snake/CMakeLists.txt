file(GLOB_RECURSE Sources "*.h" "*.cpp")
add_executable(Snake ${Sources})

target_link_libraries(Snake SRE ${SGE_LIBRARIES})

# Copy project data to output path
file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

IF (WIN32)
	## Copy dll's to output path
	file(COPY ${SGE_LIBRARIES_SHARED} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

ENDIF(WIN32)
