import chisel3._
import chiseltest._
import lib.ReadAssembly
import org.scalatest.flatspec.AnyFlatSpec

class Loop extends AnyFlatSpec with ChiselScalatestTester {
  "Loop test" should "pass" in {
    val MEM_SIZE = 1024
    val FREQ = 100000000
    val BAUD = 9600
    val LED_CNT = 16
    val PROGRAM: Seq[Int] = ReadAssembly.readBin("tests/simple/loop.bin")
    test(new TopSim(MEM_SIZE, FREQ, BAUD, LED_CNT)).withAnnotations(Seq(WriteVcdAnnotation)) { dut =>
      // C to assembly program
      while(dut.io.regs(17).peekInt != 10) {
        dut.clock.step()
      }
      //dut.io.regs(10).expect(3.S)
      //dut.io.regs(11).expect(4.S)
      dut.io.regs(16).expect(100.S)
    }
  }
}
