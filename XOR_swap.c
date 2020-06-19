void swap(int *a, int *b)
{
    //int temp = *a;
    //*a = *b;
    //*b = temp;
    printf("[%s-%d] *a=0x%08X, *b=0x%08X || *a^*b=0x%08X, ", __func__, __LINE__, *a, *b, *a^*b);
    *a ^= *b;
    printf("*a=0x%08X, *b=0x%08X, ", *a, *b);
    *b ^= *a;
    printf("*a=0x%08X, *b=0x%08X, ", *a, *b);
    *a ^= *b;
    printf("*a=0x%08X, *b=0x%08X\n", *a, *b);
}

int main()
{
    int nums[] = {1, 2, 3};
    swap(&nums[0], &nums[1]);
    return 0;
}