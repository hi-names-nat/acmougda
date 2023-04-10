#ifndef OUGDASM_VULKAN_VKRUNNER_H
#define OUGDASM_VULKAN_VKRUNNER_H

class GLFWwindow;

class vkRunner {
    GLFWwindow* window=nullptr;
    VkInstance instance;
public:
/// The initializer
    int vkInit();

/// Main loop
    void vkLoop();

/// Teardown
    void vkCleanup();
private:
    void vkCreateInstance();
};

#endif //OUGDASM_VULKAN_VKRUNNER_H
