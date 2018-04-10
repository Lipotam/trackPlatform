using System;
using System.Collections.Generic;
using System.Text;

namespace TrackPlatform.Tools
{
    public static class ConvertionTools
    {
        public static byte[] NumToArray<T>(this T num)
        {
            string speedString = Convert.ToString(num);
            return Encoding.ASCII.GetBytes(speedString);
        }

        public static int ArrayToNum(this byte[] array)
        {
            string num = Encoding.ASCII.GetString(array);
            return int.Parse(num);
        }

        public static int[] ArrayToArrayNums(this byte[] array, byte delim)
        {
            int pos;
            List<int> res = new List<int>();
            do
            {
                pos = Array.IndexOf(array, delim);

                byte[] toParse = (pos >= 0)
                    ? array.SubArray(0, pos)
                    : array;

                res.Add(toParse.ArrayToNum());

                array = array.SubArray(pos + 1);
            } while (pos >= 0);

            return res.ToArray();
        }
    }
}