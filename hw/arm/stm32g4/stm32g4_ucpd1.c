/* stm32g4_ucpd1.c */

#include "qemu/osdep.h"
#include "hw/irq.h"
#include "hw/qdev-properties.h"
#include "include/hw/arm/stm32g4/stm32g4_ucpd1.h"
#include "migration/vmstate.h"

#define STM32G4_UCPD1_MMIO TYPE_STM32G4_UCPD1 "_mmio"
#define STM32G4_UCPD1_MMIO_SIZE 0x3C

static uint64_t stm32g4_ucpd1_mmio_read(void *opaque, hwaddr offset,
                                        unsigned size)
{
    STM32G4UCPD1State *s = STM32G4_UCPD1(opaque);
    uint64_t ret = 0;

    switch (offset) {
    case 0x00 ... 0x03:
        /* CFG1, UCPD configuration register 1 */
        ret = s->cfg1;
        break;

    case 0x04 ... 0x07:
        /* CFG2, UCPD configuration register 2 */
        ret = s->cfg2;
        break;

    case 0x0C ... 0x0F:
        /* CR, UCPD configuration register 2 */
        ret = s->cr;
        break;

    case 0x10 ... 0x13:
        /* IMR, UCPD Interrupt Mask Register */
        ret = s->imr;
        break;

    case 0x14 ... 0x17:
        /* SR, UCPD Status Register */
        ret = s->sr;
        break;

    case 0x18 ... 0x1B:
        /* ICR, UCPD Interrupt Clear Register */
        ret = s->icr;
        break;

    case 0x1C ... 0x1F:
        /* TX_ORDSET, UCPD Tx Ordered Set Type Register */
        ret = s->tx_ordset;
        break;

    case 0x20 ... 0x23:
        /* TX_PAYSZ, UCPD Tx Paysize Register */
        ret = s->tx_paysz;
        break;

    case 0x24 ... 0x27:
        /* TXDR, UCPD Tx Data Register */
        ret = s->txdr;
        break;

    case 0x28 ... 0x2B:
        /* RX_ORDSET, UCPD Rx Ordered Set Register */
        ret = s->rx_ordset;
        break;

    case 0x2C ... 0x2F:
        /* RX_PAYSZ, UCPD Rx Paysize Register */
        ret = s->rx_paysz;
        break;

    case 0x30 ... 0x33:
        /* RXDR, UCPD Rx Data Register */
        ret = s->rxdr;
        break;

    case 0x34 ... 0x37:
        /* RX_ORDEXT1, UCPD Rx Ordered Set Extension Register 1 */
        ret = s->rx_ordext1;
        break;

    case 0x38 ... 0x3B:
        /* RX_ORDEXT2, UCPD Rx Ordered Set Extension Register 2 */
        ret = s->rx_ordext2;
        break;

    default:
        printf("%s: unimplemented read from 0x%" HWADDR_PRIx ", size %d\n",
               __func__, offset, size);
        break;
    }

    return ret;
}

static void stm32g4_ucpd1_mmio_write(void *opaque, hwaddr offset,
                                     uint64_t value, unsigned size)
{
    STM32G4UCPD1State *s = STM32G4_UCPD1(opaque);

    switch (offset) {
    case 0x00 ... 0x03:
        /* CFG1, UCPD configuration register 1 */
        s->cfg1 = value;
        break;

    case 0x04 ... 0x07:
        /* CFG2, UCPD configuration register 2 */
        s->cfg2 = value;
        break;

    case 0x0C ... 0x0F:
        /* CR, UCPD configuration register 2 */
        s->cr = value;
        break;

    case 0x10 ... 0x13:
        /* IMR, UCPD Interrupt Mask Register */
        s->imr = value;
        break;

    case 0x14 ... 0x17:
        /* SR, UCPD Status Register */
        s->sr = value;
        break;

    case 0x18 ... 0x1B:
        /* ICR, UCPD Interrupt Clear Register */
        s->icr = value;
        break;

    case 0x1C ... 0x1F:
        /* TX_ORDSET, UCPD Tx Ordered Set Type Register */
        s->tx_ordset = value;
        break;

    case 0x20 ... 0x23:
        /* TX_PAYSZ, UCPD Tx Paysize Register */
        s->tx_paysz = value;
        break;

    case 0x24 ... 0x27:
        /* TXDR, UCPD Tx Data Register */
        s->txdr = value;
        break;

    case 0x28 ... 0x2B:
        /* RX_ORDSET, UCPD Rx Ordered Set Register */
        s->rx_ordset = value;
        break;

    case 0x2C ... 0x2F:
        /* RX_PAYSZ, UCPD Rx Paysize Register */
        s->rx_paysz = value;
        break;

    case 0x30 ... 0x33:
        /* RXDR, UCPD Rx Data Register */
        s->rxdr = value;
        break;

    case 0x34 ... 0x37:
        /* RX_ORDEXT1, UCPD Rx Ordered Set Extension Register 1 */
        s->rx_ordext1 = value;
        break;

    case 0x38 ... 0x3B:
        /* RX_ORDEXT2, UCPD Rx Ordered Set Extension Register 2 */
        s->rx_ordext2 = value;
        break;

    default:
        printf("%s: unimplemented write to 0x%" HWADDR_PRIx ", size %d, "
               "value 0x%" PRIx64 "\n", __func__, offset, size, value);
        break;
    }
}

static const MemoryRegionOps stm32g4_ucpd1_mmio_ops = {
    .read = stm32g4_ucpd1_mmio_read,
    .write = stm32g4_ucpd1_mmio_write,
    .impl = {
        .max_access_size = 4
    }
};

static void stm32g4_ucpd1_instance_init(Object *obj)
{
    STM32G4UCPD1State *s = STM32G4_UCPD1(obj);

    memory_region_init_io(&s->mmio, obj, &stm32g4_ucpd1_mmio_ops, s,
                          STM32G4_UCPD1_MMIO, STM32G4_UCPD1_MMIO_SIZE);
    sysbus_init_mmio(SYS_BUS_DEVICE(obj), &s->mmio);
}

static void stm32g4_ucpd1_realize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4UCPD1State *s = STM32G4_UCPD1(dev);
}

static void stm32g4_ucpd1_reset(DeviceState *dev)
{
    STM32G4UCPD1State *s = STM32G4_UCPD1(dev);

    s->cfg1 = 0x00000000;
    s->cfg2 = 0x00000000;
    s->cr = 0x00000000;
    s->imr = 0x00000000;
    s->sr = 0x00000000;
    s->icr = 0x00000000;
    s->tx_ordset = 0x00000000;
    s->tx_paysz = 0x00000000;
    s->txdr = 0x00000000;
    s->rx_ordset = 0x00000000;
    s->rx_paysz = 0x00000000;
    s->rxdr = 0x00000000;
    s->rx_ordext1 = 0x00000000;
    s->rx_ordext2 = 0x00000000;
}

static void stm32g4_ucpd1_unrealize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4UCPD1State *s = STM32G4_UCPD1(dev);
}

static Property stm32g4_ucpd1_properties[] = {
    DEFINE_PROP_END_OF_LIST()
};

static const VMStateDescription vmstate_stm32g4_ucpd1 = {
    .name = "stm32g4_ucpd1",
    .version_id = 1,
    .fields = (VMStateField[]) {
        VMSTATE_UINT32(cfg1, STM32G4UCPD1State),
        VMSTATE_UINT32(cfg2, STM32G4UCPD1State),
        VMSTATE_UINT32(cr, STM32G4UCPD1State),
        VMSTATE_UINT32(imr, STM32G4UCPD1State),
        VMSTATE_UINT32(sr, STM32G4UCPD1State),
        VMSTATE_UINT32(icr, STM32G4UCPD1State),
        VMSTATE_UINT32(tx_ordset, STM32G4UCPD1State),
        VMSTATE_UINT32(tx_paysz, STM32G4UCPD1State),
        VMSTATE_UINT32(txdr, STM32G4UCPD1State),
        VMSTATE_UINT32(rx_ordset, STM32G4UCPD1State),
        VMSTATE_UINT32(rx_paysz, STM32G4UCPD1State),
        VMSTATE_UINT32(rxdr, STM32G4UCPD1State),
        VMSTATE_UINT32(rx_ordext1, STM32G4UCPD1State),
        VMSTATE_UINT32(rx_ordext2, STM32G4UCPD1State),
        VMSTATE_END_OF_LIST()
    }
};

static void stm32g4_ucpd1_class_init(ObjectClass *oc, void *opaque)
{
    DeviceClass *dc = DEVICE_CLASS(oc);

    dc->realize   = stm32g4_ucpd1_realize;
    dc->reset     = stm32g4_ucpd1_reset;
    dc->unrealize = stm32g4_ucpd1_unrealize;
    dc->vmsd      = &vmstate_stm32g4_ucpd1;
    device_class_set_props(dc, stm32g4_ucpd1_properties);
}

static TypeInfo stm32g4_ucpd1_info = {
    .name          = TYPE_STM32G4_UCPD1,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(STM32G4UCPD1State),
    .instance_init = stm32g4_ucpd1_instance_init,
    .class_init    = stm32g4_ucpd1_class_init
};

static void stm32g4_ucpd1_register_types(void)
{
    type_register_static(&stm32g4_ucpd1_info);
}

type_init(stm32g4_ucpd1_register_types)
