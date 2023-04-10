#ifndef OUGDASM_MAIN_CPP
#define OUGDASM_MAIN_CPP
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <iostream>
#include "GlobalConfig.h"
#include "vkrunner.hpp"

int run();

int main() {
    try {if (run() == -1) return EXIT_FAILURE;}
    catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int run() {
    vkRunner runner;

    if (runner.vkInit() == GLFW_FALSE) return -1;
    runner.vkLoop();
    runner.vkCleanup();
    return 0;
}
#endif //OUGDASM_MAIN_CPP