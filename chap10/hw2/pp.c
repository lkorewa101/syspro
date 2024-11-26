#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct node {
    int data;
    struct node *next;
};

void addq(struct node **head, struct node **tail, int data) {
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
        *tail = newNode;
    } else {
        (*tail)->next = newNode;
        *tail = newNode;
    }
}

int delete(struct node **head, struct node **tail) {
    if (*head == NULL) {
        return -1;
    }

    struct node *temp = *head;
    int data = temp->data;
    *head = (*head)->next;

    if (*head == NULL) {
        *tail = NULL;
    }

    free(temp);
    return data;
}

void printAndEmptyQueue(struct node **head, struct node **tail) {
    int data;
    while ((data = delete(head, tail)) != -1) {
        printf("%d\n", data);
    }
}

int main() {
    struct node *head = NULL, *tail = NULL;

    while (1) {
        char input[10];
        scanf("%s", input);

        int isNumber = 1;
        for (int i = 0; input[i] != '\0'; i++) {
            if (!isdigit(input[i])) {
                isNumber = 0;
                break;
            }
        }

        if (isNumber) {
            int data = atoi(input);
            addq(&head, &tail, data);
        } else {
            printf("Print queue\n");
            printAndEmptyQueue(&head, &tail);
            break;
        }
    }

    return 0;
}

