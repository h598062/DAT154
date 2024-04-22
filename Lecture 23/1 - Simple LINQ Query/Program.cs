using System;
using System.Collections.Generic;
using System.Linq;

namespace Simple_LINQ_Query {
    class Program {
        static void Main() {
            List<String> l =
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
