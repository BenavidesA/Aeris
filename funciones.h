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
    float niveles_actuales[NUM_CONTAMINANTES];       
    float niveles_historicos[30][NUM_CONTAMINANTES];
    struct Clima clima[30];
};

struct Clima
{
    float temperatura;
    float velocidad_viento;
    float humedad;
};

