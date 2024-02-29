using System;
using System.Drawing;
using System.Windows.Forms;

namespace _3___Form_Events {
    public partial class Form1 : Form {
        public Form1() {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e) {
            // check the Form1.Designer.cs file to see how this method is wired
            // up to the event published by the button.

            Random r = new();

            BackColor = Color.FromArgb(r.Next()%255, r.Next()%255, r.Next()%255);

            ((Button)sender).Height+=10;
            ((Button)sender).Top-=5;
        }
    }
}
