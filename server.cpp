#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <numeric>
#include "mpi.h"

using namespace std;

int main(int argc, char **argv){
    int l_recieved;
    int l_gamble1;
    int l_gamble2;
    bool f_game_over;

    MPI_Init(&argc, &argv);
    char l_port_name[MPI_MAX_PORT_NAME];
    MPI_Status l_status;
    MPI_Comm intercomm;
    MPI_Open_port(MPI_INFO_NULL, l_port_name);

    cout << "server started" << endl;
    printf("portname: %s\n", l_port_name);
    MPI_Comm_accept(l_port_name, MPI_INFO_NULL, 0, MPI_COMM_SELF, &intercomm);

    l_gamble1 = 20;

    for(;;) {
            cout << "Камней у машины: " << l_gamble1 <<  endl;
            srand(unsigned(time(nullptr)));
            l_gamle2 = (rand() % l_gamble1) + 1;

            MPI_Send(&l_gamle2, 1, MPI_INT, 0, 0, intercomm);
            MPI_Recv(&l_recieved, 1, MPI_INT, 0, 0, intercomm, &l_status);

            if (l_recieved < 0)
                cout << "Машина теряет камни:" << - l_recieved << endl;
            else
                cout << "Машина получает камни:" << l_recieved << endl;

            l_gamble1 += l_recieved;
            f_game_over = false;

        switch (l_gamble1) {
            case 0:
                cout << "Победил игрок" << endl;
                f_game_over = true;
                break;
            case 40:
                cout << "Победила машина" << endl;
                f_game_over = true;
                break;
        }

        if (f_game_over) break;

    }
    MPI_Comm_free(&intercomm);
    MPI_Close_port(l_port_name);

    MPI_Finalize();
    return 0;
}
