#include<stdio.h>
int main()
{
  int a,b;
  char op;
  scanf("%d %c %d",&a,&op,&b);
  if (op == '+') printf("%d",a+b);
  else if (op == '-') printf("%d",a-b);
  else if (op == '*') printf("%d",a*b);
  else if (op == '/') printf("%.2f",(float)a/b);
  else if (op == '%') printf("%d",a%b); 
  else printf("Unknown Operator"); 
}
