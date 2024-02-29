namespace MAUI_Animation {
    public partial class MainPage : ContentPage {

        private readonly BouncingBall ball = new();

        public MainPage() {
            InitializeComponent();

            anim.Drawable = ball;


            IDispatcherTimer t = Application.Current.Dispatcher.CreateTimer();
            t.Interval = TimeSpan.FromMilliseconds(100);
            t.Tick += DoAnimate;
            t.Start();


        }

        private void DoAnimate(object sender, EventArgs e) {
            ball.Pos = new(ball.Pos.X + ball.Movement.X, ball.Pos.Y + ball.Movement.Y);

            Random r = new();
            double delta = r.NextDouble() + 0.5;
            if (ball.Pos.X <= 0) ball.Movement = new(Math.Abs(ball.Movement.X) + delta, ball.Movement.Y);
            if (ball.Pos.X >= anim.Width) ball.Movement = new(-(Math.Abs(ball.Movement.X) + delta), ball.Movement.Y);
            if (ball.Pos.Y <= 0) ball.Movement = new(ball.Movement.X,Math.Abs(ball.Movement.X) + delta);
            if (ball.Pos.Y >= anim.Height) ball.Movement = new(ball.Movement.X ,- (Math.Abs(ball.Movement.Y) + delta));



            anim.Invalidate();
        }
    }
}