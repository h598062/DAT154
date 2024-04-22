using Microsoft.AspNetCore.Mvc;

namespace MVCDemo.Controllers {
    public class DemoController : Controller {
        public IActionResult Index() {
            return View();
        }

        public IActionResult Welcome(string data, int num = 1) {

            ViewData["Message"] = data;
            ViewData["NumTimes"] = num;

            


            return View();

        }
    }
}
