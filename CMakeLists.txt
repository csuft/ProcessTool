CMAKE_MINIMUM_REQUIRED(VERSION 3.6)
PROJECT(ProcessTool CXX)

################################################################################
# Compiler and linker options
ADD_DEFINITIONS(-Wall -DWIN32_LEAN_AND_MEAN -DUNICODE)

SET(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTORCC ON) 
SET(CMAKE_CXX_STANDARD 11) 

################################################################################
# Sources and libraries
FILE(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
FILE(GLOB HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h") 
 
SET(RESOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/qapplist.qrc) 
 
FIND_PACKAGE(Qt5 COMPONENTS Core Widgets Xml Gui REQUIRED)  
  
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR}) 
################################################################################
# Compile target
ADD_EXECUTABLE ( ${PROJECT_NAME} 
				${SOURCE_FILES} 
				${HEADER_FILES} 
				${RESOURCES})
# https://www.kdab.com/using-cmake-with-qt-5/
qt5_use_modules(${PROJECT_NAME} Core Widgets Gui Xml)  