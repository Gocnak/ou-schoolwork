import org.junit.Before;

import static org.junit.Assert.*;

/**
 * Created by nick on 3/27/17.
 */
public class NewtonSqrtTest {


    double[] testA = {-10.0, 4.0, 64.0, -10.0, -10.0, -10.0, 0.0, 0.0, 0.0, 25.0, 25.0, 25.0, -1.0, -1.0, -1.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0};
    double[] testE = {0.0, 0.05, 0.05, -10.0, 0.0, 10.0, -10.0, 0, 10.0, -10.0, 0.0, 0.01, -1.0, 0.0, 1.0, -1.0, 0.0, 1.0, -1.0, 0.0, 1.0};

    // 0 means exception here
    double[] expected = {0, 2.0, 8.0, 0.0, 0.0, 0.0, 0.00, 0.0, 0.0, 0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.25};

    @org.junit.Test
    public void newton_sqrt() throws Exception {
        for (int i = 0; i < expected.length; i++)
        {
            try {
                assertEquals(expected[i], NewtonSqrt.newton_sqrt(testA[i], testE[i]), testE[i]);
            }
            catch (Exception e)
            {
                assertTrue(e instanceof NewtonSqrt.NewtonException);
            }
        }

    }

}