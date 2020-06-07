#include <binheap.h>
#include <string.h>
#include <stdio.h>

#define PARENT(node) ((node - 1) / 2)
#define LEFT_CHILD(node) (2 * (node) + 1)
#define RIGHT_CHILD(node) (2 * (node + 1))

//node represent the index, which goes from 0 to n-1
#define VALID_NODE(H, node) ((H)->num_of_elem > (node))

// (H)->A = base of the address
// node*key_size
#define ADDR(H, node) ((H)->A + (node) * (H)->key_size)
#define ADDR_KEY_POS(H, position) ((H)->key_pos+(position))
#define ADDR_REV_POS(H, position) ((H)->rev_pos+(position))

#define INDEX_OF(H, addr) (((addr) - ((H)->A)) / (H)->key_size)

int is_heap_empty(const binheap_type *H)
{
    return H->num_of_elem == 0;
}

const void *min_value(const binheap_type *H)
{
    if (is_heap_empty(H))
    {
        return NULL;
    }
    // the minimum is stored in the root aka A[0]
    return ADDR(H, H->key_pos[0]);
}

void swap_keys(binheap_type *H, unsigned int index_a, unsigned int index_b)
{
    /*void *source = ADDR(H, node_a);
    void *destination = ADDR(H, node_b);
    void *temp = malloc(H->key_size);

    memcpy(temp, source, H->key_size);
    memcpy(source, destination, H->key_size);
    memcpy(destination, temp, H->key_size);

    free(temp);*/
    //XOR swap
    size_t *p_a = ADDR_KEY_POS(H, index_a);
	size_t *p_b = ADDR_KEY_POS(H, index_b);

    *p_a ^= *p_b;
    *p_b ^= *p_a;
    *p_a ^= *p_b;

    size_t *r_a = ADDR_REV_POS(H, *p_a);
	size_t *r_b = ADDR_REV_POS(H, *p_b);
    
    *r_a ^= *r_b;
    *r_b ^= *r_a;
    *r_a ^= *r_b;
}

void heapify(binheap_type *H, unsigned int node)
{
    unsigned int destination_node = node, child;

    do
    {
        // at the very first itertation this assignment
        // is not very useful, but it will in the next ones
        node = destination_node;

        child = RIGHT_CHILD(node);

        if (VALID_NODE(H, child) &&
            H->leq(ADDR(H, H->key_pos[child]), ADDR(H, H->key_pos[destination_node]))
            //H->leq(ADDR(H, child), ADDR(H, node))
            )
        {
            destination_node = child;
        }

        child = LEFT_CHILD(node);

        if (VALID_NODE(H, child) &&
            H->leq(ADDR(H, H->key_pos[child]), ADDR(H, H->key_pos[destination_node]))
            //H->leq(ADDR(H, child), ADDR(H, node))
            )
        {
            destination_node = child;
        }

        if (destination_node != node)
        {
            swap_keys(H, destination_node, node);
        }
    } while (destination_node != node);
}

const void *extract_min(binheap_type *H)
{
    // This function must be re-implemented
    if (is_heap_empty(H))
    {
        return NULL;
    }

    //swapping the keyes among the root A[0]
    //and the rightmost leaf of the last level A[num_of_elem-1]
    swap_keys(H, 0, H->num_of_elem - 1);
    //deleting the rightmost leaf of the last level
    H->num_of_elem--;
    //we need to restore the heap porperty
    heapify(H, 0);

    return ADDR(H, H->key_pos[H->num_of_elem]);
}

const void *find_max(void *A, unsigned int n_of_elem,
                     size_t k_size, total_order_type ord)
{
    if (n_of_elem == 0)
    {
        return NULL;
    }

    const void *max_value = A;
    for (const void *addr = A + k_size; addr != A + n_of_elem * k_size; addr += k_size)
    {
        if (!ord(addr, max_value))
        {
            max_value = addr;
        }
    }

    return max_value;
}

binheap_type *build_heap(void *A,
                         const unsigned int num_of_elem,
                         const unsigned int max_size,
                         const size_t key_size,
                         total_order_type leq)
{
    binheap_type *H = (binheap_type *)malloc(sizeof(binheap_type));
    H->A = A;
    H->num_of_elem = num_of_elem;
    H->num_of_elem = num_of_elem;
    H->max_size = max_size;
    H->key_size = key_size;
    H->leq = leq;
    H->max_order_value = malloc(key_size);
    H->key_pos = (size_t *)malloc(sizeof(size_t) * max_size);

    for (size_t i = 0; i < num_of_elem; i++)
    {
        H->key_pos[i] = i;
    }

    H->rev_pos = (size_t *) malloc(sizeof(size_t) * max_size);

    for (size_t i = 0; i < max_size; i++)
    {
        H->rev_pos[i] = i;
    }

    if (num_of_elem == 0)
    {
        return H;
    }

    //get the maximum among A[0..num_of_elem-1]
    // and store it in max_ord_value
    const void *value = find_max(A, num_of_elem,
                                 key_size, leq);

    memcpy(H->max_order_value, value, key_size);


    //from the second lowest upper low up to the root
    for (unsigned int i = num_of_elem / 2; i > 0; i--)
    {
        heapify(H, i);
    }
    heapify(H, 0);

    return H;
}

void delete_heap(binheap_type *H)
{
    free(H->max_order_value);
    free(H->key_pos);
    free(H->rev_pos);
    free(H);
}

//const void *decrease_key(binheap_type *H, unsigned int key, const void *value)
const void *decrease_key(binheap_type *H, void* node, const void *value)
{
    unsigned int node_index = INDEX_OF(H, node);
    size_t* p_node_key = ADDR_KEY_POS(H, node_index);

    //if node not belong to H or *value->*node return NULL
    if (!VALID_NODE(H, node_index) || !(H->leq(value, ADDR(H, *p_node_key))))
    {
        return NULL;
    }

    memcpy(ADDR(H, *p_node_key), value, H->key_size);

    unsigned int parent_index = PARENT(node_index);
    size_t *p_node_parent = ADDR_KEY_POS(H, parent_index);

    while ((node_index != 0) && (!H->leq(ADDR(H, *p_node_parent), ADDR(H, *p_node_key))))
    {

        //parent = PARENT(key);
        swap_keys(H, parent_index, node_index);

        node_index = parent_index;
        p_node_key = p_node_parent;

        parent_index = PARENT(node_index);
        p_node_parent = ADDR_KEY_POS(H, parent_index);
    }

    return ADDR(H, *p_node_key);
}

const void *insert_value(binheap_type *H, const void *value)
{
    if (H->max_size == H->num_of_elem_A)
    {
        return NULL;
    }

    if (!H->leq(value, H->max_order_value) || H->num_of_elem_A == 0)
    {
        memcpy(H->max_order_value, value, H->key_size);
    }

    //H->key_pos[H->num_of_elem] = H->num_of_elem;
    // num_of_elem is the index of the location past the last one
    void *new_node_addr = ADDR(H, H->num_of_elem_A);
    memcpy(new_node_addr, H->max_order_value, H->key_size);
    size_t * new_node =ADDR_KEY_POS(H, H->num_of_elem);
	*new_node = H->num_of_elem_A;
    H->rev_pos[H->num_of_elem_A] = H->num_of_elem;

    H->num_of_elem_A++;
    H->num_of_elem++;

    return decrease_key(H, new_node_addr, value);
}

void print_heap(const binheap_type *H,
                void (*key_printer)(const void *value))
{
    unsigned int node = 0;
    unsigned int next_level_node = 1;

    while (node < H->num_of_elem)
    {

        if (node == next_level_node)
        {
            printf("\n");
            next_level_node = LEFT_CHILD(node);
        }

        else
        {
            printf("\t");
        }

        key_printer(ADDR(H, H->key_pos[node]));

        node++;
    }

    printf("\n");
}