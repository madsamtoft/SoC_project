import chisel3._
import chiseltest._
import lib.ReadAssembly
import org.scalatest.flatspec.AnyFlatSpec

class String extends AnyFlatSpec with ChiselScalatestTester {
  "String test" should "pass" in {
    val MEM_SIZE = 1024
    val FREQ = 100000000
    val BAUD = 9600
    val LED_CNT = 16
    val PROGRAM: Seq[Int] = ReadAssembly.readBin("tests/simple/string.bin")
    test(new TopSim(PROGRAM, MEM_SIZE, FREQ, BAUD, LED_CNT)).withAnnotations(Seq(WriteVcdAnnotation)) { dut =>
      while(dut.io.regs(17).peekInt != 10) {
        dut.clock.step()
      }
      dut.io.regs(10).expect(268435484.S)
      dut.io.regs(11).expect(121.S)
      dut.io.regs(12).expect(111.S)
      dut.io.regs(13).expect(117.S)
      dut.io.regs(14).expect(39.S)
      dut.io.regs(15).expect(114.S)
      dut.io.regs(16).expect(101.S)
    }
  }
}
