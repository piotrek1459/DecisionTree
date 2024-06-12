#include "DecisionTreeMetrics.h"


float DecisionTreeMetrics::accuracy(DecisionTree& tree, const std::vector<std::vector<float>>& test_data) {
    int correct = 0;
    for (const auto& row : test_data) {
        int prediction = tree.predict(row);
        if (prediction == static_cast<int>(row.back())) {
            correct++;
        }
    }
    return static_cast<float>(correct) / test_data.size();
}

std::pair<int, int> DecisionTreeMetrics::confusionMatrix(DecisionTree& tree, const std::vector<std::vector<float>>& test_data) {
    int true_positive = 0;
    int false_positive = 0;
    int true_negative = 0;
    int false_negative = 0;

    for (const auto& row : test_data) {
        int prediction = tree.predict(row);
        int actual = static_cast<int>(row.back());

        if (prediction == 1 && actual == 1) {
            true_positive++;
        } else if (prediction == 1 && actual == 0) {
            false_positive++;
        } else if (prediction == 0 && actual == 0) {
            true_negative++;
        } else if (prediction == 0 && actual == 1) {
            false_negative++;
        }
    }

    return std::make_pair(true_positive + true_negative, false_positive + false_negative);
}
