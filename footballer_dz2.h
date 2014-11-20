/*=
1. В header файле обязательно нужен Header Guard вида
#ifndef FOOTBALLER_DZ2_H
#define FOOTBALLER_DZ2_H
 
... содержимое h-файла

#endif

2. Файл должен содержать только обявления функций, а не их реализацию

3. Отступы !!!
*/


/*=
 * Не сразу понял, что эта функция должна делать. Название median -- явно неудачное,
 * поскольку в мат. статистике имеет немного отличную семантику. Лучше назвать middle.
 */
  // median function, search for middle among 3 numbers
  int median(int one, int two, int three) 
  {
      /*=
       * Этот код можно (и нужно!) сократить.
       * Используй std::max и std::min
       */
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

  /*=
   * Вектора нужно передавать по ссылке, а не через указатели
   */
  // array sorting using quicksort algorithm with transposition indexes saving 
  void quicksort_indexes(std::vector< int > *sorted_array, int first,
               int last, std::vector< int > *array_with_indexes)
  {
      /*=
       * 1. Объявления переменных -- отдельными инструкциями
       * 2. Индекс, используемый в std::vector -- это size_t, а не int
       * 3. В целях безопасности нужно использовать vector::at() вместо оператора [],
       *    поскольку в циклах нет явной проверки на выход за границы массива
       */
      int indexA = first, indexB = last, x = 0, val = 0;
      x = median((*sorted_array)[first], (*sorted_array)[(first + last) / 2],
                                                            (*sorted_array)[last]);
      do {
          /*=
           * 1. Писать цикл в одну строку -- очень плохо, все отладчики при пошаговом выполнении
           * будут выполнять две инструкции за один шаг
           * 2. Два цикла while -- очень опасные, поскольку явно не проверяют выход
           * за границы вектора
           */
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

  /*=
   * Код этой функции дублирует функцию quicksort_indexes.
   * Нужно оставить только quicksort_indexes, сделав дополнительные параметры
   * опциональными
   */
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
   
  /*=
   * 1. Сравнение int >= double фактически работает как static_cast<double>(int) > double.
   * Строгое равенство при этом неочевидно ввиду особенностей внутреннего представления (см. IEEE 754-2008)
   * От использования double нужно отказаться.
   * 2. Передавать копию вектора -- слишком затратно. Нужно передавать const reference
   */
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
  
