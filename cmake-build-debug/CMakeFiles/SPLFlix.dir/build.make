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
CMAKE_COMMAND = /snap/clion/99/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/99/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/yonatan/Studies/SPL/SPLFlix

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yonatan/Studies/SPL/SPLFlix/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/SPLFlix.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/SPLFlix.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SPLFlix.dir/flags.make

CMakeFiles/SPLFlix.dir/src/Action.cpp.o: CMakeFiles/SPLFlix.dir/flags.make
CMakeFiles/SPLFlix.dir/src/Action.cpp.o: ../src/Action.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yonatan/Studies/SPL/SPLFlix/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/SPLFlix.dir/src/Action.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SPLFlix.dir/src/Action.cpp.o -c /home/yonatan/Studies/SPL/SPLFlix/src/Action.cpp

CMakeFiles/SPLFlix.dir/src/Action.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SPLFlix.dir/src/Action.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yonatan/Studies/SPL/SPLFlix/src/Action.cpp > CMakeFiles/SPLFlix.dir/src/Action.cpp.i

CMakeFiles/SPLFlix.dir/src/Action.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SPLFlix.dir/src/Action.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yonatan/Studies/SPL/SPLFlix/src/Action.cpp -o CMakeFiles/SPLFlix.dir/src/Action.cpp.s

CMakeFiles/SPLFlix.dir/src/Main.cpp.o: CMakeFiles/SPLFlix.dir/flags.make
CMakeFiles/SPLFlix.dir/src/Main.cpp.o: ../src/Main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yonatan/Studies/SPL/SPLFlix/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/SPLFlix.dir/src/Main.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SPLFlix.dir/src/Main.cpp.o -c /home/yonatan/Studies/SPL/SPLFlix/src/Main.cpp

CMakeFiles/SPLFlix.dir/src/Main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SPLFlix.dir/src/Main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yonatan/Studies/SPL/SPLFlix/src/Main.cpp > CMakeFiles/SPLFlix.dir/src/Main.cpp.i

CMakeFiles/SPLFlix.dir/src/Main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SPLFlix.dir/src/Main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yonatan/Studies/SPL/SPLFlix/src/Main.cpp -o CMakeFiles/SPLFlix.dir/src/Main.cpp.s

CMakeFiles/SPLFlix.dir/src/Session.cpp.o: CMakeFiles/SPLFlix.dir/flags.make
CMakeFiles/SPLFlix.dir/src/Session.cpp.o: ../src/Session.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yonatan/Studies/SPL/SPLFlix/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/SPLFlix.dir/src/Session.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SPLFlix.dir/src/Session.cpp.o -c /home/yonatan/Studies/SPL/SPLFlix/src/Session.cpp

CMakeFiles/SPLFlix.dir/src/Session.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SPLFlix.dir/src/Session.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yonatan/Studies/SPL/SPLFlix/src/Session.cpp > CMakeFiles/SPLFlix.dir/src/Session.cpp.i

CMakeFiles/SPLFlix.dir/src/Session.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SPLFlix.dir/src/Session.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yonatan/Studies/SPL/SPLFlix/src/Session.cpp -o CMakeFiles/SPLFlix.dir/src/Session.cpp.s

CMakeFiles/SPLFlix.dir/src/User.cpp.o: CMakeFiles/SPLFlix.dir/flags.make
CMakeFiles/SPLFlix.dir/src/User.cpp.o: ../src/User.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yonatan/Studies/SPL/SPLFlix/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/SPLFlix.dir/src/User.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SPLFlix.dir/src/User.cpp.o -c /home/yonatan/Studies/SPL/SPLFlix/src/User.cpp

CMakeFiles/SPLFlix.dir/src/User.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SPLFlix.dir/src/User.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yonatan/Studies/SPL/SPLFlix/src/User.cpp > CMakeFiles/SPLFlix.dir/src/User.cpp.i

CMakeFiles/SPLFlix.dir/src/User.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SPLFlix.dir/src/User.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yonatan/Studies/SPL/SPLFlix/src/User.cpp -o CMakeFiles/SPLFlix.dir/src/User.cpp.s

CMakeFiles/SPLFlix.dir/src/Watchable.cpp.o: CMakeFiles/SPLFlix.dir/flags.make
CMakeFiles/SPLFlix.dir/src/Watchable.cpp.o: ../src/Watchable.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yonatan/Studies/SPL/SPLFlix/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/SPLFlix.dir/src/Watchable.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SPLFlix.dir/src/Watchable.cpp.o -c /home/yonatan/Studies/SPL/SPLFlix/src/Watchable.cpp

CMakeFiles/SPLFlix.dir/src/Watchable.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SPLFlix.dir/src/Watchable.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yonatan/Studies/SPL/SPLFlix/src/Watchable.cpp > CMakeFiles/SPLFlix.dir/src/Watchable.cpp.i

CMakeFiles/SPLFlix.dir/src/Watchable.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SPLFlix.dir/src/Watchable.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yonatan/Studies/SPL/SPLFlix/src/Watchable.cpp -o CMakeFiles/SPLFlix.dir/src/Watchable.cpp.s

# Object files for target SPLFlix
SPLFlix_OBJECTS = \
"CMakeFiles/SPLFlix.dir/src/Action.cpp.o" \
"CMakeFiles/SPLFlix.dir/src/Main.cpp.o" \
"CMakeFiles/SPLFlix.dir/src/Session.cpp.o" \
"CMakeFiles/SPLFlix.dir/src/User.cpp.o" \
"CMakeFiles/SPLFlix.dir/src/Watchable.cpp.o"

# External object files for target SPLFlix
SPLFlix_EXTERNAL_OBJECTS =

SPLFlix: CMakeFiles/SPLFlix.dir/src/Action.cpp.o
SPLFlix: CMakeFiles/SPLFlix.dir/src/Main.cpp.o
SPLFlix: CMakeFiles/SPLFlix.dir/src/Session.cpp.o
SPLFlix: CMakeFiles/SPLFlix.dir/src/User.cpp.o
SPLFlix: CMakeFiles/SPLFlix.dir/src/Watchable.cpp.o
SPLFlix: CMakeFiles/SPLFlix.dir/build.make
SPLFlix: CMakeFiles/SPLFlix.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/yonatan/Studies/SPL/SPLFlix/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable SPLFlix"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SPLFlix.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SPLFlix.dir/build: SPLFlix

.PHONY : CMakeFiles/SPLFlix.dir/build

CMakeFiles/SPLFlix.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SPLFlix.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SPLFlix.dir/clean

CMakeFiles/SPLFlix.dir/depend:
	cd /home/yonatan/Studies/SPL/SPLFlix/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yonatan/Studies/SPL/SPLFlix /home/yonatan/Studies/SPL/SPLFlix /home/yonatan/Studies/SPL/SPLFlix/cmake-build-debug /home/yonatan/Studies/SPL/SPLFlix/cmake-build-debug /home/yonatan/Studies/SPL/SPLFlix/cmake-build-debug/CMakeFiles/SPLFlix.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/SPLFlix.dir/depend

