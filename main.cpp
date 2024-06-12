//
// Created by Piotr Krupiński on 21/05/2024.
//
#include <iostream>
#include <vector>
#include "Visualise.h"
#include "DecisionTree.h"
#include "DataSet.h"
#include "DecisionTreeMetrics.h"

int main(int, char**) {
    DataSet::insert_into_storage();

    auto dataset = DataSet::fetch_X_y();
    int train_size = static_cast<int>(dataset.size() * 0.8);
    std::vector<std::vector<float>> train(dataset.begin(), dataset.begin() + train_size);
    std::vector<std::vector<float>> test(dataset.begin() + train_size, dataset.end());


    DecisionTree tree;
    tree.fit(train, 3, 1);

    float accuracy = DecisionTreeMetrics::accuracy(tree, test);
    std::cout << "Accuracy: " << accuracy * 100 << "%" << std::endl;

    auto [correct, incorrect] = DecisionTreeMetrics::confusionMatrix(tree, test);
    std::cout << "Confusion Matrix: \n";
    std::cout << "Correct: " << correct << "\n";
    std::cout << "Incorrect: " << incorrect << "\n";

    TreeNode* root = tree.getRoot();
    std::vector<std::string> featureNames = {
            "age", "sex", "restbp", "chol", "fbs", "thalach", "exang", "oldpeak", "ca",
            "cp1", "cp2", "cp3", "cp4", "restecg1", "restecg2", "restecg3", "slope1",
            "slope2", "slope3", "thal3", "thal6", "thal7", "hd"
    };

    DecisionTreeVisualizer::visualize(root, "../decision_tree.dot", featureNames);

    delete root;

    return 0;
}
