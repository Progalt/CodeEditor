
#ifndef RHI_DEVICE_H
#define RHI_DEVICE_H

#include <memory>
#include "Swapchain.hpp"

namespace rhi
{
    class Device
    {
    public:

        // Return a new hardware interface
        static std::shared_ptr<Device> CreateDevice();  

        // Destroy a hardware interface
        static void DestroyDevice(std::shared_ptr<Device> device);


        virtual std::shared_ptr<Swapchain> CreateSwapchain(); 

    private: 
    };
}


#endif // RHI_DEVICE_H