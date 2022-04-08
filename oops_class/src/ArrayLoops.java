import java.util.Arrays;

public class ArrayLoops {
    public static void main(String[] args) {
        // basic();
        // average();
        // copy();
        twoDimensional();
    }

    static void basic() {
        int numbers[] = {1,2,3,4};
        // or int[] numbers = {1,2,3,4};
        // or int []numbers = {1,2,3,4};
        for (int number: numbers) {
            System.out.println(number);
        }

        for (int i=0; i<numbers.length; i++) {
            System.out.println(numbers[i]);
        }

        // declare array
        int[] myArray;
        // allocated memory
        myArray = new int[10];
    }

    static void copy() {
        int[] array = {1,2,3,4,5};
        // shallow copy (if one change other also change)
        int[] array1 = array;
        // Deep copy
        int[] array2 = Arrays.copyOf(array, array.length);

        System.out.println("Array: " + Arrays.toString(array));
        System.out.println("Array1: " + Arrays.toString(array1));
        System.out.println("Array2: " + Arrays.toString(array2));

        array1[2] = 100;
        System.out.println("Array: " + Arrays.toString(array));
        System.out.println("Array1: " + Arrays.toString(array1));
        System.out.println("Array2: " + Arrays.toString(array2));
    }

    static void average() {
        int[] array = {1,2,3,4,5,6,7,8,9,5,4,3,2,1,5,6};
        int sum = 0;
        for (int ele: array) {
            sum += ele;
        }
        double avg = (double)sum / (double)array.length;
        System.out.println("Array: " + Arrays.toString(array));
        System.out.println("Sum is: " + sum);
        System.out.println("Total number of elements: " + array.length);
        System.out.println("Average is: " + avg);
    }

    static void twoDimensional() {
        int[][] array = {
                {1,2,3,4},
                {5,6,7,8}
        };
        System.out.println(Arrays.deepToString(array));
    }
}
