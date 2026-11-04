`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2026/10/15 00:36:10
// Design Name: 
// Module Name: Edge_test
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


module Edge_test(
    input clk,
    input rst,
    input stable_key,
   output reg pulse
    );
   reg key_pre = 0;
   always @(posedge clk) begin
    if(rst) begin
        pulse <= 0;
        key_pre <= 0;
      end
    else  begin
       key_pre <= stable_key;
      if(stable_key && !key_pre) 
       pulse <= 1;
      else 
        pulse <= 0;
    end
 end
       
   
endmodule
