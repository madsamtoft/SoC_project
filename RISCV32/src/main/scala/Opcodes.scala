import chisel3._

object Opcodes {
  val RTYPE = "0b0110011".U
  val ITYPE_ARIT = "0b0010011".U
  val ITYPE_LOAD = "0b0000011".U
  val ITYPE_JALR = "0b1100111".U
  val STYPE = "0b0100011".U
  val BTYPE = "0b1100011".U
  val JTYPE = "0b1101111".U
  val UTYPE_LUI = "0b0110111".U
  val UTYPE_AUIPC = "0b0010111".U
}
