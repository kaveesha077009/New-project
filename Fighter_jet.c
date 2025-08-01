#include <stdio.h>
#include <math.h>
 int main()
{
	float velocity_kmh;
	float velocity_ms;
	float distance_m;
	float acceleration;
	float time;

	printf("Enter the takeoff speed in kmh");
	scanf("%f", &velocity_kmh);
	printf("Enter distance in meter");
	scanf("%f", &distance_m);

	velocity_ms = velocity_kmh * 1000 / 3600;
	acceleration = (vrlocity_ms ^2) / (2 * distance);
	time = velocity_ms / acceleration;


	printf("\nAcceleration = %.2f m/s^2\n", acceleration);
	printf("Time to takeoff = %.2f seconds\n", time);
	
	return 0;

}
