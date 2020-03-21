//
// Created by Octavian Custura on 18/03/2020.
//
//
#ifndef ASSIGNMENT_5_6_REPOSITORY_H
#define ASSIGNMENT_5_6_REPOSITORY_H
//
//
#include "DynamicArray.h"
#include "Footage.h"
//
class Repository {
private:
    DynamicArray<Footage> arrayOfTapes;
public:
    Repository();

    [[nodiscard]] int getSize() const;

    void addFootage(const Footage& newFootage);

    void deleteFootage(const std::string& titleToBeRemoved);

    void updateFootage(const Footage& newFootage);

    DynamicArray<Footage> getAllFootage();

};


#endif //ASSIGNMENT_5_6_REPOSITORY_H
