# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

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

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/local/bin/cmake

# The command to remove a file.
RM = /opt/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/ben/Repositories/2DRenderer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/ben/Repositories/2DRenderer/build

# Include any dependencies generated for this target.
include CMakeFiles/game.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/game.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/game.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/game.dir/flags.make

CMakeFiles/game.dir/src/main.cpp.o: CMakeFiles/game.dir/flags.make
CMakeFiles/game.dir/src/main.cpp.o: /Users/ben/Repositories/2DRenderer/src/main.cpp
CMakeFiles/game.dir/src/main.cpp.o: CMakeFiles/game.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ben/Repositories/2DRenderer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/game.dir/src/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/game.dir/src/main.cpp.o -MF CMakeFiles/game.dir/src/main.cpp.o.d -o CMakeFiles/game.dir/src/main.cpp.o -c /Users/ben/Repositories/2DRenderer/src/main.cpp

CMakeFiles/game.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/game.dir/src/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ben/Repositories/2DRenderer/src/main.cpp > CMakeFiles/game.dir/src/main.cpp.i

CMakeFiles/game.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/game.dir/src/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ben/Repositories/2DRenderer/src/main.cpp -o CMakeFiles/game.dir/src/main.cpp.s

CMakeFiles/game.dir/includes/glad.c.o: CMakeFiles/game.dir/flags.make
CMakeFiles/game.dir/includes/glad.c.o: /Users/ben/Repositories/2DRenderer/includes/glad.c
CMakeFiles/game.dir/includes/glad.c.o: CMakeFiles/game.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ben/Repositories/2DRenderer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/game.dir/includes/glad.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/game.dir/includes/glad.c.o -MF CMakeFiles/game.dir/includes/glad.c.o.d -o CMakeFiles/game.dir/includes/glad.c.o -c /Users/ben/Repositories/2DRenderer/includes/glad.c

CMakeFiles/game.dir/includes/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/game.dir/includes/glad.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ben/Repositories/2DRenderer/includes/glad.c > CMakeFiles/game.dir/includes/glad.c.i

CMakeFiles/game.dir/includes/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/game.dir/includes/glad.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ben/Repositories/2DRenderer/includes/glad.c -o CMakeFiles/game.dir/includes/glad.c.s

CMakeFiles/game.dir/src/util/stb_image.cpp.o: CMakeFiles/game.dir/flags.make
CMakeFiles/game.dir/src/util/stb_image.cpp.o: /Users/ben/Repositories/2DRenderer/src/util/stb_image.cpp
CMakeFiles/game.dir/src/util/stb_image.cpp.o: CMakeFiles/game.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ben/Repositories/2DRenderer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/game.dir/src/util/stb_image.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/game.dir/src/util/stb_image.cpp.o -MF CMakeFiles/game.dir/src/util/stb_image.cpp.o.d -o CMakeFiles/game.dir/src/util/stb_image.cpp.o -c /Users/ben/Repositories/2DRenderer/src/util/stb_image.cpp

CMakeFiles/game.dir/src/util/stb_image.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/game.dir/src/util/stb_image.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ben/Repositories/2DRenderer/src/util/stb_image.cpp > CMakeFiles/game.dir/src/util/stb_image.cpp.i

CMakeFiles/game.dir/src/util/stb_image.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/game.dir/src/util/stb_image.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ben/Repositories/2DRenderer/src/util/stb_image.cpp -o CMakeFiles/game.dir/src/util/stb_image.cpp.s

CMakeFiles/game.dir/src/util/texture.cpp.o: CMakeFiles/game.dir/flags.make
CMakeFiles/game.dir/src/util/texture.cpp.o: /Users/ben/Repositories/2DRenderer/src/util/texture.cpp
CMakeFiles/game.dir/src/util/texture.cpp.o: CMakeFiles/game.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ben/Repositories/2DRenderer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/game.dir/src/util/texture.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/game.dir/src/util/texture.cpp.o -MF CMakeFiles/game.dir/src/util/texture.cpp.o.d -o CMakeFiles/game.dir/src/util/texture.cpp.o -c /Users/ben/Repositories/2DRenderer/src/util/texture.cpp

CMakeFiles/game.dir/src/util/texture.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/game.dir/src/util/texture.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ben/Repositories/2DRenderer/src/util/texture.cpp > CMakeFiles/game.dir/src/util/texture.cpp.i

CMakeFiles/game.dir/src/util/texture.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/game.dir/src/util/texture.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ben/Repositories/2DRenderer/src/util/texture.cpp -o CMakeFiles/game.dir/src/util/texture.cpp.s

CMakeFiles/game.dir/lib/imgui/imgui.cpp.o: CMakeFiles/game.dir/flags.make
CMakeFiles/game.dir/lib/imgui/imgui.cpp.o: /Users/ben/Repositories/2DRenderer/lib/imgui/imgui.cpp
CMakeFiles/game.dir/lib/imgui/imgui.cpp.o: CMakeFiles/game.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ben/Repositories/2DRenderer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/game.dir/lib/imgui/imgui.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/game.dir/lib/imgui/imgui.cpp.o -MF CMakeFiles/game.dir/lib/imgui/imgui.cpp.o.d -o CMakeFiles/game.dir/lib/imgui/imgui.cpp.o -c /Users/ben/Repositories/2DRenderer/lib/imgui/imgui.cpp

CMakeFiles/game.dir/lib/imgui/imgui.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/game.dir/lib/imgui/imgui.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ben/Repositories/2DRenderer/lib/imgui/imgui.cpp > CMakeFiles/game.dir/lib/imgui/imgui.cpp.i

CMakeFiles/game.dir/lib/imgui/imgui.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/game.dir/lib/imgui/imgui.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ben/Repositories/2DRenderer/lib/imgui/imgui.cpp -o CMakeFiles/game.dir/lib/imgui/imgui.cpp.s

CMakeFiles/game.dir/lib/imgui/imgui_draw.cpp.o: CMakeFiles/game.dir/flags.make
CMakeFiles/game.dir/lib/imgui/imgui_draw.cpp.o: /Users/ben/Repositories/2DRenderer/lib/imgui/imgui_draw.cpp
CMakeFiles/game.dir/lib/imgui/imgui_draw.cpp.o: CMakeFiles/game.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ben/Repositories/2DRenderer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/game.dir/lib/imgui/imgui_draw.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/game.dir/lib/imgui/imgui_draw.cpp.o -MF CMakeFiles/game.dir/lib/imgui/imgui_draw.cpp.o.d -o CMakeFiles/game.dir/lib/imgui/imgui_draw.cpp.o -c /Users/ben/Repositories/2DRenderer/lib/imgui/imgui_draw.cpp

CMakeFiles/game.dir/lib/imgui/imgui_draw.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/game.dir/lib/imgui/imgui_draw.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ben/Repositories/2DRenderer/lib/imgui/imgui_draw.cpp > CMakeFiles/game.dir/lib/imgui/imgui_draw.cpp.i

CMakeFiles/game.dir/lib/imgui/imgui_draw.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/game.dir/lib/imgui/imgui_draw.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ben/Repositories/2DRenderer/lib/imgui/imgui_draw.cpp -o CMakeFiles/game.dir/lib/imgui/imgui_draw.cpp.s

CMakeFiles/game.dir/lib/imgui/imgui_tables.cpp.o: CMakeFiles/game.dir/flags.make
CMakeFiles/game.dir/lib/imgui/imgui_tables.cpp.o: /Users/ben/Repositories/2DRenderer/lib/imgui/imgui_tables.cpp
CMakeFiles/game.dir/lib/imgui/imgui_tables.cpp.o: CMakeFiles/game.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ben/Repositories/2DRenderer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/game.dir/lib/imgui/imgui_tables.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/game.dir/lib/imgui/imgui_tables.cpp.o -MF CMakeFiles/game.dir/lib/imgui/imgui_tables.cpp.o.d -o CMakeFiles/game.dir/lib/imgui/imgui_tables.cpp.o -c /Users/ben/Repositories/2DRenderer/lib/imgui/imgui_tables.cpp

CMakeFiles/game.dir/lib/imgui/imgui_tables.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/game.dir/lib/imgui/imgui_tables.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ben/Repositories/2DRenderer/lib/imgui/imgui_tables.cpp > CMakeFiles/game.dir/lib/imgui/imgui_tables.cpp.i

CMakeFiles/game.dir/lib/imgui/imgui_tables.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/game.dir/lib/imgui/imgui_tables.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ben/Repositories/2DRenderer/lib/imgui/imgui_tables.cpp -o CMakeFiles/game.dir/lib/imgui/imgui_tables.cpp.s

CMakeFiles/game.dir/lib/imgui/imgui_widgets.cpp.o: CMakeFiles/game.dir/flags.make
CMakeFiles/game.dir/lib/imgui/imgui_widgets.cpp.o: /Users/ben/Repositories/2DRenderer/lib/imgui/imgui_widgets.cpp
CMakeFiles/game.dir/lib/imgui/imgui_widgets.cpp.o: CMakeFiles/game.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ben/Repositories/2DRenderer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/game.dir/lib/imgui/imgui_widgets.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/game.dir/lib/imgui/imgui_widgets.cpp.o -MF CMakeFiles/game.dir/lib/imgui/imgui_widgets.cpp.o.d -o CMakeFiles/game.dir/lib/imgui/imgui_widgets.cpp.o -c /Users/ben/Repositories/2DRenderer/lib/imgui/imgui_widgets.cpp

CMakeFiles/game.dir/lib/imgui/imgui_widgets.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/game.dir/lib/imgui/imgui_widgets.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ben/Repositories/2DRenderer/lib/imgui/imgui_widgets.cpp > CMakeFiles/game.dir/lib/imgui/imgui_widgets.cpp.i

CMakeFiles/game.dir/lib/imgui/imgui_widgets.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/game.dir/lib/imgui/imgui_widgets.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ben/Repositories/2DRenderer/lib/imgui/imgui_widgets.cpp -o CMakeFiles/game.dir/lib/imgui/imgui_widgets.cpp.s

CMakeFiles/game.dir/lib/imgui/backends/imgui_impl_opengl3.cpp.o: CMakeFiles/game.dir/flags.make
CMakeFiles/game.dir/lib/imgui/backends/imgui_impl_opengl3.cpp.o: /Users/ben/Repositories/2DRenderer/lib/imgui/backends/imgui_impl_opengl3.cpp
CMakeFiles/game.dir/lib/imgui/backends/imgui_impl_opengl3.cpp.o: CMakeFiles/game.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ben/Repositories/2DRenderer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/game.dir/lib/imgui/backends/imgui_impl_opengl3.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/game.dir/lib/imgui/backends/imgui_impl_opengl3.cpp.o -MF CMakeFiles/game.dir/lib/imgui/backends/imgui_impl_opengl3.cpp.o.d -o CMakeFiles/game.dir/lib/imgui/backends/imgui_impl_opengl3.cpp.o -c /Users/ben/Repositories/2DRenderer/lib/imgui/backends/imgui_impl_opengl3.cpp

CMakeFiles/game.dir/lib/imgui/backends/imgui_impl_opengl3.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/game.dir/lib/imgui/backends/imgui_impl_opengl3.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ben/Repositories/2DRenderer/lib/imgui/backends/imgui_impl_opengl3.cpp > CMakeFiles/game.dir/lib/imgui/backends/imgui_impl_opengl3.cpp.i

CMakeFiles/game.dir/lib/imgui/backends/imgui_impl_opengl3.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/game.dir/lib/imgui/backends/imgui_impl_opengl3.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ben/Repositories/2DRenderer/lib/imgui/backends/imgui_impl_opengl3.cpp -o CMakeFiles/game.dir/lib/imgui/backends/imgui_impl_opengl3.cpp.s

CMakeFiles/game.dir/lib/imgui/backends/imgui_impl_glfw.cpp.o: CMakeFiles/game.dir/flags.make
CMakeFiles/game.dir/lib/imgui/backends/imgui_impl_glfw.cpp.o: /Users/ben/Repositories/2DRenderer/lib/imgui/backends/imgui_impl_glfw.cpp
CMakeFiles/game.dir/lib/imgui/backends/imgui_impl_glfw.cpp.o: CMakeFiles/game.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ben/Repositories/2DRenderer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/game.dir/lib/imgui/backends/imgui_impl_glfw.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/game.dir/lib/imgui/backends/imgui_impl_glfw.cpp.o -MF CMakeFiles/game.dir/lib/imgui/backends/imgui_impl_glfw.cpp.o.d -o CMakeFiles/game.dir/lib/imgui/backends/imgui_impl_glfw.cpp.o -c /Users/ben/Repositories/2DRenderer/lib/imgui/backends/imgui_impl_glfw.cpp

CMakeFiles/game.dir/lib/imgui/backends/imgui_impl_glfw.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/game.dir/lib/imgui/backends/imgui_impl_glfw.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ben/Repositories/2DRenderer/lib/imgui/backends/imgui_impl_glfw.cpp > CMakeFiles/game.dir/lib/imgui/backends/imgui_impl_glfw.cpp.i

CMakeFiles/game.dir/lib/imgui/backends/imgui_impl_glfw.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/game.dir/lib/imgui/backends/imgui_impl_glfw.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ben/Repositories/2DRenderer/lib/imgui/backends/imgui_impl_glfw.cpp -o CMakeFiles/game.dir/lib/imgui/backends/imgui_impl_glfw.cpp.s

# Object files for target game
game_OBJECTS = \
"CMakeFiles/game.dir/src/main.cpp.o" \
"CMakeFiles/game.dir/includes/glad.c.o" \
"CMakeFiles/game.dir/src/util/stb_image.cpp.o" \
"CMakeFiles/game.dir/src/util/texture.cpp.o" \
"CMakeFiles/game.dir/lib/imgui/imgui.cpp.o" \
"CMakeFiles/game.dir/lib/imgui/imgui_draw.cpp.o" \
"CMakeFiles/game.dir/lib/imgui/imgui_tables.cpp.o" \
"CMakeFiles/game.dir/lib/imgui/imgui_widgets.cpp.o" \
"CMakeFiles/game.dir/lib/imgui/backends/imgui_impl_opengl3.cpp.o" \
"CMakeFiles/game.dir/lib/imgui/backends/imgui_impl_glfw.cpp.o"

# External object files for target game
game_EXTERNAL_OBJECTS =

game: CMakeFiles/game.dir/src/main.cpp.o
game: CMakeFiles/game.dir/includes/glad.c.o
game: CMakeFiles/game.dir/src/util/stb_image.cpp.o
game: CMakeFiles/game.dir/src/util/texture.cpp.o
game: CMakeFiles/game.dir/lib/imgui/imgui.cpp.o
game: CMakeFiles/game.dir/lib/imgui/imgui_draw.cpp.o
game: CMakeFiles/game.dir/lib/imgui/imgui_tables.cpp.o
game: CMakeFiles/game.dir/lib/imgui/imgui_widgets.cpp.o
game: CMakeFiles/game.dir/lib/imgui/backends/imgui_impl_opengl3.cpp.o
game: CMakeFiles/game.dir/lib/imgui/backends/imgui_impl_glfw.cpp.o
game: CMakeFiles/game.dir/build.make
game: lib/glfw/src/libglfw3.a
game: lib/enet/libenet.a
game: CMakeFiles/game.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/ben/Repositories/2DRenderer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Linking CXX executable game"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/game.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/game.dir/build: game
.PHONY : CMakeFiles/game.dir/build

CMakeFiles/game.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/game.dir/cmake_clean.cmake
.PHONY : CMakeFiles/game.dir/clean

CMakeFiles/game.dir/depend:
	cd /Users/ben/Repositories/2DRenderer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/ben/Repositories/2DRenderer /Users/ben/Repositories/2DRenderer /Users/ben/Repositories/2DRenderer/build /Users/ben/Repositories/2DRenderer/build /Users/ben/Repositories/2DRenderer/build/CMakeFiles/game.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/game.dir/depend

