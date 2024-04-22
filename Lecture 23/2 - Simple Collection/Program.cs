using System;
using System.Collections.Generic;
using System.Linq;

namespace Simple_Collection {
    class Program {
        static void Main() {

            SimpleCollection<string> s =
            [
                "John",
                "Mary",
                "Alice",
                "Tom"
            ];


            foreach (string st in s.OrderBy(x => x)) {
                Console.WriteLine(st);
            }

            Console.ReadKey();

        }
    }



    class SimpleCollection<T> : IEnumerable<T> {

        private readonly List<T> data = [];

        public void Add(T item) {
            data.Add(item);
        }

        public T Get(int index) {
            return data.ElementAt(index);
        }


        public IEnumerator<T> GetEnumerator() {
            foreach (T item in data)
                yield return item;
        }

        // We're only using the generic version of the class, so we can just leave
        // this method like this
        System.Collections.IEnumerator System.Collections.IEnumerable.GetEnumerator() {
            throw new NotImplementedException();
        }
    }
}

