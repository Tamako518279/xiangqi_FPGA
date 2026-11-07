`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2026/11/07 21:06:56
// Design Name: 
// Module Name: uart_echo_top
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


module uart_echo_top(
  input wire clk,
  input wire rst,
  input wire uart_rx,

  output wire uart_tx,
  output wire [7:0] seg,
  output wire [3:0] digit_en,
  output wire overflow_LED
    );
    
    wire [7:0] rx_data;
    wire tx_busy;
    wire tx_start;
    wire rx_valid;
    wire rst_active = ~rst;
    wire [15:0] display_data = {8'b0, rx_data};
    wire [3:0] current_hex;
    wire send_request;
    reg [7:0] pending_data;
    reg pending_valid;
    reg overflow;

    assign send_request = pending_valid && !tx_busy;
    assign tx_start = send_request;
    assign tx_data = pending_data;
    assign overflow_LED = overflow;

    always @(posedge clk or negedge rst) begin
         if(!rst) begin
            pending_data <= 8'b0;
            pending_valid <= 1'b0;
            overflow <= 1'b0;
         end else begin
            if(rx_valid) begin
                if(!pending_valid || tx_start) begin //缓冲区为空或者这一拍数据被取走
                    pending_data <= rx_data;
                    pending_valid <= 1'b1;
                end else begin
                    overflow <= 1'b1;
                end
            end else if(tx_start) begin
                pending_valid <= 1'b0;
            end
        end
   end

    uart_rx uart_rx_inst (
        .clk(clk),
        .rst(rst_active),
        .uart_rx(uart_rx),
        .rx_data(rx_data),
        .rx_valid(rx_valid)
    );

    uart_tx uart_tx_inst (
        .clk(clk),
        .rst(rst_active),
        .tx_start(tx_start),
        .tx_data(pending_data),
        .uart_tx(uart_tx),
        .tx_busy(tx_busy)
        
    );

    sevenseg_scan sevenseg_scan_inst (
        .clk(clk),
        .display_data(display_data),
        .digit_en(digit_en),
        .current_hex(current_hex)
    );

    hex7seg hex7seg_inst (
        .hex(current_hex),
        .seg(seg)
    );

endmodule
