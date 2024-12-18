#include <iostream> // cout
using std::cout, std::endl, std::cin, std::ostream;
#include <unistd.h>
#include <signal.h>
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <filesystem>  
namespace fs = std::filesystem;
#include <climits> // --- Infinity

template<typename T> // NOTE: Templated functions must have their definition in the header file
bool is_arg_in_vector( T arg , const std::vector<T>& vec ){
    // Return true if 'arg' is in 'st' , false otherwise
    // URL , resolve dependent templated typenames: https://stackoverflow.com/a/11275548
    // URL , const_iterator: https://stackoverflow.com/a/309589
    typename std::vector<T>::const_iterator it = find( vec.begin() , vec.end() , arg ); 
    return it != vec.end();
}

template<typename T> // NOTE: Templated functions must have their definition in the header file
ostream& operator<<( ostream& os , const std::vector<T>& vec ) { // ostream '<<' operator for vectors
    // NOTE: This function assumes that the ostream '<<' operator for T has already been defined
    os << "[ ";
    for (size_t i = 0; i < vec.size(); i++) {
        os << vec[i];
        if (i + 1 < vec.size()) { os << ", "; }
    }
    os << " ]";
    return os; // You must return a reference to the stream!
}