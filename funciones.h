#include <stdio.h>
#include <string.h>

void save(int temperatura, int velocidaddelviento, int humedad, int presion);
void recomendaciones(int temperatura, int velocidaddelviento, int humedad, int presion);
void alertaspreventivas(int temperatura, int velocidaddelviento, int humedad, int presion);
int promediohistorico(int temperatura, int velocidaddelviento, int humedad, int presion);
int monitoreofuturo(int temperatura, int velocidaddelviento, int humedad, int presion);
int monitoreoactual(int temperatura, int velocidaddelviento, int humedad, int presion);
int menu();
