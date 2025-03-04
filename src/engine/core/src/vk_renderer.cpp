#include <vk_renderer.h>

namespace FancyEngine {

	bool FVulkanRenderer::Initialize(GLFWwindow* window) {



		// Vulkan Instance Creation

		const char* INSTANCE_EXTENSIONS[2] = { "VK_KHR_win32_surface", "VK_KHR_surface" };
		const char* INSTANCE_LAYERS[1] = { "VK_LAYER_KHRONOS_validation" };
		
		VkApplicationInfo applicationInfo{};
		applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		applicationInfo.pNext = nullptr;
		applicationInfo.apiVersion = VK_API_VERSION_1_0;
		applicationInfo.pApplicationName = "Fancy";
		applicationInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		applicationInfo.pEngineName = "Fancy Engine";
		applicationInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);

		VkInstanceCreateInfo instanceInfo{};
		instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		instanceInfo.pNext = nullptr;
		instanceInfo.flags = 0;
		instanceInfo.pApplicationInfo = &applicationInfo;
		instanceInfo.ppEnabledExtensionNames = INSTANCE_EXTENSIONS;
		instanceInfo.enabledExtensionCount = 2;
		instanceInfo.ppEnabledLayerNames = INSTANCE_LAYERS;
		instanceInfo.enabledLayerCount = 1;

		if (vkCreateInstance(&instanceInfo, nullptr, &instance) != VK_SUCCESS) return false;



		// Surface Creation

		VkWin32SurfaceCreateInfoKHR surfaceInfo{};
		surfaceInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
		surfaceInfo.pNext = nullptr;
		surfaceInfo.flags = 0;
		surfaceInfo.hwnd = glfwGetWin32Window(window);
		surfaceInfo.hinstance = nullptr;

		if (vkCreateWin32SurfaceKHR(instance, &surfaceInfo, nullptr, &surface) != VK_SUCCESS) return false;



		// Choosing Graphics Card

		vkEnumeratePhysicalDevices(instance, &GPUsCount, nullptr);
		GPUs.resize(GPUsCount);
		vkEnumeratePhysicalDevices(instance, &GPUsCount, GPUs.data());
		physical = GPUs[0];



		// Creating Logical Card

		const char* DEVICE_EXTENSIONS[1] = { "VK_KHR_swapchain" };
		const char* DEVICE_LAYERS[1] = {""};

		float priority = 1.0f;

		VkDeviceQueueCreateInfo graphicsInfo{};
		graphicsInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		graphicsInfo.pNext = nullptr;
		graphicsInfo.flags = 0;
		graphicsInfo.queueFamilyIndex = 0;
		graphicsInfo.queueCount = 1;
		graphicsInfo.pQueuePriorities = &priority;

		VkDeviceCreateInfo deviceInfo{};
		deviceInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		deviceInfo.pNext = nullptr;
		deviceInfo.flags = 0;
		deviceInfo.ppEnabledExtensionNames = DEVICE_EXTENSIONS;
		deviceInfo.enabledExtensionCount = 1;
		deviceInfo.ppEnabledLayerNames = DEVICE_LAYERS;
		deviceInfo.enabledLayerCount = 0;
		deviceInfo.pEnabledFeatures = nullptr;
		deviceInfo.pQueueCreateInfos = &graphicsInfo;
		deviceInfo.queueCreateInfoCount = 1;

		if (vkCreateDevice(physical, &deviceInfo, nullptr, &logical) != VK_SUCCESS) return false;

		vkGetDeviceQueue(logical, 0, 0, &graphicsQueue);



		// Swapchain Creation

		VkSwapchainCreateInfoKHR swapchainInfo{};
		swapchainInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		swapchainInfo.pNext = nullptr;
		swapchainInfo.flags = 0;
		swapchainInfo.surface = surface;
		swapchainInfo.presentMode = VK_PRESENT_MODE_FIFO_KHR;
		swapchainInfo.preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
		swapchainInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		swapchainInfo.clipped = false;
		swapchainInfo.imageArrayLayers = 1;
		swapchainInfo.imageColorSpace = VK_COLORSPACE_SRGB_NONLINEAR_KHR;
		swapchainInfo.imageExtent = VkExtent2D(800, 600);
		swapchainInfo.imageFormat = VK_FORMAT_R8G8B8A8_SRGB;
		swapchainInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		swapchainInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
		swapchainInfo.minImageCount = 2;

		if (vkCreateSwapchainKHR(logical, &swapchainInfo, nullptr, &swapchain) != VK_SUCCESS) return false;

		vkGetSwapchainImagesKHR(logical, swapchain, &swapchainImagesCount, nullptr);
		swapchainImages.resize(swapchainImagesCount);
		vkGetSwapchainImagesKHR(logical, swapchain, &swapchainImagesCount, swapchainImages.data());

		swapchainImagesViews.resize(swapchainImagesCount);

		for (size_t v = 0; v < swapchainImagesCount; v++)
		{

			VkImageViewCreateInfo swapchainViewInfo{};
			swapchainViewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			swapchainViewInfo.pNext = nullptr;
			swapchainViewInfo.flags = 0;
			swapchainViewInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
			swapchainViewInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
			swapchainViewInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
			swapchainViewInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
			swapchainViewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
			swapchainViewInfo.format = VK_FORMAT_R8G8B8A8_SRGB;
			swapchainViewInfo.image = swapchainImages[v];
			swapchainViewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			swapchainViewInfo.subresourceRange.baseArrayLayer = 0;
			swapchainViewInfo.subresourceRange.layerCount = 1;
			swapchainViewInfo.subresourceRange.baseMipLevel = 0;
			swapchainViewInfo.subresourceRange.levelCount = 1;

			if (vkCreateImageView(logical, &swapchainViewInfo, nullptr, &swapchainImagesViews[v]) != VK_SUCCESS) return false;

		}

		// Graphics Command Pool Creation

		VkCommandPoolCreateInfo graphicsPoolInfo{};
		graphicsPoolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		graphicsPoolInfo.pNext = nullptr;
		graphicsPoolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
		graphicsPoolInfo.queueFamilyIndex = 0;

		if (vkCreateCommandPool(logical, &graphicsPoolInfo, nullptr, &graphicsPool) != VK_SUCCESS) return false;



		// Graphics Command Buffer Creation

		VkCommandBufferAllocateInfo graphicsCommandInfo{};
		graphicsCommandInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		graphicsCommandInfo.pNext = nullptr;
		graphicsCommandInfo.commandPool = graphicsPool;
		graphicsCommandInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		graphicsCommandInfo.commandBufferCount = 1;

		if (vkAllocateCommandBuffers(logical, &graphicsCommandInfo, &graphicsCommand) != VK_SUCCESS) return false;



		// Semaphores And Fences Creation

		semaphores.resize(2);

		VkSemaphoreCreateInfo semaphoreInfo;
		semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
		semaphoreInfo.pNext = nullptr;
		semaphoreInfo.flags = 0;

		if (vkCreateSemaphore(logical, &semaphoreInfo, nullptr, &semaphores[0]) != VK_SUCCESS) return false;
		if (vkCreateSemaphore(logical, &semaphoreInfo, nullptr, &semaphores[1]) != VK_SUCCESS) return false;

		VkFenceCreateInfo fenceInfo{};
		fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		fenceInfo.pNext = nullptr;
		fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;
		
		if (vkCreateFence(logical, &fenceInfo, nullptr, &fence) != VK_SUCCESS) return false;



		// Render Pass Creation

		VkAttachmentDescription attachment1{};
		attachment1.flags = 0;
		attachment1.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		attachment1.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
		attachment1.format = VK_FORMAT_R8G8B8A8_SRGB;
		attachment1.samples = VK_SAMPLE_COUNT_1_BIT;
		attachment1.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
		attachment1.storeOp = VK_ATTACHMENT_STORE_OP_STORE;

		VkAttachmentReference reference1{};
		reference1.attachment = 0;
		reference1.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

		VkSubpassDescription description1{};
		description1.flags = 0;
		description1.pColorAttachments = &reference1;
		description1.colorAttachmentCount = 1;
		description1.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;

		VkRenderPassCreateInfo renderpassInfo{};
		renderpassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		renderpassInfo.pNext = nullptr;
		renderpassInfo.flags = 0;
		renderpassInfo.pAttachments = &attachment1;
		renderpassInfo.attachmentCount = 1;
		renderpassInfo.pDependencies;
		renderpassInfo.dependencyCount;
		renderpassInfo.pSubpasses = &description1;
		renderpassInfo.subpassCount = 1;

		if (vkCreateRenderPass(logical, &renderpassInfo, nullptr, &renderpass) != VK_SUCCESS) return false;



		// Frame Buffers And Image Views Creation

		framebuffers.resize(swapchainImagesViews.size());

		for (size_t f = 0; f < swapchainImagesViews.size(); f++)
		{

			VkFramebufferCreateInfo frameInfo{};
			frameInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
			frameInfo.pNext = nullptr;
			frameInfo.flags = 0;
			frameInfo.renderPass = renderpass;
			frameInfo.pAttachments = &swapchainImagesViews[f];
			frameInfo.attachmentCount = 1;
			frameInfo.width = 800;
			frameInfo.height = 600;
			frameInfo.layers = 1;

			if (vkCreateFramebuffer(logical, &frameInfo, nullptr, &framebuffers[f]) != VK_SUCCESS) return false;

		}

		

	std::cout << "Vulkan renderer initialized" << std::endl;
	return true;
}

void FVulkanRenderer::Shutdown() {

	vkDestroyFence(logical, fence, nullptr);
	for (auto& semaphore : semaphores) vkDestroySemaphore(logical, semaphore, nullptr);
	vkDestroyRenderPass(logical, renderpass, nullptr);
	for (auto& image : swapchainImages) vkDestroyImage(logical, image, nullptr);
	for (auto& view : swapchainImagesViews) vkDestroyImageView(logical, view, nullptr);
	for (auto& frame : framebuffers) vkDestroyFramebuffer(logical, frame, nullptr);
	vkFreeCommandBuffers(logical, graphicsPool, 1, &graphicsCommand);
	vkDestroyCommandPool(logical, graphicsPool, nullptr);
	vkDestroySwapchainKHR(logical, swapchain, nullptr);
	vkDestroyDevice(logical, nullptr);
	vkDestroySurfaceKHR(instance, surface, nullptr);
	vkDestroyInstance(instance, nullptr);

	std::cout << "Vulkan renderer shutdown" << std::endl;
}

void FVulkanRenderer::BeginFrame() {

	// Aquiring Image

	vkWaitForFences(logical, 1, &fence, VK_TRUE, UINT64_MAX);
	vkResetFences(logical, 1, &fence);

	vkAcquireNextImageKHR(logical, swapchain, UINT64_MAX, semaphores[0], nullptr, &imageIndex);


	// Submitting It For Rendering

	VkCommandBufferBeginInfo graphicsBeginInfo{};
	graphicsBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	graphicsBeginInfo.pNext = nullptr;
	graphicsBeginInfo.flags = 0;
	graphicsBeginInfo.pInheritanceInfo = nullptr;

	vkBeginCommandBuffer(graphicsCommand, &graphicsBeginInfo);

	VkRenderPassBeginInfo beginInfo{};
	beginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	beginInfo.pNext = nullptr;
	beginInfo.framebuffer = framebuffers[imageIndex];
	beginInfo.renderPass = renderpass;
	beginInfo.renderArea.extent = VkExtent2D(800, 600);
	beginInfo.renderArea.offset = VkOffset2D(0, 0);
	VkClearValue color = { {1.0, 0.0, 0.0, 1.0} };
	beginInfo.pClearValues = &color;
	beginInfo.clearValueCount = 1;
	vkCmdBeginRenderPass(graphicsCommand, &beginInfo, VK_SUBPASS_CONTENTS_INLINE);

	vkCmdEndRenderPass(graphicsCommand);

	vkEndCommandBuffer(graphicsCommand);

	VkSubmitInfo submitInfo{};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.pNext = nullptr;
	submitInfo.pCommandBuffers = &graphicsCommand;
	submitInfo.commandBufferCount = 1;
	VkPipelineStageFlags waitFlag = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
	submitInfo.pWaitDstStageMask = &waitFlag;
	submitInfo.pWaitSemaphores = &semaphores[0];
	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = &semaphores[1];
	submitInfo.signalSemaphoreCount = 1;

	vkQueueSubmit(graphicsQueue, 1, &submitInfo, fence);

	//std::cout << "Vulkan renderer begin frame" << std::endl;
}

void FVulkanRenderer::EndFrame() {

	// Presenting The Image

	VkPresentInfoKHR presentInfo{};
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	presentInfo.pNext = nullptr;
	presentInfo.pResults = nullptr;
	presentInfo.pImageIndices = &imageIndex;
	presentInfo.pWaitSemaphores = &semaphores[1];
	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pSwapchains = &swapchain;
	presentInfo.swapchainCount = 1;

	vkQueuePresentKHR(graphicsQueue, &presentInfo);

	//std::cout << "Vulkan renderer end frame" << std::endl;
}

void FVulkanRenderer::ResizeViewport(uint32_t width, uint32_t height) {
	std::cout << "Vulkan renderer resize viewport" << std::endl;
}

uint32_t FVulkanRenderer::CreateVertexBuffer(const void* data, size_t size) {
	std::cout << "Vulkan renderer create vertex buffer" << std::endl;
	return 0;
}

uint32_t FVulkanRenderer::CreateIndexBuffer(const void* data, size_t size) {
	std::cout << "Vulkan renderer create index buffer" << std::endl;
	return 0;
}

uint32_t FVulkanRenderer::CreateTexture(const void* data, uint32_t width, uint32_t height) {
	std::cout << "Vulkan renderer create texture" << std::endl;
	return 0;
}

uint32_t FVulkanRenderer::CreateShader(const std::string& vertexSource, const std::string& fragmentSource) {
	std::cout << "Vulkan renderer create shader" << std::endl;
	return 0;
}

void FVulkanRenderer::BindShader(uint32_t shaderId) {
	std::cout << "Vulkan renderer bind shader" << std::endl;
}

void FVulkanRenderer::BindVertexBuffer(uint32_t bufferId) {
	std::cout << "Vulkan renderer bind vertex buffer" << std::endl;
}

void FVulkanRenderer::BindIndexBuffer(uint32_t bufferId) {
	std::cout << "Vulkan renderer bind index buffer" << std::endl;
}

void FVulkanRenderer::BindTexture(uint32_t textureId, uint32_t slot) {
	std::cout << "Vulkan renderer bind texture" << std::endl;
}

void FVulkanRenderer::DrawIndexed(uint32_t indexCount) {
	std::cout << "Vulkan renderer draw indexed" << std::endl;
}


} // namespace FancyEngine