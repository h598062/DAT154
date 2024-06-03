using SpaceSim.SpaceLib;

namespace SpaceLib {

    namespace SolarSystem {

        // This class represents our solar system. It is not a complete
        // model, but it does include all the classical planets
        // and many of their moons.
        // This is done in the library so all the client applications
        // can instanciate the same data easily.
        // Note that this is a specialized class for our solar system,
        // for examplke it assumes a single central star.
        public class SolarSystem {
            public Star Sun { get; private set; }

            public SolarSystem() {
                Sun = new Star("Sol") { Color = 0xFFFF66, SizeClass = 7 };

                InitChildren();
            }

            private void InitChildren() {

                Sun.AddChildren(
                [
                    new Planet("Mercury") {OrbitalPeriod = 87.97, OrbitalRadius = 57910, Color = 0x9999FF, SizeClass = 2},
                    new Planet("Venus") {OrbitalPeriod = 224.70, OrbitalRadius = 108200, Color = 0x999900, SizeClass = 3},
                    new Planet("Earth") {OrbitalPeriod = 365.26, OrbitalRadius = 149600, Color = 0x0000FF, SizeClass = 3},
                    new Planet("Mars") {OrbitalPeriod = 686.98, OrbitalRadius = 227940, Color = 0xCC6600, SizeClass = 3},
                    new Planet("Jupiter") {OrbitalPeriod = 4332.71, OrbitalRadius = 778330, Color = 0x916D43, SizeClass = 5},
                    new Planet("Saturn") {OrbitalPeriod = 10759.50, OrbitalRadius = 1429400, Color = 0xB3A12C, SizeClass = 5},
                    new Planet("Uranus") {OrbitalPeriod = 30685.00, OrbitalRadius = 2870990, Color = 0x99CCFF, SizeClass = 4},
                    new Planet("Neptune") {OrbitalPeriod = 60190.00, OrbitalRadius = 4504300, Color = 0x6666FF, SizeClass = 4},
                    new DwarfPlanet("Pluto") {OrbitalPeriod = 90550.00, OrbitalRadius = 5913520, Color = 0xCBC38E, SizeClass = 2}
                ]);


                // This is me being lazy, abusing the fact that I know the order of the list
                // above.
                // There are better ways to do this, one involves actually storing the above
                // in variables instead of initializing them in the list creation,
                // the other searching for the correct planets (LINQ, which we will look
                // at later, is perfect for this)
                Sun.Children[2].AddChildren(
                [
                    new Moon("Moon") {OrbitalPeriod = 27.32, OrbitalRadius = 384, Color = 0x808080}
                ]);

                Sun.Children[3].AddChildren(
                [
                    new Moon("Phobos") {OrbitalPeriod = 0.32, OrbitalRadius = 9, Color = 0x808080},
                    new Moon("Deimos") {OrbitalPeriod = 1.26, OrbitalRadius = 23, Color = 0x808080}
                ]);

                Sun.Children[4].AddChildren(
                [
                    new Moon("Metis") {OrbitalPeriod = 0.29, OrbitalRadius = 128, Color = 0x808080},
                    new Moon("Adrastea") {OrbitalPeriod = 0.30, OrbitalRadius = 129, Color = 0x808080},
                    new Moon("Amalthea") {OrbitalPeriod = 0.50, OrbitalRadius = 181, Color = 0x808080},
                    new Moon("Thebe") {OrbitalPeriod = 0.67, OrbitalRadius = 222, Color = 0x808080},
                    new Moon("Io") {OrbitalPeriod = 1.77, OrbitalRadius = 422, Color = 0x808080},
                    new Moon("Europa") {OrbitalPeriod = 3.55, OrbitalRadius = 671, Color = 0x808080},
                    new Moon("Ganymede") {OrbitalPeriod = 7.15, OrbitalRadius = 1070, Color = 0x808080},
                    new Moon("Callisto") {OrbitalPeriod = 16.69, OrbitalRadius = 1883, Color = 0x808080},
                    new Moon("Leda") {OrbitalPeriod = 238.72, OrbitalRadius = 11094, Color = 0x808080},
                    new Moon("Himalia") {OrbitalPeriod = 250.57, OrbitalRadius = 11480, Color = 0x808080},
                    new Moon("Lysithea") {OrbitalPeriod = 259.22, OrbitalRadius = 11720, Color = 0x808080},
                    new Moon("Elara") {OrbitalPeriod = 259.65, OrbitalRadius = 11737, Color = 0x808080},
                    new Moon("Ananke") {OrbitalPeriod = -631.00, OrbitalRadius = 21200, Color = 0x808080},
                    new Moon("Carme") {OrbitalPeriod = -692.00, OrbitalRadius = 22600, Color = 0x808080},
                    new Moon("Pasiphae") {OrbitalPeriod = -735.00, OrbitalRadius = 23500, Color = 0x808080},
                    new Moon("Sinope") {OrbitalPeriod = -758.00, OrbitalRadius = 23700, Color = 0x808080}
                ]);

                Sun.Children[5].AddChildren(
                [
                    new Moon("Pan") {OrbitalPeriod = 0.58, OrbitalRadius = 134, Color = 0x808080},
                    new Moon("Atlas") {OrbitalPeriod = 0.60, OrbitalRadius = 138, Color = 0x808080},
                    new Moon("Prometheus") {OrbitalPeriod = 0.61, OrbitalRadius = 139, Color = 0x808080},
                    new Moon("Pandora") {OrbitalPeriod = 0.63, OrbitalRadius = 142, Color = 0x808080},
                    new Moon("Epimetheus") {OrbitalPeriod = 0.69, OrbitalRadius = 151, Color = 0x808080},
                    new Moon("Janus") {OrbitalPeriod = 0.69, OrbitalRadius = 151, Color = 0x808080},
                    new Moon("Mimas") {OrbitalPeriod = 0.94, OrbitalRadius = 186, Color = 0x808080},
                    new Moon("Enceladus") {OrbitalPeriod = 1.37, OrbitalRadius = 238, Color = 0x808080},
                    new Moon("Tethys") {OrbitalPeriod = 1.89, OrbitalRadius = 295, Color = 0x808080},
                    new Moon("Telesto") {OrbitalPeriod = 1.89, OrbitalRadius = 295, Color = 0x808080},
                    new Moon("Calypso") {OrbitalPeriod = 1.89, OrbitalRadius = 295, Color = 0x808080},
                    new Moon("Dione") {OrbitalPeriod = 2.74, OrbitalRadius = 377, Color = 0x808080},
                    new Moon("Helene") {OrbitalPeriod = 2.74, OrbitalRadius = 377, Color = 0x808080},
                    new Moon("Rhea") {OrbitalPeriod = 4.52, OrbitalRadius = 527, Color = 0x808080},
                    new Moon("Titan") {OrbitalPeriod = 15.95, OrbitalRadius = 1222, Color = 0x808080},
                    new Moon("Hyperion") {OrbitalPeriod = 21.28, OrbitalRadius = 1481, Color = 0x808080},
                    new Moon("Iapetus") {OrbitalPeriod = 79.33, OrbitalRadius = 3561, Color = 0x808080},
                    new Moon("Phoebe") {OrbitalPeriod = -550.48, OrbitalRadius = 12952, Color = 0x808080}
                ]);

                Sun.Children[6].AddChildren(
                [
                    new Moon("Cordelia") {OrbitalPeriod = 0.34, OrbitalRadius = 50, Color = 0x808080},
                    new Moon("Ophelia") {OrbitalPeriod = 0.38, OrbitalRadius = 54, Color = 0x808080},
                    new Moon("Bianca") {OrbitalPeriod = 0.43, OrbitalRadius = 59, Color = 0x808080},
                    new Moon("Cressida") {OrbitalPeriod = 0.46, OrbitalRadius = 62, Color = 0x808080},
                    new Moon("Desdemona") {OrbitalPeriod = 0.47, OrbitalRadius = 63, Color = 0x808080},
                    new Moon("Juliet") {OrbitalPeriod = 0.49, OrbitalRadius = 64, Color = 0x808080},
                    new Moon("Portia") {OrbitalPeriod = 0.51, OrbitalRadius = 66, Color = 0x808080},
                    new Moon("Rosalind") {OrbitalPeriod = 0.56, OrbitalRadius = 70, Color = 0x808080},
                    new Moon("Belinda") {OrbitalPeriod = 0.62, OrbitalRadius = 75, Color = 0x808080},
                    new Moon("Puck") {OrbitalPeriod = 0.76, OrbitalRadius = 86, Color = 0x808080},
                    new Moon("Miranda") {OrbitalPeriod = 1.41, OrbitalRadius = 130, Color = 0x808080},
                    new Moon("Ariel") {OrbitalPeriod = 2.52, OrbitalRadius = 191, Color = 0x808080},
                    new Moon("Umbriel") {OrbitalPeriod = 4.14, OrbitalRadius = 266, Color = 0x808080},
                    new Moon("Titania") {OrbitalPeriod = 8.71, OrbitalRadius = 436, Color = 0x808080},
                    new Moon("Oberon") {OrbitalPeriod = 13.46, OrbitalRadius = 583, Color = 0x808080},
                    new Moon("Caliban") {OrbitalPeriod = -580.00, OrbitalRadius = 7169, Color = 0x808080},
                    new Moon("Stephano") {OrbitalPeriod = -674.00, OrbitalRadius = 7948, Color = 0x808080},
                    new Moon("Sycorax") {OrbitalPeriod = -1289.00, OrbitalRadius = 12213, Color = 0x808080},
                    new Moon("Prospero") {OrbitalPeriod = -2019.00, OrbitalRadius = 16568, Color = 0x808080},
                    new Moon("Setebos") {OrbitalPeriod = -2239.00, OrbitalRadius = 17681, Color = 0x808080}
                ]);

                Sun.Children[7].AddChildren(
                [
                    new Moon("Naiad") {OrbitalPeriod = 0.29, OrbitalRadius = 48, Color = 0x808080},
                    new Moon("Thalassa") {OrbitalPeriod = 0.31, OrbitalRadius = 50, Color = 0x808080},
                    new Moon("Despina") {OrbitalPeriod = 0.33, OrbitalRadius = 53, Color = 0x808080},
                    new Moon("Galatea") {OrbitalPeriod = 0.43, OrbitalRadius = 62, Color = 0x808080},
                    new Moon("Larissa") {OrbitalPeriod = 0.55, OrbitalRadius = 74, Color = 0x808080},
                    new Moon("Proteus") {OrbitalPeriod = 44166.00, OrbitalRadius = 118, Color = 0x808080},
                    new Moon("Triton") {OrbitalPeriod = -5.88, OrbitalRadius = 355, Color = 0x808080},
                    new Moon("Nereid") {OrbitalPeriod = 360.13, OrbitalRadius = 5513, Color = 0x808080}
                ]);

                Sun.Children[8].AddChildren(
                [
                    new Moon("Charon") {OrbitalPeriod = 6.39, OrbitalRadius = 20, Color = 0x808080},
                    new Moon("Nix") {OrbitalPeriod = 24.86, OrbitalRadius = 49, Color = 0x808080},
                    new Moon("Hydra") {OrbitalPeriod = 38.21, OrbitalRadius = 65, Color = 0x808080}
                ]);

            }
        }

    }
}
