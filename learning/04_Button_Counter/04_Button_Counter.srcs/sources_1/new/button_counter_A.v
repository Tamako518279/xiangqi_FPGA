`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2026/10/14 21:26:45
// Design Name: 
// Module Name: button_counter_A
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


module button_counter_A(
  input clk,
  output reg [3:0] LED,
  input key
    );
  reg [3:0] count = 4'b0000;
  reg key_pre = 0;
  always @(posedge clk) begin
    if(key && !key_pre) begin
        count <= count + 1;
    end
    key_pre <= key;
    LED <= count;
  end
endmodule
