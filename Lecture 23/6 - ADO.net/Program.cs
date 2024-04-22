using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;
using System.Data.SqlClient;

namespace DBConnect {
    class Program {
        static void Main() {

            string host = "dat154.hvl.no,1443";
            string database = "dat154";
            string user = "dat154";
            string pass = "dat154";

            string connstr = $"Data Source={host};Initial Catalog={database};User ID={user};Password={pass}";

            using (SqlConnection conn = new SqlConnection(connstr)) {

                SqlDataReader rdr = null;

                conn.Open();

                SqlCommand cmd = new SqlCommand
                {
                    Connection = conn,
                    CommandText = "SELECT * FROM dbo.course"
                };

                rdr = cmd.ExecuteReader();

                while (rdr.Read())
                    Console.WriteLine(rdr[0]);

            }
            Console.ReadLine();
        }
    }
}