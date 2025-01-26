#include <stdio.h>
#include <string.h>

#define LIMITE_CO2 1000.0    // Nivel de CO2 en ppm (en interiores)
#define LIMITE_NO2 0.1       // Nivel de NO2 en ppm (1 hora)
#define LIMITE_SO2 0.0076    // Nivel de SO2 en ppm (24 horas)
#define LIMITE_PM25 15.0     // Nivel de PM2.5 en µg/m³ (24 horas)
#define NUM_CONTAMINANTES 4 // CO2, SO2, NO2, PM2.5;

// Datos climáticos
struct Clima
{
    float temperatura;
    float velocidad_viento;
    float humedad;
};

// Niveles de contaminación para una zona específica
struct NivelesContaminacion {
    float CO2;    // Nivel de CO2 (ppm)
    float SO2;    // Nivel de SO2 (ppm)
    float NO2;    // Nivel de NO2 (ppm)
    float PM2_5;  // Nivel de PM2.5 (µg/m3)
};

// Datos de una zona urbana
struct Zona {
    char nombre[50];                        // Nombre de la zona
    struct NivelesContaminacion actual;
    struct Clima clima;

};

void menu(); 
void agregarZona();
void mostrarZonas();
void promediohistorico();
void limpiarBuffer();
void prediccionContaminantesPromedio();
void leer_reporte(FILE *archivo);






