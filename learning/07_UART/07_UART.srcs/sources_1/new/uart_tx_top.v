`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2026/11/06 15:59:36
// Design Name: 
// Module Name: uart_top
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


module uart_tx_top(
    input  wire clk,
    input  wire rst,
    input  wire key,

    output wire uart_tx
    );

    wire stable_key;
    wire key_pulse;

    wire tx_start;
    wire tx_busy;
    wire tx_done;
    wire rst_active;

    assign tx_start = key_pulse && !tx_busy;
    assign rst_active = ~rst;

    Debounce debounce_inst(
        .clk(clk),
        .rst(rst_active),
        .key(key),
        .stable_key(stable_key)
    );

    Edge_test edge_test_inst(
        .clk(clk),
        .rst(rst_active),
        .stable_key(stable_key),
        .pulse(key_pulse)
    );

    uart_tx uart_tx_inst(
        .clk(clk),
        .rst(rst_active),
        .tx_start(tx_start),
        .tx_data(8'h55), // 发送数据为0x55
        .tx_busy(tx_busy),
        .tx_done(tx_done),
        .uart_tx(uart_tx)
    );
endmodule
