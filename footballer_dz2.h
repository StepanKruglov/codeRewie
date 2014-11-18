  // median function, search for middle among 3 numbers
  int median(int one, int two, int three) 
  {
    int mx, mn;
    if (one > two) {
      mx = one; 
    }  else {
         mx = two;
       }
    if (three > mx) {
      mx = three;
    }
    if (one < two) { 
     mn = one;
    } else {
        mn = two;
      }
    if (three < mn) { 
      mn = three;
    }

    return one + two + three - mn - mx;
  }

  // array sorting using quicksort algorithm with transposition indexes saving 
  void quicksort_indexes(std::vector< int > *sorted_array, int first,
               int last, std::vector< int > *array_with_indexes)
  {
      int indexA = first, indexB = last, x = 0, val = 0;
      x = median((*sorted_array)[first], (*sorted_array)[(first + last) / 2],
                                                            (*sorted_array)[last]);
      do {
          while ((*sorted_array)[indexA] < x) indexA++;
          while ((*sorted_array)[indexB] > x) indexB--;
  
          if (indexA <= indexB) {
              if ((*sorted_array)[indexA] > (*sorted_array)[indexB]) {
                 val = (*sorted_array)[indexA];
                 (*sorted_array)[indexA] = (*sorted_array)[indexB];
                 (*sorted_array)[indexB] = val;

                 val = (*array_with_indexes)[indexB];
                 (*array_with_indexes)[indexB] = (*array_with_indexes)[indexA];
                 (*array_with_indexes)[indexA] = val;     
              }
              indexA++;
             indexB--;
          }
      } while (indexA <= indexB);
 
      if (indexA < last)
          quicksort_indexes(sorted_array, indexA, last, array_with_indexes);
      if (first < indexB)
          quicksort_indexes(sorted_array, first, indexB, array_with_indexes);
  }

  // array sorting with quicksort algorithm
  void quicksort(std::vector< int > *sorted_array, int first,
               int last)
  {
      int indexA = first, indexB = last, x = 0, val = 0;
       x = median((*sorted_array)[first], (*sorted_array)[(first + last) / 2], 
                                                             (*sorted_array)[last]);
      do {
          while ((*sorted_array)[indexA] < x) indexA++;
          while ((*sorted_array)[indexB] > x) indexB--;
  
          if (indexA <= indexB) {
              if ((*sorted_array)[indexA] > (*sorted_array)[indexB]) {
                 val = (*sorted_array)[indexA];
                 (*sorted_array)[indexA] = (*sorted_array)[indexB];
                 (*sorted_array)[indexB] = val;
              }

             indexA++;
             indexB--;
          }
      } while (indexA <= indexB);
 
      if (indexA < last)
          quicksort(sorted_array, indexA, last);
      if (first < indexB)
          quicksort(sorted_array, first, indexB);
  }
   
  int binary_search(double search_value, std::vector< int > array, int from, int to)
  {
    int extremum = 0;
    for (extremum = (to+from)/2; from < to; extremum = (to+from)/2) {
      if (array[extremum] >= search_value) {
        to = extremum;
      } else {
          from = extremum + 1;
        }
    }
  return extremum;
  }
  
