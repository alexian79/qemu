/* stm32g4_dma1.c */

#include "qemu/osdep.h"
#include "hw/irq.h"
#include "hw/qdev-properties.h"
#include "include/hw/arm/stm32g4/stm32g4_dma1.h"
#include "migration/vmstate.h"

#define STM32G4_DMA1_MMIO TYPE_STM32G4_DMA1 "_mmio"
#define STM32G4_DMA1_MMIO_SIZE 0xA4

static uint64_t stm32g4_dma1_mmio_read(void *opaque, hwaddr offset,
                                       unsigned size)
{
    STM32G4DMA1State *s = STM32G4_DMA1(opaque);
    uint64_t ret = 0;

    switch (offset) {
    case 0x00 ... 0x03:
        /* ISR, interrupt status register */
        ret = s->isr;
        break;

    case 0x04 ... 0x07:
        /* IFCR, DMA interrupt flag clear register */
        ret = s->ifcr;
        break;

    case 0x08 ... 0x0B:
        /* CCR1, DMA channel 1 configuration register */
        ret = s->ccr1;
        break;

    case 0x0C ... 0x0F:
        /* CNDTR1, channel x number of data to transfer register */
        ret = s->cndtr1;
        break;

    case 0x10 ... 0x13:
        /* CPAR1, DMA channel x peripheral address register */
        ret = s->cpar1;
        break;

    case 0x14 ... 0x17:
        /* CMAR1, DMA channel x memory address register */
        ret = s->cmar1;
        break;

    case 0x1C ... 0x1F:
        /* CCR2, DMA channel 2 configuration register */
        ret = s->ccr2;
        break;

    case 0x20 ... 0x23:
        /* CNDTR2, channel x number of data to transfer register */
        ret = s->cndtr2;
        break;

    case 0x24 ... 0x27:
        /* CPAR2, DMA channel x peripheral address register */
        ret = s->cpar2;
        break;

    case 0x28 ... 0x2B:
        /* CMAR2, DMA channel x memory address register */
        ret = s->cmar2;
        break;

    case 0x30 ... 0x33:
        /* CCR3, DMA channel 3 configuration register */
        ret = s->ccr3;
        break;

    case 0x34 ... 0x37:
        /* CNDTR3, channel x number of data to transfer register */
        ret = s->cndtr3;
        break;

    case 0x38 ... 0x3B:
        /* CPAR3, DMA channel x peripheral address register */
        ret = s->cpar3;
        break;

    case 0x3C ... 0x3F:
        /* CMAR3, DMA channel x memory address register */
        ret = s->cmar3;
        break;

    case 0x44 ... 0x47:
        /* CCR4, DMA channel 4 configuration register */
        ret = s->ccr4;
        break;

    case 0x48 ... 0x4B:
        /* CNDTR4, channel x number of data to transfer register */
        ret = s->cndtr4;
        break;

    case 0x4C ... 0x4F:
        /* CPAR4, DMA channel x peripheral address register */
        ret = s->cpar4;
        break;

    case 0x50 ... 0x53:
        /* CMAR4, DMA channel x memory address register */
        ret = s->cmar4;
        break;

    case 0x58 ... 0x5B:
        /* CCR5, DMA channel 5 configuration register */
        ret = s->ccr5;
        break;

    case 0x5C ... 0x5F:
        /* CNDTR5, channel x number of data to transfer register */
        ret = s->cndtr5;
        break;

    case 0x60 ... 0x63:
        /* CPAR5, DMA channel x peripheral address register */
        ret = s->cpar5;
        break;

    case 0x64 ... 0x67:
        /* CMAR5, DMA channel x memory address register */
        ret = s->cmar5;
        break;

    case 0x6C ... 0x6F:
        /* CCR6, DMA channel 6 configuration register */
        ret = s->ccr6;
        break;

    case 0x70 ... 0x73:
        /* CNDTR6, channel x number of data to transfer register */
        ret = s->cndtr6;
        break;

    case 0x74 ... 0x77:
        /* CPAR6, DMA channel x peripheral address register */
        ret = s->cpar6;
        break;

    case 0x78 ... 0x7B:
        /* CMAR6, DMA channel x memory address register */
        ret = s->cmar6;
        break;

    case 0x80 ... 0x83:
        /* CCR7, DMA channel 7 configuration register */
        ret = s->ccr7;
        break;

    case 0x84 ... 0x87:
        /* CNDTR7, channel x number of data to transfer register */
        ret = s->cndtr7;
        break;

    case 0x88 ... 0x8B:
        /* CPAR7, DMA channel x peripheral address register */
        ret = s->cpar7;
        break;

    case 0x8C ... 0x8F:
        /* CMAR7, DMA channel x memory address register */
        ret = s->cmar7;
        break;

    case 0x94 ... 0x97:
        /* CCR8, DMA channel 8 configuration register */
        ret = s->ccr8;
        break;

    case 0x98 ... 0x9B:
        /* CNDTR8, channel x number of data to transfer register */
        ret = s->cndtr8;
        break;

    case 0x9C ... 0x9F:
        /* CPAR8, DMA channel x peripheral address register */
        ret = s->cpar8;
        break;

    case 0xA0 ... 0xA3:
        /* CMAR8, DMA channel x memory address register */
        ret = s->cmar8;
        break;

    default:
        printf("%s: unimplemented read from 0x%" HWADDR_PRIx ", size %d\n",
               __func__, offset, size);
        break;
    }

    return ret;
}

static void stm32g4_dma1_mmio_write(void *opaque, hwaddr offset, uint64_t value,
                                    unsigned size)
{
    STM32G4DMA1State *s = STM32G4_DMA1(opaque);

    switch (offset) {
    case 0x00 ... 0x03:
        /* ISR, interrupt status register */
        s->isr = value;
        break;

    case 0x04 ... 0x07:
        /* IFCR, DMA interrupt flag clear register */
        s->ifcr = value;
        break;

    case 0x08 ... 0x0B:
        /* CCR1, DMA channel 1 configuration register */
        s->ccr1 = value;
        break;

    case 0x0C ... 0x0F:
        /* CNDTR1, channel x number of data to transfer register */
        s->cndtr1 = value;
        break;

    case 0x10 ... 0x13:
        /* CPAR1, DMA channel x peripheral address register */
        s->cpar1 = value;
        break;

    case 0x14 ... 0x17:
        /* CMAR1, DMA channel x memory address register */
        s->cmar1 = value;
        break;

    case 0x1C ... 0x1F:
        /* CCR2, DMA channel 2 configuration register */
        s->ccr2 = value;
        break;

    case 0x20 ... 0x23:
        /* CNDTR2, channel x number of data to transfer register */
        s->cndtr2 = value;
        break;

    case 0x24 ... 0x27:
        /* CPAR2, DMA channel x peripheral address register */
        s->cpar2 = value;
        break;

    case 0x28 ... 0x2B:
        /* CMAR2, DMA channel x memory address register */
        s->cmar2 = value;
        break;

    case 0x30 ... 0x33:
        /* CCR3, DMA channel 3 configuration register */
        s->ccr3 = value;
        break;

    case 0x34 ... 0x37:
        /* CNDTR3, channel x number of data to transfer register */
        s->cndtr3 = value;
        break;

    case 0x38 ... 0x3B:
        /* CPAR3, DMA channel x peripheral address register */
        s->cpar3 = value;
        break;

    case 0x3C ... 0x3F:
        /* CMAR3, DMA channel x memory address register */
        s->cmar3 = value;
        break;

    case 0x44 ... 0x47:
        /* CCR4, DMA channel 4 configuration register */
        s->ccr4 = value;
        break;

    case 0x48 ... 0x4B:
        /* CNDTR4, channel x number of data to transfer register */
        s->cndtr4 = value;
        break;

    case 0x4C ... 0x4F:
        /* CPAR4, DMA channel x peripheral address register */
        s->cpar4 = value;
        break;

    case 0x50 ... 0x53:
        /* CMAR4, DMA channel x memory address register */
        s->cmar4 = value;
        break;

    case 0x58 ... 0x5B:
        /* CCR5, DMA channel 5 configuration register */
        s->ccr5 = value;
        break;

    case 0x5C ... 0x5F:
        /* CNDTR5, channel x number of data to transfer register */
        s->cndtr5 = value;
        break;

    case 0x60 ... 0x63:
        /* CPAR5, DMA channel x peripheral address register */
        s->cpar5 = value;
        break;

    case 0x64 ... 0x67:
        /* CMAR5, DMA channel x memory address register */
        s->cmar5 = value;
        break;

    case 0x6C ... 0x6F:
        /* CCR6, DMA channel 6 configuration register */
        s->ccr6 = value;
        break;

    case 0x70 ... 0x73:
        /* CNDTR6, channel x number of data to transfer register */
        s->cndtr6 = value;
        break;

    case 0x74 ... 0x77:
        /* CPAR6, DMA channel x peripheral address register */
        s->cpar6 = value;
        break;

    case 0x78 ... 0x7B:
        /* CMAR6, DMA channel x memory address register */
        s->cmar6 = value;
        break;

    case 0x80 ... 0x83:
        /* CCR7, DMA channel 7 configuration register */
        s->ccr7 = value;
        break;

    case 0x84 ... 0x87:
        /* CNDTR7, channel x number of data to transfer register */
        s->cndtr7 = value;
        break;

    case 0x88 ... 0x8B:
        /* CPAR7, DMA channel x peripheral address register */
        s->cpar7 = value;
        break;

    case 0x8C ... 0x8F:
        /* CMAR7, DMA channel x memory address register */
        s->cmar7 = value;
        break;

    case 0x94 ... 0x97:
        /* CCR8, DMA channel 8 configuration register */
        s->ccr8 = value;
        break;

    case 0x98 ... 0x9B:
        /* CNDTR8, channel x number of data to transfer register */
        s->cndtr8 = value;
        break;

    case 0x9C ... 0x9F:
        /* CPAR8, DMA channel x peripheral address register */
        s->cpar8 = value;
        break;

    case 0xA0 ... 0xA3:
        /* CMAR8, DMA channel x memory address register */
        s->cmar8 = value;
        break;

    default:
        printf("%s: unimplemented write to 0x%" HWADDR_PRIx ", size %d, "
               "value 0x%" PRIx64 "\n", __func__, offset, size, value);
        break;
    }
}

static const MemoryRegionOps stm32g4_dma1_mmio_ops = {
    .read = stm32g4_dma1_mmio_read,
    .write = stm32g4_dma1_mmio_write,
    .impl = {
        .max_access_size = 4
    }
};

static void stm32g4_dma1_instance_init(Object *obj)
{
    STM32G4DMA1State *s = STM32G4_DMA1(obj);

    memory_region_init_io(&s->mmio, obj, &stm32g4_dma1_mmio_ops, s,
                          STM32G4_DMA1_MMIO, STM32G4_DMA1_MMIO_SIZE);
    sysbus_init_mmio(SYS_BUS_DEVICE(obj), &s->mmio);
}

static void stm32g4_dma1_realize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4DMA1State *s = STM32G4_DMA1(dev);
}

static void stm32g4_dma1_reset(DeviceState *dev)
{
    STM32G4DMA1State *s = STM32G4_DMA1(dev);

    s->isr = 0x00000000;
    s->ifcr = 0x00000000;
    s->ccr1 = 0x00000000;
    s->cndtr1 = 0x00000000;
    s->cpar1 = 0x00000000;
    s->cmar1 = 0x00000000;
    s->ccr2 = 0x00000000;
    s->cndtr2 = 0x00000000;
    s->cpar2 = 0x00000000;
    s->cmar2 = 0x00000000;
    s->ccr3 = 0x00000000;
    s->cndtr3 = 0x00000000;
    s->cpar3 = 0x00000000;
    s->cmar3 = 0x00000000;
    s->ccr4 = 0x00000000;
    s->cndtr4 = 0x00000000;
    s->cpar4 = 0x00000000;
    s->cmar4 = 0x00000000;
    s->ccr5 = 0x00000000;
    s->cndtr5 = 0x00000000;
    s->cpar5 = 0x00000000;
    s->cmar5 = 0x00000000;
    s->ccr6 = 0x00000000;
    s->cndtr6 = 0x00000000;
    s->cpar6 = 0x00000000;
    s->cmar6 = 0x00000000;
    s->ccr7 = 0x00000000;
    s->cndtr7 = 0x00000000;
    s->cpar7 = 0x00000000;
    s->cmar7 = 0x00000000;
    s->ccr8 = 0x00000000;
    s->cndtr8 = 0x00000000;
    s->cpar8 = 0x00000000;
    s->cmar8 = 0x00000000;
}

static void stm32g4_dma1_unrealize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4DMA1State *s = STM32G4_DMA1(dev);
}

static Property stm32g4_dma1_properties[] = {
    DEFINE_PROP_END_OF_LIST()
};

static const VMStateDescription vmstate_stm32g4_dma1 = {
    .name = "stm32g4_dma1",
    .version_id = 1,
    .fields = (VMStateField[]) {
        VMSTATE_UINT32(isr, STM32G4DMA1State),
        VMSTATE_UINT32(ifcr, STM32G4DMA1State),
        VMSTATE_UINT32(ccr1, STM32G4DMA1State),
        VMSTATE_UINT32(cndtr1, STM32G4DMA1State),
        VMSTATE_UINT32(cpar1, STM32G4DMA1State),
        VMSTATE_UINT32(cmar1, STM32G4DMA1State),
        VMSTATE_UINT32(ccr2, STM32G4DMA1State),
        VMSTATE_UINT32(cndtr2, STM32G4DMA1State),
        VMSTATE_UINT32(cpar2, STM32G4DMA1State),
        VMSTATE_UINT32(cmar2, STM32G4DMA1State),
        VMSTATE_UINT32(ccr3, STM32G4DMA1State),
        VMSTATE_UINT32(cndtr3, STM32G4DMA1State),
        VMSTATE_UINT32(cpar3, STM32G4DMA1State),
        VMSTATE_UINT32(cmar3, STM32G4DMA1State),
        VMSTATE_UINT32(ccr4, STM32G4DMA1State),
        VMSTATE_UINT32(cndtr4, STM32G4DMA1State),
        VMSTATE_UINT32(cpar4, STM32G4DMA1State),
        VMSTATE_UINT32(cmar4, STM32G4DMA1State),
        VMSTATE_UINT32(ccr5, STM32G4DMA1State),
        VMSTATE_UINT32(cndtr5, STM32G4DMA1State),
        VMSTATE_UINT32(cpar5, STM32G4DMA1State),
        VMSTATE_UINT32(cmar5, STM32G4DMA1State),
        VMSTATE_UINT32(ccr6, STM32G4DMA1State),
        VMSTATE_UINT32(cndtr6, STM32G4DMA1State),
        VMSTATE_UINT32(cpar6, STM32G4DMA1State),
        VMSTATE_UINT32(cmar6, STM32G4DMA1State),
        VMSTATE_UINT32(ccr7, STM32G4DMA1State),
        VMSTATE_UINT32(cndtr7, STM32G4DMA1State),
        VMSTATE_UINT32(cpar7, STM32G4DMA1State),
        VMSTATE_UINT32(cmar7, STM32G4DMA1State),
        VMSTATE_UINT32(ccr8, STM32G4DMA1State),
        VMSTATE_UINT32(cndtr8, STM32G4DMA1State),
        VMSTATE_UINT32(cpar8, STM32G4DMA1State),
        VMSTATE_UINT32(cmar8, STM32G4DMA1State),
        VMSTATE_END_OF_LIST()
    }
};

static void stm32g4_dma1_class_init(ObjectClass *oc, void *opaque)
{
    DeviceClass *dc = DEVICE_CLASS(oc);

    dc->realize   = stm32g4_dma1_realize;
    dc->reset     = stm32g4_dma1_reset;
    dc->unrealize = stm32g4_dma1_unrealize;
    dc->vmsd      = &vmstate_stm32g4_dma1;
    device_class_set_props(dc, stm32g4_dma1_properties);
}

static TypeInfo stm32g4_dma1_info = {
    .name          = TYPE_STM32G4_DMA1,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(STM32G4DMA1State),
    .instance_init = stm32g4_dma1_instance_init,
    .class_init    = stm32g4_dma1_class_init
};

static void stm32g4_dma1_register_types(void)
{
    type_register_static(&stm32g4_dma1_info);
}

type_init(stm32g4_dma1_register_types)
