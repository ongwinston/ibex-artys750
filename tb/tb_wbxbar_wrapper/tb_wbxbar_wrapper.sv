`timescale 1ns/1ps

module tb_wbxbar_wrapper ();
  

  //---------------------
  // Waveform dump
  //---------------------
  initial begin
    $dumpfile("dump.vcd");
    $dumpvars(0);
  end


  logic clk;
  logic reset_n;
  
  initial begin
    clk = 1'b1;
    reset_n = 1'b0;
    
    
    forever begin
      // #10ns; // 100MHz
      #10ns clk = ~clk;
    end
  end


  initial begin
    #10ns reset_n = 1'b1;
    #500ns $finish();
  end


  //-----------------------
  // wbxbar_wrapper inst
  //-----------------------
  wbxbar_wrapper #(
    .NrDevices    (8),
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
    .clk_i           (clk),
    .rst_ni          (reset_n),
    .host_req_i      (),
    .host_gnt_o      (),
    .host_addr_i     (),
    .host_we_i       (),
    .host_be_i       (),
    .host_wdata_i    (),
    .host_rvalid_o   (),
    .host_rdata_o    (),
    .host_err_o      (),
    .device_req_o    (),
    .device_addr_o   (),
    .device_we_o     (),
    .device_be_o     (),
    .device_wdata_o  (),
    .device_rvalid_i (),
    .device_rdata_i  (),
    .device_err_i    ()
   );

endmodule
