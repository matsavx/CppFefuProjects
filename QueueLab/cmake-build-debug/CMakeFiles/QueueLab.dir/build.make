# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /cygdrive/c/Users/User/.CLion2019.3/system/cygwin_cmake/bin/cmake.exe

# The command to remove a file.
RM = /cygdrive/c/Users/User/.CLion2019.3/system/cygwin_cmake/bin/cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /cygdrive/c/myfiles/MyClionProjects/QueueLab

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /cygdrive/c/myfiles/MyClionProjects/QueueLab/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/QueueLab.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/QueueLab.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/QueueLab.dir/flags.make

CMakeFiles/QueueLab.dir/main.cpp.o: CMakeFiles/QueueLab.dir/flags.make
CMakeFiles/QueueLab.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/c/myfiles/MyClionProjects/QueueLab/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/QueueLab.dir/main.cpp.o"
	/usr/bin/c++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/QueueLab.dir/main.cpp.o -c /cygdrive/c/myfiles/MyClionProjects/QueueLab/main.cpp

CMakeFiles/QueueLab.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/QueueLab.dir/main.cpp.i"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /cygdrive/c/myfiles/MyClionProjects/QueueLab/main.cpp > CMakeFiles/QueueLab.dir/main.cpp.i

CMakeFiles/QueueLab.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/QueueLab.dir/main.cpp.s"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /cygdrive/c/myfiles/MyClionProjects/QueueLab/main.cpp -o CMakeFiles/QueueLab.dir/main.cpp.s

# Object files for target QueueLab
QueueLab_OBJECTS = \
"CMakeFiles/QueueLab.dir/main.cpp.o"

# External object files for target QueueLab
QueueLab_EXTERNAL_OBJECTS =

QueueLab.exe: CMakeFiles/QueueLab.dir/main.cpp.o
QueueLab.exe: CMakeFiles/QueueLab.dir/build.make
QueueLab.exe: CMakeFiles/QueueLab.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/cygdrive/c/myfiles/MyClionProjects/QueueLab/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable QueueLab.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/QueueLab.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/QueueLab.dir/build: QueueLab.exe

.PHONY : CMakeFiles/QueueLab.dir/build

CMakeFiles/QueueLab.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/QueueLab.dir/cmake_clean.cmake
.PHONY : CMakeFiles/QueueLab.dir/clean

CMakeFiles/QueueLab.dir/depend:
	cd /cygdrive/c/myfiles/MyClionProjects/QueueLab/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /cygdrive/c/myfiles/MyClionProjects/QueueLab /cygdrive/c/myfiles/MyClionProjects/QueueLab /cygdrive/c/myfiles/MyClionProjects/QueueLab/cmake-build-debug /cygdrive/c/myfiles/MyClionProjects/QueueLab/cmake-build-debug /cygdrive/c/myfiles/MyClionProjects/QueueLab/cmake-build-debug/CMakeFiles/QueueLab.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/QueueLab.dir/depend

