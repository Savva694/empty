#include <iostream>

size_t student_id_count = 0;

struct StudentId {
    private:
    const size_t id_;

    StudentId();

    public:
    bool operator<(StudentId) const;

    bool operator>(StudentId) const;

    bool operator==(StudentId) const;

    bool operator!=(StudentId) const;
};