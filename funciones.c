#include "funciones.h"

#define Limite_CO2 1000
#define Limite_NO2 100
#define Limite_SO2 100
#define Limite_PM25 25
#define NUM_CONTAMINANTES 4 // CO2, SO2, NO2, PM2.5;

// Función para mostrar el menú y obtener la opción seleccionada por el usuario
int menu()
{
    int opcion;
    printf("\nMenu:\n");
    printf("1. Ingresar datos de las zonas\n");
    printf("2. Generar recomendaciones\n");
    printf("3. Monitorear niveles de contaminacion\n");
    printf("4. Calcular promedios historicos\n");
    printf("5. Predecir niveles futuros\n");
    printf("6. Funcionalidad futura\n");
    printf("7. Salir\n");
    printf("Seleccione una opcion: ");
    scanf("%d", &opcion);
    return opcion;
}

// Función para leer los datos de las zonas desde un archivo
void leerzonas(struct Zona *zonas, int num_zonas)
{
    FILE *file = fopen("niveles_actuales.dat", "r");
    if (file == NULL)
    {
        printf("Error opening current levels data file!\n");
        return;
    }

    for (int i = 0; i < num_zonas; i++)
    {
        fscanf(file, "%s", zonas[i].nombre);
        for (int j = 0; j < NUM_CONTAMINANTES; j++)
        {
            fscanf(file, "%d", &zonas[i].niveles_actuales[j]);
        }
    }
    fclose(file);
}

// Función para leer los niveles actuales de contaminación desde un archivo
void leer_niveles_actuales(struct Zona *zonas, int num_zonas)
{
    FILE *file = fopen("niveles_actuales.dat", "r");
    if (file == NULL)
    {
        printf("Error opening current levels data file!\n");
        return;
    }

    for (int i = 0; i < num_zonas; i++)
    {
        fscanf(file, "%s", zonas[i].nombre);
        for (int j = 0; j < NUM_CONTAMINANTES; j++)
        {
            fscanf(file, "%d", &zonas[i].niveles_actuales[j]);
        }
    }
    fclose(file);
}

// Función para monitorear los niveles de contaminación y compararlos con los límites
void monitorear_contaminacion(struct Zona *zonas, int num_zonas)
{
    leer_niveles_actuales(zonas, num_zonas);

    int limites[NUM_CONTAMINANTES] = {Limite_CO2, Limite_NO2, Limite_SO2, Limite_PM25};

    printf("\nComparacion con limites:\n");
    printf("-------------------------------------------------\n");
    printf("| Zona       | Contaminante | Nivel | Limite | %% |\n");
    printf("-------------------------------------------------\n");

    for (int i = 0; i < num_zonas; i++)
    {
        for (int j = 0; j < NUM_CONTAMINANTES; j++)
        {
            float porcentaje = (float)zonas[i].niveles_actuales[j] / limites[j] * 100;
            printf("| %-10s | %-12d | %-5d | %-6d | %-3.2f%% |\n",
                   zonas[i].nombre, j + 1, zonas[i].niveles_actuales[j], limites[j], porcentaje);
            if (zonas[i].niveles_actuales[j] > limites[j])
            {
                float excedente = ((float)zonas[i].niveles_actuales[j] - limites[j]) / limites[j] * 100;
                printf("Advertencia: El nivel del contaminante %d en la zona %s excede el limite por %.2f%%\n",
                       j + 1, zonas[i].nombre, excedente);
            }
        }
    }
    printf("-------------------------------------------------\n");
}

// Función para predecir los niveles futuros de contaminación basados en el clima
void predecir_niveles_futuros(struct Zona *zonas, int num_zonas, struct Clima clima)
{
    leer_niveles_actuales(zonas, num_zonas);

    int limites[NUM_CONTAMINANTES] = {Limite_CO2, Limite_NO2, Limite_SO2, Limite_PM25};

    printf("\nComparacion con limites:\n");
    printf("-------------------------------------------------\n");
    printf("| Zona       | Contaminante | Nivel | Limite | %% |\n");
    printf("-------------------------------------------------\n");

    for (int i = 0; i < num_zonas; i++)
    {
        for (int j = 0; j < NUM_CONTAMINANTES; j++)
        {
            float porcentaje = (float)zonas[i].niveles_actuales[j] / limites[j] * 100;
            printf("| %-10s | %-12d | %-5d | %-6d | %-3.2f%% |\n",
                   zonas[i].nombre, j + 1, zonas[i].niveles_actuales[j], limites[j], porcentaje);
            if (zonas[i].niveles_actuales[j] > limites[j])
            {
                float excedente = ((float)zonas[i].niveles_actuales[j] - limites[j]) / limites[j] * 100;
                printf("Advertencia: El nivel del contaminante %d en la zona %s excede el limite por %.2f%%\n",
                       j + 1, zonas[i].nombre, excedente);
            }
        }
    }
    printf("-------------------------------------------------\n");
    printf("Prediccion de niveles futuros:\n");
    printf("-------------------------------------------------\n");
    printf("| Zona       | Contaminante | Nivel | Limite | %% |\n");
    printf("-------------------------------------------------\n");
    for (int i = 0; i < num_zonas; i++)
    {
        for (int j = 0; j < NUM_CONTAMINANTES; j++)
        {
            float factor = 1.0;
            if (clima.temperatura > 30)
                factor += 0.1;
            if (clima.velocidad_viento < 5)
                factor += 0.1;
            if (clima.humedad < 30)
                factor += 0.1;

            int nivel_futuro = zonas[i].niveles_actuales[j] * factor;
            float porcentaje = (float)nivel_futuro / limites[j] * 100;

            printf("| %-10s | %-12d | %-5d | %-6d | %-3.2f%% |\n",
                   zonas[i].nombre, j + 1, nivel_futuro, limites[j], porcentaje);

            if (nivel_futuro > limites[j])
            {
                float excedente = ((float)nivel_futuro - limites[j]) / limites[j] * 100;
                printf("Advertencia: El nivel del contaminante %d en la zona %s excedera el limite por %.2f%%\n",
                       j + 1, zonas[i].nombre, excedente);
            }
        }
    }
    printf("-------------------------------------------------\n");
}

// Función para calcular los promedios históricos de contaminación
void calcular_promedios_historicos(struct Zona *zonas, int num_zonas)
{
    FILE *file = fopen("historico.dat", "r");
    if (file == NULL)
    {
        printf("Error opening historical data file!\n");
        return;
    }

    int limites[NUM_CONTAMINANTES] = {Limite_CO2, Limite_NO2, Limite_SO2, Limite_PM25};
    int historico[30][NUM_CONTAMINANTES];

    for (int i = 0; i < num_zonas; i++)
    {
        printf("Zona: %s\n", zonas[i].nombre);
        for (int j = 0; j < NUM_CONTAMINANTES; j++)
        {
            int sum = 0;
            for (int k = 0; k < 30; k++)
            {
                fscanf(file, "%d", &historico[k][j]);
                sum += historico[k][j];
            }
            int promedio = sum / 30;
            float porcentaje = (float)promedio / limites[j] * 100;
            printf("Promedio del contaminante %d: %d (%.2f%% del limite)\n", j + 1, promedio, porcentaje);
            if (promedio > limites[j])
            {
                float excedente = ((float)promedio - limites[j]) / limites[j] * 100;
                printf("Advertencia: El promedio del contaminante %d en la zona %s excede el limite por %.2f%%\n",
                       j + 1, zonas[i].nombre, excedente);
            }
        }
    }
    fclose(file);
}

// Función para generar recomendaciones basadas en los niveles actuales de contaminación
void generar_recomendaciones(struct Zona *zonas, int num_zonas)
{
    leer_niveles_actuales(zonas, num_zonas);

    int limites[NUM_CONTAMINANTES] = {Limite_CO2, Limite_NO2, Limite_SO2, Limite_PM25};
    const char *nombres_contaminantes[NUM_CONTAMINANTES] = {"CO2", "NO2", "SO2", "PM2.5"};

    for (int i = 0; i < num_zonas; i++)
    {
        printf("Recomendaciones para la zona %s:\n", zonas[i].nombre);
        for (int j = 0; j < NUM_CONTAMINANTES; j++)
        {
            printf("Contaminante: %s\n", nombres_contaminantes[j]);
            if (zonas[i].niveles_actuales[j] > limites[j])
            {
                printf(" - El nivel del contaminante %s excede el límite.\n", nombres_contaminantes[j]);
                if (j == 0)
                {
                    printf("   * Implementar medidas para reducir las emisiones de CO2.\n");
                    printf("   * Se recomienda reducir el uso excesivo de automóviles y utilizar más transportes no contaminantes.\n");
                    printf("   * Promover el uso de energías renovables.\n");
                }
                else if (j == 1)
                {
                    printf("   * Implementar medidas para reducir las emisiones de NO2.\n");
                    printf("   * Se recomienda mejorar la eficiencia de los motores de combustión.\n");
                    printf("   * Fomentar el uso de transporte público.\n");
                }
                else if (j == 2)
                {
                    printf("   * Implementar medidas para reducir las emisiones de SO2.\n");
                    printf("   * Se recomienda utilizar combustibles con bajo contenido de azufre.\n");
                    printf("   * Instalar sistemas de desulfuración en plantas industriales.\n");
                }
                else if (j == 3)
                {
                    printf("   * Implementar medidas para reducir las emisiones de PM2.5.\n");
                    printf("   * Se recomienda controlar las emisiones de polvo en la construcción.\n");
                    printf("   * Promover el uso de filtros en chimeneas y vehículos.\n");
                }
            }
            else
            {
                printf(" - Los niveles del contaminante %s están dentro del límite.\n", nombres_contaminantes[j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

// Función para pedir datos de una zona y guardarlos en un archivo
void pedirDatosZona(struct Zona *zona, const char *nombre)
{
    strcpy(zona->nombre, nombre);
    FILE *file = fopen("niveles_actuales.dat", "a");
    if (file == NULL)
    {
        printf("Error opening current levels data file!\n");
        return;
    }
    fprintf(file, "%s ", nombre);
    for (int i = 0; i < 4; i++)
    {
        printf("Nivel %d: ", i + 1);
        scanf("%d", &zona->niveles_actuales[i]);
        fprintf(file, "%d ", zona->niveles_actuales[i]);
    }
    fprintf(file, "\n");
    fclose(file);
}

// Función para pedir datos del clima y guardarlos en un archivo
void pedirDatosClima(struct Clima *clima)
{
    FILE *file = fopen("clima.dat", "w");
    if (file == NULL)
    {
        printf("Error opening climate data file!\n");
        return;
    }
    printf("Ingrese la temperatura: ");
    scanf("%d", &clima->temperatura);
    printf("Ingrese la velocidad del viento: ");
    scanf("%d", &clima->velocidad_viento);
    printf("Ingrese la humedad: ");
    scanf("%d", &clima->humedad);
    fprintf(file, "%d %d %d\n", clima->temperatura, clima->velocidad_viento, clima->humedad);
    fclose(file);
}