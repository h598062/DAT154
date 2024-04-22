using System.ComponentModel.DataAnnotations;

namespace MVCDemo.Models {
    public class Student {
        public int Id { get; set; }
        public string? Name { get; set; }
        [DataType(DataType.Date)]
        public DateTime BirthDate { get; set; }
        public string? Country { get; set; }
        public string? Hobbies { get; set; }
    }

}
