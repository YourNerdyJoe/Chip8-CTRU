#ifndef _SVC_EX_H_
#define _SVC_EX_H_
#include <ctr/svc.h>

/* See http://3dbrew.org/wiki/SVC */

/* SVC Types and Structures */

typedef enum MemoryState {
	MEMST_FREE = 0,
	MEMST_RESERVED,
	MEMST_IO,
	MEMST_STATIC,
	MEMST_CODE,
	MEMST_PRIVATE,
	MEMST_SHARED,
	MEMST_CONTINUOUS,
	MEMST_ALIASED,
	MEMST_ALIAS,
	MEMST_ALIAS_CODE,
	MEMST_LOCKED,
} MemoryState;

typedef enum PageFlags {
	PF_LOCKED,
	PF_CHANGED,
} PageFlags;

/* for naming consistancy */
typedef MEMORY_OPERATION MemoryOperation;

/* additional memop for mapping the gsp heap */
#define MEMOP_MAP_GSP_HEAP	0x10003
#define GSP_HEAP_SIZE	0x2000000

typedef enum MemoryPermission {
	MEMPER_NONE		= 0,
	MEMPER_READ		= 1,
	MEMPER_WRITE		= 2,
	MEMPER_READWRITE	= 3,
	MEMPER_DONTCARE	= 0x10000000,
} MemoryPermission;

typedef enum ResetType {
	RT_ONESHOT,
	RT_STICKY,
	RT_PULSE,
} ResetType;

typedef struct MemoryInfo {
	u32 base_address;
	u32 size;
	u32 permission;
	MemoryState state;
} MemoryInfo;

typedef struct PageInfo {
	u32 flags;
} PageInfo;

typedef struct StartupInfo {
	s32 priority;
	u32 stack_size;
	s32 argc;
	s16* argv;
	s16* envp;
} StartupInfo;

typedef struct CreateProcessInfo {
	/* All addresses are given virtual for the process to be created. */
	/* All sizes/offsets are in given in 0x1000-pages. */
	u8  codeset_name[8];
	u32 text_addr;
	u32 text_size;
	u32 ro_addr;
	u32 ro_size;
	u32 data_addr;
	u32 data_size;
	u32 ro_offset;
	u32 data_offset;
	u32 bss_size_plus_data_size;
	u8  program_id[8];
	u32 unknown[2];
} CreateProcessInfo;

#endif
