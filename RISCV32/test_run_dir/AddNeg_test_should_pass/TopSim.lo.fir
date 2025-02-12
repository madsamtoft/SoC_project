FIRRTL version 1.1.0
circuit TopSim :
  module Cpu :
    input clock : Clock
    input reset : UInt<1>
    input io_instruction : UInt<32>

    skip

  module Memory :
    input clock : Clock
    input reset : UInt<1>
    output io_instruction : UInt<32>

    io_instruction <= UInt<32>("h0") @[Memory.scala 7:18]

  module TopSim :
    input clock : Clock
    input reset : UInt<1>
    input io_switches : UInt<16>
    input io_buttons : UInt<4>
    output io_uart_tx : UInt<1>
    input io_uart_rx : UInt<1>
    output io_leds : UInt<16>
    output io_sevSeg_value : UInt<8>
    output io_sevSeg_anode : UInt<4>
    output io_regs_0 : SInt<32>
    output io_regs_1 : SInt<32>
    output io_regs_2 : SInt<32>
    output io_regs_3 : SInt<32>
    output io_regs_4 : SInt<32>
    output io_regs_5 : SInt<32>
    output io_regs_6 : SInt<32>
    output io_regs_7 : SInt<32>
    output io_regs_8 : SInt<32>
    output io_regs_9 : SInt<32>
    output io_regs_10 : SInt<32>
    output io_regs_11 : SInt<32>
    output io_regs_12 : SInt<32>
    output io_regs_13 : SInt<32>
    output io_regs_14 : SInt<32>
    output io_regs_15 : SInt<32>
    output io_regs_16 : SInt<32>
    output io_regs_17 : SInt<32>
    output io_regs_18 : SInt<32>
    output io_regs_19 : SInt<32>
    output io_regs_20 : SInt<32>
    output io_regs_21 : SInt<32>
    output io_regs_22 : SInt<32>
    output io_regs_23 : SInt<32>
    output io_regs_24 : SInt<32>
    output io_regs_25 : SInt<32>
    output io_regs_26 : SInt<32>
    output io_regs_27 : SInt<32>
    output io_regs_28 : SInt<32>
    output io_regs_29 : SInt<32>
    output io_regs_30 : SInt<32>
    output io_regs_31 : SInt<32>

    inst cpu of Cpu @[TopSim.scala 28:19]
    inst instruction_memory of Memory @[TopSim.scala 29:34]
    node _WIRE_0 = asSInt(UInt<32>("h0")) @[TopSim.scala 38:{21,21}]
    node _WIRE_1 = asSInt(UInt<32>("h0")) @[TopSim.scala 38:{21,21}]
    node _WIRE_2 = asSInt(UInt<32>("h0")) @[TopSim.scala 38:{21,21}]
    node _WIRE_3 = asSInt(UInt<32>("h0")) @[TopSim.scala 38:{21,21}]
    node _WIRE_4 = asSInt(UInt<32>("h0")) @[TopSim.scala 38:{21,21}]
    node _WIRE_5 = asSInt(UInt<32>("h0")) @[TopSim.scala 38:{21,21}]
    node _WIRE_6 = asSInt(UInt<32>("h0")) @[TopSim.scala 38:{21,21}]
    node _WIRE_7 = asSInt(UInt<32>("h0")) @[TopSim.scala 38:{21,21}]
    node _WIRE_8 = asSInt(UInt<32>("h0")) @[TopSim.scala 38:{21,21}]
    node _WIRE_9 = asSInt(UInt<32>("h0")) @[TopSim.scala 38:{21,21}]
    node _WIRE_10 = asSInt(UInt<32>("h0")) @[TopSim.scala 38:{21,21}]
    node _WIRE_11 = asSInt(UInt<32>("h0")) @[TopSim.scala 38:{21,21}]
    node _WIRE_12 = asSInt(UInt<32>("h0")) @[TopSim.scala 38:{21,21}]
    node _WIRE_13 = asSInt(UInt<32>("h0")) @[TopSim.scala 38:{21,21}]
    node _WIRE_14 = asSInt(UInt<32>("h0")) @[TopSim.scala 38:{21,21}]
    node _WIRE_15 = asSInt(UInt<32>("h0")) @[TopSim.scala 38:{21,21}]
    node _WIRE_16 = asSInt(UInt<32>("h0")) @[TopSim.scala 38:{21,21}]
    node _WIRE_17 = asSInt(UInt<32>("h0")) @[TopSim.scala 38:{21,21}]
    node _WIRE_18 = asSInt(UInt<32>("h0")) @[TopSim.scala 38:{21,21}]
    node _WIRE_19 = asSInt(UInt<32>("h0")) @[TopSim.scala 38:{21,21}]
    node _WIRE_20 = asSInt(UInt<32>("h0")) @[TopSim.scala 38:{21,21}]
    node _WIRE_21 = asSInt(UInt<32>("h0")) @[TopSim.scala 38:{21,21}]
    node _WIRE_22 = asSInt(UInt<32>("h0")) @[TopSim.scala 38:{21,21}]
    node _WIRE_23 = asSInt(UInt<32>("h0")) @[TopSim.scala 38:{21,21}]
    node _WIRE_24 = asSInt(UInt<32>("h0")) @[TopSim.scala 38:{21,21}]
    node _WIRE_25 = asSInt(UInt<32>("h0")) @[TopSim.scala 38:{21,21}]
    node _WIRE_26 = asSInt(UInt<32>("h0")) @[TopSim.scala 38:{21,21}]
    node _WIRE_27 = asSInt(UInt<32>("h0")) @[TopSim.scala 38:{21,21}]
    node _WIRE_28 = asSInt(UInt<32>("h0")) @[TopSim.scala 38:{21,21}]
    node _WIRE_29 = asSInt(UInt<32>("h0")) @[TopSim.scala 38:{21,21}]
    node _WIRE_30 = asSInt(UInt<32>("h0")) @[TopSim.scala 38:{21,21}]
    node _WIRE_31 = asSInt(UInt<32>("h0")) @[TopSim.scala 38:{21,21}]
    io_uart_tx <= UInt<1>("h0") @[TopSim.scala 36:14]
    io_leds <= UInt<16>("h0") @[TopSim.scala 33:11]
    io_sevSeg_value <= UInt<8>("h0") @[TopSim.scala 34:19]
    io_sevSeg_anode <= UInt<4>("h0") @[TopSim.scala 35:19]
    io_regs_0 <= _WIRE_0 @[TopSim.scala 38:11]
    io_regs_1 <= _WIRE_1 @[TopSim.scala 38:11]
    io_regs_2 <= _WIRE_2 @[TopSim.scala 38:11]
    io_regs_3 <= _WIRE_3 @[TopSim.scala 38:11]
    io_regs_4 <= _WIRE_4 @[TopSim.scala 38:11]
    io_regs_5 <= _WIRE_5 @[TopSim.scala 38:11]
    io_regs_6 <= _WIRE_6 @[TopSim.scala 38:11]
    io_regs_7 <= _WIRE_7 @[TopSim.scala 38:11]
    io_regs_8 <= _WIRE_8 @[TopSim.scala 38:11]
    io_regs_9 <= _WIRE_9 @[TopSim.scala 38:11]
    io_regs_10 <= _WIRE_10 @[TopSim.scala 38:11]
    io_regs_11 <= _WIRE_11 @[TopSim.scala 38:11]
    io_regs_12 <= _WIRE_12 @[TopSim.scala 38:11]
    io_regs_13 <= _WIRE_13 @[TopSim.scala 38:11]
    io_regs_14 <= _WIRE_14 @[TopSim.scala 38:11]
    io_regs_15 <= _WIRE_15 @[TopSim.scala 38:11]
    io_regs_16 <= _WIRE_16 @[TopSim.scala 38:11]
    io_regs_17 <= _WIRE_17 @[TopSim.scala 38:11]
    io_regs_18 <= _WIRE_18 @[TopSim.scala 38:11]
    io_regs_19 <= _WIRE_19 @[TopSim.scala 38:11]
    io_regs_20 <= _WIRE_20 @[TopSim.scala 38:11]
    io_regs_21 <= _WIRE_21 @[TopSim.scala 38:11]
    io_regs_22 <= _WIRE_22 @[TopSim.scala 38:11]
    io_regs_23 <= _WIRE_23 @[TopSim.scala 38:11]
    io_regs_24 <= _WIRE_24 @[TopSim.scala 38:11]
    io_regs_25 <= _WIRE_25 @[TopSim.scala 38:11]
    io_regs_26 <= _WIRE_26 @[TopSim.scala 38:11]
    io_regs_27 <= _WIRE_27 @[TopSim.scala 38:11]
    io_regs_28 <= _WIRE_28 @[TopSim.scala 38:11]
    io_regs_29 <= _WIRE_29 @[TopSim.scala 38:11]
    io_regs_30 <= _WIRE_30 @[TopSim.scala 38:11]
    io_regs_31 <= _WIRE_31 @[TopSim.scala 38:11]
    cpu.clock <= clock
    cpu.reset <= reset
    cpu.io_instruction <= instruction_memory.io_instruction @[TopSim.scala 31:10]
    instruction_memory.clock <= clock
    instruction_memory.reset <= reset
