using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using Microsoft.EntityFrameworkCore;
using Voluntary_Task_Solution.Models;

namespace Voluntary_Task_Solution.Pages.Students
{
    public class StudentModel : PageModel
    {
        private readonly Voluntary_Task_Solution.Models.Dat154Context _context;

        public string Search { get; set; } = string.Empty;
        public int AgeLow { get; set; } = 0;
        public int AgeHigh { get; set; } = int.MaxValue;


        public StudentModel(Voluntary_Task_Solution.Models.Dat154Context context)
        {
            _context = context;
        }

        public IList<Student> Student { get;set; } = default!;

        public async Task OnGetAsync()
        {
            
            Student = await _context.Students
                .OrderBy(s => s.Studentname)
                .ToListAsync();
        }

        public async Task OnPostAsync(string search = "", int minage = 0, int maxage = int.MaxValue) {

            search ??= string.Empty;

            Student = await _context.Students
                .Where(s => s.Studentname.Contains(search))
                .Where(s => s.Studentage >= minage)
                .Where(s => s.Studentage <= maxage)
                .OrderBy(s => s.Studentname)
                .ToListAsync();
        }
    }
}
