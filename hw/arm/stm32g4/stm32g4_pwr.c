/* stm32g4_pwr.c */

#include "qemu/osdep.h"
#include "hw/irq.h"
#include "hw/qdev-properties.h"
#include "include/hw/arm/stm32g4/stm32g4_pwr.h"
#include "migration/vmstate.h"

#define STM32G4_PWR_MMIO TYPE_STM32G4_PWR "_mmio"
#define STM32G4_PWR_MMIO_SIZE 0x84

static uint64_t stm32g4_pwr_mmio_read(void *opaque, hwaddr offset,
                                      unsigned size)
{
    STM32G4PWRState *s = STM32G4_PWR(opaque);
    uint64_t ret = 0;

    switch (offset) {
    case 0x00 ... 0x03:
        /* CR1, Power control register 1 */
        ret = s->cr1;
        break;

    case 0x04 ... 0x07:
        /* CR2, Power control register 2 */
        ret = s->cr2;
        break;

    case 0x08 ... 0x0B:
        /* CR3, Power control register 3 */
        ret = s->cr3;
        break;

    case 0x0C ... 0x0F:
        /* CR4, Power control register 4 */
        ret = s->cr4;
        break;

    case 0x10 ... 0x13:
        /* SR1, Power status register 1 */
        ret = s->sr1;
        break;

    case 0x14 ... 0x17:
        /* SR2, Power status register 2 */
        ret = s->sr2;
        break;

    case 0x18 ... 0x1B:
        /* SCR, Power status clear register */
        ret = s->scr;
        break;

    case 0x20 ... 0x23:
        /* PUCRA, Power Port A pull-up control register */
        ret = s->pucra;
        break;

    case 0x24 ... 0x27:
        /* PDCRA, Power Port A pull-down control register */
        ret = s->pdcra;
        break;

    case 0x28 ... 0x2B:
        /* PUCRB, Power Port B pull-up control register */
        ret = s->pucrb;
        break;

    case 0x2C ... 0x2F:
        /* PDCRB, Power Port B pull-down control register */
        ret = s->pdcrb;
        break;

    case 0x30 ... 0x33:
        /* PUCRC, Power Port C pull-up control register */
        ret = s->pucrc;
        break;

    case 0x34 ... 0x37:
        /* PDCRC, Power Port C pull-down control register */
        ret = s->pdcrc;
        break;

    case 0x38 ... 0x3B:
        /* PUCRD, Power Port D pull-up control register */
        ret = s->pucrd;
        break;

    case 0x3C ... 0x3F:
        /* PDCRD, Power Port D pull-down control register */
        ret = s->pdcrd;
        break;

    case 0x40 ... 0x43:
        /* PUCRE, Power Port E pull-up control register */
        ret = s->pucre;
        break;

    case 0x44 ... 0x47:
        /* PDCRE, Power Port E pull-down control register */
        ret = s->pdcre;
        break;

    case 0x48 ... 0x4B:
        /* PUCRF, Power Port F pull-up control register */
        ret = s->pucrf;
        break;

    case 0x4C ... 0x4F:
        /* PDCRF, Power Port F pull-down control register */
        ret = s->pdcrf;
        break;

    case 0x50 ... 0x53:
        /* PUCRG, Power Port G pull-up control register */
        ret = s->pucrg;
        break;

    case 0x54 ... 0x57:
        /* PDCRG, Power Port G pull-down control register */
        ret = s->pdcrg;
        break;

    case 0x80 ... 0x83:
        /* CR5, Power control register 5 */
        ret = s->cr5;
        break;

    default:
        printf("%s: unimplemented read from 0x%" HWADDR_PRIx ", size %d\n",
               __func__, offset, size);
        break;
    }

    return ret;
}

static void stm32g4_pwr_mmio_write(void *opaque, hwaddr offset, uint64_t value,
                                   unsigned size)
{
    STM32G4PWRState *s = STM32G4_PWR(opaque);

    switch (offset) {
    case 0x00 ... 0x03:
        /* CR1, Power control register 1 */
        s->cr1 = value;
        break;

    case 0x04 ... 0x07:
        /* CR2, Power control register 2 */
        s->cr2 = value;
        break;

    case 0x08 ... 0x0B:
        /* CR3, Power control register 3 */
        s->cr3 = value;
        break;

    case 0x0C ... 0x0F:
        /* CR4, Power control register 4 */
        s->cr4 = value;
        break;

    case 0x10 ... 0x13:
        /* SR1, Power status register 1 */
        s->sr1 = value;
        break;

    case 0x14 ... 0x17:
        /* SR2, Power status register 2 */
        s->sr2 = value;
        break;

    case 0x18 ... 0x1B:
        /* SCR, Power status clear register */
        s->scr = value;
        break;

    case 0x20 ... 0x23:
        /* PUCRA, Power Port A pull-up control register */
        s->pucra = value;
        break;

    case 0x24 ... 0x27:
        /* PDCRA, Power Port A pull-down control register */
        s->pdcra = value;
        break;

    case 0x28 ... 0x2B:
        /* PUCRB, Power Port B pull-up control register */
        s->pucrb = value;
        break;

    case 0x2C ... 0x2F:
        /* PDCRB, Power Port B pull-down control register */
        s->pdcrb = value;
        break;

    case 0x30 ... 0x33:
        /* PUCRC, Power Port C pull-up control register */
        s->pucrc = value;
        break;

    case 0x34 ... 0x37:
        /* PDCRC, Power Port C pull-down control register */
        s->pdcrc = value;
        break;

    case 0x38 ... 0x3B:
        /* PUCRD, Power Port D pull-up control register */
        s->pucrd = value;
        break;

    case 0x3C ... 0x3F:
        /* PDCRD, Power Port D pull-down control register */
        s->pdcrd = value;
        break;

    case 0x40 ... 0x43:
        /* PUCRE, Power Port E pull-up control register */
        s->pucre = value;
        break;

    case 0x44 ... 0x47:
        /* PDCRE, Power Port E pull-down control register */
        s->pdcre = value;
        break;

    case 0x48 ... 0x4B:
        /* PUCRF, Power Port F pull-up control register */
        s->pucrf = value;
        break;

    case 0x4C ... 0x4F:
        /* PDCRF, Power Port F pull-down control register */
        s->pdcrf = value;
        break;

    case 0x50 ... 0x53:
        /* PUCRG, Power Port G pull-up control register */
        s->pucrg = value;
        break;

    case 0x54 ... 0x57:
        /* PDCRG, Power Port G pull-down control register */
        s->pdcrg = value;
        break;

    case 0x80 ... 0x83:
        /* CR5, Power control register 5 */
        s->cr5 = value;
        break;

    default:
        printf("%s: unimplemented write to 0x%" HWADDR_PRIx ", size %d, "
               "value 0x%" PRIx64 "\n", __func__, offset, size, value);
        break;
    }
}

static const MemoryRegionOps stm32g4_pwr_mmio_ops = {
    .read = stm32g4_pwr_mmio_read,
    .write = stm32g4_pwr_mmio_write,
    .impl = {
        .max_access_size = 4
    }
};

static void stm32g4_pwr_instance_init(Object *obj)
{
    STM32G4PWRState *s = STM32G4_PWR(obj);

    memory_region_init_io(&s->mmio, obj, &stm32g4_pwr_mmio_ops, s,
                          STM32G4_PWR_MMIO, STM32G4_PWR_MMIO_SIZE);
    sysbus_init_mmio(SYS_BUS_DEVICE(obj), &s->mmio);
}

static void stm32g4_pwr_realize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4PWRState *s = STM32G4_PWR(dev);
}

static void stm32g4_pwr_reset(DeviceState *dev)
{
    STM32G4PWRState *s = STM32G4_PWR(dev);

    s->cr1 = 0x00000200;
    s->cr2 = 0x00000000;
    s->cr3 = 0X00008000;
    s->cr4 = 0x00000000;
    s->sr1 = 0x00000000;
    s->sr2 = 0x00000000;
    s->scr = 0x00000000;
    s->pucra = 0x00000000;
    s->pdcra = 0x00000000;
    s->pucrb = 0x00000000;
    s->pdcrb = 0x00000000;
    s->pucrc = 0x00000000;
    s->pdcrc = 0x00000000;
    s->pucrd = 0x00000000;
    s->pdcrd = 0x00000000;
    s->pucre = 0x00000000;
    s->pdcre = 0x00000000;
    s->pucrf = 0x00000000;
    s->pdcrf = 0x00000000;
    s->pucrg = 0x00000000;
    s->pdcrg = 0x00000000;
    s->cr5 = 0x00000100;
}

static void stm32g4_pwr_unrealize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4PWRState *s = STM32G4_PWR(dev);
}

static Property stm32g4_pwr_properties[] = {
    DEFINE_PROP_END_OF_LIST()
};

static const VMStateDescription vmstate_stm32g4_pwr = {
    .name = "stm32g4_pwr",
    .version_id = 1,
    .fields = (VMStateField[]) {
        VMSTATE_UINT32(cr1, STM32G4PWRState),
        VMSTATE_UINT32(cr2, STM32G4PWRState),
        VMSTATE_UINT32(cr3, STM32G4PWRState),
        VMSTATE_UINT32(cr4, STM32G4PWRState),
        VMSTATE_UINT32(sr1, STM32G4PWRState),
        VMSTATE_UINT32(sr2, STM32G4PWRState),
        VMSTATE_UINT32(scr, STM32G4PWRState),
        VMSTATE_UINT32(pucra, STM32G4PWRState),
        VMSTATE_UINT32(pdcra, STM32G4PWRState),
        VMSTATE_UINT32(pucrb, STM32G4PWRState),
        VMSTATE_UINT32(pdcrb, STM32G4PWRState),
        VMSTATE_UINT32(pucrc, STM32G4PWRState),
        VMSTATE_UINT32(pdcrc, STM32G4PWRState),
        VMSTATE_UINT32(pucrd, STM32G4PWRState),
        VMSTATE_UINT32(pdcrd, STM32G4PWRState),
        VMSTATE_UINT32(pucre, STM32G4PWRState),
        VMSTATE_UINT32(pdcre, STM32G4PWRState),
        VMSTATE_UINT32(pucrf, STM32G4PWRState),
        VMSTATE_UINT32(pdcrf, STM32G4PWRState),
        VMSTATE_UINT32(pucrg, STM32G4PWRState),
        VMSTATE_UINT32(pdcrg, STM32G4PWRState),
        VMSTATE_UINT32(cr5, STM32G4PWRState),
        VMSTATE_END_OF_LIST()
    }
};

static void stm32g4_pwr_class_init(ObjectClass *oc, void *opaque)
{
    DeviceClass *dc = DEVICE_CLASS(oc);

    dc->realize   = stm32g4_pwr_realize;
    dc->reset     = stm32g4_pwr_reset;
    dc->unrealize = stm32g4_pwr_unrealize;
    dc->vmsd      = &vmstate_stm32g4_pwr;
    device_class_set_props(dc, stm32g4_pwr_properties);
}

static TypeInfo stm32g4_pwr_info = {
    .name          = TYPE_STM32G4_PWR,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(STM32G4PWRState),
    .instance_init = stm32g4_pwr_instance_init,
    .class_init    = stm32g4_pwr_class_init
};

static void stm32g4_pwr_register_types(void)
{
    type_register_static(&stm32g4_pwr_info);
}

type_init(stm32g4_pwr_register_types)
