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
        String fixedcolour = colour == "Grey" ? "Gray" : colour;
        var propertyInfo = typeof(Brushes).GetProperty(fixedcolour);
        if (propertyInfo != null)
        {
            return (Brush)propertyInfo.GetValue(null, null);
        }
        else
        {
            // Default to Black brush if the specified color name is not found
            return Brushes.Black;
        }
        /*return colour switch
        {
            "Yellow" => Brushes.Yellow,
            "Blue" => Brushes.Blue,
            "Red" => Brushes.Red,
            "Green" => Brushes.Green,
            "White" => Brushes.White,
            "Black" => Brushes.Black,
            "Brown" => Brushes.Brown,
            "Orange" => Brushes.Orange,
            "Grey" => Brushes.Gray,
            "Purple" => Brushes.Purple,
            "Pink" => Brushes.Pink,
            "Cyan" => Brushes.Cyan,
            "Magenta" => Brushes.Magenta,
            "Lime" => Brushes.Lime,
            "Teal" => Brushes.Teal,
            "Indigo" => Brushes.Indigo,
            "Maroon" => Brushes.Maroon,
            "Navy" => Brushes.Navy,
            "Olive" => Brushes.Olive,
            "Silver" => Brushes.Silver,
            "Aqua" => Brushes.Aqua,
            "Fuchsia" => Brushes.Fuchsia,
            "Lavender" => Brushes.Lavender,
            "DarkBrown" => Brushes.SaddleBrown,
            "DarkGoldenrod" => Brushes.DarkGoldenrod,
            "LightSkyBlue" => Brushes.LightSkyBlue,
            "DeepSkyBlue" => Brushes.DeepSkyBlue,
            _ => Brushes.Gray
        };*/
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