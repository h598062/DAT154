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
        SolarSystem.Add(Sun);

        Planet mercury = new Planet("Mercury", 4879, "Grey", Sun, 87.97f, 57910);
        Planets.Add(mercury);
        
        Planet venus = new Planet("Venus", 12104, "Yellow", Sun, 224.7f, 108200);
        Planets.Add(venus);

        Planet earth = new Planet("Earth", 12756, "Blue", Sun, 365.26f, 149600);
        Planets.Add(earth);
        Moon moon = new Moon("The Moon", 3475, "Grey", earth, 27.32f, 384);
        Moons.Add(moon);

        Planet mars = new Planet("Mars", 6792, "Red", Sun, 686.98f, 227940);
        Planets.Add(mars);
        Moon phobos = new Moon("Phobos", 22, "Grey", mars, 0.32f, 9);
        Moons.Add(phobos);
        Moon deimos = new Moon("Deimos", 12, "Grey", mars, 1.26f, 23);
        Moons.Add(deimos);

        Planet jupiter = new Planet("Jupiter", 142984, "SaddleBrown", Sun, 4332.71f, 778330);
        Planets.Add(jupiter);
        Moon io = new Moon("Io", 3643, "Yellow", jupiter, 1.77f, 422);
        Moons.Add(io);
        Moon europa = new Moon("Europa", 3122, "White", jupiter, 3.55f, 671);
        Moons.Add(europa);
        Moon ganymede = new Moon("Ganymede", 5262, "White", jupiter, 7.15f, 1070);
        Moons.Add(ganymede);
        Moon callisto = new Moon("Callisto", 4821, "White", jupiter, 16.69f, 1883);
        Moons.Add(callisto);

        Planet saturn = new Planet("Saturn", 120536, "DarkGoldenrod", Sun, 10759.5f, 1429400);
        Planets.Add(saturn);
        Moon titan = new Moon("Titan", 5150, "Brown", saturn, 15.95f, 1221);
        Moons.Add(titan);
        Moon phoebe = new Moon("Phoebe", 220, "Brown", saturn, 550.48f, 12952);
        Moons.Add(phoebe);

        Planet uranus = new Planet("Uranus", 51118, "LightSkyBlue", Sun, 30685f, 2870990);
        Planets.Add(uranus);
        Moon titania = new Moon("Titania", 1578, "White", uranus, 8.71f, 436);
        Moons.Add(titania);

        Planet neptune = new Planet("Neptune", 49528, "DeepSkyBlue", Sun, 60190f, 4504300);
        Planets.Add(neptune);
        Moon triton = new Moon("Triton", 2706, "Gray", neptune, 5.88f, 354800);
        Moons.Add(triton);

        /*DwarfPlanet eris = new DwarfPlanet("Eris", 2326, "Brown", Sun, 203830, 149597);
        DwarfPlanets.Add(eris);

        DwarfPlanet ceres = new DwarfPlanet("Ceres", 945, "Brown", Sun, 1680, 413700);
        DwarfPlanets.Add(ceres);*/

        DwarfPlanet pluto = new DwarfPlanet("Pluto", 2370, "Brown", Sun, 90520, 5913520);
        DwarfPlanets.Add(pluto);
        Moon charon = new Moon("Charon", 1207, "Gray", pluto, 6.39f, 19571);
        Moons.Add(charon);


        /*Asteroid pallas = new Asteroid("Pallas", 544, "Grey", Sun, 1680, 413700);
        Asteroids.Add(pallas);*/


        
        
        

        
        
        
        SolarSystem.AddRange(Planets);
        SolarSystem.AddRange(DwarfPlanets);
        SolarSystem.AddRange(Moons);
        SolarSystem.AddRange(Asteroids);
        
    }
}