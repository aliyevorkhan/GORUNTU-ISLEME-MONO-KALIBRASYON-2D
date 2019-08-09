#include "fonksiyonlar.h"
#include<opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <Eigen/Dense>
#include <Eigen/src/SVD/JacobiSVD.h>

using namespace cv;
using namespace Eigen;

int iKalibrasyonNoktaSayisi = 0;

std::vector<int>vektorImge;
std::vector<int>vektorDunya;

Mat source = imread("../x64/Debug/goruntu.bmp"); // uzerinde kesisim noktalarini gosterecegimiz goruntu

VideoCapture vCap(0);

vector<int> noktalar;
vector<int> kesisimler;
vector<int> iKalibrasyon;
vector<int> dKalibrasyon;


BYTE* LoadBMP(int% width, int% height, long% size, LPCTSTR bmpfile)
{
	// declare bitmap structures
	BITMAPFILEHEADER bmpheader;
	BITMAPINFOHEADER bmpinfo;
	// value to be used in ReadFile funcs
	DWORD bytesread;
	// open file to read from
	HANDLE file = CreateFile(bmpfile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if (NULL == file)
		return NULL; // coudn't open file

					 // read file header
	if (ReadFile(file, &bmpheader, sizeof(BITMAPFILEHEADER), &bytesread, NULL) == false) {
		CloseHandle(file);
		return NULL;
	}
	//read bitmap info
	if (ReadFile(file, &bmpinfo, sizeof(BITMAPINFOHEADER), &bytesread, NULL) == false) {
		CloseHandle(file);
		return NULL;
	}
	// check if file is actually a bmp
	if (bmpheader.bfType != 'MB') {
		CloseHandle(file);
		return NULL;
	}
	// get image measurements
	width = bmpinfo.biWidth;
	height = abs(bmpinfo.biHeight);

	// check if bmp is uncompressed
	if (bmpinfo.biCompression != BI_RGB) {
		CloseHandle(file);
		return NULL;
	}
	// check if we have 24 bit bmp
	if (bmpinfo.biBitCount != 24) {
		CloseHandle(file);
		return NULL;
	}

	// create buffer to hold the data
	size = bmpheader.bfSize - bmpheader.bfOffBits;
	BYTE* Buffer = new BYTE[size];
	// move file pointer to start of bitmap data
	SetFilePointer(file, bmpheader.bfOffBits, NULL, FILE_BEGIN);
	// read bmp data
	if (ReadFile(file, Buffer, size, &bytesread, NULL) == false) {
		delete[] Buffer;
		CloseHandle(file);
		return NULL;
	}
	// everything successful here: close file and return buffer
	CloseHandle(file);

	return Buffer;
}//LOADPMB

bool SaveBMP(BYTE* Buffer, int width, int height, long paddedsize, LPCTSTR bmpfile)
{
	// declare bmp structures 
	BITMAPFILEHEADER bmfh;
	BITMAPINFOHEADER info;

	// andinitialize them to zero
	memset(&bmfh, 0, sizeof(BITMAPFILEHEADER));
	memset(&info, 0, sizeof(BITMAPINFOHEADER));

	// fill the fileheader with data
	bmfh.bfType = 0x4d42;       // 0x4d42 = 'BM'
	bmfh.bfReserved1 = 0;
	bmfh.bfReserved2 = 0;
	bmfh.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + paddedsize;
	bmfh.bfOffBits = 0x36;		// number of bytes to start of bitmap bits

								// fill the infoheader

	info.biSize = sizeof(BITMAPINFOHEADER);
	info.biWidth = width;
	info.biHeight = height;
	info.biPlanes = 1;			// we only have one bitplane
	info.biBitCount = 24;		// RGB mode is 24 bits
	info.biCompression = BI_RGB;
	info.biSizeImage = 0;		// can be 0 for 24 bit images
	info.biXPelsPerMeter = 0x0ec4;     // paint and PSP use this values
	info.biYPelsPerMeter = 0x0ec4;
	info.biClrUsed = 0;			// we are in RGB mode and have no palette
	info.biClrImportant = 0;    // all colors are important

								// now we open the file to write to
	HANDLE file = CreateFile(bmpfile, GENERIC_WRITE, FILE_SHARE_READ,
		NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (file == NULL) {
		CloseHandle(file);
		return false;
	}
	// write file header
	unsigned long bwritten;
	if (WriteFile(file, &bmfh, sizeof(BITMAPFILEHEADER), &bwritten, NULL) == false) {
		CloseHandle(file);
		return false;
	}
	// write infoheader
	if (WriteFile(file, &info, sizeof(BITMAPINFOHEADER), &bwritten, NULL) == false) {
		CloseHandle(file);
		return false;
	}
	// write image data
	if (WriteFile(file, Buffer, paddedsize, &bwritten, NULL) == false) {
		CloseHandle(file);
		return false;
	}

	// and close file
	CloseHandle(file);

	return true;
} // SaveBMP

void ProjeksiyonMatrisiHesapla(int noktaSayisi/*kalibrasyonda kullanilacak nokta sayisi*/, 
	float* dunyaNoktalari/*gercek dunya koordinatlari*/, float* imgeNoktalari/*goruntudeki koordinatlar*/, 
	float* A /*projeksiyon matrisi*/) {
	//D Q = R esitliginde D ve R'yi biliyoruz ve dolduruyoruz

	MatrixXf D(noktaSayisi * 2, 11); //D matrisi
	VectorXf R(noktaSayisi * 2); // R vektoru

	float X, Y, Z, x, y, z; // D matrisinde kullanilacak 2D ve 3D duzlem noktalari



	for (int i = 0; i < noktaSayisi; i++) {
		/*Gercek dunya noktalarindan (3 boyutlu) X,Y,Z degerlerini belirliyoruz*/
		X = dunyaNoktalari[i * 3];
		Y = dunyaNoktalari[i * 3 + 1];
		Z = dunyaNoktalari[i * 3 + 2];

		/*fotograftaki noktalardan (2 boyutlu) x ve y degerlerini belirliyoruz*/
		x = imgeNoktalari[i * 2];
		y = imgeNoktalari[i * 2 + 1];

		/*R matrisini dolduruyoruz*/
		R(i * 2) = x;
		R(i * 2 + 1) = y;

		/*D matrisinde 1 noktaya karsilik olarak 2 denklem var. Bu matris icin sablon satirlar tanimlaniyor*/
		/*X,Y,Z ve x,y degerleri yukarida atanirken, her iterasyonda D matrisi icin denk dusen degerler asagida atanacak*/
		float mevcutNoktalarD[22] = { X,Y,Z,1, 0,0,0,0, -X * x, -Y * y, -Z * z,
									  0,0,0,0, X,Y,Z,1, -X * y, -Y * y, -Z * y
		};
		/*D'yi dolduruyoruz*/
		for (int j = 0; j < 11; j++) {
			D(i * 2, j) = mevcutNoktalarD[j];
			D(i * 2 + 1, j) = mevcutNoktalarD[j + 11];

		}
	}


	/*SVD (Singular Value Decomposition) yontemini kullanarak DQ=R denkleminden bilinen D ve R'ye gore Q matrisini cozuyoruz*/
	VectorXf solution(11);//Q matrisi 
	JacobiSVD<MatrixXf> svd(D, ComputeFullU | ComputeFullV);
	solution = svd.solve(R);
	//Q matrisini(vektorunu) bulduktan sonra, artik A projeksiyon matrisini belirleyebiliriz
	for (int i = 0; i < 11; i++) {
		A[i] = solution(i);
	}
	//A projeksiyon matrisi icin tum degerleri belirliyoruz fakat sondaki a44 degeri teoride 1'e esit oldugu icin ona direkt 1 atiyoruz
	A[11] = 1;

}

void ImarEt(int noktaSayisi/*imar edilecek noktalarin sayisi*/, float* imarImgeNoktalari/*imar edilecek noktalarin goruntu koordinatlarini tutar*/,
	float* p/*projeksiyon matrisi*/, float* w/*gercek dunya koordinatlari*/) {

	/*
	[a]         [X]
	[b]  =  P x [Y]
	[w]		|   [Z]
			|   [1]
	|		|    |
	|		|    |
	|       |    ----> 3D (3 boyutlu) dunya koordinatlari
	|		|
	|		----> projeksiyon matrisi
	|
	----> 2D (2 boyutlu) dunya koordinatlari
	*/


	MatrixXf A(2, 3);
	Vector2f B(2, 1);

	float x, y;

	for (int i = 0; i < noktaSayisi; i++) {
		x = imarImgeNoktalari[i * 2];
		y = imarImgeNoktalari[i * 2 + 1];


		/*
			xp31 - p11, xp32 - p12, xp33 - p13
			yp31 - p21, yp32 - p22, yp33 - p23

			A matrisi
		*/


		A << x * p[8] - p[0], x*p[9] - p[1], x*p[10] - p[2],
			y*p[8] - p[4], y*p[9] - p[5], y*p[10] - p[6];

		//Bilinmeye bir matris var o da asagidaki
		/*
			[X]
			[Y] --> W matrisi
			[Z]

			bu 3x1 lik matrisi bulmak icin A matrisinin B matrisine gore
			SVD yontemi ile cozecegiz
		*/

		/*
			p14 - xp34
			p24 - yp34

			B matrisi
		*/


		B << p[3] - x * p[11],
			p[7] - y * p[11];

		Vector3f solution;
		JacobiSVD<MatrixXf> svd(A, ComputeFullU | ComputeFullV);

		solution = svd.solve(B);

		w[i * 3] = solution(0);
		w[i * 3 + 1] = solution(1);
		w[i * 3 + 2] = solution(2);
		/*
			SVD uygulandiktan sonra XYZ degerlerini yani 3D dunyanin 2D dunyaya
			projeksiyonunu bulmus oluyoruz
		*/
	}
}

int enCokOlusanSayi(int d[], int boyut) {
	int maksimumSayim = 0;

	for (int i = 0; i < boyut; i++)
	{
		int sayac = 1;
		for (int j = i + 1; j < boyut; j++)
			if (d[i] == d[j])
				sayac++;
		if (sayac > maksimumSayim)
			maksimumSayim = sayac;
	}

	for (int i = 0; i < boyut; i++)
	{
		int sayac = 1;
		for (int j = i + 1; j < boyut; j++)
			if (d[i] == d[j])
				sayac++;
		if (sayac == maksimumSayim)
			return d[i];
	}
	
}

void vektordenDegerleriOku(int noktaSayisi, float* imge, float* dunya) {
	for (int i = 0; i < noktaSayisi; i++)
	{
		imge[i * 2] = vektorImge[i * 2];
		imge[i * 2 + 1] = vektorImge[i * 2 + 1];
		dunya[i * 3] = vektorDunya[i * 3];
		dunya[i * 3 + 1] = vektorDunya[i * 3 + 1];
		dunya[i * 3 + 2] = vektorDunya[i * 3 + 2];

	}
}

void dogruBul(int secim) {
	if (secim == 0) {
		vCap >> source;
	}
	Mat gray;
	cvtColor(source, gray, COLOR_BGR2GRAY);
	Mat dst, cdst; // 2 tane matris olusturuyoruz, uygulayacagimiz fonksiyonlarin sonucunu yazdirmak icin

	Canny(gray, dst, 50, 200, 3); // cizgileri bulabilmek icin once Canny uyguluyoruz.
	cvtColor(dst, cdst, COLOR_GRAY2BGR); //GRAY seviyeden BGR seviyesine donusturuyoruz

	vector<Vec2f> lines;//Hough uygulanmasi sonucu cizgileri yazdiracagimiz bir vektor turunden degisken tanimliyoruz.
	// Vec2f anlami 2 tane float degiskene sahip olmasi ve bu vektor degiskeninin bir struct oldugunu gosteriyor.


	HoughLines(dst, lines, 1, CV_PI / 180, 150, 0, 0); // Hough uygulayarak fotograftaki dogrulari(cizgileri) buluyoruz.

	/*Hough sonucunda buldugumuz dogrulari fotografa cizdirecegiz*/
	for (size_t i = 0; i < lines.size(); i++) // buldugumuz cizgilerin sayisi kadar gidiyoruz.
	{
		float rho = lines[i][0]; // RHO hesaplamalarda kullanlacak piksel olarak cozunurluk
		float theta = lines[i][1]; // THETA hesaplamalarda kullanilacak radyan turunden aci
		Point pt1, pt2; // PT1 ve PT2 her bir cizginin baslangic ve bitis konumu: Point turunden olduklari icin herbirinin x ve y degerleri var.

		/*her bir cizgiyi(dogruyu) cizdirebilmek icin hesaplamalar asagidaki gibidir.*/
		double a = cos(theta);
		double b = sin(theta);
		double x0 = a * rho;
		double y0 = b * rho;

		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		/*Hesaplamalarin sonu*/
		
		noktalar.push_back(pt1.x);
		noktalar.push_back(pt1.y);
		noktalar.push_back(pt2.x);
		noktalar.push_back(pt2.y);
	}

}

void kesisimBul() {

	Point A, B, C, D;// 2 dogru var ve bu 2 dogrunun 2 noktasi var(baslangic ve bitis). A ve B ilk 1. dogru icin noktalar olsun, C ve D 2. dogru icin noktalar
	int x, y; // kesisim noktalarinin x ve y noktalarini dosyaya yazdirmak icin x ve y degiskenlerini tanimliyoruz.

	int width = source.size().width; //goruntunu width'i
	int height = source.size().height; //goruntunun height'i

	/*kesisim testini uyguluyoruz*/
	for (int i = 0; i < noktalar.size() / 4; i++) {

		/*ilk dogru icin baslangic ve bitis konumlarini A ve B noktalarina tanimliyoruz*/
		A.x = noktalar[i * 4];
		A.y = noktalar[i * 4 + 1];
		B.x = noktalar[i * 4 + 2];
		B.y = noktalar[i * 4 + 3];

		for (int j = i + 1; j < noktalar.size() / 4; j++)
		{
			/*geriye cizgiler icin baslangic ve bitis konumlarini C ve D noktalarina tanimliyoruz */
			C.x = noktalar[j * 4];
			C.y = noktalar[j * 4+1];
			D.x = noktalar[j * 4 + 2];
			D.y = noktalar[j * 4 + 3];

			/*determinan bulabilmek icin a1,b1,c1 ve a2,b2,c2 hesaplaniyor*/
			double a1 = B.y - A.y;
			double b1 = A.x - B.x;
			double c1 = a1 * (A.x) + b1 * (A.y);

			double a2 = D.y - C.y;
			double b2 = C.x - D.x;
			double c2 = a2 * (C.x) + b2 * (C.y);

			//determinant hesaplaniyor
			double determinant = a1 * b2 - a2 * b1;

			if (determinant == 0)
			{
				//hicbirsey yapma, cunku paraleller
			}
			else
			{
				x = (b2*c1 - b1 * c2) / determinant;
				y = (a1*c2 - a2 * c1) / determinant;

				if (x<0 || x > width || y < 0 || y > height) { // eger kesisim noktasi goruntuden tasmissa
					//hicbirsey yapma, cunku araliga dahil degil
				}
				else {
					//x -> y -> NULL
					kesisimler.push_back(x);
					kesisimler.push_back(y);
				}
			}
		}

	}

}

void elimineEt(int tahtaBoyutu, float* maksimumDeger, int secim) {
	int treshold; //eşik değeri belirlemek için değişken oluşturuyoruz.
	// her konumun x ve y diye 2 verisi bulunmakta, bu yüzden nokta sayısını ikiye bölüyoruz.
	int* trueOrFalse = new int[kesisimler.size() / 2]; // noktanın elimine edilip edilmeyeceğine karar verdikten konumunu atayacağımız dizi
	int** distance = new int*[kesisimler.size() / 2]; //noktalar arasındaki mesafeleri atayacağımız 2 boyutlu liste oluşturuyoruz
	for (int i = 0; i < kesisimler.size() / 2; i++) { // dinamik diziyi 2 boyutlu yapıyoruz.
		distance[i] = new int[kesisimler.size() / 2];
	}

	int width = source.size().width; //goruntunu width'i

	for (int i = 0; i < kesisimler.size() / 2; i++) {
		for (int j = 0; j < kesisimler.size() / 2; j++) {
			if (i != j) {
				//mesafe fonksiyonunu uyguluyoruz ve bulduğumuz sonucu dizide gerekli konuma setliyoruz.
				distance[i][j] = sqrt(pow(kesisimler[i*2] - kesisimler[j * 2], 2) + pow(kesisimler[i * 2+1] - kesisimler[j * 2 +1], 2));
			}
			else { // i j'ye eşitse noktanın kendisidir demektir
				distance[i][j] = -1;
			}
		}
	}

	int * d = new int[kesisimler.size() / 2]; //resimden taşan noktaları elemek için oluşturduğumuz dizi
	for (int i = 0; i < kesisimler.size() / 2; i++) {
		d[i] = width;
		for (int j = 0; j < kesisimler.size() / 2; j++) {
			if (i != j) {
				if (d[i] > distance[i][j]) { // eğer noktalar arasındaki mesafe resmin genişliğinden küçükse
					d[i] = distance[i][j];
				}
			}
		}
	}

	maksimumDeger[0] = enCokOlusanSayi(d, (kesisimler.size() / 2)); //noktalar arası mesafelerde en çok oluşan mesafeyi belirliyoruz.

	for (int i = 0; i < kesisimler.size() / 2; i++) {
		treshold = 0;
		for (int j = 0; j < kesisimler.size() / 2; j++) {
			if (i != j) {
				if ((distance[i][j] <= (maksimumDeger[0] + 1)) && (distance[i][j] >= (maksimumDeger[0] - 1))) {
					treshold++;
				}
				if (treshold >= 2) { //yoğunlukta olan mesafe kadar uzaklıkta 2 ve daha fazla komşusu varsa bu nokta kalsın
					trueOrFalse[i] = true;
				}
				else { //if koşulunu sağlamadığı için elimine et
					trueOrFalse[i] = false;
				}
			}
		}
	}

	int kalibreX, kalibreY, kalibreZ = 0;

	//elimine edilmiş   noktaları kırmızı daire içerisine alıyoruz
	//elimine edilmemiş noktaları yeşil   daire içerisine alıyoruz
	for (int i = 0; i < kesisimler.size() / 2; i++) {
		if (trueOrFalse[i] == 1) {
			kalibreX = (kesisimler[i * 2] / (maksimumDeger[0] + 0.001)) * tahtaBoyutu;
			kalibreY = (kesisimler[i*2+1] / (maksimumDeger[0] + 0.001)) * tahtaBoyutu;
			iKalibrasyon.push_back(kesisimler[i * 2]);
			iKalibrasyon.push_back(kesisimler[i * 2 + 1]);
			dKalibrasyon.push_back(kalibreX);
			dKalibrasyon.push_back(kalibreY);
			dKalibrasyon.push_back(kalibreZ);
			circle(source, Point(kesisimler[i*2], kesisimler[i * 2 + 1]), 5, Scalar(0, 255, 0)); // elimine sonrasi ideal kesisim noktasi Yesil renk
		}
	}
	iKalibrasyonNoktaSayisi = iKalibrasyon.size() / 2;

	if (secim == 1) {
		for (int i = 0; i < iKalibrasyonNoktaSayisi; i++) {
			vektorImge.push_back(iKalibrasyon[i * 2]);
			vektorImge.push_back(iKalibrasyon[i * 2 + 1]);
			vektorDunya.push_back(dKalibrasyon[i * 3]);
			vektorDunya.push_back(dKalibrasyon[i * 3 + 1]);
			vektorDunya.push_back(dKalibrasyon[i * 3 + 2]);
		}
		noktalar.clear();
		kesisimler.clear();
		iKalibrasyon.clear();
		dKalibrasyon.clear();
	}

	delete[] d;
	delete[] distance;
	delete[] trueOrFalse;
	
}


int goruntuYukle(int tahtaBoyutu, float* maksimumDeger, int secim, int kalibrasyonEsik) {
	if (secim == 0) {
		for (;;) {
			dogruBul(secim);
			kesisimBul();
			elimineEt(tahtaBoyutu, maksimumDeger, secim);
			iKalibrasyonNoktaSayisi = iKalibrasyon.size() / 2;
			string putTextSonucu = to_string(iKalibrasyonNoktaSayisi);
			imwrite("sonuc.bmp", source);
			putText(source, putTextSonucu, Point(25, 25), FONT_HERSHEY_DUPLEX, 1, Scalar(0, 255, 0));
			imshow("elimine edilmis", source);
			if (waitKey(30) > 0 || iKalibrasyonNoktaSayisi>kalibrasyonEsik) {
				vektorImge.clear();
				vektorDunya.clear();
				//kesisim noktalarini burada kaydet bir yere;
				for (int i = 0; i < iKalibrasyonNoktaSayisi; i++) {		
					vektorImge.push_back(iKalibrasyon[i * 2]);
					vektorImge.push_back(iKalibrasyon[i * 2 + 1]);
					vektorDunya.push_back(dKalibrasyon[i * 3]);
					vektorDunya.push_back(dKalibrasyon[i * 3 + 1]);
					vektorDunya.push_back(dKalibrasyon[i * 3 + 2]);
				}
				destroyAllWindows();
				break;
			}


			noktalar.clear();
			kesisimler.clear();
			iKalibrasyon.clear();
			dKalibrasyon.clear();


		}
	}
	else
	{
		dogruBul(secim);
		kesisimBul();
		elimineEt(tahtaBoyutu, maksimumDeger, secim);
		imwrite("sonuc.bmp", source);
	}
	return iKalibrasyonNoktaSayisi;
}

int alanBul() {
	int enBuyukX = 0;
	int enBuyukY = 0;
	int enKucukX = 100000;
	int enKucukY = 100000;
	int sayici = 0;
	for (int i = 0; i < vektorImge.size() / 2; i++) {
		if (enBuyukX < vektorImge[2 * i]) {
			enBuyukX = vektorImge[2 * i];
		}
		if (enBuyukY < vektorImge[2 * i + 1]) {
			enBuyukY = vektorImge[2 * i + 1];
		}
		if (enKucukX > vektorImge[2 * i]) {
			enKucukX = vektorImge[2 * i];
		}
		if (enKucukY > vektorImge[2 * i + 1]) {
			enKucukY = vektorImge[2 * i + 1];
		}
	}

	for (int i = enKucukX; i < enBuyukY; i++) {
		for (int j = enKucukY; j < enBuyukY; j++) {
			sayici++;
		}
	}

	return sayici;
}