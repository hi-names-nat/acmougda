#include <vulkan/vulkan.h>
#include <iostream>
#include <vector>
#include "GLFW/glfw3.h"
#include "vkrunner.hpp"
#include "GlobalConfig.h"

const int WIDTH= 800;
const int HEIGHT= 600;
const char* WINDOW_NAME= "OUGDASM: Vulkan Renderer";

const std::vector<const char*> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
};

int vkRunner::vkInit() {
    vkCreateInstance();
    //start our GLFW instance
    std::printf("START initialize VK...\n");
    std::printf("Init GLFW...\n");
    if (glfwInit() == GLFW_FALSE) {
        const char **errMsg = nullptr;
        int success = glfwGetError(errMsg);
        std::cerr << "Could not init GLFW: " << errMsg << '\n';
        return success;
    }
    else {
        std::printf("GLFW Initialized.\n");
    }

    //build our window
    std::printf("Initializing window...\n");
    glfwWindowHint(GLFW_CLIENT_API, GLFW_FALSE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    window = glfwCreateWindow(WIDTH, HEIGHT, WINDOW_NAME, nullptr, nullptr);
    std::printf("Window initialized.\n");

    //get our supported extensions
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    std::cout << extensionCount << " extensions supported\n";



    std::printf("Vulkan initialize success!\n");
    return GLFW_TRUE;
}

void vkRunner::vkLoop() {
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }
}

void vkRunner::vkCleanup() {
    vkDestroyInstance(instance, nullptr);
    glfwDestroyWindow(window);
    glfwTerminate();
}

void vkRunner::vkCreateInstance() {
    if (enableValidationLayers && !vkCheckValidationLayers()) {
        throw std::runtime_error("validation layers requested, but not available!");
    }

    VkApplicationInfo applicationInfo{};
    applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    applicationInfo.pApplicationName = "OUGDASM Rendering example";
    applicationInfo.applicationVersion = VK_MAKE_API_VERSION(0, OUGDASM_VERSION_MAJOR, OUGDASM_VERSION_MINOR, OUGDASM_VERSION_PATCH);
    applicationInfo.pEngineName = "OUGDASM Engine";
    applicationInfo.engineVersion = VK_MAKE_API_VERSION(0, OUGDASM_VERSION_MAJOR, OUGDASM_VERSION_MINOR, OUGDASM_VERSION_PATCH);
    applicationInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &applicationInfo;

    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;

    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    //extension setups
    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;

    //validation layers
    if (enableValidationLayers) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();
    } else {
        createInfo.enabledLayerCount = 0;
    }

    if ( ::vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create VkInstance.");
    }
}

bool vkRunner::vkCheckValidationLayers() {
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    for (const char* layerName : validationLayers) {
        bool layerFound = false;

        for (const auto& layerProperties : availableLayers) {
            if (strcmp(layerName, layerProperties.layerName) == 0) {
                layerFound = true;
                break;
            }
        }

        if (!layerFound) {
            return false;
        }
    }

    return true;
}
