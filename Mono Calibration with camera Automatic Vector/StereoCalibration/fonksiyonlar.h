#pragma once
#ifndef FUNCTIONS
#define FUNCTIONS
#include <windows.h>
#include <string>
#include <atlstr.h>
#include <fstream>
#include <algorithm>
#include <math.h>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <vector>

using namespace std;

extern std::vector<int> vektorImge;
extern std::vector<int> vektorDunya;
extern std::vector<int> vektorAlan;

BYTE* LoadBMP(int% width, int% height, long% size, LPCTSTR bmpfile);

bool  SaveBMP(BYTE* Buffer, int width, int height, long paddedsize, LPCTSTR bmpfile);

void ProjeksiyonMatrisiHesapla(int noktaSayisi, float * dunyaNoktalari, float * imgeNoktalari, float * A);

void ImarEt(int noktaSayisi, float * imarImgeNoktalari, float * p, float * w);

void vektordenDegerleriOku(int noktaSayisi, float* imge, float* dunya);

int goruntuYukle(int tahtaBoyutu, float* maksimumDeger, int secim, int kalibrasyonEsik);

int alanBul();

#endif
