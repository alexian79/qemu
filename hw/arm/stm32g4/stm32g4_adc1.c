/* stm32g4_adc1.c */

#include "qemu/osdep.h"
#include "hw/irq.h"
#include "hw/qdev-properties.h"
#include "include/hw/arm/stm32g4/stm32g4_adc1.h"
#include "migration/vmstate.h"

#define STM32G4_ADC1_MMIO TYPE_STM32G4_ADC1 "_mmio"
#define STM32G4_ADC1_MMIO_SIZE 0xC4

static uint64_t stm32g4_adc1_mmio_read(void *opaque, hwaddr offset,
                                       unsigned size)
{
    STM32G4ADC1State *s = STM32G4_ADC1(opaque);
    uint64_t ret = 0;

    switch (offset) {
    case 0x00 ... 0x03:
        /* ISR, interrupt and status register */
        ret = s->isr;
        break;

    case 0x04 ... 0x07:
        /* IER, interrupt enable register */
        ret = s->ier;
        break;

    case 0x08 ... 0x0B:
        /* CR, control register */
        ret = s->cr;
        break;

    case 0x0C ... 0x0F:
        /* CFGR, configuration register */
        ret = s->cfgr;
        break;

    case 0x10 ... 0x13:
        /* CFGR2, configuration register */
        ret = s->cfgr2;
        break;

    case 0x14 ... 0x17:
        /* SMPR1, sample time register 1 */
        ret = s->smpr1;
        break;

    case 0x18 ... 0x1B:
        /* SMPR2, sample time register 2 */
        ret = s->smpr2;
        break;

    case 0x20 ... 0x23:
        /* TR1, watchdog threshold register 1 */
        ret = s->tr1;
        break;

    case 0x24 ... 0x27:
        /* TR2, watchdog threshold register */
        ret = s->tr2;
        break;

    case 0x28 ... 0x2B:
        /* TR3, watchdog threshold register 3 */
        ret = s->tr3;
        break;

    case 0x30 ... 0x33:
        /* SQR1, regular sequence register 1 */
        ret = s->sqr1;
        break;

    case 0x34 ... 0x37:
        /* SQR2, regular sequence register 2 */
        ret = s->sqr2;
        break;

    case 0x38 ... 0x3B:
        /* SQR3, regular sequence register 3 */
        ret = s->sqr3;
        break;

    case 0x3C ... 0x3F:
        /* SQR4, regular sequence register 4 */
        ret = s->sqr4;
        break;

    case 0x40 ... 0x43:
        /* DR, regular Data Register */
        ret = s->dr;
        break;

    case 0x4C ... 0x4F:
        /* JSQR, injected sequence register */
        ret = s->jsqr;
        break;

    case 0x60 ... 0x63:
        /* OFR1, offset register 1 */
        ret = s->ofr1;
        break;

    case 0x64 ... 0x67:
        /* OFR2, offset register 2 */
        ret = s->ofr2;
        break;

    case 0x68 ... 0x6B:
        /* OFR3, offset register 3 */
        ret = s->ofr3;
        break;

    case 0x6C ... 0x6F:
        /* OFR4, offset register 4 */
        ret = s->ofr4;
        break;

    case 0x80 ... 0x83:
        /* JDR1, injected data register 1 */
        ret = s->jdr1;
        break;

    case 0x84 ... 0x87:
        /* JDR2, injected data register 2 */
        ret = s->jdr2;
        break;

    case 0x88 ... 0x8B:
        /* JDR3, injected data register 3 */
        ret = s->jdr3;
        break;

    case 0x8C ... 0x8F:
        /* JDR4, injected data register 4 */
        ret = s->jdr4;
        break;

    case 0xA0 ... 0xA3:
        /* AWD2CR, Analog Watchdog 2 Configuration Register */
        ret = s->awd2cr;
        break;

    case 0xA4 ... 0xA7:
        /* AWD3CR, Analog Watchdog 3 Configuration Register */
        ret = s->awd3cr;
        break;

    case 0xB0 ... 0xB3:
        /* DIFSEL, Differential Mode Selection Register 2 */
        ret = s->difsel;
        break;

    case 0xB4 ... 0xB7:
        /* CALFACT, Calibration Factors */
        ret = s->calfact;
        break;

    case 0xC0 ... 0xC3:
        /* GCOMP, Gain compensation Register */
        ret = s->gcomp;
        break;

    default:
        printf("%s: unimplemented read from 0x%" HWADDR_PRIx ", size %d\n",
               __func__, offset, size);
        break;
    }

    return ret;
}

static void stm32g4_adc1_mmio_write(void *opaque, hwaddr offset, uint64_t value,
                                    unsigned size)
{
    STM32G4ADC1State *s = STM32G4_ADC1(opaque);

    switch (offset) {
    case 0x00 ... 0x03:
        /* ISR, interrupt and status register */
        s->isr = value;
        break;

    case 0x04 ... 0x07:
        /* IER, interrupt enable register */
        s->ier = value;
        break;

    case 0x08 ... 0x0B:
        /* CR, control register */
        s->cr = value;
        break;

    case 0x0C ... 0x0F:
        /* CFGR, configuration register */
        s->cfgr = value;
        break;

    case 0x10 ... 0x13:
        /* CFGR2, configuration register */
        s->cfgr2 = value;
        break;

    case 0x14 ... 0x17:
        /* SMPR1, sample time register 1 */
        s->smpr1 = value;
        break;

    case 0x18 ... 0x1B:
        /* SMPR2, sample time register 2 */
        s->smpr2 = value;
        break;

    case 0x20 ... 0x23:
        /* TR1, watchdog threshold register 1 */
        s->tr1 = value;
        break;

    case 0x24 ... 0x27:
        /* TR2, watchdog threshold register */
        s->tr2 = value;
        break;

    case 0x28 ... 0x2B:
        /* TR3, watchdog threshold register 3 */
        s->tr3 = value;
        break;

    case 0x30 ... 0x33:
        /* SQR1, regular sequence register 1 */
        s->sqr1 = value;
        break;

    case 0x34 ... 0x37:
        /* SQR2, regular sequence register 2 */
        s->sqr2 = value;
        break;

    case 0x38 ... 0x3B:
        /* SQR3, regular sequence register 3 */
        s->sqr3 = value;
        break;

    case 0x3C ... 0x3F:
        /* SQR4, regular sequence register 4 */
        s->sqr4 = value;
        break;

    case 0x40 ... 0x43:
        /* DR, regular Data Register */
        s->dr = value;
        break;

    case 0x4C ... 0x4F:
        /* JSQR, injected sequence register */
        s->jsqr = value;
        break;

    case 0x60 ... 0x63:
        /* OFR1, offset register 1 */
        s->ofr1 = value;
        break;

    case 0x64 ... 0x67:
        /* OFR2, offset register 2 */
        s->ofr2 = value;
        break;

    case 0x68 ... 0x6B:
        /* OFR3, offset register 3 */
        s->ofr3 = value;
        break;

    case 0x6C ... 0x6F:
        /* OFR4, offset register 4 */
        s->ofr4 = value;
        break;

    case 0x80 ... 0x83:
        /* JDR1, injected data register 1 */
        s->jdr1 = value;
        break;

    case 0x84 ... 0x87:
        /* JDR2, injected data register 2 */
        s->jdr2 = value;
        break;

    case 0x88 ... 0x8B:
        /* JDR3, injected data register 3 */
        s->jdr3 = value;
        break;

    case 0x8C ... 0x8F:
        /* JDR4, injected data register 4 */
        s->jdr4 = value;
        break;

    case 0xA0 ... 0xA3:
        /* AWD2CR, Analog Watchdog 2 Configuration Register */
        s->awd2cr = value;
        break;

    case 0xA4 ... 0xA7:
        /* AWD3CR, Analog Watchdog 3 Configuration Register */
        s->awd3cr = value;
        break;

    case 0xB0 ... 0xB3:
        /* DIFSEL, Differential Mode Selection Register 2 */
        s->difsel = value;
        break;

    case 0xB4 ... 0xB7:
        /* CALFACT, Calibration Factors */
        s->calfact = value;
        break;

    case 0xC0 ... 0xC3:
        /* GCOMP, Gain compensation Register */
        s->gcomp = value;
        break;

    default:
        printf("%s: unimplemented write to 0x%" HWADDR_PRIx ", size %d, "
               "value 0x%" PRIx64 "\n", __func__, offset, size, value);
        break;
    }
}

static const MemoryRegionOps stm32g4_adc1_mmio_ops = {
    .read = stm32g4_adc1_mmio_read,
    .write = stm32g4_adc1_mmio_write,
    .impl = {
        .max_access_size = 4
    }
};

static void stm32g4_adc1_instance_init(Object *obj)
{
    STM32G4ADC1State *s = STM32G4_ADC1(obj);

    memory_region_init_io(&s->mmio, obj, &stm32g4_adc1_mmio_ops, s,
                          STM32G4_ADC1_MMIO, STM32G4_ADC1_MMIO_SIZE);
    sysbus_init_mmio(SYS_BUS_DEVICE(obj), &s->mmio);
}

static void stm32g4_adc1_realize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4ADC1State *s = STM32G4_ADC1(dev);
}

static void stm32g4_adc1_reset(DeviceState *dev)
{
    STM32G4ADC1State *s = STM32G4_ADC1(dev);

    s->isr = 0x00000000;
    s->ier = 0x00000000;
    s->cr = 0x20000000;
    s->cfgr = 0x80000000;
    s->cfgr2 = 0x00000000;
    s->smpr1 = 0x00000000;
    s->smpr2 = 0x00000000;
    s->tr1 = 0x0FFF0000;
    s->tr2 = 0x00FF0000;
    s->tr3 = 0x00FF0000;
    s->sqr1 = 0x00000000;
    s->sqr2 = 0x00000000;
    s->sqr3 = 0x00000000;
    s->sqr4 = 0x00000000;
    s->dr = 0x00000000;
    s->jsqr = 0x00000000;
    s->ofr1 = 0x00000000;
    s->ofr2 = 0x00000000;
    s->ofr3 = 0x00000000;
    s->ofr4 = 0x00000000;
    s->jdr1 = 0x00000000;
    s->jdr2 = 0x00000000;
    s->jdr3 = 0x00000000;
    s->jdr4 = 0x00000000;
    s->awd2cr = 0x00000000;
    s->awd3cr = 0x00000000;
    s->difsel = 0x00000000;
    s->calfact = 0x00000000;
    s->gcomp = 0x00000000;
}

static void stm32g4_adc1_unrealize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4ADC1State *s = STM32G4_ADC1(dev);
}

static Property stm32g4_adc1_properties[] = {
    DEFINE_PROP_END_OF_LIST()
};

static const VMStateDescription vmstate_stm32g4_adc1 = {
    .name = "stm32g4_adc1",
    .version_id = 1,
    .fields = (VMStateField[]) {
        VMSTATE_UINT32(isr, STM32G4ADC1State),
        VMSTATE_UINT32(ier, STM32G4ADC1State),
        VMSTATE_UINT32(cr, STM32G4ADC1State),
        VMSTATE_UINT32(cfgr, STM32G4ADC1State),
        VMSTATE_UINT32(cfgr2, STM32G4ADC1State),
        VMSTATE_UINT32(smpr1, STM32G4ADC1State),
        VMSTATE_UINT32(smpr2, STM32G4ADC1State),
        VMSTATE_UINT32(tr1, STM32G4ADC1State),
        VMSTATE_UINT32(tr2, STM32G4ADC1State),
        VMSTATE_UINT32(tr3, STM32G4ADC1State),
        VMSTATE_UINT32(sqr1, STM32G4ADC1State),
        VMSTATE_UINT32(sqr2, STM32G4ADC1State),
        VMSTATE_UINT32(sqr3, STM32G4ADC1State),
        VMSTATE_UINT32(sqr4, STM32G4ADC1State),
        VMSTATE_UINT32(dr, STM32G4ADC1State),
        VMSTATE_UINT32(jsqr, STM32G4ADC1State),
        VMSTATE_UINT32(ofr1, STM32G4ADC1State),
        VMSTATE_UINT32(ofr2, STM32G4ADC1State),
        VMSTATE_UINT32(ofr3, STM32G4ADC1State),
        VMSTATE_UINT32(ofr4, STM32G4ADC1State),
        VMSTATE_UINT32(jdr1, STM32G4ADC1State),
        VMSTATE_UINT32(jdr2, STM32G4ADC1State),
        VMSTATE_UINT32(jdr3, STM32G4ADC1State),
        VMSTATE_UINT32(jdr4, STM32G4ADC1State),
        VMSTATE_UINT32(awd2cr, STM32G4ADC1State),
        VMSTATE_UINT32(awd3cr, STM32G4ADC1State),
        VMSTATE_UINT32(difsel, STM32G4ADC1State),
        VMSTATE_UINT32(calfact, STM32G4ADC1State),
        VMSTATE_UINT32(gcomp, STM32G4ADC1State),
        VMSTATE_END_OF_LIST()
    }
};

static void stm32g4_adc1_class_init(ObjectClass *oc, void *opaque)
{
    DeviceClass *dc = DEVICE_CLASS(oc);

    dc->realize   = stm32g4_adc1_realize;
    dc->reset     = stm32g4_adc1_reset;
    dc->unrealize = stm32g4_adc1_unrealize;
    dc->vmsd      = &vmstate_stm32g4_adc1;
    device_class_set_props(dc, stm32g4_adc1_properties);
}

static TypeInfo stm32g4_adc1_info = {
    .name          = TYPE_STM32G4_ADC1,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(STM32G4ADC1State),
    .instance_init = stm32g4_adc1_instance_init,
    .class_init    = stm32g4_adc1_class_init
};

static void stm32g4_adc1_register_types(void)
{
    type_register_static(&stm32g4_adc1_info);
}

type_init(stm32g4_adc1_register_types)
