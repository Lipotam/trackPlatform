using System;
using System.Text;

namespace TrackPlatform.Tools
{
    public static class ArrayTools
    {
        public static T[] SubArray<T>(this T[] data, int index, int length)
        {
            T[] result = new T[length];
            Array.Copy(data, index, result, 0, length);
            return result;
        }
        public static T[] Add<T>(this T[] data, T elem, int pos)
        {
            T[] result = new T[data.Length + 1];
            Array.Copy(data, 0, result, 0, pos);
            Array.Copy(data, pos, result, pos + 1, data.Length - pos);
            data[pos] = elem;
            return result;
        }

        public static T[] Add<T>(this T[] data, T[] right, int pos)
        {
            T[] result = new T[data.Length + right.Length];
            Array.Copy(data, 0, result, 0, pos);
            Array.Copy(right, 0, result, 0, right.Length);
            Array.Copy(data, pos, result, pos + right.Length, data.Length - pos);
            return result;
        }

        public static T[] Concat<T>(this T[] data, T right)
        {
            return data.Add(right, data.Length);
        }

        public static T[] Concat<T>(this T[] data, T[] right)
        {
            return data.Add(right, data.Length);
        }

        public static byte[] NumToArray<T>(this T num)
        {
            string speedString = Convert.ToString(num);
            return Encoding.ASCII.GetBytes(speedString);
        }
    }
}