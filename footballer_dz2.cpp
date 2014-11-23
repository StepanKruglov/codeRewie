#include <iostream>
#include <vector>
#include <iterator>
#include <stdarg.h> 
#include "footballer_dz2.h" 

int main()
{
    size_t number_of_elements = 0;
    size_t left_answer = 0; 
    size_t right_answer = 0; 
    long long answer = 0; 
  

    std::cin >> number_of_elements;

    std::vector<int> array_with_indexes(number_of_elements);
    std::vector<int> sorted_array(number_of_elements + 1);


    read(sorted_array);

    for (int index = 0; index < number_of_elements; ++index) {
        array_with_indexes.at(index) = index + 1; 
    }

    quicksort_indexes(sorted_array, 0, number_of_elements - 1, array_with_indexes);

    best_players_combination_search(sorted_array, answer, left_answer, right_answer);


    std::cout.precision(15);
    std::cout << answer << std::endl;
    quicksort_indexes(array_with_indexes, left_answer, right_answer);

    std::copy(array_with_indexes.begin() + left_answer, array_with_indexes.begin() + right_answer + 1,
                                                                 std::ostream_iterator<int>(std::cout, " "));

return 0;
} 
    void best_players_combination_search(std::vector<int> &sorted_array, long long &answer,
                                                         size_t &left_answer, size_t &right_answer)
    {
        size_t first = 0; 
        size_t second = 0;
        size_t number_of_elements = sorted_array.size() - 1;
        size_t right_new = number_of_elements;
        long long sum = 0; 
        long long full_sum = 0;
        long long par = 0;
        std::vector<long long> continuous_sum(number_of_elements);

        sorted_array.at(number_of_elements) = sorted_array.at(number_of_elements - 1);

        for (size_t index = number_of_elements - 1, right = number_of_elements - 1; 
                                                                 index >= 0; --index) {

            full_sum += sorted_array.at(index);
            continuous_sum.at(index) = full_sum;


            first = sorted_array.at(index);
            second = sorted_array.at(index + 1);

            par = static_cast<long long>(first) + static_cast<long long>(second);  
            if (par < sorted_array.at(right)) {
                if (answer < sum) {
                    answer = sum;
                    left_answer = index + 1;
                    right_answer = right;  
                } 

                right_new = binary_search(par, sorted_array, index, right) - 1;

                if (answer >= sorted_array.at(right_new) * (right_new)) break;

                sum -= continuous_sum.at(right_new + 1) - continuous_sum.at(right) + sorted_array.at(right);

                right = right_new;
            }

            sum = sum + static_cast<long long>(sorted_array.at(index));
        }

        if (answer < sum) {
            answer = sum;
            left_answer = 0;
            right_answer = right_new;
        }
    }


    void read(std::vector< int > &sorted_array)
    { 
/*= Три строки ниже можно заменить всего одной строкой, используя стандартную библиотеку STL
 * (в этом случае функция read тогда вообще не нужна)
*/
// не придумал, как сделать в одну строку. Нашел, такой вариант, но не нашел,
// как в одну строчку, оборвать ввод на переводе строки.  
/*    std::copy( std::istream_iterator<int>(cin), std::istream_iterator<int>(),
                                               std::back_inserter( sorted_array ) );
*/
        for (int index = 0; index < sorted_array.size(); ++index) {
            std::cin >> sorted_array.at(index);
        }
    }

    int middle(int one, int two, int three) 
    {
        int mx;
        int mn;

        mx = std::max(one,two);
        mx = std::max(mx,three);
        mn = std::min(one,two);
        mn = std::min(mn,three);

        return one + two + three - mn - mx;
    }


    void quicksort_indexes(std::vector<int> &sorted_array, int first,
                                    int last, std::vector<int> &array_with_indexes)
    {
      /*=
       * 2. Индекс, используемый в std::vector -- это size_t, а не int || алгоритм подразумевает, что индекс может быть отрицательным, нужен int 
       */
        int indexA = first;
        int indexB = last;
        size_t x = 0;
        size_t val = 0;
        x = middle(sorted_array.at(first), sorted_array.at((first + last) / 2),
                                                            sorted_array.at(last));
        do {

            while (indexA < sorted_array.size() && sorted_array.at(indexA) < x) {
                indexA++;
            }

            while (indexB >= 0 && sorted_array.at(indexB) > x) {
                indexB--;
            }
  
            if (indexA <= indexB) {
                if (sorted_array.at(indexA) > sorted_array.at(indexB)) {
                    val = sorted_array.at(indexA);
                    sorted_array.at(indexA) = sorted_array.at(indexB);
                    sorted_array.at(indexB) = val;

                    if (!array_with_indexes.empty()) { 
                        val = array_with_indexes.at(indexB);
                        array_with_indexes.at(indexB) = array_with_indexes.at(indexA);
                        array_with_indexes.at(indexA) = val;
                    }     
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

    int binary_search(long long search_value, const std::vector< int > &array, int from, int to)
    {
        int extremum = 0;
        for (extremum = (to+from)/2; from < to; extremum = (to+from)/2) {
            if (array.at(extremum) >= search_value) {
                to = extremum;
            } else {
                from = extremum + 1;
              }
        }

        return extremum;
    }
