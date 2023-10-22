# include <stdio.h>
# include <signal.h>
# include <stdlib.h>


//memory block
typedef struct s_mblock
{
    void *address;
    struct s_mblock *next_mb;
}   t_mblock;

//access head of garbage collector everywhere in the program
t_mblock *garbage_collector(void)
{
    static t_mblock head = { NULL, NULL };
    return &head;
}


//malloc stuff and append to the garbage collector
void * gc_malloc(size_t size)
{
    t_mblock *new_mb;
    t_mblock *gc_ptr;


    //create new block and append to list
    gc_ptr = garbage_collector();

    new_mb = malloc(sizeof(t_mblock));
    if(!new_mb)
        return NULL;
    
    while(gc_ptr->next_mb)
        gc_ptr = gc_ptr->next_mb;
    gc_ptr->next_mb = new_mb;

    //malloc content and set null 
    new_mb->next_mb = NULL;
    new_mb->address = malloc(size);
    if(!new_mb->address)
        return NULL;
    
    //return pointer on malloced adresses
    return new_mb->address;
}


// free specific memory block and its content and connect back the list
void gc_free(void*address)
{
    t_mblock*gc_ptr;
    t_mblock*ptr_copy;

    gc_ptr = garbage_collector()->next_mb;
    ptr_copy = garbage_collector();

    while(gc_ptr)
    {
        if(gc_ptr->address == address)
        {
            ptr_copy->next_mb = gc_ptr->next_mb;
            if(gc_ptr->address)
                free(gc_ptr->address);
            free(gc_ptr);

            return ;
        }
        ptr_copy = gc_ptr;
        gc_ptr = gc_ptr->next_mb;
    }
}

//free entire garbage collector
void gc_free_all(void)
{
    t_mblock*gc_ptr;
    t_mblock*ptr_copy;

    gc_ptr = garbage_collector()->next_mb;
    while(gc_ptr)
    {
        if(gc_ptr->address)
            free(gc_ptr->address);
        ptr_copy = gc_ptr;
        gc_ptr = gc_ptr->next_mb;
        free(ptr_copy);
    }
    garbage_collector()->next_mb = NULL;
}
