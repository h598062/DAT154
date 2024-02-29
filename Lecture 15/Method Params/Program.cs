namespace Method_Params {
    internal class Program {

        
        // This sorting method do a slow and inefficient sort using two loops
        // This is done for simplicity to avoid letting the complexity of
        // the algorithm be the focus
        // The interesting part is that it takes is a delegate which holds the
        // method that is used to to the actual comparison part of the routine
        // allowing users to supply their own comparisons without rewriting the 
        // sort algorithm.
        // Right now it only supports strings of course, but that is easy
        // to expand upon by using generic types.
        public static void SortList(List<string> list, Func<string,string,bool> func) {
        
            for (int a = 0; a < list.Count; a++) {
                for(int b = 0;  b < list.Count; b++) {

                    if (func(list[a], list[b])) {
                        string s = list[a];
                        list[a] = list[b];
                        list[b] = s;
                        // The tree lines above can also be written as
                        //(list[a], list[b]) = (list[b], list[a]);
                    }

                }
            }

        }

        public static bool Alphabetical(string s1, string s2) {
            return s1.CompareTo(s2) < 0;
        }

        public static bool Length(string s1, string s2) {
            return s1.Length < s2.Length;
        }


        static void Main() {

            List<string> l =
            [
                "Banana",
                "Apple",
                "Pineapple",
                "Grape",
                "Bacon",
                "Melon"
            ];

            PrintList(l);
            SortList(l, Alphabetical);
            PrintList(l);
            SortList(l, Length);
            PrintList(l);


        }

        public static void PrintList(List<string> list) {
            foreach(string s in list) {
                Console.Write($"{s}, ");
            }
            Console.WriteLine();
        }
    }
}