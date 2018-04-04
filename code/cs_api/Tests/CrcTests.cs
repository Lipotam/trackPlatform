using System;
using System.Text;
using NUnit.Framework;
using TrackPlatform.Tools;

namespace Tests
{
    [TestFixture]
    public class CrcTests
    {
        [Test]
        public void Seq123456789()
        {
            string input = "123456789";
            ushort answer = 0x4B37;
            AnySeq(input, answer);
        }

        [TestCase("1", 0x947E)]
        [TestCase("10", 0x3414)]
        [TestCase("123456789", 0x4B37)]
        [TestCase("FEEDCAFE", 0x4C98)]
        public void AnySeq(string input, int answer)
        {
            ushort res = Crc16.Modbus(Encoding.ASCII.GetBytes(input));
            Assert.IsTrue(res == answer, $"Message \"{input}\", res: {res:X4}, required: {answer:X4}");
        }
    }
}
