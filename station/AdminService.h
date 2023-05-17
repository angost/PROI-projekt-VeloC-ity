//
// Created by Adrian Murawski on 17/05/2023.
//

#ifndef PROI_PROJEKT_ADMINSERVICE_H
#define PROI_PROJEKT_ADMINSERVICE_H

#include "Service.h"


class AdminService : public Service {
public:
    AdminService(string identifier, vector < Station* > stations);
    void assignStation(Station station, Service serviceCrew);
};


#endif //PROI_PROJEKT_ADMINSERVICE_H
