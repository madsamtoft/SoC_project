import chisel3._
import chiseltest._
import lib.ReadAssembly
import org.scalatest.flatspec.AnyFlatSpec

class Shift2 extends AnyFlatSpec with ChiselScalatestTester {
  "Shift2 test" should "pass" in {
    val MEM_SIZE = 1024
    val FREQ = 100000000
    val BAUD = 9600
    val LED_CNT = 16
    val PROGRAM: Seq[Int] = ReadAssembly.readBin("tests/simple/shift2.bin")
    test(new TopSim(MEM_SIZE, FREQ, BAUD, LED_CNT)).withAnnotations(Seq(WriteVcdAnnotation)) { dut =>
      while(dut.io.regs(17).peekInt != 10) {
        dut.clock.step()
      }
      dut.io.regs(10).expect(-1412567125.S)
      dut.io.regs(11).expect(1469833046.S)
      dut.io.regs(12).expect(1441200085.S)
      dut.io.regs(13).expect(-706283563.S)
      dut.io.regs(14).expect(1584364888.S)
      dut.io.regs(15).expect(360300021.S)
      dut.io.regs(16).expect(-176570891.S)
    }
  }
}
