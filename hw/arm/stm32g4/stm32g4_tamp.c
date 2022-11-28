/* stm32g4_tamp.c */

#include "qemu/osdep.h"
#include "hw/irq.h"
#include "hw/qdev-properties.h"
#include "include/hw/arm/stm32g4/stm32g4_tamp.h"
#include "migration/vmstate.h"

#define STM32G4_TAMP_MMIO TYPE_STM32G4_TAMP "_mmio"
#define STM32G4_TAMP_MMIO_SIZE 0x180

static uint64_t stm32g4_tamp_mmio_read(void *opaque, hwaddr offset,
                                       unsigned size)
{
    STM32G4TAMPState *s = STM32G4_TAMP(opaque);
    uint64_t ret = 0;

    switch (offset) {
    case 0x000 ... 0x003:
        /* CR1, control register 1 */
        ret = s->cr1;
        break;

    case 0x004 ... 0x007:
        /* CR2, control register 2 */
        ret = s->cr2;
        break;

    case 0x00C ... 0x00F:
        /* FLTCR, TAMP filter control register */
        ret = s->fltcr;
        break;

    case 0x02C ... 0x02F:
        /* IER, TAMP interrupt enable register */
        ret = s->ier;
        break;

    case 0x030 ... 0x033:
        /* SR, TAMP status register */
        ret = s->sr;
        break;

    case 0x034 ... 0x037:
        /* MISR, TAMP masked interrupt status register */
        ret = s->misr;
        break;

    case 0x03C ... 0x03F:
        /* SCR, TAMP status clear register */
        ret = s->scr;
        break;

    case 0x100 ... 0x103:
        /* BKP0R, TAMP backup register */
        ret = s->bkp0r;
        break;

    case 0x104 ... 0x107:
        /* BKP1R, TAMP backup register */
        ret = s->bkp1r;
        break;

    case 0x108 ... 0x10B:
        /* BKP2R, TAMP backup register */
        ret = s->bkp2r;
        break;

    case 0x10C ... 0x10F:
        /* BKP3R, TAMP backup register */
        ret = s->bkp3r;
        break;

    case 0x110 ... 0x113:
        /* BKP4R, TAMP backup register */
        ret = s->bkp4r;
        break;

    case 0x114 ... 0x117:
        /* BKP5R, TAMP backup register */
        ret = s->bkp5r;
        break;

    case 0x118 ... 0x11B:
        /* BKP6R, TAMP backup register */
        ret = s->bkp6r;
        break;

    case 0x11C ... 0x11F:
        /* BKP7R, TAMP backup register */
        ret = s->bkp7r;
        break;

    case 0x120 ... 0x123:
        /* BKP8R, TAMP backup register */
        ret = s->bkp8r;
        break;

    case 0x124 ... 0x127:
        /* BKP9R, TAMP backup register */
        ret = s->bkp9r;
        break;

    case 0x128 ... 0x12B:
        /* BKP10R, TAMP backup register */
        ret = s->bkp10r;
        break;

    case 0x12C ... 0x12F:
        /* BKP11R, TAMP backup register */
        ret = s->bkp11r;
        break;

    case 0x130 ... 0x133:
        /* BKP12R, TAMP backup register */
        ret = s->bkp12r;
        break;

    case 0x134 ... 0x137:
        /* BKP13R, TAMP backup register */
        ret = s->bkp13r;
        break;

    case 0x138 ... 0x13B:
        /* BKP14R, TAMP backup register */
        ret = s->bkp14r;
        break;

    case 0x13C ... 0x13F:
        /* BKP15R, TAMP backup register */
        ret = s->bkp15r;
        break;

    case 0x140 ... 0x143:
        /* BKP16R, TAMP backup register */
        ret = s->bkp16r;
        break;

    case 0x144 ... 0x147:
        /* BKP17R, TAMP backup register */
        ret = s->bkp17r;
        break;

    case 0x148 ... 0x14B:
        /* BKP18R, TAMP backup register */
        ret = s->bkp18r;
        break;

    case 0x14C ... 0x14F:
        /* BKP19R, TAMP backup register */
        ret = s->bkp19r;
        break;

    case 0x150 ... 0x153:
        /* BKP20R, TAMP backup register */
        ret = s->bkp20r;
        break;

    case 0x154 ... 0x157:
        /* BKP21R, TAMP backup register */
        ret = s->bkp21r;
        break;

    case 0x158 ... 0x15B:
        /* BKP22R, TAMP backup register */
        ret = s->bkp22r;
        break;

    case 0x15C ... 0x15F:
        /* BKP23R, TAMP backup register */
        ret = s->bkp23r;
        break;

    case 0x160 ... 0x163:
        /* BKP24R, TAMP backup register */
        ret = s->bkp24r;
        break;

    case 0x164 ... 0x167:
        /* BKP25R, TAMP backup register */
        ret = s->bkp25r;
        break;

    case 0x168 ... 0x16B:
        /* BKP26R, TAMP backup register */
        ret = s->bkp26r;
        break;

    case 0x16C ... 0x16F:
        /* BKP27R, TAMP backup register */
        ret = s->bkp27r;
        break;

    case 0x170 ... 0x173:
        /* BKP28R, TAMP backup register */
        ret = s->bkp28r;
        break;

    case 0x174 ... 0x177:
        /* BKP29R, TAMP backup register */
        ret = s->bkp29r;
        break;

    case 0x178 ... 0x17B:
        /* BKP30R, TAMP backup register */
        ret = s->bkp30r;
        break;

    case 0x17C ... 0x17F:
        /* BKP31R, TAMP backup register */
        ret = s->bkp31r;
        break;

    default:
        printf("%s: unimplemented read from 0x%" HWADDR_PRIx ", size %d\n",
               __func__, offset, size);
        break;
    }

    return ret;
}

static void stm32g4_tamp_mmio_write(void *opaque, hwaddr offset, uint64_t value,
                                    unsigned size)
{
    STM32G4TAMPState *s = STM32G4_TAMP(opaque);

    switch (offset) {
    case 0x000 ... 0x003:
        /* CR1, control register 1 */
        s->cr1 = value;
        break;

    case 0x004 ... 0x007:
        /* CR2, control register 2 */
        s->cr2 = value;
        break;

    case 0x00C ... 0x00F:
        /* FLTCR, TAMP filter control register */
        s->fltcr = value;
        break;

    case 0x02C ... 0x02F:
        /* IER, TAMP interrupt enable register */
        s->ier = value;
        break;

    case 0x030 ... 0x033:
        /* SR, TAMP status register */
        s->sr = value;
        break;

    case 0x034 ... 0x037:
        /* MISR, TAMP masked interrupt status register */
        s->misr = value;
        break;

    case 0x03C ... 0x03F:
        /* SCR, TAMP status clear register */
        s->scr = value;
        break;

    case 0x100 ... 0x103:
        /* BKP0R, TAMP backup register */
        s->bkp0r = value;
        break;

    case 0x104 ... 0x107:
        /* BKP1R, TAMP backup register */
        s->bkp1r = value;
        break;

    case 0x108 ... 0x10B:
        /* BKP2R, TAMP backup register */
        s->bkp2r = value;
        break;

    case 0x10C ... 0x10F:
        /* BKP3R, TAMP backup register */
        s->bkp3r = value;
        break;

    case 0x110 ... 0x113:
        /* BKP4R, TAMP backup register */
        s->bkp4r = value;
        break;

    case 0x114 ... 0x117:
        /* BKP5R, TAMP backup register */
        s->bkp5r = value;
        break;

    case 0x118 ... 0x11B:
        /* BKP6R, TAMP backup register */
        s->bkp6r = value;
        break;

    case 0x11C ... 0x11F:
        /* BKP7R, TAMP backup register */
        s->bkp7r = value;
        break;

    case 0x120 ... 0x123:
        /* BKP8R, TAMP backup register */
        s->bkp8r = value;
        break;

    case 0x124 ... 0x127:
        /* BKP9R, TAMP backup register */
        s->bkp9r = value;
        break;

    case 0x128 ... 0x12B:
        /* BKP10R, TAMP backup register */
        s->bkp10r = value;
        break;

    case 0x12C ... 0x12F:
        /* BKP11R, TAMP backup register */
        s->bkp11r = value;
        break;

    case 0x130 ... 0x133:
        /* BKP12R, TAMP backup register */
        s->bkp12r = value;
        break;

    case 0x134 ... 0x137:
        /* BKP13R, TAMP backup register */
        s->bkp13r = value;
        break;

    case 0x138 ... 0x13B:
        /* BKP14R, TAMP backup register */
        s->bkp14r = value;
        break;

    case 0x13C ... 0x13F:
        /* BKP15R, TAMP backup register */
        s->bkp15r = value;
        break;

    case 0x140 ... 0x143:
        /* BKP16R, TAMP backup register */
        s->bkp16r = value;
        break;

    case 0x144 ... 0x147:
        /* BKP17R, TAMP backup register */
        s->bkp17r = value;
        break;

    case 0x148 ... 0x14B:
        /* BKP18R, TAMP backup register */
        s->bkp18r = value;
        break;

    case 0x14C ... 0x14F:
        /* BKP19R, TAMP backup register */
        s->bkp19r = value;
        break;

    case 0x150 ... 0x153:
        /* BKP20R, TAMP backup register */
        s->bkp20r = value;
        break;

    case 0x154 ... 0x157:
        /* BKP21R, TAMP backup register */
        s->bkp21r = value;
        break;

    case 0x158 ... 0x15B:
        /* BKP22R, TAMP backup register */
        s->bkp22r = value;
        break;

    case 0x15C ... 0x15F:
        /* BKP23R, TAMP backup register */
        s->bkp23r = value;
        break;

    case 0x160 ... 0x163:
        /* BKP24R, TAMP backup register */
        s->bkp24r = value;
        break;

    case 0x164 ... 0x167:
        /* BKP25R, TAMP backup register */
        s->bkp25r = value;
        break;

    case 0x168 ... 0x16B:
        /* BKP26R, TAMP backup register */
        s->bkp26r = value;
        break;

    case 0x16C ... 0x16F:
        /* BKP27R, TAMP backup register */
        s->bkp27r = value;
        break;

    case 0x170 ... 0x173:
        /* BKP28R, TAMP backup register */
        s->bkp28r = value;
        break;

    case 0x174 ... 0x177:
        /* BKP29R, TAMP backup register */
        s->bkp29r = value;
        break;

    case 0x178 ... 0x17B:
        /* BKP30R, TAMP backup register */
        s->bkp30r = value;
        break;

    case 0x17C ... 0x17F:
        /* BKP31R, TAMP backup register */
        s->bkp31r = value;
        break;

    default:
        printf("%s: unimplemented write to 0x%" HWADDR_PRIx ", size %d, "
               "value 0x%" PRIx64 "\n", __func__, offset, size, value);
        break;
    }
}

static const MemoryRegionOps stm32g4_tamp_mmio_ops = {
    .read = stm32g4_tamp_mmio_read,
    .write = stm32g4_tamp_mmio_write,
    .impl = {
        .max_access_size = 4
    }
};

static void stm32g4_tamp_instance_init(Object *obj)
{
    STM32G4TAMPState *s = STM32G4_TAMP(obj);

    memory_region_init_io(&s->mmio, obj, &stm32g4_tamp_mmio_ops, s,
                          STM32G4_TAMP_MMIO, STM32G4_TAMP_MMIO_SIZE);
    sysbus_init_mmio(SYS_BUS_DEVICE(obj), &s->mmio);
}

static void stm32g4_tamp_realize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4TAMPState *s = STM32G4_TAMP(dev);
}

static void stm32g4_tamp_reset(DeviceState *dev)
{
    STM32G4TAMPState *s = STM32G4_TAMP(dev);

    s->cr1 = 0xFFFF0000;
    s->cr2 = 0x00000000;
    s->fltcr = 0x00000000;
    s->ier = 0x00000000;
    s->sr = 0x00000000;
    s->misr = 0x00000000;
    s->scr = 0x00000000;
    s->bkp0r = 0x00000000;
    s->bkp1r = 0x00000000;
    s->bkp2r = 0x00000000;
    s->bkp3r = 0x00000000;
    s->bkp4r = 0x00000000;
    s->bkp5r = 0x00000000;
    s->bkp6r = 0x00000000;
    s->bkp7r = 0x00000000;
    s->bkp8r = 0x00000000;
    s->bkp9r = 0x00000000;
    s->bkp10r = 0x00000000;
    s->bkp11r = 0x00000000;
    s->bkp12r = 0x00000000;
    s->bkp13r = 0x00000000;
    s->bkp14r = 0x00000000;
    s->bkp15r = 0x00000000;
    s->bkp16r = 0x00000000;
    s->bkp17r = 0x00000000;
    s->bkp18r = 0x00000000;
    s->bkp19r = 0x00000000;
    s->bkp20r = 0x00000000;
    s->bkp21r = 0x00000000;
    s->bkp22r = 0x00000000;
    s->bkp23r = 0x00000000;
    s->bkp24r = 0x00000000;
    s->bkp25r = 0x00000000;
    s->bkp26r = 0x00000000;
    s->bkp27r = 0x00000000;
    s->bkp28r = 0x00000000;
    s->bkp29r = 0x00000000;
    s->bkp30r = 0x00000000;
    s->bkp31r = 0x00000000;
}

static void stm32g4_tamp_unrealize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4TAMPState *s = STM32G4_TAMP(dev);
}

static Property stm32g4_tamp_properties[] = {
    DEFINE_PROP_END_OF_LIST()
};

static const VMStateDescription vmstate_stm32g4_tamp = {
    .name = "stm32g4_tamp",
    .version_id = 1,
    .fields = (VMStateField[]) {
        VMSTATE_UINT32(cr1, STM32G4TAMPState),
        VMSTATE_UINT32(cr2, STM32G4TAMPState),
        VMSTATE_UINT32(fltcr, STM32G4TAMPState),
        VMSTATE_UINT32(ier, STM32G4TAMPState),
        VMSTATE_UINT32(sr, STM32G4TAMPState),
        VMSTATE_UINT32(misr, STM32G4TAMPState),
        VMSTATE_UINT32(scr, STM32G4TAMPState),
        VMSTATE_UINT32(bkp0r, STM32G4TAMPState),
        VMSTATE_UINT32(bkp1r, STM32G4TAMPState),
        VMSTATE_UINT32(bkp2r, STM32G4TAMPState),
        VMSTATE_UINT32(bkp3r, STM32G4TAMPState),
        VMSTATE_UINT32(bkp4r, STM32G4TAMPState),
        VMSTATE_UINT32(bkp5r, STM32G4TAMPState),
        VMSTATE_UINT32(bkp6r, STM32G4TAMPState),
        VMSTATE_UINT32(bkp7r, STM32G4TAMPState),
        VMSTATE_UINT32(bkp8r, STM32G4TAMPState),
        VMSTATE_UINT32(bkp9r, STM32G4TAMPState),
        VMSTATE_UINT32(bkp10r, STM32G4TAMPState),
        VMSTATE_UINT32(bkp11r, STM32G4TAMPState),
        VMSTATE_UINT32(bkp12r, STM32G4TAMPState),
        VMSTATE_UINT32(bkp13r, STM32G4TAMPState),
        VMSTATE_UINT32(bkp14r, STM32G4TAMPState),
        VMSTATE_UINT32(bkp15r, STM32G4TAMPState),
        VMSTATE_UINT32(bkp16r, STM32G4TAMPState),
        VMSTATE_UINT32(bkp17r, STM32G4TAMPState),
        VMSTATE_UINT32(bkp18r, STM32G4TAMPState),
        VMSTATE_UINT32(bkp19r, STM32G4TAMPState),
        VMSTATE_UINT32(bkp20r, STM32G4TAMPState),
        VMSTATE_UINT32(bkp21r, STM32G4TAMPState),
        VMSTATE_UINT32(bkp22r, STM32G4TAMPState),
        VMSTATE_UINT32(bkp23r, STM32G4TAMPState),
        VMSTATE_UINT32(bkp24r, STM32G4TAMPState),
        VMSTATE_UINT32(bkp25r, STM32G4TAMPState),
        VMSTATE_UINT32(bkp26r, STM32G4TAMPState),
        VMSTATE_UINT32(bkp27r, STM32G4TAMPState),
        VMSTATE_UINT32(bkp28r, STM32G4TAMPState),
        VMSTATE_UINT32(bkp29r, STM32G4TAMPState),
        VMSTATE_UINT32(bkp30r, STM32G4TAMPState),
        VMSTATE_UINT32(bkp31r, STM32G4TAMPState),
        VMSTATE_END_OF_LIST()
    }
};

static void stm32g4_tamp_class_init(ObjectClass *oc, void *opaque)
{
    DeviceClass *dc = DEVICE_CLASS(oc);

    dc->realize   = stm32g4_tamp_realize;
    dc->reset     = stm32g4_tamp_reset;
    dc->unrealize = stm32g4_tamp_unrealize;
    dc->vmsd      = &vmstate_stm32g4_tamp;
    device_class_set_props(dc, stm32g4_tamp_properties);
}

static TypeInfo stm32g4_tamp_info = {
    .name          = TYPE_STM32G4_TAMP,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(STM32G4TAMPState),
    .instance_init = stm32g4_tamp_instance_init,
    .class_init    = stm32g4_tamp_class_init
};

static void stm32g4_tamp_register_types(void)
{
    type_register_static(&stm32g4_tamp_info);
}

type_init(stm32g4_tamp_register_types)
