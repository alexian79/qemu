/* bnf.c */

#include "qemu/osdep.h"
#include "hw/irq.h"
#include "hw/arm/armv7m.h"
#include "hw/arm/boot.h"
#include "migration/vmstate.h"
#include "hw/boards.h"
#include "exec/address-spaces.h"
#include "qemu/units.h"
#include "include/hw/arm/stm32g4/stm32g4_adc1.h"
#include "include/hw/arm/stm32g4/stm32g4_adc12_common.h"
#include "include/hw/arm/stm32g4/stm32g4_adc3.h"
#include "include/hw/arm/stm32g4/stm32g4_comp.h"
#include "include/hw/arm/stm32g4/stm32g4_cordic.h"
#include "include/hw/arm/stm32g4/stm32g4_crc.h"
#include "include/hw/arm/stm32g4/stm32g4_crs.h"
#include "include/hw/arm/stm32g4/stm32g4_dac1.h"
#include "include/hw/arm/stm32g4/stm32g4_dbgmcu.h"
#include "include/hw/arm/stm32g4/stm32g4_dma1.h"
#include "include/hw/arm/stm32g4/stm32g4_dmamux.h"
#include "include/hw/arm/stm32g4/stm32g4_exti.h"
#include "include/hw/arm/stm32g4/stm32g4_fdcan.h"
#include "include/hw/arm/stm32g4/stm32g4_flash.h"
#include "include/hw/arm/stm32g4/stm32g4_fmac.h"
#include "include/hw/arm/stm32g4/stm32g4_fmc.h"
#include "include/hw/arm/stm32g4/stm32g4_fpu.h"
#include "include/hw/arm/stm32g4/stm32g4_fpu_cpacr.h"
#include "include/hw/arm/stm32g4/stm32g4_gpioa.h"
#include "include/hw/arm/stm32g4/stm32g4_gpiob.h"
#include "include/hw/arm/stm32g4/stm32g4_gpioc.h"
#include "include/hw/arm/stm32g4/stm32g4_i2c1.h"
#include "include/hw/arm/stm32g4/stm32g4_iwdg.h"
#include "include/hw/arm/stm32g4/stm32g4_lptimer1.h"
#include "include/hw/arm/stm32g4/stm32g4_lpuart1.h"
#include "include/hw/arm/stm32g4/stm32g4_mpu.h"
#include "include/hw/arm/stm32g4/stm32g4_nvic.h"
#include "include/hw/arm/stm32g4/stm32g4_nvic_stir.h"
#include "include/hw/arm/stm32g4/stm32g4_opamp.h"
#include "include/hw/arm/stm32g4/stm32g4_pwr.h"
#include "include/hw/arm/stm32g4/stm32g4_quadspi.h"
#include "include/hw/arm/stm32g4/stm32g4_rcc.h"
#include "include/hw/arm/stm32g4/stm32g4_rng.h"
#include "include/hw/arm/stm32g4/stm32g4_rtc.h"
#include "include/hw/arm/stm32g4/stm32g4_sai.h"
#include "include/hw/arm/stm32g4/stm32g4_scb.h"
#include "include/hw/arm/stm32g4/stm32g4_scb_actlr.h"
#include "include/hw/arm/stm32g4/stm32g4_spi1.h"
#include "include/hw/arm/stm32g4/stm32g4_spi4.h"
#include "include/hw/arm/stm32g4/stm32g4_stk.h"
#include "include/hw/arm/stm32g4/stm32g4_syscfg.h"
#include "include/hw/arm/stm32g4/stm32g4_tamp.h"
#include "include/hw/arm/stm32g4/stm32g4_tim1.h"
#include "include/hw/arm/stm32g4/stm32g4_tim15.h"
#include "include/hw/arm/stm32g4/stm32g4_tim16.h"
#include "include/hw/arm/stm32g4/stm32g4_tim2.h"
#include "include/hw/arm/stm32g4/stm32g4_tim6.h"
#include "include/hw/arm/stm32g4/stm32g4_uart4.h"
#include "include/hw/arm/stm32g4/stm32g4_ucpd1.h"
#include "include/hw/arm/stm32g4/stm32g4_usart1.h"
#include "include/hw/arm/stm32g4/stm32g4_usb_fs_device.h"
#include "include/hw/arm/stm32g4/stm32g4_vrefbuf.h"
#include "include/hw/arm/stm32g4/stm32g4_wwdg.h"

static void init_bnf(MachineState *machine)
{
    MemoryRegion *system_mem;
    DeviceState *armv7m;
    DeviceState *crc;
    DeviceState *iwdg;
    DeviceState *wwdg;
    DeviceState *i2c1;
    DeviceState *i2c2;
    DeviceState *i2c3;
    DeviceState *i2c4;
    DeviceState *flash;
    DeviceState *dbgmcu;
    DeviceState *rcc;
    DeviceState *pwr;
    DeviceState *rng;
    DeviceState *gpioa;
    DeviceState *gpiob;
    DeviceState *gpioc;
    DeviceState *gpiod;
    DeviceState *gpioe;
    DeviceState *gpiof;
    DeviceState *gpiog;
    DeviceState *tim15;
    DeviceState *tim16;
    DeviceState *tim17;
    DeviceState *tim1;
    DeviceState *tim20;
    DeviceState *tim8;
    DeviceState *tim2;
    DeviceState *tim3;
    DeviceState *tim4;
    DeviceState *tim5;
    DeviceState *tim6;
    DeviceState *tim7;
    DeviceState *lptimer1;
    DeviceState *usart1;
    DeviceState *usart2;
    DeviceState *usart3;
    DeviceState *uart4;
    DeviceState *uart5;
    DeviceState *lpuart1;
    DeviceState *spi1;
    DeviceState *spi4;
    DeviceState *spi3;
    DeviceState *spi2;
    DeviceState *exti;
    DeviceState *rtc;
    DeviceState *fmc;
    DeviceState *dma1;
    DeviceState *dma2;
    DeviceState *dmamux;
    DeviceState *syscfg;
    DeviceState *vrefbuf;
    DeviceState *comp;
    DeviceState *opamp;
    DeviceState *quadspi;
    DeviceState *dac1;
    DeviceState *dac2;
    DeviceState *dac3;
    DeviceState *dac4;
    DeviceState *adc1;
    DeviceState *adc2;
    DeviceState *adc3;
    DeviceState *adc4;
    DeviceState *adc5;
    DeviceState *adc12_common;
    DeviceState *adc345_common;
    DeviceState *fmac;
    DeviceState *cordic;
    DeviceState *sai;
    DeviceState *tamp;
    DeviceState *fpu;
    DeviceState *mpu;
    DeviceState *stk;
    DeviceState *scb;
    DeviceState *nvic;
    DeviceState *nvic_stir;
    DeviceState *fpu_cpacr;
    DeviceState *scb_actlr;
    DeviceState *fdcan;
    DeviceState *fdcan1;
    DeviceState *fdcan2;
    DeviceState *fdcan3;
    DeviceState *ucpd1;
    DeviceState *usb_fs_device;
    DeviceState *crs;
    MemoryRegion *flash_86;
    MemoryRegion *sram;
    MemoryRegion *alias;

    system_mem = get_system_memory();
    //g_new(MemoryRegion, 1);
    //memory_region_init(system_mem, NULL, "system_memory", 0xFFFFFFFFFF);

    armv7m = qdev_create(NULL, TYPE_ARMV7M);
    object_property_set_str(OBJECT(armv7m), "cortex-m4-arm-cpu", "cpu-type",
                            NULL);
    object_property_set_bool(OBJECT(armv7m), true, "enable-bitband", NULL);
    object_property_set_link(OBJECT(armv7m), OBJECT(system_mem), "memory",
                             NULL);
    object_property_set_int(OBJECT(armv7m), 0x40, "num-irq", NULL);
    qdev_init_nofail(armv7m);

    crc = qdev_create(NULL, TYPE_STM32G4_CRC);
    qdev_init_nofail(crc);
    sysbus_mmio_map(SYS_BUS_DEVICE(crc), 0, 0x40023000);

    iwdg = qdev_create(NULL, TYPE_STM32G4_IWDG);
    qdev_init_nofail(iwdg);
    sysbus_mmio_map(SYS_BUS_DEVICE(iwdg), 0, 0x40003000);

    wwdg = qdev_create(NULL, TYPE_STM32G4_WWDG);
    qdev_init_nofail(wwdg);
    sysbus_mmio_map(SYS_BUS_DEVICE(wwdg), 0, 0x40002c00);

    i2c1 = qdev_create(NULL, TYPE_STM32G4_I2C1);
    qdev_init_nofail(i2c1);
    sysbus_mmio_map(SYS_BUS_DEVICE(i2c1), 0, 0x40005400);

    i2c2 = qdev_create(NULL, TYPE_STM32G4_I2C1);
    qdev_init_nofail(i2c2);
    sysbus_mmio_map(SYS_BUS_DEVICE(i2c2), 0, 0x40005800);

    i2c3 = qdev_create(NULL, TYPE_STM32G4_I2C1);
    qdev_init_nofail(i2c3);
    sysbus_mmio_map(SYS_BUS_DEVICE(i2c3), 0, 0x40007800);

    i2c4 = qdev_create(NULL, TYPE_STM32G4_I2C1);
    qdev_init_nofail(i2c4);
    sysbus_mmio_map(SYS_BUS_DEVICE(i2c4), 0, 0x40008400);

    flash = qdev_create(NULL, TYPE_STM32G4_FLASH);
    qdev_init_nofail(flash);
    sysbus_mmio_map(SYS_BUS_DEVICE(flash), 0, 0x40022000);

    dbgmcu = qdev_create(NULL, TYPE_STM32G4_DBGMCU);
    qdev_init_nofail(dbgmcu);
    sysbus_mmio_map(SYS_BUS_DEVICE(dbgmcu), 0, 0xe0042000);

    rcc = qdev_create(NULL, TYPE_STM32G4_RCC);
    qdev_init_nofail(rcc);
    sysbus_mmio_map(SYS_BUS_DEVICE(rcc), 0, 0x40021000);

    pwr = qdev_create(NULL, TYPE_STM32G4_PWR);
    qdev_init_nofail(pwr);
    sysbus_mmio_map(SYS_BUS_DEVICE(pwr), 0, 0x40007000);

    rng = qdev_create(NULL, TYPE_STM32G4_RNG);
    qdev_init_nofail(rng);
    sysbus_mmio_map(SYS_BUS_DEVICE(rng), 0, 0x50060800);

    gpioa = qdev_create(NULL, TYPE_STM32G4_GPIOA);
    qdev_init_nofail(gpioa);
    sysbus_mmio_map(SYS_BUS_DEVICE(gpioa), 0, 0x48000000);

    gpiob = qdev_create(NULL, TYPE_STM32G4_GPIOB);
    qdev_init_nofail(gpiob);
    sysbus_mmio_map(SYS_BUS_DEVICE(gpiob), 0, 0x48000400);

    gpioc = qdev_create(NULL, TYPE_STM32G4_GPIOC);
    qdev_init_nofail(gpioc);
    sysbus_mmio_map(SYS_BUS_DEVICE(gpioc), 0, 0x48000800);

    gpiod = qdev_create(NULL, TYPE_STM32G4_GPIOC);
    qdev_init_nofail(gpiod);
    sysbus_mmio_map(SYS_BUS_DEVICE(gpiod), 0, 0x48000c00);

    gpioe = qdev_create(NULL, TYPE_STM32G4_GPIOC);
    qdev_init_nofail(gpioe);
    sysbus_mmio_map(SYS_BUS_DEVICE(gpioe), 0, 0x48001000);

    gpiof = qdev_create(NULL, TYPE_STM32G4_GPIOC);
    qdev_init_nofail(gpiof);
    sysbus_mmio_map(SYS_BUS_DEVICE(gpiof), 0, 0x48001400);

    gpiog = qdev_create(NULL, TYPE_STM32G4_GPIOC);
    qdev_init_nofail(gpiog);
    sysbus_mmio_map(SYS_BUS_DEVICE(gpiog), 0, 0x48001800);

    tim15 = qdev_create(NULL, TYPE_STM32G4_TIM15);
    qdev_init_nofail(tim15);
    sysbus_mmio_map(SYS_BUS_DEVICE(tim15), 0, 0x40014000);

    tim16 = qdev_create(NULL, TYPE_STM32G4_TIM16);
    qdev_init_nofail(tim16);
    sysbus_mmio_map(SYS_BUS_DEVICE(tim16), 0, 0x40014400);

    tim17 = qdev_create(NULL, TYPE_STM32G4_TIM16);
    qdev_init_nofail(tim17);
    sysbus_mmio_map(SYS_BUS_DEVICE(tim17), 0, 0x40014800);

    tim1 = qdev_create(NULL, TYPE_STM32G4_TIM1);
    qdev_init_nofail(tim1);
    sysbus_mmio_map(SYS_BUS_DEVICE(tim1), 0, 0x40012c00);

    tim20 = qdev_create(NULL, TYPE_STM32G4_TIM1);
    qdev_init_nofail(tim20);
    sysbus_mmio_map(SYS_BUS_DEVICE(tim20), 0, 0x40015000);

    tim8 = qdev_create(NULL, TYPE_STM32G4_TIM1);
    qdev_init_nofail(tim8);
    sysbus_mmio_map(SYS_BUS_DEVICE(tim8), 0, 0x40013400);

    tim2 = qdev_create(NULL, TYPE_STM32G4_TIM2);
    qdev_init_nofail(tim2);
    sysbus_mmio_map(SYS_BUS_DEVICE(tim2), 0, 0x40000000);

    tim3 = qdev_create(NULL, TYPE_STM32G4_TIM2);
    qdev_init_nofail(tim3);
    sysbus_mmio_map(SYS_BUS_DEVICE(tim3), 0, 0x40000400);

    tim4 = qdev_create(NULL, TYPE_STM32G4_TIM2);
    qdev_init_nofail(tim4);
    sysbus_mmio_map(SYS_BUS_DEVICE(tim4), 0, 0x40000800);

    tim5 = qdev_create(NULL, TYPE_STM32G4_TIM2);
    qdev_init_nofail(tim5);
    sysbus_mmio_map(SYS_BUS_DEVICE(tim5), 0, 0x40000c00);

    tim6 = qdev_create(NULL, TYPE_STM32G4_TIM6);
    qdev_init_nofail(tim6);
    sysbus_mmio_map(SYS_BUS_DEVICE(tim6), 0, 0x40001000);

    tim7 = qdev_create(NULL, TYPE_STM32G4_TIM6);
    qdev_init_nofail(tim7);
    sysbus_mmio_map(SYS_BUS_DEVICE(tim7), 0, 0x40001400);

    lptimer1 = qdev_create(NULL, TYPE_STM32G4_LPTIMER1);
    qdev_init_nofail(lptimer1);
    sysbus_mmio_map(SYS_BUS_DEVICE(lptimer1), 0, 0x40007c00);

    usart1 = qdev_create(NULL, TYPE_STM32G4_USART1);
    qdev_init_nofail(usart1);
    sysbus_mmio_map(SYS_BUS_DEVICE(usart1), 0, 0x40013800);

    usart2 = qdev_create(NULL, TYPE_STM32G4_USART1);
    qdev_init_nofail(usart2);
    sysbus_mmio_map(SYS_BUS_DEVICE(usart2), 0, 0x40004400);

    usart3 = qdev_create(NULL, TYPE_STM32G4_USART1);
    qdev_init_nofail(usart3);
    sysbus_mmio_map(SYS_BUS_DEVICE(usart3), 0, 0x40004800);

    uart4 = qdev_create(NULL, TYPE_STM32G4_UART4);
    qdev_init_nofail(uart4);
    sysbus_mmio_map(SYS_BUS_DEVICE(uart4), 0, 0x40004c00);

    uart5 = qdev_create(NULL, TYPE_STM32G4_UART4);
    qdev_init_nofail(uart5);
    sysbus_mmio_map(SYS_BUS_DEVICE(uart5), 0, 0x40005000);

    lpuart1 = qdev_create(NULL, TYPE_STM32G4_LPUART1);
    qdev_init_nofail(lpuart1);
    sysbus_mmio_map(SYS_BUS_DEVICE(lpuart1), 0, 0x40008000);

    spi1 = qdev_create(NULL, TYPE_STM32G4_SPI1);
    qdev_init_nofail(spi1);
    sysbus_mmio_map(SYS_BUS_DEVICE(spi1), 0, 0x40013000);

    spi4 = qdev_create(NULL, TYPE_STM32G4_SPI4);
    qdev_init_nofail(spi4);
    sysbus_mmio_map(SYS_BUS_DEVICE(spi4), 0, 0x40013c00);

    spi3 = qdev_create(NULL, TYPE_STM32G4_SPI4);
    qdev_init_nofail(spi3);
    sysbus_mmio_map(SYS_BUS_DEVICE(spi3), 0, 0x40003c00);

    spi2 = qdev_create(NULL, TYPE_STM32G4_SPI4);
    qdev_init_nofail(spi2);
    sysbus_mmio_map(SYS_BUS_DEVICE(spi2), 0, 0x40003800);

    exti = qdev_create(NULL, TYPE_STM32G4_EXTI);
    qdev_init_nofail(exti);
    sysbus_mmio_map(SYS_BUS_DEVICE(exti), 0, 0x40010400);

    rtc = qdev_create(NULL, TYPE_STM32G4_RTC);
    qdev_init_nofail(rtc);
    sysbus_mmio_map(SYS_BUS_DEVICE(rtc), 0, 0x40002800);

    fmc = qdev_create(NULL, TYPE_STM32G4_FMC);
    qdev_init_nofail(fmc);
    sysbus_mmio_map(SYS_BUS_DEVICE(fmc), 0, 0xa0000000);

    dma1 = qdev_create(NULL, TYPE_STM32G4_DMA1);
    qdev_init_nofail(dma1);
    sysbus_mmio_map(SYS_BUS_DEVICE(dma1), 0, 0x40020000);

    dma2 = qdev_create(NULL, TYPE_STM32G4_DMA1);
    qdev_init_nofail(dma2);
    sysbus_mmio_map(SYS_BUS_DEVICE(dma2), 0, 0x40020400);

    dmamux = qdev_create(NULL, TYPE_STM32G4_DMAMUX);
    qdev_init_nofail(dmamux);
    sysbus_mmio_map(SYS_BUS_DEVICE(dmamux), 0, 0x40020800);

    syscfg = qdev_create(NULL, TYPE_STM32G4_SYSCFG);
    qdev_init_nofail(syscfg);
    sysbus_mmio_map(SYS_BUS_DEVICE(syscfg), 0, 0x40010000);

    vrefbuf = qdev_create(NULL, TYPE_STM32G4_VREFBUF);
    qdev_init_nofail(vrefbuf);
    sysbus_mmio_map(SYS_BUS_DEVICE(vrefbuf), 0, 0x40010030);

    comp = qdev_create(NULL, TYPE_STM32G4_COMP);
    qdev_init_nofail(comp);
    sysbus_mmio_map(SYS_BUS_DEVICE(comp), 0, 0x40010200);

    opamp = qdev_create(NULL, TYPE_STM32G4_OPAMP);
    qdev_init_nofail(opamp);
    sysbus_mmio_map(SYS_BUS_DEVICE(opamp), 0, 0x40010300);

    quadspi = qdev_create(NULL, TYPE_STM32G4_QUADSPI);
    qdev_init_nofail(quadspi);
    sysbus_mmio_map(SYS_BUS_DEVICE(quadspi), 0, 0xa0001000);

    dac1 = qdev_create(NULL, TYPE_STM32G4_DAC1);
    qdev_init_nofail(dac1);
    sysbus_mmio_map(SYS_BUS_DEVICE(dac1), 0, 0x50000800);

    dac2 = qdev_create(NULL, TYPE_STM32G4_DAC1);
    qdev_init_nofail(dac2);
    sysbus_mmio_map(SYS_BUS_DEVICE(dac2), 0, 0x50000c00);

    dac3 = qdev_create(NULL, TYPE_STM32G4_DAC1);
    qdev_init_nofail(dac3);
    sysbus_mmio_map(SYS_BUS_DEVICE(dac3), 0, 0x50001000);

    dac4 = qdev_create(NULL, TYPE_STM32G4_DAC1);
    qdev_init_nofail(dac4);
    sysbus_mmio_map(SYS_BUS_DEVICE(dac4), 0, 0x50001400);

    adc1 = qdev_create(NULL, TYPE_STM32G4_ADC1);
    qdev_init_nofail(adc1);
    sysbus_mmio_map(SYS_BUS_DEVICE(adc1), 0, 0x50000000);

    adc2 = qdev_create(NULL, TYPE_STM32G4_ADC1);
    qdev_init_nofail(adc2);
    sysbus_mmio_map(SYS_BUS_DEVICE(adc2), 0, 0x50000100);

    adc3 = qdev_create(NULL, TYPE_STM32G4_ADC3);
    qdev_init_nofail(adc3);
    sysbus_mmio_map(SYS_BUS_DEVICE(adc3), 0, 0x50000400);

    adc4 = qdev_create(NULL, TYPE_STM32G4_ADC1);
    qdev_init_nofail(adc4);
    sysbus_mmio_map(SYS_BUS_DEVICE(adc4), 0, 0x50000500);

    adc5 = qdev_create(NULL, TYPE_STM32G4_ADC3);
    qdev_init_nofail(adc5);
    sysbus_mmio_map(SYS_BUS_DEVICE(adc5), 0, 0x50000600);

    adc12_common = qdev_create(NULL, TYPE_STM32G4_ADC12_COMMON);
    qdev_init_nofail(adc12_common);
    sysbus_mmio_map(SYS_BUS_DEVICE(adc12_common), 0, 0x50000300);

    adc345_common = qdev_create(NULL, TYPE_STM32G4_ADC12_COMMON);
    qdev_init_nofail(adc345_common);
    sysbus_mmio_map(SYS_BUS_DEVICE(adc345_common), 0, 0x50000700);

    fmac = qdev_create(NULL, TYPE_STM32G4_FMAC);
    qdev_init_nofail(fmac);
    sysbus_mmio_map(SYS_BUS_DEVICE(fmac), 0, 0x40021400);

    cordic = qdev_create(NULL, TYPE_STM32G4_CORDIC);
    qdev_init_nofail(cordic);
    sysbus_mmio_map(SYS_BUS_DEVICE(cordic), 0, 0x40020c00);

    sai = qdev_create(NULL, TYPE_STM32G4_SAI);
    qdev_init_nofail(sai);
    sysbus_mmio_map(SYS_BUS_DEVICE(sai), 0, 0x40015400);

    tamp = qdev_create(NULL, TYPE_STM32G4_TAMP);
    qdev_init_nofail(tamp);
    sysbus_mmio_map(SYS_BUS_DEVICE(tamp), 0, 0x40002400);

    fpu = qdev_create(NULL, TYPE_STM32G4_FPU);
    qdev_init_nofail(fpu);
    sysbus_mmio_map(SYS_BUS_DEVICE(fpu), 0, 0xe000ef34);

    mpu = qdev_create(NULL, TYPE_STM32G4_MPU);
    qdev_init_nofail(mpu);
    sysbus_mmio_map(SYS_BUS_DEVICE(mpu), 0, 0xe000e084);

    stk = qdev_create(NULL, TYPE_STM32G4_STK);
    qdev_init_nofail(stk);
    sysbus_mmio_map(SYS_BUS_DEVICE(stk), 0, 0xe000e010);

    scb = qdev_create(NULL, TYPE_STM32G4_SCB);
    qdev_init_nofail(scb);
    sysbus_mmio_map(SYS_BUS_DEVICE(scb), 0, 0xe000ed00);

    nvic = qdev_create(NULL, TYPE_STM32G4_NVIC);
    qdev_init_nofail(nvic);
    sysbus_mmio_map(SYS_BUS_DEVICE(nvic), 0, 0xe000e100);

    nvic_stir = qdev_create(NULL, TYPE_STM32G4_NVIC_STIR);
    qdev_init_nofail(nvic_stir);
    sysbus_mmio_map(SYS_BUS_DEVICE(nvic_stir), 0, 0xe000ef00);

    fpu_cpacr = qdev_create(NULL, TYPE_STM32G4_FPU_CPACR);
    qdev_init_nofail(fpu_cpacr);
    sysbus_mmio_map(SYS_BUS_DEVICE(fpu_cpacr), 0, 0xe000ed88);

    scb_actlr = qdev_create(NULL, TYPE_STM32G4_SCB_ACTLR);
    qdev_init_nofail(scb_actlr);
    sysbus_mmio_map(SYS_BUS_DEVICE(scb_actlr), 0, 0xe000e008);

    fdcan = qdev_create(NULL, TYPE_STM32G4_FDCAN);
    qdev_init_nofail(fdcan);
    sysbus_mmio_map(SYS_BUS_DEVICE(fdcan), 0, 0x4000a400);

    fdcan1 = qdev_create(NULL, TYPE_STM32G4_FDCAN);
    qdev_init_nofail(fdcan1);
    sysbus_mmio_map(SYS_BUS_DEVICE(fdcan1), 0, 0x40006400);

    fdcan2 = qdev_create(NULL, TYPE_STM32G4_FDCAN);
    qdev_init_nofail(fdcan2);
    sysbus_mmio_map(SYS_BUS_DEVICE(fdcan2), 0, 0x40006800);

    fdcan3 = qdev_create(NULL, TYPE_STM32G4_FDCAN);
    qdev_init_nofail(fdcan3);
    sysbus_mmio_map(SYS_BUS_DEVICE(fdcan3), 0, 0x40006c00);

    ucpd1 = qdev_create(NULL, TYPE_STM32G4_UCPD1);
    qdev_init_nofail(ucpd1);
    sysbus_mmio_map(SYS_BUS_DEVICE(ucpd1), 0, 0x4000a000);

    usb_fs_device = qdev_create(NULL, TYPE_STM32G4_USB_FS_DEVICE);
    qdev_init_nofail(usb_fs_device);
    sysbus_mmio_map(SYS_BUS_DEVICE(usb_fs_device), 0, 0x40005c00);

    crs = qdev_create(NULL, TYPE_STM32G4_CRS);
    qdev_init_nofail(crs);
    sysbus_mmio_map(SYS_BUS_DEVICE(crs), 0, 0x40002000);

    flash_86 = g_new(MemoryRegion, 1);
    memory_region_init_ram(flash_86, NULL, "flash", 524288, NULL);
    memory_region_add_subregion(system_mem, 0x08000000, flash_86);

    sram = g_new(MemoryRegion, 1);
    memory_region_init_ram(sram, NULL, "sram", 524288, NULL);
    memory_region_add_subregion(system_mem, 0x20000000, sram);

    alias = g_new(MemoryRegion, 1);
    memory_region_init_alias(alias, NULL, "Alias", flash_86, 0, 524288);
    memory_region_add_subregion(system_mem, 0x0, alias);

    system_clock_scale = NANOSECONDS_PER_SECOND/100000000;
    const uint32_t stackp_and_reset_vector[2] = {0x20000000, 0x00000001};
    cpu_physical_memory_write(0x00000000, stackp_and_reset_vector, sizeof(stackp_and_reset_vector));
    armv7m_load_kernel(ARM_CPU(first_cpu), NULL, 0);
}

static void machine_bnf_class_init(ObjectClass *oc, void *opaque)
{
    MachineClass *mc = MACHINE_CLASS(oc);

    mc->desc = "TODO: provide description for bnf";
    mc->init = init_bnf;
}

static TypeInfo machine_type_bnf = {
    .name = MACHINE_TYPE_NAME("bnf"),
    .parent = TYPE_MACHINE,
    .class_init = machine_bnf_class_init
};

static void bnf_register_types(void)
{
    type_register_static(&machine_type_bnf);
}

type_init(bnf_register_types)
