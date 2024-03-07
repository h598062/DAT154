using System;

namespace Coupling {
    class Program
    {
        static void Main()
        {

            A a = new A();

            a.CopyFiles("a.jpg", "b.txt", new B().ReportWriter);


            Console.ReadKey();

        }
    }

    public delegate void a_delg(string message);
    public class A {
        public a_delg d;

        public void CopyFiles(string file_src, string file_dest, a_delg x)
        {

           
            // Copy files......
            try {
                System.IO.File.Copy(file_src, file_dest, true);
            } catch (Exception e) {
                x($"Error copying the files: {e.Message}");
                return;
            }


            x($"File copy complete - {file_src} copied to {file_dest}");
        }


    }
    public class B
    {
        public void ReportWriter(string message)
        {
            System.Console.WriteLine(message);
        }
    }

}
