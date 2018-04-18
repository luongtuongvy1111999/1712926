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

SinhVien ReadingCSV(SinhVien sv, wchar_t buf[]){
	wchar_t *Str = NULL;
	sv.MSSV = wcstok(buf, L"\",");
	sv.Ten = wcstok(NULL, L"\",");
	sv.Khoa = wcstok(NULL, L"\",");
	sv.KhoaHoc = _wtoi(wcstok(NULL, L"\","));
	sv.NgaySinh = wcstok(NULL, L"\",");
	sv.Email = wcstok(NULL, L"\",");
	sv.HinhAnh = wcstok(NULL, L"\",");
	Str = wcstok(NULL, L"\"");
	sv.MoTaBanThan = wcstok(NULL, L"\"");
	sv.SoThich = new wchar_t*[100];
	Str = wcstok(NULL, L"\"");
	Str = wcstok(NULL, L"\"");
	while (Str != NULL){
		sv.SoThich[sv.SoSoThich] = Str;
		sv.SoSoThich++;
		Str = wcstok(NULL, L"\"");
		Str = wcstok(NULL, L"\"");
	}
	return sv;
}


int main()
{
	FILE *fin;
	errno_t eIn;
	wchar_t buf[1000];
	
	SinhVien *ArrSV = new SinhVien[10];

	eIn = fopen_s(&fin, "database.csv", "r,ccs=UTF-8");

	if (eIn != 0) {
		return 0;
	}

	int i = 0;

	while (fgetws(buf, 1000, fin) != NULL)
	{
		SinhVien sv;
		sv = ReadingCSV(sv, buf);
		ArrSV[i] = sv;
		i++;
	}
	fclose(fin);
	return 0;
}