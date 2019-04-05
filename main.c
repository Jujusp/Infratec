// ISIS-1304 - FUNDAMENTOS DE INFRAESTRUCTURA TECNOLOGICA - PROYECTO 1 - 201910
// EL GRUPO DEBE SER DESARROLLADO EN GRUPOS DE A 3 PERSONAS MAXIMO
//
// DESARROLLADO POR:
// Nombre - Código
// Nombre - Código
// Nombre - Código

#define _CRT_SECURE_NO_DEPRECATE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// La representacion de la imagen
typedef struct img
{
    int ancho;
    int alto;
    unsigned char *informacion;
} Imagen;


// Función que carga el bmp en la estructura Imagen
void cargarBMP24(Imagen * imagen, char * nomArchivoEntrada);

// Función que guarda el contenido de la estructura imagen en un archivo binario
void guardarBMP24(Imagen * imagen, char * nomArchivoSalida);

//Función que inserta un mensaje en la imagen usando n bits por Byte
void insertarMensaje(Imagen * img, unsigned char mensaje[], int n);

//Función que lee un mensaje de una imagen dando la longitud del mensaje y el numero de bits por byte usados
void leerMensaje(Imagen * img, unsigned char msg[], int l, int n);

//Función que saca n bits de una secuencia de caracteres a partir de una posición dada
unsigned char sacarNbits(unsigned char secuencia[], int bitpos, int n);

unsigned char salvarNBits(int n);
unsigned char matarNBits(int n);


// Programa principal
// NO MODIFICAR
int main(int argc, char* argv[]) {

    Imagen *img = (Imagen *)malloc(sizeof(Imagen));
    char msg[10000];
    int op, num, l, i, n;
    char nomArch[256];

    printf("ISIS-1304 - FUNDAMENTOS DE INFRAESTRUCTURA TECNOLOGICA - PROYECTO 1\n");
    printf("Indique la accion a realizar:\n\t1) Insertar mensaje\n\t2) Leer mensaje\n\n");
    printf("Opcion: ");
    scanf("%d", &op);

    printf("Ingrese el nombre/ruta de la imagen (incluya el formato .bmp): ");

    char temp;
    scanf("%c", &temp);
    gets(nomArch);

    // Cargar los datos
    cargarBMP24(img, nomArch);

    if (op == 1) {
        printf("Ingrese el mensaje a insertar:\n\n");

        gets(msg);

        printf("\nLongitud mensaje: %d bytes\n", strlen(msg));
        msg[strlen(msg)] = '\0';

        printf("Ingrese el numero de bits por Byte: ");
        scanf("%d", &num);

        printf("Insertando . . .\n");
        insertarMensaje(img, msg, num);
        printf("Insertado correctamente !\n");

        char nuevo[256];
        printf("Ingrese el nombre del archivo a guardar (incluya el formato .bmp): ");

        scanf("%c", &temp);
        gets(nuevo);

        guardarBMP24(img, nuevo);

        printf("Mensaje insertado y guardado exitosamente en el archivo/ruta '%s' ! :D\n\n", nuevo);
    }
    else if (op == 2) {
        printf("Ingrese la longitud a leer del mensaje insertado: ");

        scanf("%d", &l);

        printf("Ingrese el numero de bits por Byte: ");
        scanf("%d", &n);

        for (i = 0; i < l; i++) {
            msg[i] = 0;
        }

        leerMensaje(img, msg, l, n);

        msg[l] = 0;

        printf("Mensaje obtenido exitosamente ! El mensaje es:\n\n%s\n\n", msg);
    }
    else {
        printf("La opcion ingresada (%d) no es correcta\n", op);
        system("pause");
        return -1;
    }
    system("pause");
    return 0;
}

/**
* Inserta un mensaje, de a n bits por componente de color, en la imagen apuntada por img
* parámetro img: Apuntador a una imagen en cuyos pixeles se almacenará el mensaje.
* parámetro mensaje: Apuntador a una cadena de caracteres con el mensaje.
* parámetro n: Cantidad de bits del mensaje que se almacenarán en cada componente de color de cada pixel. 0 < n <= 8.
*/
void insertarMensaje(Imagen * img, unsigned char mensaje[], int n) {
    // TODO: Desarrollar OBLIGATORIAMENTE en su totalidad.


    //Tomamos el mensaje a encriptar y le sacamos el length
    //Multiplicamos el length por (tamaño en bytes un elemento del mensaje*8) <-- seria en bits practicamente.
    int bits = strlen(mensaje)*(sizeof mensaje[1])*8;

    //Este short es el que nos indicara en cuantos bits 'partidos' o sacados vamos de los bits del mensaje a encriptar.
    short bitsSacados =0;

    //Bueno tengo la sensacion que aquí hay ciclo infinito
    int i =0;
	while(bits>0)
	{
	//El la primera parte lo que hacemos es crear la máscara y la aplicamos sobre la información de la img para poder dejar los bits
	//más significativos protegidos y los bits a asignar en ceros para poder insertarlos
	//Luego, para la parte antes de la disyunción creamos el byte que contiene los pedazos de n bits del mensaje.
	//Finalmente generamos la disyunción entre el byte de la imagen y el byte que contiene n bits de la imagen, al generar
	//La disyunción nos genera el byte con la información insertada.

	    char byteAMeter = (salvarNBits(8-n) & img->informacion[i]) | sacarNbits(mensaje,bitsSacados,n);
	    img->informacion[i++] = byteAMeter;
		bits-=n;
		bitsSacados+=n;

	}
	
}

/**
* Extrae un mensaje de tamanio l, guardado de a n bits por componente de color, de la imagen apuntada por img
* parámetro img: Apuntador a una imagen que tiene almacenado el mensaje en sus pixeles.
* parámetro msg: Apuntador a una cadena de caracteres donde se depositará el mensaje.
* parámetro l: Tamanio en bytes del mensaje almacenado en la imagen.
* parámetro n: Cantidad de bits del mensaje que se almacenan en cada componente de color de cada pixel. 0 < n <= 8.
*/
void leerMensaje(Imagen * img, unsigned char msg[], int l, int n) {
    // TODO: Desarrollar OBLIGATORIAMENTE en su totalidad.
}
unsigned char salvarNBits(int n)
{
    int i;
	unsigned char mask =0;
        for (int i = 0; i < n; i++) {
            //Le sumamos a la máscara 1
            mask++;
            //Hacemos corrimiento de 1 bit a izquierda
            mask <<= 1;
        }

        //No existe k como tal pero me imagino que es completarByte
        int completarByte = 8 - n - 1;
        if (completarByte > 0)
            mask <<= completarByte;
        else
            mask++;
        return mask;
}


unsigned char matarNBits(int n)
{

    unsigned char mask =0;
    for(int i=0; i<n;i++)
    {
        //Le sumamos a la máscara 1
        mask++;
        //Hacemos corrimiento de 1 bit a izquierda
        mask <<=1;
    }
    mask++;
    return mask;
}
/**
* Extrae n bits a partir del bit que se encuentra en la posición bitpos en la secuencia de bytes que
* se pasan como parámetro
* parámetro secuencia: Apuntador a una secuencia de bytes.
* parámetro n: Cantidad de bits que se desea extraer. 0 < n <= 8.
* parámetro bitpos: Posición del bit desde donde se extraerán los bits. 0 <= n < 8*longitud de la secuencia
* retorno: Los n bits solicitados almacenados en los bits menos significativos de un unsigned char
*/
unsigned char sacarNbits(unsigned char secuencia[], int bitpos, int n) {
    // DESARROLLO OPCIONAL: Puede ser útil para el desarrollo de los procedimientos obligatorios.
	char a = secuencia[bitpos/8];

	if(bitpos%8>8-n) {
        //La idea para continuar acá es tomar los bits faltantes de la siguiente parte del arreglo
        //Hablamos antes sobre limpiar el siguiente del arreglo dejando los bits que necesitamos y con un or al otro y sirve
        char b = secuencia[(bitpos + 8) / 8];
        printf("B sin modificar  \n");
        int i;
        for (i = 0; i < 8; i++) {
            printf("%d", !!((b << i) & 0x80));
        }
        printf("\n");


        b = b >> 8 - ((bitpos % 8) + n) % 8;
        i=0;
        printf("B modificado  \n");
        for (i = 0; i < 8; i++) {
            printf("%d", !!((b << i) & 0x80));
        }
        printf("\n");


        printf("A sin modificar  \n");
        i=0;
        for (i = 0; i < 8; i++) {
            printf("%d", !!((a << i) & 0x80));
        }
        printf("\n");

        a= (a<<(bitpos%8))>>((8-n)+2);

        //a = (a & (salvarNBits(8-(bitpos%8)) >>8-(bitpos%8)));


        printf("A modificado \n");
        i=0;
        for (i = 0; i < 8; i++) {
            printf("%d", !!((a << i) & 0x80));
        }
        printf("\n");


        char c=a|b;
        printf("disyuncion \n");
        for (i = 0; i < 8; i++) {
            printf("%d", !!((c << i) & 0x80));
        }
        printf("\n");

		return a | b;

	}
//Primera respuesta del ternario funciona para 0<n<6
	return (bitpos%8==0)? a>>8-n:(a<<(bitpos%8)-1)>>8-n;

}

// Lee un archivo en formato BMP y lo almacena en la estructura img
// NO MODIFICAR
void cargarBMP24(Imagen * imagen, char * nomArchivoEntrada) {
    // bmpDataOffset almacena la posición inicial de los datos de la imagen. Las otras almacenan el alto y el ancho
    // en pixeles respectivamente
    int bmpDataOffset, bmpHeight, bmpWidth;
    int y;
    int x;
    int	residuo;

    FILE *bitmapFile;
    bitmapFile = fopen(nomArchivoEntrada, "rb");
    if (bitmapFile == NULL) {
        printf("No ha sido posible cargar el archivo: %s\n", nomArchivoEntrada);
        exit(-1);
    }

    fseek(bitmapFile, 10, SEEK_SET); // 10 es la posición del campo "Bitmap Data Offset" del bmp	
    fread(&bmpDataOffset, sizeof(int), 1, bitmapFile);

    fseek(bitmapFile, 18, SEEK_SET); // 18 es la posición del campo "height" del bmp
    fread(&bmpWidth, sizeof(int), 1, bitmapFile);
    bmpWidth = bmpWidth * 3;

    fseek(bitmapFile, 22, SEEK_SET); // 22 es la posición del campo "width" del bmp
    fread(&bmpHeight, sizeof(int), 1, bitmapFile);

    residuo = (4 - (bmpWidth) % 4) & 3; // Se debe calcular los bits residuales del bmp, que surjen al almacenar en palabras de 32 bits

    imagen->ancho = bmpWidth;
    imagen->alto = bmpHeight;
    imagen->informacion = (unsigned char *)calloc(bmpWidth * bmpHeight, sizeof(unsigned char));

    fseek(bitmapFile, bmpDataOffset, SEEK_SET); // Se ubica el puntero del archivo al comienzo de los datos

    for (y = 0; y < bmpHeight; y++) {
        for (x = 0; x < bmpWidth; x++) {
            int pos = y * bmpWidth + x;
            fread(&imagen->informacion[pos], sizeof(unsigned char), 1, bitmapFile);
        }
        fseek(bitmapFile, residuo, SEEK_CUR); // Se omite el residuo en los datos
    }
    fclose(bitmapFile);
}

// Esta función se encarga de guardar una estructura de Imagen con formato de 24 bits (formato destino) en un archivo binario
// con formato BMP de Windows.
// NO MODIFICAR
void guardarBMP24(Imagen * imagen, char * nomArchivoSalida) {
    unsigned char bfType[2];
    unsigned int bfSize, bfReserved, bfOffBits, biSize, biWidth, biHeight, biCompression, biSizeImage, biXPelsPerMeter, biYPelsPerMeter, biClrUsed, biClrImportant;
    unsigned short biPlanes, biBitCount;
    FILE * archivoSalida;
    int y, x;
    int relleno = 0;

    int residuo = (4 - (imagen->ancho) % 4) & 3; // Se debe calcular los bits residuales del bmp, que quedan al forzar en palabras de 32 bits


    bfType[2];       // Tipo de Bitmap
    bfType[0] = 'B';
    bfType[1] = 'M';
    bfSize = 54 + imagen->alto * ((imagen->ancho) / 3) * sizeof(unsigned char);       // Tamanio total del archivo en bytes
    bfReserved = 0;   // Reservado para uso no especificados
    bfOffBits = 54;    // Tamanio total del encabezado
    biSize = 40;      // Tamanio del encabezado de informacion del bitmap	
    biWidth = (imagen->ancho) / 3;     // Ancho en pixeles del bitmap	
    biHeight = imagen->alto;    // Alto en pixeles del bitmap	
    biPlanes = 1;    // Numero de planos	
    biBitCount = 24;  // Bits por pixel (1,4,8,16,24 or 32)	
    biCompression = 0;   // Tipo de compresion
    biSizeImage = imagen->alto * imagen->ancho;   // Tamanio de la imagen (sin ecabezado) en bits
    biXPelsPerMeter = 2835; // Resolucion del display objetivo en coordenada x
    biYPelsPerMeter = 2835; // Resolucion del display objetivo en coordenada y
    biClrUsed = 0;       // Numero de colores usados (solo para bitmaps con paleta)	
    biClrImportant = 0;  // Numero de colores importantes (solo para bitmaps con paleta)	

    archivoSalida = fopen(nomArchivoSalida, "w+b"); // Archivo donde se va a escribir el bitmap
    if (archivoSalida == 0) {
        printf("No ha sido posible crear el archivo: %s\n", nomArchivoSalida);
        exit(-1);
    }

    fwrite(bfType, sizeof(char), 2, archivoSalida); // Se debe escribir todo el encabezado en el archivo. En total 54 bytes.
    fwrite(&bfSize, sizeof(int), 1, archivoSalida);
    fwrite(&bfReserved, sizeof(int), 1, archivoSalida);
    fwrite(&bfOffBits, sizeof(int), 1, archivoSalida);
    fwrite(&biSize, sizeof(int), 1, archivoSalida);
    fwrite(&biWidth, sizeof(int), 1, archivoSalida);
    fwrite(&biHeight, sizeof(int), 1, archivoSalida);
    fwrite(&biPlanes, sizeof(short), 1, archivoSalida);
    fwrite(&biBitCount, sizeof(short), 1, archivoSalida);
    fwrite(&biCompression, sizeof(int), 1, archivoSalida);
    fwrite(&biSizeImage, sizeof(int), 1, archivoSalida);
    fwrite(&biXPelsPerMeter, sizeof(int), 1, archivoSalida);
    fwrite(&biYPelsPerMeter, sizeof(int), 1, archivoSalida);
    fwrite(&biClrUsed, sizeof(int), 1, archivoSalida);
    fwrite(&biClrImportant, sizeof(int), 1, archivoSalida);

    // Se escriben en el archivo los datos RGB de la imagen.
    for (y = 0; y < imagen->alto; y++) {
        for (x = 0; x < imagen->ancho; x++) {
            int pos = y * imagen->ancho + x;
            fwrite(&imagen->informacion[pos], sizeof(unsigned char), 1, archivoSalida);
        }
        fwrite(&relleno, sizeof(unsigned char), residuo, archivoSalida);
    }
    fclose(archivoSalida);
}
