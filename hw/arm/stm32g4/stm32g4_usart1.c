/* stm32g4_usart1.c */

#include "qemu/osdep.h"
#include "hw/irq.h"
#include "hw/qdev-properties.h"
#include "include/hw/arm/stm32g4/stm32g4_usart1.h"
#include "migration/vmstate.h"

#define STM32G4_USART1_MMIO TYPE_STM32G4_USART1 "_mmio"
#define STM32G4_USART1_MMIO_SIZE 0x30

static uint64_t stm32g4_usart1_mmio_read(void *opaque, hwaddr offset,
                                         unsigned size)
{
    STM32G4USART1State *s = STM32G4_USART1(opaque);
    uint64_t ret = 0;

    switch (offset) {
    case 0x00 ... 0x03:
        /* CR1, Control register 1 */
        ret = s->cr1;
        break;

    case 0x04 ... 0x07:
        /* CR2, Control register 2 */
        ret = s->cr2;
        break;

    case 0x08 ... 0x0B:
        /* CR3, Control register 3 */
        ret = s->cr3;
        break;

    case 0x0C ... 0x0F:
        /* BRR, Baud rate register */
        ret = s->brr;
        break;

    case 0x10 ... 0x13:
        /* GTPR, Guard time and prescaler register */
        ret = s->gtpr;
        break;

    case 0x14 ... 0x17:
        /* RTOR, Receiver timeout register */
        ret = s->rtor;
        break;

    case 0x18 ... 0x1B:
        /* RQR, Request register */
        ret = s->rqr;
        break;

    case 0x1C ... 0x1F:
        /* ISR, Interrupt & status register */
        ret = s->isr;
        break;

    case 0x20 ... 0x23:
        /* ICR, Interrupt flag clear register */
        ret = s->icr;
        break;

    case 0x24 ... 0x27:
        /* RDR, Receive data register */
        ret = s->rdr;
        break;

    case 0x28 ... 0x2B:
        /* TDR, Transmit data register */
        ret = s->tdr;
        break;

    case 0x2C ... 0x2F:
        /* PRESC, USART prescaler register */
        ret = s->presc;
        break;

    default:
        printf("%s: unimplemented read from 0x%" HWADDR_PRIx ", size %d\n",
               __func__, offset, size);
        break;
    }

    return ret;
}

static void stm32g4_usart1_mmio_write(void *opaque, hwaddr offset,
                                      uint64_t value, unsigned size)
{
    STM32G4USART1State *s = STM32G4_USART1(opaque);

    switch (offset) {
    case 0x00 ... 0x03:
        /* CR1, Control register 1 */
        s->cr1 = value;
        break;

    case 0x04 ... 0x07:
        /* CR2, Control register 2 */
        s->cr2 = value;
        break;

    case 0x08 ... 0x0B:
        /* CR3, Control register 3 */
        s->cr3 = value;
        break;

    case 0x0C ... 0x0F:
        /* BRR, Baud rate register */
        s->brr = value;
        break;

    case 0x10 ... 0x13:
        /* GTPR, Guard time and prescaler register */
        s->gtpr = value;
        break;

    case 0x14 ... 0x17:
        /* RTOR, Receiver timeout register */
        s->rtor = value;
        break;

    case 0x18 ... 0x1B:
        /* RQR, Request register */
        s->rqr = value;
        break;

    case 0x1C ... 0x1F:
        /* ISR, Interrupt & status register */
        s->isr = value;
        break;

    case 0x20 ... 0x23:
        /* ICR, Interrupt flag clear register */
        s->icr = value;
        break;

    case 0x24 ... 0x27:
        /* RDR, Receive data register */
        s->rdr = value;
        break;

    case 0x28 ... 0x2B:
        /* TDR, Transmit data register */
        s->tdr = value;
        break;

    case 0x2C ... 0x2F:
        /* PRESC, USART prescaler register */
        s->presc = value;
        break;

    default:
        printf("%s: unimplemented write to 0x%" HWADDR_PRIx ", size %d, "
               "value 0x%" PRIx64 "\n", __func__, offset, size, value);
        break;
    }
}

static const MemoryRegionOps stm32g4_usart1_mmio_ops = {
    .read = stm32g4_usart1_mmio_read,
    .write = stm32g4_usart1_mmio_write,
    .impl = {
        .max_access_size = 4
    }
};

static void stm32g4_usart1_instance_init(Object *obj)
{
    STM32G4USART1State *s = STM32G4_USART1(obj);

    memory_region_init_io(&s->mmio, obj, &stm32g4_usart1_mmio_ops, s,
                          STM32G4_USART1_MMIO, STM32G4_USART1_MMIO_SIZE);
    sysbus_init_mmio(SYS_BUS_DEVICE(obj), &s->mmio);
}

static void stm32g4_usart1_realize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4USART1State *s = STM32G4_USART1(dev);
}

static void stm32g4_usart1_reset(DeviceState *dev)
{
    STM32G4USART1State *s = STM32G4_USART1(dev);

    s->cr1 = 0x00000000;
    s->cr2 = 0x00000000;
    s->cr3 = 0x00000000;
    s->brr = 0x00000000;
    s->gtpr = 0x00000000;
    s->rtor = 0x00000000;
    s->rqr = 0x00000000;
    s->isr = 0x00000000;
    s->icr = 0x00000000;
    s->rdr = 0x00000000;
    s->tdr = 0x00000000;
    s->presc = 0x00000000;
}

static void stm32g4_usart1_unrealize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4USART1State *s = STM32G4_USART1(dev);
}

static Property stm32g4_usart1_properties[] = {
    DEFINE_PROP_END_OF_LIST()
};

static const VMStateDescription vmstate_stm32g4_usart1 = {
    .name = "stm32g4_usart1",
    .version_id = 1,
    .fields = (VMStateField[]) {
        VMSTATE_UINT32(cr1, STM32G4USART1State),
        VMSTATE_UINT32(cr2, STM32G4USART1State),
        VMSTATE_UINT32(cr3, STM32G4USART1State),
        VMSTATE_UINT32(brr, STM32G4USART1State),
        VMSTATE_UINT32(gtpr, STM32G4USART1State),
        VMSTATE_UINT32(rtor, STM32G4USART1State),
        VMSTATE_UINT32(rqr, STM32G4USART1State),
        VMSTATE_UINT32(isr, STM32G4USART1State),
        VMSTATE_UINT32(icr, STM32G4USART1State),
        VMSTATE_UINT32(rdr, STM32G4USART1State),
        VMSTATE_UINT32(tdr, STM32G4USART1State),
        VMSTATE_UINT32(presc, STM32G4USART1State),
        VMSTATE_END_OF_LIST()
    }
};

static void stm32g4_usart1_class_init(ObjectClass *oc, void *opaque)
{
    DeviceClass *dc = DEVICE_CLASS(oc);

    dc->realize   = stm32g4_usart1_realize;
    dc->reset     = stm32g4_usart1_reset;
    dc->unrealize = stm32g4_usart1_unrealize;
    dc->vmsd      = &vmstate_stm32g4_usart1;
    device_class_set_props(dc, stm32g4_usart1_properties);
}

static TypeInfo stm32g4_usart1_info = {
    .name          = TYPE_STM32G4_USART1,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(STM32G4USART1State),
    .instance_init = stm32g4_usart1_instance_init,
    .class_init    = stm32g4_usart1_class_init
};

static void stm32g4_usart1_register_types(void)
{
    type_register_static(&stm32g4_usart1_info);
}

type_init(stm32g4_usart1_register_types)
