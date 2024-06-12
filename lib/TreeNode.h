#ifndef TreeNode_h
#define TreeNode_h
class TreeNode {
public:
    int feature_index;
    float threshold;
    int label;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int feature_index, float threshold) : feature_index(feature_index), threshold(threshold), label(-1), left(nullptr), right(nullptr) {}
    TreeNode(int label) : feature_index(-1), threshold(-1), label(label), left(nullptr), right(nullptr) {}
};

#endif