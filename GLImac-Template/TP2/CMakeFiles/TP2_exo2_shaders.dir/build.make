# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/mmmaxou/Imac/Synthese-Image/imac-opengl3/GLImac-Template

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mmmaxou/Imac/Synthese-Image/imac-opengl3/GLImac-Template

# Include any dependencies generated for this target.
include TP2/CMakeFiles/TP2_exo2_shaders.dir/depend.make

# Include the progress variables for this target.
include TP2/CMakeFiles/TP2_exo2_shaders.dir/progress.make

# Include the compile flags for this target's objects.
include TP2/CMakeFiles/TP2_exo2_shaders.dir/flags.make

TP2/CMakeFiles/TP2_exo2_shaders.dir/exo2_shaders.cpp.o: TP2/CMakeFiles/TP2_exo2_shaders.dir/flags.make
TP2/CMakeFiles/TP2_exo2_shaders.dir/exo2_shaders.cpp.o: TP2/exo2_shaders.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mmmaxou/Imac/Synthese-Image/imac-opengl3/GLImac-Template/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object TP2/CMakeFiles/TP2_exo2_shaders.dir/exo2_shaders.cpp.o"
	cd /home/mmmaxou/Imac/Synthese-Image/imac-opengl3/GLImac-Template/TP2 && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TP2_exo2_shaders.dir/exo2_shaders.cpp.o -c /home/mmmaxou/Imac/Synthese-Image/imac-opengl3/GLImac-Template/TP2/exo2_shaders.cpp

TP2/CMakeFiles/TP2_exo2_shaders.dir/exo2_shaders.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TP2_exo2_shaders.dir/exo2_shaders.cpp.i"
	cd /home/mmmaxou/Imac/Synthese-Image/imac-opengl3/GLImac-Template/TP2 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mmmaxou/Imac/Synthese-Image/imac-opengl3/GLImac-Template/TP2/exo2_shaders.cpp > CMakeFiles/TP2_exo2_shaders.dir/exo2_shaders.cpp.i

TP2/CMakeFiles/TP2_exo2_shaders.dir/exo2_shaders.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TP2_exo2_shaders.dir/exo2_shaders.cpp.s"
	cd /home/mmmaxou/Imac/Synthese-Image/imac-opengl3/GLImac-Template/TP2 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mmmaxou/Imac/Synthese-Image/imac-opengl3/GLImac-Template/TP2/exo2_shaders.cpp -o CMakeFiles/TP2_exo2_shaders.dir/exo2_shaders.cpp.s

TP2/CMakeFiles/TP2_exo2_shaders.dir/exo2_shaders.cpp.o.requires:

.PHONY : TP2/CMakeFiles/TP2_exo2_shaders.dir/exo2_shaders.cpp.o.requires

TP2/CMakeFiles/TP2_exo2_shaders.dir/exo2_shaders.cpp.o.provides: TP2/CMakeFiles/TP2_exo2_shaders.dir/exo2_shaders.cpp.o.requires
	$(MAKE) -f TP2/CMakeFiles/TP2_exo2_shaders.dir/build.make TP2/CMakeFiles/TP2_exo2_shaders.dir/exo2_shaders.cpp.o.provides.build
.PHONY : TP2/CMakeFiles/TP2_exo2_shaders.dir/exo2_shaders.cpp.o.provides

TP2/CMakeFiles/TP2_exo2_shaders.dir/exo2_shaders.cpp.o.provides.build: TP2/CMakeFiles/TP2_exo2_shaders.dir/exo2_shaders.cpp.o


# Object files for target TP2_exo2_shaders
TP2_exo2_shaders_OBJECTS = \
"CMakeFiles/TP2_exo2_shaders.dir/exo2_shaders.cpp.o"

# External object files for target TP2_exo2_shaders
TP2_exo2_shaders_EXTERNAL_OBJECTS =

TP2/TP2_exo2_shaders: TP2/CMakeFiles/TP2_exo2_shaders.dir/exo2_shaders.cpp.o
TP2/TP2_exo2_shaders: TP2/CMakeFiles/TP2_exo2_shaders.dir/build.make
TP2/TP2_exo2_shaders: glimac/libglimac.a
TP2/TP2_exo2_shaders: /usr/lib/x86_64-linux-gnu/libSDLmain.a
TP2/TP2_exo2_shaders: /usr/lib/x86_64-linux-gnu/libSDL.so
TP2/TP2_exo2_shaders: /usr/lib/x86_64-linux-gnu/libGL.so
TP2/TP2_exo2_shaders: /usr/lib/x86_64-linux-gnu/libGLU.so
TP2/TP2_exo2_shaders: /usr/lib/x86_64-linux-gnu/libGLEW.so
TP2/TP2_exo2_shaders: TP2/CMakeFiles/TP2_exo2_shaders.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mmmaxou/Imac/Synthese-Image/imac-opengl3/GLImac-Template/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable TP2_exo2_shaders"
	cd /home/mmmaxou/Imac/Synthese-Image/imac-opengl3/GLImac-Template/TP2 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TP2_exo2_shaders.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
TP2/CMakeFiles/TP2_exo2_shaders.dir/build: TP2/TP2_exo2_shaders

.PHONY : TP2/CMakeFiles/TP2_exo2_shaders.dir/build

TP2/CMakeFiles/TP2_exo2_shaders.dir/requires: TP2/CMakeFiles/TP2_exo2_shaders.dir/exo2_shaders.cpp.o.requires

.PHONY : TP2/CMakeFiles/TP2_exo2_shaders.dir/requires

TP2/CMakeFiles/TP2_exo2_shaders.dir/clean:
	cd /home/mmmaxou/Imac/Synthese-Image/imac-opengl3/GLImac-Template/TP2 && $(CMAKE_COMMAND) -P CMakeFiles/TP2_exo2_shaders.dir/cmake_clean.cmake
.PHONY : TP2/CMakeFiles/TP2_exo2_shaders.dir/clean

TP2/CMakeFiles/TP2_exo2_shaders.dir/depend:
	cd /home/mmmaxou/Imac/Synthese-Image/imac-opengl3/GLImac-Template && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mmmaxou/Imac/Synthese-Image/imac-opengl3/GLImac-Template /home/mmmaxou/Imac/Synthese-Image/imac-opengl3/GLImac-Template/TP2 /home/mmmaxou/Imac/Synthese-Image/imac-opengl3/GLImac-Template /home/mmmaxou/Imac/Synthese-Image/imac-opengl3/GLImac-Template/TP2 /home/mmmaxou/Imac/Synthese-Image/imac-opengl3/GLImac-Template/TP2/CMakeFiles/TP2_exo2_shaders.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : TP2/CMakeFiles/TP2_exo2_shaders.dir/depend

