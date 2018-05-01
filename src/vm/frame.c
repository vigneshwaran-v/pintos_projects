#include "userprog/exception.h"
#include <inttypes.h>
#include <stdio.h>
#include "userprog/gdt.h"
#include "userprog/syscall.h"
#include "userprog/pagedir.h"
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "threads/palloc.h"
#include "threads/vaddr.h"
#include "vm/page.h"
#include "vm/frame.h"



struct lock frame_table_lock;


void frame_init()
{
lock_init (&frame_table_lock);
list_init (&frame_table_list);
}

/*Allocates a frame page*/

void *frame_allocator(enum palloc_flags palusr)
{
lock_acquire(&frame_table_lock);
if ( (palusr & PAL_USER) == 0 )
    {
     
      return NULL;
    }

void *frame=palloc_get_page(PAL_USER);



if(frame!=NULL)
{
struct frame *frame_table_entry= malloc(sizeof(struct frame));;
frame_table_entry->owner=thread_current();
frame_table_entry->physical_frame=frame;
list_push_back(&frame_table_list, &frame_table_entry->elem);
lock_release(&frame_table_lock);

}
else
{
lock_release(&frame_table_lock);
return NULL;
}

return frame;

}


/*Deallocates a frame page*/
void frame_deallocator(void *frame)
{
 
          
  lock_acquire(&frame_table_lock);
  struct list_elem *frame_table_entry;
  frame_table_entry=list_begin(&frame_table_list);
  
  while(frame_table_entry!=list_end(&frame_table_list))
    {
      struct frame *frame = list_entry(frame_table_entry, struct frame, elem);
      if (frame->physical_frame == frame)
	{
	  list_remove(frame_table_entry);
	  free(frame_table_entry);
	  palloc_free_page(frame);
	  break;
	}
     frame_table_entry=list_next(frame_table_entry);
    }
  lock_release(&frame_table_lock);

}





