#include "vm/page.h"



/* Returns a hash value for an supplemental page. */
unsigned spt_hash (const struct hash_elem *elem, void *aux)
{
const struct supplemental_page_table *spt_ptr=hash_entry (elem, struct supplemental_page_table, spt_elem);
return hash_bytes (&spt_ptr->page_uaddr, sizeof spt_ptr->page_uaddr);
}

/* Returns true if page a precedes page b. Taken from pintos guide*/
bool spt_hash_less (const struct hash_elem *a, const struct hash_elem *b, void *aux)
{
const struct supplemental_page_table *spt_ptr_a = hash_entry (a, struct supplemental_page_table, spt_elem);
const struct supplemental_page_table *spt_ptr_b = hash_entry (b, struct supplemental_page_table, spt_elem);
return spt_ptr_a->page_uaddr < spt_ptr_b->page_uaddr;
}
