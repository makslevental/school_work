// quick sort

#ifndef quickSort_
#define quickSort_
#include <iterator>
#include "indexOfMax.h"

using namespace std;



template <class T>
void quickSort(T a[], int leftEnd, int rightEnd, int n)
{// Sort a[leftEnd:rightEnd], a[rightEnd+1] >= a[leftEnd:rightEnd].
   if (leftEnd >= rightEnd) return;

   int leftCursor = leftEnd,        // left-to-right cursor
       rightCursor = rightEnd + 1;  // right-to-left cursor
   T pivot = a[leftEnd];

   // swap elements >= pivot on left side
   // with elements <= pivot on right side
   while (true)
   {
      do
      {// find >= element on left side
         leftCursor++;
      } while (a[leftCursor] < pivot);

      do
      {// find <= element on right side
         rightCursor--;
      } while (a[rightCursor] > pivot);

      if (leftCursor >= rightCursor) break;  // swap pair not found
      swap(a[leftCursor], a[rightCursor]);
   }
   copy(a, a+n, ostream_iterator<int>(cout, " "));
   cout << endl;
   // place pivot
   a[leftEnd] = a[rightCursor];
   a[rightCursor] = pivot;

   quickSort(a, leftEnd, rightCursor - 1, n);   // sort left segment
   quickSort(a, rightCursor + 1, rightEnd, n);  // sort right segment
}

template <class T>
void quickSort1(T a[], int n)
{// Sort a[0 : n - 1] using the quick sort method.
   if (n <= 1) return;
   // move largest element to right end
   int max = indexOfMax(a,n);
   // swap(a[n - 1], a[max]);
   quickSort(a, 0, n - 1, n);
}

#endif
