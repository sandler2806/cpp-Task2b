//
// Created by sandl on 20/03/2022.
//
#include <iostream>
#include "Notebook.hpp"
using namespace ariel;

void ariel::Notebook::show( int page) {
    if(page<0){
        throw invalid_argument( "\nthe page must be positive" );
    }
    const int rowSize=100;
    string pageS= to_string(page);
    bool correctPage= true;
    for (pair<string, array<char,rowSize>> element : map)
    {
        correctPage= true;
        for (unsigned int i = 0; i < pageS.size(); ++i) {
            if(element.first.at(i)!=pageS.at(i)){
                correctPage= false;
            }
        }
        if(correctPage){
            cout << element.first.substr(pageS.size()+1)<<":";
            for (unsigned long i = 0; i < rowSize; ++i) {
                cout << element.second.at(i);
            }
            cout <<"\n";
        }
    }
}

void ariel::Notebook::erase(int page,int row,int column, ariel::Direction dir,
                             int length) {
    const int rowSize=100;
    if(column>=rowSize){
        throw invalid_argument( "\nthe max column is 100" );
    }
    if(column+length>rowSize&&dir==Direction::Horizontal){
        throw invalid_argument( "\nthe string is bigger than 100 chars" );
    }
    if(page <0  || row <0 || column <0||length<0){
        throw invalid_argument( "\nthe page row and column can't be negative" );
    }
    string key;
    if (dir==Direction::Horizontal){
        key= to_string(page) + "," + to_string(row);
        if(map.find(key)==map.end()){
            array<char,rowSize> arr{};
            arr.fill('_');
            map[key]=arr;
        }
        for (int i = 0; i < length; ++i){
            map[key][static_cast<unsigned long>(column++)]='~';
        }
    }
    else{
        for (int i = 0; i < length; ++i) {
            key= to_string(page) + "," + to_string(row++);
            if(map.find(key)==map.end()){
                array<char,rowSize> arr{};
                arr.fill('_');
                map[key]=arr;
            }
            map[key][static_cast<unsigned long>(column)]='~';
        }

    }
}

string ariel::Notebook::read( int page,  int row,  int column, ariel::Direction dir,
                            int length) {
    const int rowSize=100;
    if(column>=rowSize){
        throw invalid_argument( "\nthe max column is 100" );
    }
    if(column+length>rowSize&&dir==Direction::Horizontal){
        throw invalid_argument( "\nthe string is bigger than 100 chars" );
    }
    if(page <0  || row <0 || column <0 ||length<0){
        throw invalid_argument( "\nthe page row and column can't be negative" );
    }
    string key;
    string str;
    if (dir==Direction::Horizontal){
        key=to_string(page)+","+to_string(row);
        if(map.find(key)==map.end()){
            str=string(static_cast<unsigned long>(length), '_');
        }
        else{
            for (int i = 0; i < length; ++i){
                str+=map[key][static_cast<unsigned long>(column++)];
            }
        }
    }
    else{
        for (int i = 0; i < length; ++i){
            key=to_string(page)+","+ to_string(row++);
            if(map.find(key)==map.end()){
                str+="_";
            }
            else{
                str+=map[key][static_cast<unsigned long>(column)];
            }
        }
    }
    return str;
}

void
ariel::Notebook::write( int page,  int row,  int column, ariel::Direction dir, string str) {
    str+="";//for tidy
    const int maxcahr=126;
    const int minchar=32;
    const int rowSize=100;
    for (char i : str) {
        if(i<minchar||i>maxcahr) {
            throw invalid_argument( "\nthe string contain unvalid char" );
        }
    }
    if(column>=rowSize){
        throw invalid_argument( "\nthe max column is 100" );
    }
    if (str.find('~') != string::npos){
        throw invalid_argument( "\nthe char '~' can't be written" );
    }
    if(static_cast<unsigned long>(column) + str.length() > rowSize && dir == Direction::Horizontal){
        throw invalid_argument( "\nthe string is bigger than 100 chars" );
    }
    if(page <0  || row <0 || column <0){
        throw invalid_argument( "\nthe page row and column can't be negative" );
    }
    string line=this->read(page, row, column, dir, static_cast<int>(str.length()));
    bool empty= true;
    for (char i : line) {
        if(i!='_') {
            empty = false;
        }
    }
    if(!empty){
        throw invalid_argument( "\nthis space already writen or erased" );
    }
    string key;
    if (dir==Direction::Horizontal){
        key= to_string(page) + "," + to_string(row);
        if(map.find(key)==map.end()){
            array<char,rowSize> arr{};
            arr.fill('_');
            map[key]=arr;
        }
        for (char i : str) {
            map[key][static_cast<unsigned long>(column++)]=i;
        }
    }
    else{
        for (char i : str) {
            key= to_string(page) + "," + to_string(row++);
            if(map.find(key)==map.end()){
                array<char,rowSize> arr{};
                arr.fill('_');
                map[key]=arr;
            }
            map[key][static_cast<unsigned long>(column)]=i;
        }
    }
}
