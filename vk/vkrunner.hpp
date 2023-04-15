#ifndef OUGDASM_VULKAN_VKRUNNER_H
#define OUGDASM_VULKAN_VKRUNNER_H

class GLFWwindow;

class vkRunner {
    GLFWwindow* window=nullptr;
    VkInstance instance;
public:
/// initializer
    int vkInit();

/// Main loop
    void vkLoop();

/// Teardown
    void vkCleanup();
private:
/// initializer
    void vkCreateInstance();
    bool vkCheckValidationLayers();
};

#endif //OUGDASM_VULKAN_VKRUNNER_H
