#include <iostream>

size_t student_id_count = 0;

struct StudentId {
    private:
    size_t id_;

    public:
    StudentId();

    StudentId(int);

    bool operator<(StudentId) const;

    bool operator>(StudentId) const;

    bool operator==(StudentId) const;

    bool operator!=(StudentId) const;
};