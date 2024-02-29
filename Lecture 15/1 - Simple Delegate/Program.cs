using System;

namespace SimpleDelegate {

    delegate void delegateTest();

    class A {
        public delegateTest t;

        public A() {
            Console.WriteLine("Adding Method B to delegate");
            t += B;
            t();
            Console.WriteLine("----------------------------------");

            Console.WriteLine("Adding B again");
            t += B;
            t();
            Console.WriteLine("----------------------------------");

            Console.WriteLine("Adding Method C to delegate");
            t += C;
            t();
            Console.WriteLine("----------------------------------");

            Console.WriteLine("Adding B yet again");
            t += B;
            t();
            Console.WriteLine("----------------------------------");

            Console.WriteLine("Removing Method B from delegate");
            t -= B;
            t();
            Console.WriteLine("----------------------------------");

            Console.WriteLine("Removing Method B from delegate again");
            t -= B;
            t();
            Console.WriteLine("----------------------------------");

        }
        public void B() {
            System.Console.WriteLine("Hi! I am 'b'.");
        }

        public void C() {
            System.Console.WriteLine("Howdy, 'c' here.");
        }
    }



    class Program {
        static void Main() {
            new A();
        }
    }
}
