#include "funciones.h"


// Función para mostrar el menú y obtener la opción seleccionada por el usuario
void menu() {
    int opcion;
    printf("\nMenú de opciones:\n");
    printf("1. Agregar zona\n");
    printf("2. Mostrar zonas\n");
    printf("3. Generar reporte actual\n");
    printf("4. datos históricos\n");
    printf("5. Generar reporte histórico\n");
    printf("6. Predicción de contaminantes\n");
    printf("7. Recomendaciones por zona\n");
    printf("8. Salir\n");
    printf("Seleccione una opción: ");
}

// Función para limpiar el búfer de entrada
void limpiarBuffer() {
    while (getchar() != '\n'); // Descartar todo hasta un salto de línea
}

// Función para agregar una nueva zona
void agregarZona() {
    FILE *f = fopen("zonas.txt", "a");  
    if (f == NULL) {
        printf("Error: No se pudo abrir el archivo zonas.txt\n");
        return;
    }

    struct Zona nuevaZona;

    // Pedir los datos de la nueva zona
    printf("Ingrese el nombre de la zona: ");
    scanf("%s", nuevaZona.nombre);

    do {
        printf("Ingrese el nivel de CO2 (ppm): ");
        if (scanf("%f", &nuevaZona.actual.CO2) != 1 || nuevaZona.actual.CO2 < 0) {
            printf("El nivel de CO2 debe ser un número mayor o igual a 0. Intente de nuevo.\n");
            limpiarBuffer(); // Limpiar el búfer
        }
    } while (nuevaZona.actual.CO2 < 0);

    do {
        printf("Ingrese el nivel de SO2 (ppm): ");
        if (scanf("%f", &nuevaZona.actual.SO2) != 1 || nuevaZona.actual.SO2 < 0) {
            printf("El nivel de SO2 debe ser un número mayor o igual a 0. Intente de nuevo.\n");
            limpiarBuffer(); // Limpiar el búfer
        }
    } while (nuevaZona.actual.SO2 < 0);

    do {
        printf("Ingrese el nivel de NO2 (ppm): ");
        if (scanf("%f", &nuevaZona.actual.NO2) != 1 || nuevaZona.actual.NO2 < 0) {
            printf("El nivel de NO2 debe ser un número mayor o igual a 0. Intente de nuevo.\n");
            limpiarBuffer(); // Limpiar el búfer
        }
    } while (nuevaZona.actual.NO2 < 0);

    do {
        printf("Ingrese el nivel de PM2.5 (µg/m3): ");
        if (scanf("%f", &nuevaZona.actual.PM2_5) != 1 || nuevaZona.actual.PM2_5 < 0) {
            printf("El nivel de PM2.5 debe ser un número mayor o igual a 0. Intente de nuevo.\n");
            limpiarBuffer(); // Limpiar el búfer
        }
    } while (nuevaZona.actual.PM2_5 < 0);

    printf("Ingrese la temperatura (°C): ");
    if (scanf("%f", &nuevaZona.clima.temperatura) != 1) {
        printf("Entrada inválida para la temperatura. Intente de nuevo.\n");
        limpiarBuffer(); // Limpiar el búfer
    }

    do {
        printf("Ingrese la velocidad del viento (m/s): ");
        if (scanf("%f", &nuevaZona.clima.velocidad_viento) != 1 || nuevaZona.clima.velocidad_viento < 0) {
            printf("La velocidad del viento debe ser un número mayor o igual a 0. Intente de nuevo.\n");
            limpiarBuffer(); // Limpiar el búfer
        }
    } while (nuevaZona.clima.velocidad_viento < 0);

    do {
        printf("Ingrese la humedad (%%): ");
        if (scanf("%f", &nuevaZona.clima.humedad) != 1 || nuevaZona.clima.humedad < 0) {
            printf("La humedad debe ser un número mayor o igual a 0. Intente de nuevo.\n");
            limpiarBuffer(); // Limpiar el búfer
        }
    } while (nuevaZona.clima.humedad < 0);

    // Escribir los datos en el archivo
    fprintf(f, "%s %.2f %.2f %.2f %.2f %.2f %.2f %.2f\n", 
            nuevaZona.nombre,
            nuevaZona.actual.CO2,
            nuevaZona.actual.SO2,
            nuevaZona.actual.NO2,
            nuevaZona.actual.PM2_5,
            nuevaZona.clima.temperatura,
            nuevaZona.clima.velocidad_viento,
            nuevaZona.clima.humedad);

    fclose(f);
    printf("Zona agregada correctamente al archivo.\n");
}

// Función para mostrar los datos de las zonas 
void mostrarZonas()
{
    FILE *f = fopen("zonas.txt", "r");
    if (f == NULL) {
        printf("Error: No se pudo abrir el archivo zonas.txt\n");
        return;
    }

    struct Zona zona;
    printf("Zonas registradas :\n");
    printf("---------------------------------------------------------------------------------------------\n");
    printf("| %-20s | %-6s | %-6s | %-6s | %-6s | %-11s | %-6s | %-7s | %-30s |\n", 
           "Nombre", "CO2", "SO2", "NO2", "PM2.5", "Temperatura", "Viento", "Humedad", "Advertencias");
    printf("---------------------------------------------------------------------------------------------\n");
    while (fscanf(f, "%s %f %f %f %f %f %f %f\n", 
                  zona.nombre, 
                  &zona.actual.CO2, 
                  &zona.actual.SO2, 
                  &zona.actual.NO2, 
                  &zona.actual.PM2_5, 
                  &zona.clima.temperatura, 
                  &zona.clima.velocidad_viento, 
                  &zona.clima.humedad) == 8) {
        printf("| %-20s | %-6.2f | %-6.2f | %-6.2f | %-6.2f | %-11.2f | %-6.2f | %-7.2f | ", 
               zona.nombre, 
               zona.actual.CO2, 
               zona.actual.SO2, 
               zona.actual.NO2, 
               zona.actual.PM2_5, 
               zona.clima.temperatura, 
               zona.clima.velocidad_viento, 
               zona.clima.humedad);

        int advertencias = 0;
        if (zona.actual.CO2 > LIMITE_CO2) {
            printf("CO2 alto ");
            advertencias++;
        }
        if (zona.actual.SO2 > LIMITE_SO2) {
            printf("SO2 alto ");
            advertencias++;
        }
        if (zona.actual.NO2 > LIMITE_NO2) {
            printf("NO2 alto ");
            advertencias++;
        }
        if (zona.actual.PM2_5 > LIMITE_PM25) {
            printf("PM2.5 alto ");
            advertencias++;
        }
        if (advertencias == 0) {
            printf("Ninguna");
        }
        printf(" |\n");
    }
    printf("---------------------------------------------------------------------------------------------\n");

    fclose(f);
}

// Función para generar un reporte de las zonas
void generarReporte() 
{
    FILE *f = fopen("reporteactual.txt", "r");  // Abrir archivo de zonas para lectura
    if (f == NULL) {
        printf("Error: No se pudo abrir el archivo zonas.txt\n");
        return;
    }

    FILE *reporte = fopen("reporte.txt", "w");  // Abrir archivo para escribir el reporte
    if (reporte == NULL) {
        printf("Error: No se pudo crear el reporte.txt\n");
        fclose(f);
        return;
    }

    struct Zona zona;
    fprintf(reporte, "Reporte de Contaminación del Aire\nFecha: %s\n\n", __DATE__);

    while (fscanf(f, "%s %f %f %f %f %f %f %f", 
                  zona.nombre, 
                  &zona.actual.CO2, 
                  &zona.actual.SO2, 
                  &zona.actual.NO2, 
                  &zona.actual.PM2_5, 
                  &zona.clima.temperatura, 
                  &zona.clima.velocidad_viento, 
                  &zona.clima.humedad) != EOF) {
        
        fprintf(reporte, "------------------------------------------------------------\n");
        fprintf(reporte, "Zona: %s\n", zona.nombre);
        fprintf(reporte, "------------------------------------------------------------\n");

        // Escribir los niveles de contaminación y compararlos con los límites
        fprintf(reporte, "- CO2: %.2f ppm (Limite: %.2f ppm) [%s]\n", zona.actual.CO2, LIMITE_CO2, zona.actual.CO2 > LIMITE_CO2 ? "Excede el límite" : "Dentro del límite");
        fprintf(reporte, "- SO2: %.2f ppm (Limite: %.2f ppm) [%s]\n", zona.actual.SO2, LIMITE_SO2, zona.actual.SO2 > LIMITE_SO2 ? "Excede el límite" : "Dentro del límite");
        fprintf(reporte, "- NO2: %.2f ppm (Limite: %.2f ppm) [%s]\n", zona.actual.NO2, LIMITE_NO2, zona.actual.NO2 > LIMITE_NO2 ? "Excede el límite" : "Dentro del límite");
        fprintf(reporte, "- PM2.5: %.2f µg/m3 (Limite: %.2f µg/m3) [%s]\n", zona.actual.PM2_5, LIMITE_PM25, zona.actual.PM2_5 > LIMITE_PM25 ? "Excede el límite" : "Dentro del límite");

        // Escribir las condiciones climáticas
        fprintf(reporte, "\nCondiciones climáticas:\n");
        fprintf(reporte, "- Temperatura: %.2f°C\n", zona.clima.temperatura);
        fprintf(reporte, "- Velocidad del viento: %.2f m/s\n", zona.clima.velocidad_viento);
        fprintf(reporte, "- Humedad: %.2f%%\n\n", zona.clima.humedad);
    }

    fclose(f);
    fclose(reporte);
    printf("Reporte generado correctamente en 'reporte.txt'.\n");
}

// Función para leer los datos históricos de las zonas
void promediohistorico() {
    FILE *f = fopen("historico.txt", "r");  // Abrir el archivo de datos históricos
    if (f == NULL) {
        printf("Error: No se pudo abrir el archivo zonas_historial.txt\n");
        return;
    }

    struct Zona zona;
    float totalCO2 = 0, totalSO2 = 0, totalNO2 = 0, totalPM25 = 0;
    int contadorZonas = 0;

    // Leer las líneas del archivo
    while (fscanf(f, "Zona%s %f %f %f %f %f %f %f\n", 
                  zona.nombre, 
                  &zona.actual.CO2, 
                  &zona.actual.SO2, 
                  &zona.actual.NO2, 
                  &zona.actual.PM2_5, 
                  &zona.clima.temperatura, 
                  &zona.clima.velocidad_viento, 
                  &zona.clima.humedad) == 8) {
        
        // Acumulamos los niveles de contaminantes
        totalCO2 += zona.actual.CO2;
        totalSO2 += zona.actual.SO2;
        totalNO2 += zona.actual.NO2;
        totalPM25 += zona.actual.PM2_5;
        contadorZonas++;
    }

    if (contadorZonas > 0) {
        // Calcular el promedio de los contaminantes
        float promedioCO2 = totalCO2 / contadorZonas;
        float promedioSO2 = totalSO2 / contadorZonas;
        float promedioNO2 = totalNO2 / contadorZonas;
        float promedioPM25 = totalPM25 / contadorZonas;

        printf("Promedio histórico de contaminantes:\n");
        printf("------------------------------------------------------------\n");
        printf("Promedio CO2: %.2f ppm\n", promedioCO2);
        printf("Promedio SO2: %.2f ppm\n", promedioSO2);
        printf("Promedio NO2: %.2f ppm\n", promedioNO2);
        printf("Promedio PM2.5: %.2f µg/m3\n", promedioPM25);

        // Comparar los promedios con los límites
        if (promedioCO2 > LIMITE_CO2) {
            printf("CO2: Excede el límite seguro de %.2f ppm.\n", LIMITE_CO2);
        } else {
            printf("CO2: Dentro del límite seguro de %.2f ppm.\n", LIMITE_CO2);
        }

        if (promedioSO2 > LIMITE_SO2) {
            printf("SO2: Excede el límite seguro de %.2f ppm.\n", LIMITE_SO2);
        } else {
            printf("SO2: Dentro del límite seguro de %.2f ppm.\n", LIMITE_SO2);
        }

        if (promedioNO2 > LIMITE_NO2) {
            printf("NO2: Excede el límite seguro de %.2f ppm.\n", LIMITE_NO2);
        } else {
            printf("NO2: Dentro del límite seguro de %.2f ppm.\n", LIMITE_NO2);
        }

        if (promedioPM25 > LIMITE_PM25) {
            printf("PM2.5: Excede el límite seguro de %.2f µg/m3.\n", LIMITE_PM25);
        } else {
            printf("PM2.5: Dentro del límite seguro de %.2f µg/m3.\n", LIMITE_PM25);
        }

    } else {
        printf("No se encontraron datos para calcular el promedio.\n");
    }
    fclose(f);
}

// Función para generar un reporte histórico de los promedios de contaminación
void generarReporteHistorico() {
    FILE *f = fopen("historico.txt", "r");  // Abrir archivo de datos históricos
    if (f == NULL) {
        printf("Error: No se pudo abrir el archivo historico.txt\n");
        return;
    }

    FILE *reporte = fopen("reporte_historico.txt", "w");  // Abrir archivo para escribir el reporte
    if (reporte == NULL) {
        printf("Error: No se pudo crear el reporte_historico.txt\n");
        fclose(f);
        return;
    }

    struct Zona zona;
    float acumuladoCO2 = 0, acumuladoSO2 = 0, acumuladoNO2 = 0, acumuladoPM25 = 0;
    float totalCO2, totalSO2, totalNO2, totalPM25;
    int contadorZonas = 0;

    fprintf(reporte, "Reporte Histórico de Promedios de Contaminación del Aire\nFecha: %s\n\n", __DATE__);

    // Iterar sobre cada zona en el archivo
    while (fscanf(f, "Zona%s %f %f %f %f %f %f %f\n", 
                  zona.nombre, 
                  &zona.actual.CO2, 
                  &zona.actual.SO2, 
                  &zona.actual.NO2, 
                  &zona.actual.PM2_5, 
                  &zona.clima.temperatura, 
                  &zona.clima.velocidad_viento, 
                  &zona.clima.humedad) == 8) {
        
        // Acumulamos los valores de cada contaminante para cada zona
        acumuladoCO2 += zona.actual.CO2;
        acumuladoSO2 += zona.actual.SO2;
        acumuladoNO2 += zona.actual.NO2;
        acumuladoPM25 += zona.actual.PM2_5;

        contadorZonas++;

        // Calcular el promedio histórico de contaminantes por zona
        totalCO2 = zona.actual.CO2;
        totalSO2 = zona.actual.SO2;
        totalNO2 = zona.actual.NO2;
        totalPM25 = zona.actual.PM2_5;
    }

    // Si hay zonas registradas, calcular el promedio histórico general
    if (contadorZonas > 0) {
        fprintf(reporte, "------------------------------------------------------------\n");
        fprintf(reporte, "Promedio histórico de todos los contaminantes:\n");
        fprintf(reporte, "------------------------------------------------------------\n");
        fprintf(reporte, "Promedio general CO2: %.2f ppm\n", acumuladoCO2 / contadorZonas);
        fprintf(reporte, "Promedio general SO2: %.2f ppm\n", acumuladoSO2 / contadorZonas);
        fprintf(reporte, "Promedio general NO2: %.2f ppm\n", acumuladoNO2 / contadorZonas);
        fprintf(reporte, "Promedio general PM2.5: %.2f µg/m3\n", acumuladoPM25 / contadorZonas);
    } else {
        fprintf(reporte, "No se encontraron datos para generar un reporte histórico.\n");
    }

    fclose(f);
    fclose(reporte);
    printf("Reporte histórico generado correctamente en 'reporte_historico.txt'.\n");
}

// Función para predecir el nivel de un contaminante en una zona
void prediccionContaminantesPromedio() {
    FILE *f = fopen("historico.txt", "r");  // Abrir archivo de datos históricos
    if (f == NULL) {
        printf("Error: No se pudo abrir el archivo historico.txt\n");
        return;
    }

    struct Zona zona;
    int contadorZonas = 0;

    // Recorrer todas las zonas en el archivo histórico
    while (fscanf(f, "Zona%s %f %f %f %f %f %f %f\n", 
                  zona.nombre, 
                  &zona.actual.CO2, 
                  &zona.actual.SO2, 
                  &zona.actual.NO2, 
                  &zona.actual.PM2_5, 
                  &zona.clima.temperatura, 
                  &zona.clima.velocidad_viento, 
                  &zona.clima.humedad) == 8) {

        // Arrays para almacenar los valores de contaminantes de los 30 días
        float X[30];  // Días (1, 2, ..., 30)
        float Y_CO2[30], Y_SO2[30], Y_NO2[30], Y_PM25[30];  // Valores para cada contaminante

        // Llenar los arrays con los datos de los contaminantes para los 30 días
        for (int i = 0; i < 30; i++) {
            X[i] = i + 1;
            Y_CO2[i] = zona.actual.CO2;
            Y_SO2[i] = zona.actual.SO2;
            Y_NO2[i] = zona.actual.NO2;
            Y_PM25[i] = zona.actual.PM2_5;

            // Leer los siguientes 29 días de datos para la misma zona
            if (i < 29) {
                fscanf(f, "Zona%s %f %f %f %f %f %f %f\n", 
                       zona.nombre, 
                       &zona.actual.CO2, 
                       &zona.actual.SO2, 
                       &zona.actual.NO2, 
                       &zona.actual.PM2_5, 
                       &zona.clima.temperatura, 
                       &zona.clima.velocidad_viento, 
                       &zona.clima.humedad);
            }
        }

        // Variables para la regresión lineal
        float sumaX = 0, sumaY_CO2 = 0, sumaY_SO2 = 0, sumaY_NO2 = 0, sumaY_PM25 = 0;
        float sumaXY_CO2 = 0, sumaXY_SO2 = 0, sumaXY_NO2 = 0, sumaXY_PM25 = 0;
        float sumaX2 = 0;
        int N = 30;

        // Calcular las sumas necesarias para la regresión
        for (int i = 0; i < 30; i++) {
            sumaX += X[i];
            sumaY_CO2 += Y_CO2[i];
            sumaY_SO2 += Y_SO2[i];
            sumaY_NO2 += Y_NO2[i];
            sumaY_PM25 += Y_PM25[i];
            sumaXY_CO2 += X[i] * Y_CO2[i];
            sumaXY_SO2 += X[i] * Y_SO2[i];
            sumaXY_NO2 += X[i] * Y_NO2[i];
            sumaXY_PM25 += X[i] * Y_PM25[i];
            sumaX2 += X[i] * X[i];
        }

        // Calcular la pendiente m y la intersección b para cada contaminante
        float m_CO2 = (N * sumaXY_CO2 - sumaX * sumaY_CO2) / (N * sumaX2 - sumaX * sumaX);
        float b_CO2 = (sumaY_CO2 - m_CO2 * sumaX) / N;

        float m_SO2 = (N * sumaXY_SO2 - sumaX * sumaY_SO2) / (N * sumaX2 - sumaX * sumaX);
        float b_SO2 = (sumaY_SO2 - m_SO2 * sumaX) / N;

        float m_NO2 = (N * sumaXY_NO2 - sumaX * sumaY_NO2) / (N * sumaX2 - sumaX * sumaX);
        float b_NO2 = (sumaY_NO2 - m_NO2 * sumaX) / N;

        float m_PM25 = (N * sumaXY_PM25 - sumaX * sumaY_PM25) / (N * sumaX2 - sumaX * sumaX);
        float b_PM25 = (sumaY_PM25 - m_PM25 * sumaX) / N;

        // Predicción para el siguiente día (día 31) con el promedio de los 30 días
        float prediccion_CO2 = m_CO2 * (30 + 1) + b_CO2;  // Día 31 para CO2
        float prediccion_SO2 = m_SO2 * (30 + 1) + b_SO2;  // Día 31 para SO2
        float prediccion_NO2 = m_NO2 * (30 + 1) + b_NO2;  // Día 31 para NO2
        float prediccion_PM25 = m_PM25 * (30 + 1) + b_PM25;  // Día 31 para PM2.5

        // Mostrar la predicción para cada contaminante en la zona
        printf("Zona %s - Predicción de contaminantes para el día 31:\n", zona.nombre);
        printf("CO2: %.2f ppm\n", prediccion_CO2);
        printf("SO2: %.2f ppm\n", prediccion_SO2);
        printf("NO2: %.2f ppm\n", prediccion_NO2);
        printf("PM2.5: %.2f µg/m3\n", prediccion_PM25);
        printf("\n");

        // Incrementar el contador de zonas
        contadorZonas++;
    }

    fclose(f);
}



// Función para leer el reporte de contaminación de un archivo
void leer_reporte(FILE *archivo) {
    FILE *reporte = fopen("recomendaciones.txt", "w");
    if (reporte == NULL) {
        printf("Error: No se pudo crear el reporteactual.txt\n");
        return;
    }

    char zona[50];
    float co2, so2, no2, pm25, temperatura, viento, humedad;

    fprintf(reporte, "------------------------------------------------------------\n");
    fprintf(reporte, "| %-20s | %-6s | %-6s | %-6s | %-6s | %-11s | %-6s | %-7s |\n", 
            "Zona", "CO2", "SO2", "NO2", "PM2.5", "Temperatura", "Viento", "Humedad");
    fprintf(reporte, "------------------------------------------------------------\n");

    while (fscanf(archivo, "%s %f %f %f %f %f %f %f", zona, &co2, &so2, &no2, &pm25, &temperatura, &viento, &humedad) != EOF) {
        fprintf(reporte, "| %-20s | %-6.2f | %-6.2f | %-6.2f | %-6.2f | %-11.2f | %-6.2f | %-7.2f |\n", 
                zona, co2, so2, no2, pm25, temperatura, viento, humedad);

        fprintf(reporte, "Recomendaciones:\n");
        if (so2 > 0.01) {
            fprintf(reporte, "- Se recomienda evitar actividades al aire libre debido a niveles elevados de SO2.\n");
            fprintf(reporte, "- Reducir el uso de combustibles fosiles y promover el uso de energias renovables.\n");
        }
        if (no2 > 0.10) {
            fprintf(reporte, "- Se recomienda usar mascarilla debido a los altos niveles de NO2.\n");
            fprintf(reporte, "- Implementar politicas para reducir las emisiones de vehiculos y promover el transporte publico.\n");
        }
        if (pm25 > 15.00) {
            fprintf(reporte, "- Evitar la exposicion prolongada al aire debido a la alta concentracion de PM2.5.\n");
            fprintf(reporte, "- Fomentar el uso de tecnologias de filtracion de aire en areas industriales y urbanas.\n");
        }
        if (co2 > 1000) {
            fprintf(reporte, "- Considerar la ventilacion del area debido a niveles elevados de CO2.\n");
            fprintf(reporte, "- Incrementar la vegetacion urbana y promover practicas de agricultura sostenible.\n");
        }

        fprintf(reporte, "------------------------------------------------------------\n");
    }

    fclose(reporte);
    printf("Reporte actual generado correctamente en 'reporteactual.txt'.\n");
}
