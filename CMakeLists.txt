CMAKE_MINIMUM_REQUIRED(VERSION 3.15)

if (WIN32)
set(VULKAN_SDK_PATH "C:/VulkanSDK/1.3.239.0")
set (OGL_SDK_PATH)
ENDIF()

project(OUGDASM_OpenGL VERSION 0.1.0)
project(OUGDASM_Vulkan VERSION 0.1.0)

add_executable(OUGDASM_OpenGL ogl/main.cpp)
add_executable(OUGDASM_Vulkan vk/main.cpp)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

configure_file(GlobalConfig.h.in GlobalConfig.h)

IF (WIN32)
    FILE(APPEND ${PROJECT_BINARY_DIR}/GlobalConfig.h "#include \"windows.h\"\n")
ENDIF()

target_include_directories(OUGDASM_OpenGL PUBLIC ${PROJECT_BINARY_DIR})
target_include_directories(OUGDASM_Vulkan PUBLIC ${PROJECT_BINARY_DIR})

set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")

target_compile_options(OUGDASM_Vulkan INTERFACE
    "$<${gcc_like_cxx}:-Wextra;-Wshadow;-Wformat=2;-Wunused>"
    "$<${msvc_cxx}:/W3>"
)

target_compile_options(OUGDASM_OpenGL INTERFACE
    "$<${gcc_like_cxx}:$<BUILD_INTERFACE:${GENERAL_FLAGS_GCC}>>"
    "$<${msvc_cxx}:$<BUILD_INTERFACE:${GENERAL_FLAGS_MSVC}>"
)

if (WIN32 AND MSVC) # Windows Visual Studio
    TARGET_LINK_LIBRARIES(OUGDASM_Vulkan PRIVATE #VULKAN
        "${CMAKE_SOURCE_DIR}/libwin64/glfw_vs22/glfw3.lib"
        "${CMAKE_SOURCE_DIR}/libwin64/glfw_vs22/glfw3dll.lib"
        "${CMAKE_SOURCE_DIR}/libwin64/glfw_vs22/glfw3mt.lib"
        "${VULKAN_SDK_PATH}/Lib/vulkan-1.lib"
    )
    TARGET_LINK_LIBRARIES(OUGDASM_OpenGL PRIVATE #OPENGL

    )
ELSE(WIN32) # Windows MinGW
    TARGET_LINK_LIBRARIES(OUGDASM_Vulkan PRIVATE #VULKAN
        "${CMAKE_SOURCE_DIR}/libwin64/glfw_mingw/libglfw3.a"
        "${CMAKE_SOURCE_DIR}/libwin64/glfw_mingw/libglfw3dll.a"
        "${VULKAN_SDK_PATH}/Lib/vulkan-1.lib"
    )
    TARGET_LINK_LIBRARIES(OUGDASM_OpenGL PRIVATE #OPENGL

    )
endif()

if (UNIX) #UNIX (assumes G++!!!!)
    TARGET_LINK_LIBRARIES(OUGDASM_Vulkan PRIVATE #VULKAN

    )
    TARGET_LINK_LIBRARIES(OUGDASM_OpenGL PRIVATE #OPENGL

    )
endif()

target_include_directories(OUGDASM_Vulkan PRIVATE
    "${CMAKE_SOURCE_DIR}/include/glm"
    "${CMAKE_SOURCE_DIR}/include/"
    "${VULKAN_SDK_PATH}/Include/"
)