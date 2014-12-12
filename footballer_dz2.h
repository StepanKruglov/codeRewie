
#ifndef FOOTBALLER_DZ2_H
/*== 
Опечатка. После define должно быть то же имя, что и после ifndef
*/

#define FOOTBALLER_DZ2_

/*==
Для всех функций нужно объявить модификатор extern, иначе их нельзя будет использовать в другом модуле.
Это необходимо только в .h файле, в .cpp -- не обязательно.
*/

        void read(std::vector<int> &sorted_array);
        // middle function, search for middle among 3 numbers
        int middle(int one, int two, int three); 

        // array sorting using quicksort algorithm with transposition indexes saving
        
        /*==
        Плохое решение для defult.
        Каждый модуль (aka .cpp-файл), который будет включать в себя этот заголовок,
        будет создавать локальную копию вектора.
        Для out-параметра лучше не объявлять значение по умолчанию, либо использовать 
        передачу по указателю (*), а не по ссылке (&), и использовать значение по умолчанию nullptr
        */
        static std::vector<int> defult;
        void quicksort_indexes(std::vector<int> &sorted_array, int first,
                                    int last, std::vector<int> &array_with_indexes = defult);

        void best_players_combination_search(std::vector<int> &sorted_array, long long &answer,
                                                          size_t &left_answer, size_t &right_answer);

        int binary_search(long long search_value, const std::vector< int > &array, int from, int to);
#endif    
