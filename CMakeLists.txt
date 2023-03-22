CMAKE_MINIMUM_REQUIRED(VERSION 3.15)


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

set(GENERAL_FLAGS_GCC, -Wextra;-Wshadow;-Wformat=2;-Wunused)
set(VK_FLAGS_GCC -lglfw;-lvulkan;-ldl;-lpthread;-lX11;-lXxf86vm;-lXrandr;-lXi)
set(OGL_FLAGS_GCC, -lGL;lglu32;-lopengl32;-lfreeglut)
set(GENERAL_FLAGS_MSVC, -W3)

target_compile_options(OUGDASM_Vulkan INTERFACE
    "$<${gcc_like_cxx}:-lglfw;-lvulkan;-ldl;-lpthread;-lX11;-lXxf86vm;-lXrandr;-lXi>"
    "$<${msvc_cxx}:${GENERAL_FLAGS_MSVC}>"
)

target_compile_options(OUGDASM_OpenGL INTERFACE
    "$<${gcc_like_cxx}:$<BUILD_INTERFACE:${GENERAL_FLAGS_GCC}>>"
    "$<${msvc_cxx}:$<BUILD_INTERFACE:${GENERAL_FLAGS_MSVC}>"
)