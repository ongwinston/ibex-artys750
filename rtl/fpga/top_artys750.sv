// Copyright lowRISC contributors.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

// This is the top level SystemVerilog file that connects the IO on the board to the Ibex Demo System.
module top_artys750 #(
  parameter SRAMInitFile = ""
) (
  // These inputs are defined in data/pins_artya7.xdc
  input         IO_CLK,
  input         IO_RST_N,
  input  [ 3:0] SW,
  input  [ 3:0] BTN,
  output [ 3:0] LED,
  // output [11:0] RGB_LED,
  output [2:0]  RGB_LED0,
  output [2:0]  RGB_LED1,
  input         UART_RX,
  output        UART_TX,
  input         SPI_RX,
  output        SPI_TX,
  output        SPI_SCK,
  input         JTAG_TCK,
  input         JTAG_TMS,
  input         JTAG_TRSTN,
  input         JTAG_TDI,
  output        JTAG_TDO,
  output        PMOD_JC
);

  localparam GPIO_WIDTH = 8;

  logic clk_sys, rst_sys_n;

  logic [3:0] DISP_CTRL; // Do nothing
  logic [11:0] RGB_LED;
  logic [GPIO_WIDTH-1:0] gpio_o;
  logic [23:0] led_shift_r = 'd0;

  assign RGB_LED0 = RGB_LED[2:0];
  assign RGB_LED1 = RGB_LED[4:2];

  assign LED = gpio_o[7:4];
  assign PMOD_JC = led_shift_r[23];


  // LED debug
  always_ff @( posedge clk_sys ) begin : g_dbg_led
    led_shift_r <= led_shift_r + 1'd1;
  end

  // Instantiating the Ibex Demo System.
  ibex_demo_system #(
    .GpiWidth     ( GPIO_WIDTH   ),
    .GpoWidth     ( GPIO_WIDTH   ),
    .PwmWidth     ( 12           ),
    .SRAMInitFile ( SRAMInitFile )
  ) u_ibex_demo_system (
    //input
    .clk_sys_i (clk_sys),
    .rst_sys_ni(rst_sys_n),
    .gp_i      ({SW, BTN}),
    .uart_rx_i (UART_RX),

    //output
    .gp_o     (gpio_o),
    .pwm_o    (RGB_LED),
    .uart_tx_o(UART_TX),

    .spi_rx_i (SPI_RX),
    .spi_tx_o (SPI_TX),
    .spi_sck_o(SPI_SCK),

    .trst_ni(JTAG_TRSTN),
    .tms_i  (JTAG_TMS),
    .tck_i  (JTAG_TCK),
    .td_i   (JTAG_TDI),
    .td_o   (JTAG_TDO)
  );

  // Generating the system clock and reset for the FPGA.
  clkgen_artys7 clkgen(
    .clk_in1    (IO_CLK),
    .resetn     (IO_RST_N),
    .clk_out_50 (clk_sys),
    // .rst_sys_n
    .locked     (rst_sys_n)
  );

endmodule
