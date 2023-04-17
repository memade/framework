cmake_minimum_required(VERSION 3.25.1)

#add_subdirectory(${SOLUTION_ROOT_DIR}/projects/framework/)
#set_target_properties(tests PROPERTIES FOLDER "tests")
#set_target_properties(${origin_entry_name} PROPERTIES FOLDER "projects")
message(STATIC "${CMAKE_CURRENT_SOURCE_DIR}")

file(GLOB entries src/*)
foreach(entry ${entries})
 if(NOT (IS_DIRECTORY ${entry}))
  continue()
 endif(NOT (IS_DIRECTORY ${entry}))
 
 get_filename_component(entry_name "${entry}" NAME)
 
 file(GLOB IS_EMPTY_DIR "${entry}/*.c" "${entry}/*.cc" "${entry}/*.cpp")	
 list(LENGTH IS_EMPTY_DIR IS_EMPTY_DIR_LEN)
 if(IS_EMPTY_DIR_LEN EQUAL 0)
  message(STATIC empty dir is ${entry})
  continue()
 endif(IS_EMPTY_DIR_LEN EQUAL 0)

 #message(STATIC "path:${entry} name:${entry_name}")
 
 #====================================================================================
 if(${entry_name} STREQUAL "main")
  file(GLOB SRCS "${entry}/*.c" "${entry}/*.cc" "${entry}/*.cpp")	
  file(GLOB HEADS "${entry}/*.h" "${entry}/*.hpp")	
  set(SOURCES
  ${SRCS}
  ${HEADS}
  )
  add_executable(${entry_name} ${SOURCES})
  set_target_properties(${entry_name} PROPERTIES LINK_FLAGS "/SUBSYSTEM:CONSOLE")
  if(MSVC AND ENABLE_MSVC_CRT_MT)
  set_property(TARGET ${entry_name} PROPERTY
  MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
  endif(MSVC AND ENABLE_MSVC_CRT_MT)
  target_include_directories(${entry_name}
  PRIVATE 
  ${SOLUTION_INCLUDE_DIR}
  ${SOLUTION_ROOT_DIR}/third_party/
  )
  target_link_directories(${entry_name}
  PRIVATE
  ${SOLUTION_ROOT_DIR}/libs/runtimes/${CMAKE_VS_PLATFORM_NAME}/
  ${SOLUTION_ROOT_DIR}/libs/third_party/${CMAKE_VS_PLATFORM_NAME}/
  )
 #====================================================================================
 elseif(${entry_name} STREQUAL "database")
  file(GLOB SRCS "${entry}/*.c" "${entry}/*.cc" "${entry}/*.cpp")	
  file(GLOB HEADS "${entry}/*.h" "${entry}/*.hpp")	
  set(SOURCES
  ${SRCS}
  ${HEADS}
  )
  
  add_library(${entry_name} STATIC ${SOURCES})
  
  if(MSVC AND ENABLE_MSVC_CRT_MT)
  set_property(TARGET ${entry_name} PROPERTY
  MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
  endif(MSVC AND ENABLE_MSVC_CRT_MT)
    
  target_include_directories(${entry_name}
  PRIVATE 
  ${SOLUTION_INCLUDE_DIR}
  ${SOLUTION_ROOT_DIR}/third_party/
  )
  target_link_directories(${entry_name}
  PRIVATE
  ${SOLUTION_ROOT_DIR}/libs/runtimes/${CMAKE_VS_PLATFORM_NAME}/
  ${SOLUTION_ROOT_DIR}/libs/third_party/${CMAKE_VS_PLATFORM_NAME}/
  )
 
 #====================================================================================
 elseif(${entry_name} STREQUAL "net")
 
 #====================================================================================
 elseif(${entry_name} STREQUAL "pipe")
  #add_subdirectory(${entry})
  #set_target_properties(${entry_name} PROPERTIES FOLDER "projects")  
  #message(STATIC "${entry}/")
 #====================================================================================
 endif()
 
 if(EXISTS ${entry}/stdafx.h AND EXISTS ${entry}/stdafx.cpp)
  MSVC_USE_PCH(${entry_name} ${entry_path}/stdafx.h ${entry_path}/stdafx.cpp)
 endif(EXISTS ${entry}/stdafx.h AND EXISTS ${entry}/stdafx.cpp)
 
 set_target_properties(${entry_name} PROPERTIES FOLDER "projects/framework/")
 

endforeach(entry)