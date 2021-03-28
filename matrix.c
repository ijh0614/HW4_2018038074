#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Method Declaration */
int** create_matrix(int row, int col);// return(반환값)이 이중포인터이다.
void print_matrix(int** matrix, int row, int col);
int free_matrix(int** matrix, int row, int col);
int fill_data(int** matrix, int row, int col);
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col);
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col);
int transpose_matrix(int** matrix, int** matrix_t, int row, int col);
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col);

int main()
{

    char command;//사용자가 메뉴에서 입력한 값을 저장해주는 변수. 메뉴 이외의 글자 전처리검사 필요.
    printf("[----- [임종훈]  [2018038074] -----]\n");

    int row, col;//행, 열 변수 선언.
    srand(time(NULL));// rand로 난수 생성 시 생성할 때마다 바뀐 난수를 출력하기 위해. 계속 바뀌는 시간을 넣어준다.

    printf("Input row and col : ");
    scanf("%d %d", &row, &col);//행과 열을 입력. 순서 주의.
    int** matrix_a = create_matrix(row, col);//create_matrix 함수로 이동한다. 동적할당을 이용한 2차원 배열이기 때문에 이중포인터 사용.
    int** matrix_b = create_matrix(row, col);
    int** matrix_a_t = create_matrix(col, row);//전치행렬을 생성한다. 행과 열의 값을 바꾸어서 입력한다.

    printf("Matrix Created.\n");

    if (matrix_a == NULL || matrix_b == NULL) {return -1;}

    do{
        printf("----------------------------------------------------------------\n");
        printf("                     Matrix Manipulation                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Matrix   = z           Print Matrix        = p \n");
        printf(" Add Matrix          = a           Subtract Matrix     = s \n");
        printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
        printf(" Quit                = q \n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);

        switch(command) {
        case 'z': case 'Z':
            printf("Matrix Initialized\n");
            fill_data(matrix_a, row, col);
            fill_data(matrix_b, row, col);
            break;
        case 'p': case 'P':
            printf("Print matrix\n");
            printf("matrix_a\n");
            print_matrix(matrix_a, row, col);
            printf("matrix_b\n");
            print_matrix(matrix_b, row, col);
            break;
        case 'a': case 'A':
            printf("Add two matrices\n");
            addition_matrix(matrix_a, matrix_b, row, col);
            break;
        case 's': case 'S':
            printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col);
            break;
        case 't': case 'T':
            printf("Transpose matrix_a \n");
            printf("matrix_a\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            print_matrix(matrix_a_t, col, row);
            break;
        case 'm': case 'M':
            printf("Multiply matrix_a with transposed matrix_a \n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);
            multiply_matrix(matrix_a, matrix_a_t, row, col);
            break;
        case 'q': case 'Q':
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t, col, row);
            free_matrix(matrix_a, row, col);
            free_matrix(matrix_b, row, col);
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    }while(command != 'q' && command != 'Q');

    return 1;
}

/* create a 2d array whose size is row x col using malloc() */
//행렬 생성 함수. 반환값이 이중 포인터.
int** create_matrix(int row, int col)
{   
    int**matrix;//생성해서 반환해줄 이중 포인터(이차원 배열의 주소를 저장할 변수)선언
   
    /*포인터 변수를 열의 크기만큼 동적할당
   1.행의 갯수는 열의 크기만큼 존재하기 때문.
   2. 아래의 선언한 배열에는 행의 주소들을 받아야 하기 때문에 이중포인터 선언.
    */
    matrix=(int**)malloc(sizeof(int*)*col);
   
    for(int a=0;a<col;a++){//반복문을 사용해서 행들을 동적할당해준다.
        matrix[a]=(int*)malloc(sizeof(int) * row);//row 크기의 메모리의 주소를 전달해주는 것.
    }
    return matrix;
}

/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col)
{

}


/* free memory allocated by create_matrix() */
//해제 또한 반복문을 사용해서 여러번 해제해야 함을 명심!
int free_matrix(int** matrix, int row, int col)
{
    for(int a=0;a<col;a++){
        free(matrix[a]);//행들을 가르키고 있는 동적할당 해제
    }
    free(matrix);//시각적으로 보았을 때 첫번째 열인 동적할당 해제.
}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col)
{

}

/* matrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)
{

}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)
{

}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)
{

}

/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)
{

}

