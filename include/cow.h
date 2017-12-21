#ifndef _KMINT_COW_H
#define _KMINT_COW_H

namespace kmint {
    class hare;
    class cow {
        const hare* _hare;
        const hare& get_hare() const { return *_hare; }
    public:
        
    };
}

#endif
