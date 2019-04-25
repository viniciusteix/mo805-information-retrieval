#include "MO445.h"
#include <stdio.h>
#include <dirent.h>
#include <string.h>

struct S_image{
	char name[1024];
	Image *img;
};

struct S_features{
	char name_query[1024];
	double *distances;
	char **result_names;
};

int partition (struct S_features arr, int low, int high) { 
	double pivot = arr.distances[high];
	int i = (low - 1);

	for (int j = low; j <= high- 1; j++) { 
		if (arr.distances[j] <= pivot) { 
			i++;
			double temp = arr.distances[i];
			arr.distances[i] = arr.distances[j];
			arr.distances[j] = temp;

			char name[1024];
			strcpy(name,arr.result_names[i]);
			strcpy(arr.result_names[i],arr.result_names[j]);
			strcpy(arr.result_names[j],name);
		} 
	}
	
	double temp = arr.distances[i+1];
	arr.distances[i+1] = arr.distances[high];
	arr.distances[high] = temp;

	char name[1024];
	strcpy(name,arr.result_names[i+1]);
	strcpy(arr.result_names[i+1],arr.result_names[high]);
	strcpy(arr.result_names[high],name);

	return (i + 1); 
} 

void quickSort(struct S_features arr, int low, int high) { 
	if (low < high) { 
		int pi = partition(arr, low, high); 

		quickSort(arr, low, pi - 1); 
		quickSort(arr, pi + 1, high); 
	} 
} 

int main(int argc,char **argv){
	
	int size, i = 0, j, fixedlen = 1400, len_result = 20;

	/* Estrutura para ler todas as imagens do diretorio imgs/ */
	char dir_name[1024] = "/home/vinicius/Área de Trabalho/mpeg7_conv/";
	// char dir_name[1024] = "/home/vinicius/Dropbox/Mestrado - IC-UNICAMP/1st Semester/Information Retrieval/assignment 07/MO445-descriptors/examples/imgs/";
	DIR *d;
	struct dirent *dir;
	d = opendir(dir_name);

	/* Estrutura para salvar os resultados */
	FILE * fp;
	fp = fopen ("results.csv","w");

	/* Estrutura para salvar as imagens */
	struct S_image *imgs;
	imgs = calloc(fixedlen,sizeof(struct S_image));
	
	/* Estrutura para salvar os vetores de caractericas de Segment Saliences */
	FeatureVector1D ** v_ss;
	v_ss = calloc(fixedlen,sizeof(FeatureVector1D));

	/* Estrutura para salvar os vetores de caractericas de Multiscale Fractal Dimension */
	FeatureVector1D ** v_mfd;
	v_mfd = calloc(fixedlen,sizeof(FeatureVector1D));

	/* Estrutura para salvar os resultados das distancias */
	struct S_features *sfeatures_ss;
	sfeatures_ss = calloc(fixedlen,sizeof(struct S_features));

	struct S_features *sfeatures_mfd;
	sfeatures_mfd = calloc(fixedlen,sizeof(struct S_features));

	printf("Lendo imagens...\n");
	
	if (d){
		while ((dir = readdir(d)) != NULL){
			if(strcmp(dir->d_name,".") == 1 && strcmp(dir->d_name,"..") == 1){
				char image_url[1024];
				strcpy(image_url, dir_name);
				strcat(image_url, dir->d_name);
				strcpy(imgs[i].name, dir->d_name);
				imgs[i].img = ReadImage(image_url);
				i++;
			}
		}
		closedir(d);
	}


	size = i;

	printf("%d\n", size);
	printf("Extraindo caracteristicas...\n");

	/* Extracao dos vetores de caracteristicas */
	for(i = 0; i < size; i++){
		v_ss[i] = SS_ExtractionAlgorithm(imgs[i].img);
		v_mfd[i] = MS_ExtractionAlgorithm(imgs[i].img);
	}

	printf("Calculando as distancias...\n");

	for(i = 0; i < size; i++){
		sfeatures_ss[i].result_names = malloc(sizeof(char *) * size);
		sfeatures_mfd[i].result_names = malloc(sizeof(char *) * size);

		sfeatures_ss[i].distances = calloc(size,sizeof(double));
		sfeatures_mfd[i].distances = calloc(size,sizeof(double));
	
		for(j = 0; j < size; j++){
			double vss = SS_DistanceAlgorithm(v_ss[i],v_ss[j]);
			strcpy(sfeatures_ss[i].name_query,imgs[i].name);
			sfeatures_ss[i].distances[j] = vss;
			sfeatures_ss[i].result_names[j] = (char*) malloc(strlen(imgs[j].name) + 1);
			strcpy(sfeatures_ss[i].result_names[j],imgs[j].name);

			double vmdf = MS_DistanceAlgorithm(v_mfd[i],v_mfd[j]);
			strcpy(sfeatures_mfd[i].name_query,imgs[i].name);
			sfeatures_mfd[i].distances[j] = vmdf;
			sfeatures_mfd[i].result_names[j] = (char*) malloc(strlen(imgs[j].name) + 1);
			strcpy(sfeatures_mfd[i].result_names[j],imgs[j].name);
		}
	}

	printf("Ordenando os resultados...\n");

	for(i = 0; i < size; i++){
		quickSort(sfeatures_ss[i],0,size-1);
		quickSort(sfeatures_mfd[i],0,size-1);
	}

	printf("Salvando os resultados mais proximos\n");
	
	printf("Segment Saliences\n");
	for(i = 0; i < size; i++){
		fprintf(fp,"1 %s", sfeatures_ss[i].name_query);
		for(j = 0; j < len_result; j++){
			fprintf(fp," %s", sfeatures_ss[i].result_names[j]);
		}
		fprintf(fp,"\n");
	}

	printf("Multiscale Fractal Dimension\n");
	for(i = 0; i < size; i++){
		fprintf(fp,"2 %s", sfeatures_mfd[i].name_query);
		for(j = 0; j < len_result; j++){
			fprintf(fp," %s", sfeatures_mfd[i].result_names[j]);
		}
		fprintf(fp,"\n");
	}


	fclose (fp);

	printf("Destruindo as imagens e vetores de caracteristicas...\n");

	/* Liberando memoria */
	for(i = 0; i < size; i++){
		DestroyImage(&imgs[i].img);
		DestroyFeatureVector1D(&v_ss[i]);
		DestroyFeatureVector1D(&v_mfd[i]);
	}

	return 0;
}