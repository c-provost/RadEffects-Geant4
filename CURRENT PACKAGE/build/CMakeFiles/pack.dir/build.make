# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.29

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.29.6/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.29.6/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/condo/Geant-4/RadEffects-Geant4/Current Package"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/condo/Geant-4/RadEffects-Geant4/Current Package/build"

# Include any dependencies generated for this target.
include CMakeFiles/pack.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/pack.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/pack.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/pack.dir/flags.make

CMakeFiles/pack.dir/pack.cc.o: CMakeFiles/pack.dir/flags.make
CMakeFiles/pack.dir/pack.cc.o: /Users/condo/Geant-4/RadEffects-Geant4/Current\ Package/pack.cc
CMakeFiles/pack.dir/pack.cc.o: CMakeFiles/pack.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/condo/Geant-4/RadEffects-Geant4/Current Package/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/pack.dir/pack.cc.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/pack.dir/pack.cc.o -MF CMakeFiles/pack.dir/pack.cc.o.d -o CMakeFiles/pack.dir/pack.cc.o -c "/Users/condo/Geant-4/RadEffects-Geant4/Current Package/pack.cc"

CMakeFiles/pack.dir/pack.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/pack.dir/pack.cc.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/condo/Geant-4/RadEffects-Geant4/Current Package/pack.cc" > CMakeFiles/pack.dir/pack.cc.i

CMakeFiles/pack.dir/pack.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/pack.dir/pack.cc.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/condo/Geant-4/RadEffects-Geant4/Current Package/pack.cc" -o CMakeFiles/pack.dir/pack.cc.s

CMakeFiles/pack.dir/src/Action.cc.o: CMakeFiles/pack.dir/flags.make
CMakeFiles/pack.dir/src/Action.cc.o: /Users/condo/Geant-4/RadEffects-Geant4/Current\ Package/src/Action.cc
CMakeFiles/pack.dir/src/Action.cc.o: CMakeFiles/pack.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/condo/Geant-4/RadEffects-Geant4/Current Package/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/pack.dir/src/Action.cc.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/pack.dir/src/Action.cc.o -MF CMakeFiles/pack.dir/src/Action.cc.o.d -o CMakeFiles/pack.dir/src/Action.cc.o -c "/Users/condo/Geant-4/RadEffects-Geant4/Current Package/src/Action.cc"

CMakeFiles/pack.dir/src/Action.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/pack.dir/src/Action.cc.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/condo/Geant-4/RadEffects-Geant4/Current Package/src/Action.cc" > CMakeFiles/pack.dir/src/Action.cc.i

CMakeFiles/pack.dir/src/Action.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/pack.dir/src/Action.cc.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/condo/Geant-4/RadEffects-Geant4/Current Package/src/Action.cc" -o CMakeFiles/pack.dir/src/Action.cc.s

CMakeFiles/pack.dir/src/ConstructWorld.cc.o: CMakeFiles/pack.dir/flags.make
CMakeFiles/pack.dir/src/ConstructWorld.cc.o: /Users/condo/Geant-4/RadEffects-Geant4/Current\ Package/src/ConstructWorld.cc
CMakeFiles/pack.dir/src/ConstructWorld.cc.o: CMakeFiles/pack.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/condo/Geant-4/RadEffects-Geant4/Current Package/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/pack.dir/src/ConstructWorld.cc.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/pack.dir/src/ConstructWorld.cc.o -MF CMakeFiles/pack.dir/src/ConstructWorld.cc.o.d -o CMakeFiles/pack.dir/src/ConstructWorld.cc.o -c "/Users/condo/Geant-4/RadEffects-Geant4/Current Package/src/ConstructWorld.cc"

CMakeFiles/pack.dir/src/ConstructWorld.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/pack.dir/src/ConstructWorld.cc.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/condo/Geant-4/RadEffects-Geant4/Current Package/src/ConstructWorld.cc" > CMakeFiles/pack.dir/src/ConstructWorld.cc.i

CMakeFiles/pack.dir/src/ConstructWorld.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/pack.dir/src/ConstructWorld.cc.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/condo/Geant-4/RadEffects-Geant4/Current Package/src/ConstructWorld.cc" -o CMakeFiles/pack.dir/src/ConstructWorld.cc.s

CMakeFiles/pack.dir/src/DetectorMessenger.cc.o: CMakeFiles/pack.dir/flags.make
CMakeFiles/pack.dir/src/DetectorMessenger.cc.o: /Users/condo/Geant-4/RadEffects-Geant4/Current\ Package/src/DetectorMessenger.cc
CMakeFiles/pack.dir/src/DetectorMessenger.cc.o: CMakeFiles/pack.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/condo/Geant-4/RadEffects-Geant4/Current Package/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/pack.dir/src/DetectorMessenger.cc.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/pack.dir/src/DetectorMessenger.cc.o -MF CMakeFiles/pack.dir/src/DetectorMessenger.cc.o.d -o CMakeFiles/pack.dir/src/DetectorMessenger.cc.o -c "/Users/condo/Geant-4/RadEffects-Geant4/Current Package/src/DetectorMessenger.cc"

CMakeFiles/pack.dir/src/DetectorMessenger.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/pack.dir/src/DetectorMessenger.cc.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/condo/Geant-4/RadEffects-Geant4/Current Package/src/DetectorMessenger.cc" > CMakeFiles/pack.dir/src/DetectorMessenger.cc.i

CMakeFiles/pack.dir/src/DetectorMessenger.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/pack.dir/src/DetectorMessenger.cc.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/condo/Geant-4/RadEffects-Geant4/Current Package/src/DetectorMessenger.cc" -o CMakeFiles/pack.dir/src/DetectorMessenger.cc.s

CMakeFiles/pack.dir/src/Dose.cc.o: CMakeFiles/pack.dir/flags.make
CMakeFiles/pack.dir/src/Dose.cc.o: /Users/condo/Geant-4/RadEffects-Geant4/Current\ Package/src/Dose.cc
CMakeFiles/pack.dir/src/Dose.cc.o: CMakeFiles/pack.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/condo/Geant-4/RadEffects-Geant4/Current Package/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/pack.dir/src/Dose.cc.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/pack.dir/src/Dose.cc.o -MF CMakeFiles/pack.dir/src/Dose.cc.o.d -o CMakeFiles/pack.dir/src/Dose.cc.o -c "/Users/condo/Geant-4/RadEffects-Geant4/Current Package/src/Dose.cc"

CMakeFiles/pack.dir/src/Dose.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/pack.dir/src/Dose.cc.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/condo/Geant-4/RadEffects-Geant4/Current Package/src/Dose.cc" > CMakeFiles/pack.dir/src/Dose.cc.i

CMakeFiles/pack.dir/src/Dose.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/pack.dir/src/Dose.cc.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/condo/Geant-4/RadEffects-Geant4/Current Package/src/Dose.cc" -o CMakeFiles/pack.dir/src/Dose.cc.s

CMakeFiles/pack.dir/src/ElectronCapture.cc.o: CMakeFiles/pack.dir/flags.make
CMakeFiles/pack.dir/src/ElectronCapture.cc.o: /Users/condo/Geant-4/RadEffects-Geant4/Current\ Package/src/ElectronCapture.cc
CMakeFiles/pack.dir/src/ElectronCapture.cc.o: CMakeFiles/pack.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/condo/Geant-4/RadEffects-Geant4/Current Package/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/pack.dir/src/ElectronCapture.cc.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/pack.dir/src/ElectronCapture.cc.o -MF CMakeFiles/pack.dir/src/ElectronCapture.cc.o.d -o CMakeFiles/pack.dir/src/ElectronCapture.cc.o -c "/Users/condo/Geant-4/RadEffects-Geant4/Current Package/src/ElectronCapture.cc"

CMakeFiles/pack.dir/src/ElectronCapture.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/pack.dir/src/ElectronCapture.cc.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/condo/Geant-4/RadEffects-Geant4/Current Package/src/ElectronCapture.cc" > CMakeFiles/pack.dir/src/ElectronCapture.cc.i

CMakeFiles/pack.dir/src/ElectronCapture.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/pack.dir/src/ElectronCapture.cc.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/condo/Geant-4/RadEffects-Geant4/Current Package/src/ElectronCapture.cc" -o CMakeFiles/pack.dir/src/ElectronCapture.cc.s

CMakeFiles/pack.dir/src/ParticleGun.cc.o: CMakeFiles/pack.dir/flags.make
CMakeFiles/pack.dir/src/ParticleGun.cc.o: /Users/condo/Geant-4/RadEffects-Geant4/Current\ Package/src/ParticleGun.cc
CMakeFiles/pack.dir/src/ParticleGun.cc.o: CMakeFiles/pack.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/condo/Geant-4/RadEffects-Geant4/Current Package/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/pack.dir/src/ParticleGun.cc.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/pack.dir/src/ParticleGun.cc.o -MF CMakeFiles/pack.dir/src/ParticleGun.cc.o.d -o CMakeFiles/pack.dir/src/ParticleGun.cc.o -c "/Users/condo/Geant-4/RadEffects-Geant4/Current Package/src/ParticleGun.cc"

CMakeFiles/pack.dir/src/ParticleGun.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/pack.dir/src/ParticleGun.cc.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/condo/Geant-4/RadEffects-Geant4/Current Package/src/ParticleGun.cc" > CMakeFiles/pack.dir/src/ParticleGun.cc.i

CMakeFiles/pack.dir/src/ParticleGun.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/pack.dir/src/ParticleGun.cc.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/condo/Geant-4/RadEffects-Geant4/Current Package/src/ParticleGun.cc" -o CMakeFiles/pack.dir/src/ParticleGun.cc.s

CMakeFiles/pack.dir/src/PhysList.cc.o: CMakeFiles/pack.dir/flags.make
CMakeFiles/pack.dir/src/PhysList.cc.o: /Users/condo/Geant-4/RadEffects-Geant4/Current\ Package/src/PhysList.cc
CMakeFiles/pack.dir/src/PhysList.cc.o: CMakeFiles/pack.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/condo/Geant-4/RadEffects-Geant4/Current Package/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/pack.dir/src/PhysList.cc.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/pack.dir/src/PhysList.cc.o -MF CMakeFiles/pack.dir/src/PhysList.cc.o.d -o CMakeFiles/pack.dir/src/PhysList.cc.o -c "/Users/condo/Geant-4/RadEffects-Geant4/Current Package/src/PhysList.cc"

CMakeFiles/pack.dir/src/PhysList.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/pack.dir/src/PhysList.cc.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/condo/Geant-4/RadEffects-Geant4/Current Package/src/PhysList.cc" > CMakeFiles/pack.dir/src/PhysList.cc.i

CMakeFiles/pack.dir/src/PhysList.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/pack.dir/src/PhysList.cc.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/condo/Geant-4/RadEffects-Geant4/Current Package/src/PhysList.cc" -o CMakeFiles/pack.dir/src/PhysList.cc.s

CMakeFiles/pack.dir/src/Physics.cc.o: CMakeFiles/pack.dir/flags.make
CMakeFiles/pack.dir/src/Physics.cc.o: /Users/condo/Geant-4/RadEffects-Geant4/Current\ Package/src/Physics.cc
CMakeFiles/pack.dir/src/Physics.cc.o: CMakeFiles/pack.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/condo/Geant-4/RadEffects-Geant4/Current Package/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/pack.dir/src/Physics.cc.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/pack.dir/src/Physics.cc.o -MF CMakeFiles/pack.dir/src/Physics.cc.o.d -o CMakeFiles/pack.dir/src/Physics.cc.o -c "/Users/condo/Geant-4/RadEffects-Geant4/Current Package/src/Physics.cc"

CMakeFiles/pack.dir/src/Physics.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/pack.dir/src/Physics.cc.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/condo/Geant-4/RadEffects-Geant4/Current Package/src/Physics.cc" > CMakeFiles/pack.dir/src/Physics.cc.i

CMakeFiles/pack.dir/src/Physics.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/pack.dir/src/Physics.cc.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/condo/Geant-4/RadEffects-Geant4/Current Package/src/Physics.cc" -o CMakeFiles/pack.dir/src/Physics.cc.s

CMakeFiles/pack.dir/src/StepAction.cc.o: CMakeFiles/pack.dir/flags.make
CMakeFiles/pack.dir/src/StepAction.cc.o: /Users/condo/Geant-4/RadEffects-Geant4/Current\ Package/src/StepAction.cc
CMakeFiles/pack.dir/src/StepAction.cc.o: CMakeFiles/pack.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/condo/Geant-4/RadEffects-Geant4/Current Package/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/pack.dir/src/StepAction.cc.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/pack.dir/src/StepAction.cc.o -MF CMakeFiles/pack.dir/src/StepAction.cc.o.d -o CMakeFiles/pack.dir/src/StepAction.cc.o -c "/Users/condo/Geant-4/RadEffects-Geant4/Current Package/src/StepAction.cc"

CMakeFiles/pack.dir/src/StepAction.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/pack.dir/src/StepAction.cc.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/condo/Geant-4/RadEffects-Geant4/Current Package/src/StepAction.cc" > CMakeFiles/pack.dir/src/StepAction.cc.i

CMakeFiles/pack.dir/src/StepAction.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/pack.dir/src/StepAction.cc.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/condo/Geant-4/RadEffects-Geant4/Current Package/src/StepAction.cc" -o CMakeFiles/pack.dir/src/StepAction.cc.s

CMakeFiles/pack.dir/src/event.cc.o: CMakeFiles/pack.dir/flags.make
CMakeFiles/pack.dir/src/event.cc.o: /Users/condo/Geant-4/RadEffects-Geant4/Current\ Package/src/event.cc
CMakeFiles/pack.dir/src/event.cc.o: CMakeFiles/pack.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/condo/Geant-4/RadEffects-Geant4/Current Package/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/pack.dir/src/event.cc.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/pack.dir/src/event.cc.o -MF CMakeFiles/pack.dir/src/event.cc.o.d -o CMakeFiles/pack.dir/src/event.cc.o -c "/Users/condo/Geant-4/RadEffects-Geant4/Current Package/src/event.cc"

CMakeFiles/pack.dir/src/event.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/pack.dir/src/event.cc.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/condo/Geant-4/RadEffects-Geant4/Current Package/src/event.cc" > CMakeFiles/pack.dir/src/event.cc.i

CMakeFiles/pack.dir/src/event.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/pack.dir/src/event.cc.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/condo/Geant-4/RadEffects-Geant4/Current Package/src/event.cc" -o CMakeFiles/pack.dir/src/event.cc.s

CMakeFiles/pack.dir/src/run.cc.o: CMakeFiles/pack.dir/flags.make
CMakeFiles/pack.dir/src/run.cc.o: /Users/condo/Geant-4/RadEffects-Geant4/Current\ Package/src/run.cc
CMakeFiles/pack.dir/src/run.cc.o: CMakeFiles/pack.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/Users/condo/Geant-4/RadEffects-Geant4/Current Package/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/pack.dir/src/run.cc.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/pack.dir/src/run.cc.o -MF CMakeFiles/pack.dir/src/run.cc.o.d -o CMakeFiles/pack.dir/src/run.cc.o -c "/Users/condo/Geant-4/RadEffects-Geant4/Current Package/src/run.cc"

CMakeFiles/pack.dir/src/run.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/pack.dir/src/run.cc.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/condo/Geant-4/RadEffects-Geant4/Current Package/src/run.cc" > CMakeFiles/pack.dir/src/run.cc.i

CMakeFiles/pack.dir/src/run.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/pack.dir/src/run.cc.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/condo/Geant-4/RadEffects-Geant4/Current Package/src/run.cc" -o CMakeFiles/pack.dir/src/run.cc.s

# Object files for target pack
pack_OBJECTS = \
"CMakeFiles/pack.dir/pack.cc.o" \
"CMakeFiles/pack.dir/src/Action.cc.o" \
"CMakeFiles/pack.dir/src/ConstructWorld.cc.o" \
"CMakeFiles/pack.dir/src/DetectorMessenger.cc.o" \
"CMakeFiles/pack.dir/src/Dose.cc.o" \
"CMakeFiles/pack.dir/src/ElectronCapture.cc.o" \
"CMakeFiles/pack.dir/src/ParticleGun.cc.o" \
"CMakeFiles/pack.dir/src/PhysList.cc.o" \
"CMakeFiles/pack.dir/src/Physics.cc.o" \
"CMakeFiles/pack.dir/src/StepAction.cc.o" \
"CMakeFiles/pack.dir/src/event.cc.o" \
"CMakeFiles/pack.dir/src/run.cc.o"

# External object files for target pack
pack_EXTERNAL_OBJECTS =

pack: CMakeFiles/pack.dir/pack.cc.o
pack: CMakeFiles/pack.dir/src/Action.cc.o
pack: CMakeFiles/pack.dir/src/ConstructWorld.cc.o
pack: CMakeFiles/pack.dir/src/DetectorMessenger.cc.o
pack: CMakeFiles/pack.dir/src/Dose.cc.o
pack: CMakeFiles/pack.dir/src/ElectronCapture.cc.o
pack: CMakeFiles/pack.dir/src/ParticleGun.cc.o
pack: CMakeFiles/pack.dir/src/PhysList.cc.o
pack: CMakeFiles/pack.dir/src/Physics.cc.o
pack: CMakeFiles/pack.dir/src/StepAction.cc.o
pack: CMakeFiles/pack.dir/src/event.cc.o
pack: CMakeFiles/pack.dir/src/run.cc.o
pack: CMakeFiles/pack.dir/build.make
pack: /usr/local/lib/libG4Tree.dylib
pack: /usr/local/lib/libG4FR.dylib
pack: /usr/local/lib/libG4GMocren.dylib
pack: /usr/local/lib/libG4visHepRep.dylib
pack: /usr/local/lib/libG4RayTracer.dylib
pack: /usr/local/lib/libG4VRML.dylib
pack: /usr/local/lib/libG4ToolsSG.dylib
pack: /usr/local/lib/libG4OpenGL.dylib
pack: /usr/local/lib/libG4visQt3D.dylib
pack: /usr/local/lib/libG4vis_management.dylib
pack: /usr/local/lib/libG4modeling.dylib
pack: /usr/local/lib/libG4interfaces.dylib
pack: /usr/local/lib/libG4mctruth.dylib
pack: /usr/local/lib/libG4geomtext.dylib
pack: /usr/local/lib/libG4gdml.dylib
pack: /usr/local/lib/libG4error_propagation.dylib
pack: /usr/local/lib/libG4readout.dylib
pack: /usr/local/lib/libG4physicslists.dylib
pack: /usr/local/lib/libG4run.dylib
pack: /usr/local/lib/libG4event.dylib
pack: /usr/local/lib/libG4tracking.dylib
pack: /usr/local/lib/libG4parmodels.dylib
pack: /usr/local/lib/libG4processes.dylib
pack: /usr/local/lib/libG4digits_hits.dylib
pack: /usr/local/lib/libG4track.dylib
pack: /usr/local/lib/libG4particles.dylib
pack: /usr/local/lib/libG4geometry.dylib
pack: /usr/local/lib/libG4materials.dylib
pack: /usr/local/lib/libG4graphics_reps.dylib
pack: /Library/Developer/CommandLineTools/SDKs/MacOSX14.2.sdk/System/Library/Frameworks/OpenGL.framework
pack: /opt/homebrew/opt/qt@5/lib/QtOpenGL.framework/QtOpenGL
pack: /usr/X11R6/lib/libXmu.dylib
pack: /opt/homebrew/lib/libXext.dylib
pack: /usr/X11R6/lib/libXt.dylib
pack: /usr/X11R6/lib/libICE.dylib
pack: /usr/X11R6/lib/libSM.dylib
pack: /opt/homebrew/lib/libX11.dylib
pack: /usr/X11R6/lib/libGL.dylib
pack: /opt/homebrew/opt/qt@5/lib/QtWidgets.framework/QtWidgets
pack: /opt/homebrew/opt/qt@5/lib/QtGui.framework/QtGui
pack: /opt/homebrew/opt/qt@5/lib/QtCore.framework/QtCore
pack: /opt/homebrew/lib/libxerces-c.dylib
pack: /usr/local/lib/libG4analysis.dylib
pack: /Library/Developer/CommandLineTools/SDKs/MacOSX14.2.sdk/usr/lib/libexpat.tbd
pack: /usr/local/lib/libG4zlib.dylib
pack: /usr/local/lib/libG4intercoms.dylib
pack: /usr/local/lib/libG4global.dylib
pack: /usr/local/lib/libG4clhep.dylib
pack: /usr/local/lib/libG4ptl.2.3.3.dylib
pack: CMakeFiles/pack.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir="/Users/condo/Geant-4/RadEffects-Geant4/Current Package/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_13) "Linking CXX executable pack"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pack.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/pack.dir/build: pack
.PHONY : CMakeFiles/pack.dir/build

CMakeFiles/pack.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/pack.dir/cmake_clean.cmake
.PHONY : CMakeFiles/pack.dir/clean

CMakeFiles/pack.dir/depend:
	cd "/Users/condo/Geant-4/RadEffects-Geant4/Current Package/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/condo/Geant-4/RadEffects-Geant4/Current Package" "/Users/condo/Geant-4/RadEffects-Geant4/Current Package" "/Users/condo/Geant-4/RadEffects-Geant4/Current Package/build" "/Users/condo/Geant-4/RadEffects-Geant4/Current Package/build" "/Users/condo/Geant-4/RadEffects-Geant4/Current Package/build/CMakeFiles/pack.dir/DependInfo.cmake" "--color=$(COLOR)"
.PHONY : CMakeFiles/pack.dir/depend

