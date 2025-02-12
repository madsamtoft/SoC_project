circuit TopSim :
  module Cpu :
    input clock : Clock
    input reset : Reset
    output io : { flip instruction : UInt<32>}

    skip

  module Memory :
    input clock : Clock
    input reset : Reset
    output io : { instruction : UInt<32>}

    io.instruction <= UInt<1>("h0") @[Memory.scala 7:18]

  module TopSim :
    input clock : Clock
    input reset : UInt<1>
    output io : { flip switches : UInt<16>, flip buttons : UInt<4>, uart : { tx : UInt<1>, flip rx : UInt<1>}, leds : UInt<16>, sevSeg_value : UInt<8>, sevSeg_anode : UInt<4>, regs : SInt<32>[32]}

    inst cpu of Cpu @[TopSim.scala 28:19]
    cpu.clock <= clock
    cpu.reset <= reset
    inst instruction_memory of Memory @[TopSim.scala 29:34]
    instruction_memory.clock <= clock
    instruction_memory.reset <= reset
    cpu.io.instruction <= instruction_memory.io.instruction @[TopSim.scala 31:10]
    io.leds <= UInt<1>("h0") @[TopSim.scala 33:11]
    io.sevSeg_value <= UInt<1>("h0") @[TopSim.scala 34:19]
    io.sevSeg_anode <= UInt<1>("h0") @[TopSim.scala 35:19]
    io.uart.tx <= UInt<1>("h0") @[TopSim.scala 36:14]
    wire _WIRE : SInt<32>[32] @[TopSim.scala 38:21]
    _WIRE[0] <= asSInt(UInt<32>("h0")) @[TopSim.scala 38:21]
    _WIRE[1] <= asSInt(UInt<32>("h0")) @[TopSim.scala 38:21]
    _WIRE[2] <= asSInt(UInt<32>("h0")) @[TopSim.scala 38:21]
    _WIRE[3] <= asSInt(UInt<32>("h0")) @[TopSim.scala 38:21]
    _WIRE[4] <= asSInt(UInt<32>("h0")) @[TopSim.scala 38:21]
    _WIRE[5] <= asSInt(UInt<32>("h0")) @[TopSim.scala 38:21]
    _WIRE[6] <= asSInt(UInt<32>("h0")) @[TopSim.scala 38:21]
    _WIRE[7] <= asSInt(UInt<32>("h0")) @[TopSim.scala 38:21]
    _WIRE[8] <= asSInt(UInt<32>("h0")) @[TopSim.scala 38:21]
    _WIRE[9] <= asSInt(UInt<32>("h0")) @[TopSim.scala 38:21]
    _WIRE[10] <= asSInt(UInt<32>("h0")) @[TopSim.scala 38:21]
    _WIRE[11] <= asSInt(UInt<32>("h0")) @[TopSim.scala 38:21]
    _WIRE[12] <= asSInt(UInt<32>("h0")) @[TopSim.scala 38:21]
    _WIRE[13] <= asSInt(UInt<32>("h0")) @[TopSim.scala 38:21]
    _WIRE[14] <= asSInt(UInt<32>("h0")) @[TopSim.scala 38:21]
    _WIRE[15] <= asSInt(UInt<32>("h0")) @[TopSim.scala 38:21]
    _WIRE[16] <= asSInt(UInt<32>("h0")) @[TopSim.scala 38:21]
    _WIRE[17] <= asSInt(UInt<32>("h0")) @[TopSim.scala 38:21]
    _WIRE[18] <= asSInt(UInt<32>("h0")) @[TopSim.scala 38:21]
    _WIRE[19] <= asSInt(UInt<32>("h0")) @[TopSim.scala 38:21]
    _WIRE[20] <= asSInt(UInt<32>("h0")) @[TopSim.scala 38:21]
    _WIRE[21] <= asSInt(UInt<32>("h0")) @[TopSim.scala 38:21]
    _WIRE[22] <= asSInt(UInt<32>("h0")) @[TopSim.scala 38:21]
    _WIRE[23] <= asSInt(UInt<32>("h0")) @[TopSim.scala 38:21]
    _WIRE[24] <= asSInt(UInt<32>("h0")) @[TopSim.scala 38:21]
    _WIRE[25] <= asSInt(UInt<32>("h0")) @[TopSim.scala 38:21]
    _WIRE[26] <= asSInt(UInt<32>("h0")) @[TopSim.scala 38:21]
    _WIRE[27] <= asSInt(UInt<32>("h0")) @[TopSim.scala 38:21]
    _WIRE[28] <= asSInt(UInt<32>("h0")) @[TopSim.scala 38:21]
    _WIRE[29] <= asSInt(UInt<32>("h0")) @[TopSim.scala 38:21]
    _WIRE[30] <= asSInt(UInt<32>("h0")) @[TopSim.scala 38:21]
    _WIRE[31] <= asSInt(UInt<32>("h0")) @[TopSim.scala 38:21]
    io.regs <= _WIRE @[TopSim.scala 38:11]

