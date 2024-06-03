using SpaceSim.SpaceLib;

namespace SpaceSim.MAUI {
    internal class SolarSystemVisual : IDrawable {

        public Star Body { get; set; }
        public double Scale { get; set; } = 1;
        public Point Center { get; set; } = new();

        public Switch Orbits { get; set; }
        public Switch Names { get; set; }


        public void Draw(ICanvas canvas, RectF dirtyRect) {

            canvas.FillColor = Colors.Black;
            canvas.FillRectangle(dirtyRect);

            foreach (Planet p in Body.Children) {

                // Calculate the position in the window for the object
                int x = (int)(Center.X + p.PositionRelative.X * Scale);
                int y = (int)(Center.Y + p.PositionRelative.Y * Scale);

                // Set up the fill color based on the color value in the space object
                // Note that this does not contain alpha value so we just add
                // alpha for full opacity (0xFF000000). If we didn't do this
                // it would treat them as having no opacity, thus being invisible.
                canvas.FillColor = Color.FromUint((uint)p.Color | 0xFF000000);


                // When you are zoomed out, some objects appear to orbit inside
                // the central star/planet. This is a consequence of using
                // fixed scaling for the objects and only scale the distances
                // but this is required as distances in space are vast and
                // planets are tiny in comparison
                // What we do here is to hide any object that isn't outside
                // the body it orbits.
                // Note that this causes them to simply "pop" into view when we zoom
                // close enough. This could be much prettier (see the WindowsForms solution
                // for another way of doing it, where I fade them in out), but it gets the job
                // done.
                if (!(Math.Abs(Center.X - x) < Body.SizeClass * 7 && Math.Abs(Center.Y - y) < Body.SizeClass * 7)) {
                    canvas.FillCircle(x, y, p.SizeClass * 5);

                    
                    // Draws orbits if enabled
                    if (Orbits.IsToggled) {
                        canvas.StrokeColor = Color.FromUint((uint)p.Color + 0x99000000);
                        canvas.DrawCircle(Center, p.OrbitalRadius * Scale);
                    }

                    // Draws object names if enabled
                    if (Names.IsToggled) {
                        canvas.FontColor = Color.FromUint((uint)p.Color + 0x99000000);
                        canvas.DrawString(p.Name, x + p.SizeClass*5, y+ p.SizeClass * 5, HorizontalAlignment.Left);
                        
                    }

                }
                
            }

            // Draw the center object last. This way it will overlap anything else
            canvas.FillColor = Color.FromUint((uint)Body.Color + 0xFF000000);
            canvas.FillCircle(Center, Body.SizeClass * 5.0);

        }


    }
}
