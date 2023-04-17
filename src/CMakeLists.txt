function(install_sub_project entry_path entry_name)
		file(GLOB SRCS "${entry_path}/*.c" "${entry_path}/*.cc" "${entry_path}/*.cpp")	
		file(GLOB HEADS "${entry_path}/*.h" "${entry_path}/*.hpp")	
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
		#[[
		target_include_directories(${entry_name} 
		PRIVATE 
		${SOLUTION_INCLUDE_DIR}
		${SOLUTION_ROOT_DIR}/third_party/
		${SOLUTION_ROOT_DIR}/third_party/wxWidgets/wxWidgets-3.2.2.1/include/
		${SOLUTION_ROOT_DIR}/third_party/wxWidgets/wxWidgets-3.2.2.1/include/msvc/
		)
		
		set(WXLIB_DIR ${SOLUTION_ROOT_DIR}/third_party/wxWidgets/wxWidgets-3.2.2.1/lib/vc_lib/)
		if(${CMAKE_VS_PLATFORM_NAME} STREQUAL "x64")
		set(WXLIB_DIR ${SOLUTION_ROOT_DIR}/third_party/wxWidgets/wxWidgets-3.2.2.1/lib/vc_x64_lib/)
		endif(${CMAKE_VS_PLATFORM_NAME} STREQUAL "x64")
		
		target_link_directories(${entry_name} 
		PRIVATE 
		${SOLUTION_ROOT_DIR}/third_party/wxWidgets/wxWidgets-3.2.2.1/lib/
		${WXLIB_DIR}/
		${SOLUTION_ROOT_DIR}/libs/runtimes/${CMAKE_VS_PLATFORM_NAME}/
		${SOLUTION_ROOT_DIR}/libs/third_party/${CMAKE_VS_PLATFORM_NAME}/
		)
		]]
endfunction(install_sub_project entry_path entry_name)


file(GLOB entries *)
foreach(entry ${entries})
	if(IS_DIRECTORY ${entry})
		get_filename_component(origin_entry_name "${entry}" NAME)

		install_sub_project(${entry} ${origin_entry_name})
		
		if(${origin_entry_name} STREQUAL "data")
			target_include_directories(${origin_entry_name} 
			PRIVATE 
			${SOLUTION_INCLUDE_DIR}
			${SOLUTION_ROOT_DIR}/third_party/
			)
			target_link_directories(${origin_entry_name} 
			PRIVATE 
			${SOLUTION_ROOT_DIR}/libs/runtimes/${CMAKE_VS_PLATFORM_NAME}/
			${SOLUTION_ROOT_DIR}/libs/third_party/${CMAKE_VS_PLATFORM_NAME}/
			)		
		elseif(${origin_entry_name} STREQUAL "unknown")

		endif()

			
		set_target_properties(${origin_entry_name} PROPERTIES FOLDER "tests")
	 #message(STATUS "current filename ${origin_entry_name}") 
		#message(STATUS "current path ${entry}")
 endif()
endforeach(entry)
