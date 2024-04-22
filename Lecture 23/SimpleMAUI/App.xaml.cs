namespace SimpleMAUI {
    public partial class App : Application {
        public App() {
            InitializeComponent();

            MainPage = new AppShell();
        }
    }
}