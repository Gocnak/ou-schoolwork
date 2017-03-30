import static org.junit.Assert.*;

/**
 * Created by nick on 3/27/17.
 */
public class NewtonSqrtTest {
    @org.junit.Test(expected = Exception.class)
    public void newton_sqrt() throws Exception {

        double[] testA = {};
        double[] testE = {};

        double[] expected = {};

        for (int i = 0 i < expected.length; i++)
        {
            assertEquals(NewtonSqrt.newton_sqrt(testA[i], testE[i]), expected[i], 0.01);
        }
    }

}