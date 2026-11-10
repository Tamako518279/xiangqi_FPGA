`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2026/11/08 23:00:58
// Design Name: 
// Module Name: uart_timer_top
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


module uart_timer_top(
    input wire clk,
    input wire rst,
    input wire uart_rx,

    output wire [7:0] seg,
    output wire [3:0] digit_en,
    output wire uart_tx,
    output reg response_overflow
    );

    wire tick_1s;
    wire [3:0] current_hex;
    wire running;
    wire [7:0] rx_data;
    wire rx_valid;
    wire [15:0] display_data;
    wire serial_start_pause_pulse;
    wire rst_active = ~rst;
    wire load_inital = rx_valid && (rx_data == 8'h02);
    wire clear = rx_valid && (rx_data == 8'h02); 
    wire tx_start;
    wire tx_busy;
    wire tx_done;
    wire [1:0] status_data;
    wire [7:0] status_byte = {6'b000000, status_data};
    wire query_req = rx_valid && (rx_data == 8'h03); // 查询状态请求
    reg [7:0] pending_data;
    reg pending_valid;
   
    assign serial_start_pause_pulse = rx_valid && (rx_data == 8'h01); 
    assign tx_start = pending_valid && !tx_busy;
   

always @(posedge clk or posedge rst_active) begin

    if (rst_active) begin
        pending_data      <= 8'h00;
        pending_valid     <= 1'b0;
        response_overflow <= 1'b0;
    end

    else begin

        // 收到新的状态查询请求
        if (query_req) begin

            // 缓冲区为空，或者旧数据本周期正被 TX 取走
            if (!pending_valid || tx_start) begin
                pending_data  <= status_byte;
                pending_valid <= 1'b1;
            end

            // 缓冲区已满，不能覆盖尚未发送的响应
            else begin
                response_overflow <= 1'b1;
            end

        end

        // 没有新查询，但旧响应已交给 UART_TX
        else if (tx_start) begin
            pending_valid <= 1'b0;
        end

    end
end 

   

    countdown countdown_inst (
        .clk(clk),
        .rst(rst_active),
        .start_pause_pulse(serial_start_pause_pulse),
        .tick_1s(tick_1s),
        .running(running),
        .display_data(display_data),
        .load_inital(load_inital),
        .status_data(status_data)
    );

    hex7seg hex7seg_inst (
       .hex(current_hex),
       .seg(seg)
    );

    sevenseg_scan sevenseg_scan_inst (
        .clk(clk),
        .digit_en(digit_en),
        .current_hex(current_hex),
        .display_data(display_data)
    );

    uart_rx uart_rx_inst (
        .clk(clk),
        .rst(rst_active),
        .uart_rx(uart_rx),
        .rx_data(rx_data),
        .rx_valid(rx_valid)
    );

    timer_tick timer_tick_inst (
        .clk(clk),
        .rst(rst_active),
        .tick_1s(tick_1s),
        .enable(running),
        .clear(clear)

    );

    uart_tx uart_tx_inst (
        .clk(clk),
        .rst(rst_active),
        .tx_start(tx_start),
        .tx_data(pending_data),
        .tx_busy(tx_busy),
        .tx_done(tx_done),
        .uart_tx(uart_tx)
    );
endmodule
