#ifndef BTREECREATOR_H
#define BTREECREATOR_H

#include"BTreeNode.h"
#include<vector>
#include<string>

class BTreeCreator
{
    std::string m_linear_tree_values;

    bool node_is_terminal( BTreeNode* node );
    void visit_node( BTreeNode* node );

public:
    std::vector<BTreeNode> m_nodes;
    BTreeCreator();
    void create_btree();
    bool search_value_in_tree( int val );
    void breadth_first();
    void depth_first_inorder( BTreeNode *node );
    void depth_first_preorder( BTreeNode *node );
    void depth_first_postorder( BTreeNode *node );
    void morris_inorder(BTreeNode *p );
    void threaded_inorder( BTreeNode *node );
    BTreeNode* get_root();
    void clear_diplay_values( );
    void display_linear_tree(std::string type);
    void create_node_threads();
    void reset_node_threads();
    void insert_node( int node_value );
    void threaded_insert_node( int node_value );
    void delete_by_merging( BTreeNode* node );
};

#endif // BTREECREATOR_H
