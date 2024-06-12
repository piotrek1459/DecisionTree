#ifndef DecisionTreeMetrics_h
#define DecisionTreeMetrics_h

#include <vector>
#include <utility>
#include "TreeNode.h"
#include "DecisionTree.h"

class DecisionTreeMetrics {
public:
    static float accuracy(DecisionTree& tree, const std::vector<std::vector<float>>& test_data);
    static std::pair<int, int> confusionMatrix(DecisionTree& tree, const std::vector<std::vector<float>>& test_data);
};

#endif