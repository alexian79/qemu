
#include "qemu/osdep.h"
#include "qemu/units.h"
#include "qemu/cutils.h"
#include "qapi/error.h"
#include "qemu/error-report.h"
#include "hw/arm/boot.h"
#include "hw/arm/armv7m.h"
#include "hw/or-irq.h"
#include "hw/boards.h"
#include "exec/address-spaces.h"
#include "sysemu/sysemu.h"
#include "hw/misc/unimp.h"
#include "hw/char/cmsdk-apb-uart.h"
#include "hw/timer/cmsdk-apb-timer.h"
#include "hw/timer/cmsdk-apb-dualtimer.h"
#include "hw/misc/mps2-scc.h"
#include "hw/misc/mps2-fpgaio.h"
#include "hw/ssi/pl022.h"
#include "hw/i2c/arm_sbcon_i2c.h"
#include "hw/net/lan9118.h"
#include "net/net.h"
#include "hw/watchdog/cmsdk-apb-watchdog.h"
#include "hw/qdev-clock.h"
#include "qom/object.h"


struct BnfMachineClass {
    MachineClass parent;
    uint32_t scc_id;
    hwaddr sram_base;
    hwaddr flash_base;
};

struct BnfMachineState {
    MachineState parent;

    ARMv7MState armv7m;
    MemoryRegion sram;
    MemoryRegion flash;
    /* CMSDK APB subsystem */
    //CMSDKAPBDualTimer dualtimer;
    //CMSDKAPBWatchdog watchdog;
    //CMSDKAPBTimer timer[2];
    Clock *sysclk;
    Clock *refclk;
};

#define TYPE_BNF_MACHINE MACHINE_TYPE_NAME("BNF")

OBJECT_DECLARE_TYPE(BnfMachineState, BnfMachineClass, BNF_MACHINE)

/* Main SYSCLK frequency in Hz */
#define SYSCLK_FRQ 25000000 // TODO: fix clock

/*
 * The Application Notes don't say anything about how the
 * systick reference clock is configured. (Quite possibly
 * they don't have one at all.) This 1MHz clock matches the
 * pre-existing behaviour that used to be hardcoded in the
 * armv7m_systick implementation.
 */
#define REFCLK_FRQ (1 * 1000 * 1000)

/* Initialize the auxiliary RAM region @mr and map it into
 * the memory map at @base.
 */
static void make_ram(MemoryRegion *mr, const char *name,
                     hwaddr base, hwaddr size)
{
    memory_region_init_ram(mr, NULL, name, size, &error_fatal);
    memory_region_add_subregion(get_system_memory(), base, mr);
}

/* Create an alias of an entire original MemoryRegion @orig
 * located at @base in the memory map.
 */
/*
static void make_ram_alias(MemoryRegion *mr, const char *name,
                           MemoryRegion *orig, hwaddr base)
{
    memory_region_init_alias(mr, NULL, name, orig, 0,
                             memory_region_size(orig));
    memory_region_add_subregion(get_system_memory(), base, mr);
}*/

static void bnf_init(MachineState *machine)
{
    BnfMachineState *mms = BNF_MACHINE(machine);
    BnfMachineClass *mmc = BNF_MACHINE_GET_CLASS(machine);
    MemoryRegion *system_memory = get_system_memory();
    //MachineClass *mc = MACHINE_GET_CLASS(machine);
    DeviceState *armv7m;

    /* This clock doesn't need migration because it is fixed-frequency */
    mms->sysclk = clock_new(OBJECT(machine), "SYSCLK");
    clock_set_hz(mms->sysclk, SYSCLK_FRQ);

    mms->refclk = clock_new(OBJECT(machine), "REFCLK");
    clock_set_hz(mms->refclk, REFCLK_FRQ);

    memory_region_add_subregion(system_memory, mmc->flash_base, machine->ram);
    make_ram(&mms->sram, "bnf.sram", mmc->sram_base, 1 * MiB);
    //make_ram_alias(&mms->flash, "bnf.flash", &mms->sram, mmc->flash_base);

    object_initialize_child(OBJECT(mms), "armv7m", &mms->armv7m, TYPE_ARMV7M);
    armv7m = DEVICE(&mms->armv7m);
    qdev_prop_set_uint32(armv7m, "num-irq", 128);// TODO: set correct number
    qdev_connect_clock_in(armv7m, "cpuclk", mms->sysclk);
    qdev_connect_clock_in(armv7m, "refclk", mms->refclk);
    qdev_prop_set_string(armv7m, "cpu-type", machine->cpu_type);
    qdev_prop_set_bit(armv7m, "enable-bitband", true);
    object_property_set_link(OBJECT(&mms->armv7m), "memory",
                             OBJECT(system_memory), &error_abort);
    sysbus_realize(SYS_BUS_DEVICE(&mms->armv7m), &error_fatal);

    //create_unimplemented_device("RESERVED 1", 0x00800000, 0x00800000);
    
    armv7m_load_kernel(ARM_CPU(first_cpu), machine->kernel_filename,
                       1 * MiB);
}

static void bnf_class_init(ObjectClass *oc, void *data)
{
    MachineClass *mc = MACHINE_CLASS(oc);
    BnfMachineClass *mmc = BNF_MACHINE_CLASS(oc);

    mc->init = bnf_init;
    mc->desc = "BNF cortex-m4";
    mc->max_cpus = 1;
    mc->default_ram_size = 1 * MiB;
    mc->default_ram_id = "bnf.flash";
    mc->default_cpu_type = ARM_CPU_TYPE_NAME("cortex-m4");
    mmc->sram_base = 0x20000000;
    mmc->flash_base = 0x00000000;
}

static const TypeInfo bnf_info = {
    .name = TYPE_BNF_MACHINE,
    .parent = TYPE_MACHINE,
    .abstract = false,
    .instance_size = sizeof(BnfMachineState),
    .class_size = sizeof(BnfMachineClass),
    .class_init = bnf_class_init,
};

static void bnf_machine_init(void)
{
    type_register_static(&bnf_info);
}

type_init(bnf_machine_init);
