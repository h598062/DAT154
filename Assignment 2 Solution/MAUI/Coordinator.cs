
namespace SpaceSim.MAUI {
    public class Coordinator {

        private readonly IDispatcherTimer timer;
        public double Time {get; private set;}
        public double Rate { get; set; }
        public TimeSpan Interval { get; } = TimeSpan.FromMilliseconds(50);


        // This is the event other methods should subscribe to
        public event Action<double> DoTick;

        public Coordinator() {
            Time = 0;
            Rate = 0.25;

            timer = Application.Current.Dispatcher.CreateTimer();
            timer.Interval = Interval;
            timer.Tick += Timer_Tick;
            timer.Start();

        }

        // This method fires each time the timer ticks,
        // and fires the DoTick event with the appropriate
        // Data.
        private void Timer_Tick(object sender, EventArgs e) {
            Time += Rate;
            DoTick?.Invoke(Time);
        }
    }
}
