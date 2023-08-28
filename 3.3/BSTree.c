#include <stdio.h>
#include <stdlib.h>
#include "Tree.h"

struct Node {
    int num;
    Tree left, right;
} Node;

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