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
CMAKE_COMMAND = /u/group/clas12/packages/cmake/3.15.2/bin/cmake

# The command to remove a file.
RM = /u/group/clas12/packages/cmake/3.15.2/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/erins/work_erins/repos/rgm/NeutronEfficiency

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/erins/work_erins/repos/rgm/NeutronEfficiency/build

# Include any dependencies generated for this target.
include CMakeFiles/neff_h_epin.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/neff_h_epin.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/neff_h_epin.dir/flags.make

CMakeFiles/neff_h_epin.dir/neff_h_epin.cpp.o: CMakeFiles/neff_h_epin.dir/flags.make
CMakeFiles/neff_h_epin.dir/neff_h_epin.cpp.o: ../neff_h_epin.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/erins/work_erins/repos/rgm/NeutronEfficiency/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/neff_h_epin.dir/neff_h_epin.cpp.o"
	/apps/gcc/9.2.0/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/neff_h_epin.dir/neff_h_epin.cpp.o -c /home/erins/work_erins/repos/rgm/NeutronEfficiency/neff_h_epin.cpp

CMakeFiles/neff_h_epin.dir/neff_h_epin.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/neff_h_epin.dir/neff_h_epin.cpp.i"
	/apps/gcc/9.2.0/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/erins/work_erins/repos/rgm/NeutronEfficiency/neff_h_epin.cpp > CMakeFiles/neff_h_epin.dir/neff_h_epin.cpp.i

CMakeFiles/neff_h_epin.dir/neff_h_epin.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/neff_h_epin.dir/neff_h_epin.cpp.s"
	/apps/gcc/9.2.0/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/erins/work_erins/repos/rgm/NeutronEfficiency/neff_h_epin.cpp -o CMakeFiles/neff_h_epin.dir/neff_h_epin.cpp.s

# Object files for target neff_h_epin
neff_h_epin_OBJECTS = \
"CMakeFiles/neff_h_epin.dir/neff_h_epin.cpp.o"

# External object files for target neff_h_epin
neff_h_epin_EXTERNAL_OBJECTS =

neff_h_epin: CMakeFiles/neff_h_epin.dir/neff_h_epin.cpp.o
neff_h_epin: CMakeFiles/neff_h_epin.dir/build.make
neff_h_epin: /u/site/12gev_phys/2.5/Linux_CentOS7.7.1908-gcc9.2.0/root/6.24.06/lib/libCore.so
neff_h_epin: /u/site/12gev_phys/2.5/Linux_CentOS7.7.1908-gcc9.2.0/root/6.24.06/lib/libImt.so
neff_h_epin: /u/site/12gev_phys/2.5/Linux_CentOS7.7.1908-gcc9.2.0/root/6.24.06/lib/libRIO.so
neff_h_epin: /u/site/12gev_phys/2.5/Linux_CentOS7.7.1908-gcc9.2.0/root/6.24.06/lib/libNet.so
neff_h_epin: /u/site/12gev_phys/2.5/Linux_CentOS7.7.1908-gcc9.2.0/root/6.24.06/lib/libHist.so
neff_h_epin: /u/site/12gev_phys/2.5/Linux_CentOS7.7.1908-gcc9.2.0/root/6.24.06/lib/libGraf.so
neff_h_epin: /u/site/12gev_phys/2.5/Linux_CentOS7.7.1908-gcc9.2.0/root/6.24.06/lib/libGraf3d.so
neff_h_epin: /u/site/12gev_phys/2.5/Linux_CentOS7.7.1908-gcc9.2.0/root/6.24.06/lib/libGpad.so
neff_h_epin: /u/site/12gev_phys/2.5/Linux_CentOS7.7.1908-gcc9.2.0/root/6.24.06/lib/libROOTDataFrame.so
neff_h_epin: /u/site/12gev_phys/2.5/Linux_CentOS7.7.1908-gcc9.2.0/root/6.24.06/lib/libTree.so
neff_h_epin: /u/site/12gev_phys/2.5/Linux_CentOS7.7.1908-gcc9.2.0/root/6.24.06/lib/libTreePlayer.so
neff_h_epin: /u/site/12gev_phys/2.5/Linux_CentOS7.7.1908-gcc9.2.0/root/6.24.06/lib/libRint.so
neff_h_epin: /u/site/12gev_phys/2.5/Linux_CentOS7.7.1908-gcc9.2.0/root/6.24.06/lib/libPostscript.so
neff_h_epin: /u/site/12gev_phys/2.5/Linux_CentOS7.7.1908-gcc9.2.0/root/6.24.06/lib/libMatrix.so
neff_h_epin: /u/site/12gev_phys/2.5/Linux_CentOS7.7.1908-gcc9.2.0/root/6.24.06/lib/libPhysics.so
neff_h_epin: /u/site/12gev_phys/2.5/Linux_CentOS7.7.1908-gcc9.2.0/root/6.24.06/lib/libMathCore.so
neff_h_epin: /u/site/12gev_phys/2.5/Linux_CentOS7.7.1908-gcc9.2.0/root/6.24.06/lib/libThread.so
neff_h_epin: /u/site/12gev_phys/2.5/Linux_CentOS7.7.1908-gcc9.2.0/root/6.24.06/lib/libMultiProc.so
neff_h_epin: /u/site/12gev_phys/2.5/Linux_CentOS7.7.1908-gcc9.2.0/root/6.24.06/lib/libROOTVecOps.so
neff_h_epin: source/libeventcut.a
neff_h_epin: /u/site/12gev_phys/2.5/Linux_CentOS7.7.1908-gcc9.2.0/root/6.24.06/lib/libCore.so
neff_h_epin: /u/site/12gev_phys/2.5/Linux_CentOS7.7.1908-gcc9.2.0/root/6.24.06/lib/libImt.so
neff_h_epin: /u/site/12gev_phys/2.5/Linux_CentOS7.7.1908-gcc9.2.0/root/6.24.06/lib/libRIO.so
neff_h_epin: /u/site/12gev_phys/2.5/Linux_CentOS7.7.1908-gcc9.2.0/root/6.24.06/lib/libNet.so
neff_h_epin: /u/site/12gev_phys/2.5/Linux_CentOS7.7.1908-gcc9.2.0/root/6.24.06/lib/libHist.so
neff_h_epin: /u/site/12gev_phys/2.5/Linux_CentOS7.7.1908-gcc9.2.0/root/6.24.06/lib/libGraf.so
neff_h_epin: /u/site/12gev_phys/2.5/Linux_CentOS7.7.1908-gcc9.2.0/root/6.24.06/lib/libGraf3d.so
neff_h_epin: /u/site/12gev_phys/2.5/Linux_CentOS7.7.1908-gcc9.2.0/root/6.24.06/lib/libGpad.so
neff_h_epin: /u/site/12gev_phys/2.5/Linux_CentOS7.7.1908-gcc9.2.0/root/6.24.06/lib/libROOTDataFrame.so
neff_h_epin: /u/site/12gev_phys/2.5/Linux_CentOS7.7.1908-gcc9.2.0/root/6.24.06/lib/libTree.so
neff_h_epin: /u/site/12gev_phys/2.5/Linux_CentOS7.7.1908-gcc9.2.0/root/6.24.06/lib/libTreePlayer.so
neff_h_epin: /u/site/12gev_phys/2.5/Linux_CentOS7.7.1908-gcc9.2.0/root/6.24.06/lib/libRint.so
neff_h_epin: /u/site/12gev_phys/2.5/Linux_CentOS7.7.1908-gcc9.2.0/root/6.24.06/lib/libPostscript.so
neff_h_epin: /u/site/12gev_phys/2.5/Linux_CentOS7.7.1908-gcc9.2.0/root/6.24.06/lib/libMatrix.so
neff_h_epin: /u/site/12gev_phys/2.5/Linux_CentOS7.7.1908-gcc9.2.0/root/6.24.06/lib/libPhysics.so
neff_h_epin: /u/site/12gev_phys/2.5/Linux_CentOS7.7.1908-gcc9.2.0/root/6.24.06/lib/libMathCore.so
neff_h_epin: /u/site/12gev_phys/2.5/Linux_CentOS7.7.1908-gcc9.2.0/root/6.24.06/lib/libThread.so
neff_h_epin: /u/site/12gev_phys/2.5/Linux_CentOS7.7.1908-gcc9.2.0/root/6.24.06/lib/libMultiProc.so
neff_h_epin: /u/site/12gev_phys/2.5/Linux_CentOS7.7.1908-gcc9.2.0/root/6.24.06/lib/libROOTVecOps.so
neff_h_epin: CMakeFiles/neff_h_epin.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/erins/work_erins/repos/rgm/NeutronEfficiency/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable neff_h_epin"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/neff_h_epin.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/neff_h_epin.dir/build: neff_h_epin

.PHONY : CMakeFiles/neff_h_epin.dir/build

CMakeFiles/neff_h_epin.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/neff_h_epin.dir/cmake_clean.cmake
.PHONY : CMakeFiles/neff_h_epin.dir/clean

CMakeFiles/neff_h_epin.dir/depend:
	cd /home/erins/work_erins/repos/rgm/NeutronEfficiency/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/erins/work_erins/repos/rgm/NeutronEfficiency /home/erins/work_erins/repos/rgm/NeutronEfficiency /home/erins/work_erins/repos/rgm/NeutronEfficiency/build /home/erins/work_erins/repos/rgm/NeutronEfficiency/build /home/erins/work_erins/repos/rgm/NeutronEfficiency/build/CMakeFiles/neff_h_epin.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/neff_h_epin.dir/depend

