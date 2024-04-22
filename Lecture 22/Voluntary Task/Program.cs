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

            /* Printing using a foreach loop. You should be able to use this 
             * exact loop for all the questions, except for replacing the
             * name of the list variable and the header text */
            System.Console.WriteLine("1. Planets");
            foreach (var p in planetNames) {
                Console.WriteLine(p);
            }
            System.Console.WriteLine();



            // 2. Print out the names of all the moons of Jupiter



            // 3. Print out an ordered list of all the planets according
            //    to their Size (SizeClass). Include the name and the size
            //    only in the output



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




            // 5. Print out a list that shows the name of the planet and the number
            //    of moons it has





            // 6. Print out a list of all planets that has a moon starting with
            //    the letter "T". Show the number of such moonbs along with the
            //    name of the planet



        }
    }
}
