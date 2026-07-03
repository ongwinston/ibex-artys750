// Math module

/*
  parameter logic [31:0] MATH_MODULE_SIZE  =  4 * 1024; //  4 KiB
  parameter logic [31:0] MATH_MODULE_START = 32'h80005000;
  parameter logic [31:0] MATH_MODULE_MASK  = ~(MATH_MODULE_SIZE-1);
*/


  /* verilator lint_off UNUSEDSIGNAL */

module math_module #(
  parameter int unsigned AddrWidth      = 32,
  parameter int unsigned DataWidth      = 32

) (
  input logic clk_i,
  input logic rst_ni,

  // Bus Interface
  input  logic                 device_req_i,
  input  logic [AddrWidth-1:0] device_addr_i,
  input  logic                 device_we_i,
  input  logic [3:0]           device_be_i,
  input  logic [DataWidth-1:0] device_wdata_i,
  output logic                 device_rvalid_o,
  output logic [DataWidth-1:0] device_rdata_o
);

  // Math Config map
  typedef enum logic [31:0] {
    mult,
    sqrt
  } math_op_e;

  localparam logic [31:0] OPERATION_REG_ADDR = 32'h80005000;
  localparam logic [31:0] DATA_A_ADDR = 32'h80005004;
  localparam logic [31:0] DATA_B_ADDR = 32'h80005008;

  logic signed [31:0] data_a;
  logic signed [31:0] data_b;
  math_op_e    math_operation;

  logic valid_req_in;
  logic signed [31:0] math_op_out;

  /* verilator lint_on UNUSEDSIGNAL */

  always_ff @( posedge clk_i ) begin
    if(!rst_ni) begin
      data_a <= 32'd0;
      data_b <= 32'd0;
      math_operation <= mult;
      valid_req_in <= 1'b0;
    end else begin
      if(device_req_i & device_we_i) begin
        if(device_addr_i == DATA_A_ADDR) begin
          data_a <= device_wdata_i;
        end else if(device_addr_i == DATA_B_ADDR) begin
          data_b <= device_wdata_i;
        end else if(device_addr_i == OPERATION_REG_ADDR) begin
          math_operation <= math_op_e'(device_wdata_i);
        end
      end

      if(device_req_i) begin
        valid_req_in <= 1'b1;
      end else begin
        valid_req_in <= 1'b0;
      end
    end
  end


  always_comb begin
    math_op_out = 'd0;
    unique case(math_operation)
      mult: begin
        math_op_out = data_a * data_b;
      end
      sqrt: begin
        math_op_out = data_a; // TODO
      end
    endcase
  end

  assign device_rvalid_o = valid_req_in;
  assign device_rdata_o = math_op_out;


endmodule
