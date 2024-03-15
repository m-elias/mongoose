#pragma once

#if MG_ENABLE_TCPIP && defined(MG_ENABLE_DRIVER_STM32H) && \
    MG_ENABLE_DRIVER_STM32H

struct mg_tcpip_driver_stm32h_data {
  // MDC clock divider. MDC clock is derived from HCLK, must not exceed 2.5MHz
  //    HCLK range    DIVIDER    mdc_cr VALUE
  //    -------------------------------------
  //                                -1  <-- tell driver to guess the value
  //    60-100 MHz    HCLK/42        0
  //    100-150 MHz   HCLK/62        1
  //    20-35 MHz     HCLK/16        2
  //    35-60 MHz     HCLK/26        3
  //    150-250 MHz   HCLK/102       4  <-- value for Nucleo-H* on max speed
  //    driven by HSI 250-300 MHz   HCLK/124       5  <-- value for Nucleo-H* on
  //    max speed driven by CSI 110, 111 Reserved
  int mdc_cr;  // Valid values: -1, 0, 1, 2, 3, 4, 5

  uint8_t phy_addr;  // PHY address
  uint8_t phy_conf;  // PHY config
};

#ifndef MG_MAC_ADDRESS
#define MG_MAC_ADDRESS MG_MAC_ADDRESS_RANDOM
#endif

#ifndef MG_TCPIP_PHY_ADDR
#define MG_TCPIP_PHY_ADDR 0
#endif

#ifndef MG_DRIVER_MDC_CR
#define MG_DRIVER_MDC_CR 4
#endif

#define MG_TCPIP_DRIVER_DATA                                \
  static struct mg_tcpip_driver_stm32h_data driver_data = { \
      .mdc_cr = MG_DRIVER_MDC_CR,                           \
      .phy_addr = MG_TCPIP_PHY_ADDR,                        \
  };

#define MG_TCPIP_DRIVER_CODE &mg_tcpip_driver_stm32h
#define MG_TCPIP_DRIVER_NAME "stm32h"

#endif
