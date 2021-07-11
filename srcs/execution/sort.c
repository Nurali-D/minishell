#include "minishell.h"

// void	bubblesort(char **values)
// {
// 	int		i;
// 	int		j;
// 	int		arrlen;
// 	char	*tmp;

// 	i = 0;
// 	arrlen = ft_arrlen(values);
// 	while (i + 1 < arrlen)
// 	{
// 		j = 0;
// 		while (j + 1 < arrlen - i)
// 		{
// 			if ((ft_strcmp(values[j], values[j + 1])) > 0)
// 			{
// 				tmp = values[j];
// 				values[j] = values[j + 1];
// 				values[j + 1] = tmp;
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// }

// void	bubblesort(t_env *head){
//	 t_env *left = head;		         //Первый элемент — это пусть будет голова
//     t_env *right = head->next;          //Второй элемент — это пусть будет следующий за головой элемент
//     t_env *temp = NULL;              //Временное звено для хранения переставляемого всех значений переставляемого звена
 
//     while (left->next){                 //Обходим по всем звеньям, за исключением крайнего правого
//             while (right){              //Обходим по всем звеньям, включая крайний правый (по всем относительно первого левого на текущий момент)
//                     if ((ft_strcmp(left->key, right->key)) > 0){        //Проверяем необходимость перестановки
//                         temp = left->next;              //И переставляем все внутренние элементы, за исключением указателей связи, местами
//                         left->next = right->next;             //Сейчас у нас имеется только x, поэтому только его
//                         right->next = temp;             //иначе бы  нужно было это проделывать для каждого несвязующего элемента
//                     }
//                 right = right->next;                    //не забываем направлять указатель на следующий элемент (по подобию инкремента), иначе цикл зависнет
//             }
//         left = left->next;                              //не забываем направлять указатель на следующий элемент (по подобию инкремента), иначе цикл зависнет
//         right = left->next;                             //Поскольку второй указатель убежал немного вперёд, обязательно возвращаем его назад, это следующий элемент относительно текущего первого
//     }
// 	print_export(head);
// }

/* function to swap data of two nodes a and b*/
// void swap(t_env *a, t_env *b)
// {
//     t_env *temp = a;
//     a = b;
//     b = temp;
// }

// void bubblesort(t_env *start)
// {
//     int swapped;
//     t_env *ptr1;
//     t_env *lptr = NULL;
  
//     /* Checking for empty list */
//     if (start == NULL)
//         return;
  
//     do
//     {
//         swapped = 0;
//         ptr1 = start;
  
//         while (ptr1->next != lptr)
//         {
//             if ((ft_strcmp(ptr1->key, ptr1->next->key)) > 0)
//             { 
//                 swap(ptr1, ptr1->next);
//                 swapped = 1;
//             }
//             ptr1 = ptr1->next;
//         }
//         lptr = ptr1;
//     }
//     while (swapped);
// }

// void sort(struct node **list) // selection sort
// {
// 	if (!*list) return;
// 	struct node **minadr = list;
// 	struct node *cur = *list;
// 	int min = (*list)->val;

// 	while (cur)
// 	{
// 		if (cur->val<min)
// 		{
// 			min=cur->val;
// 			minadr=&(cur->next);
// 		}
// 		cur=cur->next;
// 	}
// 	if (minadr!=list)
// 	{
// 		cur=*minadr;
// 		*minadr=*list;
// 		*list=cur;
// 	}
// 	sort(&((*list)->next));
// }

void	bubblesort(t_env *head)
{
	int i;
	t_env	*p;
	t_env	*key;
	t_env	*result;

	result = head;
	head = head->next;
	result->next = NULL;
	while (head->next != NULL)
	{
		key = head;
		head = head->next;
		if ((i = ft_strcmp(result->key, key->key)) < 0)
		{
			key->next = result;
			result = key;
		}
		else
		{
			p = result;
			while (p->next != NULL)
			{
				if ((i = ft_strcmp(key->key, p->next->key)) > 0)
					break;
				p = p->next;
			}
			key->next = p->next;
			p->next = key;
		}
	}
	head = result;
}

// void bubblesort(t_env *head) 
// {
// 	t_env *p1,* p2;
// 	t_env *list;

// 	list = head;
// 	//	int n;float t;char pk[10];
		
// 	if (list != NULL) {										   //если стек не пустой
// 		while (list->next != NULL) 
// 		{														// пока стек не закончится
// 			p1=list;
// 			p2=p1->next;
// 			do 
// 			{
// 				if ((ft_strcmp(p1->key, p2->key)) > 0)
// 				{
// 					p1->next = p2->next;
// 					p2->next = p1;
// 					p1 = p2;
// 				}
// 				p2 = p2->next;
// 			}
// 			while (p2 != NULL);
// 				list = list->next;
// 		}
// 	}
// }