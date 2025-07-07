#ifndef RESERVATIONCONTROLLER_H
#define RESERVATIONCONTROLLER_H

#include <string>
#include <vector>

class ReservationController {
public:
    std::string createReservation(const std::string& datetime, const std::string& clientName);
    bool deleteReservation(const std::string& key);
    bool searchReservation(const std::string& key);
    std::vector<std::string> getAllReservations();
    std::string getTreeStructure();
};

#endif
