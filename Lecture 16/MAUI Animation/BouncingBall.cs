namespace MAUI_Animation {
    internal class BouncingBall : IDrawable {

        public Point Pos { get; set; } = new(0, 0);
        public Point Movement { get; set; } = new(5,5);

        public void Draw(ICanvas canvas, RectF dirtyRect) {

            canvas.FillColor = Colors.DarkBlue;
            canvas.FillCircle(Pos, 5.0);


        }
    }
}
