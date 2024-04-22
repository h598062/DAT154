using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Drawing;

namespace WebForms
{
    public partial class _Default : Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

            Label1.ForeColor = Color.White;
            Label1.Text = "Mandag";
            Label1.Font.Size = 24;
            Label1.BackColor = Color.Black;

        }
    }
}