#ifndef __TEST_SET__
#define __TEST_SET__

void setup_test_set(float *test_set_A[], float *test_set_H[], 
                    const unsigned int num_of_instances,
                    const unsigned int instance_size);
void destroy_test_set(float *test_set_A[], float *test_set_H[], 
                      const unsigned int num_of_instances);

int *allocate_int_random_array(const unsigned int num_of_elem);

      
#endif
