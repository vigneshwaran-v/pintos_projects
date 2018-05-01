#include "threads/thread.h"
#include "lib/kernel/list.h"



/*vv Creating struct to hold info about frames*/
struct frame
{
uint32_t *frame_ptr;
struct thread* owner;
struct sup_page_entry* aux;
void *physical_frame;
struct list_elem elem;
};

/* Frame table - holds info about frames */
struct list frame_table_list;


/*Function to initialize frame table*/
void frame_init();

/*Function to allocate frames //and add frame table entries//*/
void *frame_allocator(enum palloc_flags palusr);


/* Function to free frames //and remove page table entries//*/
void frame_deallocator(void*);



