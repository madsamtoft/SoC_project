import chisel3._
import chiseltest._
import lib.ReadAssembly
import org.scalatest.flatspec.AnyFlatSpec

class Bool extends AnyFlatSpec with ChiselScalatestTester {
  "Bool test" should "pass" in {
    val MEM_SIZE = 1024
    val FREQ = 100000000
    val BAUD = 9600
    val LED_CNT = 16
    val PROGRAM: Seq[Int] = ReadAssembly.readBin("tests/simple/bool.bin")
    test(new TopSim(MEM_SIZE, FREQ, BAUD, LED_CNT)).withAnnotations(Seq(WriteVcdAnnotation)) { dut =>
      while(dut.io.regs(17).peekInt != 10) {
        dut.clock.step()
      }
      dut.io.regs(11).expect(-1174816301.S)
      dut.io.regs(12).expect(-1140981765.S)
      dut.io.regs(13).expect(33834536.S)
      dut.io.regs(14).expect(305419097.S)
      dut.io.regs(15).expect(305420153.S)
      dut.io.regs(16).expect(1056.S)
    }
  }
}
