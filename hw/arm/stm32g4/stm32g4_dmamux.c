/* stm32g4_dmamux.c */

#include "qemu/osdep.h"
#include "hw/irq.h"
#include "hw/qdev-properties.h"
#include "include/hw/arm/stm32g4/stm32g4_dmamux.h"
#include "migration/vmstate.h"

#define STM32G4_DMAMUX_MMIO TYPE_STM32G4_DMAMUX "_mmio"
#define STM32G4_DMAMUX_MMIO_SIZE 0x148

static uint64_t stm32g4_dmamux_mmio_read(void *opaque, hwaddr offset,
                                         unsigned size)
{
    STM32G4DMAMUXState *s = STM32G4_DMAMUX(opaque);
    uint64_t ret = 0;

    switch (offset) {
    case 0x000 ... 0x003:
        /* C0CR, DMAMux - DMA request line multiplexer channel x control
            register */
        ret = s->c0cr;
        break;

    case 0x004 ... 0x007:
        /* C1CR, DMAMux - DMA request line multiplexer channel x control
            register */
        ret = s->c1cr;
        break;

    case 0x008 ... 0x00B:
        /* C2CR, DMAMux - DMA request line multiplexer channel x control
            register */
        ret = s->c2cr;
        break;

    case 0x00C ... 0x00F:
        /* C3CR, DMAMux - DMA request line multiplexer channel x control
            register */
        ret = s->c3cr;
        break;

    case 0x010 ... 0x013:
        /* C4CR, DMAMux - DMA request line multiplexer channel x control
            register */
        ret = s->c4cr;
        break;

    case 0x014 ... 0x017:
        /* C5CR, DMAMux - DMA request line multiplexer channel x control
            register */
        ret = s->c5cr;
        break;

    case 0x018 ... 0x01B:
        /* C6CR, DMAMux - DMA request line multiplexer channel x control
            register */
        ret = s->c6cr;
        break;

    case 0x01C ... 0x01F:
        /* C7CR, DMAMux - DMA request line multiplexer channel x control
            register */
        ret = s->c7cr;
        break;

    case 0x020 ... 0x023:
        /* C8CR, DMAMux - DMA request line multiplexer channel x control
            register */
        ret = s->c8cr;
        break;

    case 0x024 ... 0x027:
        /* C9CR, DMAMux - DMA request line multiplexer channel x control
            register */
        ret = s->c9cr;
        break;

    case 0x028 ... 0x02B:
        /* C10CR, DMAMux - DMA request line multiplexer channel x control
            register */
        ret = s->c10cr;
        break;

    case 0x02C ... 0x02F:
        /* C11CR, DMAMux - DMA request line multiplexer channel x control
            register */
        ret = s->c11cr;
        break;

    case 0x030 ... 0x033:
        /* C12CR, DMAMux - DMA request line multiplexer channel x control
            register */
        ret = s->c12cr;
        break;

    case 0x034 ... 0x037:
        /* C13CR, DMAMux - DMA request line multiplexer channel x control
            register */
        ret = s->c13cr;
        break;

    case 0x038 ... 0x03B:
        /* C14CR, DMAMux - DMA request line multiplexer channel x control
            register */
        ret = s->c14cr;
        break;

    case 0x03C ... 0x03F:
        /* C15CR, DMAMux - DMA request line multiplexer channel x control
            register */
        ret = s->c15cr;
        break;

    case 0x080 ... 0x083:
        /* CSR, DMAMUX request line multiplexer interrupt channel status
            register */
        ret = s->csr;
        break;

    case 0x084 ... 0x087:
        /* CFR, DMAMUX request line multiplexer interrupt clear flag register */
        ret = s->cfr;
        break;

    case 0x100 ... 0x103:
        /* RG0CR, DMAMux - DMA request generator channel x control register */
        ret = s->rg0cr;
        break;

    case 0x104 ... 0x107:
        /* RG1CR, DMAMux - DMA request generator channel x control register */
        ret = s->rg1cr;
        break;

    case 0x108 ... 0x10B:
        /* RG2CR, DMAMux - DMA request generator channel x control register */
        ret = s->rg2cr;
        break;

    case 0x10C ... 0x10F:
        /* RG3CR, DMAMux - DMA request generator channel x control register */
        ret = s->rg3cr;
        break;

    case 0x140 ... 0x143:
        /* RGSR, DMAMux - DMA request generator status register */
        ret = s->rgsr;
        break;

    case 0x144 ... 0x147:
        /* RGCFR, DMAMux - DMA request generator clear flag register */
        ret = s->rgcfr;
        break;

    default:
        printf("%s: unimplemented read from 0x%" HWADDR_PRIx ", size %d\n",
               __func__, offset, size);
        break;
    }

    return ret;
}

static void stm32g4_dmamux_mmio_write(void *opaque, hwaddr offset,
                                      uint64_t value, unsigned size)
{
    STM32G4DMAMUXState *s = STM32G4_DMAMUX(opaque);

    switch (offset) {
    case 0x000 ... 0x003:
        /* C0CR, DMAMux - DMA request line multiplexer channel x control
            register */
        s->c0cr = value;
        break;

    case 0x004 ... 0x007:
        /* C1CR, DMAMux - DMA request line multiplexer channel x control
            register */
        s->c1cr = value;
        break;

    case 0x008 ... 0x00B:
        /* C2CR, DMAMux - DMA request line multiplexer channel x control
            register */
        s->c2cr = value;
        break;

    case 0x00C ... 0x00F:
        /* C3CR, DMAMux - DMA request line multiplexer channel x control
            register */
        s->c3cr = value;
        break;

    case 0x010 ... 0x013:
        /* C4CR, DMAMux - DMA request line multiplexer channel x control
            register */
        s->c4cr = value;
        break;

    case 0x014 ... 0x017:
        /* C5CR, DMAMux - DMA request line multiplexer channel x control
            register */
        s->c5cr = value;
        break;

    case 0x018 ... 0x01B:
        /* C6CR, DMAMux - DMA request line multiplexer channel x control
            register */
        s->c6cr = value;
        break;

    case 0x01C ... 0x01F:
        /* C7CR, DMAMux - DMA request line multiplexer channel x control
            register */
        s->c7cr = value;
        break;

    case 0x020 ... 0x023:
        /* C8CR, DMAMux - DMA request line multiplexer channel x control
            register */
        s->c8cr = value;
        break;

    case 0x024 ... 0x027:
        /* C9CR, DMAMux - DMA request line multiplexer channel x control
            register */
        s->c9cr = value;
        break;

    case 0x028 ... 0x02B:
        /* C10CR, DMAMux - DMA request line multiplexer channel x control
            register */
        s->c10cr = value;
        break;

    case 0x02C ... 0x02F:
        /* C11CR, DMAMux - DMA request line multiplexer channel x control
            register */
        s->c11cr = value;
        break;

    case 0x030 ... 0x033:
        /* C12CR, DMAMux - DMA request line multiplexer channel x control
            register */
        s->c12cr = value;
        break;

    case 0x034 ... 0x037:
        /* C13CR, DMAMux - DMA request line multiplexer channel x control
            register */
        s->c13cr = value;
        break;

    case 0x038 ... 0x03B:
        /* C14CR, DMAMux - DMA request line multiplexer channel x control
            register */
        s->c14cr = value;
        break;

    case 0x03C ... 0x03F:
        /* C15CR, DMAMux - DMA request line multiplexer channel x control
            register */
        s->c15cr = value;
        break;

    case 0x080 ... 0x083:
        /* CSR, DMAMUX request line multiplexer interrupt channel status
            register */
        s->csr = value;
        break;

    case 0x084 ... 0x087:
        /* CFR, DMAMUX request line multiplexer interrupt clear flag register */
        s->cfr = value;
        break;

    case 0x100 ... 0x103:
        /* RG0CR, DMAMux - DMA request generator channel x control register */
        s->rg0cr = value;
        break;

    case 0x104 ... 0x107:
        /* RG1CR, DMAMux - DMA request generator channel x control register */
        s->rg1cr = value;
        break;

    case 0x108 ... 0x10B:
        /* RG2CR, DMAMux - DMA request generator channel x control register */
        s->rg2cr = value;
        break;

    case 0x10C ... 0x10F:
        /* RG3CR, DMAMux - DMA request generator channel x control register */
        s->rg3cr = value;
        break;

    case 0x140 ... 0x143:
        /* RGSR, DMAMux - DMA request generator status register */
        s->rgsr = value;
        break;

    case 0x144 ... 0x147:
        /* RGCFR, DMAMux - DMA request generator clear flag register */
        s->rgcfr = value;
        break;

    default:
        printf("%s: unimplemented write to 0x%" HWADDR_PRIx ", size %d, "
               "value 0x%" PRIx64 "\n", __func__, offset, size, value);
        break;
    }
}

static const MemoryRegionOps stm32g4_dmamux_mmio_ops = {
    .read = stm32g4_dmamux_mmio_read,
    .write = stm32g4_dmamux_mmio_write,
    .impl = {
        .max_access_size = 4
    }
};

static void stm32g4_dmamux_instance_init(Object *obj)
{
    STM32G4DMAMUXState *s = STM32G4_DMAMUX(obj);

    memory_region_init_io(&s->mmio, obj, &stm32g4_dmamux_mmio_ops, s,
                          STM32G4_DMAMUX_MMIO, STM32G4_DMAMUX_MMIO_SIZE);
    sysbus_init_mmio(SYS_BUS_DEVICE(obj), &s->mmio);
}

static void stm32g4_dmamux_realize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4DMAMUXState *s = STM32G4_DMAMUX(dev);
}

static void stm32g4_dmamux_reset(DeviceState *dev)
{
    STM32G4DMAMUXState *s = STM32G4_DMAMUX(dev);

    s->c0cr = 0x00000000;
    s->c1cr = 0x00000000;
    s->c2cr = 0x00000000;
    s->c3cr = 0x00000000;
    s->c4cr = 0x00000000;
    s->c5cr = 0x00000000;
    s->c6cr = 0x00000000;
    s->c7cr = 0x00000000;
    s->c8cr = 0x00000000;
    s->c9cr = 0x00000000;
    s->c10cr = 0x00000000;
    s->c11cr = 0x00000000;
    s->c12cr = 0x00000000;
    s->c13cr = 0x00000000;
    s->c14cr = 0x00000000;
    s->c15cr = 0x00000000;
    s->csr = 0x00000000;
    s->cfr = 0x00000000;
    s->rg0cr = 0x00000000;
    s->rg1cr = 0x00000000;
    s->rg2cr = 0x00000000;
    s->rg3cr = 0x00000000;
    s->rgsr = 0x00000000;
    s->rgcfr = 0x00000000;
}

static void stm32g4_dmamux_unrealize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4DMAMUXState *s = STM32G4_DMAMUX(dev);
}

static Property stm32g4_dmamux_properties[] = {
    DEFINE_PROP_END_OF_LIST()
};

static const VMStateDescription vmstate_stm32g4_dmamux = {
    .name = "stm32g4_dmamux",
    .version_id = 1,
    .fields = (VMStateField[]) {
        VMSTATE_UINT32(c0cr, STM32G4DMAMUXState),
        VMSTATE_UINT32(c1cr, STM32G4DMAMUXState),
        VMSTATE_UINT32(c2cr, STM32G4DMAMUXState),
        VMSTATE_UINT32(c3cr, STM32G4DMAMUXState),
        VMSTATE_UINT32(c4cr, STM32G4DMAMUXState),
        VMSTATE_UINT32(c5cr, STM32G4DMAMUXState),
        VMSTATE_UINT32(c6cr, STM32G4DMAMUXState),
        VMSTATE_UINT32(c7cr, STM32G4DMAMUXState),
        VMSTATE_UINT32(c8cr, STM32G4DMAMUXState),
        VMSTATE_UINT32(c9cr, STM32G4DMAMUXState),
        VMSTATE_UINT32(c10cr, STM32G4DMAMUXState),
        VMSTATE_UINT32(c11cr, STM32G4DMAMUXState),
        VMSTATE_UINT32(c12cr, STM32G4DMAMUXState),
        VMSTATE_UINT32(c13cr, STM32G4DMAMUXState),
        VMSTATE_UINT32(c14cr, STM32G4DMAMUXState),
        VMSTATE_UINT32(c15cr, STM32G4DMAMUXState),
        VMSTATE_UINT32(csr, STM32G4DMAMUXState),
        VMSTATE_UINT32(cfr, STM32G4DMAMUXState),
        VMSTATE_UINT32(rg0cr, STM32G4DMAMUXState),
        VMSTATE_UINT32(rg1cr, STM32G4DMAMUXState),
        VMSTATE_UINT32(rg2cr, STM32G4DMAMUXState),
        VMSTATE_UINT32(rg3cr, STM32G4DMAMUXState),
        VMSTATE_UINT32(rgsr, STM32G4DMAMUXState),
        VMSTATE_UINT32(rgcfr, STM32G4DMAMUXState),
        VMSTATE_END_OF_LIST()
    }
};

static void stm32g4_dmamux_class_init(ObjectClass *oc, void *opaque)
{
    DeviceClass *dc = DEVICE_CLASS(oc);

    dc->realize   = stm32g4_dmamux_realize;
    dc->reset     = stm32g4_dmamux_reset;
    dc->unrealize = stm32g4_dmamux_unrealize;
    dc->vmsd      = &vmstate_stm32g4_dmamux;
    device_class_set_props(dc, stm32g4_dmamux_properties);
}

static TypeInfo stm32g4_dmamux_info = {
    .name          = TYPE_STM32G4_DMAMUX,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(STM32G4DMAMUXState),
    .instance_init = stm32g4_dmamux_instance_init,
    .class_init    = stm32g4_dmamux_class_init
};

static void stm32g4_dmamux_register_types(void)
{
    type_register_static(&stm32g4_dmamux_info);
}

type_init(stm32g4_dmamux_register_types)
