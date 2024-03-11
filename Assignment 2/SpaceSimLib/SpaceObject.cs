using System.Numerics;

namespace SpaceSimLib
{
    /// <summary>
    /// An object in space.
    /// </summary>
    public abstract class SpaceObject
    {
        public String Name { get; }
        public long DiameterKm { get; }
        public string Colour { get; }

        protected SpaceObject(String name, long diameterKm, String colour)
        {
            this.Name = name;
            this.DiameterKm = diameterKm;
            this.Colour = colour;
        }

        public virtual void Draw()
        {
            Console.WriteLine($"{Name} ({DiameterKm} km) - {Colour}");
        }
        
        public abstract Vector2 GetPosition(float timeDays);
        
    }


    /// <summary>
    /// Any object that orbits another object.
    /// </summary>
    public abstract class OrbitalBody : SpaceObject
    {
        public SpaceObject Orbiting { get; }
        public float OrbitalPeriodDays { get; }

        /// <summary>
        /// Orbital radius in thousands of kilometers. 5 = 5000 km.
        /// </summary>
        public long OrbitalRadiuskKm { get; }

        protected OrbitalBody(String name, long diameterKm, String colour,
            SpaceObject orbiting, float orbitalPeriodDays, long orbitalRadiuskKm) :
            base(name, diameterKm, colour)
        {
            this.Orbiting = orbiting;
            this.OrbitalPeriodDays = orbitalPeriodDays;
            this.OrbitalRadiuskKm = orbitalRadiuskKm;
        }

        /// <summary>
        /// Get the position of the object at a given time.
        /// </summary>
        /// <param name="timeDays"></param>
        /// <returns></returns>
        public override Vector2 GetPosition(float timeDays)
        {
            float angle = timeDays / OrbitalPeriodDays * 2 * (float)Math.PI;
            return new Vector2((float)Math.Cos(angle) * OrbitalRadiuskKm,
                (float)Math.Sin(angle) * OrbitalRadiuskKm);
        }

        public override void Draw()
        {
            base.Draw();
            Console.Write(" - Orbiting: ");
            Orbiting.Draw();
        }
    }

    /// <summary>
    /// The central object in a solar system.
    /// </summary>
    public class Star : SpaceObject
    {
        public Star(String name, long diameterKm, String colour) :
            base(name, diameterKm, colour)
        {
        }

        public override void Draw()
        {
            Console.Write("Star: ");
            base.Draw();
        }
        
        public override Vector2 GetPosition(float timeDays)
        {
            return new Vector2(0, 0);
        }
    }

    /// <summary>
    /// A large Solar System Body that orbits a Star.
    /// </summary>
    public class Planet : OrbitalBody
    {
        public Planet(String name, long diameterKm, String colour, Star orbiting,
            float orbitalPeriodDays, long orbitalRadiuskKm) :
            base(name, diameterKm, colour, orbiting, orbitalPeriodDays, orbitalRadiuskKm)
        {
        }

        public override void Draw()
        {
            Console.Write("Planet: ");
            base.Draw();
        }
    }

    /// <summary>
    /// A natural satellite orbiting a planet.
    /// </summary>
    public class Moon : OrbitalBody
    {
        public Moon(String name, long diameterKm, String colour, Planet orbiting,
            float orbitalPeriodDays, long orbitalRadiuskKm) :
            base(name, diameterKm, colour, orbiting, orbitalPeriodDays, orbitalRadiuskKm)
        {
        }

        public override void Draw()
        {
            Console.Write("Moon: ");
            base.Draw();
        }

        public override Vector2 GetPosition(float timeDays)
        {
            return Orbiting.GetPosition(timeDays) + base.GetPosition(timeDays);
        }
    }

    /// <summary>
    /// Planet, but smaller
    /// </summary>
    public class DwarfPlanet : OrbitalBody
    {
        public DwarfPlanet(String name, long diameterKm, String colour,
            Star orbiting, float orbitalPeriodDays, long orbitalRadiuskKm) :
            base(name, diameterKm, colour, orbiting, orbitalPeriodDays, orbitalRadiuskKm)
        {
        }

        public override void Draw()
        {
            Console.Write("Dwarf Planet: ");
            base.Draw();
        }
    }


    /// <summary>
    /// An SSSB that mostly consists of rock and metal.
    /// </summary>
    public class Asteroid : OrbitalBody
    {
        public Asteroid(String name, long diameterKm, String colour, Star orbiting,
            float orbitalPeriodDays, long orbitalRadiuskKm) :
            base(name, diameterKm, colour, orbiting, orbitalPeriodDays, orbitalRadiuskKm)
        {
        }

        public override void Draw()
        {
            Console.Write("Asteroid: ");
            base.Draw();
        }
    }
}