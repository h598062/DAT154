using System;
using System.Text;


namespace Properties {
    class Program {
        static void Main() {

            // Standard traditional syntax
            Body sun = new Body("Sol");
            sun.Radius = 0;
            sun.Period = 0;

            // Using object initilaizers instead
            Body earth = new Body("Terra")
            {
                Period = 365,
                Radius = 150000000
            };
            sun[2] = earth;

            // And now with simplified "new" statement
            Body moon = new("The Moon") {Period = 28,Radius = 300000};
            earth[0] = moon;



            Body mercury = new Body("Mercury") { Period = 88, Radius = 57900000 };
            sun[0] = mercury;


            sun[1] = new Body("Venus") { Period = 225, Radius = 108208000 };

            Body mars = new Body("Mars") { Period = 687, Radius = 150000000 };
            mars[0] = new Body("Phobos") { Period = 8, Radius = 9377 };
            mars[1] = new Body("Deimos") { Period = 30, Radius = 23460 };

            sun[3] = mars;

            PrintWithChildren(sun);



        }

        static void PrintWithChildren(Body x, int level = 0) {

            if (level == 0) {
                Console.WriteLine($"{"Astronomical Body",-20}\tOrbital Velocity");
                Console.WriteLine($"=================\t================");
            }

            StringBuilder padding = new StringBuilder();
            for (int i = 0; i < level; i++) { padding.Append("  "); }
            Console.WriteLine($"{padding.ToString() + x.Name,-20}\t{x.Velocity,10:F2} km/day");


            // Current implementation don't allow me to fetch the actual list of children
            // I only have access to the indexer, which is why I used this less-than
            // optimal solution here.
            // Obviously, I could just have exposed the array directly through a property,
            // but I kept it this way to focus on the indexer. We'll explore better options
            // later in the course.
            for (int i = 0; i < 100; i++) {
                if (x[i] != null) {
                    PrintWithChildren(x[i], level + 1);
                } else {
                    break;
                }
            }


        }


    }
}
