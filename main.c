#include "funciones.h"

int main() {
    int temperatura, velocidaddelviento, humedad, presion;
    int opcion;
    do {
        opcion = menu();
        switch (opcion) {
            case 1:
                printf("Ingrese la temperatura: ");
                scanf("%d", &temperatura);
                printf("Ingrese la velocidad del viento: ");
                scanf("%d", &velocidaddelviento);
                printf("Ingrese la humedad: ");
                scanf("%d", &humedad);
                printf("Ingrese la presion: ");
                scanf("%d", &presion);
                save(temperatura, velocidaddelviento, humedad, presion);
                break;
            case 2:
                recomendaciones(temperatura, velocidaddelviento, humedad, presion);
                break;
            case 3:
                alertaspreventivas(temperatura, velocidaddelviento, humedad, presion);
                break;
            case 4:
                promediohistorico(temperatura, velocidaddelviento, humedad, presion);
                break;
            case 5:
                monitoreofuturo(temperatura, velocidaddelviento, humedad, presion);
                break;
            case 6:
                monitoreoactual(temperatura, velocidaddelviento, humedad, presion);
                break;
            case 7:
                break;
            default:
                printf("Opción no válida\n");
                break;
        }
    } while (opcion != 7);
    return 0;
}