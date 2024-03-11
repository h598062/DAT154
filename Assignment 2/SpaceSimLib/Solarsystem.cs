namespace SpaceSimLib;

public class Solarsystem
{
    public List<SpaceObject> SolarSystem { get; private set; }
    public Star Sun { get; private set; }
    public List<Planet> Planets { get; private set; }
    public List<Moon> Moons { get; private set; }
    public List<DwarfPlanet> DwarfPlanets { get; private set; }
    public List<Asteroid> Asteroids { get; private set; }

    public Solarsystem()
    {
        SolarSystem = new List<SpaceObject>();
        Planets = new List<Planet>();
        Moons = new List<Moon>();
        DwarfPlanets = new List<DwarfPlanet>();
        Asteroids = new List<Asteroid>();
        
        Sun = new Star("The Sun", 1392000, "Yellow");

        Planet mercury = new Planet("Mercury", 4879, "Grey", Sun, 87.97f, 57910);

        Planet venus = new Planet("Venus", 12104, "Yellow", Sun, 224.7f, 108200);

        Planet earth = new Planet("Earth", 12756, "Blue", Sun, 365.26f, 149600);
        Moon moon = new Moon("The Moon", 3475, "Grey", earth, 27.32f, 384);

        Planet mars = new Planet("Mars", 6792, "Red", Sun, 686.98f, 227940);
        Moon phobos = new Moon("Phobos", 22, "Grey", mars, 0.32f, 9);
        Moon deimos = new Moon("Deimos", 12, "Grey", mars, 1.26f, 23);

        Planet jupiter = new Planet("Jupiter", 142984, "Brown", Sun, 4332.71f, 778330);
        Moon io = new Moon("Io", 3643, "Yellow", jupiter, 1.77f, 422);
        Moon europa = new Moon("Europa", 3122, "White", jupiter, 3.55f, 671);
        Moon ganymede = new Moon("Ganymede", 5262, "White", jupiter, 7.15f, 1070);
        Moon callisto = new Moon("Callisto", 4821, "White", jupiter, 16.69f, 1883);

        Planet saturn = new Planet("Saturn", 120536, "Brown", Sun, 10759.5f, 1429400);
        Moon titan = new Moon("Titan", 5150, "Brown", saturn, 15.95f, 1221);
        Moon phoebe = new Moon("Phoebe", 220, "Brown", saturn, 550.48f, 12952);

        Planet uranus = new Planet("Uranus", 51118, "Blue", Sun, 30685f, 2870990);

        Planet neptune = new Planet("Neptune", 49528, "Blue", Sun, 60190f, 4504300);

        /*DwarfPlanet eris = new DwarfPlanet("Eris", 2326, "Brown", Sun, 203830, 149597);
        DwarfPlanet ceres = new DwarfPlanet("Ceres", 945, "Brown", Sun, 1680, 413700);
        DwarfPlanet pluto = new DwarfPlanet("Pluto", 2370, "Brown", Sun, 90520, 5913520);


        Asteroid pallas = new Asteroid("Pallas", 544, "Grey", Sun, 1680, 413700);*/


        SolarSystem.Add(Sun);
        
        Planets.Add(mercury);
        Planets.Add(venus);
        Planets.Add(earth);
        Planets.Add(mars);
        /*Planets.Add(jupiter);*/
        /*Planets.Add(saturn);
        Planets.Add(uranus);
        Planets.Add(neptune);*/

        /*DwarfPlanets.Add(pluto);
        DwarfPlanets.Add(ceres);
        DwarfPlanets.Add(eris);*/
        
        Moons.Add(moon);
        Moons.Add(phobos);
        Moons.Add(deimos);
        Moons.Add(io);
        Moons.Add(europa);
        Moons.Add(ganymede);
        Moons.Add(callisto);
        Moons.Add(titan);
        Moons.Add(phoebe);
        
        /*Asteroids.Add(pallas);*/
        
        SolarSystem.AddRange(Planets);
        SolarSystem.AddRange(Moons);
        SolarSystem.AddRange(DwarfPlanets);
        SolarSystem.AddRange(Asteroids);
    }
}