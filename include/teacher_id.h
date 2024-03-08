#include <iostream>

size_t teacher_id_count = 0;

struct TeacherId {
    private:
    const size_t id_;

    TeacherId();

    public:
    bool operator<(TeacherId other) const;

    bool operator>(TeacherId other) const;
    
    bool operator==(TeacherId other) const;

    bool operator!=(TeacherId other) const;
};