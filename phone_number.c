#include<stdlib.h>
#include<stdio.h>
#include<string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
void generate(int *returnSize, char **output, char *item, char *digits, int i);

char *item_insert(int *returnSize, char **list, char *item)
{
    static int i = 0;
    printf("[%s-%d] i=%d.\n", __func__, __LINE__, i);
    static int count = 0;
    list[i] = malloc(strlen(item)+1);
    printf("[%s] &list[%d]=%p, list[%d]=%p\n", __func__, i, &list[i], i, list[i]);
    *returnSize+=1;
    return strcpy(list[i++], item);
}

void generate(int *returnSize, char **output, char *item, char *digits, int i)
{
    int j;
    char *src = NULL;
    char template[8][5] = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    if(strlen(digits) == i)
    {
        printf("[%s] i=%d\n", __func__, i);
        item_insert(returnSize, output, item);
        return;
    }
    if((src = realloc(src, strlen(item)+2)))
        strcpy(src, item);
    else
    {
        printf("Error memory realloc.\n");
        return;
    }
    for(j = 0; template[digits[i]-'2'][j]; j++)
    {
        src[strlen(item)] = template[digits[i]-'2'][j];
        src[strlen(item)+1] = 0;
        generate(returnSize, output, src, digits, i+1);
    }
    free(src);
    return;
}

char ** letterCombinations(char * digits, int* returnSize){
    //char **output = calloc((1<<(2*strlen(digits))), sizeof(char *));
    *returnSize = 0;
    char **output = calloc(1024, sizeof(char *));
    printf("[%s] output=%p\n", __func__, output);
    if(strlen(digits) == 0)
    {
        output[0] = calloc(1, sizeof(char *));
        return output;
    }
    generate(returnSize, output, "" , digits, 0);
    return output;
}

int main(int argc, char ** argv)
{
    char digits[] = "2";
    int *returnSize = malloc(sizeof(int));
    letterCombinations(digits, returnSize);
    return 0;
}