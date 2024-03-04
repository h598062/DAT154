using System;
namespace SpaceSimLib {
    public class SpaceObject {
        protected String name;
        public SpaceObject(String name) {
            this.name = name;
        }
        public virtual void Draw() {
            Console.WriteLine(name);
        }
    }
    public class Star : SpaceObject {
        public Star(String name) : base(name) { }
        public override void Draw() {
            Console.Write("Star : ");
            base.Draw();
        }
    }
    public class Planet : SpaceObject {
        public Planet(String name) : base(name) { }
        public override void Draw() {
            Console.Write("Planet: ");
            base.Draw();
        }
    }
    public class Moon : Planet {
        public Moon(String name) : base(name) { }
        public override void Draw() {
            Console.Write("Moon : ");
            base.Draw();
        }
    }
}