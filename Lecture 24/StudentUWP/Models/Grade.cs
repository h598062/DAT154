namespace StudentWeb.Models
{

    public enum GradeEnum {
        A, B, C, D, F
    }

    public class Grade {



        public int GradeID { get; set; }
        public int CourseID { get; set; }
        public int StudentID { get; set; }
        public GradeEnum? Grade_ { get; set; }

        public virtual Course Course { get; set; }
        public virtual Student Student { get; set; }



    }
}