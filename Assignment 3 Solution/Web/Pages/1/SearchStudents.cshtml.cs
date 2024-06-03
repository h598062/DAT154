using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using Microsoft.EntityFrameworkCore;
using Web.Models;

namespace Web.Pages._1
{
    public class SearchStudentsModel : PageModel
    {
        private readonly Web.Models.Dat154Context _context;

        public SearchStudentsModel(Web.Models.Dat154Context context)
        {
            _context = context;
        }

        public IList<Student> Student { get;set; } = default!;

        // Default method when the page loads simply loads
        // all the students into a list. The display logic is
        // handled by the cshtml file.
        public async Task OnGetAsync()
        {
            if (_context.Students != null)
            {
                Student = await _context.Students.ToListAsync();
            }
        }


        // The bindable proprty automatically maps to the searchStudent
        // form field in the cshtml file. This field contains the search string
        // submitted by the user, which is used by the method below
        // to find the right students.
        [BindProperty]
        public string SearchStudent { get; set; } = "";
        public async Task<IActionResult> OnPostSearchStudents() {

            
            if (_context.Students != null) {
                Student = await _context.Students.Where(s => s.Studentname.ToLower().Contains(SearchStudent.ToLower())).ToListAsync();
            }


            return Page();
        }

    }
}
