#ifndef DataSet_h
#define DataSet_h

#include <sqlite_orm.h>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <map>
#include "parser.hpp"
#include "Visualise.h"
#include "DecisionTree.h"


using std::cout;
using std::endl;
using namespace sqlite_orm;

class DataSet {

    struct Data {
        int id;
        int age;
        int sex;
        int restbp;
        int chol;
        int fbs;
        int thalach;
        int exang;
        float oldpeak;
        int ca;
        int cp1;
        int cp2;
        int cp3;
        int cp4;
        int restecg1;
        int restecg2;
        int restecg3;
        int slope1;
        int slope2;
        int slope3;
        int thal3;
        int thal6;
        int thal7;
        int hd;
    };

public:
    static auto return_storage();
    static void insert_into_storage();
    static void print_storage();
    static std::vector<Data> fetch_data();
    static std::vector<std::vector<float>> fetch_X_y();

};

#endif