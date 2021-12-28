//
// Created by Maxim Maximovsky on 28.12.2021.
//
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include "mpi.h"

using namespace std;

int main(int argc, char **argv){

    int l_bf;
    int l_indic;
    int l_bet;
    int l_min;
    int l_rank;
    int l_rem;
    bool f_game_over;

    l_bf = 20;

    MPI_Init(&argc, &argv);
    char port_name[MPI_MAX_PORT_NAME];
    MPI_Comm intercomm;
    MPI_Status status;
    strcpy(port_name, argv[1]);
    MPI_Comm_connect(port_name, MPI_INFO_NULL, 0, MPI_COMM_SELF, &intercomm);
    MPI_Comm_rank(MPI_COMM_WORLD, &l_rank);


    for(;;) {
        cout << "У вас камней:" << l_bf << endl;
        cout << "Введи: 0 - чётное, 1 - нечётное." << endl;
        cin >> l_indic;
        cout << "Загадай число" << endl;
        cin >> l_bet;

        MPI_Recv(&l_rem, 1, MPI_INT, 0, 0, intercomm, &status);

        if (l_indic == (l_rem % 2)) {
            cout << "Вы выигываете камней: " << min(l_bet, l_rem) << endl;
            l_bf += min(l_bet, l_rem);
            l_min =  - min(l_bet, l_rem);
            MPI_Send(&l_min, 1, MPI_INT, 0, 0, intercomm);
        }
        else {
            cout << "Ты теряешь камней: " << min(l_bet, l_rem) << endl;
            l_bf -= min(l_bet, l_rem);
            l_min = min(l_bet, l_rem);
            MPI_Send(&l_min, 1, MPI_INT, 0, 0, intercomm);
        }

        f_game_over = false;

        switch (l_bf) {
            case 40: cout << "Ты выиграл" << endl;
                f_game_over = true;
                break;
            case 0:  cout << "Тебе конец!" << endl;
                f_game_over = true;
                break;
        }

        if (f_game_over) break;

    }
    MPI_Finalize();
    return 0;
}

