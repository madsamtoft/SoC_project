FIRRTL version 1.1.0
circuit MemoryMappedUart :
  module Tx :
    input clock : Clock
    input reset : UInt<1>
    output io_txd : UInt<1>
    output io_channel_ready : UInt<1>
    input io_channel_valid : UInt<1>
    input io_channel_bits : UInt<8>

    reg shiftReg : UInt<11>, clock with :
      reset => (UInt<1>("h0"), shiftReg) @[Uart.scala 30:25]
    reg cntReg : UInt<20>, clock with :
      reset => (UInt<1>("h0"), cntReg) @[Uart.scala 31:23]
    reg bitsReg : UInt<4>, clock with :
      reset => (UInt<1>("h0"), bitsReg) @[Uart.scala 32:24]
    node _io_channel_ready_T = eq(cntReg, UInt<1>("h0")) @[Uart.scala 34:31]
    node _io_channel_ready_T_1 = eq(bitsReg, UInt<1>("h0")) @[Uart.scala 34:52]
    node _io_channel_ready_T_2 = and(_io_channel_ready_T, _io_channel_ready_T_1) @[Uart.scala 34:40]
    node _io_txd_T = bits(shiftReg, 0, 0) @[Uart.scala 35:21]
    node _T = eq(cntReg, UInt<1>("h0")) @[Uart.scala 37:15]
    node _T_1 = neq(bitsReg, UInt<1>("h0")) @[Uart.scala 40:18]
    node shift = shr(shiftReg, 1) @[Uart.scala 41:28]
    node _shiftReg_T = bits(shift, 9, 0) @[Uart.scala 42:33]
    node _shiftReg_T_1 = cat(UInt<1>("h1"), _shiftReg_T) @[Cat.scala 33:92]
    node _bitsReg_T = sub(bitsReg, UInt<1>("h1")) @[Uart.scala 43:26]
    node _bitsReg_T_1 = tail(_bitsReg_T, 1) @[Uart.scala 43:26]
    node _shiftReg_T_2 = cat(UInt<2>("h3"), io_channel_bits) @[Cat.scala 33:92]
    node _shiftReg_T_3 = cat(_shiftReg_T_2, UInt<1>("h0")) @[Cat.scala 33:92]
    node _GEN_0 = mux(io_channel_valid, _shiftReg_T_3, UInt<11>("h7ff")) @[Uart.scala 45:30 46:18 49:18]
    node _GEN_1 = mux(io_channel_valid, UInt<4>("hb"), bitsReg) @[Uart.scala 45:30 47:17 32:24]
    node _GEN_2 = mux(_T_1, _shiftReg_T_1, _GEN_0) @[Uart.scala 40:27 42:16]
    node _GEN_3 = mux(_T_1, _bitsReg_T_1, _GEN_1) @[Uart.scala 40:27 43:15]
    node _cntReg_T = sub(cntReg, UInt<1>("h1")) @[Uart.scala 54:22]
    node _cntReg_T_1 = tail(_cntReg_T, 1) @[Uart.scala 54:22]
    node _GEN_4 = mux(_T, UInt<2>("h2"), _cntReg_T_1) @[Uart.scala 37:24 39:12 54:12]
    node _GEN_5 = mux(_T, _GEN_2, shiftReg) @[Uart.scala 37:24 30:25]
    node _GEN_6 = mux(_T, _GEN_3, bitsReg) @[Uart.scala 32:24 37:24]
    io_txd <= _io_txd_T @[Uart.scala 35:10]
    io_channel_ready <= _io_channel_ready_T_2 @[Uart.scala 34:20]
    shiftReg <= mux(reset, UInt<11>("h7ff"), _GEN_5) @[Uart.scala 30:{25,25}]
    cntReg <= mux(reset, UInt<20>("h0"), _GEN_4) @[Uart.scala 31:{23,23}]
    bitsReg <= mux(reset, UInt<4>("h0"), _GEN_6) @[Uart.scala 32:{24,24}]

  module Rx :
    input clock : Clock
    input reset : UInt<1>
    input io_rxd : UInt<1>
    input io_channel_ready : UInt<1>
    output io_channel_valid : UInt<1>
    output io_channel_bits : UInt<8>

    reg rxReg_REG : UInt<1>, clock with :
      reset => (UInt<1>("h0"), rxReg_REG) @[Uart.scala 76:30]
    reg rxReg : UInt<1>, clock with :
      reset => (UInt<1>("h0"), rxReg) @[Uart.scala 76:22]
    reg shiftReg : UInt<8>, clock with :
      reset => (UInt<1>("h0"), shiftReg) @[Uart.scala 78:25]
    reg cntReg : UInt<20>, clock with :
      reset => (UInt<1>("h0"), cntReg) @[Uart.scala 79:23]
    reg bitsReg : UInt<4>, clock with :
      reset => (UInt<1>("h0"), bitsReg) @[Uart.scala 80:24]
    reg valReg : UInt<1>, clock with :
      reset => (UInt<1>("h0"), valReg) @[Uart.scala 81:23]
    node _T = neq(cntReg, UInt<1>("h0")) @[Uart.scala 83:15]
    node _cntReg_T = sub(cntReg, UInt<1>("h1")) @[Uart.scala 84:22]
    node _cntReg_T_1 = tail(_cntReg_T, 1) @[Uart.scala 84:22]
    node _T_1 = neq(bitsReg, UInt<1>("h0")) @[Uart.scala 85:22]
    node _shiftReg_T = shr(shiftReg, 1) @[Uart.scala 87:37]
    node _shiftReg_T_1 = cat(rxReg, _shiftReg_T) @[Cat.scala 33:92]
    node _bitsReg_T = sub(bitsReg, UInt<1>("h1")) @[Uart.scala 88:24]
    node _bitsReg_T_1 = tail(_bitsReg_T, 1) @[Uart.scala 88:24]
    node _T_2 = eq(bitsReg, UInt<1>("h1")) @[Uart.scala 90:18]
    node _GEN_0 = mux(_T_2, UInt<1>("h1"), valReg) @[Uart.scala 90:27 91:14 81:23]
    node _T_3 = eq(rxReg, UInt<1>("h0")) @[Uart.scala 93:20]
    node _GEN_1 = mux(_T_3, UInt<3>("h4"), cntReg) @[Uart.scala 93:29 94:12 79:23]
    node _GEN_2 = mux(_T_3, UInt<4>("h8"), bitsReg) @[Uart.scala 93:29 95:13 80:24]
    node _GEN_3 = mux(_T_1, UInt<2>("h2"), _GEN_1) @[Uart.scala 85:31 86:12]
    node _GEN_4 = mux(_T_1, _shiftReg_T_1, shiftReg) @[Uart.scala 85:31 87:14 78:25]
    node _GEN_5 = mux(_T_1, _bitsReg_T_1, _GEN_2) @[Uart.scala 85:31 88:13]
    node _GEN_6 = mux(_T_1, _GEN_0, valReg) @[Uart.scala 81:23 85:31]
    node _GEN_7 = mux(_T, _cntReg_T_1, _GEN_3) @[Uart.scala 83:24 84:12]
    node _GEN_8 = mux(_T, shiftReg, _GEN_4) @[Uart.scala 83:24 78:25]
    node _GEN_9 = mux(_T, bitsReg, _GEN_5) @[Uart.scala 80:24 83:24]
    node _GEN_10 = mux(_T, valReg, _GEN_6) @[Uart.scala 81:23 83:24]
    node _T_4 = and(valReg, io_channel_ready) @[Uart.scala 98:15]
    node _GEN_11 = mux(_T_4, UInt<1>("h0"), _GEN_10) @[Uart.scala 98:36 99:12]
    io_channel_valid <= valReg @[Uart.scala 103:20]
    io_channel_bits <= shiftReg @[Uart.scala 102:19]
    rxReg_REG <= mux(reset, UInt<1>("h1"), io_rxd) @[Uart.scala 76:{30,30,30}]
    rxReg <= mux(reset, UInt<1>("h1"), rxReg_REG) @[Uart.scala 76:{22,22,22}]
    shiftReg <= mux(reset, UInt<8>("h0"), _GEN_8) @[Uart.scala 78:{25,25}]
    cntReg <= mux(reset, UInt<20>("h0"), _GEN_7) @[Uart.scala 79:{23,23}]
    bitsReg <= mux(reset, UInt<4>("h0"), _GEN_9) @[Uart.scala 80:{24,24}]
    valReg <= mux(reset, UInt<1>("h0"), _GEN_11) @[Uart.scala 81:{23,23}]

  module Queue :
    input clock : Clock
    input reset : UInt<1>
    output io_enq_ready : UInt<1>
    input io_enq_valid : UInt<1>
    input io_enq_bits : UInt<8>
    input io_deq_ready : UInt<1>
    output io_deq_valid : UInt<1>
    output io_deq_bits : UInt<8>
    output io_count : UInt<2>

    mem ram : @[Decoupled.scala 273:95]
      data-type => UInt<8>
      depth => 2
      read-latency => 0
      write-latency => 1
      reader => io_deq_bits_MPORT
      writer => MPORT
      read-under-write => undefined
    reg enq_ptr_value : UInt<1>, clock with :
      reset => (UInt<1>("h0"), enq_ptr_value) @[Counter.scala 61:40]
    reg deq_ptr_value : UInt<1>, clock with :
      reset => (UInt<1>("h0"), deq_ptr_value) @[Counter.scala 61:40]
    reg maybe_full : UInt<1>, clock with :
      reset => (UInt<1>("h0"), maybe_full) @[Decoupled.scala 276:27]
    node ptr_match = eq(enq_ptr_value, deq_ptr_value) @[Decoupled.scala 277:33]
    node _empty_T = eq(maybe_full, UInt<1>("h0")) @[Decoupled.scala 278:28]
    node empty = and(ptr_match, _empty_T) @[Decoupled.scala 278:25]
    node full = and(ptr_match, maybe_full) @[Decoupled.scala 279:24]
    node _do_enq_T = and(io_enq_ready, io_enq_valid) @[Decoupled.scala 51:35]
    node _do_deq_T = and(io_deq_ready, io_deq_valid) @[Decoupled.scala 51:35]
    node wrap = eq(enq_ptr_value, UInt<1>("h1")) @[Counter.scala 73:24]
    node _value_T = add(enq_ptr_value, UInt<1>("h1")) @[Counter.scala 77:24]
    node _value_T_1 = tail(_value_T, 1) @[Counter.scala 77:24]
    node do_enq = _do_enq_T @[Decoupled.scala 280:{27,27}]
    node _GEN_0 = validif(do_enq, enq_ptr_value) @[Decoupled.scala 286:16 287:8]
    node _GEN_1 = validif(do_enq, clock) @[Decoupled.scala 286:16 287:8]
    node _GEN_2 = mux(do_enq, UInt<1>("h1"), UInt<1>("h0")) @[Decoupled.scala 286:16 287:8 273:95]
    node _GEN_3 = validif(do_enq, UInt<1>("h1")) @[Decoupled.scala 286:16 287:24]
    node _GEN_4 = validif(do_enq, io_enq_bits) @[Decoupled.scala 286:16 287:24]
    node _GEN_5 = mux(do_enq, _value_T_1, enq_ptr_value) @[Decoupled.scala 286:16 Counter.scala 77:15 61:40]
    node wrap_1 = eq(deq_ptr_value, UInt<1>("h1")) @[Counter.scala 73:24]
    node _value_T_2 = add(deq_ptr_value, UInt<1>("h1")) @[Counter.scala 77:24]
    node _value_T_3 = tail(_value_T_2, 1) @[Counter.scala 77:24]
    node do_deq = _do_deq_T @[Decoupled.scala 281:{27,27}]
    node _GEN_6 = mux(do_deq, _value_T_3, deq_ptr_value) @[Decoupled.scala 290:16 Counter.scala 77:15 61:40]
    node _T = neq(do_enq, do_deq) @[Decoupled.scala 293:15]
    node _GEN_7 = mux(_T, do_enq, maybe_full) @[Decoupled.scala 293:27 294:16 276:27]
    node _GEN_8 = mux(UInt<1>("h0"), UInt<1>("h0"), _GEN_5) @[Decoupled.scala 296:15 Counter.scala 98:11]
    node _GEN_9 = mux(UInt<1>("h0"), UInt<1>("h0"), _GEN_6) @[Decoupled.scala 296:15 Counter.scala 98:11]
    node _GEN_10 = mux(UInt<1>("h0"), UInt<1>("h0"), _GEN_7) @[Decoupled.scala 296:15 299:16]
    node _io_deq_valid_T = eq(empty, UInt<1>("h0")) @[Decoupled.scala 302:19]
    node _io_enq_ready_T = eq(full, UInt<1>("h0")) @[Decoupled.scala 303:19]
    node _ptr_diff_T = sub(enq_ptr_value, deq_ptr_value) @[Decoupled.scala 326:32]
    node ptr_diff = tail(_ptr_diff_T, 1) @[Decoupled.scala 326:32]
    node _io_count_T = and(maybe_full, ptr_match) @[Decoupled.scala 329:32]
    node _io_count_T_1 = mux(_io_count_T, UInt<2>("h2"), UInt<1>("h0")) @[Decoupled.scala 329:20]
    node _io_count_T_2 = or(_io_count_T_1, ptr_diff) @[Decoupled.scala 329:62]
    io_enq_ready <= _io_enq_ready_T @[Decoupled.scala 303:16]
    io_deq_valid <= _io_deq_valid_T @[Decoupled.scala 302:16]
    io_deq_bits <= ram.io_deq_bits_MPORT.data @[Decoupled.scala 310:17]
    io_count <= _io_count_T_2 @[Decoupled.scala 329:14]
    ram.io_deq_bits_MPORT.addr <= deq_ptr_value @[Decoupled.scala 310:23]
    ram.io_deq_bits_MPORT.en <= UInt<1>("h1") @[Decoupled.scala 310:23]
    ram.io_deq_bits_MPORT.clk <= clock @[Decoupled.scala 310:23]
    ram.MPORT.addr <= _GEN_0
    ram.MPORT.en <= _GEN_2
    ram.MPORT.clk <= _GEN_1
    ram.MPORT.data <= _GEN_4
    ram.MPORT.mask <= _GEN_3
    enq_ptr_value <= mux(reset, UInt<1>("h0"), _GEN_8) @[Counter.scala 61:{40,40}]
    deq_ptr_value <= mux(reset, UInt<1>("h0"), _GEN_9) @[Counter.scala 61:{40,40}]
    maybe_full <= mux(reset, UInt<1>("h0"), _GEN_10) @[Decoupled.scala 276:{27,27}]

  module MemoryMappedUart :
    input clock : Clock
    input reset : UInt<1>
    input io_port_read : UInt<1>
    input io_port_write : UInt<1>
    input io_port_addr : UInt<32>
    input io_port_wrData : UInt<32>
    output io_port_rdData : UInt<32>
    output io_pins_tx : UInt<1>
    input io_pins_rx : UInt<1>

    inst transmitter of Tx @[MemoryMappedUart.scala 61:27]
    inst receiver of Rx @[MemoryMappedUart.scala 62:24]
    inst txBuffer of Queue @[MemoryMappedUart.scala 65:24]
    inst rxBuffer of Queue @[MemoryMappedUart.scala 66:24]
    node _hadDataReadRequest_T = eq(io_port_addr, UInt<1>("h0")) @[Bus.scala 82:30]
    node _hadDataReadRequest_T_1 = and(io_port_read, _hadDataReadRequest_T) @[Bus.scala 82:17]
    reg hadDataReadRequest : UInt<1>, clock with :
      reset => (UInt<1>("h0"), hadDataReadRequest) @[MemoryMappedUart.scala 74:12]
    node _txBuffer_io_enq_valid_T = eq(io_port_addr, UInt<1>("h0")) @[Bus.scala 75:31]
    node _txBuffer_io_enq_valid_T_1 = and(io_port_write, _txBuffer_io_enq_valid_T) @[Bus.scala 75:18]
    node _io_port_rdData_T = cat(rxBuffer.io_deq_valid, txBuffer.io_enq_ready) @[MemoryMappedUart.scala 94:27]
    node _io_port_rdData_T_1 = mux(hadDataReadRequest, rxBuffer.io_deq_bits, _io_port_rdData_T) @[MemoryMappedUart.scala 91:24]
    io_port_rdData <= pad(_io_port_rdData_T_1, 32) @[MemoryMappedUart.scala 91:18]
    io_pins_tx <= transmitter.io_txd @[MemoryMappedUart.scala 87:14]
    transmitter.clock <= clock
    transmitter.reset <= reset
    transmitter.io_channel_valid <= txBuffer.io_deq_valid @[MemoryMappedUart.scala 69:19]
    transmitter.io_channel_bits <= txBuffer.io_deq_bits @[MemoryMappedUart.scala 69:19]
    receiver.clock <= clock
    receiver.reset <= reset
    receiver.io_rxd <= io_pins_rx @[MemoryMappedUart.scala 88:19]
    receiver.io_channel_ready <= rxBuffer.io_enq_ready @[MemoryMappedUart.scala 70:23]
    txBuffer.clock <= clock
    txBuffer.reset <= reset
    txBuffer.io_enq_valid <= _txBuffer_io_enq_valid_T_1 @[MemoryMappedUart.scala 81:25]
    txBuffer.io_enq_bits <= bits(io_port_wrData, 7, 0) @[MemoryMappedUart.scala 80:24]
    txBuffer.io_deq_ready <= transmitter.io_channel_ready @[MemoryMappedUart.scala 69:19]
    rxBuffer.clock <= clock
    rxBuffer.reset <= reset
    rxBuffer.io_enq_valid <= receiver.io_channel_valid @[MemoryMappedUart.scala 70:23]
    rxBuffer.io_enq_bits <= receiver.io_channel_bits @[MemoryMappedUart.scala 70:23]
    rxBuffer.io_deq_ready <= hadDataReadRequest @[MemoryMappedUart.scala 84:25]
    hadDataReadRequest <= mux(reset, UInt<1>("h0"), _hadDataReadRequest_T_1) @[MemoryMappedUart.scala 74:{12,12,12}]
