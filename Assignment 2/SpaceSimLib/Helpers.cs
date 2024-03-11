using System.Windows.Media;

namespace SpaceSimLib;

public class Helpers
{
    public static float Map(float value, float fromLow, float fromHigh, float toLow, float toHigh)
    {
        // Map the value from the input range to the output range
        return (value - fromLow) * (toHigh - toLow) / (fromHigh - fromLow) + toLow;
    }

    public static Brush ColourSelector(String colour)
    {
        return colour switch
        {
            "Yellow" => Brushes.Yellow,
            "Blue" => Brushes.Blue,
            "Red" => Brushes.Red,
            "Green" => Brushes.Green,
            "White" => Brushes.White,
            "Black" => Brushes.Black,
            "Brown" => Brushes.Brown,
            _ => Brushes.Gray
        };
    }
    
    public static long MaxOrbit(SpaceObject obj)
    {
        long max = 0;
        foreach (var orbitalBody in obj.Orbiters)
        {
            if (orbitalBody.OrbitalRadiuskKm > max)
            {
                max = orbitalBody.OrbitalRadiuskKm;
            }
        }
        return max;
    }
    public static long MaxDiameter(SpaceObject obj)
    {
        long max = 0;
        foreach (var orbitalBody in obj.Orbiters)
        {
            if (orbitalBody.DiameterKm > max)
            {
                max = orbitalBody.DiameterKm;
            }
        }
        return max;
    }
}