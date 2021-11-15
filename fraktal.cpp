
#include <iostream>
#include <iomanip> 
#include <cmath>
#include <graphics.h>
#include <fstream>

template<typename T>
void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

size_t num(size_t a, size_t b) {
    if (a / 10 == 0)
        return b;
    else num(a / 10, ++b);
}

size_t** flip(size_t** a, size_t n) {
    for (size_t i = 0; i < n / 2; i++)
        for (size_t j = 0; j < n; j++)
            if (i != n - i - 1)
                swap(a[i][j], a[n - 1 - i][j]);
    return a;
}

size_t** rotate(size_t** a, size_t n) {
    for(size_t i = 0; i < n; i++)
        for (size_t j = i; j < n; j++)
            if (i != j)
                swap(a[i][j],a[j][i]);
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < n/2; j++)
            if (j != n - j - 1)
                swap(a[i][j], a[i][n - 1 - j]);
    return a;
}

size_t** unrotate(size_t** a, size_t n) {
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < n / 2; j++)
            if (j != n - j - 1)
                swap(a[i][j], a[i][n - 1 - j]);
    for (size_t i = 0; i < n; i++)
        for (size_t j = i; j < n; j++)
            if (i != j)
                swap(a[i][j], a[j][i]);
    return a;
}

void printArr(size_t** a, size_t n) {
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            std::cout << std::setw(4) << a[i][j];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void intput(size_t** a, size_t as, size_t** new_a, size_t y, size_t x) {
    for (size_t i = 0; i < as; i++)
        for (size_t j = 0; j < as; j++)
            new_a[x*as+i][y*as+j] = a[i][j];
}

void inc(size_t** a, size_t as, size_t k) {
    for (size_t i = 0; i < as; i++)
        for (size_t j = 0; j < as; j++)
            a[i][j] = a[i][j] + k;
}

size_t** rec(size_t** a, size_t n, short int time) {
    for (size_t t=0; t < time; t++) {
        size_t** new_a = new size_t* [n*3];
        for (size_t i = 0; i < n*3; i++)
            new_a[i] = new size_t[n*3];
        
        size_t k = a[n-1][0];
        
        intput(a, n, new_a, 2, 2);
        
        inc(a, n, k);
        a = flip(unrotate(a,n),n);
        intput(a, n, new_a, 1, 2);
        
        inc(a, n, k);
        intput(a, n, new_a, 1, 1);

        inc(a, n, k);
        a = unrotate(flip(a, n), n);
        intput(a, n, new_a, 2, 1);

        inc(a, n, k);
        a = unrotate(unrotate(a, n), n);
        intput(a, n, new_a, 2, 0);

        inc(a, n, k);
        intput(a, n, new_a, 1, 0);

        inc(a, n, k);
        intput(a, n, new_a, 0, 0);

        inc(a, n, k);
        a = unrotate(flip(a, n), n);
        intput(a, n, new_a, 0, 1);

        inc(a, n, k);
        intput(a, n, new_a, 0, 2);
        
        for (size_t i = 0; i < n; i++)
        	delete[] a[i];
    	delete[] a;
		n = n * 3;
        a = new_a;
    }
    return a;
}

void Draw (size_t** c, size_t n, double k, size_t translate) {
	for (size_t i = 0; i < n-1; i++) {
		if(abs(c[i][n-1] - c[i+1][n-1]) == 1)
	    		line((n-1)*k+translate,i*k+translate,(n-1)*k+translate,(i+1)*k+translate);
	    if(abs(c[n-1][i] - c[n-1][i+1]) == 1)
    		line(i*k+translate,(n-1)*k+translate,(i+1)*k+translate,(n-1)*k+translate);		
        for (size_t j = 0; j < n-1; j++) {
    		if(abs(c[j][i] - c[j+1][i]) == 1)
    			line(i*k+translate,j*k+translate,i*k+translate,(j+1)*k+translate);
			if(abs(c[j][i] - c[j][i+1]) == 1)
				line(i*k+translate,j*k+translate,(i+1)*k+translate,j*k+translate);
    	}
    }			
}


int main() {
	int n = 3;
    size_t** a = new size_t*[n];
    for (size_t i = 0; i < n; i++)
        a[i] = new size_t[n];

    a[0][0] = 7;
    a[0][1] = 6;
    a[0][2] = 5;
    
    a[1][0] = 8;
    a[1][1] = 3;
    a[1][2] = 4;
    
    a[2][0] = 9;
    a[2][1] = 2;
    a[2][2] = 1;

	double k = 81.0f;
	size_t translate = 50;
	
	
    initwindow(820,820);
    size_t** b;
    int time = n;
    b = rec(a, n, time-1);
    int new_n = 9 * pow(3,time-2);
    int new_k = k / pow(3,time-2);
    Draw(b,new_n,new_k,translate);
    
	std::ofstream out ("texttest.txt");
    for (size_t i = 0; i < new_n; i++) {
		for (size_t j = 0; j < new_n; j++)
        	out << std::setw(8) << b[i][j];
        out << std::endl;
    }
	
   
    getch();
    
    for (size_t i = 0; i < n; i++)
        delete[] a[i];
    delete[] a;
    for (size_t i = 0; i < new_n; i++)
        delete[] b[i];
    delete[] b;
 
    return 0;
}

