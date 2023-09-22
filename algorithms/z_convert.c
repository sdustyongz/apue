#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    char c;
    struct node *next;
} Node;

typedef struct
{
    Node *header;
    Node *tail;
} Link;

char *convert(char *s, int numRows)
{
    int len =strlen(s);
    if(numRows == 1)
        return s;
    char * str = s;
    Link arr[numRows];
    memset(arr,0,sizeof(arr));
    char c;
    int i = 0,  flag = 0;
    Node * n ;
    while ((c = *str++) != '\0')
    {
        n = malloc(sizeof(Node));
        n->c = c;
        n->next = NULL;
        if (arr[i].tail == NULL)
        {
            arr[i].tail = arr[i].header = n;
        }
        else
        {
            arr[i].tail->next = n;
            arr[i].tail = n;
        }

        if (!flag)
        {
            if (++i == numRows)
            {
                i-=2;
                flag = 1;
            }
        }
        else
        {
            if(--i < 0){
                i = 1;
                flag = 0;
            }
        }
    }
    int j = 0;
    char * t = malloc(len+1);
    Node * prev;
    for(i = 0 ;i < numRows ; i++){
        Link l = arr[i];
        n = l.header;
        while(n != NULL){
            t[j++] = n->c;
            prev = n;
            n = n->next;
            free(prev);
        }

    }
    t[len]='\0';
    return t;
}

int main(int argc, char *argv[]){

    char * s = "PAYPALISHIRING";
    char * t = convert(s,3);
    printf("%s\n",t);
}