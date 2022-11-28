/* stm32g4_usb_fs_device.h */
#ifndef INCLUDE_STM32G4_USB_FS_DEVICE_H
#define INCLUDE_STM32G4_USB_FS_DEVICE_H

#include "hw/sysbus.h"

#define TYPE_STM32G4_USB_FS_DEVICE "stm32g4_usb_fs_device"
#define STM32G4_USB_FS_DEVICE(obj) OBJECT_CHECK(STM32G4USBFSDeviceState, \
    (obj), TYPE_STM32G4_USB_FS_DEVICE)

typedef struct STM32G4USBFSDeviceState {
    SysBusDevice parent_obj;
    MemoryRegion mmio;
    uint32_t ep0r;
    uint32_t ep1r;
    uint32_t ep2r;
    uint32_t ep3r;
    uint32_t ep4r;
    uint32_t ep5r;
    uint32_t ep6r;
    uint32_t ep7r;
    uint32_t cntr;
    uint32_t istr;
    uint32_t fnr;
    uint32_t daddr;
    uint32_t btable;
} STM32G4USBFSDeviceState;

#endif /* INCLUDE_STM32G4_USB_FS_DEVICE_H */
