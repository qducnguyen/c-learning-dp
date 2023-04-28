#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int compare_scores(const void* score_a, const void* score_b){
	int a = *(int *)score_a;
	int b = *(int *)score_b;
	return a - b;
}

int compare_scores_desc(const void* score_a, const void* score_b){
	int a = *(int *)score_a;
	int b = *(int *)score_b;
	return b - a;
}


typedef struct {
	int width;
	int height;
} rectangle;


int compare_areas(const void* a, const void* b){
	int area_a = ((rectangle *)a)->width * ((rectangle *)a)->height;
	int area_b = ((rectangle *)b)->width * ((rectangle *)b)->height;
	return area_a - area_b;

}

int compare_names(const void* a, const void* b){
	char** str1 = (char **)a;
	char** str2 = (char **)b;
	return strcmp(*str1, *str2);
}


int compare_areas_desc(const void* a, const void* b){
	return compare_areas(b, a);
}

int compare_names_desc(const void*a, const void* b){
	return compare_names(b, a);
}


int main()
{
	int scores[] = {543, 223, 32, 554, 11, 3, 112};

	int i;

	qsort(scores, 7, sizeof(int), compare_scores_desc);
	puts("These are the scores in order:");
	
	for (i=0; i<7; i++){
		printf("Score = %i\n", scores[i]);
	}

	char *names[] = {"Karen", "Mark", "Brett", "Molly"};
	qsort(names, 4, sizeof(char*), compare_names);
	puts("These are the names in order:");

	for (i=0; i<4;i++){
		printf("%s\n", names[i]);
	}

	return 0;
}

