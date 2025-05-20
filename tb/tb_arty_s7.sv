module tb_arty_s7
(

);

localparam GPI_WIDTH = 8;
localparam GPO_WIDTH = 16;
localparam PWM_WIDTH = 12;
localparam CLOCK_FREQ = 50_000_000;
localparam BAUD_RATE = 115_200;

  ibex_demo_system #(
    .GpiWidth       (GPI_WIDTH),
    .GpoWidth       (GPO_WIDTH),
    .PwmWidth       (PWM_WIDTH),
    .ClockFrequency (CLOCK_FREQ),
    .BaudRate       (BAUD_RATE)
    // .RegFile        (ibex_pkg::RegFileFPGA),
    // .SRAMInitFile   (""),
  ) ibex_demo_system_inst (
    .clk_sys_i       (),
    .rst_sys_ni      (),

    .gp_i            (),
    .gp_o            (),
    .pwm_o           (),
    .uart_rx_i       (),
    .uart_tx_o       (),
    .spi_rx_i        (),
    .spi_tx_o        (),
    .spi_sck_o       (),

    .tck_i           (),    // JTAG test clock pad
    .tms_i           (),    // JTAG test mode select pad
    .trst_ni         (),  // JTAG test reset pad
    .td_i            (),     // JTAG test data input pad
    .td_o            ()      // JTAG test data output pad
  );

endmodule
