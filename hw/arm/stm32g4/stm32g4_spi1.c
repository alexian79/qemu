/* stm32g4_spi1.c */

#include "qemu/osdep.h"
#include "hw/irq.h"
#include "hw/qdev-properties.h"
#include "include/hw/arm/stm32g4/stm32g4_spi1.h"
#include "migration/vmstate.h"

#define STM32G4_SPI1_MMIO TYPE_STM32G4_SPI1 "_mmio"
#define STM32G4_SPI1_MMIO_SIZE 0x24

static uint64_t stm32g4_spi1_mmio_read(void *opaque, hwaddr offset,
                                       unsigned size)
{
    STM32G4SPI1State *s = STM32G4_SPI1(opaque);
    uint64_t ret = 0;

    switch (offset) {
    case 0x00 ... 0x03:
        /* CR1, control register 1 */
        ret = s->cr1;
        break;

    case 0x04 ... 0x07:
        /* CR2, control register 2 */
        ret = s->cr2;
        break;

    case 0x08 ... 0x0B:
        /* SR, status register */
        ret = s->sr;
        break;

    case 0x0C ... 0x0F:
        /* DR, data register */
        ret = s->dr;
        break;

    case 0x10 ... 0x13:
        /* CRCPR, CRC polynomial register */
        ret = s->crcpr;
        break;

    case 0x14 ... 0x17:
        /* RXCRCR, RX CRC register */
        ret = s->rxcrcr;
        break;

    case 0x18 ... 0x1B:
        /* TXCRCR, TX CRC register */
        ret = s->txcrcr;
        break;

    case 0x1C ... 0x1F:
        /* I2SCFGR, configuration register */
        ret = s->i2scfgr;
        break;

    case 0x20 ... 0x23:
        /* I2SPR, prescaler register */
        ret = s->i2spr;
        break;

    default:
        printf("%s: unimplemented read from 0x%" HWADDR_PRIx ", size %d\n",
               __func__, offset, size);
        break;
    }

    return ret;
}

static void stm32g4_spi1_mmio_write(void *opaque, hwaddr offset, uint64_t value,
                                    unsigned size)
{
    STM32G4SPI1State *s = STM32G4_SPI1(opaque);

    switch (offset) {
    case 0x00 ... 0x03:
        /* CR1, control register 1 */
        s->cr1 = value;
        break;

    case 0x04 ... 0x07:
        /* CR2, control register 2 */
        s->cr2 = value;
        break;

    case 0x08 ... 0x0B:
        /* SR, status register */
        s->sr = value;
        break;

    case 0x0C ... 0x0F:
        /* DR, data register */
        s->dr = value;
        break;

    case 0x10 ... 0x13:
        /* CRCPR, CRC polynomial register */
        s->crcpr = value;
        break;

    case 0x14 ... 0x17:
        /* RXCRCR, RX CRC register */
        s->rxcrcr = value;
        break;

    case 0x18 ... 0x1B:
        /* TXCRCR, TX CRC register */
        s->txcrcr = value;
        break;

    case 0x1C ... 0x1F:
        /* I2SCFGR, configuration register */
        s->i2scfgr = value;
        break;

    case 0x20 ... 0x23:
        /* I2SPR, prescaler register */
        s->i2spr = value;
        break;

    default:
        printf("%s: unimplemented write to 0x%" HWADDR_PRIx ", size %d, "
               "value 0x%" PRIx64 "\n", __func__, offset, size, value);
        break;
    }
}

static const MemoryRegionOps stm32g4_spi1_mmio_ops = {
    .read = stm32g4_spi1_mmio_read,
    .write = stm32g4_spi1_mmio_write,
    .impl = {
        .max_access_size = 4
    }
};

static void stm32g4_spi1_instance_init(Object *obj)
{
    STM32G4SPI1State *s = STM32G4_SPI1(obj);

    memory_region_init_io(&s->mmio, obj, &stm32g4_spi1_mmio_ops, s,
                          STM32G4_SPI1_MMIO, STM32G4_SPI1_MMIO_SIZE);
    sysbus_init_mmio(SYS_BUS_DEVICE(obj), &s->mmio);
}

static void stm32g4_spi1_realize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4SPI1State *s = STM32G4_SPI1(dev);
}

static void stm32g4_spi1_reset(DeviceState *dev)
{
    STM32G4SPI1State *s = STM32G4_SPI1(dev);

    s->cr1 = 0x00000000;
    s->cr2 = 0x00000700;
    s->sr = 0x00000002;
    s->dr = 0x00000000;
    s->crcpr = 0x00000007;
    s->rxcrcr = 0x00000000;
    s->txcrcr = 0x00000000;
    s->i2scfgr = 0x00000000;
    s->i2spr = 0x00000002;
}

static void stm32g4_spi1_unrealize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4SPI1State *s = STM32G4_SPI1(dev);
}

static Property stm32g4_spi1_properties[] = {
    DEFINE_PROP_END_OF_LIST()
};

static const VMStateDescription vmstate_stm32g4_spi1 = {
    .name = "stm32g4_spi1",
    .version_id = 1,
    .fields = (VMStateField[]) {
        VMSTATE_UINT32(cr1, STM32G4SPI1State),
        VMSTATE_UINT32(cr2, STM32G4SPI1State),
        VMSTATE_UINT32(sr, STM32G4SPI1State),
        VMSTATE_UINT32(dr, STM32G4SPI1State),
        VMSTATE_UINT32(crcpr, STM32G4SPI1State),
        VMSTATE_UINT32(rxcrcr, STM32G4SPI1State),
        VMSTATE_UINT32(txcrcr, STM32G4SPI1State),
        VMSTATE_UINT32(i2scfgr, STM32G4SPI1State),
        VMSTATE_UINT32(i2spr, STM32G4SPI1State),
        VMSTATE_END_OF_LIST()
    }
};

static void stm32g4_spi1_class_init(ObjectClass *oc, void *opaque)
{
    DeviceClass *dc = DEVICE_CLASS(oc);

    dc->realize   = stm32g4_spi1_realize;
    dc->reset     = stm32g4_spi1_reset;
    dc->unrealize = stm32g4_spi1_unrealize;
    dc->vmsd      = &vmstate_stm32g4_spi1;
    device_class_set_props(dc, stm32g4_spi1_properties);
}

static TypeInfo stm32g4_spi1_info = {
    .name          = TYPE_STM32G4_SPI1,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(STM32G4SPI1State),
    .instance_init = stm32g4_spi1_instance_init,
    .class_init    = stm32g4_spi1_class_init
};

static void stm32g4_spi1_register_types(void)
{
    type_register_static(&stm32g4_spi1_info);
}

type_init(stm32g4_spi1_register_types)
