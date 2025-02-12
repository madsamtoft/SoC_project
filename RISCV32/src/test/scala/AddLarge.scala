import chisel3._
import chiseltest._
import lib.ReadAssembly
import org.scalatest.flatspec.AnyFlatSpec

class AddLarge extends AnyFlatSpec with ChiselScalatestTester {
  "AddLarge test" should "pass" in {
    val MEM_SIZE = 1024
    val FREQ = 100000000
    val BAUD = 9600
    val LED_CNT = 16
    val PROGRAM: Seq[Int] = ReadAssembly.readBin("tests/simple/addlarge.bin")
    test(new TopSim(MEM_SIZE, FREQ, BAUD, LED_CNT)).withAnnotations(Seq(WriteVcdAnnotation)) { dut =>
      while(dut.io.regs(17).peekInt != 10) {
        dut.clock.step()
      }
      dut.io.regs(12).expect(-1.S)
    }
  }
}
