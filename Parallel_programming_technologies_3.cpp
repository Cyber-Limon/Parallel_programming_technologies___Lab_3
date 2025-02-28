#include <iostream>
#include <omp.h>



using namespace std;

int q;
const int N = 500;
double start_time, end_time;
float A[N][N], B[N][N], C[N][N], c;

int main() {
	setlocale(LC_ALL, "Russian");

	cout << "������� ���������� �������� ��������� = ";
	cin >> q;
	cout << endl;



	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			A[i][j] = (rand() % 1000 - 500.0) / 1000.0;
			B[i][j] = (rand() % 1000 - 500.0) / 1000.0;
		}
	}

		
	
	c = 0;
	start_time = omp_get_wtime();
	for (int n = 0; n < q; n++) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				float sum = 0;

				for (int k = 0; k < N; k++) {
					sum += A[i][k] * B[k][j];
				}

				C[i][j] = sum;
			}
		}
	}

	end_time = omp_get_wtime();

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			c += C[i][j] * C[i][j];

	cout << "��������� ��� ���������               = " << c << endl;
	cout << "����� ���������� ��� ���������        = " << end_time - start_time << "\n\n";
	
	
	
	c = 0;
	start_time = omp_get_wtime();
	for (int n = 0; n < q; n++) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				float sum = 0;

#pragma omp parallel reduction(+:sum) num_threads(4) 
				{
#pragma omp for

					for (int k = 0; k < N; k++) {
						sum += A[i][k] * B[k][j];
					}
				}

				C[i][j] = sum;
			}
		}
	}	
	
	end_time = omp_get_wtime();

	for (int i = 0; i < N; i++) 
		for (int j = 0; j < N; j++) 
			c += C[i][j] * C[i][j];
		

	cout << "��������� ��������� 1                 = " << c << endl;
	cout << "����� ���������� ��������� 1          = " << end_time - start_time << "\n\n";

	

	c = 0;
	start_time = omp_get_wtime();
	for (int n = 0; n < q; n++) {

#pragma omp parallel num_threads(4) 
		{
#pragma omp for

			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					float sum = 0;

					for (int k = 0; k < N; k++) {
						sum += A[i][k] * B[k][j];
					}

					C[i][j] = sum;
				}
			}
		}
	}
	end_time = omp_get_wtime();

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) 
			c += C[i][j] * C[i][j];

	cout << "��������� ��������� 2                 = " << c << endl;
	cout << "����� ���������� ��������� 2          = " << end_time - start_time << "\n\n";



	c = 0;
	start_time = omp_get_wtime();
	for (int n = 0; n < q; n++) {
		for (int i = 0; i < N; i++) {

#pragma omp parallel num_threads(4) 
			{
#pragma omp for

				for (int j = 0; j < N; j++) {
					float sum = 0;

					for (int k = 0; k < N; k++) {
						sum += A[i][k] * B[k][j];
					}

					C[i][j] = sum;
				}
			}
		}
	}
	end_time = omp_get_wtime();
	
	for (int i = 0; i < N; i++) 
		for (int j = 0; j < N; j++) 
			c += C[i][j] * C[i][j];

	cout << "��������� ��������� 3                 = " << c << endl;
	cout << "����� ���������� ��������� 3          = " << end_time - start_time << "\n\n\n";



	return 0;
}