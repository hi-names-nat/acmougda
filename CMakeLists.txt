CMAKE_MINIMUM_REQUIRED(VERSION 3.15)

project(OUGDASM_Vulkan VERSION 0.1.0)

add_executable(OUGDASM_Vulkan vk/main.cpp)

find_package(Vulkan)
get_filename_component(Vulkan_LIBRARY_DIR ${Vulkan_LIBRARY} DIRECTORY)
message(STATUS "Vulkan FOUND = ${Vulkan_FOUND}")
message(STATUS "Vulkan Includes = ${Vulkan_INCLUDE_DIR}")
message(STATUS "Vulkan Lib Dir = ${Vulkan_LIBRARY_DIR}")
message(STATUS "Vulkan Lib = ${Vulkan_LIBRARY}")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

configure_file(GlobalConfig.h.in GlobalConfig.h)

IF (WIN32)
    FILE(APPEND ${PROJECT_BINARY_DIR}/GlobalConfig.h "#include \"windows.h\"\n")
    set_target_properties(OUGDASM_Vulkan PROPERTIES OUTPUT_NAME "ougdasm_vk")
ENDIF()
IF (UNIX)
    set_target_properties(OUGDASM_Vulkan PROPERTIES OUTPUT_NAME "ougdasm_vk.o")
ENDIF()

set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")

target_compile_options(OUGDASM_Vulkan INTERFACE
        # O2 is heavily suggested for any sort of building, as Vulkan without it is very inefficient.
        # However O2 might rewrite your code, so it's not perfect for debugging.
    "$<${gcc_like_cxx}:-Wextra;-Wshadow;-Wformat=2;-Wunused;-O2>"
    "$<${msvc_cxx}:/W3>"
)

if (WIN32 AND MSVC) # Windows Visual Studio
    TARGET_LINK_LIBRARIES(OUGDASM_Vulkan PRIVATE #VULKAN
        "${CMAKE_SOURCE_DIR}/libwin64/glfw/lib-vc2022/glfw3.lib"
        "${CMAKE_SOURCE_DIR}/libwin64/glfw/lib-vc2022/glfw3dll.lib"
        "${CMAKE_SOURCE_DIR}/libwin64/glfw/lib-vc2022/glfw3mt.lib"
        "${Vulkan_LIBRARY}"

    )
ELSE()
    if(WIN32) # Windows MinGW
        TARGET_LINK_LIBRARIES(OUGDASM_Vulkan PRIVATE #VULKAN
            "${CMAKE_SOURCE_DIR}/libwin64/glfw/lib-mingw-w64/libglfw3.a"
            "${CMAKE_SOURCE_DIR}/libwin64/glfw/lib-mingw-w64/libglfw3dll.a"
            "${Vulkan_LIBRARY}"
        )
    endif()
endif()

if (UNIX) #Unix G++
    TARGET_LINK_LIBRARIES(OUGDASM_Vulkan PRIVATE #VULKAN
        "${CMAKE_SOURCE_DIR}/libunix/libglfw.so"
        "${CMAKE_SOURCE_DIR}/libunix/libglfw.so.3"
        "${CMAKE_SOURCE_DIR}/libunix/libglfw.so.3.3"
        "${Vulkan_LIBRARY}"
    )
endif()

target_include_directories(OUGDASM_Vulkan PRIVATE
    "${CMAKE_SOURCE_DIR}/include/"
    "${Vulkan_INCLUDE_DIR}"
)