cmake_minimum_required(VERSION 3.9)
set(CMAKE_VERBOSE_MAKEFILE ON)
project(Windows_API_Experiments)

#================================#
#  Global Configuration          #
#================================#

# Set C++ 14 Standard
set(CMAKE_CXX_STANDARD 17)

# ===>>>> TARGET base64: Windows API base 64 facilities    
# Uses: Wincrypt API  crypt32.dll 
#--------------------------------------------------------------
add_executable(base64 src/base64.cpp)
# Link against crypt32.dll (crypt32.lib)
target_link_libraries(base64 PUBLIC crypt32)

# ====>>>> TARGET: guiBasic1 - Minimal graphical user interface - WinMain entry point, 
# window subsystem 
# Flag WIN32 => Compiles program to Windows subsystem (without console window)
# Reference: https://stackoverflow.com/questions/33400777/
#---------------------------------------------------------------
add_executable(guiBasic1 WIN32 src/guiBasic1.cpp)
# target_link_libraries(guiBasic1 user32 gdi32)


add_executable(guiBasicNOWinmain WIN32 src/guiBasicNOWinmain.cpp)
# target_link_libraries(guiBasicNOWinmain user32 gdi32)
set_target_properties(guiBasicNOWinmain PROPERTIES LINK_FLAGS "/entry:mainCRTStartup")

#==========>>> Helper Targets <<<====================#

# Copy targets to ./ - Directory where is this file CMakeLists.txt (project top level dir)
install(TARGETS base64 
				guiBasic1 
				guiBasicNOWinmain 
		DESTINATION ${CMAKE_CURRENT_LIST_DIR}/bin)
