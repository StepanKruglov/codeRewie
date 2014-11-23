
#ifndef FOOTBALLER_DZ2_H
#define FOOTBALLER_DZ2_


        void read(std::vector<int> &sorted_array);
        // middle function, search for middle among 3 numbers
        int middle(int one, int two, int three); 

        // array sorting using quicksort algorithm with transposition indexes saving
        static std::vector<int> defult;
        void quicksort_indexes(std::vector<int> &sorted_array, int first,
                                    int last, std::vector<int> &array_with_indexes = defult);

        void best_players_combination_search(std::vector<int> &sorted_array, long long &answer,
                                                          size_t &left_answer, size_t &right_answer);

        int binary_search(long long search_value, const std::vector< int > &array, int from, int to);
#endif    
