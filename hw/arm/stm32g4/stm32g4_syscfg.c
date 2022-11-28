/* stm32g4_syscfg.c */

#include "qemu/osdep.h"
#include "hw/irq.h"
#include "hw/qdev-properties.h"
#include "include/hw/arm/stm32g4/stm32g4_syscfg.h"
#include "migration/vmstate.h"

#define STM32G4_SYSCFG_MMIO TYPE_STM32G4_SYSCFG "_mmio"
#define STM32G4_SYSCFG_MMIO_SIZE 0x28

static uint64_t stm32g4_syscfg_mmio_read(void *opaque, hwaddr offset,
                                         unsigned size)
{
    STM32G4SYSCFGState *s = STM32G4_SYSCFG(opaque);
    uint64_t ret = 0;

    switch (offset) {
    case 0x00 ... 0x03:
        /* MEMRMP, Remap Memory register */
        ret = s->memrmp;
        break;

    case 0x04 ... 0x07:
        /* CFGR1, peripheral mode configuration register */
        ret = s->cfgr1;
        break;

    case 0x08 ... 0x0B:
        /* EXTICR1, external interrupt configuration register 1 */
        ret = s->exticr1;
        break;

    case 0x0C ... 0x0F:
        /* EXTICR2, external interrupt configuration register 2 */
        ret = s->exticr2;
        break;

    case 0x10 ... 0x13:
        /* EXTICR3, external interrupt configuration register 3 */
        ret = s->exticr3;
        break;

    case 0x14 ... 0x17:
        /* EXTICR4, external interrupt configuration register 4 */
        ret = s->exticr4;
        break;

    case 0x18 ... 0x1B:
        /* SCSR, CCM SRAM control and status register */
        ret = s->scsr;
        break;

    case 0x1C ... 0x1F:
        /* CFGR2, configuration register 2 */
        ret = s->cfgr2;
        break;

    case 0x20 ... 0x23:
        /* SWPR, SRAM Write protection register 1 */
        ret = s->swpr;
        break;

    case 0x24 ... 0x27:
        /* SKR, SRAM2 Key Register */
        ret = s->skr;
        break;

    default:
        printf("%s: unimplemented read from 0x%" HWADDR_PRIx ", size %d\n",
               __func__, offset, size);
        break;
    }

    return ret;
}

static void stm32g4_syscfg_mmio_write(void *opaque, hwaddr offset,
                                      uint64_t value, unsigned size)
{
    STM32G4SYSCFGState *s = STM32G4_SYSCFG(opaque);

    switch (offset) {
    case 0x00 ... 0x03:
        /* MEMRMP, Remap Memory register */
        s->memrmp = value;
        break;

    case 0x04 ... 0x07:
        /* CFGR1, peripheral mode configuration register */
        s->cfgr1 = value;
        break;

    case 0x08 ... 0x0B:
        /* EXTICR1, external interrupt configuration register 1 */
        s->exticr1 = value;
        break;

    case 0x0C ... 0x0F:
        /* EXTICR2, external interrupt configuration register 2 */
        s->exticr2 = value;
        break;

    case 0x10 ... 0x13:
        /* EXTICR3, external interrupt configuration register 3 */
        s->exticr3 = value;
        break;

    case 0x14 ... 0x17:
        /* EXTICR4, external interrupt configuration register 4 */
        s->exticr4 = value;
        break;

    case 0x18 ... 0x1B:
        /* SCSR, CCM SRAM control and status register */
        s->scsr = value;
        break;

    case 0x1C ... 0x1F:
        /* CFGR2, configuration register 2 */
        s->cfgr2 = value;
        break;

    case 0x20 ... 0x23:
        /* SWPR, SRAM Write protection register 1 */
        s->swpr = value;
        break;

    case 0x24 ... 0x27:
        /* SKR, SRAM2 Key Register */
        s->skr = value;
        break;

    default:
        printf("%s: unimplemented write to 0x%" HWADDR_PRIx ", size %d, "
               "value 0x%" PRIx64 "\n", __func__, offset, size, value);
        break;
    }
}

static const MemoryRegionOps stm32g4_syscfg_mmio_ops = {
    .read = stm32g4_syscfg_mmio_read,
    .write = stm32g4_syscfg_mmio_write,
    .impl = {
        .max_access_size = 4
    }
};

static void stm32g4_syscfg_instance_init(Object *obj)
{
    STM32G4SYSCFGState *s = STM32G4_SYSCFG(obj);

    memory_region_init_io(&s->mmio, obj, &stm32g4_syscfg_mmio_ops, s,
                          STM32G4_SYSCFG_MMIO, STM32G4_SYSCFG_MMIO_SIZE);
    sysbus_init_mmio(SYS_BUS_DEVICE(obj), &s->mmio);
}

static void stm32g4_syscfg_realize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4SYSCFGState *s = STM32G4_SYSCFG(dev);
}

static void stm32g4_syscfg_reset(DeviceState *dev)
{
    STM32G4SYSCFGState *s = STM32G4_SYSCFG(dev);

    s->memrmp = 0x00000000;
    s->cfgr1 = 0x7C000001;
    s->exticr1 = 0x0000;
    s->exticr2 = 0x0000;
    s->exticr3 = 0x0000;
    s->exticr4 = 0x0000;
    s->scsr = 0x00000000;
    s->cfgr2 = 0x00000000;
    s->swpr = 0x00000000;
    s->skr = 0x00000000;
}

static void stm32g4_syscfg_unrealize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4SYSCFGState *s = STM32G4_SYSCFG(dev);
}

static Property stm32g4_syscfg_properties[] = {
    DEFINE_PROP_END_OF_LIST()
};

static const VMStateDescription vmstate_stm32g4_syscfg = {
    .name = "stm32g4_syscfg",
    .version_id = 1,
    .fields = (VMStateField[]) {
        VMSTATE_UINT32(memrmp, STM32G4SYSCFGState),
        VMSTATE_UINT32(cfgr1, STM32G4SYSCFGState),
        VMSTATE_UINT32(exticr1, STM32G4SYSCFGState),
        VMSTATE_UINT32(exticr2, STM32G4SYSCFGState),
        VMSTATE_UINT32(exticr3, STM32G4SYSCFGState),
        VMSTATE_UINT32(exticr4, STM32G4SYSCFGState),
        VMSTATE_UINT32(scsr, STM32G4SYSCFGState),
        VMSTATE_UINT32(cfgr2, STM32G4SYSCFGState),
        VMSTATE_UINT32(swpr, STM32G4SYSCFGState),
        VMSTATE_UINT32(skr, STM32G4SYSCFGState),
        VMSTATE_END_OF_LIST()
    }
};

static void stm32g4_syscfg_class_init(ObjectClass *oc, void *opaque)
{
    DeviceClass *dc = DEVICE_CLASS(oc);

    dc->realize   = stm32g4_syscfg_realize;
    dc->reset     = stm32g4_syscfg_reset;
    dc->unrealize = stm32g4_syscfg_unrealize;
    dc->vmsd      = &vmstate_stm32g4_syscfg;
    device_class_set_props(dc, stm32g4_syscfg_properties);
}

static TypeInfo stm32g4_syscfg_info = {
    .name          = TYPE_STM32G4_SYSCFG,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(STM32G4SYSCFGState),
    .instance_init = stm32g4_syscfg_instance_init,
    .class_init    = stm32g4_syscfg_class_init
};

static void stm32g4_syscfg_register_types(void)
{
    type_register_static(&stm32g4_syscfg_info);
}

type_init(stm32g4_syscfg_register_types)
