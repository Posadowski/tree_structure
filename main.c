#include <stdio.h>

#define NO_OP ' '

typedef struct tree_el
{
    char op; // operation character
    double val;
    int is_val_computed;

    struct tree_el *left;
    struct tree_el *right;

} tree_el;

tree_el create_op(char op)
{
    tree_el new_el = {op, 0, 0, NULL, NULL};
    return new_el;
}

tree_el create_val(double val)
{
    tree_el new_el = {NO_OP, val, 1, NULL, NULL};
    return new_el;
}

void print_tree(tree_el *el, int level)
{
    if (el == NULL)
    {
        return;
    }
    for (int i = 0; i < level; i++)
    {
        printf(" ");
    }
    printf("|-");

    if (el->op != NO_OP)
    {
        printf("%c\t", el->op);
    }

    if (el->is_val_computed)
    {
        printf("%.2f\n", el->val);
    }
    else
    {
        printf("?\n");
    }

    print_tree(el->left, level + 1);
    print_tree(el->right, level + 1);
}

void evaluate(tree_el *el)
{
    if (el == NULL)
    {
        return;
    }
    evaluate(el->left);
    evaluate(el->right);
    if (el->op != NO_OP)
    {
        if (el->left == NULL || el->right == NULL)
        {
            printf("ERROR: tree built incorrectly, no leaves\n");
            return;
        }
        double a = el->left->val;
        double b = el->right->val;
        double c;
        switch (el->op)
        {
        case '+':
            c = a + b;
            break;
        case '*':
            c = a * b;
            break;
        default:
            printf("ERROR: unsupported operator\n");
            return;
        }
        el->val = c;
        el->is_val_computed = 1;
    }
}

int main()
{
    // 1+2*3
    tree_el el1, el2, el3, el4, el5;

    el1 = create_val(1);
    el2 = create_op('+');
    el3 = create_val(2);
    el4 = create_op('*');
    el5 = create_val(3);

    el2.left = &el1;
    el2.right = &el4;

    el4.left = &el3;
    el4.right = &el5;

    print_tree(&el2, 0);
    evaluate(&el2);
    printf("\n\n\n\n");
    print_tree(&el2, 0);
    return 0;
}