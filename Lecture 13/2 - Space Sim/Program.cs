using System;
using System.Collections.Generic;
using SpaceSim;

class Astronomy {
    public static void Main() {
        List<SpaceObject> a = new List<SpaceObject>
        {
            new Star("Sun"),
            new Planet("Mercury"),
            new Planet("Venus"),
            new Planet("Terra"),
            new Moon("The Moon")
        };

        foreach (var s in a) {
            s.Draw();
        }

        Console.ReadLine();
    }
}

