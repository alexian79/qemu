/* stm32g4_usb_fs_device.c */

#include "qemu/osdep.h"
#include "hw/irq.h"
#include "hw/qdev-properties.h"
#include "include/hw/arm/stm32g4/stm32g4_usb_fs_device.h"
#include "migration/vmstate.h"

#define STM32G4_USB_FS_DEVICE_MMIO TYPE_STM32G4_USB_FS_DEVICE "_mmio"
#define STM32G4_USB_FS_DEVICE_MMIO_SIZE 0x54

static uint64_t stm32g4_usb_fs_device_mmio_read(void *opaque, hwaddr offset,
                                                unsigned size)
{
    STM32G4USBFSDeviceState *s = STM32G4_USB_FS_DEVICE(opaque);
    uint64_t ret = 0;

    switch (offset) {
    case 0x00 ... 0x03:
        /* EP0R, USB endpoint n register */
        ret = s->ep0r;
        break;

    case 0x04 ... 0x07:
        /* EP1R, USB endpoint n register */
        ret = s->ep1r;
        break;

    case 0x08 ... 0x0B:
        /* EP2R, USB endpoint n register */
        ret = s->ep2r;
        break;

    case 0x0C ... 0x0F:
        /* EP3R, USB endpoint n register */
        ret = s->ep3r;
        break;

    case 0x10 ... 0x13:
        /* EP4R, USB endpoint n register */
        ret = s->ep4r;
        break;

    case 0x14 ... 0x17:
        /* EP5R, USB endpoint n register */
        ret = s->ep5r;
        break;

    case 0x18 ... 0x1B:
        /* EP6R, USB endpoint n register */
        ret = s->ep6r;
        break;

    case 0x1C ... 0x1F:
        /* EP7R, USB endpoint n register */
        ret = s->ep7r;
        break;

    case 0x40 ... 0x43:
        /* CNTR, USB control register */
        ret = s->cntr;
        break;

    case 0x44 ... 0x47:
        /* ISTR, USB interrupt status register */
        ret = s->istr;
        break;

    case 0x48 ... 0x4B:
        /* FNR, USB frame number register */
        ret = s->fnr;
        break;

    case 0x4C ... 0x4F:
        /* DADDR, USB device address */
        ret = s->daddr;
        break;

    case 0x50 ... 0x53:
        /* BTABLE, Buffer table address */
        ret = s->btable;
        break;

    default:
        printf("%s: unimplemented read from 0x%" HWADDR_PRIx ", size %d\n",
               __func__, offset, size);
        break;
    }

    return ret;
}

static void stm32g4_usb_fs_device_mmio_write(void *opaque, hwaddr offset,
                                             uint64_t value, unsigned size)
{
    STM32G4USBFSDeviceState *s = STM32G4_USB_FS_DEVICE(opaque);

    switch (offset) {
    case 0x00 ... 0x03:
        /* EP0R, USB endpoint n register */
        s->ep0r = value;
        break;

    case 0x04 ... 0x07:
        /* EP1R, USB endpoint n register */
        s->ep1r = value;
        break;

    case 0x08 ... 0x0B:
        /* EP2R, USB endpoint n register */
        s->ep2r = value;
        break;

    case 0x0C ... 0x0F:
        /* EP3R, USB endpoint n register */
        s->ep3r = value;
        break;

    case 0x10 ... 0x13:
        /* EP4R, USB endpoint n register */
        s->ep4r = value;
        break;

    case 0x14 ... 0x17:
        /* EP5R, USB endpoint n register */
        s->ep5r = value;
        break;

    case 0x18 ... 0x1B:
        /* EP6R, USB endpoint n register */
        s->ep6r = value;
        break;

    case 0x1C ... 0x1F:
        /* EP7R, USB endpoint n register */
        s->ep7r = value;
        break;

    case 0x40 ... 0x43:
        /* CNTR, USB control register */
        s->cntr = value;
        break;

    case 0x44 ... 0x47:
        /* ISTR, USB interrupt status register */
        s->istr = value;
        break;

    case 0x48 ... 0x4B:
        /* FNR, USB frame number register */
        s->fnr = value;
        break;

    case 0x4C ... 0x4F:
        /* DADDR, USB device address */
        s->daddr = value;
        break;

    case 0x50 ... 0x53:
        /* BTABLE, Buffer table address */
        s->btable = value;
        break;

    default:
        printf("%s: unimplemented write to 0x%" HWADDR_PRIx ", size %d, "
               "value 0x%" PRIx64 "\n", __func__, offset, size, value);
        break;
    }
}

static const MemoryRegionOps stm32g4_usb_fs_device_mmio_ops = {
    .read = stm32g4_usb_fs_device_mmio_read,
    .write = stm32g4_usb_fs_device_mmio_write,
    .impl = {
        .max_access_size = 4
    }
};

static void stm32g4_usb_fs_device_instance_init(Object *obj)
{
    STM32G4USBFSDeviceState *s = STM32G4_USB_FS_DEVICE(obj);

    memory_region_init_io(&s->mmio, obj, &stm32g4_usb_fs_device_mmio_ops, s,
                          STM32G4_USB_FS_DEVICE_MMIO,
                          STM32G4_USB_FS_DEVICE_MMIO_SIZE);
    sysbus_init_mmio(SYS_BUS_DEVICE(obj), &s->mmio);
}

static void stm32g4_usb_fs_device_realize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4USBFSDeviceState *s =
        STM32G4_USB_FS_DEVICE(dev);
}

static void stm32g4_usb_fs_device_reset(DeviceState *dev)
{
    STM32G4USBFSDeviceState *s = STM32G4_USB_FS_DEVICE(dev);

    s->ep0r = 0x00000000;
    s->ep1r = 0x00000000;
    s->ep2r = 0x00000000;
    s->ep3r = 0x00000000;
    s->ep4r = 0x00000000;
    s->ep5r = 0x00000000;
    s->ep6r = 0x00000000;
    s->ep7r = 0x00000000;
    s->cntr = 0x00000000;
    s->istr = 0x00000000;
    s->fnr = 0x00000000;
    s->daddr = 0x00000000;
    s->btable = 0x00000000;
}

static void stm32g4_usb_fs_device_unrealize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4USBFSDeviceState *s =
        STM32G4_USB_FS_DEVICE(dev);
}

static Property stm32g4_usb_fs_device_properties[] = {
    DEFINE_PROP_END_OF_LIST()
};

static const VMStateDescription vmstate_stm32g4_usb_fs_device = {
    .name = "stm32g4_usb_fs_device",
    .version_id = 1,
    .fields = (VMStateField[]) {
        VMSTATE_UINT32(ep0r, STM32G4USBFSDeviceState),
        VMSTATE_UINT32(ep1r, STM32G4USBFSDeviceState),
        VMSTATE_UINT32(ep2r, STM32G4USBFSDeviceState),
        VMSTATE_UINT32(ep3r, STM32G4USBFSDeviceState),
        VMSTATE_UINT32(ep4r, STM32G4USBFSDeviceState),
        VMSTATE_UINT32(ep5r, STM32G4USBFSDeviceState),
        VMSTATE_UINT32(ep6r, STM32G4USBFSDeviceState),
        VMSTATE_UINT32(ep7r, STM32G4USBFSDeviceState),
        VMSTATE_UINT32(cntr, STM32G4USBFSDeviceState),
        VMSTATE_UINT32(istr, STM32G4USBFSDeviceState),
        VMSTATE_UINT32(fnr, STM32G4USBFSDeviceState),
        VMSTATE_UINT32(daddr, STM32G4USBFSDeviceState),
        VMSTATE_UINT32(btable, STM32G4USBFSDeviceState),
        VMSTATE_END_OF_LIST()
    }
};

static void stm32g4_usb_fs_device_class_init(ObjectClass *oc, void *opaque)
{
    DeviceClass *dc = DEVICE_CLASS(oc);

    dc->realize   = stm32g4_usb_fs_device_realize;
    dc->reset     = stm32g4_usb_fs_device_reset;
    dc->unrealize = stm32g4_usb_fs_device_unrealize;
    dc->vmsd      = &vmstate_stm32g4_usb_fs_device;
    device_class_set_props(dc, stm32g4_usb_fs_device_properties);
}

static TypeInfo stm32g4_usb_fs_device_info = {
    .name          = TYPE_STM32G4_USB_FS_DEVICE,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(STM32G4USBFSDeviceState),
    .instance_init = stm32g4_usb_fs_device_instance_init,
    .class_init    = stm32g4_usb_fs_device_class_init
};

static void stm32g4_usb_fs_device_register_types(void)
{
    type_register_static(&stm32g4_usb_fs_device_info);
}

type_init(stm32g4_usb_fs_device_register_types)
