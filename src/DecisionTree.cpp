#include "DecisionTree.h"


float DecisionTree::calculate_gini(const std::vector<std::vector<std::vector<float>>>& groups, const std::vector<int>& classes) {
    float gini = 0.0;
    int total_instances = 0;
    for (const auto& group : groups) {
        total_instances += (int)group.size();
    }

    for (const auto& group : groups) {
        int size = (int)group.size();
        if (size == 0) continue;
        float score = 0.0;
        for (const auto& class_val : classes) {
            int count = 0;
            for (const auto& row : group) {
                if ((int)row.back() == class_val) {
                    count++;
                }
            }
            float p = static_cast<float>(count) / float(size);
            score += p * p;
        }
        gini += (1.0 - score) * (static_cast<float>(size) / total_instances);
    }
    return gini;
}

void DecisionTree::test_split(int index, float value, const std::vector<std::vector<float>>& dataset, std::vector<std::vector<float>>& left, std::vector<std::vector<float>>& right) {
    for (const auto& row : dataset) {
        if (row[index] < value) {
            left.push_back(row);
        } else {
            right.push_back(row);
        }
    }
}

std::pair<int, float> DecisionTree::get_split(const std::vector<std::vector<float>>& dataset) {
    std::vector<int> class_values = {0, 1};
    int b_index = 999;
    float b_value = 999;
    float b_score = 999;
    std::vector<std::vector<float>> b_groups[2];
    for (int index = 0; index < dataset[0].size() - 1; ++index) {
        for (const auto& row : dataset) {
            std::vector<std::vector<float>> groups[2] = {std::vector<std::vector<float>>(), std::vector<std::vector<float>>()};
            test_split(index, row[index], dataset, groups[0], groups[1]);
            float gini = calculate_gini(std::vector<std::vector<std::vector<float>>>{groups[0], groups[1]}, class_values);
            if (gini < b_score) {
                b_index = index;
                b_value = row[index];
                b_score = gini;
                b_groups[0] = groups[0];
                b_groups[1] = groups[1];
            }
        }
    }
    return {b_index, b_value};
}

TreeNode* DecisionTree::build_tree(const std::vector<std::vector<float>>& train, int max_depth, int min_size, int depth) {
    std::pair<int, float> split = get_split(train);
    int feature_index = split.first;
    float threshold = split.second;
    if (feature_index == 999) {
        int label = count_class_instances(train, 1) > count_class_instances(train, 0) ? 1 : 0;
        return new TreeNode(label);
    }

    auto* node = new TreeNode(feature_index, threshold);
    std::vector<std::vector<float>> left, right;
    test_split(feature_index, threshold, train, left, right);

    if (left.empty() || right.empty()) {
        int label = count_class_instances(train, 1) > count_class_instances(train, 0) ? 1 : 0;
        node->left = node->right = new TreeNode(label);
        return node;
    }

    if (depth >= max_depth) {
        node->left = new TreeNode(count_class_instances(left, 1) > count_class_instances(left, 0) ? 1 : 0);
        node->right = new TreeNode(count_class_instances(right, 1) > count_class_instances(right, 0) ? 1 : 0);
    } else {
        if (left.size() <= min_size) {
            node->left = new TreeNode(count_class_instances(left, 1) > count_class_instances(left, 0) ? 1 : 0);
        } else {
            node->left = build_tree(left, max_depth, min_size, depth + 1);
        }
        if (right.size() <= min_size) {
            node->right = new TreeNode(count_class_instances(right, 1) > count_class_instances(right, 0) ? 1 : 0);
        } else {
            node->right = build_tree(right, max_depth, min_size, depth + 1);
        }
    }
    return node;
}

int DecisionTree::predict(TreeNode* node, std::vector<float> row) {
    if (node->feature_index == -1) {
        return node->label;
    }
    if (row[node->feature_index] < node->threshold) {
        if (node->left) {
            return predict(node->left, row);
        } else {
            return node->label;
        }
    } else {
        if (node->right) {
            return predict(node->right, row);
        } else {
            return node->label;
        }
    }
}

int DecisionTree::count_class_instances(const std::vector<std::vector<float>>& group, int class_value) {
    int count = 0;
    for (const auto& row : group) {
        if ((int)row.back() == class_value) {
            count++;
        }
    }
    return count;
}

