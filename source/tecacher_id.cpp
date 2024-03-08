#include "../include/teacher_id.h"

TeacherId::TeacherId() : id_(++teacher_id_count) {}

bool TeacherId::operator<(TeacherId other) const { return id_ < other.id_; }

bool TeacherId::operator>(TeacherId other) const { return id_ > other.id_; }

bool TeacherId::operator==(TeacherId other) const { return id_ == other.id_; }

bool TeacherId::operator!=(TeacherId other) const { return id_ != other.id_; }
