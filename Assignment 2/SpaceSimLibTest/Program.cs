using SpaceSimLib;

class SpaceSimLibTest
{
    public static void Main()
    {
        var solarSystem = new Solarsystem();
        var solarSystemList = solarSystem.SolarSystem;


        foreach (SpaceObject obj in solarSystemList)
        {
            obj.Draw();
            if (obj is OrbitalBody orbitalBody)
            {
                Console.WriteLine($"{orbitalBody.Name} Position at 20 days: {orbitalBody.GetPosition(20)}");
            }
        }

        Console.WriteLine("Skriv inn navnet på et objekt i solsystemet du vil sjekke: ");
        String navn = Console.ReadLine();
        
        var treff = solarSystemList.Find(x => x.Name.ToLower() == navn.ToLower());
        if (treff is null)
        {
            Console.WriteLine($"Fant ikke noe objekt med navn {navn} i solsystemet, prøv igjen.");
            Console.WriteLine("Navn på objekt i solsystemet: ");
            navn = Console.ReadLine();
            treff = solarSystemList.Find(x => x.Name == navn);
        }

        Console.WriteLine("Skriv inn antall dager fram i tid du vil sjekke: ");
        String dager = Console.ReadLine();
        int dagerInt = Convert.ToInt32(dager);
        Console.WriteLine($"{treff.Name} Position at {dagerInt} days: {treff.GetPosition(dagerInt)}");
    }
}