
namespace EFCore.Models {
    partial class Course {

        public override string ToString() {
            return $"{Coursecode} - {Coursename} ({Teacher})";
        }


    }
}