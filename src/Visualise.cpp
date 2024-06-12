#include "Visualise.h"


void DecisionTreeVisualizer::visualize(TreeNode* root, const std::string& filename, const std::vector<std::string>& featureNames) {
    std::ofstream dotFile(filename);
    dotFile << "digraph DecisionTree {\n";
    visualizeHelper(root, dotFile, featureNames, 0);
    dotFile << "}\n";
    dotFile.close();
}

int DecisionTreeVisualizer::visualizeHelper(TreeNode* node, std::ofstream& dotFile, const std::vector<std::string>& featureNames, int nodeId) {
    if (node == nullptr) {
        return nodeId;
    }

    int currentId = nodeId;
    std::string label;
    if (node->feature_index != -1) {
        label = featureNames[node->feature_index] + " < " + std::to_string(node->threshold);
        dotFile << "node" << currentId << " [label=\"" << label << "\"];\n";
    } else {
        label = "Label: " + std::to_string(node->label);
        dotFile << "node" << currentId << " [label=\"" << label << "\", shape=box];\n";
    }

    int leftId = ++nodeId;
    if (node->left != nullptr) {
        dotFile << "node" << currentId << " -> " << "node" << leftId << " [label=\"True\"];\n";
        nodeId = visualizeHelper(node->left, dotFile, featureNames, leftId);
    }

    int rightId = ++nodeId;
    if (node->right != nullptr) {
        dotFile << "node" << currentId << " -> " << "node" << rightId << " [label=\"False\"];\n";
        nodeId = visualizeHelper(node->right, dotFile, featureNames, rightId);
    }

    return nodeId;
}