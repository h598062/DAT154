using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;

namespace RazorPages.Pages
{
    public class DataModel : PageModel
    {

        public string GetData { get; set; } = "";
        public string PostData { get; set; } = "";


        public void OnGet(string input)
        {
            GetData = input;
            PostData = "Ikke en POST foresp�rsel";

        }

        public void OnPost(string input) {
            GetData = "Ikke en GET foresp�rsel";
            PostData = input;
        }
    }
}
