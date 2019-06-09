#include <iostream>
#include "bstree.h"
#include "treenode.h"

using namespace std;

int main()
{
    BinSTree<int> MyTree;
    TreeNode<int> * TreeP1, * TreeP2;
    MyTree.Insert(90);
    MyTree.Insert(150);
    MyTree.Insert(180);
    MyTree.Insert(75);
    MyTree.Insert(100);
    MyTree.Insert(120);
    MyTree.Insert(130);
    MyTree.Insert(110);
    MyTree.Insert(40);
    TreeP1=MyTree.FindNode(120,TreeP2);
    cout<<TreeP2->data<<endl;     //100
    TreeP1=MyTree.FindNode(100,TreeP2);
    cout<<TreeP2->data<<endl;     //150
    TreeP1=MyTree.FindNode(40,TreeP2);
    cout<<TreeP2->data<<endl;      //75
    MyTree.Delete(150);
    TreeP1=MyTree.FindNode(100,TreeP2); //130
    cout<<TreeP2->data<<endl;
    MyTree.Delete(90);
    TreeP1=MyTree.FindNode(130,TreeP2); //75
    cout<<TreeP2->data<<endl;



}
