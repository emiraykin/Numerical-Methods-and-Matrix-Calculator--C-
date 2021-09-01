#include<stdio.h>
#include<math.h>
#include <stdlib.h>
#define PI 3.14159265359
#define e 2.7182818284
#define MAX 10


void find_root_others(float [],float [][3],float [][3],float [][2], int* );
//Get the math function from user
void get_function_type( int* );
void add_function(char );
void select_menu();
void add_polynom(float [],int ,int*);
void add_exponential(float [][3],int );
void add_sinusoidal(float [][3],int );
void add_logarithmic(float [][2], int );
void get_method_type(int*);
// find root 
double f(float [],int,float [][3],int,float [][3],int,float [][2], int, double );  // function value calculator
void bisection(float [],int,float [][3],int,float [][3],int,float [][2], int);  //bisection method function
void regula_falsi(float [],int ,float [][3],int ,float [][3],int  ,float [][2], int ); //regula-falsi / lineer interpolation method
void newton_raphson(float [],int ,float [][3],int ,float [][3],int  ,float [][2], int ); 

//numeric derrivative
double numerical_differentiation(float [],int ,float [][3],int j,float [][3],int  ,float [][2], int , double,char);
//numeric integral
void trapez_simpson(float [],int ,float [][3],int ,float [][3],int  ,float [][2], int );
//nterpolation
void gregory_newton(float [],int ,float [][3],int ,float [][3],int  ,float [][2], int );

//matrix operation functions
void matrix_operations(double[][MAX] ,int*);
void get_matrix(double[][MAX],int ,int);
void matrix_inverse(double[][MAX],int, int);
void gauss_elemination(double[][MAX],int ,int);
void gauss_seidel(double[][MAX],int , int);



int main(){

	int method_type;
	int polynom_grade=0;
	float polynom[MAX];
	float sinusoidal[MAX][3];
	float exponential[MAX][3];
	float logarithmic[MAX][2];
	double matrix[MAX][MAX]={0};
	int i,j,k,l,n;
	int repeat= 3;
	
	while(repeat==3){
		repeat=-1;
		int selected=0;
		printf("\n\n 1---> finding root, numeric differantiation/integral and interplation \n 2---> matrix operations \n -1---> exit \n\n  pick your operation : ");
		
		do{
			scanf("%d",&selected);
		}while(selected!=1 && selected!=2  && selected!=3 && selected!=-1 );
		
		if(selected==1){
			find_root_others(polynom, exponential,sinusoidal,logarithmic,&repeat);
		}
		else if(selected==2){
			matrix_operations(matrix,&repeat);
		}
	
	}
	
	

}




void find_root_others(float polynom[],float exponential[][3],float sinusoidal[][3],float logarithmic[][2],int *repeat){
	*repeat=2;
	
	while(*repeat==2){ // Loop for trying a different numeric method with different math functions
	int function_type;
	int is_polynom=0;
	int polynom_grade=0;
	int sinusoidal_number=0;
	int exponential_number=0;
	int logarithmic_number=0;
	int i=0;
	int method_type;
	
	
	do{
		
		get_function_type( &function_type);
		//add_function(function_type);
		if(function_type == 1){
			add_polynom( polynom ,MAX,&polynom_grade);
			is_polynom=1;
		}
		else if(function_type == 2){
			
			add_sinusoidal(sinusoidal,sinusoidal_number);
			sinusoidal_number++;
		}
		/*else if(function_type == 3){
			add_exponential(exponential,exponential_number);
			exponential_number++;
		}*/
		else if(function_type == 3 ){
			add_logarithmic(logarithmic,logarithmic_number);
			logarithmic_number++;
		}	
		
		
		}while(function_type != -1  /*&& is_polynom+sinusoidal_number+exponential_number+logarithmic_number==0*/);
		
		
		// print the final function
		printf("Final function is:\n");
		if(is_polynom!=0){
		
			for(i=polynom_grade;i>0;i--){
			printf("%0.2f x^%d+",polynom[i],i);
			}
			printf("%0.2f ",polynom[0]);
		}
		
		for(i=0;i<sinusoidal_number;i++){
			if(sinusoidal[i][0]==0){
				printf("+ %0.2fsin(%0.2f(x) )",sinusoidal[i][1],sinusoidal[i][2]/*,sinusoidal[n][3],(int)sinusoidal[n][4],sinusoidal[n][5]*/);
			}
			else{
				printf("+ %0.2fcos(%0.2f(x) )",sinusoidal[i][1],sinusoidal[i][2]/*sinusoidal[n][3],(int)sinusoidal[n][4],sinusoidal[n][5]*/);
	
			}	
		}
		for(i=0;i<exponential_number;i++){
				printf("+ %0.2f*(%0.2f)^(%0.2f*x ) ",exponential[i][0],exponential[i][1],exponential[i][2] );
	
		}
		
		for(i=0;i<logarithmic_number;i++){
			if(logarithmic[i][1]==1){
				printf("+ %0.2f log 10 tabanýnda (x) \n",logarithmic[i][0]);
			}
			else{
				printf("+ %0.2f log e tabanýnda (x) \n",logarithmic[i][0]);

			}
		}
		


		
		
		*repeat=1;
		while(*repeat==1){ // While Loop for trying different numeric method with the same math function
			
			get_method_type(&method_type);
			
			if(method_type==1){
				bisection(polynom, polynom_grade, exponential,exponential_number,sinusoidal,sinusoidal_number,logarithmic,logarithmic_number);
			}
			else if(method_type==2){
				regula_falsi(polynom, polynom_grade, exponential,exponential_number,sinusoidal,sinusoidal_number,logarithmic,logarithmic_number);
			}
			else if(method_type==3){
				newton_raphson(polynom, polynom_grade, exponential,exponential_number,sinusoidal,sinusoidal_number,logarithmic,logarithmic_number);
			}
			else if(method_type==4){
				printf("\nsonuc = %lf",numerical_differentiation(polynom,polynom_grade,exponential,exponential_number, sinusoidal,sinusoidal_number , logarithmic,  logarithmic_number,0,'M'));
			}
			else if(method_type==5){
				trapez_simpson(polynom, polynom_grade, exponential,exponential_number,sinusoidal,sinusoidal_number,logarithmic,logarithmic_number);
			}
			else if(method_type==6){
				gregory_newton(polynom, polynom_grade, exponential,exponential_number,sinusoidal,sinusoidal_number,logarithmic,logarithmic_number);
			}
			
			printf("\n\n\n 1---> try different method with the same function \n\n 2---> try different method with a different function \n\n 3---> Back to main menü \n\n -1 ---> Exit \n");
			scanf("%d",repeat);
		}
	
	}
}


void get_function_type(int *ptr_f_type){
	int is_correct=0;
	while(is_correct==0 ){
		is_correct=1;
		printf("\n");
		
		printf(" 1---> Polynom \n 2---> Sinusoidal \n 3---> Logarithmic \n  \n -1 for  Done \n Which type of function do you want to add? ");
		fflush(stdin);
		scanf("%d",ptr_f_type);
		
		printf("\n");
		
		if(*ptr_f_type!=1 && *ptr_f_type!=2 && *ptr_f_type!=3 && *ptr_f_type!=3 && *ptr_f_type!=4 && *ptr_f_type!=-1 ){
			is_correct=0;
			printf(" Wrong choice, Please try again\n");
		}
	}
}


void add_polynom(float polynom[],int size,int *polynom_grade){
	int i;
	printf("Please enter the grade of the polynom:");
	scanf("%d",polynom_grade);
	
	for(i=0;i<=*polynom_grade;i++){
		printf("Please enter the coefficient of the  %d'th grade element :",i);
		scanf("%f",&polynom[i]);
		
	}
	for(i=*polynom_grade;i>0;i--){
		printf("%0.2f x^%d + ",polynom[i],i);
	}
	printf("%0.2f added\n",polynom[0]);

	
	
}
void add_sinusoidal(float sinusoidal[][3],int row){
	printf("a*sin(b*x) / a*cos(b*x)\n");

	printf("Enter  0 for sinus, 1 for cosinus:");
	scanf("%f",&sinusoidal[row][0]);
	
	printf("Please enter the coefficient of sin/cos(...) element:");
	scanf("%f",&sinusoidal[row][1]);
	
	printf("Please enter the coefficient of x element:");
	scanf("%f",&sinusoidal[row][2]);


	if(sinusoidal[row][0]==0){
		printf("Added function is: %0.2fsin(%0.2f(x))\n",sinusoidal[row][1],sinusoidal[row][2]/*sinusoidal[row][3],(int)sinusoidal[row][4],sinusoidal[row][5]*/);
	}else{
		printf("Added function is: %0.2fcos(%0.2f(x))\n",sinusoidal[row][1],sinusoidal[row][2]/*sinusoidal[row][3],(int)sinusoidal[row][4],sinusoidal[row][5]*/);

	}

}

void add_exponential(float exponential[][3],int row){
	printf("a * (b)^(c*x)\n");
	printf("Enter the coefficient of exponential expression (a)   :");
	scanf("%f",&exponential[row][0]);
	printf("Enter the exponential expression's base' (b)  (for e enter 1 ) :");
	scanf("%f",&exponential[row][1]);
	printf("Enter the coefficient of x (c)    :");
	scanf("%f",&exponential[row][2]);
	

	
	if(exponential[row][1]==1){
		exponential[row][1]=e;
	}
	
	printf("Added function is:%0.2f*(%0.2f)^(%0.2f*x)\n ",exponential[row][0],exponential[row][1],exponential[row][2]/*,exponential[j][3]*/ );
	
}

void add_logarithmic(float logarithmic[][2], int row ){
	printf("Coefficient of logarithmic expression: ");
	scanf("%f",&logarithmic[row][0]);
	printf("enter the base: \n for 10 ---> 1 \n for e ---> 2 \n");
	scanf("%f",&logarithmic[row][1]);
	if(logarithmic[row][1]==1){
		printf("Added function is:  %0.2f log  (x)  in base 10\n",logarithmic[row][0]);
	}
	else{
		printf("Added function is:  %0.2f log  (x)  in base e\n",logarithmic[row][0]);

	}

	
}


void get_method_type(int *ptr_method_type){
	int is_correct=0;
	while(is_correct==0 ){
		is_correct=1;
		printf("\n");
		do{
		
			printf("\n\n 1---> Bisection method \n 2---> Linear Interpolation (regula falsi) \n 3---> Newton Raphson method\n\n 4---> Numeric Differantiation \n 5--->Trapez or simpson method \n  \n 6--->Gregory Newton interpolation -1 for exit   \n\n pick a method:");
			fflush(stdin);
			scanf("%d",ptr_method_type);
		}while(*ptr_method_type!=1 && *ptr_method_type!=2 && *ptr_method_type!=3 && *ptr_method_type!=3 && *ptr_method_type!=4 && *ptr_method_type!=5 && *ptr_method_type!=6 && *ptr_method_type!=7  && *ptr_method_type!=-1 );
		printf("\n");
		
	
	}
}


double f(float polynom[],int polynom_grade,float exponential[][3],int exponential_number,float sinusoidal[][3],int sinusoidal_number ,float logarithmic[][2], int logarithmic_number,double x){
	double result=0;
	int i;
	int j;
	int m;
	double element=0;
	double carpim=1; //multiplier
	long long bolum; //  denominator
	double pay=1; // numerator
	int sign;
	int iteration;
	double x2;
	int exponent;
	float base;
	//add polynom
	for(i=1;i<=polynom_grade;i++){
		carpim=1;
		for(j=0;j<i;j++){
			carpim*=x;
		}
		element=polynom[i]*carpim;
		result+= element;
	}
	result+=polynom[0];
	//add sinusoidal 
	for(i=0;i<sinusoidal_number;i++){
		if(sinusoidal[i][0]==0){ // sinus
		
				
				pay=1,
				sign=1;
				bolum=1;
				iteration=19;
				x2=sinusoidal[i][2]*x;
				
				x2=fmod(x2,(2*PI));
				
				m=1;
				for(j=1;j<=iteration;j+=2){
			
				carpim =1;
							
				bolum*=j*m;
				m=j-1;
				pay=x2;
				for(m=2;m<=j;m++){
					carpim=carpim*x2;
					pay=x2*carpim;
								
				}
							
				pay=pay*sign;
				sign*=-1;
					
				result+=(sinusoidal[i][1])*(pay/bolum);
			
				}
					
				
				//printf(" %lf",result);
		}
		else { //cosinus
				result+=sinusoidal[i][1];
				pay=1;
				sign=-1;
				bolum=1;
				iteration=20;
				x2=sinusoidal[i][2]*x;
				x2=fmod(x2,(2*PI));

				for(j=2;j<=iteration;j+=2){
				//result+=us(i,x)/fakt(i);
					carpim =1;
					bolum*=j*(j-1);
					for(m=2;m<=j;m++){
								carpim=carpim*x2;
								pay=x2*carpim;
							
					}
						
					pay=pay*sign;
					sign*=-1;
					
					result+= sinusoidal[i][1]*(pay/bolum);
				//	printf("pay : %lf , bolum : %lli\n",pay,bolum);
				}
		}

	}
	
	//exponantial
	
/*	for(i=0;i<exponential_number;i++){
		
		result+=exponential[i][0] * pow(exponential[i][1], exponential[i][2]*x );
			
		/*
		carpim=1;
		exponent=exponential[i][2]*x;

		if(exponent>0){
			base=exponential[i][1];

		}
		else {
			base=1/exponential[i][1];

		}
		
		for(m=0;m<abs(exponent);m++){
			carpim=base*carpim;
		}
		result+=exponential[i][0]*carpim;
		
	}*/
	
	//logarithmic
	for(i=0;i<logarithmic_number;i++){
		if(logarithmic[i][1]==1){
			
			result+=logarithmic[i][0]*log10(x);
		}
		else{
			result+=logarithmic[i][0]*log(x);
		}
		
	}
	
	
	
	
	
	
	
	
	
	return result;
}


void bisection(float polynom[],int polynom_grade,float exponential[][3],int exponential_number,float sinusoidal[][3],int sinusoidal_number ,float logarithmic[][2], int logarithmic_number){

	double low, high,mid,StopError,error,isroot=0;
	int bolum=1;
	int iteration=1;
	double x;
	printf(" upper limit is: ");
	scanf("%lf",&high);
	
	printf(" lower limit is: ");
	scanf("%lf",&low);
	
	printf(" Stop-error value: ");
	scanf("%lf",&StopError);
	
	error=(high-low );
	printf("\t\tHigh\t\tLow\t  mid\t  Error\n" );

	//printf("%lf --- %lf--- %lf\n",high,low,mid);
	
	
	while(error>StopError && ( (f(polynom,polynom_grade,exponential,exponential_number, sinusoidal,sinusoidal_number , logarithmic,  logarithmic_number,high)) * (f(polynom,polynom_grade,exponential,exponential_number, sinusoidal,sinusoidal_number , logarithmic,  logarithmic_number,low) ) < 0 )){
		isroot=1;
		printf( "%d'th iteration--->",iteration);
		mid=(high+low)/2;
		bolum=2*bolum;
		error=(high-low)/bolum;
		
		printf("%lf --- %lf--- %lf----%lf\n",high,low,mid,error);
		
		if( (f(polynom,polynom_grade,exponential,exponential_number, sinusoidal,sinusoidal_number , logarithmic,  logarithmic_number,mid))*(f(polynom,polynom_grade,exponential,exponential_number, sinusoidal,sinusoidal_number , logarithmic,  logarithmic_number,low))  < 0){
			
			high=mid;

		}
		else if((f(polynom,polynom_grade,exponential,exponential_number, sinusoidal,sinusoidal_number, logarithmic,  logarithmic_number,mid))*(f(polynom,polynom_grade,exponential,exponential_number, sinusoidal,sinusoidal_number , logarithmic,  logarithmic_number,high) ) < 0){
			low=mid;
		}
		
		iteration++;
		
		
	}
	
	if(isroot==0){
		if(f(polynom,polynom_grade,exponential,exponential_number, sinusoidal,sinusoidal_number , logarithmic,  logarithmic_number,high)==0){
			printf("root = %lf",high);
		}
		else if(f(polynom,polynom_grade,exponential,exponential_number, sinusoidal,sinusoidal_number , logarithmic,  logarithmic_number,low)==0){
			printf("root = %lf",low);
		}
		else{
			printf("\n\n there might not be any root in this range");

		}

	}

	

	else{
		
		printf("kok = %lf",mid);
	}
	
}



void regula_falsi(float polynom[],int polynom_grade,float exponential[][3],int exponential_number,float sinusoidal[][3],int sinusoidal_number ,float logarithmic[][2], int logarithmic_number){


	double low, high,mid,StopError,error,isroot=0;
	int bolum=1;
	int iteration=1;

	printf(" upper limit is: ");
	scanf("%lf",&high);
	
	printf(" lower limit is: ");
	scanf("%lf",&low);
	
	printf(" Stop-error valuse: ");
	scanf("%lf",&StopError);
	
	error=(high-low );
	printf("\t\tHigh\t\tLow\t  mid\t  Error\n" );

	//printf("%lf --- %lf--- %lf\n",high,low,mid);
	
	while(error>StopError && f(polynom,polynom_grade,exponential,exponential_number, sinusoidal,sinusoidal_number , logarithmic,  logarithmic_number,high)*f(polynom,polynom_grade,exponential,exponential_number, sinusoidal,sinusoidal_number , logarithmic,  logarithmic_number,low) < 0 ){
		isroot=1;
		printf( "%d.iterasyon--->",iteration);
		mid=(low*f(polynom,polynom_grade,exponential,exponential_number, sinusoidal,sinusoidal_number , logarithmic,  logarithmic_number,high)-high*f(polynom,polynom_grade,exponential,exponential_number, sinusoidal,sinusoidal_number, logarithmic,  logarithmic_number,low))/(f(polynom,polynom_grade,exponential,exponential_number, sinusoidal,sinusoidal_number , logarithmic,  logarithmic_number,high)-f(polynom,polynom_grade,exponential,exponential_number, sinusoidal,sinusoidal_number , logarithmic,  logarithmic_number,low));
		bolum=2*bolum;
		error=(high-low)/bolum;
		printf("%lf --- %lf--- %lf----%lf\n\n",high,low,mid,error);
		
		if( f(polynom,polynom_grade,exponential,exponential_number, sinusoidal,sinusoidal_number , logarithmic,  logarithmic_number,mid)*f(polynom,polynom_grade,exponential,exponential_number, sinusoidal,sinusoidal_number , logarithmic,  logarithmic_number,low)<0){
			
			high=mid;

		}
		else{
			low=mid;
		}
		iteration++;

	}
	if(isroot==0){
		if(f(polynom,polynom_grade,exponential,exponential_number, sinusoidal,sinusoidal_number , logarithmic,  logarithmic_number,high)==0){
			printf("higher root = %lf",high);
		}
		else if(f(polynom,polynom_grade,exponential,exponential_number, sinusoidal,sinusoidal_number , logarithmic,  logarithmic_number,low)==0){
			printf("lower root = %lf",low);
		}
		else{
			printf("\n\n Could not find any root in this range ");


		}

	}
	else{
		
		printf("root = %lf",mid);
	}
	
}

double numerical_differentiation(float polynom[],int polynom_grade,float exponential[][3],int exponential_number,float sinusoidal[][3],int sinusoidal_number ,float logarithmic[][2], int logarithmic_number,double x, char type){
	double result;
	double h;
	int difference_type;
	if(type=='A'){ //automatic ( newton raphson metodu için belirli h deðeri ve merkezi fark kullanýr)
		h=0.0000001;
		result=(f(polynom,polynom_grade,exponential,exponential_number, sinusoidal,sinusoidal_number , logarithmic,  logarithmic_number,x+h)-f(polynom,polynom_grade,exponential,exponential_number, sinusoidal,sinusoidal_number , logarithmic,  logarithmic_number,x-h))/(2*h);

	}
	else{//manuel
		printf("Enter the value of h:");
		scanf("%lf",&h);
		printf("The point whose derrivative you are looking for is:");
		scanf("%lf",&x);
		printf("1---> forward difference\n2---> backward difference\n3---> central difference\n");
		scanf("%d",&difference_type);
	
		if(difference_type==1){
			result=(f(polynom,polynom_grade,exponential,exponential_number, sinusoidal,sinusoidal_number , logarithmic,  logarithmic_number,x+h)-f(polynom,polynom_grade,exponential,exponential_number, sinusoidal,sinusoidal_number , logarithmic,  logarithmic_number,x))/(h);

		}
		else if(difference_type==2){
			result=(f(polynom,polynom_grade,exponential,exponential_number, sinusoidal,sinusoidal_number , logarithmic,  logarithmic_number,x)-f(polynom,polynom_grade,exponential,exponential_number, sinusoidal,sinusoidal_number , logarithmic,  logarithmic_number,x-h))/(h);

		}
		else if(difference_type==3){
			result=(f(polynom,polynom_grade,exponential,exponential_number, sinusoidal,sinusoidal_number , logarithmic,  logarithmic_number,x+h)-f(polynom,polynom_grade,exponential,exponential_number, sinusoidal,sinusoidal_number , logarithmic,  logarithmic_number,x-h))/(2*h);

		}
	}
	
	
	
	return result;
}

void newton_raphson(float polynom[],int polynom_grade,float exponential[][3],int exponential_number,float sinusoidal[][3],int sinusoidal_number ,float logarithmic[][2], int logarithmic_number){
	
	double x0,x1;
	double error=10,StopError;
	int iteration=1;
	
	
	printf("Enter the start value (x0) :");
	scanf("%lf",&x0);
	printf("Enter the stop value :");
	scanf("%lf",&StopError); 
	
	while(error>StopError && iteration!=50 ){
		x1=x0-(f(polynom,polynom_grade,exponential,exponential_number, sinusoidal,sinusoidal_number , logarithmic,  logarithmic_number,x0)/numerical_differentiation(polynom,polynom_grade,exponential,exponential_number, sinusoidal,sinusoidal_number , logarithmic,  logarithmic_number,x0,'A'));
		error=fabs(x1-x0);
		printf( "%d'th iteration---> x%d = %lf\t Error:%lf \n",iteration,iteration,x1,error);
		
		x0=x1;
		iteration++;
	}
	
	if( iteration== 50){
		printf("Function diverged for this start value");
	}
}




void matrix_operations(double matrix[][MAX] ,int *repeat){
	int row;
	int column;
	*repeat=2;
	int method;
	while(*repeat==2){
	
		printf("!!! For inversing matrix you should enter a square matrix!!!\n\n");
		printf("!!! For solving systems, number of columns must be higher than rows ([A:B]) !!! \n\n");
		printf("!!! For Gauss seidel, maximum coefficients must be at the diognal !!!\n\n");

		printf("number of rows (max 10) : ");
		scanf("%d",&row);
		
		printf("number of columns (max 10) : ");
		scanf("%d",&column);
		
		get_matrix(matrix,row,column);
		
	
	
		*repeat=1;
		while(*repeat==1){
			
			do{
				printf("\n 1---> Inverse a matrix \n 2---> Find root with Gauss-Elemination \n 3---> Find root with Gauss-Seidal\n\n");
				printf("Pick your operation");
				scanf("%d",&method);
			}while(method!=1 && method!=2 &&  method!=3  );
			
			if(method==1){
				matrix_inverse(matrix,row,column);
			}
			else if(method==2){
				gauss_elemination(matrix,row,column);
			}
			else{
				gauss_seidel(matrix,row,column);
			}
		
		
			printf("\n\n\n 1---> Try another method with the same matrix \n\n 2---> Reset the matrix \n\n 3---> Back to main menu\n\n -1 ---> Exit\n\n ");
			scanf("%d",repeat);
		}
	}
	
}

void get_matrix(double matrix[][MAX],int row ,int column){
	int i,j;
	printf("\n\n");
	for(i=0;i<row;i++){
		for(j=0;j<column;j++){
			printf("Matrix[%d][%d] : ",i,j);
			scanf("%lf",&matrix[i][j]);
		}
	}
}

void matrix_inverse(double matrix[][MAX],int row, int column){
	int i,j,k,n,m,c=1;
	double ratio,multip;
	double augmented[MAX][2*MAX];
	printf("-------Extented MAtrix---------\n");
	for(i=0;i<row;i++){					//EXTENDING MATRIX

		for(j=0;j<column;j++){

			augmented[i][j]=matrix[i][j];
			if(i==j){
				augmented[i][j+row]=1;
			}	
			else{
				augmented[i][j+row]=0;
			}
		}
	}
	
	for(i=0;i<row;i++){
		printf("\n");
		for(j=0;j<2*column;j++){
			printf(" %0.3lf ",augmented[i][j]);
		}
	}
	// genisletilmis matris üzerinde ters alma
	c=0;
	for(j=0;j<column;j++){
	
		if(augmented[j][j]!=1){
			ratio=augmented[j][j];
			for(k=0;k<2*column;k++){
				augmented[c][k]/=ratio;
			}
		}
		for(i=0;i<row;i++){
			if(i!=j){
				multip=augmented[i][j];
				for(k=0;k<2*column;k++){
					
					augmented[i][k]-=(multip*augmented[c][k]);
				}
			}	
				
			}
		
		printf("\n\n");		
		c++;
		for(n=0;n<row;n++){
			printf("\n");
			for(m=0;m<2*column;m++){
				printf(" %0.3lf ",augmented[n][m]);
			}
			
		}
	}
	printf("\n\n");
 //print the inverse
	for(i=0;i<row;i++){
		printf("\n");
		for(j=0;j<column;j++){
				printf(" %0.3lf ",augmented[i][j+row]);
			}
	}
	
}

void gauss_elemination(double matrix[][MAX],int row,int column ){
	int i,j,k,n,m,c=1;
	double roots[10]={0};
	double ratio,multip;
	
	for(i=0;i<row;i++){
		printf("\n");
		for(j=0;j<column;j++){
			printf(" %0.3lf ",matrix[i][j]);
		}
	}
	c=0;
	for(j=0;j<column;j++){
	
		if(matrix[j][j]!=1){
			ratio=matrix[j][j];
			for(k=0;k<2*column;k++){
				matrix[c][k]/=ratio;
			}
		}
		for(i=j;i<row;i++){
			if(i!=j){
				multip=matrix[i][j];
				for(k=0;k<column;k++){
					
					matrix[i][k]-=(multip*matrix[c][k]);
				}
			}	
				
			}
		
		printf("\n\n");		
		c++;
		for(n=0;n<row;n++){
			printf("\n");
			for(m=0;m<column;m++){
				printf(" %0.3lf ",matrix[n][m]);
			}
			
		}
		printf("\n");
	}
	
	for(i=row-1;i>=0;i--){
		roots[i]+=matrix[i][column-1];
		j=row-1;
		while(j>i){
			roots[i]-= (roots[j]*matrix[i][j]);
			j--;
		}
		printf("\n x%d = %lf \n",i+1,roots[i]);
	}
	
}

void gauss_seidel(double matrix[][MAX],int row,int column ){
	
	double equation[MAX][MAX]={0}; //çarpým için yardýmcý matris
	int i,j,k,max_ind,is_error,divergency=0;
	double error,tmp;
	double roots[MAX][MAX]={{0,0,0},{1000,1000,1000}}; //ilk satýrýnda kök degerlerini, ikinci satirinda hatalarý tutanmatris
	
	for(j=0;j<row;j++){
	
		//degiskeni yalnýz býrakýp katsayýlar matrisini(equation) doldurma
		equation[j][column-1]=matrix[j][column-1]/matrix[j][j];
		for(k=0;k<row;k++){
			if(k != j){
				equation[j][k]-=(matrix[j][k]/matrix[j][j]);
				
			}
		}
		
	}
	
	for(i=0;i<column;i++){
		printf("\n");
		for(j=0;j<column;j++){
			printf(" %0.3lf ",equation[i][j]);
		}
	}
	//baslanguc degerlerini alma
	printf("\n stop-error value:");
	scanf("%lf",&error);
	for(i=0;i<row;i++){
		printf("\n start value for  x%d  :",i+1);
		scanf("%lf",&roots[0][i]);
	}
	for(i=0;i<row;i++){
		printf("\tx%d\tE%d",i+1,i+1);
	}
	
	is_error=0;
	while(is_error==0 && divergency<=100){
		printf("\n");
		is_error=1;
		for(i=0;i<row;i++){
			tmp=roots[0][i];
			roots[0][i]=equation[i][column-1]; //x(i)'ye sabit sayýyý ekleme
			for(j=0;j<row;j++){
				if(equation[i][j]!=0){
					roots[0][i]+=equation[i][j]*roots[0][j]; //x(i)'ye diðer köklerden gelen sonucu ekleme
				}
			}
			roots[1][i]=fabs(tmp-roots[0][i]);
		}
		
		for(j=0;j<row;j++){
			if(roots[1][j]>error){
				is_error=0;
			}
			printf("\t%0.4lf\t%0.4lf",roots[0][j],roots[1][j]);
		}
		divergency++;
	}
	
	if(divergency>100){
		printf("\n\n Result diverged");
	}
	
}




void trapez_simpson(float polynom[],int polynom_grade,float exponential[][3],int exponential_number,float sinusoidal[][3],int sinusoidal_number ,float logarithmic[][2], int logarithmic_number){
	double ust_sinir,alt_sinir,n,sum,x,h,type;
	printf("\nlower bound:");
	scanf("%lf",&alt_sinir);
	printf("\nupper bound:");
	scanf("%lf",&ust_sinir);
	printf("\nnumber of ranges(must be even for simpson method) ");
	scanf("%lf",&n);
	printf("\n 1--> trapez \n 2---> simpson 1/3\n 3---> simpson 3/8\n ");
	scanf("%lf",&type);
	sum=0;
	x=alt_sinir;
	h=fabs(ust_sinir-alt_sinir)/n;
	if(type==1){
		while(x<ust_sinir){
			sum+=f(polynom,polynom_grade,exponential,exponential_number, sinusoidal,sinusoidal_number , logarithmic,  logarithmic_number,x)+f(polynom,polynom_grade,exponential,exponential_number, sinusoidal,sinusoidal_number , logarithmic,  logarithmic_number,x+h);
			x+=h;
		}
		sum*=(h/2);
	}
	else if(type==2){
		
		while(x<ust_sinir){
			sum+=f(polynom,polynom_grade,exponential,exponential_number, sinusoidal,sinusoidal_number , logarithmic,  logarithmic_number,x)+4*f(polynom,polynom_grade,exponential,exponential_number, sinusoidal,sinusoidal_number , logarithmic,  logarithmic_number,x+h)+f(polynom,polynom_grade,exponential,exponential_number, sinusoidal,sinusoidal_number , logarithmic,  logarithmic_number,x+2*h);
			x+=2*h;
		}
		sum*=(h/3);
	}
	else if(type==3){
		while(x<ust_sinir){
			sum+=f(polynom,polynom_grade,exponential,exponential_number, sinusoidal,sinusoidal_number , logarithmic,  logarithmic_number,x)+3*f(polynom,polynom_grade,exponential,exponential_number, sinusoidal,sinusoidal_number , logarithmic,  logarithmic_number,x+(h/3))+3*f(polynom,polynom_grade,exponential,exponential_number, sinusoidal,sinusoidal_number , logarithmic,  logarithmic_number,x+(2*h/3))+f(polynom,polynom_grade,exponential,exponential_number, sinusoidal,sinusoidal_number , logarithmic,  logarithmic_number,x+h);
			x+=h;
		}
		sum*=(h/8);
	}
	printf("\n result %lf",sum);
}

void gregory_newton(float polynom[],int polynom_grade,float exponential[][3],int exponential_number,float sinusoidal[][3],int sinusoidal_number ,float logarithmic[][2], int logarithmic_number){

	int grade,i,j,fakt;
	double sonlu_fark[10][10]={0},x0,h,x,pay,payda,h_clone,result;
	printf("\n Your curve's grade is : ");
	scanf("%d",&grade);
	printf("\n x0 nedir? ");
	scanf("%lf",&x0);
	printf("\n h nedir? ");
	scanf("%lf",&h);
	
	for(j=0;j<=grade;j++){
		printf("\n f(x%d) : ",j);
		scanf("%lf",&sonlu_fark[0][j]);
	}
	
/*	for(i=0;i<=grade;i++){
		printf("\n");
		for(j=0;j<=grade;j++){
			printf(" %lf ",sonlu_fark[i][j]);
		}
	}*/
	
	j=0;
	while(j<grade){
		
		
		for(i=1;i<=grade-j;i++){
			
			sonlu_fark[j+1][i-1]=sonlu_fark[j][i]-sonlu_fark[j][i-1];
		}
		
		j++;
	}

/*	for(i=0;i<=grade;i++){
		printf("\n");
		for(j=0;j<=grade;j++){
			printf(" %lf ",sonlu_fark[i][j]);
		}
	}*/

	printf("Value of the x that you want to find: ");
	scanf("%lf",&x);
	pay=1;
	fakt=1;
	payda=1;
	h_clone=0;
	result=sonlu_fark[0][0];
	for(i=1;i<=grade;i++){
			pay*=(x-x0-h_clone);
			payda*=h*i;
			result+=(pay*sonlu_fark[i][0])/payda;
			h_clone+=h;
			
			
	}
	
	printf("\n f(%0.2lf) = %lf ",x,result);
	
}








