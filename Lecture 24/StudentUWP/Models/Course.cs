using Newtonsoft.Json;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations.Schema;

namespace StudentWeb.Models
{
    public class Course {

        [DatabaseGenerated(DatabaseGeneratedOption.None)]
        public int CourseID { get; set; }
        public string Title { get; set; }

        [JsonIgnore]
        public virtual ICollection<Grade> Grades { get; set; }


    }
}