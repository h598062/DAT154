using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data.Entity;

namespace WebForms
{
    public partial class About : Page
    {

        dat154Entities dx = new dat154Entities();

        protected void Page_Load(object sender, EventArgs e)
        {

            dx.student.Load();

            GridView1.DataSource = dx.student.Local.Where(st => st.studentage > 30).OrderBy(st => st.studentname);
            GridView1.DataBind();

            var query = dx.course
                        .Join(dx.grade, course => course.coursecode, grade => grade.coursecode, (course, grade) => new { course.coursename, grade.studentid })
                        .Join(dx.student, item => item.studentid, stud => stud.id, (item, stud) => new { stud.studentname, item.coursename })
                        .Distinct()
                        .OrderBy(c => c.coursename)
                        .OrderBy(c => c.studentname);

            GridView2.DataSource = query.ToList();
            GridView2.DataBind();


        }
    }
}