using System;
using System.Collections.Generic;

namespace Lambda {
    public delegate bool NumberProcess(int x);
    class Program {
        static void Main() {

            int[] num = { 1, 2, 3, 4, 5, 6 };

            List<int> processed = ProcessArray(num, (x) => { return x % 3 == 0; });


            foreach (int n in processed)
            {
                System.Console.WriteLine("{0} matches criteria", n);
            }
            Console.ReadLine();

        }

        public static List<int> ProcessArray(int[] arr, Predicate<int> numbers) {
            List<int> l = new();

            foreach (int n in arr)
            {
                if (numbers(n))
                {
                    l.Add(n);
                }
            }

            return l;
        }
    }

}
