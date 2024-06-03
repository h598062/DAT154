using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using Microsoft.AspNetCore.Mvc.Rendering;
using Microsoft.EntityFrameworkCore;
using Web.Models;

namespace Web.Pages._2
{
    public class StudentsByCourseModel : PageModel
    {
        private readonly Web.Models.Dat154Context _context;

        public StudentsByCourseModel(Web.Models.Dat154Context context)
        {
            _context = context;
        }

        public IList<Student> Student { get;set; } = default!;
        public IList<Grade> Grade { get; set; } = default!;

        public List<SelectListItem> Courses { get; set; }
        
        // Default method on page load. Users haven't selected anything yet
        // in the combo box, so we just set up the filtered list which will
        // match the first item in the combo box
        // Note that we use Grade as the "Base" class here, because it is
        // convenient to go to both Course and Student from here
        // (Each grade contains only one student and one course, as opposed
        // to for example a student which contains a list of grades)
        public async Task OnGetAsync() {
            Courses = _context.Courses.Select(c => new SelectListItem
            {
                Value = c.Coursecode,
                Text = c.Coursename
            }).ToList();

            if (_context.Grades != null) {
                Grade = await _context.Grades
                    .Where(s => s.Coursecode == Courses.First().Value)
                    .ToListAsync();

                // EntityFramework does lazy loading to prevent more data being loaded than we
                // need. However, since the above query never even visited the student navigation
                // property, we need to load them as a separate action or the student names
                // will be blank on the webpage.
                Student = await _context.Students.Where(s => s.Grades.Any(g => g.Coursecode == Courses.First().Value)).ToListAsync();

            }

        }


        // When users select a value in the combobox and submit, it is
        // bound to the below Property. This property is used both
        // to set the correct item as selected in the combobox, as well
        // as search for the right students
        [BindProperty]
        public string CourseId { get; set; } = "";
        public async Task<IActionResult> OnPostSearchStudents() {

            Courses = _context.Courses.Select(c => new SelectListItem
            {
                Value = c.Coursecode,
                Text = c.Coursename
            }).ToList();

            Courses.Where(c => c.Value == CourseId).First().Selected = true;

            if (_context.Grades != null) {
                Grade = await _context.Grades
                    .Where(s => s.Coursecode == CourseId)
                    .ToListAsync();

                Student = await _context.Students.Where(s => s.Grades.Any(g => g.Coursecode == CourseId)).ToListAsync();
            }

            return Page();
        }
    }
}
