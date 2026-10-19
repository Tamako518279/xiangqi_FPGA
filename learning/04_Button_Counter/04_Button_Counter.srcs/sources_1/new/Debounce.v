`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2026/10/14 23:54:35
// Design Name: 
// Module Name: Debounce
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


module Debounce(
    input clk,
    input rst,
    input key,
    output reg stable_key

    );
   reg[19:0] counter = 20'd0;
   always @(posedge clk or posedge rst ) begin
       if(rst) begin
           counter <= 20'd0;
           stable_key <= 0;
       end
       else if(key == stable_key) begin
       counter <= 20'd0;
       end
       else if(counter == 20'd999_999) begin
           stable_key <= key;
           counter <= 20'd0;
       end
       else begin
           counter <= counter + 1'b1;
        end
    end
  
endmodule
