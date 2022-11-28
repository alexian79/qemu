/* stm32g4_flash.c */

#include "qemu/osdep.h"
#include "hw/irq.h"
#include "hw/qdev-properties.h"
#include "include/hw/arm/stm32g4/stm32g4_flash.h"
#include "migration/vmstate.h"

#define STM32G4_FLASH_MMIO TYPE_STM32G4_FLASH "_mmio"
#define STM32G4_FLASH_MMIO_SIZE 0x78

static uint64_t stm32g4_flash_mmio_read(void *opaque, hwaddr offset,
                                        unsigned size)
{
    STM32G4FLASHState *s = STM32G4_FLASH(opaque);
    uint64_t ret = 0;

    switch (offset) {
    case 0x00 ... 0x03:
        /* ACR, Access control register */
        ret = s->acr;
        break;

    case 0x04 ... 0x07:
        /* PDKEYR, Power down key register */
        ret = s->pdkeyr;
        break;

    case 0x08 ... 0x0B:
        /* KEYR, Flash key register */
        ret = s->keyr;
        break;

    case 0x0C ... 0x0F:
        /* OPTKEYR, Option byte key register */
        ret = s->optkeyr;
        break;

    case 0x10 ... 0x13:
        /* SR, Status register */
        ret = s->sr;
        break;

    case 0x14 ... 0x17:
        /* CR, Flash control register */
        ret = s->cr;
        break;

    case 0x18 ... 0x1B:
        /* ECCR, Flash ECC register */
        ret = s->eccr;
        break;

    case 0x20 ... 0x23:
        /* OPTR, Flash option register */
        ret = s->optr;
        break;

    case 0x24 ... 0x27:
        /* PCROP1SR, Flash Bank 1 PCROP Start address register */
        ret = s->pcrop1sr;
        break;

    case 0x28 ... 0x2B:
        /* PCROP1ER, Flash Bank 1 PCROP End address register */
        ret = s->pcrop1er;
        break;

    case 0x2C ... 0x2F:
        /* WRP1AR, Flash Bank 1 WRP area A address register */
        ret = s->wrp1ar;
        break;

    case 0x30 ... 0x33:
        /* WRP1BR, Flash Bank 1 WRP area B address register */
        ret = s->wrp1br;
        break;

    case 0x44 ... 0x47:
        /* PCROP2SR, Flash PCROP2 Start address register */
        ret = s->pcrop2sr;
        break;

    case 0x48 ... 0x4B:
        /* PCROP2ER, Flash PCROP2 End address register */
        ret = s->pcrop2er;
        break;

    case 0x4C ... 0x4F:
        /* WRP2AR, Flash Bank 2 WRP area A address register */
        ret = s->wrp2ar;
        break;

    case 0x50 ... 0x53:
        /* WRP2BR, Flash Bank 2 WRP area B address register */
        ret = s->wrp2br;
        break;

    case 0x70 ... 0x73:
        /* SEC1R, Flash securable area bank1 register */
        ret = s->sec1r;
        break;

    case 0x74 ... 0x77:
        /* SEC2R, Flash securable area bank2 register */
        ret = s->sec2r;
        break;

    default:
        printf("%s: unimplemented read from 0x%" HWADDR_PRIx ", size %d\n",
               __func__, offset, size);
        break;
    }

    return ret;
}

static void stm32g4_flash_mmio_write(void *opaque, hwaddr offset,
                                     uint64_t value, unsigned size)
{
    STM32G4FLASHState *s = STM32G4_FLASH(opaque);

    switch (offset) {
    case 0x00 ... 0x03:
        /* ACR, Access control register */
        s->acr = value;
        break;

    case 0x04 ... 0x07:
        /* PDKEYR, Power down key register */
        s->pdkeyr = value;
        break;

    case 0x08 ... 0x0B:
        /* KEYR, Flash key register */
        s->keyr = value;
        break;

    case 0x0C ... 0x0F:
        /* OPTKEYR, Option byte key register */
        s->optkeyr = value;
        break;

    case 0x10 ... 0x13:
        /* SR, Status register */
        s->sr = value;
        break;

    case 0x14 ... 0x17:
        /* CR, Flash control register */
        s->cr = value;
        break;

    case 0x18 ... 0x1B:
        /* ECCR, Flash ECC register */
        s->eccr = value;
        break;

    case 0x20 ... 0x23:
        /* OPTR, Flash option register */
        s->optr = value;
        break;

    case 0x24 ... 0x27:
        /* PCROP1SR, Flash Bank 1 PCROP Start address register */
        s->pcrop1sr = value;
        break;

    case 0x28 ... 0x2B:
        /* PCROP1ER, Flash Bank 1 PCROP End address register */
        s->pcrop1er = value;
        break;

    case 0x2C ... 0x2F:
        /* WRP1AR, Flash Bank 1 WRP area A address register */
        s->wrp1ar = value;
        break;

    case 0x30 ... 0x33:
        /* WRP1BR, Flash Bank 1 WRP area B address register */
        s->wrp1br = value;
        break;

    case 0x44 ... 0x47:
        /* PCROP2SR, Flash PCROP2 Start address register */
        s->pcrop2sr = value;
        break;

    case 0x48 ... 0x4B:
        /* PCROP2ER, Flash PCROP2 End address register */
        s->pcrop2er = value;
        break;

    case 0x4C ... 0x4F:
        /* WRP2AR, Flash Bank 2 WRP area A address register */
        s->wrp2ar = value;
        break;

    case 0x50 ... 0x53:
        /* WRP2BR, Flash Bank 2 WRP area B address register */
        s->wrp2br = value;
        break;

    case 0x70 ... 0x73:
        /* SEC1R, Flash securable area bank1 register */
        s->sec1r = value;
        break;

    case 0x74 ... 0x77:
        /* SEC2R, Flash securable area bank2 register */
        s->sec2r = value;
        break;

    default:
        printf("%s: unimplemented write to 0x%" HWADDR_PRIx ", size %d, "
               "value 0x%" PRIx64 "\n", __func__, offset, size, value);
        break;
    }
}

static const MemoryRegionOps stm32g4_flash_mmio_ops = {
    .read = stm32g4_flash_mmio_read,
    .write = stm32g4_flash_mmio_write,
    .impl = {
        .max_access_size = 4
    }
};

static void stm32g4_flash_instance_init(Object *obj)
{
    STM32G4FLASHState *s = STM32G4_FLASH(obj);

    memory_region_init_io(&s->mmio, obj, &stm32g4_flash_mmio_ops, s,
                          STM32G4_FLASH_MMIO, STM32G4_FLASH_MMIO_SIZE);
    sysbus_init_mmio(SYS_BUS_DEVICE(obj), &s->mmio);
}

static void stm32g4_flash_realize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4FLASHState *s = STM32G4_FLASH(dev);
}

static void stm32g4_flash_reset(DeviceState *dev)
{
    STM32G4FLASHState *s = STM32G4_FLASH(dev);

    s->acr = 0x00000600;
    s->pdkeyr = 0x00000000;
    s->keyr = 0x00000000;
    s->optkeyr = 0x00000000;
    s->sr = 0x00000000;
    s->cr = 0xC0000000;
    s->eccr = 0x00000000;
    s->optr = 0xF0000000;
    s->pcrop1sr = 0xFFFF0000;
    s->pcrop1er = 0x0FFF0000;
    s->wrp1ar = 0x00000000;
    s->wrp1br = 0x00000000;
    s->pcrop2sr = 0x00000000;
    s->pcrop2er = 0x00000000;
    s->wrp2ar = 0x00000000;
    s->wrp2br = 0x00000000;
    s->sec1r = 0xFF00FF00;
    s->sec2r = 0xFF00FF00;
}

static void stm32g4_flash_unrealize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4FLASHState *s = STM32G4_FLASH(dev);
}

static Property stm32g4_flash_properties[] = {
    DEFINE_PROP_END_OF_LIST()
};

static const VMStateDescription vmstate_stm32g4_flash = {
    .name = "stm32g4_flash",
    .version_id = 1,
    .fields = (VMStateField[]) {
        VMSTATE_UINT32(acr, STM32G4FLASHState),
        VMSTATE_UINT32(pdkeyr, STM32G4FLASHState),
        VMSTATE_UINT32(keyr, STM32G4FLASHState),
        VMSTATE_UINT32(optkeyr, STM32G4FLASHState),
        VMSTATE_UINT32(sr, STM32G4FLASHState),
        VMSTATE_UINT32(cr, STM32G4FLASHState),
        VMSTATE_UINT32(eccr, STM32G4FLASHState),
        VMSTATE_UINT32(optr, STM32G4FLASHState),
        VMSTATE_UINT32(pcrop1sr, STM32G4FLASHState),
        VMSTATE_UINT32(pcrop1er, STM32G4FLASHState),
        VMSTATE_UINT32(wrp1ar, STM32G4FLASHState),
        VMSTATE_UINT32(wrp1br, STM32G4FLASHState),
        VMSTATE_UINT32(pcrop2sr, STM32G4FLASHState),
        VMSTATE_UINT32(pcrop2er, STM32G4FLASHState),
        VMSTATE_UINT32(wrp2ar, STM32G4FLASHState),
        VMSTATE_UINT32(wrp2br, STM32G4FLASHState),
        VMSTATE_UINT32(sec1r, STM32G4FLASHState),
        VMSTATE_UINT32(sec2r, STM32G4FLASHState),
        VMSTATE_END_OF_LIST()
    }
};

static void stm32g4_flash_class_init(ObjectClass *oc, void *opaque)
{
    DeviceClass *dc = DEVICE_CLASS(oc);

    dc->realize   = stm32g4_flash_realize;
    dc->reset     = stm32g4_flash_reset;
    dc->unrealize = stm32g4_flash_unrealize;
    dc->vmsd      = &vmstate_stm32g4_flash;
    device_class_set_props(dc, stm32g4_flash_properties);
}

static TypeInfo stm32g4_flash_info = {
    .name          = TYPE_STM32G4_FLASH,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(STM32G4FLASHState),
    .instance_init = stm32g4_flash_instance_init,
    .class_init    = stm32g4_flash_class_init
};

static void stm32g4_flash_register_types(void)
{
    type_register_static(&stm32g4_flash_info);
}

type_init(stm32g4_flash_register_types)
