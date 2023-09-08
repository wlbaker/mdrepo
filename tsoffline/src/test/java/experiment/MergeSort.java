package experiment;

public class MergeSort {

  public static void main(String[] args) {
      //Initializing array
      int arr[] = {9, 4, 8, 3, 1, 2, 5};
      System.out.print("Initial Array: ");
      printArray(arr, 0, arr.length - 1);
      System.out.println();
      mergesort(arr, 0, arr.length - 1);
  }
  public static void printArray(int[] arr, int i, int j) {
      System.out.print("[");

      for(int k = i; k < j; k++) {
          System.out.print(arr[k] + ", ");
      }

      System.out.print(arr[j] + "]");
  }
  //Sorting in non decreasing order
  private static void mergesort(int[] arr, int i, int j) {
      int mid = 0;

      if(i < j) {
          mid = (i + j) / 2;
          //System.out.println("mid="+mid);
          mergesort(arr, i, mid);
          mergesort(arr, mid + 1, j);
          merge(arr, i, mid, j);
      }
  }

  private static void merge(int[] arr, int i, int mid, int j) {
      System.out.print("Left: ");
      printArray(arr, i, mid);
      System.out.print(" Right: ");
      printArray(arr, mid + 1, j);
      System.out.println();
      int temp[] = new int[arr.length];
      int l = i;
      int r = j;
      int m = mid + 1;
      int k = l;

      while(l <= mid && m <= r) {
          if(arr[l] <= arr[m]) {
              temp[k++] = arr[l++];
          }
          else {
              temp[k++] = arr[m++];
          }
      }

      while(l <= mid)
          temp[k++] = arr[l++];

      while(m <= r) {
          temp[k++] = arr[m++];
      }

      for(int i1 = i; i1 <= j; i1++) {
          arr[i1] = temp[i1];
      }

      System.out.print("After Merge: ");
      printArray(arr, i, j);
      System.out.println();
  }

}
