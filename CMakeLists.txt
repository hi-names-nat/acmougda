CMAKE_MINIMUM_REQUIRED(VERSION 3.15)

if (WIN32)
set(VULKAN_SDK_PATH "C:/VulkanSDK/1.3.239.0")
ENDIF()

project(OUGDASM_Vulkan VERSION 0.1.0)

add_executable(OUGDASM_Vulkan vk/main.cpp)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

configure_file(GlobalConfig.h.in GlobalConfig.h)

IF (WIN32)
    FILE(APPEND ${PROJECT_BINARY_DIR}/GlobalConfig.h "#include \"windows.h\"\n")
    set_target_properties(OUGDASM_Vulkan PROPERTIES OUTPUT_NAME "ougdasm_vk.exe")
ENDIF()
IF (UNIX)
    set_target_properties(OUGDASM_Vulkan PROPERTIES OUTPUT_NAME "ougdasm_vk.o")
ENDIF()

target_include_directories(OUGDASM_Vulkan PUBLIC ${PROJECT_BINARY_DIR})

set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")

target_compile_options(OUGDASM_Vulkan INTERFACE
    "$<${gcc_like_cxx}:-Wextra;-Wshadow;-Wformat=2;-Wunused>"
    "$<${msvc_cxx}:/W3>"
)

if (WIN32 AND MSVC) # Windows Visual Studio
    TARGET_LINK_LIBRARIES(OUGDASM_Vulkan PRIVATE #VULKAN
        "${CMAKE_SOURCE_DIR}/libwin64/glfw_vs22/glfw3.lib"
        "${CMAKE_SOURCE_DIR}/libwin64/glfw_vs22/glfw3dll.lib"
        "${CMAKE_SOURCE_DIR}/libwin64/glfw_vs22/glfw3mt.lib"
        "${VULKAN_SDK_PATH}/Lib/vulkan-1.lib"
    )
ELSE()
    if(WIN32) # Windows MinGW
        TARGET_LINK_LIBRARIES(OUGDASM_Vulkan PRIVATE #VULKAN
            "${CMAKE_SOURCE_DIR}/libwin64/glfw_mingw/libglfw3.a"
            "${CMAKE_SOURCE_DIR}/libwin64/glfw_mingw/libglfw3dll.a"
            "${VULKAN_SDK_PATH}/Lib/vulkan-1.lib"
        )
    endif()
endif()

if (UNIX) #UNIX (assumes G++!!!!)

    find_package(Vulkan)
    find_package(VulkanHeaders REQUIRED CONFIG)
    get_filename_component(Vulkan_LIBRARY_DIR ${Vulkan_LIBRARY} DIRECTORY)
    message(STATUS "Vulkan FOUND = ${Vulkan_FOUND}")
    message(STATUS "Vulkan Lib Dir = ${Vulkan_LIBRARY_DIR}")
    message(STATUS "Vulkan Lib = ${Vulkan_LIBRARY}")

    TARGET_LINK_LIBRARIES(OUGDASM_Vulkan PRIVATE #VULKAN
        "${CMAKE_SOURCE_DIR}/libunix/libglfw.so"
        "${Vulkan_LIBRARY}"
    )
endif()

target_include_directories(OUGDASM_Vulkan PRIVATE
    "${CMAKE_SOURCE_DIR}/include/"
    "${VULKAN_SDK_PATH}/Include/"
)