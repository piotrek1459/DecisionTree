#ifndef DecisionTree_h
#define DecisionTree_h

#include <sqlite_orm.h>
#include <string>
#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <map>
#include "DataSet.h"
#include "TreeNode.h"



class DecisionTree {
    TreeNode* root;
    static float calculate_gini(const std::vector<std::vector<std::vector<float>>>& groups, const std::vector<int>& classes);
    static void test_split(int index, float value, const std::vector<std::vector<float>>& dataset, std::vector<std::vector<float>>& left, std::vector<std::vector<float>>& right);
    std::pair<int, float> get_split(const std::vector<std::vector<float>>& dataset);
    TreeNode* build_tree(const std::vector<std::vector<float>>& train, int max_depth, int min_size, int depth);
    int predict(TreeNode* node, std::vector<float> row);
    static int count_class_instances(const std::vector<std::vector<float>>& group, int class_value);
public:
    DecisionTree() : root(nullptr) {}
    void fit(const std::vector<std::vector<float>>& train, int max_depth, int min_size) {
        root = build_tree(train, max_depth, min_size, 1);
    }

    int predict(std::vector<float> row) {
        return predict(root, std::move(row));
    }

    [[nodiscard]] TreeNode* getRoot() const {
        return root;
    }
};

#endif

