
#include "Direction.hpp"
#include <string> // for string class
#include <unordered_map>
using namespace std;
namespace ariel{
    class Notebook {

        unordered_map<string, array<char,100>> map;
    public:

        void write( int page,int row,  int column, Direction dir, string str);
        string read( int page, int row, int column,Direction dir, int length);
        void erase( int page, int row, int column,Direction dir, int length);
        void show( int page);
    };
}
