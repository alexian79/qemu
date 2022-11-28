/* stm32g4_sai.c */

#include "qemu/osdep.h"
#include "hw/irq.h"
#include "hw/qdev-properties.h"
#include "include/hw/arm/stm32g4/stm32g4_sai.h"
#include "migration/vmstate.h"

#define STM32G4_SAI_MMIO TYPE_STM32G4_SAI "_mmio"
#define STM32G4_SAI_MMIO_SIZE 0x48

static uint64_t stm32g4_sai_mmio_read(void *opaque, hwaddr offset,
                                      unsigned size)
{
    STM32G4SAIState *s = STM32G4_SAI(opaque);
    uint64_t ret = 0;

    switch (offset) {
    case 0x00 ... 0x03:
        /* ACR1, AConfiguration register 1 */
        ret = s->acr1;
        break;

    case 0x04 ... 0x07:
        /* ACR2, AConfiguration register 2 */
        ret = s->acr2;
        break;

    case 0x08 ... 0x0B:
        /* AFRCR, AFRCR */
        ret = s->afrcr;
        break;

    case 0x0C ... 0x0F:
        /* ASLOTR, ASlot register */
        ret = s->aslotr;
        break;

    case 0x10 ... 0x13:
        /* AIM, AInterrupt mask register2 */
        ret = s->aim;
        break;

    case 0x14 ... 0x17:
        /* ASR, AStatus register */
        ret = s->asr;
        break;

    case 0x18 ... 0x1B:
        /* ACLRFR, AClear flag register */
        ret = s->aclrfr;
        break;

    case 0x1C ... 0x1F:
        /* ADR, AData register */
        ret = s->adr;
        break;

    case 0x20 ... 0x23:
        /* BCR1, BConfiguration register 1 */
        ret = s->bcr1;
        break;

    case 0x24 ... 0x27:
        /* BCR2, BConfiguration register 2 */
        ret = s->bcr2;
        break;

    case 0x28 ... 0x2B:
        /* BFRCR, BFRCR */
        ret = s->bfrcr;
        break;

    case 0x2C ... 0x2F:
        /* BSLOTR, BSlot register */
        ret = s->bslotr;
        break;

    case 0x30 ... 0x33:
        /* BIM, BInterrupt mask register2 */
        ret = s->bim;
        break;

    case 0x34 ... 0x37:
        /* BSR, BStatus register */
        ret = s->bsr;
        break;

    case 0x38 ... 0x3B:
        /* BCLRFR, BClear flag register */
        ret = s->bclrfr;
        break;

    case 0x3C ... 0x3F:
        /* BDR, BData register */
        ret = s->bdr;
        break;

    case 0x40 ... 0x43:
        /* PDMCR, PDM control register */
        ret = s->pdmcr;
        break;

    case 0x44 ... 0x47:
        /* PDMDLY, PDM delay register */
        ret = s->pdmdly;
        break;

    default:
        printf("%s: unimplemented read from 0x%" HWADDR_PRIx ", size %d\n",
               __func__, offset, size);
        break;
    }

    return ret;
}

static void stm32g4_sai_mmio_write(void *opaque, hwaddr offset, uint64_t value,
                                   unsigned size)
{
    STM32G4SAIState *s = STM32G4_SAI(opaque);

    switch (offset) {
    case 0x00 ... 0x03:
        /* ACR1, AConfiguration register 1 */
        s->acr1 = value;
        break;

    case 0x04 ... 0x07:
        /* ACR2, AConfiguration register 2 */
        s->acr2 = value;
        break;

    case 0x08 ... 0x0B:
        /* AFRCR, AFRCR */
        s->afrcr = value;
        break;

    case 0x0C ... 0x0F:
        /* ASLOTR, ASlot register */
        s->aslotr = value;
        break;

    case 0x10 ... 0x13:
        /* AIM, AInterrupt mask register2 */
        s->aim = value;
        break;

    case 0x14 ... 0x17:
        /* ASR, AStatus register */
        s->asr = value;
        break;

    case 0x18 ... 0x1B:
        /* ACLRFR, AClear flag register */
        s->aclrfr = value;
        break;

    case 0x1C ... 0x1F:
        /* ADR, AData register */
        s->adr = value;
        break;

    case 0x20 ... 0x23:
        /* BCR1, BConfiguration register 1 */
        s->bcr1 = value;
        break;

    case 0x24 ... 0x27:
        /* BCR2, BConfiguration register 2 */
        s->bcr2 = value;
        break;

    case 0x28 ... 0x2B:
        /* BFRCR, BFRCR */
        s->bfrcr = value;
        break;

    case 0x2C ... 0x2F:
        /* BSLOTR, BSlot register */
        s->bslotr = value;
        break;

    case 0x30 ... 0x33:
        /* BIM, BInterrupt mask register2 */
        s->bim = value;
        break;

    case 0x34 ... 0x37:
        /* BSR, BStatus register */
        s->bsr = value;
        break;

    case 0x38 ... 0x3B:
        /* BCLRFR, BClear flag register */
        s->bclrfr = value;
        break;

    case 0x3C ... 0x3F:
        /* BDR, BData register */
        s->bdr = value;
        break;

    case 0x40 ... 0x43:
        /* PDMCR, PDM control register */
        s->pdmcr = value;
        break;

    case 0x44 ... 0x47:
        /* PDMDLY, PDM delay register */
        s->pdmdly = value;
        break;

    default:
        printf("%s: unimplemented write to 0x%" HWADDR_PRIx ", size %d, "
               "value 0x%" PRIx64 "\n", __func__, offset, size, value);
        break;
    }
}

static const MemoryRegionOps stm32g4_sai_mmio_ops = {
    .read = stm32g4_sai_mmio_read,
    .write = stm32g4_sai_mmio_write,
    .impl = {
        .max_access_size = 4
    }
};

static void stm32g4_sai_instance_init(Object *obj)
{
    STM32G4SAIState *s = STM32G4_SAI(obj);

    memory_region_init_io(&s->mmio, obj, &stm32g4_sai_mmio_ops, s,
                          STM32G4_SAI_MMIO, STM32G4_SAI_MMIO_SIZE);
    sysbus_init_mmio(SYS_BUS_DEVICE(obj), &s->mmio);
}

static void stm32g4_sai_realize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4SAIState *s = STM32G4_SAI(dev);
}

static void stm32g4_sai_reset(DeviceState *dev)
{
    STM32G4SAIState *s = STM32G4_SAI(dev);

    s->acr1 = 0x00000040;
    s->acr2 = 0x00000000;
    s->afrcr = 0x00000007;
    s->aslotr = 0x00000000;
    s->aim = 0x00000000;
    s->asr = 0x00000000;
    s->aclrfr = 0x00000000;
    s->adr = 0x00000000;
    s->bcr1 = 0x00000040;
    s->bcr2 = 0x00000000;
    s->bfrcr = 0x00000007;
    s->bslotr = 0x00000000;
    s->bim = 0x00000000;
    s->bsr = 0x00000000;
    s->bclrfr = 0x00000000;
    s->bdr = 0x00000000;
    s->pdmcr = 0x00000000;
    s->pdmdly = 0x00000000;
}

static void stm32g4_sai_unrealize(DeviceState *dev, Error **errp)
{
    __attribute__((unused)) STM32G4SAIState *s = STM32G4_SAI(dev);
}

static Property stm32g4_sai_properties[] = {
    DEFINE_PROP_END_OF_LIST()
};

static const VMStateDescription vmstate_stm32g4_sai = {
    .name = "stm32g4_sai",
    .version_id = 1,
    .fields = (VMStateField[]) {
        VMSTATE_UINT32(acr1, STM32G4SAIState),
        VMSTATE_UINT32(acr2, STM32G4SAIState),
        VMSTATE_UINT32(afrcr, STM32G4SAIState),
        VMSTATE_UINT32(aslotr, STM32G4SAIState),
        VMSTATE_UINT32(aim, STM32G4SAIState),
        VMSTATE_UINT32(asr, STM32G4SAIState),
        VMSTATE_UINT32(aclrfr, STM32G4SAIState),
        VMSTATE_UINT32(adr, STM32G4SAIState),
        VMSTATE_UINT32(bcr1, STM32G4SAIState),
        VMSTATE_UINT32(bcr2, STM32G4SAIState),
        VMSTATE_UINT32(bfrcr, STM32G4SAIState),
        VMSTATE_UINT32(bslotr, STM32G4SAIState),
        VMSTATE_UINT32(bim, STM32G4SAIState),
        VMSTATE_UINT32(bsr, STM32G4SAIState),
        VMSTATE_UINT32(bclrfr, STM32G4SAIState),
        VMSTATE_UINT32(bdr, STM32G4SAIState),
        VMSTATE_UINT32(pdmcr, STM32G4SAIState),
        VMSTATE_UINT32(pdmdly, STM32G4SAIState),
        VMSTATE_END_OF_LIST()
    }
};

static void stm32g4_sai_class_init(ObjectClass *oc, void *opaque)
{
    DeviceClass *dc = DEVICE_CLASS(oc);

    dc->realize   = stm32g4_sai_realize;
    dc->reset     = stm32g4_sai_reset;
    dc->unrealize = stm32g4_sai_unrealize;
    dc->vmsd      = &vmstate_stm32g4_sai;
    device_class_set_props(dc, stm32g4_sai_properties);
}

static TypeInfo stm32g4_sai_info = {
    .name          = TYPE_STM32G4_SAI,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(STM32G4SAIState),
    .instance_init = stm32g4_sai_instance_init,
    .class_init    = stm32g4_sai_class_init
};

static void stm32g4_sai_register_types(void)
{
    type_register_static(&stm32g4_sai_info);
}

type_init(stm32g4_sai_register_types)
