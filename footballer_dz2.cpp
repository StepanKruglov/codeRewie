#include <iostream>
#include <vector>
/*= Ошибка компиляции: такой файл не существует
#include "lib2dz.h"
*/
#include "footballer_dz2.h" 

/*=
 * 1. Если функция используется только в данном .cpp файле, то желательно
 * в начале дописать ключевое слово static (это автоматически подразумевается
 * компилятором, но явное указание улучшает читаемость кода)
 * 2. Если функция является общедоступной, то ее заголовок должен быть
 * в .h, а не .cpp файле
 */
void read(std::vector< int > *sorted_array, int number_of_elements);

using std::cin;
using std::cout;

/*= Отступы !!!
 * Общепринятый стандарт: 1 отступ = 4 пробела,
 * должны быть внутри каждого блока {}
 */
int main()
{
    /*=
     * 1. Объявление каждой переменной должно быть отдельным statement'ом
     * с новой строки, поскольку в будущем возможны изменения типов, а
     * системы контроля версий ориентированы на построчные изменения текстов
     * 2. ВСЕ переменные нужно инициализировать начальными значениями
     * 3. Число элементов и индекс -- это не int, а беззнаковый тип size_t.
     * См. reference класса std::vector
     */
int number_of_elements = 0, index = 0;
int left_answer, right_answer, right = 0, right_new, first, second;
double sum = 0, full_sum = 0, answer = 0, par = 0;

cin >> number_of_elements;

    /*=
     * Пробелы внутри <> не ставятся (за исключением вложенных треугольных скобок).
     * См. code style guide
     */
std::vector< int > array_with_indexes(number_of_elements);
std::vector< int > sorted_array(number_of_elements);;
    /*=
     * Имена большими буквами приняты для констант или макросов.
     * См. code style guide
     */
std::vector< double > SUM(number_of_elements);

/*=
 * 1. Составные типы данных в C++ передаются по ссылке, а не через указатель,
 * единственное исключение -- нулевой указатель.
 * Аналогичное замечание -- при вызове quicksort_indexes.
 * 2. Число элементов передавать не нужно, оно однозначно определяется
 * через vector::size()
 * 3. Более логично строку cin >> number_of_elements внести внутрь функции read
 */
read(&sorted_array, number_of_elements);

for (index = 0; index < number_of_elements; ++index) {
  array_with_indexes[index] = index; 
}

quicksort_indexes(&sorted_array, 0, number_of_elements - 1, &array_with_indexes);

/*= Все манипуляции с std::cout должны выполняться непосредственно перед выводом */
std::cout.precision(15);

/*=
 * 1. Программа на этой строке всегда падает независимо от входных данных. Подумай, почему.
 * 2. Падение не очевидно для отладчика, поскольку используются квадратные скобки всесто
 * метода vector::at(size_t index)
 * 3. Что будет, если 0==sorted_array.size() ?
 */
sorted_array[number_of_elements] = sorted_array[number_of_elements - 1];

/*=
 * 1. Весь код ниже, до вывода на экран, должен быть вынесен в отдельную функцию
 * с понятным именем, которое описывает, что этот код делает
 * 2. Используется очень опасный прием: внутри цикла for меняются значения переменных, объявленных
 * вне этого цикла. C++, в отличии от Си, позволяет объявлять переменные в любом месте
 */
for (index = number_of_elements - 1, right = number_of_elements - 1; 
                                                         index >= 0; --index) {

full_sum += sorted_array[index];
SUM[index] = full_sum;

/*= Присваивания -- отдельными инструкциями, разделенными ;, а не запятой ! */
first = sorted_array[index],
        /*= Что будет, если (index + 1) == sorted_array().size() ? */
second = sorted_array[index + 1],

/*= Зачем здесь double??? В данной задаче используется исключительно целочисленная арифметика */
par = static_cast<double>(first) + static_cast<double>(second);  
  if (par < sorted_array[right]) {
    if (answer < sum) {
      answer = sum;
      left_answer = index + 1;
      right_answer = right;  
    } 

    right_new = binary_search(par, sorted_array, index, right) - 1;

    if (answer >= sorted_array[right_new] * (right_new)) break;

    sum -= SUM[right_new + 1] - SUM[right] + sorted_array[right];

    right = right_new;
  }

sum = sum + static_cast<double>(sorted_array[index]);
}

    if (answer < sum) {
      answer = sum;
      left_answer = index + 1;
      right_answer = right;
    }

/*= Лучше выводить std::endl вместо платформо-зависимой ESC-последовательности "\n" */
cout << answer << "\n";
quicksort(&array_with_indexes, left_answer, right_answer);

/*= Три строки ниже можно заменить всего одной строкой, используя стандартную библиотеку STL */
for (index = left_answer; index <= right_answer; ++index) {
      cout << array_with_indexes[index] + 1 << " "; 
    }

return 0;
} 

  void read(std::vector< int > *sorted_array, int number_of_elements)
  { 
/*= Три строки ниже можно заменить всего одной строкой, используя стандартную библиотеку STL
 * (в этом случае функция read тогда вообще не нужна)
*/
    for (int index = 0; index < number_of_elements; ++index) {
      std::cin >> (*sorted_array)[index];
    }
  }



