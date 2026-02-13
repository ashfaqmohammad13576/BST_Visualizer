#include <stdio.h>
#include <stdlib.h>

// ---------------- PHASE 1: NODE STRUCTURE ----------------

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

// Function to create a new node
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// ---------------- PHASE 2: INSERT FUNCTION ----------------

struct Node* insertNode(struct Node* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }

    if (value < root->data) {
        root->left = insertNode(root->left, value);
    }
    else if (value > root->data) {
        root->right = insertNode(root->right, value);
    }
    else {
        printf("Duplicate value not allowed!\n");
    }

    return root;
}

// ---------------- PHASE 3: TRAVERSALS ----------------

// Inorder Traversal (Left -> Root -> Right)
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Preorder Traversal (Root -> Left -> Right)
void preorder(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

// Postorder Traversal (Left -> Right -> Root)
void postorder(struct Node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

// ---------------- PHASE 4: SEARCH FUNCTION ----------------

int searchNode(struct Node* root, int key) {
    if (root == NULL)
        return 0;

    if (root->data == key)
        return 1;

    if (key < root->data)
        return searchNode(root->left, key);

    return searchNode(root->right, key);
}

// ---------------- PHASE 5: DELETE FUNCTION ----------------

// Find minimum value node (used in deletion)
struct Node* findMin(struct Node* root) {
    while (root->left != NULL)
        root = root->left;

    return root;
}

// Delete node function
struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL) {
        printf("Value not found in tree!\n");
        return root;
    }

    if (key < root->data) {
        root->left = deleteNode(root->left, key);
    }
    else if (key > root->data) {
        root->right = deleteNode(root->right, key);
    }
    else {
        // Case 1: No child (Leaf Node)
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }

        // Case 2: One child
        else if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        // Case 3: Two children
        else {
            struct Node* temp = findMin(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }

    return root;
}

// ---------------- PHASE 6: EXTRA FEATURES ----------------

// Count total nodes
int countNodes(struct Node* root) {
    if (root == NULL)
        return 0;

    return 1 + countNodes(root->left) + countNodes(root->right);
}

// Height of tree
int height(struct Node* root) {
    if (root == NULL)
        return 0;

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// Find maximum value
int findMaxValue(struct Node* root) {
    if (root == NULL) {
        printf("Tree is empty!\n");
        return -1;
    }

    while (root->right != NULL)
        root = root->right;

    return root->data;
}

// Find minimum value
int findMinValue(struct Node* root) {
    if (root == NULL) {
        printf("Tree is empty!\n");
        return -1;
    }

    while (root->left != NULL)
        root = root->left;

    return root->data;
}

// ---------------- PHASE 7: TREE VISUALIZATION ----------------

void displayTree(struct Node* root, int space) {
    if (root == NULL)
        return;

    space += 5;

    displayTree(root->right, space);

    printf("\n");
    for (int i = 5; i < space; i++)
        printf(" ");

    printf("%d\n", root->data);

    displayTree(root->left, space);
}

// ---------------- PHASE 8: LEVEL ORDER TRAVERSAL (BFS) ----------------

void levelOrder(struct Node* root) {
    if (root == NULL) {
        printf("Tree is empty!\n");
        return;
    }

    struct Node* queue[100];
    int front = 0, rear = 0;

    queue[rear++] = root;

    while (front < rear) {
        struct Node* current = queue[front++];
        printf("%d ", current->data);

        if (current->left != NULL)
            queue[rear++] = current->left;

        if (current->right != NULL)
            queue[rear++] = current->right;
    }
}

// ---------------- MAIN FUNCTION (MENU) ----------------

int main() {
    struct Node* root = NULL;
    int choice, value;

    while (1) {
        printf("\n================ BST VISUALIZER MENU ================\n");
        printf("1. Insert Node\n");
        printf("2. Delete Node\n");
        printf("3. Search Node\n");
        printf("4. Inorder Traversal\n");
        printf("5. Preorder Traversal\n");
        printf("6. Postorder Traversal\n");
        printf("7. Level Order Traversal\n");
        printf("8. Display Tree Structure\n");
        printf("9. Count Nodes\n");
        printf("10. Height of Tree\n");
        printf("11. Find Minimum Value\n");
        printf("12. Find Maximum Value\n");
        printf("13. Exit\n");
        printf("=====================================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insertNode(root, value);
                printf("Inserted successfully!\n");
                break;

            case 2:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                root = deleteNode(root, value);
                break;

            case 3:
                printf("Enter value to search: ");
                scanf("%d", &value);
                if (searchNode(root, value))
                    printf("Value %d FOUND in BST!\n", value);
                else
                    printf("Value %d NOT FOUND in BST!\n", value);
                break;

            case 4:
                printf("Inorder Traversal: ");
                inorder(root);
                printf("\n");
                break;

            case 5:
                printf("Preorder Traversal: ");
                preorder(root);
                printf("\n");
                break;

            case 6:
                printf("Postorder Traversal: ");
                postorder(root);
                printf("\n");
                break;

            case 7:
                printf("Level Order Traversal: ");
                levelOrder(root);
                printf("\n");
                break;

            case 8:
                printf("BST Tree Structure (Sideways):\n");
                displayTree(root, 0);
                printf("\n");
                break;

            case 9:
                printf("Total Nodes = %d\n", countNodes(root));
                break;

            case 10:
                printf("Height of Tree = %d\n", height(root));
                break;

            case 11:
                printf("Minimum Value = %d\n", findMinValue(root));
                break;

            case 12:
                printf("Maximum Value = %d\n", findMaxValue(root));
                break;

            case 13:
                printf("Exiting Program... Goodbye!\n");
                exit(0);

            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    }

    return 0;
}
