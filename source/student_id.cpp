#include "../include/student_id.h"

StudentId::StudentId() : id_(++student_id_count) {}

bool StudentId::operator<(StudentId other) const { return id_ < other.id_; }

bool StudentId::operator>(StudentId other) const { return id_ > other.id_; }

bool StudentId::operator==(StudentId other) const { return id_ == other.id_; }

bool StudentId::operator!=(StudentId other) const { return id_ != other.id_; }
