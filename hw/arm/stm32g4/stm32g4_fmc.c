/* stm32g4_fmc.c */

#include "qemu/osdep.h"
#include "hw/irq.h"
#include "hw/qdev-properties.h"
#include "include/hw/arm/stm32g4/stm32g4_fmc.h"
#include "migration/vmstate.h"

#define STM32G4_FMC_MMIO TYPE_STM32G4_FMC "_mmio"
#define STM32G4_FMC_MMIO_SIZE 0x120

static uint64_t stm32g4_fmc_mmio_read(void *opaque, hwaddr offset,
                                      unsigned size)
{
    STM32G4FMCState *s = STM32G4_FMC(opaque);
    uint64_t ret = 0;

    switch (offset) {
    case 0x000 ... 0x003:
        /* BCR1, SRAM/NOR-Flash chip-select control register 1 */
        ret = s->bcr1;
        break;

    case 0x004 ... 0x007:
        /* BTR1, SRAM/NOR-Flash chip-select timing register 1 */
        ret = s->btr1;
        break;

    case 0x008 ... 0x00B:
        /* BCR2, SRAM/NOR-Flash chip-select control register 2 */
        ret = s->bcr2;
        break;

    case 0x00C ... 0x00F:
        /* BTR2, SRAM/NOR-Flash chip-select timing register 2 */
        ret = s->btr2;
        break;

    case 0x010 ... 0x013:
        /* BCR3, SRAM/NOR-Flash chip-select control register 3 */
        ret = s->bcr3;
        break;

    case 0x014 ... 0x017:
        /* BTR3, SRAM/NOR-Flash chip-select timing register 3 */
        ret = s->btr3;
        break;

    case 0x018 ... 0x01B:
        /* BCR4, SRAM/NOR-Flash chip-select control register 4 */
        ret = s->bcr4;
        break;

    case 0x01C ... 0x01F:
        /* BTR4, SRAM/NOR-Flash chip-select timing register 4 */
        ret = s->btr4;
        break;

    case 0x020 ... 0x023:
        /* PCSCNTR, PSRAM chip select counter register */
        ret = s->pcscntr;
        break;

    case 0x080 ... 0x083:
        /* PCR, PC Card/NAND Flash control register 3 */
        ret = s->pcr;
        break;

    case 0x084 ... 0x087:
        /* SR, FIFO status and interrupt register 3 */
        ret = s->sr;
        break;

    case 0x088 ... 0x08B:
        /* PMEM, Common memory space timing register 3 */
        ret = s->pmem;
        break;

    case 0x08C ... 0x08F:
        /* PATT, Attribute memory space timing register 3 */
        ret = s->patt;
        break;

    case 0x094 ... 0x097:
        /* ECCR, ECC result register 3 */
        ret = s->eccr;
        break;

    case 0x104 ... 0x107:
        /* BWTR1, SRAM/NOR-Flash write timing registers 1 */
        ret = s->bwtr1;
        break;

    case 0x10C ... 0x10F:
        /* BWTR2, SRAM/NOR-Flash write timing registers 2 */
        ret = s->bwtr2;
        break;

    case 0x114 ... 0x117:
        /* BWTR3, SRAM/NOR-Flash write timing registers 3 */
        ret = s->bwtr3;
        break;

    case 0x11C ... 0x11F:
        /* BWTR4, SRAM/NOR-Flash write timing registers 4 */
        ret = s->bwtr4;
        break;

    default:
        printf("%s: unimplemented read from 0x%" HWADDR_PRIx ", size %d\n",
               __func__, offset, size);
        break;
    }

    return ret;
}

static void stm32g4_fmc_mmio_write(void *opaque, hwaddr offset, uint64_t value,
                                   unsigned size)
{
    STM32G4FMCState *s = STM32G4_FMC(opaque);

    switch (offset) {
    case 0x000 ... 0x003:
        /* BCR1, SRAM/NOR-Flash chip-select control register 1 */
        s->bcr1 = value;
        break;

    case 0x004 ... 0x007:
        /* BTR1, SRAM/NOR-Flash chip-select timing register 1 */
        s->btr1 = value;
        break;

    case 0x008 ... 0x00B:
        /* BCR2, SRAM/NOR-Flash chip-select control register 2 */
        s->bcr2 = value;
        break;

    case 0x00C ... 0x00F:
        /* BTR2, SRAM/NOR-Flash chip-select timing register 2 */
        s->btr2 = value;
        break;

    case 0x010 ... 0x013:
        /* BCR3, SRAM/NOR-Flash chip-select control register 3 */
        s->bcr3 = value;
        break;

    case 0x014 ... 0x017:
        /* BTR3, SRAM/NOR-Flash chip-select timing register 3 */
        s->btr3 = value;
        break;

    case 0x018 ... 0x01B:
        /* BCR4, SRAM/NOR-Flash chip-select control register 4 */
        s->bcr4 = value;
        break;

    case 0x01C ... 0x01F:
        /* BTR4, SRAM/NOR-Flash chip-select timing register 4 */
        s->btr4 = value;
        break;

    case 0x020 ... 0x023:
        /* PCSCNTR, PSRAM chip select counter register */
        s->pcscntr = value;
        break;

    case 0x080 ... 0x083:
        /* PCR, PC Card/NAND Flash control register 3 */
        s->pcr = value;
        break;

    case 0x084 ... 0x087:
        /* SR, FIFO status and interrupt register 3 */
        s->sr = value;
        break;

    case 0x088 ... 0x08B:
        /* PMEM, Common memory space timing register 3 */
        s->pmem = value;
        break;

    case 0x08C ... 0x08F:
        /* PATT, Attribute memory space timing register 3 */
        s->patt = value;
        break;

    case 0x094 ... 0x097:
        /* ECCR, ECC result register 3 */
        s->eccr = value;
        break;

    case 0x104 ... 0x107:
        /* BWTR1, SRAM/NOR-Flash write timing registers 1 */
        s->bwtr1 = value;
        break;

    case 0x10C ... 0x10F:
        /* BWTR2, SRAM/NOR-Flash write timing registers 2 */
        s->bwtr2 = value;
        break;

    case 0x114 ... 0x117:
        /* BWTR3, SRAM/NOR-Flash write timing registers 3 */
        s->bwtr3 = value;
        break;

    case 0x11C ... 0x11F:
        /* BWTR4, SRAM/NOR-Flash write timing registers 4 */
        s->bwtr4 = value;
        break;

    default:
        printf("%s: unimplemented write to 0x%" HWADDR_PRIx ", size %d, "
               "value 0x%" PRIx64 "\n", __func__, offset, size, value);
        break;
    }
}

static const MemoryRegionOps stm32g4_fmc_mmio_ops = {
    .read = stm32g4_fmc_mmio_read,
    .write = stm32g4_fmc_mmio_write,
    .impl = {
        .max_access_size = 4
    }
};

static void stm32g4_fmc_instance_init(Object *obj)
{
    STM32G4FMCState *s = STM32G4_FMC(obj);

    memory_region_init_io(&s->mmio, obj, &stm32g4_fmc_mmio_ops, s,
                          STM32G4_FMC_MMIO, STM32G4_FMC_MMIO_SIZE);
    sysbus_init_mmio(SYS_BUS_DEVICE(obj), &s->mmio);
}

static void stm32g4_fmc_realize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4FMCState *s = STM32G4_FMC(dev);
}

static void stm32g4_fmc_reset(DeviceState *dev)
{
    STM32G4FMCState *s = STM32G4_FMC(dev);

    s->bcr1 = 0x000030D0;
    s->btr1 = 0xFFFFFFFF;
    s->bcr2 = 0x000030D0;
    s->btr2 = 0xFFFFFFFF;
    s->bcr3 = 0x000030D0;
    s->btr3 = 0xFFFFFFFF;
    s->bcr4 = 0x000030D0;
    s->btr4 = 0xFFFFFFFF;
    s->pcscntr = 0x00000000;
    s->pcr = 0x00000018;
    s->sr = 0x00000040;
    s->pmem = 0xFCFCFCFC;
    s->patt = 0xFCFCFCFC;
    s->eccr = 0x00000000;
    s->bwtr1 = 0x0FFFFFFF;
    s->bwtr2 = 0x0FFFFFFF;
    s->bwtr3 = 0x0FFFFFFF;
    s->bwtr4 = 0x0FFFFFFF;
}

static void stm32g4_fmc_unrealize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4FMCState *s = STM32G4_FMC(dev);
}

static Property stm32g4_fmc_properties[] = {
    DEFINE_PROP_END_OF_LIST()
};

static const VMStateDescription vmstate_stm32g4_fmc = {
    .name = "stm32g4_fmc",
    .version_id = 1,
    .fields = (VMStateField[]) {
        VMSTATE_UINT32(bcr1, STM32G4FMCState),
        VMSTATE_UINT32(btr1, STM32G4FMCState),
        VMSTATE_UINT32(bcr2, STM32G4FMCState),
        VMSTATE_UINT32(btr2, STM32G4FMCState),
        VMSTATE_UINT32(bcr3, STM32G4FMCState),
        VMSTATE_UINT32(btr3, STM32G4FMCState),
        VMSTATE_UINT32(bcr4, STM32G4FMCState),
        VMSTATE_UINT32(btr4, STM32G4FMCState),
        VMSTATE_UINT32(pcscntr, STM32G4FMCState),
        VMSTATE_UINT32(pcr, STM32G4FMCState),
        VMSTATE_UINT32(sr, STM32G4FMCState),
        VMSTATE_UINT32(pmem, STM32G4FMCState),
        VMSTATE_UINT32(patt, STM32G4FMCState),
        VMSTATE_UINT32(eccr, STM32G4FMCState),
        VMSTATE_UINT32(bwtr1, STM32G4FMCState),
        VMSTATE_UINT32(bwtr2, STM32G4FMCState),
        VMSTATE_UINT32(bwtr3, STM32G4FMCState),
        VMSTATE_UINT32(bwtr4, STM32G4FMCState),
        VMSTATE_END_OF_LIST()
    }
};

static void stm32g4_fmc_class_init(ObjectClass *oc, void *opaque)
{
    DeviceClass *dc = DEVICE_CLASS(oc);

    dc->realize   = stm32g4_fmc_realize;
    dc->reset     = stm32g4_fmc_reset;
    dc->unrealize = stm32g4_fmc_unrealize;
    dc->vmsd      = &vmstate_stm32g4_fmc;
    device_class_set_props(dc, stm32g4_fmc_properties);
}

static TypeInfo stm32g4_fmc_info = {
    .name          = TYPE_STM32G4_FMC,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(STM32G4FMCState),
    .instance_init = stm32g4_fmc_instance_init,
    .class_init    = stm32g4_fmc_class_init
};

static void stm32g4_fmc_register_types(void)
{
    type_register_static(&stm32g4_fmc_info);
}

type_init(stm32g4_fmc_register_types)
