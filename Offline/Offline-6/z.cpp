// void print_tree(Node *x)
// {
//     if (x == NULL || x->child == NULL)
//     {
//         return;
//     }
//     Node *temp = x;
//     // cout<<"("<<temp->key<<", "<<temp->data<<")";
//     Node *temp2 = temp->child;
//     do
//     {
//         cout << "(" << temp2->key << ", " << temp2->data << ")";
//         if (temp2->right != temp->child)
//         {
//             cout << ",";
//         }
//         temp2 = temp2->right;
//     } while (temp2 != temp->child);

//     cout << endl;

//     temp2 = temp->child;
//     do
//     {
//         if (temp2->child != NULL)
//         {
//             cout << "(" << temp2->key << ", " << temp2->data << ")"
//                  << "->";
//             print_tree(temp2);
//         }
//         temp2 = temp2->right;
//     } while (temp2 != temp->child);

//     cout << endl;
// }

// void print()
// {
//     int treeNum = 1;
//     Node *temp = H;
//     if (temp == NULL)
//     {
//         cout << "The heap is empty" << endl;
//         return;
//     }

//     do
//     {
//         cout << "Tree " << treeNum << ": ";
//         cout << "(" << temp->key << ", " << temp->data << ")";
//         if (temp->child != NULL)
//         {
//             cout << "->";
//         }
//         print_tree(temp);
//         temp = temp->right;
//         // cout<<endl;
//         treeNum++;
//     } while (temp != H);
// }