#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

#define TIME_QUOTA 20

int passed_time = 0;
int count = 0;
int finish_p = 0;
int input_cnt = 0;

typedef struct
{
	int process_id;
	int priority;
	int computing_time;
	int remain_time;
	int turn_around_time;
	int input_time;
	int end_time;
} ReadyQ;

void input_Data(ReadyQ* pr, int process_id, int priority, int computing_time);
void FCFS_Scheduling(ReadyQ* pr, int type, ReadyQ* finish);
void print_Process(ReadyQ* finish);

int main()
{
	int i = 0;
	int flag = 1;
	int type = 0, process_id = 0, priority = 0, computing_time = 0;

	FILE* fp = fopen("./input.txt", "r");
	ReadyQ* finish = malloc(sizeof(ReadyQ)*sizeof(int));
	ReadyQ* process = malloc(sizeof(ReadyQ)*sizeof(int));

	if(fp == NULL)
	{
		printf("SYSTEM >> 파일 열기 오류 | 프로그램을 종료합니다.");
		exit(0);
	}

	while(flag)
	{
		getchar();
		fscanf(fp, "%d %d %d %d", &type, &process_id, &priority, &computing_time);

		switch(type)
		{
			case 0 :
				input_Data(process, process_id, priority, computing_time);

				break;

			case 1 :
				FCFS_Scheduling(process, type, finish);

				break;

			case -1 :
				FCFS_Scheduling(process, type, finish);

				flag = 0;

				break;

			default :
				printf("SYSTEM >> ERROR) 잘못된 타입 입력입니다.\n");
		}

		if(feof(fp) != 0)
		{
			flag = 0;
		}
	}

	fclose(fp);
}

void input_Data(ReadyQ* pr, int process_id, int priority, int computing_time)
{
	pr[count].process_id = process_id;
	pr[count].priority = priority;
	pr[count].computing_time = computing_time;

	pr[count].remain_time = pr[count].computing_time;
	
	count ++;
}

void FCFS_Scheduling(ReadyQ* pr, int type, ReadyQ* finish)
{
	if(type == 1)
	{
		int value = TIME_QUOTA;

		for(int i = input_cnt; i < count; i ++)
		{
			pr[i].input_time = passed_time;

			input_cnt ++;
		}

		for(int i = finish_p; i < count; i ++)
		{
			if(pr[i].remain_time - value <= 0)
			{
				value = value - pr[i].remain_time;

				passed_time += pr[i].remain_time;

				pr[i].end_time = passed_time;
				finish[i] = pr[i];

				pr[i].turn_around_time = pr[i].end_time - pr[i].input_time;

				finish_p += 1;

				break;
			}
			else
			{
				pr[i].remain_time = pr[i].remain_time - TIME_QUOTA;
				passed_time += value;

				break;
			}
		}
	}
	else if(type == -1)
	{
		for(int i = input_cnt; i < count; i++)
		{
			pr[i].input_time = passed_time;
			input_cnt ++;
		}

		for(int i = finish_p; i < count; i ++)
		{
			passed_time += pr[i].remain_time;
			pr[i].remain_time = 0;
			pr[i].end_time = passed_time;

			pr[i].turn_around_time = pr[i].end_time - pr[i].input_time;

			finish[i] = pr[i];
		}

		print_Process(finish);
	}
	else
	{
		printf("SYSTEM >> ERROR) 잘못된 타입 입력입니다.\n");
	}
}

void print_Process(ReadyQ* finish)
{
	float sum = 0;

	printf("-------------------------- 스케줄링 완료 --------------------------\n");
	printf("Process_id\tPriority\tComputing_Time\tTurn_Around Time\n");

	for(int i = 0; i < count; i ++)
	{
		printf("%5d\t\t%5d\t\t%8d\t%8d\t\n", finish[i].process_id, finish[i].priority, finish[i].computing_time, finish[i].turn_around_time);

		sum += finish[i].turn_around_time;
	}

	printf("\nNormalized Average Turn_Around Time : %.2f\n", sum / count);
}
