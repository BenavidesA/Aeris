#include <stdio.h>
#include <string.h>

#define Limite_CO2 1000
#define Limite_NO2 100
#define Limite_SO2 100
#define Limite_PM25s 25
#define NUM_CONTAMINANTES 4 // CO2, SO2, NO2, PM2.5

struct Zona
{
    char nombre[50];
    float niveles_actuales[NUM_CONTAMINANTES];         // Niveles actuales de contaminación
    float niveles_historicos[30][NUM_CONTAMINANTES];
     // Datos de los últimos 30 días
};

struct Clima
{
    float temperatura;
    float velocidad_viento;
    float humedad;
};

int menu();
void leerzonas(struct Zona *zonas, int num_zonas);
void monitorear_contaminacion(struct Zona *zonas, int num_zonas);
void calcular_promedios_historicos(struct Zona *zonas, int num_zonas);
void generar_recomendaciones(struct Zona *zonas, int num_zonas);
void predecir_niveles_futuros(struct Zona *zonas, int num_zonas);
void pedirDatosZona(struct Zona *zona, const char *nombre);
void leer_niveles_actuales(struct Zona *zonas, int num_zonas);
