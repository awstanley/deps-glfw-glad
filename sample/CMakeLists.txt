# Sample project
PROJECT(deps_glfw_glad_sample C)

# We have the values from the parent scope; if the project in question
# loads in the main library it gets the variables below from PARENT_SCOPE
# settings at the end of the primary CMakeLists.txt.

# Sadly we need to use the intermediary includes because
# the copy happens *after* glad builds.
INCLUDE_DIRECTORIES(
	"${GLFW_DIRECTORY}/include"
	"${GLAD_INCLUDE_DIRS}"
	"${CMAKE_INSTALL_PREFIX}/include"
)

# Create the sample.
ADD_EXECUTABLE(glfw_glad_sample "main.cpp")

# Add dependencies (order)
ADD_DEPENDENCIES(
	glfw_glad_sample
	glad
	glfw
)

# Actual linking (import)
TARGET_LINK_LIBRARIES(
	glfw_glad_sample
	glad
	glfw
)

INSTALL(
	TARGETS glfw_glad_sample
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib/static
)