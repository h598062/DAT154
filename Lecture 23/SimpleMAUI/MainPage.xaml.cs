using EFCore.Models;
using Microsoft.EntityFrameworkCore;

namespace SimpleMAUI {
    public partial class MainPage : ContentPage {

        private readonly dat154Context dx = new();

        public MainPage() {
            InitializeComponent();


            dx.Courses.Load();

            // Binds the list of courses to the GUI component
            col.ItemsSource = dx.Courses.Local;


        }


    }
}