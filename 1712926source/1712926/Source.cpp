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
	int SoSoThich = 1;
};

struct OptionProfile
{
	bool NgaySinh = true;;
	bool Email = true;
	bool MoTaBanThan = true;
	bool SoThich = true;
};

int CountSinhVien() {
	int count = 0;
	wchar_t ch[1000];
	FILE *fin;
	errno_t eIn;
	eIn = fopen_s(&fin, "database.csv", "r,ccs=UTF-8");
	if (eIn != 0)
	{
		return 0;
	}
	while (fgetws(ch, 1000, fin) != NULL) {
		count++;
	}
	return count;
}

SinhVien ReadingCSV(SinhVien sv, wchar_t buf[]) {
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
	//sv.SoThich = new wchar_t*[100];
	Str = wcstok(NULL, L"\"");
	Str = wcstok(NULL, L"\"");
	//wchar_t *A = Str;
	//sv.SoSoThich = CountSoThich(Str);
	sv.SoThich = (wchar_t **)malloc(sv.SoSoThich*sizeof(wchar_t**));
	//for (int i = 0; i < sv.SoSoThich; i++){
	while (Str != NULL) {
		sv.SoThich = (wchar_t **)realloc(sv.SoThich, sv.SoSoThich*sizeof(wchar_t**));
		sv.SoThich[sv.SoSoThich] = Str;
		sv.SoSoThich++;
		Str = wcstok(NULL, L"\"");
		Str = wcstok(NULL, L"\"");
	}
	//}
	return sv;
}

void WritingHTML(SinhVien sv, OptionProfile option) {
	setlocale(LC_ALL, "en_US.UTF-8");
	FILE *fout;

	//errno_t eOut;
	wchar_t *str = new wchar_t[50];
	wchar_t s[20] = L".\\Website\\";
	wcscpy(str, s);
	wcscat(str, sv.MSSV);
	wcscat(str, L".html");
	//eOut = fopen_s(&fout, str, "w,ccs=UTF-8");
	fout = _wfopen(str, L"w,ccs=UTF-8");


	fwprintf(fout, L"%s", L"<!DOCTYPE html>");
	fwprintf(fout, L"%s", L"<html xmlns='http://www.w3.org/1999/xhtml'>");
	fwprintf(fout, L"%s", L"<head>");
	fwprintf(fout, L"%s", L"<meta http-equiv='Content-Type' content='text/html;charset=utf-8'/>");
	fwprintf(fout, L"%s", L"<link rel='stylesheet' type='text/css' href='personal.css'/>");
	fwprintf(fout, L"%s %s %s", L"<title>HCMUS -", sv.Ten, L"</title>");
	fwprintf(fout, L"%s", L"</head>");
	fwprintf(fout, L"%s", L"<body>");
	fwprintf(fout, L"%s", L"<div class='Layout_container'>");
	fwprintf(fout, L"%s", L"<div class='Layout_Banner'>");
	fwprintf(fout, L"%s", L"<div><img id='logo' src='Images/logo.jpg' height='105'/></div>");
	fwprintf(fout, L"%s", L"<div class='Header_Title'>TRƯỜNG ĐẠI HỌC KHOA HỌC TỰ NHIÊN</div>");
	fwprintf(fout, L"%s", L"</div>");
	fwprintf(fout, L"%s", L"<div class='Layout_MainContents'>");
	fwprintf(fout, L"%s", L"<div class='Personal_Main_Information'>");
	fwprintf(fout, L"%s", L"<div class='Personal_Location'>");
	fwprintf(fout, L"%s", L"<img src='Images/LogoFooter.jpg' width='27' height='33'/>");

	//Name
	fwprintf(fout, L"%s", L"<div class='Personal_FullName'>");
	fwprintf(fout, L"%s %s %s %s", sv.Ten, L"-", sv.MSSV, L"</div>");
	fwprintf(fout, L"%s %s %s", L"<div class='Personal_Department'>KHOA ", sv.Khoa, L"</div>");
	fwprintf(fout, L"%s", L"<br />");
	fwprintf(fout, L"%s", L"<div class='Personal_Phone'>");
	fwprintf(fout, L"%s %s", L"Email:", sv.Email);
	fwprintf(fout, L"%s", L"</div>");
	fwprintf(fout, L"%s", L"<br/>");
	fwprintf(fout, L"%s", L"<br/>");
	fwprintf(fout, L"%s", L"</div>");
	fwprintf(fout, L"%s", L"<div class='Personal_HinhcanhanKhung'>");
	fwprintf(fout, L"%s%s%s", L"<img src='Images/", sv.HinhAnh, L"' class='Personal_Hinhcanhan'/>");
	fwprintf(fout, L"%s", L"</div>");
	fwprintf(fout, L"%s", L"</div>");
	fwprintf(fout, L"%s", L"<div class='MainContain'>");
	fwprintf(fout, L"%s", L"<div class='MainContain_Top'>");
	fwprintf(fout, L"%s", L"<div class='InfoGroup'>Thông tin cá nhân</div>");
	fwprintf(fout, L"%s", L"<div>");
	fwprintf(fout, L"%s", L"<ul class='TextInList'>");
	fwprintf(fout, L"%s %s %s", L"<li>Họ và tên:", sv.Ten, L"</li>");
	fwprintf(fout, L"%s %s %s", L"<li>MSSV:", sv.MSSV, L"</li>");
	fwprintf(fout, L"%s %s %s", L"<li>Sinh viên khoa", sv.Khoa, L"</li>");
	if (option.NgaySinh == true)
	{
		fwprintf(fout, L"%s %s %s", L"<li>Ngày sinh :", sv.NgaySinh, L"</li>");
	}

	if (option.Email == true)
	{
		fwprintf(fout, L"%s %s %s", L"<li>Email :", sv.Email, L"</li>"); // email???
	}

	fwprintf(fout, L"%s", L"</ul>");
	fwprintf(fout, L"%s", L"</div>");

	if (option.SoThich == true)
	{
		fwprintf(fout, L"%s", L"<div class = 'InfoGroup'>Sở thích</div>");
		fwprintf(fout, L"%s", L"<div>");
		fwprintf(fout, L"%s", L"<ul class='TextInList'>");

		//Sở thích
		for (int i = 1; i <= sv.SoSoThich; i++)
		{
			fwprintf(fout, L"%s %s %s", L"<li>", sv.SoThich[i], L"</li>");
		}

		//fwprintf(fout, L"%s", L"<li>Ẩm thực : bún riêu, bún thịt nướng</li>");
		fwprintf(fout, L"%s", L"</ul>");
		fwprintf(fout, L"%s", L"</div>");
	}

	if (option.MoTaBanThan == true)
	{
		fwprintf(fout, L"%s", L"<div class = 'InfoGroup'>Mô tả</div>");
		fwprintf(fout, L"%s", L"<div class = 'Description'>");
		fwprintf(fout, L"%s", sv.MoTaBanThan);
		fwprintf(fout, L"%s", L"</div>");
	}


	fwprintf(fout, L"%s", L"</div>");
	fwprintf(fout, L"%s", L"</div>");
	fwprintf(fout, L"%s", L"</div>");
	fwprintf(fout, L"%s", L"<div class='Layout_Footer'>");
	fwprintf(fout, L"%s", L"<div class = 'divCopyright'>");
	fwprintf(fout, L"%s", L"<br/>");
	fwprintf(fout, L"%s", L"<img src='Images/LogoFooter_gray.jpg' width='34' height='41'/><br/>");
	fwprintf(fout, L"%s", L"<br/>");
	fwprintf(fout, L"%s", L"@2018</br>");
	fwprintf(fout, L"%s", L"Đồ án giữa kỳ</br>");
	fwprintf(fout, L"%s", L"Kỹ thuật lập trình</br>");
	fwprintf(fout, L"%s", L"17CTT7</br>");
	fwprintf(fout, L"%s", L"1712926 - Lương Tường Vy</br>");
	fwprintf(fout, L"%s", L"</div>");
	fwprintf(fout, L"%s", L"</div>");
	fwprintf(fout, L"%s", L"</div>");
	fwprintf(fout, L"%s", L"</body>");
	fwprintf(fout, L"%s", L"</html>");
	fclose(fout);
}

OptionProfile ResetOption()
{
	OptionProfile option;
	option.Email = false;
	option.MoTaBanThan = false;
	option.NgaySinh = false;
	option.SoThich = false;
	return option;
}

OptionProfile Option()
{
	OptionProfile option;
	option = ResetOption();
	printf("---------------Option Profile --------------\n");
	//char Answer;
	printf("Ban muon hien thi muc nao tren trang web?\n");
	printf("1: Ngay sinh \n");
	printf("2: Email \n");
	printf("3: Mo ta ban than \n");
	printf("4: So thich \n");
	printf("0: Tro lai \n");

	int n;
	do
	{
		printf("Chon: ");
		scanf_s("%d", &n);
		switch (n)
		{
		case 1:
			option.NgaySinh = true;
			break;
		case 2:
			option.Email = true;
			break;
		case 3:
			option.MoTaBanThan = true;
			break;
		case 4:
			option.SoThich = true;
			break;
		default:
			break;
		}
	} while (n != 0);

	return option;

}

int main()
{
	FILE *fin;
	errno_t eIn;
	SinhVien *ArrSV = NULL;
	int SoSV;

	SoSV = CountSinhVien();
	ArrSV = (SinhVien*)malloc(SoSV * sizeof(SinhVien));

	eIn = fopen_s(&fin, "database.csv", "r,ccs=UTF-8");
	if (eIn != 0)
	{
		return 0;
	}
	int i = 0;
	wchar_t *buf = (wchar_t*)malloc(1000 * sizeof(wchar_t));
	while (fgetws(buf, 1000, fin) != NULL)
	{
		SinhVien sv;
		sv = ReadingCSV(sv, buf);
		ArrSV[i] = sv;
		//WritingHTML(ArrSV[i],option);
		i++;
		buf = (wchar_t*)malloc(1000 * sizeof(wchar_t));
	}

	OptionProfile option;
	do
	{

		int opt;
		printf("-------------Sinh Vien-------------\n");
		printf("Chon cac tuy chon sau:\n");
		printf("1: Tuy chinh profile page \n");
		printf("2: Tuy chon in profile page \n");
		printf("0: Thoat \n");
		printf("Chon: ");
		scanf_s("%d", &opt);
		if (opt == 0)
			break;
		switch (opt)
		{
		case 1:
			option = Option();
			break;
		case 2:
		{

				  printf("----------Danh sach sinh vien------------ \n");
				  for (int j = 0; j < SoSV; j++)
				  {
					  printf("%d ", j + 1);
					  wprintf(L" %s\n", ArrSV[j].MSSV);
				  }

				  int n;

				  do
				  {
					  printf("Nhap stt (nhap 0 de tro lai): ");
					  scanf_s("%d", &n);
					  if (n == 0)
						  break;
					  else
					  {
						  if (n <= SoSV && n > 0)
							  WritingHTML(ArrSV[n - 1], option);
						  else
						  {
							  printf("==> Khong ton tai, xin nhap lai \n");
						  }
					  }
				  } while (true);
				  break;
		}
		default:
			break;
		}
	} while (true);

	fclose(fin);
	delete[] ArrSV;
	delete[] buf;
	return 0;
}