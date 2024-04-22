using SpaceSim;

namespace Voluntary_Task {



    internal class Program {

        static void Main() {


            // For all these tasks, the idea is to figure out
            // how to do things with LINQ. There will be other
            // ways of managing to do the same, but the idea
            // of these are to help you learn LINQ.
            // As such, ALL data selection and prosessing
            // should be part of the LINQ query. You'll need a
            // foreach loop to actually write out the data from the
            // query, but this loop should do nothing but print the
            // data provided wholesale

            // For this task, use the Solar System Data, which is
            // already included in this project. Question 1 shows
            // an example to get you started.

            SolarSystem Sol = new();

            // 1. Print out a list of the names of all the planets

            /* The LINQ Query */
            var planetNames = Sol.Sun.Children.Select(p => new { p.Name });

            /* Printing using a foreach loop */
            System.Console.WriteLine("1. Planets");
            foreach (var p in planetNames) {
                Console.WriteLine(p);
            }
            System.Console.WriteLine();


            // 2. Print out the names of all the moons of Jupiter

            var moonsJupiter = Sol.Sun.Children.Where(p => p.Name.Equals("Jupiter"))
                                    .First().Children.Select(p => new { p.Name });

            System.Console.WriteLine("2. Moons of Jupiter");
            foreach (var p in moonsJupiter) {
                Console.WriteLine(p);
            }
            System.Console.WriteLine();


            // 3. Print out an ordered list of all the planets according
            //    to their Size (SizeClass). Include the name and the size
            //    only in the output

            var planetsBySize = Sol.Sun.Children.OrderBy(p => p.SizeClass)
                                    .Select(p => new { p.Name, p.SizeClass });

            System.Console.WriteLine("3. Planets by Size");
            foreach (var p in planetsBySize) {
                Console.WriteLine(p);
            }
            System.Console.WriteLine();


            // 4. Join this list containing textual descriptions of the size
            //    classes to the planets list, and print out a list similar
            //    to the one from 3., but now with the textual descriptions
            //    instead of the number
            var desc = new[] { 
                new { Size = 1, Text = "Tiny" },
                new { Size = 2, Text = "Small" },
                new { Size = 3, Text = "Medium" },
                new { Size = 4, Text = "Large" },
                new { Size = 5, Text = "Huge" },
            };

            var planetsByTextSize = Sol.Sun.Children.OrderBy(p => p.SizeClass)
                        .Join(desc, p => p.SizeClass, d => d.Size, (p, d) => new { p.Name, d.Text });
                        

            System.Console.WriteLine("4. Planets by Size");
            foreach (var p in planetsByTextSize) {
                Console.WriteLine(p);
            }
            System.Console.WriteLine();


            // 5. Print out a list that shows the name of the planet and the number
            //    of moons it has

            var planetMoonCount = Sol.Sun.Children.Select(p => new {p.Name, Moons = p.Children.Count });

            System.Console.WriteLine("5. Counting Moons");
            foreach (var p in planetMoonCount) {
                Console.WriteLine(p);
            }
            System.Console.WriteLine();


            // 6. Print out a list of all planets that has a moon starting with
            //    the letter "T". Show the number of such moonbs along with the
            //    name of the planet

            var planetTMoons = Sol.Sun.Children
                   .Where(p => p.Children.Any(m => m.Name[0] == 'T'))
                   .Select(p => new { p.Name, T_Moons = p.Children.Where(m => m.Name[0] == 'T').Count() }); ;



            System.Console.WriteLine("6. Planets with T-Moons");
            foreach (var p in planetTMoons) {
                Console.WriteLine(p);
            }
            System.Console.WriteLine();

        }
    }
}
