# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\Users\RFMinePC\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\203.7148.70\bin\cmake\win\bin\cmake.exe

# The command to remove a file.
RM = C:\Users\RFMinePC\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\203.7148.70\bin\cmake\win\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\dev_clion\OpenGLProject

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\dev_clion\OpenGLProject\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/OpenGLProject.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/OpenGLProject.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/OpenGLProject.dir/flags.make

CMakeFiles/OpenGLProject.dir/code/main.cpp.obj: CMakeFiles/OpenGLProject.dir/flags.make
CMakeFiles/OpenGLProject.dir/code/main.cpp.obj: CMakeFiles/OpenGLProject.dir/includes_CXX.rsp
CMakeFiles/OpenGLProject.dir/code/main.cpp.obj: ../code/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\dev_clion\OpenGLProject\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/OpenGLProject.dir/code/main.cpp.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\OpenGLProject.dir\code\main.cpp.obj -c C:\dev_clion\OpenGLProject\code\main.cpp

CMakeFiles/OpenGLProject.dir/code/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OpenGLProject.dir/code/main.cpp.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\dev_clion\OpenGLProject\code\main.cpp > CMakeFiles\OpenGLProject.dir\code\main.cpp.i

CMakeFiles/OpenGLProject.dir/code/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OpenGLProject.dir/code/main.cpp.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\dev_clion\OpenGLProject\code\main.cpp -o CMakeFiles\OpenGLProject.dir\code\main.cpp.s

# Object files for target OpenGLProject
OpenGLProject_OBJECTS = \
"CMakeFiles/OpenGLProject.dir/code/main.cpp.obj"

# External object files for target OpenGLProject
OpenGLProject_EXTERNAL_OBJECTS =

OpenGLProject.exe: CMakeFiles/OpenGLProject.dir/code/main.cpp.obj
OpenGLProject.exe: CMakeFiles/OpenGLProject.dir/build.make
OpenGLProject.exe: CMakeFiles/OpenGLProject.dir/linklibs.rsp
OpenGLProject.exe: CMakeFiles/OpenGLProject.dir/objects1.rsp
OpenGLProject.exe: CMakeFiles/OpenGLProject.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\dev_clion\OpenGLProject\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable OpenGLProject.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\OpenGLProject.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/OpenGLProject.dir/build: OpenGLProject.exe

.PHONY : CMakeFiles/OpenGLProject.dir/build

CMakeFiles/OpenGLProject.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\OpenGLProject.dir\cmake_clean.cmake
.PHONY : CMakeFiles/OpenGLProject.dir/clean

CMakeFiles/OpenGLProject.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\dev_clion\OpenGLProject C:\dev_clion\OpenGLProject C:\dev_clion\OpenGLProject\cmake-build-debug C:\dev_clion\OpenGLProject\cmake-build-debug C:\dev_clion\OpenGLProject\cmake-build-debug\CMakeFiles\OpenGLProject.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/OpenGLProject.dir/depend

