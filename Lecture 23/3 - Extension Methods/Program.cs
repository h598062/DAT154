using System;
using System.Collections.Generic;

namespace Extension_Methods {
    class Program {
        static void Main() {

            List<string> strings = ["Ann", "Johnn", "August", "Cleopatra", "Tim"];


            foreach (string s in strings) {
                Console.WriteLine(s.EightChars());
            }

            int num = -25;

            Console.WriteLine(num.RoundToNearest(47));
            Console.WriteLine(num.RoundToNearest(7));

            Console.WriteLine(5.RoundToNearest(4));
            Console.WriteLine(5.RoundToNearest(3));

            


            Console.ReadKey();

        }
    }


    public static class Ext {

        public static string EightChars(this string s) {
            while (s.Length < 8) {
                s += ".";
            }
                        
            return s[..8];
        }

        public static int RoundToNearest(this int i, int multiple) {

            return (i / multiple * multiple) + (Math.Abs(i)%multiple >= multiple/2 ? multiple*(i/Math.Abs(i)) : 0);


        }


    }
}
