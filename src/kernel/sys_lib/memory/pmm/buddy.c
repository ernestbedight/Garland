#include <memory/memory.h>

#define MAX_ORDER 11

#define ZONE_KERNEL 1
#define ZONE_USER   2
#define ZONE_DMA    3

uint64_t reserved_data_region_address   = 0; 

typedef struct page PACKED page_t;

typedef struct page{
    void * address;
    bool used;
    bool user_used;     //WIP
    bool kernel_used;   //WIP
    bool reserved;
    page_t * next_page;
    page_t * previous_page;
    uint16_t order;
    bool left;
}PACKED page_t;

page_t * _analyse_region(struct limine_memmap_entry mem_entry, uint64_t reserved_data_region_base);

struct allocator_head_t {
    page_t * free_list[MAX_ORDER+1];
}allocator_head;

void _check(void);

void initialize_allocator()
{
    uint64_t reserved_data_region_size  = 0;
    page_t * last_page;

    #define ENTRY_MASKING   for(uint8_t entry_number = 0; entry_number < memmap_req.response->entry_count; entry_number++){\
                            if(memmap_req.response->entries[entry_number]->type == LIMINE_MEMMAP_USABLE && memmap_req.response->entries[entry_number]->length >= (PAGE_SIZE << MAX_ORDER)){

    ENTRY_MASKING
        //finds the biggest region to put data in
        if(memmap_req.response->entries[entry_number]->length > reserved_data_region_size)
            {
                reserved_data_region_size    = memmap_req.response->entries[entry_number]->length;
                reserved_data_region_address = ((memmap_req.response->entries[entry_number]->base%PAGE_SIZE))?PAGE_SIZE:0 +(memmap_req.response->entries[entry_number]->base>>(12)<<(12)); //aligns the address
            }
        }
    }

    print("%c%nBiggest region:%n%tbase:0x%h%n%tlenght:0x%h%n%c",RED,reserved_data_region_address,reserved_data_region_size,TERMINAL_FOREGROUND_COLOUR);

    ENTRY_MASKING
            print("%c%nANALYSING REGION...%n%c",MAGENTA,TERMINAL_FOREGROUND_COLOUR);    
            last_page = _analyse_region(*memmap_req.response->entries[entry_number], reserved_data_region_address);    //goes through all the regions and sets the data for them
        }
    }

    uint64_t reserved_page_count = (sizeof(page_t)*(((uint64_t)last_page->address)/PAGE_SIZE)); 
             reserved_page_count += (((uint64_t)last_page->address)%PAGE_SIZE)?1:0;        

    uint64_t reserved_page_segment_count = (reserved_page_count/(1<<MAX_ORDER)) + (reserved_page_count%(1<<MAX_ORDER))?1:0;
    
    for(uint64_t reserved_page_counter   = 0; reserved_page_counter < reserved_page_segment_count; reserved_page_counter++)
    {
        ((page_t *) reserved_data_region_address)[reserved_page_counter*(1<<MAX_ORDER)+reserved_data_region_address/PAGE_SIZE].reserved = true;
    }

    allocator_head.free_list[MAX_ORDER]                 = &(((page_t *) reserved_data_region_address)[reserved_page_segment_count*(1<<MAX_ORDER)+reserved_data_region_address/PAGE_SIZE]);
    allocator_head.free_list[MAX_ORDER]->previous_page  = last_page;
    print("The memory allocator has been succesfully initialized%n");
}

page_t * _analyse_region(struct limine_memmap_entry mem_entry, uint64_t reserved_data_region_base)
{
    uint64_t    entry_size                     = mem_entry.length, \
                entry_base                     = ((mem_entry.base%PAGE_SIZE))?PAGE_SIZE:0 +(mem_entry.base>>(12)<<(12));
    uint64_t    regional_order_segments_count  = (entry_size+(PAGE_SIZE - mem_entry.base%PAGE_SIZE)) / (PAGE_SIZE << MAX_ORDER);               
    uint64_t    page_count                     = regional_order_segments_count*(1<<MAX_ORDER);          
    page_t    * regional_data                  = (void *) reserved_data_region_base;

    page_t    * return_page;
    static bool first_call;

    print("entry size:0x%h%nentry base:0x%h%ndata location:0x%h%n",entry_size, entry_base, regional_data);

    static page_t * previous;

    print("page count:%d%n",page_count);
    bool buddy_switch = true;
    for(uint64_t page_selector = 0; page_selector <= page_count;page_selector++)
    {
        uint64_t address = entry_base + page_selector * PAGE_SIZE;
        uint64_t index   = address/PAGE_SIZE;
        if(!(page_selector%(1<<MAX_ORDER))){
            regional_data[index].order = MAX_ORDER;     
            if(!first_call){
                first_call = true; 
            }
            else{
                previous->next_page = &regional_data[index];     
                regional_data[index].previous_page = previous;  
            }
            previous = &regional_data[index];
        }
        regional_data[index].address  = address;  
        regional_data[index].left     = buddy_switch;
        buddy_switch = (buddy_switch)?false:true;
        return_page  = &regional_data[index];
    }
    return return_page;
}

void _check(void){
    page_t * current_page = allocator_head.free_list[MAX_ORDER];
    while(current_page->next_page){
        print("base:0x%h  ",(uint64_t)current_page->next_page);
        current_page = current_page->next_page;
    }
}

uint64_t request_page(uint8_t order){
    uint64_t return_address;
    if(allocator_head.free_list[order])
    {

        allocator_head.free_list[order]->used = true;
        return_address = allocator_head.free_list[order]->address;
        remove_page(return_address,order,return_address/PAGE_SIZE);
        return return_address;
    }

    else
    {
        for(uint8_t order_selector = order+1; order_selector <= MAX_ORDER; order_selector++)
        {
            if(allocator_head.free_list[order_selector])
            {
                return_address = allocator_head.free_list[order_selector]->address;
                allocator_head.free_list[order_selector]->used = true;

                remove_first_page(order_selector);

                for(uint8_t inverted_order_selector = order_selector; inverted_order_selector > order; inverted_order_selector--)
                {
                    add_page(return_address+(PAGE_SIZE<<(inverted_order_selector-1)),inverted_order_selector-1);
                }   
                return return_address;
            }
            
        }
    }
    print("memory finished%n");
    return NULL;
}

void add_page(uint64_t address, uint8_t order)
{
    uint64_t index = address/PAGE_SIZE;
    page_t * page = &((page_t *)reserved_data_region_address)[index];
    if(allocator_head.free_list[order])
    {
        allocator_head.free_list[order]->previous_page->next_page = page;
        page->previous_page                                       = allocator_head.free_list[order]->previous_page;
        allocator_head.free_list[order]->previous_page            = page;
    }
    else{
        allocator_head.free_list[order]                = page;
        allocator_head.free_list[order]->previous_page = page;
    }
    page->next_page = NULL;
    page->order     = order;
    page->used = false;
}

void remove_page(uint64_t address, uint8_t order, uint64_t index)
{
    page_t * page = allocator_head.free_list[order];

    if(page)
    {
        if(page->next_page)
        {
            do
            {
                if(((uint64_t)(page->address))/PAGE_SIZE == index){
                    page->used = true;
                    page->previous_page->next_page = page->next_page;
                    page->next_page->previous_page = page->previous_page;
                    return;        
                }
                page = page->next_page;
            }
            while(page->next_page);
        }
        else
        {
            allocator_head.free_list[order] = NULL;
        }
    }
}

void remove_first_page(uint8_t order){
    page_t * page = allocator_head.free_list[order];
    if(page->next_page)
        {
          page->used = true;
          page->previous_page->next_page = page->next_page;
          page->next_page->previous_page = page->previous_page;
        }
    else
        {
            allocator_head.free_list[order] = NULL;
        }
}

uint8_t free_page(uint64_t address)
{
    uint64_t index = address/PAGE_SIZE;

    if(((page_t *)reserved_data_region_address)[index].used)
    {
        uint64_t    order                                          = ((page_t *)reserved_data_region_address)[index].order;
        ((page_t *) reserved_data_region_address)[index].used = false;

        while(order <= MAX_ORDER)
        {
            uint64_t buddy_index = index + ((((page_t *)reserved_data_region_address)[index].left)?1:-1)*(1<<order);

            if(((page_t *)reserved_data_region_address)[buddy_index].used)
            {
                break; //I could do this in one line but it's just to make it clearer
            }

            remove_page(((page_t *)reserved_data_region_address)[buddy_index].address,order,buddy_index);
            order++;
        }
        
        ((page_t *)reserved_data_region_address)[index].order     = order;
        ((page_t *)reserved_data_region_address)[index].used = false;

        add_page(address,order);

        return 1;
    }
    else
    {
        print("double free%n");
        return 0;
    }
}




