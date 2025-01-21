#include "funciones.h"

int main()
{
    int opcion;
    struct Zona zonas[5]; // Arreglo para almacenar datos de 5 zonas
    struct Clima clima;   // Estructura para almacenar datos climáticos
    int i;

    // Bucle para obtener los nombres de las 5 zonas del usuario
    for (i = 0; i < 5; i++)
    {
        printf("Ingrese el nombre de la zona %d: ", i + 1);
        scanf("%s", zonas[i].nombre);
    }

    // Bucle infinito para mostrar el menú y procesar las opciones del usuario
    while (1)
    {
        opcion = menu(); // Mostrar menú y obtener la opción del usuario

        switch (opcion)
        {
        case 1:
            // Obtener datos para cada zona
            for (i = 0; i < 5; i++)
            {
                pedirDatosZona(&zonas[i], zonas[i].nombre);
            }
            break;
        case 2:
            // Generar recomendaciones basadas en los datos de las zonas
            generar_recomendaciones(zonas, 5);
            break;
        case 3:
            // Monitorear niveles de contaminación en las zonas
            monitorear_contaminacion(zonas, 5);
            break;
        case 4:
            // Calcular promedios históricos para las zonas
            calcular_promedios_historicos(zonas, 5);
            break;
        case 5:
            // Predecir niveles futuros basados en los datos de las zonas y el clima
            predecir_niveles_futuros(zonas, 5);
            break;
        case 6:
            // Espacio reservado para funcionalidad futura
            break;
        case 7:
            // Salir del programa
            return 0;
        default:
            // Manejar opciones de menú inválidas
            printf("Opcion invalida\n");
            break;
        }
    }

    return 0;
}