using System;
using System.Collections.Generic;
using System.Linq;

namespace _1___Simple_LINQ_Query {
    class Program {
        static void Main() {
            List<string> l =
            [
                "Bob",
                "Alice",
                "Oscar",
                "Mike"
            ];

            foreach (string x in l.OrderBy(x => x)) {
                Console.WriteLine(x);
            }

            Console.ReadKey();
        }
    }
}
