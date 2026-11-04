`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2026/10/23 00:23:31
// Design Name: 
// Module Name: hex7seg
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


module hex7seg(
 input wire[3:0] hex,
 output reg [7:0] seg
    );

// 对应当前 XDC：{a, b, c, d, e, f, g, dp}
// 1 点亮，0 熄灭
always @(*) begin
    case (hex)
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



endmodule
