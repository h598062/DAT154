using Newtonsoft.Json;
using StudentWeb.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.Web.Http;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

namespace StudentUWP
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainPage : Page
    {

        public MainPage()
        {
            this.InitializeComponent();
            UpdateList();
        }

        private readonly string baseURL = "http://localhost:50167/api/StudentAPI";
               
        public void UpdateList()
        {
            using (var client = new HttpClient())
            {
                var response = "";

                // Sets up an async task to fetch the list of users from the WEB api
                Task task = Task.Run(async () =>
                {
                    response = await client.GetStringAsync(new Uri($"{baseURL}"));
                });
                task.Wait();

                // Converts the json-formatted list we received to a proper list of student objects,
                // and binds them to the view directly.
                studentList.ItemsSource = JsonConvert.DeserializeObject<List<Student>>(response);

            }
        }

        private void BAdd_Click(object sender, RoutedEventArgs e)
        {
            Student s = new Student();
            s.Name = "Web API Demo Student";
            s.Address = "In the Database";


            using (var client = new HttpClient())
            {

                //Converts the student object to json and prepare for transmission
                var content = JsonConvert.SerializeObject(s);
                var data = new HttpStringContent(content, Windows.Storage.Streams.UnicodeEncoding.Utf8, "application/json");


                // transmits the student object
                var res = new HttpResponseMessage();
                Task task = Task.Run(async () =>
                {
                    res = await client.PostAsync(new Uri($"{baseURL}"), data);
                });
                task.Wait();


            }
            UpdateList();

        }

        private void BDel_Click(object sender, RoutedEventArgs e)
        {

            Student s = ((List<Student>)studentList.ItemsSource).Where(x => x.Name.Equals("Web API Demo Student")).FirstOrDefault();

            if (s != null)
            {

                using (var client = new HttpClient())
                {

                    // Sets up an async task to delete the student by id
                    Task task = Task.Run(async () =>
                    {
                        await client.DeleteAsync(new Uri($"{baseURL}/{s.ID}"));
                    });
                    task.Wait();

                }
                UpdateList();
            }

        }

        private void BModify_Click(object sender, RoutedEventArgs e)
        {
            Student s = ((List<Student>)studentList.ItemsSource).Where(x => x.Name.Equals("Web API Demo Student")).FirstOrDefault();

            if (s != null)
            {
                s.Address = "I have just moved.....";

                using (var client = new HttpClient())
                {

                    //Converts the student object to json and prepare for transmission
                    var content = JsonConvert.SerializeObject(s);
                    var data = new HttpStringContent(content, Windows.Storage.Streams.UnicodeEncoding.Utf8, "application/json");


                    // transmits the student object
                    var res = new HttpResponseMessage();
                    Task task = Task.Run(async () =>
                    {
                        res = await client.PutAsync(new Uri($"{baseURL}/{s.ID}"), data);
                    });
                    task.Wait();

                }
                UpdateList();

            }



        }

        private void bRefresh_Click(object sender, RoutedEventArgs e) {
            UpdateList();
        }
    }
}
