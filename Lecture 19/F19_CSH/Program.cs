using System.Diagnostics.CodeAnalysis;

namespace F19_CSH;

internal class Program
{
	static void Main(string[] args)
	{
		// CSharpFSharpEx();
		FuncEx._Main(args);
	}


	static void CSharpFSharpEx()
	{
		Console.WriteLine("C# and F# - Bad Weather days in Bergen");

		// Use F# model to get raindays objects
		var days = F19_FSH.Rain.raindays;
		foreach (var day in days)
		{
			Console.WriteLine($"Dato {day.date} Nedbor {day.mm} Vind {day.ms}");	
		}
	}

}
