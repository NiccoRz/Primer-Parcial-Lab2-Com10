#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int dni;
    char nombre_apellido[30];
    int edad;
    char equipo[30];
} player;

typedef struct
{
    player p;
    struct nodoPlayer * siguiente;
} nodoPlayer;


nodoPlayer * agregarPrincipio(nodoPlayer * lista,nodoPlayer * nuevo);
nodoPlayer * arrayTolista(nodoPlayer * lista, player A[], int val);
nodoPlayer * inicLista();
nodoPlayer * crearNodo(player A);
nodoPlayer * listaToLista(nodoPlayer * listaVieja, nodoPlayer * listaNueva, char equipo[]);

int main()
{
    player A[100];
    int val = loadPlayers(A);
    //mostrarArrayRec(A,val,0);

    nodoPlayer * lista = inicLista();

    lista = arrayTolista(lista,A,val);
    printf("\nLista de Jugadores:\n");
    mostrarLista(lista);

    //printf("\nMayores de 25 años:\n");
    //mostrarMayoresRec(lista);

    int dniMayor = busquedaMayorEdad(lista);
    printf("\n\nEl DNI del jugador con mas edad es: %d",dniMayor);

    nodoPlayer * listaNueva = inicLista();
    char equip[30];
    printf("\n\nIngrese equipo a buscar: ");
    fflush(stdin);
    gets(equip);
    listaNueva = listaToLista(lista,listaNueva,equip);
    if(listaNueva==NULL)
        printf("No se encuentran jugadores del equipo en este archivo...");
    else
    {
        printf("\n\nLista Nueva:\n");
        mostrarLista(listaNueva);
    }

    return 0;
}

nodoPlayer * inicLista()
{
    return NULL;
}

int loadPlayers(player A[])
{
    int i=0;

    A[i].dni=1234;
    A[i].edad=23;
    strcpy(A[i].nombre_apellido,"JuanFer Quintero");
    strcpy(A[i].equipo,"River Plate");
    i++;

    A[i].dni=9876;
    A[i].edad=33;
    strcpy(A[i].nombre_apellido,"Nacho Scocco");
    strcpy(A[i].equipo,"River Plate");
    i++;

    A[i].dni=2341;
    A[i].edad=28;
    strcpy(A[i].nombre_apellido,"Pity Martinez");
    strcpy(A[i].equipo,"River Plate");
    i++;

    A[i].dni=9999;
    A[i].edad=45;
    strcpy(A[i].nombre_apellido,"Juan Roman Riquelme");
    strcpy(A[i].equipo,"Boca Juniors");
    i++;

    A[i].dni=1213;
    A[i].edad=50;
    strcpy(A[i].nombre_apellido,"Guillermo Barros Schelotto");
    strcpy(A[i].equipo,"Gimnasia de La Plata");
    i++;

    A[i].dni=1927;
    A[i].edad=48;
    strcpy(A[i].nombre_apellido,"Marcelo Gallardo");
    strcpy(A[i].equipo,"River Plate");
    i++;

    A[i].dni=8362;
    A[i].edad=28;
    strcpy(A[i].nombre_apellido,"Franco Armani");
    strcpy(A[i].equipo,"River Plate");
    i++;

    A[i].dni=2415;
    A[i].edad=23;
    strcpy(A[i].nombre_apellido,"Cristian Pavon");
    strcpy(A[i].equipo,"Boca Juniors");
    i++;

    A[i].dni=9642;
    A[i].edad=36;
    strcpy(A[i].nombre_apellido,"Fernando Gago");
    strcpy(A[i].equipo,"Boca Juniors");
    i++;

    A[i].dni=9642;
    A[i].edad=46;
    strcpy(A[i].nombre_apellido,"Carlitos Tevez");
    strcpy(A[i].equipo,"Boca Juniors");
    i++;

    A[i].dni=2643;
    A[i].edad=34;
    strcpy(A[i].nombre_apellido,"Ariel Rojas");
    strcpy(A[i].equipo,"San Lorenzo");
    i++;

    A[i].dni=2647;
    A[i].edad=30;
    strcpy(A[i].nombre_apellido,"Sebastian Torrico");
    strcpy(A[i].equipo,"San Lorenzo");
    i++;

    A[i].dni=3426;
    A[i].edad=26;
    strcpy(A[i].nombre_apellido,"Maximiliano Meza");
    strcpy(A[i].equipo,"Independiente");
    i++;

    A[i].dni=3827;
    A[i].edad=36;
    strcpy(A[i].nombre_apellido,"Martin Campania");
    strcpy(A[i].equipo,"Independiente");
    i++;

    A[i].dni=1673;
    A[i].edad=20;
    strcpy(A[i].nombre_apellido,"Emmanuel Gigliotti");
    strcpy(A[i].equipo,"Chongqing Lifan");
    i++;

    return i;
}


///1) Hacer una función que muestre un arreglo de “players” en forma recursiva, desde el inicio hasta el final del arreglo. Modularizar.

void mostrarArrayRec(player A[], int dim, int i)
{
    if(i<dim)
    {
        mostrarArrayRec(A,dim,i+1);
        mostrarUno(A[i]);
    }
}

void mostrarUno(player A)
{
    printf("\n--------------------------------------------------\n");
    printf("- DNI:               %d\n",A.dni);
    printf("- Nombre y Apellido: %s\n",A.nombre_apellido);
    printf("- Edad:              %d\n",A.edad);
    printf("- Equipo:            %s",A.equipo);
    printf("\n--------------------------------------------------\n");
}

///2) Hacer una función que cree un nodoPlayer, cargue sus datos y retorne un puntero al mismo. Piense que parámetro/s convendría que reciba esta función.

nodoPlayer * crearNodo(player A)
{
    nodoPlayer * nuevo = (nodoPlayer*)malloc(sizeof(nodoPlayer));
    nuevo->p = A;
    nuevo->siguiente = NULL;
    return nuevo;
}

///3) Hacer una función que inserte un nuevo nodo a la lista, manteniendo el orden creciente por “dni”. Esta función debe recibir un puntero doble a la lista y el nuevo nodo a insertar, utilizar el siguiente prototipado: void insertInOrder (nodoPlayer * * lista, nodoPlayer * nuevo)

void agregarEnOrden(nodoPlayer ** lista, nodoPlayer * nuevo)
{
    if((*lista)==NULL)
        (*lista) = nuevo;
    else
    {
        if((*lista)->p.dni > nuevo->p.dni)
            (*lista) = agregarPrincipio((*lista),nuevo);
        else
        {
            nodoPlayer * seg = (*lista);
            nodoPlayer * ante;
            while(seg!=NULL && seg->p.dni < nuevo->p.dni)
            {
                ante = seg;
                seg = seg->siguiente;
            }
            ante->siguiente = nuevo;
            nuevo->siguiente = seg;
        }
    }
}

nodoPlayer * agregarPrincipio(nodoPlayer * lista,nodoPlayer * nuevo)
{
    if(lista==NULL)
        lista = nuevo;
    else
    {
        nuevo->siguiente = lista;
        lista = nuevo;
    }
    return lista;
}

///4) Hacer una función que pase los “players” del arreglo que ya está cargado a una lista, invocando las funciones de los incisos 2 y 3. O sea, debe recorrer el arreglo, crear los nodos y agregarlos en orden a la lista. La función recibe el arreglo cargado, la lista vacía y retorna la lista cargada

nodoPlayer * arrayTolista(nodoPlayer * lista, player A[], int val)
{
    nodoPlayer * nuevo;
    for(int i=0; i<val; i++)
    {
        nuevo = crearNodo(A[i]);
        agregarEnOrden(&lista,nuevo);
    }
    return lista;
}

void mostrarLista(nodoPlayer * lista)
{
    nodoPlayer * seg = lista;
    if(seg!=NULL)
    {
        while(seg!=NULL)
        {
            mostrarUno(seg->p);
            seg=seg->siguiente;
        }
    }
}

///5) Hacer una función que muestre los “players” mayores a 25 años de una lista en forma recursiva, pero de forma invertida (del último al primero). Modularizar.

void mostrarMayoresRec(nodoPlayer * lista)
{
    if(lista!=NULL)
    {
        mostrarMayoresRec(lista->siguiente);
        if(lista->p.edad > 25)
            mostrarUno(lista->p);
    }
}


///6) Hacer una función que busque al player de mayor edad en la lista y retorna el dni del mismo. Puede ser iterativa o recursiva.

int busquedaMayorEdad(nodoPlayer * lista)
{
    nodoPlayer * aux = NULL;
    nodoPlayer * seg = lista;
    if(seg!=NULL)
    {
        aux = seg;
        while(seg!=NULL)
        {
            if(aux->p.edad < seg->p.edad)
                aux = seg;
            seg = seg->siguiente;
        }
    }
    return aux->p.dni;
}

///7) Hacer una función que pase los “players” de la lista que se encuentra cargada a una nueva lista, pasando únicamente los de un determinado equipo (dato que se recibe por parámetro). Al encontrar un player que cumpla con la condición, crear un nuevo nodo a partir de sus datos e insertarlo en la nueva lista (utilice las funciones 2 y 3). nodoPlayer * pasarDeListaToLista (nodoPlayer * listaVieja, nodoPlayer * listaNueva, char equipo [ ])

nodoPlayer * listaToLista(nodoPlayer * listaVieja, nodoPlayer * listaNueva, char equipo[])
{
    nodoPlayer * seg = listaVieja;
    nodoPlayer * nuevo;
    while(seg!=NULL)
    {
        if(strcmpi(seg->p.equipo,equipo)==0)
        {
            nuevo = crearNodo(seg->p);
            agregarEnOrden(&listaNueva,nuevo);
        }
        seg = seg->siguiente;
    }
    return listaNueva;
}
