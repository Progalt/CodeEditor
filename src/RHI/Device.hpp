
#ifndef RHI_DEVICE_H
#define RHI_DEVICE_H

#include <memory>

namespace rhi
{
    class Device
    {
    public:

        // Return a new hardware interface
        static std::shared_ptr<Device> CreateDevice();  

        // Destroy a hardware interface
        static void DestroyDevice(std::shared_ptr<Device> device);

    private: 
    };
}


#endif // RHI_DEVICE_H