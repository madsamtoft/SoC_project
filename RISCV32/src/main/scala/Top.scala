import chisel3._
import lib.peripherals.MemoryMappedUart.UartPins

object Bus extends Bundle {
  val read = Output(Bool())
  val write = Output(Bool())
  val addr = Output(UInt(32.W))
  val wrData = Output(UInt(32.W))
  val rdData = Input(UInt(32.W))
}

object Top extends App {
  val MEM_SIZE = 1024
  val FREQ = 100000000
  val BAUD = 9600
  val LED_COUNT = 16

  emitVerilog(
    new Top(MEM_SIZE, FREQ, BAUD, LED_COUNT),
    Array("--target-dir", "generated")
  )
}

class Top(mem_size: Int, freq: Int, baud: Int, led_cnt: Int) extends Module {
  val io = IO(new Bundle {
    val switches = Input(UInt(16.W))
    val buttons = Input(UInt(4.W))
    val uart = UartPins()
    val leds = Output(UInt(led_cnt.W))
    val sevSeg_value = Output(UInt(8.W))
    val sevSeg_anode = Output(UInt(4.W))
  })

  val cpu = Module(new Cpu)
  val instruction_memory = Module(new Memory)

  cpu.io <> instruction_memory.io


  io.leds := 0.U
  io.sevSeg_value := 0.U
  io.sevSeg_anode := 0.U
  io.uart.tx := 0.U
}
