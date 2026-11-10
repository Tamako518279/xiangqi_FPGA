`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2026/10/31 15:21:06
// Design Name: 
// Module Name: timer_tick
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


module timer_tick(

    input  wire clk,
    input  wire rst,
    input enable,
    input wire clear,

    output reg  tick_1s
   
);

    reg [31:0] counter;
  
    

initial begin
    counter = 32'd0;
    tick_1s = 1'b0;
end
    always @(posedge clk or posedge rst) begin
       
        if (rst) begin
            counter <= 32'd0;
            tick_1s <= 1'b0;
        end else if (clear) begin
            counter <= 32'd0;
            tick_1s <= 1'b0;
        end else if (enable) begin
            if (counter == 32'd99999999) begin // Assuming a 100MHz clock for 1 second
                counter <= 32'd0;
                tick_1s <= 1'b1;
            end else begin
                counter <= counter + 1;
                tick_1s <= 1'b0;
            end
        end else if (!enable) begin
            counter <= counter;
            tick_1s <= 1'b0;
        end
    end
endmodule
