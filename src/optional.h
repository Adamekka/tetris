#ifndef OPTIONAL_H
#define OPTIONAL_H

#define optional(T)                                                            \
    struct {                                                                   \
        bool present;                                                          \
        T value;                                                               \
    }

#endif
