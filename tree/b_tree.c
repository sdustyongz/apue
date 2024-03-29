#include "b_tree.h"
#include "../collection/queue.h"

BTNode *root;

BTNode *createNode()
{
    BTNode *node = malloc(sizeof(BTNode));
    if (node != NULL)
    {
        node->isLeaf = 1;
        node->num = 0;
        return node;
    }
    return NULL;
}

BTNode *createThree()
{
    if (root == NULL)
    {
        root = createNode();
    }
    return root;
}
void insert_notfull_node(BTNode *x, int key);

struct node_position
{
    BTNode *pr;
    int index;
};
typedef struct node_position Np;

Np *search(BTNode *node, int key)
{
    int i = node->num - 1;
    while (i >= 0 && key < node->value[i])
    {
        i--;
    }
    if (i >= 0 && key == node->value[i])
    {
        Np *np = malloc(sizeof(Np));
        np->pr = node;
        np->index = i;
        return np;
    }
    if (node->isLeaf)
    {
        return NULL;
    }
    return search(node->ptr[i + 1], key);
}

void split_node(BTNode *parent, int index)
{
    BTNode *child = parent->ptr[index];
    int t = KEY_NUM / 2 + 1;
    BTNode *node = createNode();
    node->isLeaf = child->isLeaf;
    int i = KEY_NUM - 1;

    for (i = 0; i < t - 1; i++)
    {
        node->value[i] = child->value[i + t];
        child->value[i + t] = 0;
        node->ptr[i] = child->ptr[i + t];
        child->ptr[i + t] = NULL;
    }

    node->ptr[i] = child->ptr[i + t];
    child->ptr[i + t] = NULL;

    child->num = t - 1;
    node->num = t - 1;

    i = parent->num - 1;
    int key = child->value[t - 1];
    while (i >= 0 && key < parent->value[i])
    {
        parent->value[i + 1] = parent->value[i];
        parent->ptr[i + 2] = parent->ptr[i + 1];
        i--;
    }
    parent->value[i + 1] = key;
    parent->ptr[i + 2] = node;
    parent->num++;
}

void insert_node(int key)
{
    if (root->num == KEY_NUM)
    {
        BTNode *node = createNode();
        node->isLeaf = 0;
        node->ptr[0] = root;
        root = node;
        split_node(node, 0);
        insert_notfull_node(root, key);
    }
    else
    {
        insert_notfull_node(root, key);
    }
}

void insert_notfull_node(BTNode *x, int key)
{
    int i = x->num - 1;
    if (x->isLeaf != 0)
    {
        while (i >= 0 && key < x->value[i])
        {
            x->value[i + 1] = x->value[i];
            i--;
        }
        x->value[i + 1] = key;
        x->num++;
    }
    else
    {
        while (i >= 0 && key < x->value[i])
            i--;
        BTNode *y = x->ptr[i + 1];
        if (y->num == KEY_NUM)
        {
            split_node(x, i + 1);
            y = x;
        }
        insert_notfull_node(y, key);
    }
}

void print()
{
    BTNode *p = root;
    queue *que = init_queue();
    add(que, (void *)p);
    int i = 0;
    int j = 0;
    queue *temp = init_queue();
    ;
    while (que->size > 0)
    {
        i = que->size;
        while (i-- > 0)
        {
            BTNode *bnode = (BTNode *)offer(que);
            for (j = 0; j < bnode->num; j++)
            {
                printf("%d ", bnode->value[j]);
                if (bnode->ptr[j] != NULL)
                {
                    add(temp, (void *)bnode->ptr[j]);
                }
            }
            if (bnode->ptr[j] != NULL)
                add(temp, bnode->ptr[j]);
            printf("    ");
        }
        free(que);
        que = temp;
        temp = init_queue();
        printf("\n");
    }
    free(que);
    free(temp);
}

/**
 * 将parent的左右两个节点合并，并将value[leftIndex]的值也合并到新的节点
 */
BTNode *merge_brother_node(BTNode *parent, int leftIndex, int rightIndex)
{
    BTNode *lChild = parent->ptr[leftIndex];
    BTNode *rChild = parent->ptr[rightIndex];
    int i = leftIndex, j = lChild->num;
    int value = parent->value[leftIndex];
    BTNode *ptr = parent->ptr[leftIndex + 1];
    while (i < parent->num - 1)
    {
        parent->value[i] = parent->value[i + 1];
        parent->ptr[i + 1] = parent->ptr[i + 2];
        i++;
    }
    parent->num--;
    i = 0;
    lChild->value[j] = value;
    lChild->ptr[j + 1] = ptr;
    lChild->num++;
    j++;
    while (i < rChild->num)
    {
        lChild->value[j] = rChild->value[i];
        lChild->ptr[j] = rChild->ptr[i];
        i++;
        j++;
        lChild->num++;
    }
    lChild->ptr[j] = rChild->ptr[rChild->num];
    free(rChild);
    return lChild;
}
/**
 * prIndex位置从x借一位，brotherIndex 的一位移到parent
 */
void borrow_brother_one(BTNode *parent, int prIndex, int brotherIndex)
{
    int i = 0;
    BTNode *brother = parent->ptr[brotherIndex];
    BTNode *node = parent->ptr[prIndex];
    int value;
    BTNode *pr;
    if (brotherIndex > prIndex)
    {
        pr = brother->ptr[0];
        value = brother->value[0];
        while (i < brother->num - 1)
        {
            brother->value[i] = brother->value[i + 1];
            brother->ptr[i] = brother->ptr[i + 1];
            i++;
        }
        brother->ptr[i] = brother->ptr[i + 1];
        brother->num--;

        node->value[node->num] = parent->value[prIndex];
        node->num++;
        node->ptr[node->num + 1] = pr;

        parent->value[prIndex] = value;
    }
    else if (brotherIndex < prIndex)
    {
        pr = brother->ptr[brother->num];
        value = brother->value[brother->num - 1];
        i = node->num;
        while (i > 0)
        {
            node->ptr[i + 1] = node->ptr[i];
            node->value[i] = node->value[i - 1];
            i--;
        }
        node->ptr[1] = node->ptr[0];
        node->value[0] = parent->value[brotherIndex];
        node->ptr[0] = brother->ptr[brother->num];
        node->num++;

        parent->value[brotherIndex] = brother->value[brother->num - 1];
        brother->num--;
    }
}

/**
 *
 */
Np *previous(BTNode *node, int valueIndex)
{
    Np *np = malloc(sizeof(Np));
    if (node->isLeaf)
    {
        np->pr = node;
        if (valueIndex >= 1)
            np->index = valueIndex - 1;
        else
            np->index = 0;
        return np;
    }
    node = node->ptr[valueIndex];
    while (node->ptr[node->num] != NULL)
    {
        node = node->ptr[node->num];
    }
    np->pr = node;
    np->index = node->num - 1;
    return np;
}

Np *next(BTNode *node, int valueIndex)
{
    Np *np = malloc(sizeof(Np));
    if (node->isLeaf)
    {
        np->pr = node;
        np->index = 0;
        return np;
    }
    node = node->ptr[valueIndex + 1];
    while (node->isLeaf == 0)
    {
        node = node->ptr[0];
    }
    np->pr = node;
    np->index = 0;
    return np;
}



void delete_on_node(BTNode *pr, int key)
{
    int t = KEY_NUM / 2 + 1;
    int i = pr->num - 1;
    int value;
    while (i >= 0 && pr->value[i] > key)
    {
        i--;
    }
    if (i < 0)
    {
        if (pr->isLeaf)
            return;
        if (pr->ptr[0]->num >= t)
        {
            delete_on_node (pr->ptr[0], key);
        }
        else
        {
            if (pr->ptr[1]->num >= t)
            {
                borrow_brother_one(pr, 0, 1);
                delete_on_node(pr->ptr[0], key);
            }
            else
            {
                merge_brother_node(pr, 0, 1);
                delete_on_node(pr->ptr[0], key);
            }
        }
    }
    else if (pr->value[i] == key)
    {
        if (pr->isLeaf)
        {
            while (i < pr->num - 1)
            {
                pr->value[i] = pr->value[i + 1];
                pr->ptr[i + 1] = pr->ptr[i + 2];
                i++;
            }
            pr->num--;
            return;
        }
        else
        {
            if (pr->ptr[i]->num >= t)
            {
                Np *np = previous(pr, i);
                np->index;
                value = np->pr->value[np->index];
                np->pr->value[np->pr->num - 1] = -1;
                np->pr->num--;
                pr->value[i] = value;
                free(np);
                return;
            }
            else if (pr->ptr[i + 1]->num >= t)
            {
                Np *np = next(pr, i);
                value = np->pr->value[0];
                i = 0;
                while (i < np->pr->num)
                {
                    np->pr->value[i] = np->pr->value[i + 1];
                }
                np->pr->num--;
                pr->value[i] = value;
                free(np);
                return;
            }
            else
            {
                merge_brother_node(pr, i, i + 1);
                delete_on_node(pr->ptr[i], key);
            }
        }
    }
    else
    {
        if(pr->ptr[i+1]->num < t){
            if(pr->ptr[i]->num >= t){
                borrow_brother_one(pr,i+1,i);
                delete_on_node(pr,key);
            }else if(i < pr->num-1 && pr->ptr[i+2]->num >= t){
                borrow_brother_one(pr,i+1,i+2);
                delete_on_node(pr,key);
            }else{
                merge_brother_node(pr,i,i+1);
                delete_on_node(pr,key);
            }
        }else{
            delete_on_node(pr->ptr[i+1],key);
        }
    }
}

int main(int argc, char *argv[])
{
    root = createThree();
    insert_node(10);
    insert_node(1);
    insert_node(5);
    insert_node(6);
    insert_node(3);
    insert_node(2);
    insert_node(4);
    insert_node(20);
    insert_node(7);
    insert_node(30);
    insert_node(8);
    insert_node(9);
    insert_node(50);
    insert_node(40);
    insert_node(60);
    print();
    printf("\n");
    insert_node(70);
    print();
    delete_on_node(root,20);
    printf("after delete 20\n");
    print();
    delete_on_node(root,7);
    printf("after delete 7\n");
    print();
    delete_on_node(root,10);
    printf("after delete 10\n");
    print();
    delete_on_node(root,9);
    printf("after delete 9\n");
    print();
    delete_on_node(root,5);
    printf("after delete 5\n");
    print();
    delete_on_node(root,50);
    printf("after delete 50\n");
    print();
    delete_on_node(root,40);
    printf("after delete 40\n");
    print();
    delete_on_node(root,30);
    printf("after delete 30\n");
    print();
    delete_on_node(root,4);
    printf("after delete 4\n");
    print();
    delete_on_node(root,2);
    printf("after delete 2\n");
    print();
    delete_on_node(root,3);
    printf("after delete 3\n");
    print();
    delete_on_node(root,8);
    printf("after delete 3\n");
    print();
    
   return 1;
}