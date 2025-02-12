import chisel3._

class Cpu extends Module{
  val io = IO(new Bundle{
    val instruction = Input(UInt(32.W))
  })

}
