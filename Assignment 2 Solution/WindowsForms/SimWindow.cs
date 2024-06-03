using SpaceLib.SolarSystem;
using SpaceSim.SpaceLib;

namespace SpaceSim.WinForms {
    public partial class SimWindow : Form {

        private Point center = new();
        private readonly SolarSystem sim = new();
        private readonly Coordinator coordinator = new();
        private double scale = 1;
        private Star centralObject;
        private readonly CheckBox showOrbits;
        private readonly CheckBox showNames;

        public SimWindow() {
            InitializeComponent();

            // Makes sense to set the initial central object as the sun
            // This is the object that will be shown in the middle of the window
            centralObject = sim.Sun;

            // We need to recalculate scale when the window size changes,
            // so we subscribe to the Resize event
            this.Resize += ModelViewChanged;

            // We use the arrow keys to control the sim, so we
            // subscribe to the keydown event
            this.KeyDown += SimWindow_KeyDown;

            // Each object should recalculate it's own positionon each tick
            // (This was part of the assignment spesification)
            // This subscribes each object to the relevant event
            // Note that we assume a standard solar system here, with two
            // layers, planets orbits the sun, moons orbits planets.
            // Because the list we inherit in the space object is a list of planets
            // I still use the Planet class for the moons here, but 
            // polymorphism handles that neatly for us.
            // (The moons simply inherits the CalculatePos from Planet anyway)
            foreach (Planet p in sim.Sun.Children) {
                coordinator.DoTick += p.CalculatePos;
                foreach (Planet m in p.Children) {
                    coordinator.DoTick += m.CalculatePos;
                }
            }

            // Add the combobox to select the central object
            ComboBox selectCentral = new()
            {
                Width = 200,
                BackColor = Color.Black,
                ForeColor = Color.AntiqueWhite,
            };
            selectCentral.Items.Add(sim.Sun);
            selectCentral.Items.AddRange(sim.Sun.Children.ToArray());
            selectCentral.SelectedIndex = 0;
            selectCentral.SelectedIndexChanged += SelectCentral_SelectedIndexChanged;
            selectCentral.KeyDown += SimWindow_KeyDown;
            this.Controls.Add(selectCentral);

            // Checkbox for the orbits
            showOrbits = new()
            {
                Left = 200,
                Width = 150,
                Text = "Show Orbits",
                ForeColor = Color.AntiqueWhite,
                BackColor = Color.Black,
                Checked = false,
            };
            showOrbits.KeyDown += SimWindow_KeyDown;
            this.Controls.Add(showOrbits);

            // Checkbox for the planet names
            showNames = new()
            {
                Left = 350,
                Width = 150,
                Text = "Show Names",
                ForeColor = Color.AntiqueWhite,
                BackColor = Color.Black,
                Checked = false,
            };
            showNames.KeyDown += SimWindow_KeyDown;
            this.Controls.Add(showNames);

            // Call ModelViewChanged as this updates the scale based on window size
            ModelViewChanged(this, EventArgs.Empty);

            // Subscribes to the tick event to start the animation
            coordinator.DoTick += UpdateDrawing;
        }

   
        // Event handler for the ComboBox. Changes the central object when the
        // selected item in the ComboBox changes.
        private void SelectCentral_SelectedIndexChanged(object? sender, EventArgs e) {
            if (sender != null && (sender as ComboBox)?.SelectedItem != null) {
                centralObject = (Star)((ComboBox)sender).SelectedItem;
                ModelViewChanged(this, EventArgs.Empty);
                Invalidate();
            }
        }

        // Triggers a redraw each timer tick.
        private void UpdateDrawing(double time) {
            Invalidate();
        }

        // Handles keypresses
        private void SimWindow_KeyDown(object? sender, KeyEventArgs e) {
            e.Handled = true;
            switch (e.KeyCode) {
                case Keys.Up:
                    scale *= 1.1;
                    break;
                case Keys.Down:
                    scale /= 1.1;
                    break;
                case Keys.Left:
                    coordinator.Rate /= 1.2;
                    break;
                case Keys.Right:
                    coordinator.Rate *= 1.2;
                    break;
                default:
                    e.Handled = false;
                    break;
            }
            
            Invalidate();
        }

        // Calculate the scale of the simulation based on window size
        // This allow us to both have a sensible scaling at startup,
        // and also each time the central object changes or the window
        // is resized.
        private void ModelViewChanged(object? sender, EventArgs e) {
            center.X = this.ClientSize.Width / 2;
            center.Y = this.ClientSize.Height / 2;

            try {
                scale = this.ClientSize.Height / (2 * centralObject.Children.Last().OrbitalRadius);
            } catch {
                scale = 1;
            }

            Invalidate();
        }

        // Here we do our painting.
        protected override void OnPaint(PaintEventArgs e) {
            
            // We let the base class do any painting it may want first
            base.OnPaint(e);
            Graphics g = e.Graphics;

            // We want a black background
            g.Clear(Color.Black);

            // We want double buffering to avoid flickering
            this.DoubleBuffered = true;

            // Some informational text first
            double simspeed = 1000 / coordinator.Interval * coordinator.Rate;
            g.DrawString($"Sim Speed {simspeed:N5} days/second. Left/Right arrows to change", SystemFonts.DefaultFont, Brushes.AntiqueWhite, 0, 40);
            g.DrawString("Up/Down arrows to change zoom", SystemFonts.DefaultFont, Brushes.AntiqueWhite, 0, 65);




            // This loop calculates the screen position of each child of the main
            // central object and draws it on screen. The object already knows
            // it's position in space, but we need to scale it down to fit the
            // window and center it correctly
            foreach (Planet p in centralObject.Children) {
                int x = (int)(center.X + p.PositionRelative.X * scale);
                int y = (int)(center.Y + p.PositionRelative.Y * scale);

                // Due to the fact that we use size classes on the objects
                // and don't scale them as we zoom, we need to handle the case
                // of some child objects orbiting inside the parent object
                // when not zoomed close enough. The following code calculates
                // alpha transparency to fade these objects out
                double distCentres = p.OrbitalRadius * scale;
                double minDistanceFullAlpha = p.SizeClass * 5 + centralObject.SizeClass * 5;
                double minDistanceMinAlpha = (centralObject.SizeClass - 1) * 5;
                int alpha = distCentres > minDistanceFullAlpha ? 255 : (int)(255 * (distCentres - minDistanceMinAlpha) / (minDistanceFullAlpha - minDistanceMinAlpha));
                alpha = alpha < 0 ? 0 : alpha;
                alpha *= 0x01000000;

                // Note the color value here "p.Color | alpha"
                // The | is the binary or-operator and we often use this
                // when we combine things like flags into a single value
                // Here however, the Color in the object is stored without
                // an alpha component, so it only contains the lower 24 bits.
                // As you can see from the alpha variable above, I am only working
                // with the 8 highest (most significant) bits here, so when I or
                // these numbers together I apply the alpha to the color without
                // changing the color itself.
                Brush color = new SolidBrush(Color.FromArgb((int)(p.Color | alpha)));

                // Draws orbits if enabled
                if (showOrbits.Checked) {
                    int ox = center.X - (int)(p.OrbitalRadius * scale);
                    int oy = center.Y - (int)(p.OrbitalRadius * scale);
                    int ow = (int)(p.OrbitalRadius * scale * 2);

                    g.DrawEllipse(new Pen(color, 2), ox , oy, ow, ow);
                }

                // Draws object names if enabled
                if(showNames.Checked) {
                    g.DrawString(p.Name, SystemFonts.DefaultFont, color, x + p.SizeClass *5, y);
                }



                // Paints the actual object on screen
                g.FillEllipse(color, x - p.SizeClass*5, y - p.SizeClass*5, p.SizeClass*10, p.SizeClass*10);
            }

            // Draw the central object on screen. I draw this last so that it will appear on top
            // of anything partially inside it.
            g.FillEllipse(new SolidBrush(Color.FromArgb((int)(centralObject.Color | 0xFF000000))), center.X - centralObject.SizeClass*5, center.Y - centralObject.SizeClass * 5, centralObject.SizeClass * 10, centralObject.SizeClass * 10);



            // Draw the body information
            g.DrawString(centralObject.InfoText(), SystemFonts.DefaultFont,Brushes.AntiqueWhite, 10, this.ClientSize.Height - 100);

        }
    }

}