#pragma once
#include <stdlib.h>
#include <cstddef>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

typedef struct tree {
    int key;
    struct tree* left;
    struct tree* right;
    struct tree* parent;
} node;

node* create(node* root, int key);
node* add(node* root, int key);
node* find(node* root, int key);
node* del(node* root, int key);

node* read_from(node* root, string path);
bool write_to(node* root, string path);

size_t size(node* root);
bool empty(node* root);

node* min(node* root);
node* max(node* root);

void preorder(node* root, ostream& out);
void postorder(node* root, ostream& out);

node* inserting_position_parent(node* root, int key);
node* next_to(node* start_node);
node* back_to(node* start_node);

void del_leaf(node* leaf);
void del_with_one_child(node* deleting_node, bool has_left, bool has_right);
void del_with_two_child(node* deleting_node);

bool has_right_child(node* cur_node);
bool has_left_child(node* cur_node);
bool is_root(node* cur_node);