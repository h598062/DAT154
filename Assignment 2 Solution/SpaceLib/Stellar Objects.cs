using System.Drawing;

namespace SpaceSim {
    namespace SpaceLib {

        // This class defines the core space object
        // which all the other classes inherit from
        // It is abstact to prevent it from being 
        // instansiated.
        // Note that the inheritance hiarchy here
        // is based on the behaviour of the classes
        // in the program, which is the right way to
        // handle inheritance, and not based on the
        // real world equivalents we model.
        public abstract class SpaceObject(string name) {

            public string Name { get; protected set; } = name;
            protected int indent = 0;
            public Point PositionAbsolute { get; protected set; } = new();
            public Point PositionRelative { get; protected set; }
            public int SizeClass { get; set; }

            public virtual void Write(int time = 0) {
                Console.WriteLine($"{new string('\t', indent)}{Name}");
            }
            public abstract void CalculatePos(double time);

            public override string ToString() {
                return Name;
            }

            public virtual string InfoText() {
                return Name;
            }
        }

        public class Star : SpaceObject {

            public List<Planet> Children { get; private set; }
            public int Color { get; set; }

            public Star(string name) : base(name) {
                Children = [];
                Color = 0x404040;
                SizeClass = 7;
            }
            public override void Write(int time = 0) {
                base.Write(time);
                CalculatePos(time);

                if (Children.Count > 0) {
                    Console.WriteLine($"{new string('\t', indent + 1)}Orbiting Bodies:");
                    foreach (var child in Children) {
                        child.Write(time);
                    }
                }

            }

            // This method allow us to easily add a range of
            // objects orbiting this one, and automatically
            // updatting their Parent without having to explicitly
            // state it in each object as we create it.
            public void AddChildren(List<Planet> children) {

                foreach (var child in children) {
                    child.Parent = this;
                }

                Children.AddRange(children);

            }

            public override void CalculatePos(double time) { }

            public override string InfoText() {
                return $@"{Name}
{Children.Count} planets";
            }

        }

        // Why do a planet inherit from a star? That sounds like
        // a bit of a stretch, right?
        // Well, in programming, remeber that inheritance is about
        // the behaviour, not the real-world equivalents. And for
        // this model, a planet do behave much like a star by the
        // fact that it is an astonomical body that can have other bodies
        // orbiting it (Stars have planets, planaets have moons).
        public class Planet : Star {
            public double OrbitalRadius { get; set; }
            public double OrbitalPeriod { get; set; }

            public SpaceObject? Parent { get; set; }

            public Planet(string name) : base(name) {
                indent = 2;
                SizeClass = 3;
            }

            public override void Write(int time = 0) {
                base.Write(time);
                Console.WriteLine($"{new string('\t', indent + 1)}Orbital Radius (in 1000km): {OrbitalRadius:N}");
                Console.WriteLine($"{new string('\t', indent + 1)}Orbital Period (in days): {OrbitalPeriod:N2}");
                Console.WriteLine($"{new string('\t', indent + 1)}Position in Space: {PositionAbsolute}");

            }

            // Calculates the position of the object in space
            // Note that it calculates two values, the absolute
            // value take the parent objects position into consideration
            // and is importen when we wish to position a moon that orbits
            // around a planet (that again orbits around a star) correctly.
            // The relative value is relative to the parent object
            public override void CalculatePos(double time) {
                double angle = 360 / OrbitalPeriod * time * Math.PI / 180;
                double x = OrbitalRadius * Math.Cos(angle);
                double y = OrbitalRadius * Math.Sin(angle);

                PositionAbsolute = new((int)x + Parent?.PositionAbsolute.X ?? 0, (int)y + Parent?.PositionAbsolute.Y ?? 0);
                PositionRelative = new((int)x, (int)y);

            }

            public override string InfoText() {
                return $@"{Name}
{Children.Count} moons
Orbital Radius: {OrbitalRadius} km
Orbital Period: {OrbitalPeriod} days";

            }
        }

        public class DwarfPlanet(string name) : Planet(name) {
            public override void Write(int time = 0) {
                base.Write(time);
            }
        }

        public class Moon : Planet {

            public Moon(string name) : base(name) {
                indent = 4;
                SizeClass = 1;
            }

            public override void Write(int time = 0) {
                base.Write(time);
            }
        }
    }

}