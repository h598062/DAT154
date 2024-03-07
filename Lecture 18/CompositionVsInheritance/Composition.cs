using System.Timers;

namespace Composition {

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

    public class TimerAlarm {

        public event Action<object> Alarm;
        public System.Timers.Timer Timer { get; private set; }
        public object Owner { get; set; }


        public TimerAlarm() {
            Timer = new()
            {
                Interval = 360000 // 5 mins
            };
            Timer.Elapsed += Timer_Elapsed;
        }

        private void Timer_Elapsed(object? sender, ElapsedEventArgs e) {
            Alarm?.Invoke(Owner);
        }

    }

    public class TimedDoor  {

        public required Door Door { get; set; }
        public required TimerAlarm Alarm { get; set; }

        public void Open() {
            Alarm.Timer.Start();
            Door.Open();
        }

        public void Close() {
            Alarm.Timer.Stop();
            Door.Close();
        }

    }


    public class TimedWindow {

        public required Door Window { get; set; }
        public required TimerAlarm Alarm { get; set; }

        public void Open() {
            Alarm.Timer.Start();
            Window.Open();
        }

        public void Close() {
            Alarm.Timer.Stop();
            Window.Close();
        }

    }


}
