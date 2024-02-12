
using static System.Console;

internal class F12
{
class Vehicle { }
class Car : Vehicle { }
class Bike : Vehicle { }
static void Main(string[] _)
{
    Vehicle[] a= new Vehicle[100];
    int iv=0, ch, nCars=0;
    do
    {
        Write("1=Car,2=Bike,0=Quit :"); 
        ch = Convert.ToInt32(ReadLine());
        if (ch == 1) a[iv++] = new Car();
        if (ch == 2) a[iv++] = new Bike();
    } while (ch != 0);

    
    for (int i=0; i < iv; i++)
    {
        Vehicle v = a[i];
        WriteLine(v.ToString());
        if (v is Car)
            nCars++;
    }
    WriteLine($"Cars: {nCars}");
}

}
