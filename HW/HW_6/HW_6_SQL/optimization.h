#pragma once

#include "student_repository.h"
#include "database_manager.h"

void createIndexes(DatabaseManager& dbManager);
void bulkInsertStudents(DatabaseManager& dbManager,
    StudentRepository& repo,
    int count);

