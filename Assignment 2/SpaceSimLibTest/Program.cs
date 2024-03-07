using SpaceSimLib;

class SpaceSimLibTest
{
    public static void Main()
    {
        List<SpaceObject> solarSystem = new List<SpaceObject>();
        Star sun = new Star("The Sun", 1392000, "Yellow");

        Planet mercury = new Planet("Mercury", 4879, "Grey", sun, 87.97f, 57910);

        Planet venus = new Planet("Venus", 12104, "Yellow", sun, 224.7f, 108200);

        Planet earth = new Planet("Earth", 12756, "Blue", sun, 365.26f, 149600);
        Moon moon = new Moon("The Moon", 3475, "Grey", earth, 27.32f, 384);

        Planet mars = new Planet("Mars", 6792, "Red", sun, 686.98f, 227940);
        Moon phobos = new Moon("Phobos", 22, "Grey", mars, 0.32f, 9);
        Moon deimos = new Moon("Deimos", 12, "Grey", mars, 1.26f, 23);

        Planet jupiter = new Planet("Jupiter", 142984, "Brown", sun, 4332.71f, 778330);
        Moon io = new Moon("Io", 3643, "Yellow", jupiter, 1.77f, 422);
        Moon europa = new Moon("Europa", 3122, "White", jupiter, 3.55f, 671);
        Moon ganymede = new Moon("Ganymede", 5262, "White", jupiter, 7.15f, 1070);
        Moon callisto = new Moon("Callisto", 4821, "White", jupiter, 16.69f, 1883);

        Planet saturn = new Planet("Saturn", 120536, "Brown", sun, 10759.5f, 1429400);
        Moon titan = new Moon("Titan", 5150, "Brown", saturn, 15.95f, 1221);
        Moon phoebe = new Moon("Phoebe", 220, "Brown", saturn, 550.48f, 12952);

        Planet uranus = new Planet("Uranus", 51118, "Blue", sun, 30685f, 2870990);

        Planet neptune = new Planet("Neptune", 49528, "Blue", sun, 60190f, 4504300);

        DwarfPlanet eris = new DwarfPlanet("Eris", 2326, "Brown", sun, 203830, 149597);
        DwarfPlanet ceres = new DwarfPlanet("Ceres", 945, "Brown", sun, 1680, 413700);
        DwarfPlanet pluto = new DwarfPlanet("Pluto", 2370, "Brown", sun, 90520, 5913520);


        Asteroid pallas = new Asteroid("Pallas", 544, "Grey", sun, 1680, 413700);


        solarSystem.Add(sun);
        solarSystem.Add(mercury);
        solarSystem.Add(venus);
        solarSystem.Add(earth);
        solarSystem.Add(moon);
        solarSystem.Add(mars);
        solarSystem.Add(phobos);
        solarSystem.Add(deimos);
        solarSystem.Add(jupiter);
        solarSystem.Add(io);
        solarSystem.Add(europa);
        solarSystem.Add(ganymede);
        solarSystem.Add(callisto);
        solarSystem.Add(saturn);
        solarSystem.Add(titan);
        solarSystem.Add(phoebe);
        solarSystem.Add(uranus);
        solarSystem.Add(neptune);
        solarSystem.Add(ceres);
        solarSystem.Add(pluto);
        solarSystem.Add(eris);
        solarSystem.Add(pallas);


        foreach (SpaceObject obj in solarSystem)
        {
            obj.Draw();
            if (obj is OrbitalBody orbitalBody)
            {
                Console.WriteLine($"{orbitalBody.Name} Position at 20 days: {orbitalBody.GetPosition(20)}");
            }
        }

        Console.WriteLine("Skriv inn navnet på et objekt i solsystemet du vil sjekke: ");
        String navn = Console.ReadLine();
        var treff = solarSystem.Find(x => x.Name == navn);
        if (treff is null)
        {
            Console.WriteLine($"Fant ikke noe objekt med navn {navn} i solsystemet, prøv igjen.");
            Console.WriteLine("Navn på objekt i solsystemet: ");
            navn = Console.ReadLine();
            treff = solarSystem.Find(x => x.Name == navn);
        }

        Console.WriteLine("Skriv inn antall dager fram i tid du vil sjekke: ");
        String dager = Console.ReadLine();
        int dagerInt = Convert.ToInt32(dager);
        Console.WriteLine($"{treff.Name} Position at {dagerInt} days: {treff.GetPosition(dagerInt)}");
    }
}