void print1(Tree *tree)
{
    Node *root = tree->root;
    Node *empty_node = malloc(sizeof(Node));
    memset(empty_node, 0, sizeof(Node));
    Node *p = root;
    int height = tree_height(root);
    int level = 0;
    int level_num = pow(2, level);
    Node **node_queue = malloc(sizeof(Node *) * level_num);
    int first_space = (pow(2, height - 1) * 3 - 1) / 2;
    int i;
    node_queue[0] = root;
    while (level < height)
    {
        for (i = 0; i < first_space; i++)
            printf("   ");
        int distance = pow(2, (height - level - 1)) + 1;
        for (i = 0; i < level_num; i++)
        {
            if (node_queue[i] != empty_node)
                printf("%3d", node_queue[i]->key);
            else
                printf("---");
            for (int j = 0; j < distance; j++)
                printf("   ");
        }
        level++;
        Node **temp_queue = malloc(sizeof(Node *) * pow(2, level));
        for (i = 0; i < level_num; i++)
        {
            temp_queue[2 * i] = node_queue[i]->left == NULL ? empty_node : node_queue[i]->left;
            temp_queue[2 * i + 1] = node_queue[i]->right == NULL ? empty_node : node_queue[i]->right;
        }
        level_num = pow(2, level);
        first_space -= 2;
        free(node_queue);
        node_queue = temp_queue;
        printf("\n");
    }
    free(empty_node);
}