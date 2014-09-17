#include <stdio.h>
#include <stdlib.h>    /* srand, rand */
#include <time.h>       /* time */
#define MAX 200003
struct cell{
	
	long long int key;
	long long int random_no;
	int collision;
	struct cell *next_level;
	};
	struct collision_keys
	{
		long long int key;
		long long int index;
	};
	
int extract_input(char *,struct cell**,struct collision_keys **);
void construct_second_level(struct cell**,struct collision_keys **,int);
long long int generate_random_number(int);
int main()
{
	struct cell *base_table[MAX];
	long long i,limit,size,j;
	struct collision_keys **c=NULL;
	for(i=0;i<MAX;i++)
	{
		base_table[i]=(struct cell*)malloc(sizeof(struct cell));
		base_table[i]->key=-1;
		base_table[i]->next_level=NULL;
		base_table[i]->collision=0;
	}
	size=extract_input("input.txt",base_table,c);
	construct_second_level(base_table,c,size);
	for(i=0;i<MAX;i++)
	{
		if(base_table[i]->next_level!=NULL)
		{
			limit=(base_table[i]->collision)*(base_table[i]->collision);
			for(j=0;j<limit;j++)
			{
				if((base_table[i]->next_level)[j].collision>0)
					printf("%d\n",(base_table[i]->next_level)[j].collision);
			}
		}
	}
return 0;
}
int extract_input(char *file_name,struct cell**a,struct collision_keys **c_key)
{
	int r,nr,cr;
	long long int index,num=0,i,c,sum=0,rand,n,k=0,x;
	FILE *f;
	char* line;
	ssize_t len=0;
	ssize_t read;
	f=fopen(file_name,"r");
	if(f)
	{	while((read=getline(&line,&len,f))!=-1)
		{
			i=0;
			while((int)line[i]!=10)
			{
				while((int)line[i]!=44&&(int)line[i]!=10)
				{
					if((int)line[i]==32)
					{	
						i++;                               //spaces removed
					}
					else
					{
						r=(int)line[i]-48;
						num=num*10+r;
						i++;
					}
				}
				x=MAX;
				c=generate_random_number(x);
				rand=c;
				n=num;
				while(rand>0||n>0)
				{
					cr=rand%10;
					nr=n%10;
					rand=rand/10;
					n=n/10;
					sum=sum+nr*cr;
				}
				index=sum%MAX;
				if(a[index]->key!=-1)
				{	
					(a[index]->collision)++;
					c_key[k]=(struct collision_keys*)malloc(sizeof(struct collision_keys));
					c_key[k]->key=num;
					c_key[k]->index=index;
					k++;
				}
				else
				{
					a[index]->key=num;
					a[index]->random_no=c;
				}
				num=0;
				sum=0;
				if((int)line[i]!=10)                           //if it is not the last number in the line
					i++;
			}			
		}
	}
	printf("\nk=%lld\n",k);
	return k;
}
long long int generate_random_number(int k)
{
	long long int r;
	r = rand() % k;
	return r;
}
void construct_second_level(struct cell **arr,struct collision_keys **b,int b_size)
{
	struct cell **second_level_table=NULL;
	long long int i,j,num,c,loc;
	long long int n,r,sum=0;
	int nr,cr;
	for(i=0;i<MAX;i++)
	{
		if(arr[i]->collision>0)
		{
			n=(arr[i]->collision)*(arr[i]->collision);
			for(j=0;j<n;j++)
			{
				second_level_table[j]=(struct cell*)malloc(sizeof(struct cell));
				second_level_table[j]->next_level=NULL;
				second_level_table[j]->key=-1;
				second_level_table[j]->random_no=0;
				second_level_table[j]->collision=0;
			}
			arr[i]->next_level=second_level_table[0];
		}
	}	
	for(i=0;i<b_size;i++)
	{
		num=b[i]->key;
		c=generate_random_number(num);
		n=num;
		r=c;
		while(n>0||c>0)
		{
			nr=n%10;
			cr=r%10;
			n=n/10;
			r=r/10;
			sum=sum+nr*cr;
		}		
		loc=sum;
		sum=0;
		if((arr[b[i]->index]->next_level)[loc].key!=-1)
		{
			((arr[b[i]->index]->next_level)[loc].collision)++;
		}
		else
		{
			(arr[b[i]->index]->next_level)[loc].key=b[i]->key;
		}
		printf("\nh=%d\n",(arr[b[i]->index]->next_level)[loc].collision);
	}
	//printf("\nHey\n");
}
