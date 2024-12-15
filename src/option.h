#ifndef OPTION_H
#define OPTION_H

#define Option(T)                                                              \
    struct {                                                                   \
        bool present;                                                          \
        T value;                                                               \
    }

#endif
