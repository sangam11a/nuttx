static void stm32_dumpnvic(const char *msg, int irq)
{
  stm32_gpiowrite(GPIO_WD_WDI, true);


  irqstate_t flags;
  uint32_t reg_values[32]; // Array to store the register values if needed.

  stm32_gpiowrite(GPIO_WD_WDI, true);

  flags = enter_critical_section();
  stm32_gpiowrite(GPIO_WD_WDI, false);

  // Retrieve NVIC register values directly
  reg_values[0] = getreg32(NVIC_INTCTRL);
  stm32_gpiowrite(GPIO_WD_WDI, true);

  reg_values[1] = getreg32(NVIC_VECTAB);
  stm32_gpiowrite(GPIO_WD_WDI, false);
  #if 0
  irqinfo("  SYSH ENABLE MEMFAULT: %08x BUSFAULT: %08x USGFAULT: %08x "
          "SYSTICK: %08x\n",
          getreg32(NVIC_SYSHCON_MEMFAULTENA),
          getreg32(NVIC_SYSHCON_BUSFAULTENA),
          getreg32(NVIC_SYSHCON_USGFAULTENA),
          getreg32(NVIC_SYSTICK_CTRL_ENABLE));
  #endif

  reg_values[2] = getreg32(NVIC_IRQ0_31_ENABLE);
  stm32_gpiowrite(GPIO_WD_WDI, true);

  reg_values[3] = getreg32(NVIC_IRQ32_63_ENABLE);
  stm32_gpiowrite(GPIO_WD_WDI, false);

  reg_values[4] = getreg32(NVIC_IRQ64_95_ENABLE);
  stm32_gpiowrite(GPIO_WD_WDI, true);

  reg_values[5] = getreg32(NVIC_SYSH4_7_PRIORITY);
  stm32_gpiowrite(GPIO_WD_WDI, false);

  reg_values[6] = getreg32(NVIC_SYSH8_11_PRIORITY);
  stm32_gpiowrite(GPIO_WD_WDI, true);

  reg_values[7] = getreg32(NVIC_SYSH12_15_PRIORITY);
  stm32_gpiowrite(GPIO_WD_WDI, false);

  // Iterate to retrieve all IRQ priorities
  for (int i = 0; i < 16; ++i)
  {
    reg_values[8 + i] = getreg32(NVIC_IRQ0_3_PRIORITY + (i * 4));
    stm32_gpiowrite(GPIO_WD_WDI, (i % 2) == 0);
  }

  stm32_gpiowrite(GPIO_WD_WDI, true);
  leave_critical_section(flags);
}