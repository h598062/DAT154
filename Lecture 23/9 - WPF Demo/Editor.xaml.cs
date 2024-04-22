using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Principal;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace _8___WPF_Demo {
    /// <summary>
    /// Interaction logic for Editor.xaml
    /// </summary>
    public partial class Editor : Window {

        private dat154Entities dx = new dat154Entities();

        public Editor() {
            InitializeComponent();
        }

        public Editor(dat154Entities context) : this() {
            dx = context;
        }

        public Editor(dat154Entities context, student s) :  this() {
            sid.Text = s.id.ToString();
            sname.Text = s.studentname;
            sage.Text = s.studentage.ToString();
        }

        private void AddButton_Click(object sender, RoutedEventArgs e) {

            student s = new student();
            s.id = int.Parse(sid.Text);
            s.studentname = sname.Text;
            s.studentage = int.Parse(sage.Text);

            dx.student.Add(s);

            dx.SaveChanges();
            sid.Text = sname.Text = sage.Text = "";



        }

        private void DeleteButton_Click(object sender, RoutedEventArgs e) {

            int id = int.Parse(sid.Text);
            student s = dx.student.Where(st => st.id == id).FirstOrDefault();

            if (s != null) {
                dx.student.Remove(s);
                dx.SaveChanges();
            }

            sid.Text = sname.Text = sage.Text = "";


        }

        private void ModifyButton_Click(object sender, RoutedEventArgs e) {

            int id = int.Parse(sid.Text);
            student s = dx.student.Where(st => st.id == id).FirstOrDefault();

            if (s != null) {

                if (!sage.Text.Equals("")) s.studentage = int.Parse(sage.Text);
                if (!sname.Text.Equals("")) s.studentname = sname.Text;

                dx.SaveChanges();
            }

            sid.Text = sname.Text = sage.Text = "";
        }
    }
}
