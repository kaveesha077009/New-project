#include <stdio.h>
  
int main()
{ 
	float length_rectangle;
	float length_square;
	float width_rectangle;
		float width_square;
	float rectangle_area;
	float square_area;

	printf("Enter the lenght of rectangle:");
	scanf("%f", &length_rectangle);
	printf("Enter the width of rectangle:");
	scanf("%f", &width_rectangle);
	printf("Enter the lenght of square:");
	scanf("%f", &length_square);
	printf("Enter the width of square:");
	scanf("%f", &width_square);

	rectangle_area = length_rectangle * width_rectangle;
	square_area = length_square * width_square;

	printf("display area of rectangle : %.2f\n", rectangle_area);
	printf("display area of square : %.2f\n", square_area);
	return 0;
}
