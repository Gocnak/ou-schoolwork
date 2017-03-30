/**
 * Created by nick on 3/27/17.
 */
public class NewtonSqrt {
    // Newton's algorithm to calculate the square root of a
    // with error less than e.
    public static double newton_sqrt(double a, double e) throws Exception
    {
        if (a <= 0.0 || e <= 0.0)
            throw new Exception("Your inputs are bad!");

        double x = 0.5 * a;
        double y = (x*x + a) / (2.0 * x);

        while (Math.abs(x-y) > e)
        {
            x = y;
            y = (x*x + a) / (2.0 * x);
        }

        return y;
    }
}
