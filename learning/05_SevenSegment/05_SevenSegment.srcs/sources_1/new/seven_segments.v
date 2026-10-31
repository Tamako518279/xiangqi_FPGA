`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2026/10/23 22:10:44
// Design Name: 
// Module Name: seven_segments
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


module seven_segments(
   input clk,
   input rst,
   input key,
   output reg [7:0] seg,
   output wire [3:0] digit_en
    );
    wire stable_key;
    wire pulse;
    wire rst_active;
assign rst_active = ~rst;
    reg [3:0] count = 4'b0000;
    always @(posedge clk or posedge rst_active) begin
        if (rst_active) begin
            count <= 4'b0000;
        end else if (pulse) begin
            count <= count + 1;
        end
    end
   Debounce key_debounce_inst(
        .clk(clk),
        .rst(rst_active),
        .key(key),
        .stable_key(stable_key)
    );
   Edge_test edge_test_inst(
        .clk(clk),
        .rst(rst_active),
        .stable_key(stable_key),
        .pulse(pulse)
    );
    always @(*) begin
    case (count)
        4'h0: seg = 8'b11111100;
        4'h1: seg = 8'b01100000;
        4'h2: seg = 8'b11011010;
        4'h3: seg = 8'b11110010;
        4'h4: seg = 8'b01100110;
        4'h5: seg = 8'b10110110;
        4'h6: seg = 8'b10111110;
        4'h7: seg = 8'b11100000;
        4'h8: seg = 8'b11111110;
        4'h9: seg = 8'b11110110;
        4'hA: seg = 8'b11101110;
        4'hB: seg = 8'b00111110; // 显示 b
        4'hC: seg = 8'b10011100;
        4'hD: seg = 8'b01111010; // 显示 d
        4'hE: seg = 8'b10011110;
        4'hF: seg = 8'b10001110;
        default: seg = 8'b00000000;
    endcase
end
    assign digit_en = 4'b0001; // Enable the first digit (active high)
endmodule
