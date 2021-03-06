#include <stdio.h>
#include <stdlib.h>

struct list
{
	int value;	// Вершина графа
	struct list* next;	// Указатель на следующую смежную вершину
};

typedef struct list* LNode;


void add_bond(LNode top, LNode graph, int l_value)	// Добавление элемента списка
{
	LNode temp = top;
	while (temp->next)
	{
		temp = temp->next;
		if (temp->value == l_value)
		{
			return;
		}
	}
	temp->next = (LNode)malloc(sizeof(struct list));
	temp->next->value = l_value;
	temp->next->next = NULL;
}

int make_dot(LNode top, FILE* fp)
{
	LNode temp = top;
	int e = 0;
	while (temp->next)
	{
			fprintf(fp, "\t%d -> %d ;\n",
				top->value, temp->next->value);
			temp = temp->next; e++; 
	}return e;
}

void free_list(LNode pg)
{
	LNode p;
	while (pg->next != NULL)
	{
		p = pg->next->next;
		free(pg->next);
		pg->next = p;
	}
}

int main(void)
{
	int i;
	FILE* fp = fopen("graph.dot", "w");
	fputs("digraph {\n", fp);
	int col;
	printf("Количество \n\n");
	scanf("%d", &col);
	int nom;
	printf("Номер удаленной вершины \n\n");
	scanf("%d", &nom);
	
	int *mass1;
    mass1 = (int*) malloc(col);
	
	LNode pg;
	LNode graph = (LNode)malloc(col * sizeof(struct list)); // Создание массива списков
	int j = 1;
	for (int i = 0; i < col; ++i, ++j)
	{
		graph[i].value = j;
		graph[i].next = NULL;
	}
	int m;
	int c = 0;
	for (i = 0; i < col; ++i)
	{	
	
			pg = &graph[i];
			printf("Введите смежные с %d вершины:\n", i+1);
			while (scanf(" %d", &c) != EOF && c != 0)
			{
				if (c >= 1 && c <= col)
				{	
					if((c!=nom) && (i+1!=nom))
					{
					mass1[c]++;
					mass1[i+1]++;
					add_bond(pg, graph, c);
					};
				}
				else
				{
					printf("Введите смежные с %d вершины:\n", i+1);
				}
			}
			printf("Связи с %d вершиной установлены. Продолжаем\n\n", i + 1);
		
	}
	printf("Вершины кончились\n\n");

	// создание dot
	int r;
	for (i = 0; i < col; ++i)
	{
		pg = &graph[i];
		r=make_dot(pg, fp);
		if (r == 0) {if (i+1!=nom){
			fprintf(fp, "\t%d;\n",
		i+1);}
		}
	}
	fprintf(fp, "}");

	
	for (i = 0; i < col*col; i++)
	{for (j = 0; j < col; j++)
	if (mass1[j+1]==i)
	{
		if (j+1!=nom){printf("%d %d\n", j+1, mass1[j+1]);}
	}}
	//очищение памяти
	for (i = 0; i < col; ++i)
	{
		pg = &graph[i];
		free_list(pg);
	}
	free(graph);

	fclose(fp);
	
	system("dot -Tpng graph.dot -o graph.png");
	system("xdg-open graph.png");
	return 0;
}
