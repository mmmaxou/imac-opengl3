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
CMAKE_BINARY_DIR = /home/mmmaxou/Imac/Synthese-Image/imac-opengl3/GLImac-Template/build

# Include any dependencies generated for this target.
include TP1/CMakeFiles/TP1_exo4_quad_draw.dir/depend.make

# Include the progress variables for this target.
include TP1/CMakeFiles/TP1_exo4_quad_draw.dir/progress.make

# Include the compile flags for this target's objects.
include TP1/CMakeFiles/TP1_exo4_quad_draw.dir/flags.make

TP1/CMakeFiles/TP1_exo4_quad_draw.dir/exo4_quad_draw.cpp.o: TP1/CMakeFiles/TP1_exo4_quad_draw.dir/flags.make
TP1/CMakeFiles/TP1_exo4_quad_draw.dir/exo4_quad_draw.cpp.o: ../TP1/exo4_quad_draw.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mmmaxou/Imac/Synthese-Image/imac-opengl3/GLImac-Template/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object TP1/CMakeFiles/TP1_exo4_quad_draw.dir/exo4_quad_draw.cpp.o"
	cd /home/mmmaxou/Imac/Synthese-Image/imac-opengl3/GLImac-Template/build/TP1 && /usr/bin/x86_64-linux-gnu-g++-7  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TP1_exo4_quad_draw.dir/exo4_quad_draw.cpp.o -c /home/mmmaxou/Imac/Synthese-Image/imac-opengl3/GLImac-Template/TP1/exo4_quad_draw.cpp

TP1/CMakeFiles/TP1_exo4_quad_draw.dir/exo4_quad_draw.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TP1_exo4_quad_draw.dir/exo4_quad_draw.cpp.i"
	cd /home/mmmaxou/Imac/Synthese-Image/imac-opengl3/GLImac-Template/build/TP1 && /usr/bin/x86_64-linux-gnu-g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mmmaxou/Imac/Synthese-Image/imac-opengl3/GLImac-Template/TP1/exo4_quad_draw.cpp > CMakeFiles/TP1_exo4_quad_draw.dir/exo4_quad_draw.cpp.i

TP1/CMakeFiles/TP1_exo4_quad_draw.dir/exo4_quad_draw.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TP1_exo4_quad_draw.dir/exo4_quad_draw.cpp.s"
	cd /home/mmmaxou/Imac/Synthese-Image/imac-opengl3/GLImac-Template/build/TP1 && /usr/bin/x86_64-linux-gnu-g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mmmaxou/Imac/Synthese-Image/imac-opengl3/GLImac-Template/TP1/exo4_quad_draw.cpp -o CMakeFiles/TP1_exo4_quad_draw.dir/exo4_quad_draw.cpp.s

TP1/CMakeFiles/TP1_exo4_quad_draw.dir/exo4_quad_draw.cpp.o.requires:

.PHONY : TP1/CMakeFiles/TP1_exo4_quad_draw.dir/exo4_quad_draw.cpp.o.requires

TP1/CMakeFiles/TP1_exo4_quad_draw.dir/exo4_quad_draw.cpp.o.provides: TP1/CMakeFiles/TP1_exo4_quad_draw.dir/exo4_quad_draw.cpp.o.requires
	$(MAKE) -f TP1/CMakeFiles/TP1_exo4_quad_draw.dir/build.make TP1/CMakeFiles/TP1_exo4_quad_draw.dir/exo4_quad_draw.cpp.o.provides.build
.PHONY : TP1/CMakeFiles/TP1_exo4_quad_draw.dir/exo4_quad_draw.cpp.o.provides

TP1/CMakeFiles/TP1_exo4_quad_draw.dir/exo4_quad_draw.cpp.o.provides.build: TP1/CMakeFiles/TP1_exo4_quad_draw.dir/exo4_quad_draw.cpp.o


# Object files for target TP1_exo4_quad_draw
TP1_exo4_quad_draw_OBJECTS = \
"CMakeFiles/TP1_exo4_quad_draw.dir/exo4_quad_draw.cpp.o"

# External object files for target TP1_exo4_quad_draw
TP1_exo4_quad_draw_EXTERNAL_OBJECTS =

TP1/TP1_exo4_quad_draw: TP1/CMakeFiles/TP1_exo4_quad_draw.dir/exo4_quad_draw.cpp.o
TP1/TP1_exo4_quad_draw: TP1/CMakeFiles/TP1_exo4_quad_draw.dir/build.make
TP1/TP1_exo4_quad_draw: glimac/libglimac.a
TP1/TP1_exo4_quad_draw: /usr/lib/x86_64-linux-gnu/libSDLmain.a
TP1/TP1_exo4_quad_draw: /usr/lib/x86_64-linux-gnu/libSDL.so
TP1/TP1_exo4_quad_draw: /usr/lib/x86_64-linux-gnu/libGL.so
TP1/TP1_exo4_quad_draw: /usr/lib/x86_64-linux-gnu/libGLU.so
TP1/TP1_exo4_quad_draw: /usr/lib/x86_64-linux-gnu/libGLEW.so
TP1/TP1_exo4_quad_draw: TP1/CMakeFiles/TP1_exo4_quad_draw.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mmmaxou/Imac/Synthese-Image/imac-opengl3/GLImac-Template/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable TP1_exo4_quad_draw"
	cd /home/mmmaxou/Imac/Synthese-Image/imac-opengl3/GLImac-Template/build/TP1 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TP1_exo4_quad_draw.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
TP1/CMakeFiles/TP1_exo4_quad_draw.dir/build: TP1/TP1_exo4_quad_draw

.PHONY : TP1/CMakeFiles/TP1_exo4_quad_draw.dir/build

TP1/CMakeFiles/TP1_exo4_quad_draw.dir/requires: TP1/CMakeFiles/TP1_exo4_quad_draw.dir/exo4_quad_draw.cpp.o.requires

.PHONY : TP1/CMakeFiles/TP1_exo4_quad_draw.dir/requires

TP1/CMakeFiles/TP1_exo4_quad_draw.dir/clean:
	cd /home/mmmaxou/Imac/Synthese-Image/imac-opengl3/GLImac-Template/build/TP1 && $(CMAKE_COMMAND) -P CMakeFiles/TP1_exo4_quad_draw.dir/cmake_clean.cmake
.PHONY : TP1/CMakeFiles/TP1_exo4_quad_draw.dir/clean

TP1/CMakeFiles/TP1_exo4_quad_draw.dir/depend:
	cd /home/mmmaxou/Imac/Synthese-Image/imac-opengl3/GLImac-Template/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mmmaxou/Imac/Synthese-Image/imac-opengl3/GLImac-Template /home/mmmaxou/Imac/Synthese-Image/imac-opengl3/GLImac-Template/TP1 /home/mmmaxou/Imac/Synthese-Image/imac-opengl3/GLImac-Template/build /home/mmmaxou/Imac/Synthese-Image/imac-opengl3/GLImac-Template/build/TP1 /home/mmmaxou/Imac/Synthese-Image/imac-opengl3/GLImac-Template/build/TP1/CMakeFiles/TP1_exo4_quad_draw.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : TP1/CMakeFiles/TP1_exo4_quad_draw.dir/depend

