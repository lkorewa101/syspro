#include <stdio.h>
#include <stdlib.h>

struct store {
	int id;
	char name;
	char category;
	int expiredDate;
	int stock;
};

int main(int argc, char* argv[]) {
	struct store rec;
	FILE *fp;

	if(argc != 2) {
		exit(1);
	}

	fp = fopen(argv[1], "wb");
	printf("%-2s %-13s %-7s %-12s %-5s\n", "id", "name", "category", "expired date", "stock");
	while(scanf("%d %s %s %d %d", &rec.id, rec.name, rec.category, &rec.expiredDate, &rec.stock) == 5) {
		fwrite(&rec, sizeof(rec), 1, fp);
	}

	fclose(fp);
	exit(0);
}
