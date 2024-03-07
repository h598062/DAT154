using System.Timers;

namespace Inheritance {

    public class Door {

        public string Location { get; set; } = "In a hole in the wall";

        public virtual void Open() {
            IsOpen = true;
        }

        public virtual void Close() {
            IsOpen = false;
        }

        public bool IsOpen { get; private set; }
    }


    public class TimedDoor : Door {

        public event Action<Door> DoorAlarm;
        private readonly System.Timers.Timer Timer;

        public TimedDoor() {
            Timer = new()
            {
                Interval = 360000 // 5 mins
            };
            Timer.Elapsed += Timer_Elapsed;
        }

        private void Timer_Elapsed(object? sender, ElapsedEventArgs e) {
            DoorAlarm?.Invoke(this);
        }

        public override void Open() {
            Timer.Start();
            base.Open();
        }

        public override void Close() {
            Timer.Stop();
            base.Close();
        }


    }

}
