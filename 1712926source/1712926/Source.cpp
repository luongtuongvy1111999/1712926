#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

struct SinhVien
{
	char* MSSV;
	char* Ten;
	char* Khoa;
	int KhoaHoc;
	char* NgaySinh;
	char* HinhAnh;
	char* MoTaBanThan;
	char **SoThich = NULL;
};

char* ReplaceStr(char* str)
{
	for (int i = 0; i < strlen(str); i++)
	{
		if (str[i] == '?')
		{
			str[i] = ',';
		}
	}
	return str;
}
int main()
{
	FILE *fin;
	FILE *fout;
	errno_t eIn;
	char buf[255];
	char *Str, *next;
	SinhVien sv;

	eIn = fopen_s(&fin, "database.csv", "r");

	if (eIn != 0) {
		return 0;
	}

	while (fgets(buf, 255, fin) != NULL)
	{

		//fprintf(fout, "%s", buf)
		sv.MSSV = strtok(buf, ",");
		sv.Ten = strtok(NULL, ",");
		sv.Khoa = strtok(NULL, ",");
		sv.KhoaHoc = atoi(strtok(NULL, ","));
		sv.NgaySinh = strtok(NULL, ",");
		sv.HinhAnh = strtok(NULL, ",");
		sv.MoTaBanThan = strtok(NULL, ",");
		sv.SoThich = new char*[100];
		Str = strtok(NULL, ",");
		int i = 0;
		while (Str != NULL)
		{
			Str = ReplaceStr(Str);
			sv.SoThich[i] = Str;
			Str = strtok(NULL, ",");
			i++;
		}
	}
	fclose(fin);
	return 0;
}