namespace MAUI {
    public partial class MainPage : ContentPage {

        public MainPage() {
            InitializeComponent();
        }

        private void QuitButton_Click(object sender, EventArgs e) {
            Application.Current.Quit();
        }

        private void Button_Click(object sender, EventArgs e) {
            string txt = txtField.Text;

            if (txt.Length > 0) {
                byte r = (byte)(txt.Length * 5 % 255);
                byte g = (byte)(txt[..1].ToCharArray()[0] * 5 % 255);
                byte b = (byte)((r + g) % 255);

                Background = new SolidColorBrush(Color.FromRgb(r, g, b));

            }
        }
    }
}