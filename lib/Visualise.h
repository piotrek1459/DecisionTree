#ifndef Visualise_h
#define Visualise_h

#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "TreeNode.h"

class DecisionTreeVisualizer {
public:
    static void visualize(TreeNode* root, const std::string& filename, const std::vector<std::string>& featureNames);
private:
    static int visualizeHelper(TreeNode* node, std::ofstream& dotFile, const std::vector<std::string>& featureNames, int nodeId);
};

#endif