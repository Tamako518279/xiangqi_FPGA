`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2026/10/16 23:09:32
// Design Name: 
// Module Name: button_counter_B
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


module button_counter_B(
  input clk,
  input rst,
  input key,
  output [3:0] LED
    );

    wire stable_key;
    wire pulse;
    wire rst_active;
    assign rst_active = ~rst;
    reg [3:0] count = 4'b0000;
    Debounce u_deboune(

     .clk(clk),
     .rst(rst_active),
     .key(key),
     .stable_key(stable_key)
    );

    Edge_test u_Edge_test(
        .clk(clk),
        .rst(rst_active),
        .stable_key(stable_key),
        .pulse(pulse)
    );


    always @(posedge clk or posedge rst_active) begin
        if (rst_active) begin
            count <= 4'b0000;
     end
         else if (pulse) begin
            count <= count + 1;
     end
end


    assign LED = count;

endmodule
