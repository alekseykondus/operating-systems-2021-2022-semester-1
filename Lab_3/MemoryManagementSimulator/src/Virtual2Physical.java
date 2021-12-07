
public class Virtual2Physical {
    public static int pageNum(long memoryAddress, int numberOfPages, long block) {

        for (int i = 0; i <= numberOfPages; i++) {
            long low = block * i;
            long high = block * (i + 1);
            if (low <= memoryAddress && memoryAddress < high) {
                return i;
            }
        }
        return -1;
    }
}