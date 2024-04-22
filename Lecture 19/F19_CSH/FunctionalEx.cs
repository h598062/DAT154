using System;
using static System.Console;
using System.Linq;
using System.Collections.Generic;
using System.Collections.Immutable;

public static class FuncEx
{
    public static void _Main(string[] args)
    {
        // PureEx();
         ImmutableExample();
        // PatternMatching();
        // LinqEx();
    }

    static int magicnumber = new Random().Next(100);
    static void PureEx()
    {
        static int X(int a, int b) => a + b;    //  Pure function
        static int Y(int a) => a + magicnumber; //  Unpure function

        WriteLine("Functional Concepts");
        WriteLine($" Pure {X(2, 4)}, Unpure {Y(5)}");
    }

    // Immutable stack
    static void ImmutableExample()
    {
        WriteLine("Imutable collection:");
        // Create an immutable list of strings
        ImmutableList<string> colors = ["Red", "Green", "Blue"];

        var colorsWithPink = colors.Add("pink");


        // Create a new immutable list by adding and removing items from the original list
        ImmutableList<string> colorsModified = colors.RemoveAt(1).Add("Orange");
        colorsModified.ForEach(x => WriteLine("    " + x));

        WriteLine("Orginal Colors With Pink:");
        colorsWithPink.ForEach(x => WriteLine("    " + x));
    }

    // Pattern Matching
    public enum Light { green, yellow, red };
    public record Car(int Speed, string Skilt);
    public record EmergencyCar(int Speed, string Alarmtype) : Car(Speed, "EMRG");
    static void PatternMatching()
    {
        WriteLine("Pattern Matching - Action Cross");
        var car = new Car(40, "SN12345");
        var police = new EmergencyCar(120, "Police");
        var ambulance = police with { Alarmtype = "Ambulance" };
        // police.Alarmtype = "Ambulance";

        WriteLine($"    {car}: {TodoInCross(car, Light.red)}");
        WriteLine($"    {police}: {TodoInCross(police, Light.red)}");
        WriteLine($"    {ambulance}: {TodoInCross(ambulance, Light.red)}");

        static string TodoInCross(Car car, Light light) // Pure
        {
            return (car, light) switch
            {
                (EmergencyCar ecar, _) => $"{ecar.Alarmtype} continue",
                ({ Speed: > 50 }, Light.red) => "Hardbreak and stopp",
                ({ Speed: < 50 }, Light.red or Light.yellow) => "Break and stop",
                ({ Speed: > 50 }, Light.yellow) => "Slow down and continue",
                (_, Light.green) => "Drive normally ",
                _ => "Error " // NOT throw new Exception("BANG??") if pure function
            };
        }
    }

    // Example - LINQ (Later just an example elegant functional programming)
    public static void LinqEx()
    {
        WriteLine("Even sqare numbers");
        // Declarative and beautiful1 ALL EVEN SQUARES
        var fwr = ((int x, int x2) t) => WriteLine($"    n: {t.x}  n2: {t.x2}");
        var feven = ((int x, int x2) t) => t.x % 2 == 0;
        var lst = Enumerable.Range(0, 20).ToList();
        lst.Select(x => (x, x * x)).Where(feven).ToList().ForEach(fwr);
    }

}