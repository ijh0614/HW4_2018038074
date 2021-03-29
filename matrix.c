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
    int do_initial =0;//초기화를 해줬는지 안 해줬는지 확인
    char command;//사용자가 메뉴에서 입력한 값을 저장해주는 변수. 메뉴 이외의 글자 전처리검사 필요.
    printf("[----- [임종훈]  [2018038074] -----]\n");

    int row, col =0;//행, 열 변수 선언.
    srand(time(NULL));// rand로 난수 생성 시 생성할 때마다 바뀐 난수를 출력하기 위해. 계속 바뀌는 시간을 넣어준다.

    printf("Input row and col : ");
    scanf("%d %d", &row, &col);//행과 열의 개수를 입력한 것!!!!!!!!!!!!!!!!!!!!
    //크기를 입력받는 것과 헷갈리지 않도록한다.
    //행의 크기는 col개이고 열의 크기는 row개 이다.

    int** matrix_a = create_matrix(row, col);//create_matrix 함수로 이동한다. 동적할당을 이용한 2차원 배열이기 때문에 이중포인터 사용.
    int** matrix_b = create_matrix(row, col);
    int** matrix_a_t = create_matrix(col, row);//전치행렬을 생성한다. 행과 열의 값을 바꾸어서 입력한다.

    if (matrix_a == NULL || matrix_b == NULL) {return -1;}//후처리 검사. 제대로 배열이 할당되었는지 확인
    //만약 전처리 검사에서 옳지 않게 되었다면 이중포인터 변수에 NULL이 반환되어 후처리기에 걸림.

    printf("Matrix Created.\n");

    do{//do while문
        printf("----------------------------------------------------------------\n");
        printf("                     Matrix Manipulation                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Matrix   = z           Print Matrix        = p \n");
        printf(" Add Matrix          = a           Subtract Matrix     = s \n");
        printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
        printf(" Quit                = q \n");
        printf("----------------------------------------------------------------\n");//메뉴 출력

        printf("Command = ");
        scanf(" %c", &command);//사용자로부터 명령을 입력받음


        switch(command) {
        case 'z': case 'Z'://행렬 초기화. 랜덤값 넣어주기
            printf("Matrix Initialized\n");
            fill_data(matrix_a, row, col);
            fill_data(matrix_b, row, col);
            do_initial = 1;
            break;
        case 'p': case 'P'://행렬 출력. *행렬 초기화하기 전에 실행하면 되돌려보내는 전처리기 만들기
            if(do_initial!=1){//초기화를 하지 않았다면 다시 메뉴로 돌려보내기
                printf("Please Initialize Matrix\n");
                break;
            }
            printf("Print matrix\n");
            printf("matrix_a\n");
            print_matrix(matrix_a, row, col);
            printf("matrix_b\n");
            print_matrix(matrix_b, row, col);
            break;
        case 'a': case 'A'://행렬 덧셈
            if(do_initial!=1){//초기화를 하지 않았다면 다시 메뉴로 돌려보내기
                printf("Please Initialize Matrix\n");
                break;
            }
            printf("Add two matrices\n");
            addition_matrix(matrix_a, matrix_b, row, col);
            printf("Print result\n");
            break;
        case 's': case 'S'://행렬 뺄셈 (A-B)
            if(do_initial!=1){//초기화를 하지 않았다면 다시 메뉴로 돌려보내기
                printf("Please Initialize Matrix\n");
                break;
            }
            printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col);
            break;
        case 't': case 'T':
            if(do_initial!=1){//초기화를 하지 않았다면 다시 메뉴로 돌려보내기
                printf("Please Initialize Matrix\n");
                break;
            }
            printf("Transpose matrix_a \n");
            printf("matrix_t\n");
            transpose_matrix(matrix_a, matrix_a_t, row, col);
            break;
        case 'm': case 'M':
            if(do_initial!=1){//초기화를 하지 않았다면 다시 메뉴로 돌려보내기
                printf("Please Initialize Matrix\n");
                break;
            }
            
            printf("Multiply matrix_a with transposed matrix_a\n");
            transpose_matrix(matrix_a, matrix_a_t, row, col);
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
int** create_matrix(int row, int col)//갯수를 받은 것.
{   
    int**matrix;//생성해서 반환해줄 이중 포인터(이차원 배열의 주소를 저장할 변수)선언
    if(row <= 0 || col <=0) {
        printf("Check the sizes of row and col!\n");
        exit(1);
    }
    /*포인터 변수를 열의 크기만큼 동적할당
   1.행의 갯수는 열의 크기만큼 존재하기 때문.
   2. 아래의 선언한 배열에는 행의 주소들을 받아야 하기 때문에 이중포인터 선언.
    */
    matrix=(int**)malloc(sizeof(int*)*row);
   
    for(int a=0;a<row;a++){//반복문을 사용해서 행들을 동적할당해준다.
        matrix[a]=(int*)malloc(sizeof(int) * col);//col의 메모리의 주소를 전달해주는 것.->a행의 열이 된다.
    }
    return matrix;
}

/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col)//갯수를 받은 것.
{
    for(int a=0;a<row;a++){
        for(int b=0; b<col; b++){
            printf("%3d ", matrix[a][b]);//행렬 한개당 3칸 할당
        }
        printf("\n");//한 행을 모두 출력하면 개행
    }
    printf("\n");
}


/* free memory allocated by create_matrix() */
//해제 또한 반복문을 사용해서 여러번 해제해야 함을 명심!
int free_matrix(int** matrix, int row, int col)//갯수를 받은 것.
{
    for(int a=0;a<row;a++){
        free(matrix[a]);//열들을 가르키고 있는 동적할당 해제
    }
    free(matrix);//시각적으로 보았을 때 첫번째 열인 동적할당 해제.
    return 0;
}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col)//갯수를 받은 것.
{
    for(int a=0;a<row;a++){
        for(int b=0;b<col;b++){
            matrix[a][b] = rand()%20;//20의 나머지. 0~19의 값이 나옴.
        }
    }
    return 0;
}

/* matrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    int** result_matrix = create_matrix(row, col);//결과값을 저장해 줄 행렬 생성.

    for(int a=0;a<row;a++){
        for(int b=0;b<col;b++){
            result_matrix[a][b]=matrix_a[a][b] + matrix_b[a][b];
        }
    }
    print_matrix(result_matrix, row, col);//결과를 출력
    free_matrix(result_matrix, row, col);//결과를 저장한 동적할당 메모리 해제
    return 0;
}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    int** result_matrix = create_matrix(row, col);//결과값을 저장해 줄 행렬 생성.

    for(int a=0;a<row;a++){
        for(int b=0;b<col;b++){
            result_matrix[a][b]=matrix_a[a][b] - matrix_b[a][b];
        }
    }
    print_matrix(result_matrix, row, col);//결과를 출력
    free_matrix(result_matrix, row, col);//결과를 저장한 동적할당 메모리 해제
    return 0;
}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col)//전치행렬 만드는 함수
{
    for(int a=0;a<row;a++){//이중 for문 사용해서 미리 만들어놓은 전치행렬 배열에 대입해서 생성.
        for(int b=0;b<col;b++){
            matrix_t[b][a] = matrix[a][b];
        }
    }
    print_matrix(matrix_t, col, row);//결과를 출력
    return 0;
}

/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)
{
    int** result_matrix = create_matrix(row, row);//결과값을 저장해 줄 행렬 생성.
    //결과적으로 만들어지는 행렬은 (A행렬의 행의 갯수) * (B행렬의 열의 갯수)가 될 것이다.
    //이는 (A행렬의 행의 갯수) * (A행렬의 행의 갯수) 와 같다.
    int sum;
    for(int a=0;a<row;a++){//가장 바깥의 for문은 A행렬의 행의 수 만큼 반복
        for(int b=0;b<row;b++){//두번째 for문은 T행렬의 열의 수(= A행렬의 행의 수) 만큼 반복
            sum=0;
            for(int c=0;c<col;c++){//가장 안쪽 for문은 A행렬의 열의 수만큼 반복
                sum = sum + matrix_a[a][c] * matrix_t[c][b];//A행렬의 행, T행렬의 열을 하나씩 결정하고 나머지를 증가시키면서 모두 더함.
            }
            result_matrix[a][b] = sum;//모두 다 더한값을 고정시켰던 부분끼리의 행렬의 위치에 저장. ->[A행렬의 행][T행렬의 열]
        }
    }
    print_matrix(result_matrix, row, row);//결과를 출력
    free_matrix(result_matrix, row, row);//결과를 저장한 동적할당 메모리 해제
    return 0;
}