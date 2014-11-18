#include <iostream>
#include <vector>
#include "lib2dz.h"

void read(std::vector< int > *sorted_array, int number_of_elements);

using std::cin;
using std::cout;

int main()
{
int number_of_elements = 0, index = 0;
int left_answer, right_answer, right = 0, right_new, first, second;
double sum = 0, full_sum = 0, answer = 0, par = 0;

cin >> number_of_elements;

std::vector< int > array_with_indexes(number_of_elements);
std::vector< int > sorted_array(number_of_elements);;
std::vector< double > SUM(number_of_elements);

read(&sorted_array, number_of_elements);

for (index = 0; index < number_of_elements; ++index) {
  array_with_indexes[index] = index; 
}

quicksort_indexes(&sorted_array, 0, number_of_elements - 1, &array_with_indexes);


std::cout.precision(15);

sorted_array[number_of_elements] = sorted_array[number_of_elements - 1];

for (index = number_of_elements - 1, right = number_of_elements - 1; 
                                                         index >= 0; --index) {

full_sum += sorted_array[index];
SUM[index] = full_sum;

first = sorted_array[index],
second = sorted_array[index + 1],
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


cout << answer << "\n";
quicksort(&array_with_indexes, left_answer, right_answer);


for (index = left_answer; index <= right_answer; ++index) {
      cout << array_with_indexes[index] + 1 << " "; 
    }

return 0;
} 

  void read(std::vector< int > *sorted_array, int number_of_elements)
  { 
    for (int index = 0; index < number_of_elements; ++index) {
      std::cin >> (*sorted_array)[index];
    }
  }



