#include"btreecreator.h"
#include<queue>
#include<string>
#include<iostream>

BTreeCreator::BTreeCreator()
    :m_nodes{13,10,25,2,12,20,31}
{
}

BTreeNode* BTreeCreator::get_root()
{
    if( !m_nodes.empty( ) )
    {
        return &m_nodes[0];
    }
    return nullptr;
}

void
BTreeCreator::create_btree()
{
/*      13
        / \
       10  25
      / \  / \
     2 12 20 31
*/
    m_nodes[0].m_left = &m_nodes[1];
    m_nodes[0].m_right = &m_nodes[2];

    m_nodes[1].m_left = &m_nodes[3];
    m_nodes[1].m_right = &m_nodes[4];

    m_nodes[2].m_left = &m_nodes[5];
    m_nodes[2].m_right = &m_nodes[6];
}

void BTreeCreator::create_node_threads()
{
    // inorder sequence: 2 10 12 13 20 25 31

    m_nodes[3].m_right = &m_nodes[1]; // node 2 has node 10 as in order succesor
    m_nodes[3].m_has_succesor = true;

    m_nodes[4].m_right = &m_nodes[0]; // node 12 has node 13 as in order succesor
    m_nodes[4].m_has_succesor = true;

    m_nodes[5].m_right = &m_nodes[2]; // node 20 has node 25 as in order succesor
    m_nodes[5].m_has_succesor = true;
}

void BTreeCreator::reset_node_threads()
{
    // inorder sequence: 2 10 12 13 20 25 31

    m_nodes[3].m_right = nullptr; // node 2 has node 10 as in order succesor
    m_nodes[3].m_has_succesor = false;

    m_nodes[4].m_right = nullptr; // node 12 has node 13 as in order succesor
    m_nodes[4].m_has_succesor = false;

    m_nodes[5].m_right = nullptr; // node 20 has node 25 as in order succesor
    m_nodes[5].m_has_succesor = false;
}

void BTreeCreator::clear_diplay_values( )
{
    m_linear_tree_values.clear();
}

void BTreeCreator::display_linear_tree( std::string type ="")
{
  std::cout<< "Linear BTree for " << type << ": " << m_linear_tree_values.c_str() << std::endl;
  clear_diplay_values( );
}

bool
BTreeCreator::search_value_in_tree( int val )
{
  BTreeNode *current_node = &m_nodes[0];

  while ( current_node != nullptr )
  {
    if ( val == current_node->m_value )
    {
      return true;
    }
    if ( val < current_node->m_value )
    {
      current_node = current_node->m_left;
    }
    else
    {
      current_node = current_node->m_right;
    }
  }
}

bool
BTreeCreator::node_is_terminal( BTreeNode* node )
{
    return( node->m_left == nullptr && node->m_left == nullptr );
}

void BTreeCreator::breadth_first() {
  std::queue<BTreeNode *> queue;

  queue.push(&m_nodes[0]);

  while (!queue.empty())
  {
    auto node = queue.front();
    queue.pop();
    m_linear_tree_values += std::to_string( node->m_value ) + " ";

    if (node->m_left != nullptr)
    {
      queue.push(node->m_left);
    }

    if ( node->m_left != nullptr)
    {
      queue.push(node->m_right);
    }
  }
  display_linear_tree( "Breadth first " );
}

void BTreeCreator::visit_node( BTreeNode *node )
{
    m_linear_tree_values += std::to_string( node->m_value ) + " ";
}

void BTreeCreator::depth_first_inorder( BTreeNode *node )
{
// Traverse left all the way, visit the node, and traverse right

    if( node != nullptr )
    {
        depth_first_inorder(node->m_left);
        //Visit the node
        visit_node( node );
        depth_first_inorder(node->m_right);
    }
}

void BTreeCreator::depth_first_preorder( BTreeNode *node )
{
// visit the node first and then left and right

    if( node != nullptr )
    {
        //Visit the node first
        visit_node( node );

        depth_first_preorder(node->m_left);

        depth_first_preorder(node->m_right);
    }
}

void BTreeCreator::depth_first_postorder( BTreeNode *node )
{
    //Visit the node at the end after left and right traversal

    if( node != nullptr )
    {
        depth_first_postorder(node->m_left);

        depth_first_postorder(node->m_right);

        visit_node( node );
    }
}

void BTreeCreator::morris_inorder( BTreeNode *p )
{
 // If the tree has a left child node n, go to the rightmost node of n and make it as a temporary
 //       parent of n's parent p, and make the left child as the new parent p
 // Else visit the node and go to the right child
  /*
        (p) 13                10                2
            / \               / \                \
       (n) 10  25            2  12               10
          / \  / \                \                \
         2 12 20 31               13               12
          (tmp)                    \                \
                                    25               13
                                    / \                \
                                   20 31               25
                                                       / \
                                                      20 31
    */

    BTreeNode *tmp;

    while( p != nullptr )
    {
        if( p->m_left == nullptr )
        {
            visit_node( p );
            p = p->m_right;
        }
        else
        {
            tmp = p->m_left;

            while( tmp->m_right != nullptr && tmp->m_right != p )
            {
                tmp = tmp->m_right;
            }
            if( tmp->m_right == nullptr )
            {
                // make the rightmost node as the parent of the current p
                tmp->m_right = p;
                p = p->m_left;
            }
            else
            {
                // if a temporary parent has been found visit it and remove it as a tmp parent
                visit_node(p);
                tmp->m_right = nullptr;
                p = p->m_right;
            }
        }
    }
}

void BTreeCreator::threaded_inorder( BTreeNode *node )
{
    BTreeNode *prev;

    if( node != nullptr )
    {
        // if the node is not null go all the way to the left branch
        while ( node->m_left != nullptr)
        {
            node = node->m_left;
        }
        while( node != nullptr )
        {
            visit_node( node );
            prev = node;
            node = node->m_right;
            // if the right node is not a succesor continue inorder traversal, by going left
            if( node != nullptr && !prev->m_has_succesor)
            {
                while ( node->m_left != nullptr)
                {
                    node = node->m_left;
                }
            }
        }
    }
}

// to insert a node we need to go all the way down to the terminal nodes
void BTreeCreator::threaded_insert_node( int node_value )
{
    BTreeNode *prev, *p;

    BTreeNode *new_node = new BTreeNode( node_value );

    auto root = get_root( );

    if( root == nullptr )
    {
        root = new_node;
    }

    while ( p != nullptr )
    {
        prev = p;
        if( node_value < p->m_value )
        {
            p = p->m_left;
        }
        else if( !p->m_has_succesor )
        {
            p = p->m_right;
        }
        else
        {
            break;
        }
    }

    if( node_value < prev->m_value )
    {
    // the prev node will become the new successor of the new node
        prev->m_has_succesor = false;
        prev->m_left = new_node;
        new_node->m_right = prev;
    }
    else if( prev->m_has_succesor )
    {
        prev->m_has_succesor = false;
        new_node->m_right = prev->m_right;
        prev->m_right = new_node;
        new_node->m_has_succesor = true;
    }
    else
    {
        prev->m_right = new_node;
    }
}

void BTreeCreator::insert_node( int node_value )
{
    auto root = get_root();
    auto p = root;
    auto prev = root;

    while( p != nullptr )
    {
        if( node_value < p->m_value )
        {
            p = p->m_left;
        }
        else
        {
            p = p->m_right;
        }
    }

    if( root == nullptr ) // tree is empty
    {
        root = new BTreeNode( node_value );
    }
    else if( node_value < prev->m_value )
    {
        prev->m_left = new BTreeNode( node_value );
    }
    else
    {
        prev->m_right = new BTreeNode( node_value );
    }
}

void BTreeCreator::delete_by_merging( BTreeNode* node )
{
    // if the node to be deleted has both left and right children the method to be deleted will
    // be as follows: since all the values in the right tree are bigger than any value from the
    // left tree, the biggest value from the left tree will be made as the new parent of the right
    // subtree, and the parent of the left subtree will become the new parent. The biggest value
    // in the left subtree can be found as the rightmost node.

    BTreeNode* tmp = node;

    if( tmp->m_left == nullptr )
    {
        node = tmp->m_right;
    }
    else if( tmp->m_right == nullptr )
    {
        node = tmp->m_left;
    }
    else
    {
        // if it has both children
        BTreeNode* new_parent = tmp->m_left;
        BTreeNode* right_subtree_parent = tmp->m_right;
        tmp = new_parent;

        while( tmp != nullptr )
        {
            tmp = tmp->m_right;
        }
        tmp = right_subtree_parent;
        tmp = node;
        node = new_parent;
    }
    delete tmp;
}
