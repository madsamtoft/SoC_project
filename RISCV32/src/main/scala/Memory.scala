import chisel3._

class Memory extends Module{
  val io = IO(new Bundle{
    val instruction = Output(UInt(32.W))
  })
  io.instruction := 0.U
}
