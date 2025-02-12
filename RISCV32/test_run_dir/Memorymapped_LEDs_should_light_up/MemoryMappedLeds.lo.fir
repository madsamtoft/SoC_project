FIRRTL version 1.1.0
circuit MemoryMappedLeds :
  module MemoryMappedLeds :
    input clock : Clock
    input reset : UInt<1>
    input io_port_read : UInt<1>
    input io_port_write : UInt<1>
    input io_port_addr : UInt<32>
    input io_port_wrData : UInt<32>
    output io_port_rdData : UInt<32>
    output io_pins : UInt<4>

    reg ledReg : UInt<4>, clock with :
      reset => (UInt<1>("h0"), ledReg) @[MemoryMappedLeds.scala 28:23]
    node _GEN_0 = mux(io_port_write, io_port_wrData, ledReg) @[MemoryMappedLeds.scala 30:23 31:12 28:23]
    io_port_rdData <= pad(ledReg, 32) @[MemoryMappedLeds.scala 35:18]
    io_pins <= ledReg @[MemoryMappedLeds.scala 34:11]
    ledReg <= bits(mux(reset, UInt<4>("h0"), _GEN_0), 3, 0) @[MemoryMappedLeds.scala 28:{23,23}]
