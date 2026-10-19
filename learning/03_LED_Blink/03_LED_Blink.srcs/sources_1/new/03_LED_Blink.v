`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2026/10/14 18:05:38
// Design Name: 
// Module Name: 03_LED_Blink
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


module LED_Blink(

input clk,
output reg LED_State
    );

 reg [26:0] count = 0;
 always @(posedge clk) begin
   if (count == 27'd100000000 - 1) begin
        count <= 0;
        LED_State <= ~LED_State;
   end
   else begin
        count <= count + 1;
   end


 end
endmodule
