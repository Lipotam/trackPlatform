using System;

namespace TrackPlatform.Tools
{
    public static class ArrayTools
    {
        #region SubArray

        public static T[] SubArray<T>(this T[] data, int index, int length)
        {
            T[] result = new T[length];
            Array.Copy(data, index, result, 0, length);
            return result;
        }

        public static T[] SubArray<T>(this T[] data, int index)
        {
            return data.SubArray(index, data.Length);
        }

        #endregion

        #region Add

        public static T[] Add<T>(this T[] data, T elem, int pos)
        {
            T[] result = new T[data.Length + 1];
            Array.Copy(data, 0, result, 0, pos);
            Array.Copy(data, pos, result, pos + 1, data.Length - pos);
            result[pos] = elem;
            return result;
        }

        public static T[] Add<T>(this T[] data, T[] right, int pos)
        {
            T[] result = new T[data.Length + right.Length];
            Array.Copy(data, 0, result, 0, pos);
            Array.Copy(right, 0, result, pos, right.Length);
            Array.Copy(data, pos, result, pos + right.Length, data.Length - pos);
            return result;
        }

        #endregion

        #region Concat

        public static T[] Concat<T>(this T[] data, T right)
        {
            return data.Add(right, data.Length);
        }

        public static T[] Concat<T>(this T[] data, T[] right)
        {
            return data.Add(right, data.Length);
        }

        #endregion
    }
}