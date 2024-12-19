//
// Wrapper file for Wishbone bus implementation by ZipCPU
// Converts array based bus addresses by Ibex Bus implementation
// into concatenated address bus used by wbxbar
//

module wbxbar_wrapper #(
  parameter int unsigned NrDevices    = 9,
  parameter int unsigned NrHosts      = 2,
  parameter int unsigned DataWidth    = 32,
  parameter int unsigned AddressWidth = 32,
  // Change array parameters to packed arrays
  parameter [(NrDevices*AddressWidth)-1:0] SLAVE_ADDR = {
      32'h1a110000, // DBG
      32'h80005000,  // WishboneM
      32'h20000,     // SimCtrl
      32'h80004000,  // SPI
      32'h80002000,  // Timer
      32'h80001000,  // UART
      32'h80003000,  // PWM
      32'h80000000,  // GPIO
      32'h00100000   // RAM
  },
  parameter [(NrDevices*AddressWidth)-1:0] SLAVE_MASK = {
      32'hFFFF_0000 , // DBG
      32'hFFFF_F000,  // WishboneM
      32'hFFFF_F000,  // SimCtrl
      32'hFFFF_F000,  // SPI
      32'hFFFF_F000,  // Timer
      32'hFFFF_F000,  // UART
      32'hFFFF_F000,  // PWM
      32'hFFFF_F000,  // GPIO
      32'hFFF0_0000   // RAM
  }
) (
  input                           clk_i,
  input                           rst_ni,

  // Hosts (masters)
  input                           host_req_i    [NrHosts],
  output logic                    host_gnt_o    [NrHosts],

  input        [AddressWidth-1:0] host_addr_i   [NrHosts],
  input                           host_we_i     [NrHosts],
  input        [ DataWidth/8-1:0] host_be_i     [NrHosts],
  input        [   DataWidth-1:0] host_wdata_i  [NrHosts],
  output logic                    host_rvalid_o [NrHosts],
  output logic [   DataWidth-1:0] host_rdata_o  [NrHosts],
  output logic                    host_err_o    [NrHosts],

  // Devices (slaves)
  output logic                    device_req_o    [NrDevices],
  output logic [AddressWidth-1:0] device_addr_o   [NrDevices],
  output logic                    device_we_o     [NrDevices],
  output logic [ DataWidth/8-1:0] device_be_o     [NrDevices],
  output logic [   DataWidth-1:0] device_wdata_o  [NrDevices],
  input                           device_rvalid_i [NrDevices],
  input        [   DataWidth-1:0] device_rdata_i  [NrDevices],
  input                           device_err_i    [NrDevices]
);


////////////////////////////////////////////////////////////
// Wishbone Ibex Bridge Master
////////////////////////////////////////////////////////////
  
//   // Wb to Ibex
//   logic [31:0] wb_data;
//   logic wb_data_intg, wb_data_err;

  
//   logic [31:0] wb_m_data;
//   logic wb_m_data_intg, wb_m_data_err;
//   logic wb_m_cyc, wb_m_stb, wb_m_we;
//   logic [3:0] wb_m_sel;
//   logic [31:0] wb_m_addr;

//   logic wb_xbar_stall, wb_xbar_ack, wb_xbar_err;
//   logic [31:0] wb_xbar_data;


//   wb_bridge_master #(
//    .DATA_WIDTH(32),
//    .ADDR_WIDTH(32)
//   ) wb_bridge_master_inst (
//     .clk_i                  (clk_sys_i),
//     .reset_i                (!rst_sys_ni),

//     // To From Ibex Core
//     .data_req_i             (host_req[CoreD]),
//     .data_gnt_o             (host_gnt[CoreD]),

//     .data_we_i              (host_we[CoreD]),
//     .data_be_i              (host_be[CoreD]),
//     .data_addr_i            (host_addr[CoreD]),
//     .data_wdata_i           (host_wdata[CoreD]),
//     .data_wdata_intg_i      (1'bz),

//     .data_rdata_o           (wb_data),
//     .data_rdata_intg_o      (wb_data_intg),
//     .data_rvalid_o          (host_rvalid[CoreD]),
//     .data_err_o             (wb_data_err),

//     // To Wishbone Xbar Requests
//     .mcyc_o                 (wb_m_cyc),
//     .mstb_o                 (wb_m_stb),
//     .mwe_o                  (wb_m_we),
//     .maddr_o                (wb_m_addr),
//     .mdata_o                (wb_m_data),
//     .msel_o                 (wb_m_sel),

//     // Wishbone Xbar Response
//     .mstall_i               (wb_xbar_stall),
//     .mack_i                 (wb_xbar_ack),
//     .mdata_i                (wb_xbar_data),
//     .merr_i                 (wb_xbar_err)

// );


////////////////////////////////////////////////////////////
// Wishbone Xbar
////////////////////////////////////////////////////////////


  logic [NrHosts-1 : 0]                wb_m_cyc, wb_m_stb, wb_m_we;
  logic [(NrHosts*AddressWidth)-1 : 0] wb_m_addr;
  logic [(NrHosts*DataWidth)-1 : 0]    wb_m_data;
  logic [NrHosts*(DataWidth/8)-1 : 0]  wb_m_sel;

  logic [NrHosts-1:0]                  wb_xbar_stall;
  logic [NrHosts-1:0]                  wb_xbar_ack;
  logic [(NrHosts*DataWidth)-1 : 0]    wb_xbar_data;
  logic [NrHosts-1:0]                  wb_xbar_err;


  logic [NrDevices-1 : 0]                 scyc;
  logic [NrDevices-1 : 0]                 sstb;
  logic [NrDevices-1 : 0]                 swe;
  logic [(NrDevices*AddressWidth)-1 : 0]  saddr;
  logic [(NrDevices*DataWidth)-1 : 0]     sdata;
  logic [(NrDevices*(DataWidth/8))-1 : 0] ssel;

  // Slave Responses
  // Create a stall signal
  // error signal
  logic [NrDevices-1 : 0]                 sDevice_valid;
  logic [(NrDevices*DataWidth)-1 : 0]     sDevice_rdata;
  logic [NrDevices-1 : 0]                 sDevice_err;
  logic [NrDevices-1:0]                   sDevice_stall;

  logic [NrHosts-1:0]                     request_in;

  always_ff @( posedge clk_i ) begin : request_flop
    if(!rst_ni) begin
      request_in <= 'd0;
    end else begin
      if(host_req_i[0]) begin
        request_in[0] <= 1'd1;
      end
      if(request_in[0] & wb_xbar_ack[0]) begin
        request_in[0]<= 1'd0;
      end
      if(host_req_i[1]) begin
        request_in[1] <= 1'd1;
      end
      if(request_in[1] & wb_xbar_ack[1]) begin
        request_in[1]<= 1'd0;
      end

    end
  end

  genvar IdxHost;
  // NrHosts:
  // - CoreD
  // - DbgHost
  generate
    for(IdxHost=0; IdxHost<NrHosts; IdxHost=IdxHost+1) begin: gen_flatten_hosts
      assign wb_m_cyc[IdxHost +: 1] = request_in[IdxHost];
      assign wb_m_stb[IdxHost +: 1] = request_in[IdxHost];
      assign wb_m_we[IdxHost +: 1] = host_we_i[IdxHost];
      assign wb_m_addr[(IdxHost*AddressWidth) +: AddressWidth] = host_addr_i[IdxHost];
      assign wb_m_data[(IdxHost*DataWidth) +: DataWidth] = host_wdata_i[IdxHost];
      assign wb_m_sel[IdxHost*(DataWidth/8) +: (DataWidth/8)] = host_be_i[IdxHost];

      // Wb Slave -> Host core
      assign host_rvalid_o[IdxHost] = wb_xbar_ack[IdxHost];
      assign host_rdata_o[IdxHost] = wb_xbar_data[(IdxHost*DataWidth) +: DataWidth];
      assign host_err_o[IdxHost] = wb_xbar_err[IdxHost];

    end
  endgenerate

  // assign host_gnt_o[0] = sDevice_valid[0] & !wb_xbar_stall[0];// TODO: Arbitrate the gnt signal to either Core or Dbg
  assign host_gnt_o[0] = scyc[0] & sstb[0] & !sDevice_stall[0] & host_req_i[0];

  // Register to keep track of transactions completed
  logic transaction_in_prog;
  always_ff @( posedge clk_i ) begin
    if(!rst_ni) begin
      transaction_in_prog <= 'd0;
    end else begin
      if(!scyc[0] && transaction_in_prog) begin
        transaction_in_prog <= 1'd0;
      end else begin
        if(scyc[0] & !transaction_in_prog) transaction_in_prog <= 1'd1;
      end
    end
    
  end

  // Generate Xbar to Slave interface
  genvar  IdxSlaves;
  generate
    for(IdxSlaves = 0; IdxSlaves < NrDevices; IdxSlaves = IdxSlaves + 1) begin : gen_split_slaves
      assign device_req_o[IdxSlaves] = scyc[IdxSlaves] & sstb[IdxSlaves] && !transaction_in_prog;
      assign device_addr_o[IdxSlaves] = saddr[(IdxSlaves*AddressWidth) +: AddressWidth];
      assign device_we_o[IdxSlaves] = swe[IdxSlaves];
      assign device_be_o[IdxSlaves] = ssel[IdxSlaves*(DataWidth/8) +: (DataWidth/8)];
      assign device_wdata_o[IdxSlaves] = sdata[(IdxSlaves*DataWidth) +: DataWidth];

      // SlaveData
      assign sDevice_valid[IdxSlaves] = device_rvalid_i[IdxSlaves];
      assign sDevice_rdata[IdxSlaves*DataWidth +: DataWidth] = device_rdata_i[IdxSlaves];
      assign sDevice_err[IdxSlaves] = device_err_i[IdxSlaves];
    end
  endgenerate

  wbxbar #(
    .NM(NrHosts),
    .NS(NrDevices),
    .AW(AddressWidth),
    .DW(DataWidth),
    .SLAVE_ADDR(SLAVE_ADDR),
    .SLAVE_MASK(SLAVE_MASK)
  ) u_xbar (
    .i_clk               (clk_i),
    .i_reset             (!rst_ni),

    // Inputs from Masters
    .i_mcyc              (wb_m_cyc),
    .i_mstb              (wb_m_stb),
    .i_mwe               (wb_m_we),
    .i_maddr             (wb_m_addr),
    .i_mdata             (wb_m_data),
    .i_msel              (wb_m_sel),

    // Output to Master Slave Response
    .o_mstall            (wb_xbar_stall),
    .o_mack              (wb_xbar_ack),
    .o_mdata             (wb_xbar_data),
    .o_merr              (wb_xbar_err),

    // WB Requests to Slaves
    .o_scyc               (scyc),
    .o_sstb               (sstb),
    .o_swe                (swe),
    .o_saddr              (saddr),
    .o_sdata              (sdata),
    .o_ssel               (ssel),

     // Responses from Slave
    .i_sstall             (sDevice_stall),
    .i_sack               (sDevice_valid),
    .i_sdata              (sDevice_rdata),
    .i_serr               (sDevice_err)
  );


endmodule