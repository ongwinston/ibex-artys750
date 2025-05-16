
// 20ns clock - 50MHz
`define HALF_CLK_PERIOD 10ns

`timescale 1ns/1ps

module tb_wbxbar_wrapper ();

  localparam logic [31:0] MEM_SIZE      = 64 * 2 *  1024; // 64 KiB + 64 KiB = 128KiB
  localparam logic [31:0] MEM_START     = 32'h00100000;
  localparam logic [31:0] MEM_MASK      = ~(MEM_SIZE-1);

  localparam logic [31:0] GPIO_SIZE     =  4 * 1024; //  4 KiB
  localparam logic [31:0] GPIO_START    = 32'h80000000;
  localparam logic [31:0] GPIO_MASK     = ~(GPIO_SIZE-1);

  localparam logic [31:0] DEBUG_SIZE    = 64 * 1024; // 64 KiB
  localparam logic [31:0] DEBUG_START   = 32'h1a110000;
  localparam logic [31:0] DEBUG_MASK    = ~(DEBUG_SIZE-1);

  localparam logic [31:0] UART_SIZE     =  4 * 1024; //  4 KiB
  localparam logic [31:0] UART_START    = 32'h80001000;
  localparam logic [31:0] UART_MASK     = ~(UART_SIZE-1);

  localparam logic [31:0] TIMER_SIZE    =  4 * 1024; //  4 KiB
  localparam logic [31:0] TIMER_START   = 32'h80002000;
  localparam logic [31:0] TIMER_MASK    = ~(TIMER_SIZE-1);

  localparam logic [31:0] PWM_SIZE      =  4 * 1024; //  4 KiB
  localparam logic [31:0] PWM_START     = 32'h80003000;
  localparam logic [31:0] PWM_MASK      = ~(PWM_SIZE-1);
  localparam int PwmCtrSize = 8;

  parameter logic [31:0] SPI_SIZE       =  1 * 1024; //  1 KiB
  parameter logic [31:0] SPI_START      = 32'h80004000;
  parameter logic [31:0] SPI_MASK       = ~(SPI_SIZE-1);

  parameter logic [31:0] SIM_CTRL_SIZE  =  1 * 1024; //  1 KiB
  parameter logic [31:0] SIM_CTRL_START = 32'h20000;
  parameter logic [31:0] SIM_CTRL_MASK  = ~(SIM_CTRL_SIZE-1);

  parameter logic [31:0] WISHBONEM_SIZE  =  4 * 1024; //  4 KiB
  parameter logic [31:0] WISHBONEM_START = 32'h80005000;
  parameter logic [31:0] WISHBONEM_MASK  = ~(WISHBONEM_SIZE-1);

  localparam int NrDevices = 9;
  localparam int NrHosts   = 2;


  // Host signals.
  logic        host_req      [NrHosts];
  logic        host_gnt      [NrHosts];
  logic [31:0] host_addr     [NrHosts];
  logic        host_we       [NrHosts];
  logic [ 3:0] host_be       [NrHosts];
  logic [31:0] host_wdata    [NrHosts];
  logic        host_rvalid   [NrHosts];
  logic [31:0] host_rdata    [NrHosts];
  logic        host_err      [NrHosts];

  // Device signals.
  logic        device_req    [NrDevices];
  logic [31:0] device_addr   [NrDevices];
  logic        device_we     [NrDevices];
  logic [ 3:0] device_be     [NrDevices];
  logic [31:0] device_wdata  [NrDevices];
  logic        device_rvalid [NrDevices];
  logic [31:0] device_rdata  [NrDevices];
  logic        device_err    [NrDevices];

  logic clk = 1'b0;
  logic reset_n = 1'b0;

  //----------------------------------
  // Clock and Reset driving logic
  //----------------------------------

  initial begin
    forever begin
      #`HALF_CLK_PERIOD clk = ~clk;
    end
  end

  task hw_reset();
    reset_n = 1'b1;
    @ (negedge clk);
    reset_n <= 1'b0;
    @ (negedge clk);
    @ (negedge clk);
    reset_n <= 1'b1;
  endtask: hw_reset


  initial begin
    // #`HALF_CLK_PERIOD reset_n = 1'b1;
    hw_reset;
  end

  //-----------------------
  logic start_test;

  initial begin
    start_test = 1'b0;
    zero_host_ports(0);
    zero_host_ports(1);
    zero_device_ports(0);

    #100ns start_test = 1'b1;

    @(posedge clk);
    host_read();
    @ (posedge clk);

    zero_host_ports(1);

    @ (posedge clk);
    @ (negedge clk);
  end

  initial begin
    #1000ns $finish();
  end

  // Need to create these 1-D signals because Icarus doesnt dump them otherwise
  generate
    genvar host_index;
    for (host_index = 0; host_index < NrHosts; host_index = host_index + 1) begin : g_host_index_dbg
      logic        host_req_dbg;
      logic        host_gnt_dbg;
      logic [31:0] host_addr_dbg;
      logic        host_we_dbg;
      logic [ 3:0] host_be_dbg;
      logic [31:0] host_wdata_dbg;
      logic        host_rvalid_dbg;
      logic [31:0] host_rdata_dbg;
      logic        host_err_dbg;

      assign host_req_dbg = host_req[host_index];
      assign host_gnt_dbg = host_gnt[host_index];
      assign host_addr_dbg = host_addr[host_index];
      assign host_we_dbg = host_we[host_index];
      assign host_be_dbg = host_be[host_index];
      assign host_wdata_dbg = host_wdata[host_index];
      assign host_rvalid_dbg = host_rvalid[host_index];
      assign host_rdata_dbg = host_rdata[host_index];
      assign host_err_dbg = host_err[host_index];
    end
  endgenerate


  // Flatten devices ports for Icarus to dump
  generate
    genvar device_index;
    for(device_index = 0; device_index < NrDevices; device_index = device_index + 1) begin : g_device_index_dbg
      logic        device_req_dbg;
      logic [31:0] device_addr_dbg;
      logic        device_we_dbg;
      logic [ 3:0] device_be_dbg;
      logic [31:0] device_wdata_dbg;
      logic        device_rvalid_dbg;
      logic [31:0] device_rdata_dbg;
      logic        device_err_dbg;

      assign device_req_dbg = device_req[device_index];
      assign device_addr_dbg = device_addr[device_index];
      assign device_we_dbg = device_we[device_index];
      assign device_be_dbg = device_be[device_index];
      assign device_wdata_dbg = device_wdata[device_index];
      assign device_rvalid_dbg = device_rvalid[device_index];
      assign device_rdata_dbg = device_rdata[device_index];
      assign device_err_dbg = device_err[device_index];

    end
  endgenerate


  //----------------------------
  // Dut Driving logic
  //---------------------------

  //--------------------
  // Host req transaction
  //--------------------
  task host_read();
    host_req[1] <= 1'b1;
    host_addr[1] <= MEM_START;
    host_we[1] <= 1'b0;
    host_be[1] <= 4'b1111;
    host_wdata[1] <= 32'h0badbeef;
  endtask;

  task zero_host_ports(int index);
    host_req[index] <= 1'b0;
    host_addr[index] <= 'd0;
    host_we[index] <= 'd0;
    host_be[index] <= 'd0;
    host_wdata[index] <= 'd0;
  endtask;

  task zero_device_ports(int index);
    device_rvalid[index] <= 1'b1;
    device_rdata[index] <= 32'd0;
    device_err[index] <= 1'b0;
  endtask;

  //-----------------------
  // wbxbar_wrapper inst
  //-----------------------
  wbxbar_wrapper #(
    .NrDevices    (9),
    .NrHosts      (2),
    .DataWidth    (32),
    .AddressWidth (32),
    .SLAVE_ADDR   ({
        DEBUG_START,      // Device 8
        WISHBONEM_START,  // Device 7
        SIM_CTRL_START,   // Device 6
        SPI_START,        // Device 5
        TIMER_START,      // Device 4
        UART_START,       // Device 3
        PWM_START,        // Device 2
        GPIO_START,       // Device 1
        MEM_START         // Device 0
    }),
    .SLAVE_MASK   ({
        DEBUG_MASK,       // Device 8
        WISHBONEM_MASK,   // Device 7
        SIM_CTRL_MASK,    // Device 6
        SPI_MASK,         // Device 5
        TIMER_MASK,       // Device 4
        UART_MASK,        // Device 3
        PWM_MASK,         // Device 2
        GPIO_MASK,        // Device 1
        MEM_MASK          // Device 0
    })
)
  wbxbar_wrapper_inst(
    .clk_i          (clk),
    .rst_ni         (reset_n),

    .host_req_i     (host_req     ),
    .host_gnt_o     (host_gnt     ),
    .host_addr_i    (host_addr    ),
    .host_we_i      (host_we      ),
    .host_be_i      (host_be      ),
    .host_wdata_i   (host_wdata   ),
    .host_rvalid_o  (host_rvalid  ),
    .host_rdata_o   (host_rdata   ),
    .host_err_o     (host_err     ),

    .device_req_o   (device_req   ),
    .device_addr_o  (device_addr  ),
    .device_we_o    (device_we    ),
    .device_be_o    (device_be    ),
    .device_wdata_o (device_wdata ),
    .device_rvalid_i(device_rvalid),
    .device_rdata_i (device_rdata ),
    .device_err_i   (device_err   )
   );


  //---------------------
  // Waveform dump
  //---------------------
  initial begin
    $dumpfile("dump.vcd");
    $dumpvars(0, tb_wbxbar_wrapper);
  end

endmodule
