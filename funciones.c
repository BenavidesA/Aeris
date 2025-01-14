#include "funciones.h"

int menu() {
    int opcion;
    printf("1. Ingresar datos\n");
    printf("2. Recomendaciones\n");
    printf("3. Alertas preventivas\n");
    printf("4. Promedio histórico\n");
    printf("5. Monitoreo futuro\n");
    printf("6. Monitoreo actual\n");
    printf("7. Salir\n");
    printf("Ingrese una opción: ");
    scanf("%d", &opcion);
    return opcion;
}

void save(int temperatura, int velocidaddelviento, int humedad, int presion) {
    FILE *file;
    file = fopen("data.dat", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fprintf(file, "Temperatura: %d\n", temperatura);
    fprintf(file, "Velocidad del viento: %d\n", velocidaddelviento);
    fprintf(file, "Humedad: %d\n", humedad);
    fprintf(file, "Presion: %d\n", presion);
    fclose(file);
}

void recomendaciones(int temperatura, int velocidaddelviento, int humedad, int presion) {
    FILE *file;
    file = fopen("data.dat", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    int temperaturafile, velocidaddelvientofile, humedadfile, presionfile;
    fscanf(file, "Temperatura: %d\n", &temperaturafile);
    fscanf(file, "Velocidad del viento: %d\n", &velocidaddelvientofile);
    fscanf(file, "Humedad: %d\n", &humedadfile);
    fscanf(file, "Presion: %d\n", &presionfile);
    fclose(file);
    
    if (temperatura > temperaturafile) {
        printf("La temperatura actual es mayor a la temperatura promedio\n");
    } else {
        printf("La temperatura actual es menor a la temperatura promedio\n");
    }
    if (velocidaddelviento > velocidaddelvientofile) {
        printf("La velocidad del viento actual es mayor a la velocidad del viento promedio\n");
    } else {
        printf("La velocidad del viento actual es menor a la velocidad del viento promedio\n");
    }
    if (humedad > humedadfile) {
        printf("La humedad actual es mayor a la humedad promedio\n");
    } else {
        printf("La humedad actual es menor a la humedad promedio\n");
    }
    if (presion > presionfile) {
        printf("La presion actual es mayor a la presion promedio\n");
    } else {
        printf("La presion actual es menor a la presion promedio\n");
    }

    // Sugerencias de mitigación
    if (temperatura > temperaturafile || velocidaddelviento > velocidaddelvientofile || humedad > humedadfile || presion > presionfile) {
        printf("Recomendaciones de mitigación:\n");
        printf("1. Reducción del tráfico vehicular.\n");
        printf("2. Cierre temporal de industrias.\n");
        printf("3. Suspensión de actividades al aire libre.\n");
    }
}

void alertaspreventivas(int temperatura, int velocidaddelviento, int humedad, int presion) {
    FILE *file;
    file = fopen("data.dat", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    int temperaturafile, velocidaddelvientofile, humedadfile, presionfile;
    fscanf(file, "Temperatura: %d\n", &temperaturafile);
    fscanf(file, "Velocidad del viento: %d\n", &velocidaddelvientofile);
    fscanf(file, "Humedad: %d\n", &humedadfile);
    fscanf(file, "Presion: %d\n", &presionfile);
    fclose(file);
    
    if (temperatura > temperaturafile) {
        printf("La temperatura actual es mayor a la temperatura promedio\n");
    } else {
        printf("La temperatura actual es menor a la temperatura promedio\n");
    }
    if (velocidaddelviento > velocidaddelvientofile) {
        printf("La velocidad del viento actual es mayor a la velocidad del viento promedio\n");
    } else {
        printf("La velocidad del viento actual es menor a la velocidad del viento promedio\n");
    }
    if (humedad > humedadfile) {
        printf("La humedad actual es mayor a la humedad promedio\n");
    } else {
        printf("La humedad actual es menor a la humedad promedio\n");
    }
    if (presion > presionfile) {
        printf("La presion actual es mayor a la presion promedio\n");
    } else {
        printf("La presion actual es menor a la presion promedio\n");
    }

    // Alertas preventivas
    if (temperatura > temperaturafile || velocidaddelviento > velocidaddelvientofile || humedad > humedadfile || presion > presionfile) {
        printf("Alertas preventivas:\n");
        printf("1. Uso de mascarillas.\n");
        printf("2. Evitar actividades al aire libre.\n");
        printf("3. Cierre de ventanas.\n");
    }
}

int promediohistorico(int temperatura, int velocidaddelviento, int humedad, int presion) {
    FILE *file;
    file = fopen("data.dat", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 0;
    }
    int temperaturafile, velocidaddelvientofile, humedadfile, presionfile;
    fscanf(file, "Temperatura: %d\n", &temperaturafile);
    fscanf(file, "Velocidad del viento: %d\n", &velocidaddelvientofile);
    fscanf(file, "Humedad: %d\n", &humedadfile);
    fscanf(file, "Presion: %d\n", &presionfile);
    fclose(file);
    
    return (temperaturafile + velocidaddelvientofile + humedadfile + presionfile) / 4;
}

int monitoreofuturo(int temperatura, int velocidaddelviento, int humedad, int presion) {
    int promedio = promediohistorico(temperatura, velocidaddelviento, humedad, presion);
    printf("El promedio histórico es: %d\n", promedio);
    return promedio;
}

int monitoreoactual(int temperatura, int velocidaddelviento, int humedad, int presion) {
    int promedio = promediohistorico(temperatura, velocidaddelviento, humedad, presion);
    printf("El promedio histórico es: %d\n", promedio);
    return promedio;
}


//arreglos, estructuras, punteros funciones y archivos
//uso de algoritmos de prediccion simples como promedio ponderado de los utimos dias de contaminacion  con mas peso en dias recientes
//persistencia de datos
//evitar usar librerias externs para el uso de archivos o calculos avanzados