import chisel3._
import chiseltest._
import lib.ReadAssembly
import org.scalatest.flatspec.AnyFlatSpec

class BranchTrap extends AnyFlatSpec with ChiselScalatestTester {
  "BranchTrap test" should "pass" in {
    val MEM_SIZE = 1024
    val FREQ = 100000000
    val BAUD = 9600
    val LED_CNT = 16
    val PROGRAM: Seq[Int] = ReadAssembly.readBin("tests/simple/branchtrap.bin")
    test(new TopSim(PROGRAM, MEM_SIZE, FREQ, BAUD, LED_CNT)).withAnnotations(Seq(WriteVcdAnnotation)) { dut =>
      while(dut.io.regs(17).peekInt != 10) {
        dut.clock.step()
      }
      dut.io.regs(5).expect(-123.S)
      dut.io.regs(6).expect(-123.S)
      dut.io.regs(7).expect(122.S)
      dut.io.regs(11).expect(1.S)
      dut.io.regs(12).expect(2.S)
      dut.io.regs(13).expect(3.S)
      dut.io.regs(14).expect(4.S)
      dut.io.regs(15).expect(5.S)
    }
  }
}
