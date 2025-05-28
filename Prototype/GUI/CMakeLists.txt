cmake_minimum_required(VERSION 3.26)

project(GuiPrototype VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)


add_executable(GuiPrototype "Source/main.cpp")

target_compile_options(GuiPrototype
	PUBLIC ${GTKMM_CFLAGS_OTHER}
)

target_link_libraries(GuiPrototype ${GTKMM_LIBRARIES})

if(WIN32)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
	# Optional: Copy necessary DLLs if needed (uncomment if you face runtime issues)
	# file(GLOB GTK_DLLS "${GTKMM_LIBDIR}/*.dll")
	# file(COPY ${GTK_DLLS} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif()
