#include <hash.h>
struct supplemental_page_table
{
void *page_uaddr;
struct hash_elem spt_elem;
void *physical_frame;
void *page_owner;
bool read_or_write;
};



/* Returns true if page a precedes page b. Taken from pintos guide */

bool spt_hash_less (const struct hash_elem *a, const struct hash_elem *b, void *aux);

/* Returns a hash value for an supplemental page. */
unsigned spt_hash (const struct hash_elem *elem, void *aux);
