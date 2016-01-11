# deps-glfw-glad redist; CMakeLists.txt
#
# licence is public domain; if public domain isn't available to you
# (due to legalities/restrictions) feel free to consider this
# MIT licenced content.  The purpose of this document is to provide easy
# access to OpenGL via GLFW and glad; they are submodules within the git
# repository and minimal work is required to get a working opengl test
# up and running.  It can also be extended into full projects by adding
# more CMake based dependencies (e.g. zlib, libpng, physfs).

# This is just what Visual Studio or whatever project manager you use
# will see the project as.  Changing this is meaningless.
PROJECT(deps_glfw_glad C)

# glad uses 3.0 so it needs to be at least that high anyway.
CMAKE_MINIMUM_REQUIRED(VERSION 3.0 FATAL_ERROR)

# glad hack/workaround for this scope to bypass the error.
SET(OLD_CMAKE_POLICY_DEFAULT_CMP0054 ${CMAKE_POLICY_DEFAULT_CMP0054})
SET(CMAKE_POLICY_DEFAULT_CMP0054 OLD)

# If this is built standalone, and not part of an embedded project,
# define the build directory.
STRING(COMPARE EQUAL 
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_SOURCE_DIR}
	IS_ROOT_PROJECT
)

# It's cleaner to just clone this out than it is to mess with overrides.
OPTION(BUILD_SHARED_LIBS "Build shared libraries" ON)
OPTION(GLFW_BUILD_EXAMPLES "Build the GLFW example programs" OFF)
OPTION(GLFW_BUILD_TESTS "Build the GLFW test programs" OFF)
OPTION(GLFW_BUILD_DOCS "Build the GLFW documentation" OFF)
OPTION(GLFW_INSTALL "Generate installation target" ON)
OPTION(GLFW_DOCUMENT_INTERNALS "Include internals in documentation" OFF)

IF(IS_ROOT_PROJECT)
	IF(NOT DEFINED DEPS_GLFW_GLAD_BUILDSAMPLE)
		SET(DEPS_GLFW_GLAD_BUILDSAMPLE
			FALSE
			CACHE BOOL
			"Build the trivial sample application."
			FORCE
		)
	ENDIF()

	IF(NOT DEFINED DEPS_INSTALL_PREFIX)
		SET(DEPS_INSTALL_PREFIX
			"${CMAKE_BINARY_DIR}/build"
			CACHE STRING
			"Installation Prefix"
			FORCE
		)
	ENDIF()

	GET_PROPERTY(
		CMAKE_INSTALL_PREFIX_DOCS
		DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		PROPERTY CMAKE_INSTALL_PREFIX
		FULL_DOCS
	)

	SET(CMAKE_INSTALL_PREFIX ${DEPS_INSTALL_PREFIX} CACHE STRING
		"${CMAKE_INSTALL_PREFIX_DOCS}" FORCE)

	SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/bin)
	SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/bin)
	SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/bin)
	SET(CMAKE_PDB_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/bin)
ENDIF()

# Set the directory GLFW for easier usage
SET(GLFW_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/glfw")
ADD_SUBDIRECTORY(${GLFW_DIRECTORY})

# glad
SET(GLAD_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/glad")
ADD_SUBDIRECTORY(${GLAD_DIRECTORY})

# This a helper for glad.  It'll load in glad and
# Should just be .h, but future proofing doesn't hurt
#
# Note: glad exports this for us, so we can do this.
IF(NOT SKIP_INSTALL_HEADERS)
	INSTALL(
		DIRECTORY ${GLAD_INCLUDE_DIRS}
		DESTINATION "${CMAKE_INSTALL_PREFIX}"
		FILES_MATCHING PATTERN *.h PATTERN *.hpp
	)
ENDIF()

# Conditionally exported values
IF(IS_ROOT_PROJECT)
	IF(DEPS_GLFW_GLAD_BUILDSAMPLE)
		ADD_SUBDIRECTORY(sample)
	ENDIF()
ELSE()
	SET(GLFW_DIRECTORY ${GLFW_DIRECTORY} PARENT_SCOPE)
	SET(GLFW_LIBRARY glfw PARENT_SCOPE)
	SET(GLAD_DIRECTORY ${GLAD_DIRECTORY} PARENT_SCOPE)
	SET(GLAD_LIBRARY glad PARENT_SCOPE)
	SET(GLAD_INCLUE_DIRS ${GLAD_INCLUDE_DIRS} PARENT_SCOPE)
ENDIF()

# restoration to keep other projects sane.
SET(CMAKE_POLICY_DEFAULT_CMP0054 ${OLD_CMAKE_POLICY_DEFAULT_CMP0054})