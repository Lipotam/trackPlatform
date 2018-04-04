using System;
using System.Text;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using TrackPlatform.Tools;

namespace Tests
{
    [TestClass]
    public class CrcTests
    {
        [TestMethod]
        public void Seq123456789()
        {
            string input = "123456789";
            ushort answer = 0x4B37;
            Assert.IsTrue(Crc16.Modbus(Encoding.ASCII.GetBytes(input)) == answer);
        }
    }
}
