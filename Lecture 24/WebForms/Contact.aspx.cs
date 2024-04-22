using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace WebForms
{
    public partial class Contact : Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

            if(IsPostBack)
            {
                Validate();

                if(IsValid)
                {
                    Button1.BackColor = System.Drawing.Color.Green;
                } else
                {
                    Button1.BackColor = System.Drawing.Color.Red;
                }
            }



        }

        protected void Button1_Click(object sender, EventArgs e)
        {
            Label1.Text = TextBox1.Text;

        }
    }
}