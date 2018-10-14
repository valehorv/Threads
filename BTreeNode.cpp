#include"BTreeNode.h"

BTreeNode::BTreeNode(int value ):
    m_value(value),
    m_left( nullptr ),
    m_right( nullptr ),
    m_has_succesor(false)
{}

