module TopSim(
  input         clock,
  input         reset,
  input  [15:0] io_switches,
  input  [3:0]  io_buttons,
  output        io_uart_tx,
  input         io_uart_rx,
  output [15:0] io_leds,
  output [7:0]  io_sevSeg_value,
  output [3:0]  io_sevSeg_anode,
  output [31:0] io_regs_0,
  output [31:0] io_regs_1,
  output [31:0] io_regs_2,
  output [31:0] io_regs_3,
  output [31:0] io_regs_4,
  output [31:0] io_regs_5,
  output [31:0] io_regs_6,
  output [31:0] io_regs_7,
  output [31:0] io_regs_8,
  output [31:0] io_regs_9,
  output [31:0] io_regs_10,
  output [31:0] io_regs_11,
  output [31:0] io_regs_12,
  output [31:0] io_regs_13,
  output [31:0] io_regs_14,
  output [31:0] io_regs_15,
  output [31:0] io_regs_16,
  output [31:0] io_regs_17,
  output [31:0] io_regs_18,
  output [31:0] io_regs_19,
  output [31:0] io_regs_20,
  output [31:0] io_regs_21,
  output [31:0] io_regs_22,
  output [31:0] io_regs_23,
  output [31:0] io_regs_24,
  output [31:0] io_regs_25,
  output [31:0] io_regs_26,
  output [31:0] io_regs_27,
  output [31:0] io_regs_28,
  output [31:0] io_regs_29,
  output [31:0] io_regs_30,
  output [31:0] io_regs_31
);
  assign io_uart_tx = 1'h0; // @[TopSim.scala 36:14]
  assign io_leds = 16'h0; // @[TopSim.scala 33:11]
  assign io_sevSeg_value = 8'h0; // @[TopSim.scala 34:19]
  assign io_sevSeg_anode = 4'h0; // @[TopSim.scala 35:19]
  assign io_regs_0 = 32'sh0; // @[TopSim.scala 38:{21,21}]
  assign io_regs_1 = 32'sh0; // @[TopSim.scala 38:{21,21}]
  assign io_regs_2 = 32'sh0; // @[TopSim.scala 38:{21,21}]
  assign io_regs_3 = 32'sh0; // @[TopSim.scala 38:{21,21}]
  assign io_regs_4 = 32'sh0; // @[TopSim.scala 38:{21,21}]
  assign io_regs_5 = 32'sh0; // @[TopSim.scala 38:{21,21}]
  assign io_regs_6 = 32'sh0; // @[TopSim.scala 38:{21,21}]
  assign io_regs_7 = 32'sh0; // @[TopSim.scala 38:{21,21}]
  assign io_regs_8 = 32'sh0; // @[TopSim.scala 38:{21,21}]
  assign io_regs_9 = 32'sh0; // @[TopSim.scala 38:{21,21}]
  assign io_regs_10 = 32'sh0; // @[TopSim.scala 38:{21,21}]
  assign io_regs_11 = 32'sh0; // @[TopSim.scala 38:{21,21}]
  assign io_regs_12 = 32'sh0; // @[TopSim.scala 38:{21,21}]
  assign io_regs_13 = 32'sh0; // @[TopSim.scala 38:{21,21}]
  assign io_regs_14 = 32'sh0; // @[TopSim.scala 38:{21,21}]
  assign io_regs_15 = 32'sh0; // @[TopSim.scala 38:{21,21}]
  assign io_regs_16 = 32'sh0; // @[TopSim.scala 38:{21,21}]
  assign io_regs_17 = 32'sh0; // @[TopSim.scala 38:{21,21}]
  assign io_regs_18 = 32'sh0; // @[TopSim.scala 38:{21,21}]
  assign io_regs_19 = 32'sh0; // @[TopSim.scala 38:{21,21}]
  assign io_regs_20 = 32'sh0; // @[TopSim.scala 38:{21,21}]
  assign io_regs_21 = 32'sh0; // @[TopSim.scala 38:{21,21}]
  assign io_regs_22 = 32'sh0; // @[TopSim.scala 38:{21,21}]
  assign io_regs_23 = 32'sh0; // @[TopSim.scala 38:{21,21}]
  assign io_regs_24 = 32'sh0; // @[TopSim.scala 38:{21,21}]
  assign io_regs_25 = 32'sh0; // @[TopSim.scala 38:{21,21}]
  assign io_regs_26 = 32'sh0; // @[TopSim.scala 38:{21,21}]
  assign io_regs_27 = 32'sh0; // @[TopSim.scala 38:{21,21}]
  assign io_regs_28 = 32'sh0; // @[TopSim.scala 38:{21,21}]
  assign io_regs_29 = 32'sh0; // @[TopSim.scala 38:{21,21}]
  assign io_regs_30 = 32'sh0; // @[TopSim.scala 38:{21,21}]
  assign io_regs_31 = 32'sh0; // @[TopSim.scala 38:{21,21}]
endmodule
