# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.10

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\Users\zhu\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-1\181.4668.70\bin\cmake\bin\cmake.exe

# The command to remove a file.
RM = C:\Users\zhu\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-1\181.4668.70\bin\cmake\bin\cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\code\DSC_hw\hw_4

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\code\DSC_hw\hw_4\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/hw_4.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/hw_4.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/hw_4.dir/flags.make

CMakeFiles/hw_4.dir/main.cpp.obj: CMakeFiles/hw_4.dir/flags.make
CMakeFiles/hw_4.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\code\DSC_hw\hw_4\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/hw_4.dir/main.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\hw_4.dir\main.cpp.obj -c C:\code\DSC_hw\hw_4\main.cpp

CMakeFiles/hw_4.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hw_4.dir/main.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\code\DSC_hw\hw_4\main.cpp > CMakeFiles\hw_4.dir\main.cpp.i

CMakeFiles/hw_4.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hw_4.dir/main.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\code\DSC_hw\hw_4\main.cpp -o CMakeFiles\hw_4.dir\main.cpp.s

CMakeFiles/hw_4.dir/main.cpp.obj.requires:

.PHONY : CMakeFiles/hw_4.dir/main.cpp.obj.requires

CMakeFiles/hw_4.dir/main.cpp.obj.provides: CMakeFiles/hw_4.dir/main.cpp.obj.requires
	$(MAKE) -f CMakeFiles\hw_4.dir\build.make CMakeFiles/hw_4.dir/main.cpp.obj.provides.build
.PHONY : CMakeFiles/hw_4.dir/main.cpp.obj.provides

CMakeFiles/hw_4.dir/main.cpp.obj.provides.build: CMakeFiles/hw_4.dir/main.cpp.obj


# Object files for target hw_4
hw_4_OBJECTS = \
"CMakeFiles/hw_4.dir/main.cpp.obj"

# External object files for target hw_4
hw_4_EXTERNAL_OBJECTS =

hw_4.exe: CMakeFiles/hw_4.dir/main.cpp.obj
hw_4.exe: CMakeFiles/hw_4.dir/build.make
hw_4.exe: CMakeFiles/hw_4.dir/linklibs.rsp
hw_4.exe: CMakeFiles/hw_4.dir/objects1.rsp
hw_4.exe: CMakeFiles/hw_4.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\code\DSC_hw\hw_4\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable hw_4.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\hw_4.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/hw_4.dir/build: hw_4.exe

.PHONY : CMakeFiles/hw_4.dir/build

CMakeFiles/hw_4.dir/requires: CMakeFiles/hw_4.dir/main.cpp.obj.requires

.PHONY : CMakeFiles/hw_4.dir/requires

CMakeFiles/hw_4.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\hw_4.dir\cmake_clean.cmake
.PHONY : CMakeFiles/hw_4.dir/clean

CMakeFiles/hw_4.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\code\DSC_hw\hw_4 C:\code\DSC_hw\hw_4 C:\code\DSC_hw\hw_4\cmake-build-debug C:\code\DSC_hw\hw_4\cmake-build-debug C:\code\DSC_hw\hw_4\cmake-build-debug\CMakeFiles\hw_4.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/hw_4.dir/depend

