

int a = 10;
float b = 20.5;
char ch = 'A';
char str[] = "Hello World";

a++;
b += 5;
a = a + b;

if (a > 10)
{
    printf("%s", str);
}
else
{
    printf("Value is small");
}

for (int i = 0; i < 5; i++)
{
    a = a + i;
}

return 0;