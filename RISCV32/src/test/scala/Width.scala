import chisel3._
import chiseltest._
import lib.ReadAssembly
import org.scalatest.flatspec.AnyFlatSpec

class Width extends AnyFlatSpec with ChiselScalatestTester {
  "simple.Width test" should "pass" in {
    val MEM_SIZE = 1024
    val FREQ = 100000000
    val BAUD = 9600
    val LED_CNT = 16
    val PROGRAM: Seq[Int] = ReadAssembly.readBin("tests/simple/width.bin")
    test(new TopSim(PROGRAM, MEM_SIZE, FREQ, BAUD, LED_CNT)).withAnnotations(Seq(WriteVcdAnnotation)) { dut =>
      while(dut.io.regs(17).peekInt != 10) {
        dut.clock.step()
      }
      dut.io.regs(10).expect(0.S)
      //dut.io.regs(11).expect(-85.S)
      //dut.io.regs(12).expect(-4181.S)
      dut.io.regs(13).expect(-1412567125.S)
      //dut.io.regs(14).expect(171.S)
      //dut.io.regs(15).expect(61355.S)
      dut.io.regs(16).expect(-1410356309.S)
    }
  }
}
