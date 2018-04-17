#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

struct SinhVien
{
	wchar_t* MSSV;
	wchar_t* Ten;
	wchar_t* Khoa;
	int KhoaHoc;
	wchar_t* NgaySinh;
	wchar_t* Email;
	wchar_t* HinhAnh;
	wchar_t* MoTaBanThan;
	wchar_t **SoThich = NULL;
	int SoSoThich = 0;
};

wchar_t* ReplaceStr(wchar_t* str)
{
	for (int i = 0; i < wcslen(str); i++)
	{
		if (str[i] == L'?')
		{
			str[i] = L',';
		}
	}
	return str;
}

int main()
{
	FILE *fin;
	FILE *fout;
	errno_t eIn;
	wchar_t buf[255];
	wchar_t *Str, *next;
	SinhVien *ArrSV = new SinhVien[10];
	eIn = fopen_s(&fin, "database.csv", "r,ccs=UTF-8");

	if (eIn != 0) {
		return 0;
	}

	int i = 0;

	while (fgetws(buf, 1000, fin) != NULL)
	{
		SinhVien sv;
		sv.MSSV = wcstok(buf, L",");
		sv.Ten = wcstok(NULL, L",");
		sv.Khoa = wcstok(NULL, L",");
		sv.KhoaHoc = _wtoi(wcstok(NULL, L","));
		sv.NgaySinh = wcstok(NULL, L",");
		sv.Email = wcstok(NULL, L",");
		sv.HinhAnh = wcstok(NULL, L",");
		sv.MoTaBanThan = ReplaceStr(wcstok(NULL, L","));
		sv.SoThich = new wchar_t*[100];
		Str = wcstok(NULL, L",");

		while (Str != NULL)
		{
			Str = ReplaceStr(Str);
			sv.SoThich[sv.SoSoThich] = Str;
			sv.SoSoThich++;
			Str = wcstok(NULL, L",");
		}
		ArrSV[i] = sv;
		i++;
	}

	fclose(fin);
	return 0;
}