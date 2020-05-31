#ifndef __TOTAL_ORDERS__
#define __TOTAL_ORDERS__

//pointer to a function
typedef int (*total_order_type)(const void *a, const void *b);

typedef int new_type;

int leq_float(const void *a, const void *b);
int leq_int(const void *a, const void *b);
int geq_int(const void *a, const void *b);

#endif