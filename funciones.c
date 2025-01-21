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

    const char *nombres_contaminantes[NUM_CONTAMINANTES] = {"CO2", "NO2", "SO2", "PM2.5"};

    for (int i = 0; i < num_zonas; i++)
    {
        fscanf(file, "%s", zonas[i].nombre);
        printf("Leyendo datos para la zona: %s\n", zonas[i].nombre);
        for (int j = 0; j < NUM_CONTAMINANTES; j++)
        {
            do {
                fscanf(file, "%d", &zonas[i].niveles_actuales[j]);
                if (zonas[i].niveles_actuales[j] < 0) {
                    printf("Error: El nivel de %s debe ser un número positivo. Intente de nuevo.\n", nombres_contaminantes[j]);
                }
            } while (zonas[i].niveles_actuales[j] < 0);
            printf("  Nivel de %s: %d\n", nombres_contaminantes[j], zonas[i].niveles_actuales[j]);
        }
    }
    fclose(file);
}

// Función para monitorear los niveles de contaminación y compararlos con los límites
void monitorear_contaminacion(struct Zona *zonas, int num_zonas)
{
    FILE *file = fopen("niveles_actuales.dat", "r");
    if (file == NULL)
    {
        printf("Error opening current levels data file!\n");
        return;
    }

    int i = 0;
    while (i < num_zonas && fscanf(file, "%s", zonas[i].nombre) == 1) {
        for (int j = 0; j < NUM_CONTAMINANTES; j++) {
            if (fscanf(file, "%f", &zonas[i].niveles_actuales[j]) != 1) { // Cambiar a %f
                printf("Error leyendo niveles de contaminantes para la zona %s\n", zonas[i].nombre);
                fclose(file);
                return;
            }
        }
        i++;
    }
    fclose(file);

    float limites[NUM_CONTAMINANTES] = {Limite_CO2, Limite_NO2, Limite_SO2, Limite_PM25};
    const char *nombres_contaminantes[NUM_CONTAMINANTES] = {"CO2", "NO2", "SO2", "PM2.5"};

    printf("\nComparacion con limites:\n");
    printf("-------------------------------------------------\n");
    printf("| Zona       | Contaminante | Nivel   | Limite | %%      |\n");
    printf("-------------------------------------------------\n");

    for (int i = 0; i < num_zonas; i++)
    {
        for (int j = 0; j < NUM_CONTAMINANTES; j++)
        {
            float porcentaje = (zonas[i].niveles_actuales[j] / limites[j]) * 100;
            printf("| %-10s | %-12s | %-7.2f | %-6.2f | %-6.2f%% |\n",
                   zonas[i].nombre, nombres_contaminantes[j], zonas[i].niveles_actuales[j], limites[j], porcentaje);

            if (zonas[i].niveles_actuales[j] > limites[j])
            {
                float excedente = ((zonas[i].niveles_actuales[j] - limites[j]) / limites[j]) * 100;
                printf("Advertencia: El nivel del contaminante %s en la zona %s excede el limite por %.2f%%\n",
                       nombres_contaminantes[j], zonas[i].nombre, excedente);
            }
        }
    }
    printf("-------------------------------------------------\n");
}



// Función para predecir los niveles futuros de contaminación basados en el clima
void predecir_niveles_futuros(struct Zona *zonas, int num_zonas, struct Clima clima)
{
    // Definir límites de contaminantes
    int limites[NUM_CONTAMINANTES] = {Limite_CO2, Limite_NO2, Limite_SO2, Limite_PM25};
    const char *contaminante_names[NUM_CONTAMINANTES] = {"CO2", "NO2", "SO2", "PM2.5"};

    // Leer datos históricos de contaminación
    FILE *file = fopen("niveles_historicos.dat", "r");
    if (file == NULL)
    {
        printf("Error al abrir el archivo de niveles históricos.\n");
        return;
    }

    // Leer los datos históricos de cada zona
    for (int i = 0; i < num_zonas; i++)
    {
        fscanf(file, "%s", zonas[i].nombre);  // Leer el nombre de la zona

        // Leer los datos históricos para cada contaminante
        for (int j = 0; j < NUM_CONTAMINANTES; j++)
        {
            for (int k = 0; k < 30; k++)  // Los últimos 30 días
            {
                fscanf(file, "%f", &zonas[i].niveles_historicos[k][j]);
            }
        }
    }
    fclose(file);

    // Leer datos climáticos históricos
    FILE *clima_file = fopen("climatico.dat", "r");
    if (clima_file == NULL)
    {
        printf("Error al abrir el archivo de datos climáticos.\n");
        return;
    }

    struct Clima clima_historico[30];
    for (int i = 0; i < 30; i++)
    {
        fscanf(clima_file, "%f %f %f", &clima_historico[i].temperatura, &clima_historico[i].velocidad_viento, &clima_historico[i].humedad);
    }
    fclose(clima_file);

    // Imprimir encabezado para los resultados
    printf("Predicción de niveles futuros:\n");
    printf("-------------------------------------------------\n");
    printf("| Zona       | Contaminante | Nivel | Limite | %% |\n");
    printf("-------------------------------------------------\n");

    // Realizar predicción para cada zona y contaminante
    for (int i = 0; i < num_zonas; i++)
    {
        // Promediar los datos históricos de los últimos 30 días
        for (int j = 0; j < NUM_CONTAMINANTES; j++)
        {
            float sum = 0.0;
            // Sumar los niveles históricos
            for (int k = 0; k < 30; k++)
            {
                sum += zonas[i].niveles_historicos[k][j];
            }

            // Calcular el promedio de los últimos 30 días
            float promedio = sum / 30.0;

            // Factor climático de predicción
            float factor = 1.0;
            for (int k = 0; k < 30; k++)
            {
                if (clima_historico[k].temperatura > 30)  // Si la temperatura es alta
                    factor += 0.1 / 30;
                if (clima_historico[k].velocidad_viento < 5)  // Si la velocidad del viento es baja
                    factor += 0.1 / 30;
                if (clima_historico[k].humedad < 30)  // Si la humedad es baja
                    factor += 0.1 / 30;
            }

            // Calcular el nivel futuro
            int nivel_futuro = (int)(promedio * factor);

            // Calcular el porcentaje con respecto al límite
            float porcentaje = (float)nivel_futuro / limites[j] * 100;

            // Imprimir los resultados de la predicción
            printf("| %-10s | %-12s | %-5d | %-6d | %-3.2f%% |\n",
                   zonas[i].nombre, contaminante_names[j], nivel_futuro, limites[j], porcentaje);

            // Verificar si el nivel futuro excede el límite
            if (nivel_futuro > limites[j])
            {
                float excedente = ((float)nivel_futuro - limites[j]) / limites[j] * 100;
                printf("Advertencia: El nivel del contaminante %s en la zona %s excederá el límite por %.2f%%\n",
                       contaminante_names[j], zonas[i].nombre, excedente);
            }
        }
    }

    printf("-------------------------------------------------\n");
}



// Función para calcular los promedios históricos de contaminación
void calcular_promedios_historicos(struct Zona *zonas, int num_zonas)
{
    int NUM_DIAS = 30;
    FILE *file = fopen("niveles_historicos.dat", "r");
    if (file == NULL)
    {
        printf("Error abriendo el archivo de datos históricos!\n");
        return;
    }

    int limites[NUM_CONTAMINANTES] = {Limite_CO2, Limite_NO2, Limite_SO2, Limite_PM25};
    const char *nombres_contaminantes[NUM_CONTAMINANTES] = {"CO2", "NO2", "SO2", "PM2.5"};

    for (int i = 0; i < num_zonas; i++)
    {
        // Leer el nombre de la zona
        fscanf(file, "%s", zonas[i].nombre);
        printf("Zona: %s\n", zonas[i].nombre);

        // Leer los datos históricos para los 30 días de cada contaminante
        for (int j = 0; j < NUM_CONTAMINANTES; j++)
        {
            float sum = 0;
            // Leer los 30 días de datos para el contaminante j
            for (int k = 0; k < NUM_DIAS; k++)
            {
                if (fscanf(file, "%f", &zonas[i].niveles_historicos[k][j]) != 1)
                {
                    printf("Error leyendo datos históricos para la zona %s, contaminante %s\n", zonas[i].nombre, nombres_contaminantes[j]);
                    fclose(file);
                    return;
                }
                sum += zonas[i].niveles_historicos[k][j]; // Sumar los niveles de contaminación
            }

            // Calcular el promedio de los últimos 30 días
            float promedio = sum / NUM_DIAS;
            float porcentaje = (promedio / limites[j]) * 100;

            // Mostrar los resultados
            printf("Promedio del contaminante %s: %.2f (%.2f%% del límite)\n", nombres_contaminantes[j], promedio, porcentaje);

            // Verificar si el promedio excede el límite
            if (promedio > limites[j])
            {
                float excedente = ((promedio - limites[j]) / limites[j]) * 100;
                printf("Advertencia: El promedio del contaminante %s en la zona %s excede el límite por %.2f%%\n",
                       nombres_contaminantes[j], zonas[i].nombre, excedente);
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
    // Copiar el nombre a la estructura
    strncpy(zona->nombre, nombre, sizeof(zona->nombre) - 1);
    zona->nombre[sizeof(zona->nombre) - 1] = '\0'; // Asegurar terminación nula

    // Nombres de los contaminantes
    const char *nombres_contaminantes[NUM_CONTAMINANTES] = {"CO2", "NO2", "SO2", "PM2.5"};

    // Pedir niveles de contaminación
    for (int i = 0; i < NUM_CONTAMINANTES; i++) {
        do {
            printf("Ingrese el nivel de %s para la zona %s: ", nombres_contaminantes[i], nombre);

            // Cambiar scanf para capturar float
            if (scanf("%f", &zona->niveles_actuales[i]) != 1 || zona->niveles_actuales[i] < 0) {
                printf("Error: El nivel de %s debe ser un número positivo. Intente de nuevo.\n", nombres_contaminantes[i]);
                zona->niveles_actuales[i] = -1; // Marcar como inválido

                // Limpiar el búfer
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
            }
        } while (zona->niveles_actuales[i] < 0);
    }

    // Abrir archivo en modo adición
    FILE *file = fopen("niveles_actuales.dat", "a");
    if (file == NULL) {
        perror("Error al abrir el archivo niveles_actuales.dat");
        return;
    }

    // Escribir datos en el archivo
    fprintf(file, "%s ", zona->nombre);
    for (int i = 0; i < NUM_CONTAMINANTES; i++) {
        fprintf(file, "%.2f ", zona->niveles_actuales[i]); // Escribir float con dos decimales
    }
    fprintf(file, "\n");

    fclose(file);
    printf("Datos de la zona %s guardados correctamente.\n", zona->nombre);
}
