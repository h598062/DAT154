using SpaceLib.SolarSystem;
using SpaceSim.SpaceLib;

// This .NET MAU application solves the task
// by using a canvas and do drawing calls.
// It would also have been possible to make
// a solution similar to the WPF one with 
// persistent shapes that are animated instead
// MAUI also have animation tools that can do
// circular motions, which is also a possible
// solution.


namespace SpaceSim.MAUI {
    public partial class SimPage : ContentPage {

        private readonly SolarSystem sim = new();
        private readonly Coordinator coordinator = new();

        private readonly SolarSystemVisual drawable;

        public SimPage() {
            InitializeComponent();



            drawable = new SolarSystemVisual() { Body = sim.Sun, Names = nameSwitch, Orbits = orbitSwitch };
            animationContainer.Drawable = drawable;

            foreach (Planet p in sim.Sun.Children) {
                coordinator.DoTick += p.CalculatePos;
                foreach (Planet m in p.Children) {
                    coordinator.DoTick += m.CalculatePos;
                }
            }


            // Filling the selection dropdown
            selectCentral.Items.Add(sim.Sun.Name);
            foreach (Planet p in sim.Sun.Children) {
                selectCentral.Items.Add(p.Name);
            }
            selectCentral.SelectedIndex = 0;
            selectCentral.SelectedIndexChanged += SelectCentral_SelectedIndexChanged;

            SizeChanged += RefreshView;
            coordinator.DoTick += (x) => animationContainer.Invalidate();

            SimSpeed = 1.0;



        }

        private void SelectCentral_SelectedIndexChanged(object sender, EventArgs e) {
            string name = (string)((Picker)sender).SelectedItem;

            Star x = sim.Sun.Children.Where(x => x.Name == name).FirstOrDefault(sim.Sun);

            drawable.Body = x;
            RefreshView(this, EventArgs.Empty);
        }

        // Recalculates centerpoint whenever the view changes, such as window
        // size being changed.
        private void RefreshView(object sender, EventArgs e) {
            Point center = new()
            {
                X = animationContainer.Width / 2,
                Y = animationContainer.Height / 2
            };
            drawable.Center = center;

            try {
                drawable.Scale = Math.Min(animationContainer.Height, animationContainer.Width) / (2 * drawable.Body.Children.Last().OrbitalRadius);
            } catch { }

            PlanetInfo.Text = drawable.Body.InfoText();

            animationContainer.Invalidate();
        }

        private double SimSpeed {
            set { 
                coordinator.Rate = value;
                double simspeed = 1000 / coordinator.Interval.Milliseconds * coordinator.Rate;
                SimSpeedInfo.Text = $"Sim Speed {simspeed:N2} days/second.";
            }
        }

        private void SlowDown(object sender, EventArgs e) {
            SimSpeed = coordinator.Rate /= 1.5;
        }

        private void SpeedUp(object sender, EventArgs e) {
            SimSpeed = coordinator.Rate *= 1.5;
        }

        private void ZoomIn(object sender, EventArgs e) {
            drawable.Scale *= 1.1;
        }

        private void ZoomOut(object sender, EventArgs e) {
            drawable.Scale /= 1.1;

        }
    }
}