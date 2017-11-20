import java.util.Arrays;
import java.util.Comparator;
import java.util.List;
import java.util.Random;
import java.util.stream.Collectors;

public class JavaCode {

    static long SEED = 867530942069L;
    static Random r = new Random(SEED);

    private static List<Integer> NONRAND() {
        return Arrays.stream(new int[] {75, -18, 216, 21, -6, 352, 39, -68, -318, 182}).boxed().collect(Collectors.toList());
    }

    private static List<Integer> RANDOM()
    {
        return r.ints(10, -999, 999).boxed().collect(Collectors.toList());
    }

    public static void main(String... args) {
        System.out.println("Calling NONRAND...");
        List<Integer> nonrands = NONRAND();
        nonrands.sort(Comparator.naturalOrder());
        nonrands.forEach(System.out::println);

        System.out.println("Smallest number: " + nonrands.get(0));
        System.out.println("Largest number: " + nonrands.get(nonrands.size() - 1));
        System.out.println("Average: " + nonrands.stream().reduce(0, (integer, integer2) -> integer + integer2) / nonrands.size());

        System.out.println();

        System.out.println("Calling RANDOM...");
        List<Integer> rands = RANDOM();
        rands.forEach(System.out::println);
        rands.sort(Comparator.naturalOrder());

        System.out.println("Smallest number: " + rands.get(0));
        System.out.println("Largest number: " + rands.get(rands.size() - 1));
        System.out.println("Average: " + rands.stream().reduce(0, (integer, integer2) -> integer + integer2) / rands.size());

    }
}