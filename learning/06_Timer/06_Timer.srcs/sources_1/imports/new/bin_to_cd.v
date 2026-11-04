`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2026/10/31 14:24:09
// Design Name: 
// Module Name: bin_to_bcd
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module bin_to_bcd( 
  input wire [15:0] bin,
  output reg [15:0] bcd
    );
  reg [31:0] temp;
  integer i;
  always @(*) begin
    temp = 0;
    temp[15:0] = bin;
    for (i = 0; i < 16; i = i + 1) begin
      if (temp[19:16] >= 5)
        temp[19:16] = temp[19:16] + 3;
      if (temp[23:20] >= 5)
        temp[23:20] = temp[23:20] + 3;
      if (temp[27:24] >= 5)
        temp[27:24] = temp[27:24] + 3;
      if (temp[31:28] >= 5)
        temp[31:28] = temp[31:28] + 3;
      temp = temp << 1;
    end
    bcd = temp[31:16];
  end
endmodule
