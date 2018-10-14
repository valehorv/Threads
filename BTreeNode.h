#ifndef BTREENODE_H
#define BTREENODE_H

class BTreeNode
{
public:
    int m_value;
    BTreeNode* m_left;
    BTreeNode* m_right;
    BTreeNode( int value );
    bool m_has_succesor;
};

#endif // BTREENODE_H
