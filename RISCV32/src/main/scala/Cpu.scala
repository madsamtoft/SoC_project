import chisel3._
import chisel3.util._

class Cpu extends Module{
  val io = IO(new Bundle{
    val instruction = Input(UInt(32.W))

    //Outputs for testing
    val pc = Output(UInt(32.W))
    val regs = Vec(32, SInt(32.W))
  })

  // IF
  val pc_reg = RegInit(0.S(32.W))
  val pc = WireDefault(0.U(32.W))
  pc := (pc_reg + 4.S).asUInt
  pc_reg := pc.asSInt

  // ID
  val opcode = io.instruction(6, 0)
  val rd = WireDefault(0.U(5.W))
  val funct3 = WireDefault(0.U(3.W))
  val rs1 = WireDefault(0.U(5.W))
  val rs2 = WireDefault(0.U(5.W))
  val funct7 = WireDefault(0.U(7.W))
  val imm = WireDefault(0.S(32.W))

  switch(opcode) {
    is(Opcodes.RTYPE) {
      rd := io.instruction(11, 7)
      funct3 := io.instruction(12, 14)
      rs1 := io.instruction(19, 15)
      rs2 := io.instruction(24, 20)
      funct7 := io.instruction(31, 25)
    }
    is(Opcodes.ITYPE_ARIT, Opcodes.ITYPE_LOAD, Opcodes.ITYPE_JALR) {
      rd := io.instruction(11, 7)
      funct3 := io.instruction(12, 14)
      rs1 := io.instruction(19, 15)
      imm := io.instruction(31, 20)
    }
    is(Opcodes.STYPE) {
      funct3 := io.instruction(12, 14)
      rs1 := io.instruction(19, 15)
      rs2 := io.instruction(24, 20)
      imm := Cat(io.instruction(31, 25), io.instruction(11, 7))
    }
    is(Opcodes.BTYPE) {
      funct3 := io.instruction(12, 14)
      rs1 := io.instruction(19, 15)
      rs2 := io.instruction(24, 20)
      imm := Cat(io.instruction(31), io.instruction(7), io.instruction(30, 25), io.instruction(11, 8))
    }
    is(Opcodes.UTYPE_LUI, Opcodes.UTYPE_AUIPC) {
      rd := io.instruction(11, 7)
      imm := io.instruction(31, 12)
    }
    is(Opcodes.JTYPE) {
      rd := io.instruction(11, 7)
      imm := io.instruction(31, 12)
    }
  }





}
