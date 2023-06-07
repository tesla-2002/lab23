//Файл с реализациями функций и структур
#include "23header.h" //Подключаем файл с определениями прототипов функций, структур и библиотек

struct _tree { //Структура определяющая дерево 
    TreeItem data;  //Значение узла
    Tree right;     //Указатель на правого потомка
    Tree left;      //Указатель на левого потомка
    Tree parent;    //Указатель на родителя
};

Tree tree_create() {  //Функция создания дерева (корня)
    TreeItem value = 0; //Переменная, хранящая значение узла
    Tree tree = (Tree)malloc(sizeof(*tree)); //Выделение памяти под узел
    printf("Введите значение корня дерева: ");
    scanf("%d", &value);
    tree->data = value; //Присвоение узлу введенного значения 
    tree->parent = NULL; //Присвоение потомкам и родителю данного узла пустые указатели, т.к. их пока нет
    tree->right = NULL;
    tree->left = NULL;
    return tree; //возвращает указатель на данный узел типа структуры _tree
}

Tree search_in_tree(Tree root, TreeItem value) {   //Функция поиска
    if(!search_left(root,value)) return search_right(root, value);
    else return search_left(root, value);
}

Tree search_left(Tree root, TreeItem value) { //Функция поиска, обходит корень и левую ветвь дерева
    if(root->data == value) return root;
    if(root->left) return search_left(root->left, value);
    if(root->right) return search_left(root->right, value);
    else return NULL;
}

Tree search_right(Tree root, TreeItem value) { //Функция поиска, обходит корень и правую ветвь дерева
    if(root->data == value) return root;
    if(root->right) return search_right(root->right, value);
    if(root->left) return search_right(root->left, value);
    else return NULL;
}

void add_node(Tree root) { //Функция добавления узла в дерево, в качестве аргумента получает указатель на узел типа структуры _tree
    TreeItem value = 0; //Переменная, хранящая значение узла
    int flag = 1; //Переменная для меню действий
    printf("Выберите, куда нужно добавить узел:\n [1]-Добавить узел влево\n [2]-Добавить узел вправо\n");
    scanf("%d", &flag);
    switch (flag) {
        case 1:
            if (!root->left) { //Если левого потомка еще не существует, то добавляется узел влево
                Tree node = (Tree)malloc(sizeof(*node)); //Выделение памяти под узел
                node->parent = root; //Присвоение полю структуры данного узла указателя на родителя
                node->left = NULL;
                node->right = NULL;
                root->left = node; //Присвоение полю родителя данного узла указателя на левого потомка
                printf("Введите значение данного узла дерева: ");
                scanf("%d", &value);
                node->data = value; //Присвоение полю структуры данного узла - значения узла
                //return node; //Возваращется указатель на добавленный узел 
            } else { //Если такой узел уже существует
                printf("Такой узел уже существует, пожалуйста, добавьте другой узел.\n");
                //return root; //Возваращается указатель на сам узел
            }
        break;
        case 2:
            if (!root->right) { //Если правого потомка еще не существует, то добавляется узел вправо
                Tree node = (Tree)malloc(sizeof(*node)); //Все аналогично 
                node->parent = root;
                node->left = NULL;
                node->right = NULL;
                root->right = node;
                printf("Введите значение данного узла дерева: ");
                scanf("%d", &value);
                node->data = value;
                //return node;
            } else {
                printf("Такой узел уже существует, пожалуйста, добавьте другой узел.\n");
                //return root;
            }
        break;
    }
}

void delete_node(Tree node) { //Функция удаления узла, в качестве аргумента принимает указатель на узел типа структуры _tree
    int flag = 0;
    if(!node->parent && !node->left && !node->right) { //Если у дерева есть только корень и он удаляется
        printf("Вы удалили дерево!\n");
        delete_tree(node);
        exit(0);
    }

    if (!node->left && !node->right) { //Если у удаляемого узла нет потомков 
        if (node == node->parent->left) { //Если данный узел является левым потомком родителя
            node->parent->left = NULL;    //Для родителя обнуляется поле левого потомка
        } else { //Если данный узел является правым потомком родителя
            node->parent->right = NULL;   //Для родителя обнуляется поле правого потомка
        }
    }
    
    if (!node->right && node->left) { //Если у удаляемого узла только левый потомок
        if(!node->parent) { //Если удаляется корень дерева
            TreeItem temp = 0;
            temp = node->data; //Обмен значения удаляемого узла со значением левого потомка через временную переменную 
            node->data = node->left->data;
            node->left->data = temp;
            flag = 1;
            delete_node(node->left);  //Рекурсивный вызов для левого потомка, который содержит значение удаляемого узла
        } else {
            if (node == node->parent->left) { //Если данный узел является левым потомком родителя
                node->parent->left = node->left;
                node->left->parent = node->parent;//Полю левого потомка родителя (вместо данного узла) присв. значение левого потомка данного узла
            } else { //Если данный узел является правым потомком родителя
                node->parent->right = node->left;
                node->left->parent = node->parent;//Полю правогопотомка родителя (вместо данного узла) присв. значение левого потомка данного узла
            } 
        }
    }

    if (node->right && !node->left) { //Если у удаляемого узла только правый потомок
        if(!node->parent) { //Если удаляется корень дерева
            TreeItem temp = 0;
            temp = node->data; //Обмен значения удаляемого узла со значением левого потомка через временную переменную 
            node->data = node->right->data;
            node->right->data = temp;
            flag = 1;
            delete_node(node->right); //Рекурсивный вызов для правого потомка, который содержит значение удаляемого узла
        } else {
            if (node == node->parent->left) { //Аналогично с предыдущим случаем, тлько потомок правый
                node->parent->left = node->right;
                node->right->parent = node->parent;
            } else {
                node->parent->right = node->right;
                node->right->parent = node->parent;
            }
        }
    }

    if (node->right && node->left) { //Если у узла есть оба потомка
        TreeItem temp = 0; //Временная переменная для обмена значений узлов
        temp = node->data; //Обмен значения удаляемого узла со значением левого потомка через временную переменную 
        node->data = node->left->data;
        node->left->data = temp;
        delete_node(node->left); //Рекурсивный вызов функции для левого потомка (по правилу для корректного перестроения дерева) 
    }
    
    if(flag==0)free(node);
}

void print_node(TreeItem value, int inter) { //Функция вывода одного узла дерева с отступами
    for (int i = 0; i < inter; ++i) {
        printf(" ");
    }

    printf("%d\n", value);
}

void print_tree(Tree root, int inter) {  //Функция печати дерева
    if (!root) return;
    if (root->right) print_tree(root->right, inter + 5); //Рекурсивный проход по правой ветви дерева, начиная с самого правого листа
    print_node(root->data, inter);                    //Вывод значений каждого обойденного узла и затем корня дерева
    if (root->left) print_tree(root->left, inter + 5);   //Аналогично с левой ветвью дерева
}

int count(Tree node) { //Функция подсчёта нетерминальных вершин дерева, в качестве аргумента принимает указатель на корень дерева
    if (!node || (!(node->right) && !(node->left))) //Если у узла нет потомков
        return 0; 
    return count(node->right) + count(node->left) + 1; //Рекурсивный вызов, пока будут потомки - будет прибавляться 1, таким образом считаем
}

void delete_tree(Tree root) {  
    //if(!root) return;                                    //Функция удаления дерева и очистки памяти 
    if (root->right) delete_tree(root->right);  //Рекурсивный проход по правой ветви дерева, начиная с самого правого листа
    if (root->left) delete_tree(root->left);    //Аналогично
    printf("Deleted node is: %d\n", root->data);
    free(root);   //Очистка памяти каждой структуры узла
}