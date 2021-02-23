#include "bin_tree.h"

node* create(node* root, int key) {
    node* tmp = (node*)malloc(sizeof(node));
    tmp->key = key;
    tmp->parent = NULL;
    tmp->left = tmp->right = NULL;
    root = tmp;
    return root;
}

node* add(node* root, int key) {
    node* tmp = (node*)malloc(sizeof(node));
    tmp->key = key;
    tmp->left = NULL;
    tmp->right = NULL;
    tmp->parent = inserting_position_parent(root, key);

    node* parent = tmp->parent;
    if (key < parent->key) {
        parent->left = tmp;
    }
    else {
        parent->right = tmp;
    }

    return root;
}

node* find(node* root, int key) {

    if ((root == NULL) || (root->key == key)) {
        return root;
    }

    if (key < root->key) {
        return find(root->left, key);
    }
    else {
        return find(root->right, key);
    }
}

node* del(node* root, int key) {
    node* deleting_node = NULL;
    deleting_node = find(root, key);

    bool has_left = has_left_child(deleting_node);
    bool has_right = has_right_child(deleting_node);

    if (has_left && has_right) {
        del_with_two_child(deleting_node);
    }
    else if (has_left || has_right) {
        del_with_one_child(deleting_node, has_left, has_right);
    }
    else {
        del_leaf(deleting_node);
    }

    return root;
}

size_t size(node* root) {
    if (root == NULL) {
        return 0;
    }
    return size(root->right) + size(root->left) + 1;
}

node* min(node* root)
{
    node* l = root;
    while (l->left != NULL) {
        l = l->left;
    }
    return l;
}

node* max(node* root)
{
    node* r = root;
    while (r->right != NULL) {
        r = r->right;
    }
    return r;
}

void preorder(node* root) {
    if (root == NULL) {
        return;
    }

    std::cout << root->key << " ";
    preorder(root->left);
    preorder(root->right);
}

void postorder(node* root) {
    if (root == NULL) {
        return;
    }
    postorder(root->left);
    postorder(root->right);
    std::cout << root->key << " ";
}

node* inserting_position_parent(node* root, int key) {
    node* tmp = root;
    node* inserting_node_parent = NULL;

    while (tmp != NULL) {
        inserting_node_parent = tmp;
        if (key < tmp->key) { // Ищем место в левом поддереве 
            tmp = tmp->left;
        }
        else {
            tmp = tmp->right; // Ищем место в правом поддереве 
        }
    }

    return inserting_node_parent;
}

node* next_to(node* start_node) {
    if (has_right_child(start_node)) {
        return min(start_node->right);
    }

    node* tmp = start_node, * next_node = NULL;
    next_node = tmp->parent;
    while (!is_root(next_node) && (tmp != next_node->left)) {
        tmp = next_node;
        next_node = next_node->parent;
    }

    if (is_root(next_node) && (next_node->key < start_node->key)) {
        return NULL;
    }
    else {
        return next_node;
    }
}

node* back_to(node* start_node) {
    if (has_left_child(start_node)) {
        return max(start_node->left);
    }

    node* tmp = start_node, * back_node = NULL;
    back_node = tmp->parent;
    while (!is_root(back_node) && (tmp != back_node->right)) {
        tmp = back_node;
        back_node = back_node->parent;
    }

    if (is_root(back_node) && (back_node->key > start_node->key)) {
        return NULL;
    }
    else {
        return back_node;
    }
}

void del_leaf(node* leaf) {
    node* leaf_parent = leaf->parent;

    if (leaf == leaf_parent->right) {
        leaf_parent->right = NULL;
    }
    else {
        leaf_parent->left = NULL;
    }

    free(leaf);
}

void del_with_one_child(node* deleting_node, bool has_left, bool has_right) {
    node* deleting_node_parent = deleting_node->parent;

    //1 вариант - поддерево справа
    if (!has_left && has_right) {
        deleting_node_parent = deleting_node->parent;

        if (deleting_node == deleting_node_parent->right) {
            deleting_node_parent->right = deleting_node->right;
        }
        else {
            deleting_node_parent->left = deleting_node->right;
        }

        free(deleting_node);
    }
    //2 вариант - поддерево слева
    if (has_left && !has_right) {
        deleting_node_parent = deleting_node->parent;

        if (deleting_node == deleting_node_parent->right) {
            deleting_node_parent->right = deleting_node->left;
        }
        else {
            deleting_node_parent->left = deleting_node->left;
        }

        free(deleting_node);
    }

}

void del_with_two_child(node* deleting_node) {
    node* deleting_node_next = next_to(deleting_node);

    deleting_node->key = deleting_node_next->key;
    if (deleting_node_next->right == NULL) {
        deleting_node_next->parent->left = NULL;
    }
    else {
        deleting_node_next->parent->left = deleting_node_next->right;
    }

    free(deleting_node_next);

}

bool has_right_child(node* cur_node) {
    return cur_node->right != NULL;
}

bool has_left_child(node* cur_node) {
    return cur_node->left != NULL;
}

bool is_root(node* cur_node) {
    return cur_node->parent == NULL;
}