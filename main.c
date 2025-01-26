#include "funciones.h"

int main() {
    int opc;
    
    do {
        menu();
        scanf("%d", &opc);
        limpiarBuffer();
        switch (opc) {
            case 1:
                agregarZona();
                break;
            case 2:
                mostrarZonas();
                break;
            case 3:
                generarReporte();
                break;
            case 4:
                promediohistorico();
                break;
            case 5:
                generarReporteHistorico();
                break;
            case 6:
                prediccionContaminantesPromedio(); 
                break;
            case 7: 
                FILE *archivo = fopen("zonas.txt", "r");

                if (archivo == NULL) {
                    printf("No se pudo abrir el archivo\n");
                    return 1;
                }
                leer_reporte(archivo);
                fclose(archivo);
                break;

            case 8:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opción no válida. Intente de nuevo.\n");
                break;
        }
    } while (opc != 8);
    return 0;
}