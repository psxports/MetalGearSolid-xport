#include "xport.h"

/* Unresolved until the original PsyQ graph type storage is audited */
const uint32 xport_gpu_graph_type_address = 0u;

/* Unresolved CD bindings until original storage is audited */
const uint32 xport_cd_sync_callback_address = 0u;
const uint32 xport_cd_ready_callback_address = 0u;
const uint32 xport_cd_status_address = 0u;
const uint32 xport_cd_setloc_table_address = 0u;

void mgs_initialize_heap_8009bf20(uint32 address, uint32 bytes);
void mgs_main_80014b04(void);

void mgs_executable_entry(uint32 bios_return_address)
{
    uint32 address = 0x800AE098;
    uint32 stack_top;
    uint32 reserved_stack;
    uint32 heap_size;

    FUNCTION_MARKER(0x8009B9B0, "SLUS_005.94");
    do
    {
        w_u32(address, 0);
        address += 4;
    } while (address < 0x800C5970);

    stack_top = r_u32(0x800ADA04);
    if (stack_top >= 0x80000000 && stack_top < 0x80000008)
    {
        xport_mips_overflow_exception(0x8009B9E0);
        return;
    }
    stack_top -= 8;
    reserved_stack = r_u32(0x800ADA08);
    heap_size = stack_top - reserved_stack - 0x000C5970;
    w_u32(0x800AD8E8, heap_size);
    w_u32(0x800AD8E4, 0x800C5970);
    w_u32(0x800AE368, bios_return_address);

    /* Preserve the heap pointer adjustment in the original call delay slot */
    mgs_initialize_heap_8009bf20(0x800C5974, heap_size);
    /* The following JAL overwrites the reloaded return address */
    (void)r_u32(0x800AE368);
    mgs_main_80014b04();
    xport_mips_break(1);
}
