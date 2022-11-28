/* stm32g4_rtc.c */

#include "qemu/osdep.h"
#include "hw/irq.h"
#include "hw/qdev-properties.h"
#include "include/hw/arm/stm32g4/stm32g4_rtc.h"
#include "migration/vmstate.h"

#define STM32G4_RTC_MMIO TYPE_STM32G4_RTC "_mmio"
#define STM32G4_RTC_MMIO_SIZE 0x60

static uint64_t stm32g4_rtc_mmio_read(void *opaque, hwaddr offset,
                                      unsigned size)
{
    STM32G4RTCState *s = STM32G4_RTC(opaque);
    uint64_t ret = 0;

    switch (offset) {
    case 0x00 ... 0x03:
        /* TR, time register */
        ret = s->tr;
        break;

    case 0x04 ... 0x07:
        /* DR, date register */
        ret = s->dr;
        break;

    case 0x08 ... 0x0B:
        /* SSR, sub second register */
        ret = s->ssr;
        break;

    case 0x0C ... 0x0F:
        /* ICSR, initialization and status register */
        ret = s->icsr;
        break;

    case 0x10 ... 0x13:
        /* PRER, prescaler register */
        ret = s->prer;
        break;

    case 0x14 ... 0x17:
        /* WUTR, wakeup timer register */
        ret = s->wutr;
        break;

    case 0x18 ... 0x1B:
        /* CR, control register */
        ret = s->cr;
        break;

    case 0x24 ... 0x27:
        /* WPR, write protection register */
        ret = s->wpr;
        break;

    case 0x28 ... 0x2B:
        /* CALR, calibration register */
        ret = s->calr;
        break;

    case 0x2C ... 0x2F:
        /* SHIFTR, shift control register */
        ret = s->shiftr;
        break;

    case 0x30 ... 0x33:
        /* TSTR, time stamp time register */
        ret = s->tstr;
        break;

    case 0x34 ... 0x37:
        /* TSDR, time stamp date register */
        ret = s->tsdr;
        break;

    case 0x38 ... 0x3B:
        /* TSSSR, timestamp sub second register */
        ret = s->tsssr;
        break;

    case 0x40 ... 0x43:
        /* ALRMAR, alarm A register */
        ret = s->alrmar;
        break;

    case 0x44 ... 0x47:
        /* ALRMASSR, alarm A sub second register */
        ret = s->alrmassr;
        break;

    case 0x48 ... 0x4B:
        /* ALRMBR, alarm B register */
        ret = s->alrmbr;
        break;

    case 0x4C ... 0x4F:
        /* ALRMBSSR, alarm B sub second register */
        ret = s->alrmbssr;
        break;

    case 0x50 ... 0x53:
        /* SR, status register */
        ret = s->sr;
        break;

    case 0x54 ... 0x57:
        /* MISR, status register */
        ret = s->misr;
        break;

    case 0x5C ... 0x5F:
        /* SCR, status register */
        ret = s->scr;
        break;

    default:
        printf("%s: unimplemented read from 0x%" HWADDR_PRIx ", size %d\n",
               __func__, offset, size);
        break;
    }

    return ret;
}

static void stm32g4_rtc_mmio_write(void *opaque, hwaddr offset, uint64_t value,
                                   unsigned size)
{
    STM32G4RTCState *s = STM32G4_RTC(opaque);

    switch (offset) {
    case 0x00 ... 0x03:
        /* TR, time register */
        s->tr = value;
        break;

    case 0x04 ... 0x07:
        /* DR, date register */
        s->dr = value;
        break;

    case 0x08 ... 0x0B:
        /* SSR, sub second register */
        s->ssr = value;
        break;

    case 0x0C ... 0x0F:
        /* ICSR, initialization and status register */
        s->icsr = value;
        break;

    case 0x10 ... 0x13:
        /* PRER, prescaler register */
        s->prer = value;
        break;

    case 0x14 ... 0x17:
        /* WUTR, wakeup timer register */
        s->wutr = value;
        break;

    case 0x18 ... 0x1B:
        /* CR, control register */
        s->cr = value;
        break;

    case 0x24 ... 0x27:
        /* WPR, write protection register */
        s->wpr = value;
        break;

    case 0x28 ... 0x2B:
        /* CALR, calibration register */
        s->calr = value;
        break;

    case 0x2C ... 0x2F:
        /* SHIFTR, shift control register */
        s->shiftr = value;
        break;

    case 0x30 ... 0x33:
        /* TSTR, time stamp time register */
        s->tstr = value;
        break;

    case 0x34 ... 0x37:
        /* TSDR, time stamp date register */
        s->tsdr = value;
        break;

    case 0x38 ... 0x3B:
        /* TSSSR, timestamp sub second register */
        s->tsssr = value;
        break;

    case 0x40 ... 0x43:
        /* ALRMAR, alarm A register */
        s->alrmar = value;
        break;

    case 0x44 ... 0x47:
        /* ALRMASSR, alarm A sub second register */
        s->alrmassr = value;
        break;

    case 0x48 ... 0x4B:
        /* ALRMBR, alarm B register */
        s->alrmbr = value;
        break;

    case 0x4C ... 0x4F:
        /* ALRMBSSR, alarm B sub second register */
        s->alrmbssr = value;
        break;

    case 0x50 ... 0x53:
        /* SR, status register */
        s->sr = value;
        break;

    case 0x54 ... 0x57:
        /* MISR, status register */
        s->misr = value;
        break;

    case 0x5C ... 0x5F:
        /* SCR, status register */
        s->scr = value;
        break;

    default:
        printf("%s: unimplemented write to 0x%" HWADDR_PRIx ", size %d, "
               "value 0x%" PRIx64 "\n", __func__, offset, size, value);
        break;
    }
}

static const MemoryRegionOps stm32g4_rtc_mmio_ops = {
    .read = stm32g4_rtc_mmio_read,
    .write = stm32g4_rtc_mmio_write,
    .impl = {
        .max_access_size = 4
    }
};

static void stm32g4_rtc_instance_init(Object *obj)
{
    STM32G4RTCState *s = STM32G4_RTC(obj);

    memory_region_init_io(&s->mmio, obj, &stm32g4_rtc_mmio_ops, s,
                          STM32G4_RTC_MMIO, STM32G4_RTC_MMIO_SIZE);
    sysbus_init_mmio(SYS_BUS_DEVICE(obj), &s->mmio);
}

static void stm32g4_rtc_realize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4RTCState *s = STM32G4_RTC(dev);
}

static void stm32g4_rtc_reset(DeviceState *dev)
{
    STM32G4RTCState *s = STM32G4_RTC(dev);

    s->tr = 0x00000000;
    s->dr = 0x00002101;
    s->ssr = 0x00000000;
    s->icsr = 0x00000007;
    s->prer = 0x007F00FF;
    s->wutr = 0x0000FFFF;
    s->cr = 0x00000000;
    s->wpr = 0x00000000;
    s->calr = 0x00000000;
    s->shiftr = 0x00000000;
    s->tstr = 0x00000000;
    s->tsdr = 0x00000000;
    s->tsssr = 0x00000000;
    s->alrmar = 0x00000000;
    s->alrmassr = 0x00000000;
    s->alrmbr = 0x00000000;
    s->alrmbssr = 0x00000000;
    s->sr = 0x00000000;
    s->misr = 0x00000000;
    s->scr = 0x00000000;
}

static void stm32g4_rtc_unrealize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4RTCState *s = STM32G4_RTC(dev);
}

static Property stm32g4_rtc_properties[] = {
    DEFINE_PROP_END_OF_LIST()
};

static const VMStateDescription vmstate_stm32g4_rtc = {
    .name = "stm32g4_rtc",
    .version_id = 1,
    .fields = (VMStateField[]) {
        VMSTATE_UINT32(tr, STM32G4RTCState),
        VMSTATE_UINT32(dr, STM32G4RTCState),
        VMSTATE_UINT32(ssr, STM32G4RTCState),
        VMSTATE_UINT32(icsr, STM32G4RTCState),
        VMSTATE_UINT32(prer, STM32G4RTCState),
        VMSTATE_UINT32(wutr, STM32G4RTCState),
        VMSTATE_UINT32(cr, STM32G4RTCState),
        VMSTATE_UINT32(wpr, STM32G4RTCState),
        VMSTATE_UINT32(calr, STM32G4RTCState),
        VMSTATE_UINT32(shiftr, STM32G4RTCState),
        VMSTATE_UINT32(tstr, STM32G4RTCState),
        VMSTATE_UINT32(tsdr, STM32G4RTCState),
        VMSTATE_UINT32(tsssr, STM32G4RTCState),
        VMSTATE_UINT32(alrmar, STM32G4RTCState),
        VMSTATE_UINT32(alrmassr, STM32G4RTCState),
        VMSTATE_UINT32(alrmbr, STM32G4RTCState),
        VMSTATE_UINT32(alrmbssr, STM32G4RTCState),
        VMSTATE_UINT32(sr, STM32G4RTCState),
        VMSTATE_UINT32(misr, STM32G4RTCState),
        VMSTATE_UINT32(scr, STM32G4RTCState),
        VMSTATE_END_OF_LIST()
    }
};

static void stm32g4_rtc_class_init(ObjectClass *oc, void *opaque)
{
    DeviceClass *dc = DEVICE_CLASS(oc);

    dc->realize   = stm32g4_rtc_realize;
    dc->reset     = stm32g4_rtc_reset;
    dc->unrealize = stm32g4_rtc_unrealize;
    dc->vmsd      = &vmstate_stm32g4_rtc;
    device_class_set_props(dc, stm32g4_rtc_properties);
}

static TypeInfo stm32g4_rtc_info = {
    .name          = TYPE_STM32G4_RTC,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(STM32G4RTCState),
    .instance_init = stm32g4_rtc_instance_init,
    .class_init    = stm32g4_rtc_class_init
};

static void stm32g4_rtc_register_types(void)
{
    type_register_static(&stm32g4_rtc_info);
}

type_init(stm32g4_rtc_register_types)
