/* stm32g4_rcc.c */

#include "qemu/osdep.h"
#include "hw/irq.h"
#include "hw/qdev-properties.h"
#include "include/hw/arm/stm32g4/stm32g4_rcc.h"
#include "migration/vmstate.h"

#define STM32G4_RCC_MMIO TYPE_STM32G4_RCC "_mmio"
#define STM32G4_RCC_MMIO_SIZE 0xA0

static uint64_t stm32g4_rcc_mmio_read(void *opaque, hwaddr offset,
                                      unsigned size)
{
    STM32G4RCCState *s = STM32G4_RCC(opaque);
    uint64_t ret = 0;

    switch (offset) {
    case 0x00 ... 0x03:
        /* CR, Clock control register */
        ret = s->cr;
        break;

    case 0x04 ... 0x07:
        /* ICSCR, Internal clock sources calibration register */
        ret = s->icscr;
        break;

    case 0x08 ... 0x0B:
        /* CFGR, Clock configuration register */
        ret = s->cfgr;
        break;

    case 0x0C ... 0x0F:
        /* PLLSYSCFGR, PLL configuration register */
        ret = s->pllsyscfgr;
        break;

    case 0x18 ... 0x1B:
        /* CIER, Clock interrupt enable register */
        ret = s->cier;
        break;

    case 0x1C ... 0x1F:
        /* CIFR, Clock interrupt flag register */
        ret = s->cifr;
        break;

    case 0x20 ... 0x23:
        /* CICR, Clock interrupt clear register */
        ret = s->cicr;
        break;

    case 0x28 ... 0x2B:
        /* AHB1RSTR, AHB1 peripheral reset register */
        ret = s->ahb1rstr;
        break;

    case 0x2C ... 0x2F:
        /* AHB2RSTR, AHB2 peripheral reset register */
        ret = s->ahb2rstr;
        break;

    case 0x30 ... 0x33:
        /* AHB3RSTR, AHB3 peripheral reset register */
        ret = s->ahb3rstr;
        break;

    case 0x38 ... 0x3B:
        /* APB1RSTR1, APB1 peripheral reset register 1 */
        ret = s->apb1rstr1;
        break;

    case 0x3C ... 0x3F:
        /* APB1RSTR2, APB1 peripheral reset register 2 */
        ret = s->apb1rstr2;
        break;

    case 0x40 ... 0x43:
        /* APB2RSTR, APB2 peripheral reset register */
        ret = s->apb2rstr;
        break;

    case 0x48 ... 0x4B:
        /* AHB1ENR, AHB1 peripheral clock enable register */
        ret = s->ahb1enr;
        break;

    case 0x4C ... 0x4F:
        /* AHB2ENR, AHB2 peripheral clock enable register */
        ret = s->ahb2enr;
        break;

    case 0x50 ... 0x53:
        /* AHB3ENR, AHB3 peripheral clock enable register */
        ret = s->ahb3enr;
        break;

    case 0x58 ... 0x5B:
        /* APB1ENR1, APB1ENR1 */
        ret = s->apb1enr1;
        break;

    case 0x5C ... 0x5F:
        /* APB1ENR2, APB1 peripheral clock enable register 2 */
        ret = s->apb1enr2;
        break;

    case 0x60 ... 0x63:
        /* APB2ENR, APB2ENR */
        ret = s->apb2enr;
        break;

    case 0x68 ... 0x6B:
        /* AHB1SMENR, AHB1 peripheral clocks enable in Sleep and Stop modes
            register */
        ret = s->ahb1smenr;
        break;

    case 0x6C ... 0x6F:
        /* AHB2SMENR, AHB2 peripheral clocks enable in Sleep and Stop modes
            register */
        ret = s->ahb2smenr;
        break;

    case 0x70 ... 0x73:
        /* AHB3SMENR, AHB3 peripheral clocks enable in Sleep and Stop modes
            register */
        ret = s->ahb3smenr;
        break;

    case 0x78 ... 0x7B:
        /* APB1SMENR1, APB1SMENR1 */
        ret = s->apb1smenr1;
        break;

    case 0x7C ... 0x7F:
        /* APB1SMENR2, APB1 peripheral clocks enable in Sleep and Stop modes
            register 2 */
        ret = s->apb1smenr2;
        break;

    case 0x80 ... 0x83:
        /* APB2SMENR, APB2SMENR */
        ret = s->apb2smenr;
        break;

    case 0x88 ... 0x8B:
        /* CCIPR1, CCIPR */
        ret = s->ccipr1;
        break;

    case 0x90 ... 0x93:
        /* BDCR, BDCR */
        ret = s->bdcr;
        break;

    case 0x94 ... 0x97:
        /* CSR, CSR */
        ret = s->csr;
        break;

    case 0x98 ... 0x9B:
        /* CRRCR, Clock recovery RC register */
        ret = s->crrcr;
        break;

    case 0x9C ... 0x9F:
        /* CCIPR2, Peripherals independent clock configuration register */
        ret = s->ccipr2;
        break;

    default:
        printf("%s: unimplemented read from 0x%" HWADDR_PRIx ", size %d\n",
               __func__, offset, size);
        break;
    }

    return ret;
}

static void stm32g4_rcc_mmio_write(void *opaque, hwaddr offset, uint64_t value,
                                   unsigned size)
{
    STM32G4RCCState *s = STM32G4_RCC(opaque);

    switch (offset) {
    case 0x00 ... 0x03:
        /* CR, Clock control register */
        s->cr = value;
        break;

    case 0x04 ... 0x07:
        /* ICSCR, Internal clock sources calibration register */
        s->icscr = value;
        break;

    case 0x08 ... 0x0B:
        /* CFGR, Clock configuration register */
        s->cfgr = value;
        break;

    case 0x0C ... 0x0F:
        /* PLLSYSCFGR, PLL configuration register */
        s->pllsyscfgr = value;
        break;

    case 0x18 ... 0x1B:
        /* CIER, Clock interrupt enable register */
        s->cier = value;
        break;

    case 0x1C ... 0x1F:
        /* CIFR, Clock interrupt flag register */
        s->cifr = value;
        break;

    case 0x20 ... 0x23:
        /* CICR, Clock interrupt clear register */
        s->cicr = value;
        break;

    case 0x28 ... 0x2B:
        /* AHB1RSTR, AHB1 peripheral reset register */
        s->ahb1rstr = value;
        break;

    case 0x2C ... 0x2F:
        /* AHB2RSTR, AHB2 peripheral reset register */
        s->ahb2rstr = value;
        break;

    case 0x30 ... 0x33:
        /* AHB3RSTR, AHB3 peripheral reset register */
        s->ahb3rstr = value;
        break;

    case 0x38 ... 0x3B:
        /* APB1RSTR1, APB1 peripheral reset register 1 */
        s->apb1rstr1 = value;
        break;

    case 0x3C ... 0x3F:
        /* APB1RSTR2, APB1 peripheral reset register 2 */
        s->apb1rstr2 = value;
        break;

    case 0x40 ... 0x43:
        /* APB2RSTR, APB2 peripheral reset register */
        s->apb2rstr = value;
        break;

    case 0x48 ... 0x4B:
        /* AHB1ENR, AHB1 peripheral clock enable register */
        s->ahb1enr = value;
        break;

    case 0x4C ... 0x4F:
        /* AHB2ENR, AHB2 peripheral clock enable register */
        s->ahb2enr = value;
        break;

    case 0x50 ... 0x53:
        /* AHB3ENR, AHB3 peripheral clock enable register */
        s->ahb3enr = value;
        break;

    case 0x58 ... 0x5B:
        /* APB1ENR1, APB1ENR1 */
        s->apb1enr1 = value;
        break;

    case 0x5C ... 0x5F:
        /* APB1ENR2, APB1 peripheral clock enable register 2 */
        s->apb1enr2 = value;
        break;

    case 0x60 ... 0x63:
        /* APB2ENR, APB2ENR */
        s->apb2enr = value;
        break;

    case 0x68 ... 0x6B:
        /* AHB1SMENR, AHB1 peripheral clocks enable in Sleep and Stop modes
            register */
        s->ahb1smenr = value;
        break;

    case 0x6C ... 0x6F:
        /* AHB2SMENR, AHB2 peripheral clocks enable in Sleep and Stop modes
            register */
        s->ahb2smenr = value;
        break;

    case 0x70 ... 0x73:
        /* AHB3SMENR, AHB3 peripheral clocks enable in Sleep and Stop modes
            register */
        s->ahb3smenr = value;
        break;

    case 0x78 ... 0x7B:
        /* APB1SMENR1, APB1SMENR1 */
        s->apb1smenr1 = value;
        break;

    case 0x7C ... 0x7F:
        /* APB1SMENR2, APB1 peripheral clocks enable in Sleep and Stop modes
            register 2 */
        s->apb1smenr2 = value;
        break;

    case 0x80 ... 0x83:
        /* APB2SMENR, APB2SMENR */
        s->apb2smenr = value;
        break;

    case 0x88 ... 0x8B:
        /* CCIPR1, CCIPR */
        s->ccipr1 = value;
        break;

    case 0x90 ... 0x93:
        /* BDCR, BDCR */
        s->bdcr = value;
        break;

    case 0x94 ... 0x97:
        /* CSR, CSR */
        s->csr = value;
        break;

    case 0x98 ... 0x9B:
        /* CRRCR, Clock recovery RC register */
        s->crrcr = value;
        break;

    case 0x9C ... 0x9F:
        /* CCIPR2, Peripherals independent clock configuration register */
        s->ccipr2 = value;
        break;

    default:
        printf("%s: unimplemented write to 0x%" HWADDR_PRIx ", size %d, "
               "value 0x%" PRIx64 "\n", __func__, offset, size, value);
        break;
    }
}

static const MemoryRegionOps stm32g4_rcc_mmio_ops = {
    .read = stm32g4_rcc_mmio_read,
    .write = stm32g4_rcc_mmio_write,
    .impl = {
        .max_access_size = 4
    }
};

static void stm32g4_rcc_instance_init(Object *obj)
{
    STM32G4RCCState *s = STM32G4_RCC(obj);

    memory_region_init_io(&s->mmio, obj, &stm32g4_rcc_mmio_ops, s,
                          STM32G4_RCC_MMIO, STM32G4_RCC_MMIO_SIZE);
    sysbus_init_mmio(SYS_BUS_DEVICE(obj), &s->mmio);
}

static void stm32g4_rcc_realize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4RCCState *s = STM32G4_RCC(dev);
}

static void stm32g4_rcc_reset(DeviceState *dev)
{
    STM32G4RCCState *s = STM32G4_RCC(dev);

    s->cr = 0x00000063;
    s->icscr = 0x40000000;
    s->cfgr = 0x00000005;
    s->pllsyscfgr = 0x00001000;
    s->cier = 0x00000000;
    s->cifr = 0x00000000;
    s->cicr = 0x00000000;
    s->ahb1rstr = 0x00000000;
    s->ahb2rstr = 0x00000000;
    s->ahb3rstr = 0x00000000;
    s->apb1rstr1 = 0x00000000;
    s->apb1rstr2 = 0x00000000;
    s->apb2rstr = 0x00000000;
    s->ahb1enr = 0x00000100;
    s->ahb2enr = 0x00000000;
    s->ahb3enr = 0x00000000;
    s->apb1enr1 = 0x00000000;
    s->apb1enr2 = 0x00000000;
    s->apb2enr = 0x00000000;
    s->ahb1smenr = 0x0000130F;
    s->ahb2smenr = 0x050F667F;
    s->ahb3smenr = 0x000000101;
    s->apb1smenr1 = 0xD2FECD3F;
    s->apb1smenr2 = 0x00000103;
    s->apb2smenr = 0x0437F801;
    s->ccipr1 = 0x00000000;
    s->bdcr = 0x00000000;
    s->csr = 0x0C000000;
    s->crrcr = 0x00000000;
    s->ccipr2 = 0x00000000;
}

static void stm32g4_rcc_unrealize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4RCCState *s = STM32G4_RCC(dev);
}

static Property stm32g4_rcc_properties[] = {
    DEFINE_PROP_END_OF_LIST()
};

static const VMStateDescription vmstate_stm32g4_rcc = {
    .name = "stm32g4_rcc",
    .version_id = 1,
    .fields = (VMStateField[]) {
        VMSTATE_UINT32(cr, STM32G4RCCState),
        VMSTATE_UINT32(icscr, STM32G4RCCState),
        VMSTATE_UINT32(cfgr, STM32G4RCCState),
        VMSTATE_UINT32(pllsyscfgr, STM32G4RCCState),
        VMSTATE_UINT32(cier, STM32G4RCCState),
        VMSTATE_UINT32(cifr, STM32G4RCCState),
        VMSTATE_UINT32(cicr, STM32G4RCCState),
        VMSTATE_UINT32(ahb1rstr, STM32G4RCCState),
        VMSTATE_UINT32(ahb2rstr, STM32G4RCCState),
        VMSTATE_UINT32(ahb3rstr, STM32G4RCCState),
        VMSTATE_UINT32(apb1rstr1, STM32G4RCCState),
        VMSTATE_UINT32(apb1rstr2, STM32G4RCCState),
        VMSTATE_UINT32(apb2rstr, STM32G4RCCState),
        VMSTATE_UINT32(ahb1enr, STM32G4RCCState),
        VMSTATE_UINT32(ahb2enr, STM32G4RCCState),
        VMSTATE_UINT32(ahb3enr, STM32G4RCCState),
        VMSTATE_UINT32(apb1enr1, STM32G4RCCState),
        VMSTATE_UINT32(apb1enr2, STM32G4RCCState),
        VMSTATE_UINT32(apb2enr, STM32G4RCCState),
        VMSTATE_UINT32(ahb1smenr, STM32G4RCCState),
        VMSTATE_UINT32(ahb2smenr, STM32G4RCCState),
        VMSTATE_UINT32(ahb3smenr, STM32G4RCCState),
        VMSTATE_UINT32(apb1smenr1, STM32G4RCCState),
        VMSTATE_UINT32(apb1smenr2, STM32G4RCCState),
        VMSTATE_UINT32(apb2smenr, STM32G4RCCState),
        VMSTATE_UINT32(ccipr1, STM32G4RCCState),
        VMSTATE_UINT32(bdcr, STM32G4RCCState),
        VMSTATE_UINT32(csr, STM32G4RCCState),
        VMSTATE_UINT32(crrcr, STM32G4RCCState),
        VMSTATE_UINT32(ccipr2, STM32G4RCCState),
        VMSTATE_END_OF_LIST()
    }
};

static void stm32g4_rcc_class_init(ObjectClass *oc, void *opaque)
{
    DeviceClass *dc = DEVICE_CLASS(oc);

    dc->realize   = stm32g4_rcc_realize;
    dc->reset     = stm32g4_rcc_reset;
    dc->unrealize = stm32g4_rcc_unrealize;
    dc->vmsd      = &vmstate_stm32g4_rcc;
    device_class_set_props(dc, stm32g4_rcc_properties);
}

static TypeInfo stm32g4_rcc_info = {
    .name          = TYPE_STM32G4_RCC,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(STM32G4RCCState),
    .instance_init = stm32g4_rcc_instance_init,
    .class_init    = stm32g4_rcc_class_init
};

static void stm32g4_rcc_register_types(void)
{
    type_register_static(&stm32g4_rcc_info);
}

type_init(stm32g4_rcc_register_types)
