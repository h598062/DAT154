using SpaceLib.SolarSystem;
using SpaceSim.SpaceLib;

namespace SpaceSim {
    namespace ConsoleApp {
        internal class Program {
            static void Main(string[] args) {

                // Create a new instance of our solar system. The class itself
                // contains the initialization data with all the planets and moons
                SolarSystem system = new();

                // Start at time 0 unless the user says otherwise
                int time = 0;

                // We ask the user for the number of days since the start of the sim
                // Note that if the user just presses enter, that will result in day 0
                Console.Write("Please enter number of days: ");
                string? input = Console.ReadLine();
                int.TryParse(input, out time);

                // Asking the user for the name of the planet to 
                // show data for
                Console.Write("Please enter the name of a planet: ");
                input = Console.ReadLine();

                // If the user's input was blank, we print out data
                // for the entire solar system. Otherwise we look through
                // the planets untill we find the one specified.
                // Note that if the user types an invalid planet
                // the result is a blank printout.
                if (input == null || input.Length == 0) {
                    system.Sun.Write(time);
                } else {
                    foreach(Planet p in system.Sun.Children) {
                        if(p.Name.ToLower() == input.ToLower()) {
                            p.Write(time);
                        }
                    }
                }

            }
        }
    }
}