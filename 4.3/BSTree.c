#include <stdio.h>
#include <stdlib.h>
#include "Tree.h"

struct Node {
    int num;
    Tree left, right;
    int height;
} Node;

struct B_Node {
    int order;
    int nums[3];
    B_Tree child[4];
    B_Tree parent;
} B_Node;

Tree TreeCreate(int n) {
    Tree s;
    if ((s = malloc(sizeof(struct Node))) != NULL) {
        s->num = n;
        s->left = NULL;
        s->right = NULL;
        return s;
    }
    fprintf(stderr, "No memory!\n");
    exit(EXIT_FAILURE);
}

Tree TreeInsert(Tree s, int n) {
    if (s == NULL) {
        return TreeCreate(n);
    } else if (n < (s->num)) {
        s->left = TreeInsert((s->left), n);
    } else if (n > (s->num)) {
        s->right = TreeInsert((s->right), n);
    }
    return s;
}

void TreeShow(Tree s) {
   
    printf("%d", s->num);
    if ((s->left) != NULL) {\
        printf(",");
        TreeShow(s->left);
    }

    if ((s->right) != NULL) {
        printf(",");
        TreeShow(s->right);
    }
    
    return;
}

Tree TreeJoin(Tree tree1, Tree tree2) {
    if (tree1 == NULL) {
        return tree2;
    } else if (tree2 == NULL) {
        return tree1;
    }
    Tree current;
    Tree parent;
    // printf("tree1 num is %d, tree2 num is %d\n", tree1->num, tree2->num);
    if ((tree1->num) < (tree2->num)) {
        current = tree2;
        while ((current->left) != NULL) {
            parent = current;
            current = current->left;
        }
        if ((current->right) != NULL) {
            parent->left = current->right;
        } else {
            parent->left = NULL;
        }
        current->right = parent;
        current->left = tree1;
    } else if ((tree1->num) > (tree2->num)) {
        Tree temp = NULL;
        temp = tree1;
        tree1 = tree2;
        tree2 = temp;
        return TreeJoin(tree1, tree2);
    }
    return current;
}

Tree TreeDelete(Tree s, int n) {
    if (s == NULL) {
        return NULL;    
    }
    if ((s->num) == n) {
        if (((s->left) == NULL) && (s->right) == NULL) {
            free(s);
            return NULL;
        }

    }

    Tree parent = TreeTraverse(s, n, NULL);
    if (parent == NULL) {
        printf("node not in tree!\n");
        return s;
    }
    Tree that_node;
    if (n < (parent->num)) {
        that_node = parent->left;
        if ((that_node->left != NULL) && (that_node->right) != NULL) {
            parent->right = that_node->left;
            parent->right->right = that_node->right;
            return s;
        } if (that_node->left != NULL) {
            parent->left = that_node->left;
            free(that_node);
            return s;
        } if (that_node->right != NULL) {
            parent->right = that_node->right;
            free(that_node);
            return s;
        } 
        free(that_node);
        return s;
    } else if (n > (parent->num)) {
        that_node = parent->right;
        if ((that_node->left != NULL) && (that_node->right) != NULL) {
            parent->right = that_node->left;
            parent->right->right = that_node->right;
            return s;
        } if (that_node->left != NULL) {
            parent->left = that_node->left;
            free(that_node);
            return s;
        } if (that_node->right != NULL) {
            parent->right = that_node->right;
            free(that_node);
            return s;
        } 
        free(that_node);
        return s;
    } else if (n == parent->num) {
        that_node = parent;
        if (that_node->left != NULL && (that_node->right == NULL)) {
            free(that_node);
            return that_node->left;
        }
        if (that_node->left == NULL && (that_node->right != NULL)) {
            free(that_node);
            return that_node->right;
        } else {
            // printf("left is %d, right is %d\n", that_node->left->num, that_node->right->num);
            // TreeShow(that_node->left);
            // TreeShow(that_node->right);
            return TreeJoin(that_node->left, that_node->right);
            free(that_node);
        }
    }
    return NULL;
}

Tree TreeTraverse(Tree s, int n, Tree last) {
    if (s == NULL) {
        return NULL;
    }
    if (n == (s->num) && last == NULL) {
        return s;
    }
    if (n == (s->num)) {
        return last;
    }
    if (n < (s->num)) {
        return TreeTraverse(s->left, n, s);
    } else if (n > (s->num)) {
        return TreeTraverse(s->right, n, s);
    }
    return NULL;
}

Tree TreeShiftRight(Tree root) {
    if (root == NULL) {
        return NULL;
    }
    if (root->left == NULL) {
        return root;
    }
    Tree NewRoot = root->left;
    Tree temp = (NewRoot)->right;
    NewRoot->right = root;
    root->left = temp;
    return NewRoot;
}

Tree TreeShiftLeft(Tree root) {
    if (root == NULL) {
        return NULL;
    }
    if (root->right == NULL) {
        return root;
    }
    Tree NewRoot = root->right;
    Tree Temp = NewRoot->left;
    root->right = Temp;
    NewRoot->left = root;
    return NewRoot;
}

Tree TreeInsertRoot(Tree root, int n) {
    if (root == NULL) {
        Tree NewNode = malloc(sizeof(struct Node)); 
        NewNode->num = n;
        NewNode->right = NULL;
        NewNode->left = NULL;
        root = NewNode;
    }
    if (n < root->num) {
        root->left = TreeInsertRoot(root->left, n);
        root = TreeShiftRight(root);
    } else if (n > root->num) {
        root->right = TreeInsertRoot(root->right, n);
        root = TreeShiftLeft(root);
    }
    return root;
}

Tree InsertAVL(Tree root, int n) {
    if (root == NULL) {
        Tree New_Node = malloc(sizeof(struct Node));
        New_Node->left = NULL;
        New_Node->right = NULL;
        New_Node->num = n;
        New_Node->height = 0;
        return New_Node;
    } else if (root->num == n) {
        return root;
    }
    if (n < root->num) {
        root->left = InsertAVL(root->left, n);
        root->height = max(root) + 1;
    } else if (n > root->num) {
        root->right = InsertAVL(root->right, n);
        root->height = max(root) + 1;
    }
    
    int Height_Left;
    int Height_Right;
    int h_difference;
    // two test cases
    // https://imgur.com/a/pcm12n6
    // https://imgur.com/a/PHsyy6q
    if (root->left == NULL) {
        
        if (root->right == NULL) {
            Height_Left = 0;
            Height_Right = 0;
            h_difference = 0;
        } else {
            Height_Right = root->right->height;
            h_difference = -1 * (Height_Right + 1);
        }
    } else {
        if (root->right != NULL) {
            Height_Left = root->left->height;
            Height_Right = root->right->height;
            h_difference = Height_Left - Height_Right;
        } else {
            Height_Left = root->left->height;
            h_difference = Height_Left + 1;
        }
    }
    printf("h difference is %d\n", h_difference);
    if (h_difference > 1) {
        Tree Old_Critical;
        Tree New_Critical;
        if (n > root->left->num) {
            Old_Critical = root->left;
            root->left = TreeShiftLeft(root->left);
            New_Critical = root->left;
            Old_Critical->height = max(Old_Critical) + 1;
            New_Critical->height = max(New_Critical) + 1;
            printf("left bigger then go right! special\n");
        }
        Old_Critical = root;
        root = TreeShiftRight(root);
        printf("Shift right!\n");
        New_Critical = root->left;
        Old_Critical->height = max(Old_Critical) + 1;
        New_Critical->height = max(New_Critical) + 1;
    } else if (h_difference < -1) {
        Tree Old_Critical;
        Tree New_Critical;      
        if (n < root->right->num) {
            Tree Old_Critical = root->right;
            root->right = TreeShiftRight(root->right);
            printf("right bigger then go left! special\n");
            Tree New_Critical = root->right;
            Old_Critical->height = max(Old_Critical) + 1;
            New_Critical->height = max(New_Critical) + 1;
        }
        Old_Critical = root;
        root = TreeShiftLeft(root);
        printf("Shift right!\n");
        New_Critical = root->left;
        Old_Critical->height = max(Old_Critical) + 1;
        New_Critical->height = max(New_Critical) + 1;
    }
    return root;
}

int max(Tree s) {
    if (s->left == NULL) {
        if (s->right == NULL) {
            return -1;
        } else {
            return s->right->height;
        }
    }
    if (s->right == NULL) {
        if (s->left == NULL) {
            return -1;
        } else {
            return s->left->height;
        }
    } 
   
    if (s->left->height > s->right->height) {
        return s->left->height;
    } else if (s->left->height == s->right->height) {
        return s->left->height;
    } else {
        return s->right->height;
    }
}

B_Tree Insert_B_Tree(B_Tree root, int n, B_Tree Parent_Node) { // https://imgur.com/a/N4SLIIm
    if (root == NULL) {
        B_Tree New_Node = malloc(sizeof(struct B_Node));
        New_Node->order = 2;
        (New_Node->nums)[0] = n;
        New_Node->parent = NULL;
        for (int i = 0; i < 4; i ++) {
            (New_Node->child)[i] = NULL;
        }
        return New_Node;
    }

    B_Tree result = Search_Node(root, n);
    if (result != NULL) {
        return result;
    }
    if (root->order < 3) { // when less than 3 nodes
        int i;
        for (i = 0; i < root->order - 1; i ++) {
            if (n < (root->nums)[i]) { // insert in between nodes
                if ((root->child)[i] == NULL) { // if there is no child
                    int j;
                    int temp;
                    int temp_next;
                    for (j = i; j < root->order; j ++) {
                        if (j == i) {
                            temp = (root->nums)[i];
                            if (j < root->order - 2) {
                                temp_next = (root->nums)[j + 1];
                            }
                            (root->nums)[j] = n;
                            root->order ++;
                        } else {
                            temp = temp_next;
                            (root->nums)[j] = temp;
                            if (j < root->order - 2) {
                                temp_next = (root->nums)[j + 1];
                            }
                        }
                    }
                    return root;
                } else { // if there is child
                    (root->child)[i] = Insert_B_Tree((root->child)[i], n, root);
                }
                
            }
        } 
        if ((root->child)[i] == NULL) { // insert at the end of nodes
            (root->nums)[i] = n;
            root->order ++;
            return root;
        } else {
           (root->child)[i] = Insert_B_Tree((root->child)[i], n, root); // insert at the child
        }
    } else { // No available nodes
        int i;
        int promote;
        B_Tree NodeL;
        B_Tree NodeR;
        if (n < (root->nums)[1]) { //  compare with nums[1]
            if (n < (root->nums)[0]) { // insert at head, promote is nums[0]
                promote = (root->nums)[0];

                NodeL = malloc(sizeof(struct B_Node)); // create left node
                (NodeL->nums)[0] = n;
                NodeL->order = 2;

                NodeR = malloc(sizeof(struct B_Node)); // create right node
                (NodeR->nums)[0] = (root->nums)[1];
                (NodeR->nums)[1] = (root->nums)[2];
                NodeR->order = 3;

                free(root); // from this moment onwareds, root doesnt work anymore
                for (int i = 0; i < parent->order - 1; i ++) {
                    if ((NodeL->nums)[0] < (parent->nums)[i]) {
                        Parent_Node = Insert_B_Tree(Parent_Node, promote, Parent_Node->parent);
                        (parent->child)[i] = NodeL;
                        (parent->child)[i + 1] = NodeR;
                        return Parent_Node;
                    }
                }
                Parent_Node = Insert_B_Tree(Parent_Node, promote, Parent_Node->parent);
                (parent->child)[i - 1] = NodeL;
                (parent->child)[i] = NodeR;
                return Parent_Node;
            } //
        }
    }
}

B_Tree Search_Node(B_Tree root, int n) {
    if (root == NULL) {
        return NULL;
    }

    int i;
    for (i = 0; i < (root->order - 1); i ++) {
        if (n == (root->nums)[i]) {
            return root;
        }
    }
    for (i = 0; i < (root->order - 1); i ++) {
        if (n < (root->nums)[i]) {
            return Search_Node((root->child)[i], n);
        }
    }
    return Search_Node((root->child)[i], n);
}