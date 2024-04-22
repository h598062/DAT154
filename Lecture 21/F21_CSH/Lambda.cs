using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection.Metadata.Ecma335;
using System.Security.Cryptography.X509Certificates;
using static System.Console;
using static System.Math;

static class Lambda
{
    public static void _Main(string[] argv)
    {
      // Ex1();
      // Ex2();
       Ex3();

    }


    #region Ex1 - Delegate lambda intro
    static void Ex1()
    {     
        int n = 10;
        var f1 =  (int x) => x * x;
        WriteLine("Value x^2: " + f1(n));

        Func<int, int, int> f2 = (x, y) => x + y;
        WriteLine("Value 2 + 3 = " + f2(2, 3));

    }
    #endregion

    #region Ex 2 & 3
    public static List<T> Filter<T>(List<T> ls, Func<T, Boolean> fn)
    {
        var lsFilter = new List<T>();
        foreach (var e in ls)
             if (fn(e))
                lsFilter.Add(e);
        return lsFilter;                
    }
    #endregion 
    #region Ex2
    static void Ex2()
    {
        List<int> l = new () { 3, 7, 9, 12, 11, 19, 17, 3, 4, 1, 2, 3 };
        l.ForEach(e => Write(e.ToString() + ','));
        WriteLine();

        var l2 =Filter(l, x => x % 3 == 0);
        l2.ForEach(e => Write(e.ToString() + ','));
        WriteLine();

    }
    #endregion
    #region Ex3
    public record Student(string Name, double[] Kar); // .NET 9
    static void Ex3()
    {
        List<Student> l = new () {
              new Student("Bent", [2.1,3, 3 ]),
              new Student("Karen",[4, 3.2, 4.5]),
              new Student("Carol", [2.9, 3.1, 4]),
              new Student("Sue", [3, 4, 3.8 ]),
              };

        WriteLine("Alle");
        var fwrite = (Student o) => WriteLine($" {o.Name} {Math.Round(o.Kar.Average(),2)} ");
        l.ForEach(o => fwrite(o));

        // Compare function
        var fnFilter = (Student c) => c.Kar.Average() > 3.5;
        var lf = Filter(l, fnFilter);
        WriteLine("Filtrert - kommer inn på master");
        lf.ForEach(o => fwrite(o));
    }
    #endregion

    static string GetInfo<T>(T x) where T : notnull
    {
        return x.GetType() + " " + x.ToString();
    }

}


