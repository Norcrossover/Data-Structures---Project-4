1
int removeEven(node *& root)
{
        int count = 0;
        if (root)
        {
                removeEven(root->left, count);
                removeEven(root->right, count);
                if (root->data % 2 == 0)
                {
                        deleteNode(root);
                }
        }
        return count;
}



void removeEven(node *& curr, int& count)
{
        if (curr)
        {
                if (curr->data % 2 == 0)
                {
                        cout << curr->data << " is now removed" << endl;
                        deleteNode(curr);
                        count++;
        //              removeEven(curr, count);
                }
                removeEven(curr->left, count);
                removeEven(curr->right, count);
        }
}
/*
            node * temp = target;
                        target = target->right;
                        delete temp;
                }
                else
                {
                        node * prev = nullptr;
                        node * curr = target->right;
                        if (!curr->left)
                        {
                                target->right = curr->right;
                        }
                        else
                        {
                                while (curr->left)
                                {
                                        prev = curr;
                                        curr= curr->left;
                                }
                                prev->left = curr->right;
                        }
                        target->data = curr->data;
                        delete curr;
                }
        }
*/
        // case 1
        if (!target->left && !target->right)
        {
                delete target;
                target = nullptr;
        }
        // case 2
        else if (!target->right)
        {
                node * temp = target;
                target = target->left;
                delete temp;
        }
        // case 3
        else if (!target->left)
        {
                node * temp = target;
                target = target->right;
                delete temp;
        }
        // case 4
        else
        {
                node * prev = nullptr;
                node * curr = target->right;
                if (!curr->left)
                {
                        target->right = curr->right;
                }
                else
                {
                        while (curr->left)
                        {
                                prev = curr;
                                curr = curr->left;
                        }
                        prev->left = curr->right;
                }
                //delete target->data;
                target->data = curr->data;
                delete curr;
                return;
        }
}

