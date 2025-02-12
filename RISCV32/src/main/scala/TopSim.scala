import chisel3._
import lib.peripherals.MemoryMappedUart.UartPins

object TopSim extends App {
  val MEM_SIZE = 1024
  val FREQ = 100000000
  val BAUD = 9600
  val LED_COUNT = 16

  emitVerilog(
    new TopSim(MEM_SIZE, FREQ, BAUD, LED_COUNT),
    Array("--target-dir", "generated")
  )
}

class TopSim(mem_size: Int, freq: Int, baud: Int, led_cnt: Int) extends Module {
  val io = IO(new Bundle {
    val switches = Input(UInt(16.W))
    val buttons = Input(UInt(4.W))
    val uart = UartPins()
    val leds = Output(UInt(led_cnt.W))
    val sevSeg_value = Output(UInt(8.W))
    val sevSeg_anode = Output(UInt(4.W))

    val regs = Output(Vec(32, SInt(32.W)))
  })

  val cpu = Module(new Cpu)
  val instruction_memory = Module(new Memory)

  cpu.io <> instruction_memory.io

  io.leds := 0.U
  io.sevSeg_value := 0.U
  io.sevSeg_anode := 0.U
  io.uart.tx := 0.U

  io.regs := VecInit(Seq.fill(32)(0.S(32.W)))
}
