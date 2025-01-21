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
    printf("\n");
    printf("1. Ingresar datos de las zonas\n");
    printf("2. Generar recomendaciones\n");
    printf("3. Monitorear niveles de contaminación\n");
    printf("4. Calcular promedios históricos\n");
    printf("5. Predecir niveles futuros\n");
    printf("6. Funcionalidad adicional\n");
    printf("7. Salir\n");
    printf("Seleccione una opción: ");
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
        fscanf(file, "%49s", zonas[i].nombre); // Limitar la longitud del nombre a 49 caracteres
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
void predecir_niveles_futuros(struct Zona *zonas, int num_zonas) {
    // Límites de contaminantes
    int limites[NUM_CONTAMINANTES] = {Limite_CO2, Limite_NO2, Limite_SO2, Limite_PM25};
    const char *contaminante_names[NUM_CONTAMINANTES] = {"CO2", "NO2", "SO2", "PM2.5"};

    // Abrir archivo de datos históricos
    FILE *file = fopen("niveles_historicos.dat", "r");
    if (file == NULL) {
        printf("Error al abrir el archivo niveles_historicos.dat.\n");
        return;
    }

    // Leer datos históricos de cada zona
    for (int i = 0; i < num_zonas; i++) {
        fscanf(file, "%s", zonas[i].nombre);  // Leer el nombre de la zona

        // Leer los niveles históricos para los últimos 30 días por contaminante
        for (int j = 0; j < NUM_CONTAMINANTES; j++) {
            for (int k = 0; k < 30; k++) {
                fscanf(file, "%f", &zonas[i].niveles_historicos[k][j]);
                // Validar valores negativos
                if (zonas[i].niveles_historicos[k][j] < 0) {
                    printf("Advertencia: valor negativo en zona %s, contaminante %s, día %d. Ajustado a 0.\n",
                           zonas[i].nombre, contaminante_names[j], k + 1);
                    zonas[i].niveles_historicos[k][j] = 0.0;
                }
            }
        }
    }
    fclose(file);

    // Abrir archivo de datos climáticos
    FILE *clima_file = fopen("climatico.dat", "r");
    if (clima_file == NULL) {
        printf("Error al abrir el archivo climatico.dat.\n");
        return;
    }

    // Leer datos climáticos para los últimos 30 días
    struct Clima clima_historico[30];
    for (int k = 0; k < 30; k++) {
        fscanf(clima_file, "%f %f %f", &clima_historico[k].temperatura,
               &clima_historico[k].velocidad_viento, &clima_historico[k].humedad);
    }
    fclose(clima_file);

    // Imprimir encabezado
    printf("Predicción de niveles futuros:\n");
    printf("----------------------------------------------------------------------------\n");
    printf("| Zona       | Contaminante | Nivel Futuro | Limite  | %% Limite | Total Zona |\n");
    printf("----------------------------------------------------------------------------\n");

    // Calcular predicciones
    for (int i = 0; i < num_zonas; i++) {
        float total_contaminacion_zona = 0.0;  // Predicción total para la zona

        for (int j = 0; j < NUM_CONTAMINANTES; j++) {
            // Calcular promedio de los últimos 30 días
            float suma = 0.0;
            for (int k = 0; k < 30; k++) {
                suma += zonas[i].niveles_historicos[k][j];
            }
            float promedio = suma / 30.0;

            // Calcular factor climático
            float factor = 1.0;
            for (int k = 0; k < 30; k++) {
                if (clima_historico[k].temperatura > 30)
                    factor += 0.1 / 30;
                if (clima_historico[k].velocidad_viento < 5)
                    factor += 0.1 / 30;
                if (clima_historico[k].humedad < 30)
                    factor += 0.1 / 30;
            }

            // Calcular nivel futuro
            int nivel_futuro = (int)(promedio * factor);
            if (nivel_futuro < 0) nivel_futuro = 0;  // Ajustar a 0 si es negativo

            // Calcular porcentaje con respecto al límite
            float porcentaje = (float)nivel_futuro / limites[j] * 100;

            // Sumar al total de la zona
            total_contaminacion_zona += nivel_futuro;

            // Imprimir resultados por contaminante
            printf("| %-10s | %-12s | %-12d | %-7d | %-9.2f | %-11.2f |\n",
                   zonas[i].nombre, contaminante_names[j], nivel_futuro, limites[j], porcentaje, total_contaminacion_zona);
        }

        // Imprimir total por zona
        printf("----------------------------------------------------------------------------\n");
        printf("| Total Predicción de Contaminación para la zona %-10s: %-11.2f |\n", zonas[i].nombre, total_contaminacion_zona);
        printf("----------------------------------------------------------------------------\n");
    }
}




// Función para calcular los promedios históricos de contaminación
void calcular_promedios_historicos(struct Zona *zonas, int num_zonas)
{
    FILE *file = fopen("niveles_historicos.dat", "r");
    if (file == NULL) {
        printf("Error al abrir el archivo niveles_actuales.dat\n");
        return;
    }

    char nombre_zona[50];
    float suma_contaminantes[NUM_CONTAMINANTES] = {0.0};
    num_zonas = 0;

    // Leer datos del archivo
    while (fscanf(file, "%s", nombre_zona) != EOF) {
        float suma_diaria[NUM_CONTAMINANTES] = {0.0};

        // Leer los 30 días de datos para los 4 contaminantes
        for (int dia = 0; dia < 30; dia++) {
            for (int i = 0; i < NUM_CONTAMINANTES; i++) {
                float contaminante;
                if (fscanf(file, "%f", &contaminante) == 1) {
                    suma_diaria[i] += contaminante;
                }
            }
        }

        // Sumar los promedios diarios de cada contaminante
        for (int i = 0; i < NUM_CONTAMINANTES; i++) {
            suma_contaminantes[i] += suma_diaria[i] / 30; // Promedio diario por zona
        }
        num_zonas++;
    }
    fclose(file);

    // Calcular los promedios generales por contaminante
    printf("\nPromedio histórico de contaminación (últimos 30 días):\n");
    float suma_total_contaminacion = 0.0;
    const char *nombres_contaminantes[NUM_CONTAMINANTES] = {"CO2", "NO2", "SO2", "PM2.5"};
    for (int i = 0; i < NUM_CONTAMINANTES; i++) {
        float promedio_general = suma_contaminantes[i] / num_zonas;
        printf("Promedio de %s: %.2f\n", nombres_contaminantes[i], promedio_general);
        suma_total_contaminacion += promedio_general;
    }

    // Mostrar el valor total de contaminación
    printf("Valor total de contaminación (suma de promedios): %.2f\n", suma_total_contaminacion);
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
