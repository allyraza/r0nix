/*
 * Copyright (C) 1992, 1993, 1994, 1995
 * Remy Card (card@masi.ibp.fr)
 * Laboratoire MASI - Institut Blaise Pascal
 * Universite Pierre et Marie Curie (Paris VI)
 *
 *  from
 *
 *  linux/include/linux/minix_fs.h
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 */

#include <stdint.h>

/* data type for block offset of block group */
typedef int ext2_grpblk_t;

typedef unsigned long ext2_fsblk_t;

#define E2FSBLK "%lu"

#define rsv_start rsv_window._rsv_start
#define rsv_end rsv_window._rsv_end

/* Define EXT2_RESERVATION to reserve data blocks for expanding file  */
#define EXT2_DEFAULT_RESERVE_BLOCKS     8
/*max window size: 1024(direct blocks) + 3([t,d]indirect blocks) */
#define EXT2_MAX_RESERVE_BLOCKS         1027
#define EXT2_RESERVE_WINDOW_NOT_ALLOCATED 0
/* The second extended file system versio  */
#define EXT2FS_DATE		"95/08/09"
#define EXT2FS_VERSION		"0.5b"

/* Special inode number  */
#define	EXT2_BAD_INO		 1	/* Bad blocks inode */
#define EXT2_ROOT_INO		 2	/* Root inode */
#define EXT2_BOOT_LOADER_INO	 5	/* Boot loader inode */
#define EXT2_UNDEL_DIR_INO	 6	/* Undelete directory inode */

/* First non-reserved inode for old ext2 filesystems */
#define EXT2_GOOD_OLD_FIRST_INO	11

/* Macro-instructions used to manage several block size  */
#define EXT2_MIN_BLOCK_SIZE		1024
#define	EXT2_MAX_BLOCK_SIZE		4096
#define EXT2_MIN_BLOCK_LOG_SIZE		  10
#define EXT2_BLOCK_SIZE(s)		((s)->s_blocksize)
#define	EXT2_ADDR_PER_BLOCK(s)		(EXT2_BLOCK_SIZE(s) / sizeof (uint32_t))
#define EXT2_BLOCK_SIZE_BITS(s)		((s)->s_blocksize_bits)
#define	EXT2_ADDR_PER_BLOCK_BITS(s)	(EXT2_SB(s)->s_addr_per_block_bits)
#define EXT2_INODE_SIZE(s)		(EXT2_SB(s)->s_inode_size)
#define EXT2_FIRST_INO(s)		(EXT2_SB(s)->s_first_ino)

/* Macro-instructions used to manage fragment  */
#define EXT2_MIN_FRAG_SIZE		1024
#define	EXT2_MAX_FRAG_SIZE		4096
#define EXT2_MIN_FRAG_LOG_SIZE		  10
#define EXT2_FRAG_SIZE(s)		(EXT2_SB(s)->s_frag_size)
#define EXT2_FRAGS_PER_BLOCK(s)		(EXT2_SB(s)->s_frags_per_block)


/* Structure of a blocks group descriptor */
/* (the Block Group Descriptor Table is just an array of these) */
struct ext2_group_desc
{
	uint32_t	bg_block_bitmap;/* Blocks bitmap block, _NOT_ the actual bitmap */
	uint32_t	bg_inode_bitmap;	/* Inodes bitmap block */
	uint32_t	bg_inode_table;		/* Inodes table block */
	uint16_t	bg_free_blocks_count;	/* Free blocks count */
	uint16_t	bg_free_inodes_count;	/* Free inodes count */
	uint16_t	bg_used_dirs_count;	/* Directories count */
	uint16_t	bg_pad;
	uint32_t	bg_reserved[3];
};

/* Macro-instructions used to manage group descriptors */
#define EXT2_BLOCKS_PER_GROUP(s)	(EXT2_SB(s)->s_blocks_per_group)
#define EXT2_DESC_PER_BLOCK(s)		(EXT2_SB(s)->s_desc_per_block)
#define EXT2_INODES_PER_GROUP(s)	(EXT2_SB(s)->s_inodes_per_group)
#define EXT2_DESC_PER_BLOCK_BITS(s)	(EXT2_SB(s)->s_desc_per_block_bits)

/* Constants relative to the data blocks */
#define	EXT2_NDIR_BLOCKS		12
#define	EXT2_IND_BLOCK			EXT2_NDIR_BLOCKS
#define	EXT2_DIND_BLOCK			(EXT2_IND_BLOCK + 1)
#define	EXT2_TIND_BLOCK			(EXT2_DIND_BLOCK + 1)
#define	EXT2_N_BLOCKS			(EXT2_TIND_BLOCK + 1)

/* Inode flags (GETFLAGS/SETFLAGS  */
#define	EXT2_SECRM_FL			FS_SECRM_FL	/* Secure deletion */
#define	EXT2_UNRM_FL			FS_UNRM_FL	/* Undelete */
#define	EXT2_COMPR_FL			FS_COMPR_FL	/* Compress file */
#define EXT2_SYNC_FL			FS_SYNC_FL	/* Synchronous updates */
#define EXT2_IMMUTABLE_FL		FS_IMMUTABLE_FL	/* Immutable file */
#define EXT2_APPEND_FL			FS_APPEND_FL	/* writes to file may only append */
#define EXT2_NODUMP_FL			FS_NODUMP_FL	/* do not dump file */
#define EXT2_NOATIME_FL			FS_NOATIME_FL	/* do not update atime */
/* Reserved for compression usage... */
#define EXT2_DIRTY_FL			FS_DIRTY_FL
#define EXT2_COMPRBLK_FL		FS_COMPRBLK_FL	/* One or more compressed clusters */
#define EXT2_NOCOMP_FL			FS_NOCOMP_FL	/* Don't compress */
#define EXT2_ECOMPR_FL			FS_ECOMPR_FL	/* Compression error */
/* End compression flags --- maybe not all used */	
#define EXT2_BTREE_FL			FS_BTREE_FL	/* btree format dir */
#define EXT2_INDEX_FL			FS_INDEX_FL	/* hash-indexed directory */
#define EXT2_IMAGIC_FL			FS_IMAGIC_FL	/* AFS directory */
#define EXT2_JOURNAL_DATA_FL		FS_JOURNAL_DATA_FL /* Reserved for ext3 */
#define EXT2_NOTAIL_FL			FS_NOTAIL_FL	/* file tail should not be merged */
#define EXT2_DIRSYNC_FL			FS_DIRSYNC_FL	/* dirsync behaviour (directories only) */
#define EXT2_TOPDIR_FL			FS_TOPDIR_FL	/* Top of directory hierarchies*/
#define EXT2_RESERVED_FL		FS_RESERVED_FL	/* reserved for ext2 lib */

#define EXT2_FL_USER_VISIBLE		FS_FL_USER_VISIBLE	/* User visible flags */
#define EXT2_FL_USER_MODIFIABLE		FS_FL_USER_MODIFIABLE	/* User modifiable flags */

/* Flags that should be inherited by new inodes from their parent. */
#define EXT2_FL_INHERITED (EXT2_SECRM_FL | EXT2_UNRM_FL | EXT2_COMPR_FL |\
			   EXT2_SYNC_FL | EXT2_NODUMP_FL |\
			   EXT2_NOATIME_FL | EXT2_COMPRBLK_FL |\
			   EXT2_NOCOMP_FL | EXT2_JOURNAL_DATA_FL |\
			   EXT2_NOTAIL_FL | EXT2_DIRSYNC_FL)

/* Flags that are appropriate for regular files (all but dir-specific ones). */
#define EXT2_REG_FLMASK (~(EXT2_DIRSYNC_FL | EXT2_TOPDIR_FL))

/* Flags that are appropriate for non-directories/regular files. */
#define EXT2_OTHER_FLMASK (EXT2_NODUMP_FL | EXT2_NOATIME_FL)

/* ioctl commands */
#define	EXT2_IOC_GETFLAGS		FS_IOC_GETFLAGS
#define	EXT2_IOC_SETFLAGS		FS_IOC_SETFLAGS
#define	EXT2_IOC_GETVERSION		FS_IOC_GETVERSION
#define	EXT2_IOC_SETVERSION		FS_IOC_SETVERSION
#define	EXT2_IOC_GETRSVSZ		_IOR('f', 5, long)
#define	EXT2_IOC_SETRSVSZ		_IOW('f', 6, long)

/* ioctl commands in 32 bit emulation */
#define EXT2_IOC32_GETFLAGS		FS_IOC32_GETFLAGS
#define EXT2_IOC32_SETFLAGS		FS_IOC32_SETFLAGS
#define EXT2_IOC32_GETVERSION		FS_IOC32_GETVERSION
#define EXT2_IOC32_SETVERSION		FS_IOC32_SETVERSION


/* NOTE: _ INODE ADDRESSES START AT 1 _ */
/* Structure of an inode on the disk */
struct ext2_inode {
	uint16_t	i_mode;		/* File mode */
	uint16_t	i_uid;		/* Low 16 bits of Owner Uid */
	uint32_t	i_size;		/* Size in bytes */
	uint32_t	i_atime;	/* Access time */
	uint32_t	i_ctime;	/* Creation time */
	uint32_t	i_mtime;	/* Modification time */
	uint32_t	i_dtime;	/* Deletion Time */
	uint16_t	i_gid;		/* Low 16 bits of Group Id */
	uint16_t	i_links_count;	/* Links count */
	uint32_t	i_blocks;	/* Blocks count */
	uint32_t	i_flags;	/* File flags */
	union {
		struct {
			uint32_t  l_i_reserved1;
		} linux1;
		struct {
			uint32_t  h_i_translator;
		} hurd1;
		struct {
			uint32_t  m_i_reserved1;
		} masix1;
	} osd1;				/* OS dependent 1 */
	uint32_t	i_block[EXT2_N_BLOCKS];/* Pointers to blocks */
	uint32_t	i_generation;	/* File version (for NFS) */
	uint32_t	i_file_acl;	/* File ACL */
	uint32_t	i_dir_acl;	/* Directory ACL */
	uint32_t	i_faddr;	/* Fragment address */
	union {
		struct {
			uint8_t	l_i_frag;	/* Fragment number */
			uint8_t	l_i_fsize;	/* Fragment size */
			uint16_t	i_pad1;
			uint16_t	l_i_uid_high;	/* these 2 fields    */
			uint16_t	l_i_gid_high;	/* were reserved2[0] */
			uint32_t	l_i_reserved2;
		} linux2;
		struct {
			uint8_t	h_i_frag;	/* Fragment number */
			uint8_t	h_i_fsize;	/* Fragment size */
			uint16_t	h_i_mode_high;
			uint16_t	h_i_uid_high;
			uint16_t	h_i_gid_high;
			uint32_t	h_i_author;
		} hurd2;
		struct {
			uint8_t	m_i_frag;	/* Fragment number */
			uint8_t	m_i_fsize;	/* Fragment size */
			uint16_t	m_pad1;
			uint32_t	m_i_reserved2[2];
		} masix2;
	} osd2;				/* OS dependent 2 */
};

#define i_size_high	i_dir_acl

#define i_reserved1	osd1.linux1.l_i_reserved1
#define i_frag		osd2.linux2.l_i_frag
#define i_fsize		osd2.linux2.l_i_fsize
#define i_uid_low	i_uid
#define i_gid_low	i_gid
#define i_uid_high	osd2.linux2.l_i_uid_high
#define i_gid_high	osd2.linux2.l_i_gid_high
#define i_reserved2	osd2.linux2.l_i_reserved2

/* File system states */
#define	EXT2_VALID_FS			0x0001	/* Unmounted cleanly */
#define	EXT2_ERROR_FS			0x0002	/* Errors detected */

/* Mount flags */
#define EXT2_MOUNT_CHECK		0x000001  /* Do mount-time checks */
#define EXT2_MOUNT_OLDALLOC		0x000002  /* Don't use the new Orlov allocator */
#define EXT2_MOUNT_GRPID		0x000004  /* Create files with directory's group */
#define EXT2_MOUNT_DEBUG		0x000008  /* Some debugging messages */
#define EXT2_MOUNT_ERRORS_CONT		0x000010  /* Continue on errors */
#define EXT2_MOUNT_ERRORS_RO		0x000020  /* Remount fs ro on errors */
#define EXT2_MOUNT_ERRORS_PANIC		0x000040  /* Panic on errors */
#define EXT2_MOUNT_MINIX_DF		0x000080  /* Mimics the Minix statfs */
#define EXT2_MOUNT_NOBH			0x000100  /* No buffer_heads */
#define EXT2_MOUNT_NO_UID32		0x000200  /* Disable 32-bit UIDs */
#define EXT2_MOUNT_XATTR_USER		0x004000  /* Extended user attributes */
#define EXT2_MOUNT_POSIX_ACL		0x008000  /* POSIX Access Control Lists */
#define EXT2_MOUNT_XIP			0x010000  /* Obsolete, use DAX */
#define EXT2_MOUNT_USRQUOTA		0x020000  /* user quota */
#define EXT2_MOUNT_GRPQUOTA		0x040000  /* group quota */
#define EXT2_MOUNT_RESERVATION		0x080000  /* Preallocation */
#ifdef CONFIG_FS_DAX
#define EXT2_MOUNT_DAX			0x100000  /* Direct Access */
#else
#define EXT2_MOUNT_DAX			0
#endif

#define clear_opt(o, opt)		o &= ~EXT2_MOUNT_##opt
#define set_opt(o, opt)			o |= EXT2_MOUNT_##opt
#define test_opt(sb, opt)		(EXT2_SB(sb)->s_mount_opt & \
					 EXT2_MOUNT_##opt)
/* Maximal mount counts between two filesystem checks */
#define EXT2_DFL_MAX_MNT_COUNT		20	/* Allow 20 mounts */
#define EXT2_DFL_CHECKINTERVAL		0	/* Don't use interval check */

/* Behaviour when detecting errors */
#define EXT2_ERRORS_CONTINUE		1	/* Continue execution */
#define EXT2_ERRORS_RO			2	/* Remount fs read-only */
#define EXT2_ERRORS_PANIC		3	/* Panic */
#define EXT2_ERRORS_DEFAULT		EXT2_ERRORS_CONTINUE

/* Structure of the super block */
struct ext2_super_block {
	uint32_t	s_inodes_count;		/* Inodes count */
	uint32_t	s_blocks_count;		/* Blocks count */
	uint32_t	s_r_blocks_count;	/* Reserved blocks count */
	uint32_t	s_free_blocks_count;	/* Free blocks count */
	uint32_t	s_free_inodes_count;	/* Free inodes count */
	uint32_t	s_first_data_block;	/* First Data Block */
	uint32_t	s_log_block_size;	/* Block size */
	uint32_t	s_log_frag_size;	/* Fragment size */
	uint32_t	s_blocks_per_group;	/* # Blocks per group */
	uint32_t	s_frags_per_group;	/* # Fragments per group */
	uint32_t	s_inodes_per_group;	/* # Inodes per group */
	uint32_t	s_mtime;		/* Mount time */
	uint32_t	s_wtime;		/* Write time */
	uint16_t	s_mnt_count;		/* Mount count */
	uint16_t	s_max_mnt_count;	/* Maximal mount count */
	uint16_t	s_magic;		/* Magic signature */
	uint16_t	s_state;		/* File system state */
	uint16_t	s_errors;	/* Behaviour when detecting errors */
	uint16_t	s_minor_rev_level; 	/* minor revision level */
	uint32_t	s_lastcheck;		/* time of last check */
	uint32_t	s_checkinterval;	/* max. time between checks */
	uint32_t	s_creator_os;		/* OS */
	uint32_t	s_rev_level;		/* Revision level */
	uint16_t	s_def_resuid;	/* Default uid for reserved blocks */
	uint16_t	s_def_resgid;	/* Default gid for reserved blocks */
	/*
	 * These fields are for EXT2_DYNAMIC_REV superblocks only.
	 *
	 * Note: the difference between the compatible feature set and
	 * the incompatible feature set is that if there is a bit set
	 * in the incompatible feature set that the kernel doesn't
	 * know about, it should refuse to mount the filesystem.
	 * 
	 * e2fsck's requirements are more strict; if it doesn't know
	 * about a feature in either the compatible or incompatible
	 * feature set, it must abort and not try to meddle with
	 * things it doesn't understand...
	 */
	uint32_t	s_first_ino; 		/* First non-reserved inode */
	uint16_t   s_inode_size; 		/* size of inode structure */
	uint16_t	s_block_group_nr; 	/* block group # of this superblock */
	uint32_t	s_feature_compat; 	/* compatible feature set */
	uint32_t	s_feature_incompat; 	/* incompatible feature set */
	uint32_t	s_feature_ro_compat; 	/* readonly-compatible feature set */
	uint8_t	s_uuid[16];		/* 128-bit uuid for volume */
	char	s_volume_name[16]; 	/* volume name */
	char	s_last_mounted[64]; 	/* directory where last mounted */
	uint32_t	s_algorithm_usage_bitmap; /* For compression */
	/*
	 * Performance hints.  Directory preallocation should only
	 * happen if the EXT2_COMPAT_PREALLOC flag is on.
	 */
	uint8_t	s_prealloc_blocks;	/* Nr of blocks to try to preallocate*/
	uint8_t	s_prealloc_dir_blocks;	/* Nr to preallocate for dirs */
	uint16_t	s_padding1;
	/* Journaling support valid if EXT3_FEATURE_COMPAT_HAS_JOURNAL set.*/
	uint8_t	s_journal_uuid[16];	/* uuid of journal superblock */
	uint32_t	s_journal_inum;		/* inode number of journal file */
	uint32_t	s_journal_dev;		/* device number of journal file */
	uint32_t	s_last_orphan;		/* start of list of inodes to delete */
	uint32_t	s_hash_seed[4];		/* HTREE hash seed */
	uint8_t	s_def_hash_version;	/* Default hash version to use */
	uint8_t	s_reserved_char_pad;
	uint16_t	s_reserved_word_pad;
	uint32_t	s_default_mount_opts;
 	uint32_t	s_first_meta_bg; 	/* First metablock block group */
	uint32_t	s_reserved[190];	/* Padding to the end of the block */
};

/* Codes for operating systems */
#define EXT2_OS_LINUX		0
#define EXT2_OS_HURD		1
#define EXT2_OS_MASIX		2
#define EXT2_OS_FREEBSD		3
#define EXT2_OS_LITES		4

/* Revision levels */
#define EXT2_GOOD_OLD_REV	0	/* The good old (original) format */
#define EXT2_DYNAMIC_REV	1 	/* V2 format w/ dynamic inode sizes */

#define EXT2_CURRENT_REV	EXT2_GOOD_OLD_REV
#define EXT2_MAX_SUPP_REV	EXT2_DYNAMIC_REV

#define EXT2_GOOD_OLD_INODE_SIZE 128

/* Feature set definitions */

#define EXT2_HAS_COMPAT_FEATURE(sb,mask)			\
	( EXT2_SB(sb)->s_es->s_feature_compat & cpu_to_le32(mask) )
#define EXT2_HAS_RO_COMPAT_FEATURE(sb,mask)			\
	( EXT2_SB(sb)->s_es->s_feature_ro_compat & cpu_to_le32(mask) )
#define EXT2_HAS_INCOMPAT_FEATURE(sb,mask)			\
	( EXT2_SB(sb)->s_es->s_feature_incompat & cpu_to_le32(mask) )
#define EXT2_SET_COMPAT_FEATURE(sb,mask)			\
	EXT2_SB(sb)->s_es->s_feature_compat |= cpu_to_le32(mask)
#define EXT2_SET_RO_COMPAT_FEATURE(sb,mask)			\
	EXT2_SB(sb)->s_es->s_feature_ro_compat |= cpu_to_le32(mask)
#define EXT2_SET_INCOMPAT_FEATURE(sb,mask)			\
	EXT2_SB(sb)->s_es->s_feature_incompat |= cpu_to_le32(mask)
#define EXT2_CLEAR_COMPAT_FEATURE(sb,mask)			\
	EXT2_SB(sb)->s_es->s_feature_compat &= ~cpu_to_le32(mask)
#define EXT2_CLEAR_RO_COMPAT_FEATURE(sb,mask)			\
	EXT2_SB(sb)->s_es->s_feature_ro_compat &= ~cpu_to_le32(mask)
#define EXT2_CLEAR_INCOMPAT_FEATURE(sb,mask)			\
	EXT2_SB(sb)->s_es->s_feature_incompat &= ~cpu_to_le32(mask)

#define EXT2_FEATURE_COMPAT_DIR_PREALLOC	0x0001
#define EXT2_FEATURE_COMPAT_IMAGIC_INODES	0x0002
#define EXT3_FEATURE_COMPAT_HAS_JOURNAL		0x0004
#define EXT2_FEATURE_COMPAT_EXT_ATTR		0x0008
#define EXT2_FEATURE_COMPAT_RESIZE_INO		0x0010
#define EXT2_FEATURE_COMPAT_DIR_INDEX		0x0020
#define EXT2_FEATURE_COMPAT_ANY			0xffffffff

#define EXT2_FEATURE_RO_COMPAT_SPARSE_SUPER	0x0001
#define EXT2_FEATURE_RO_COMPAT_LARGE_FILE	0x0002
#define EXT2_FEATURE_RO_COMPAT_BTREE_DIR	0x0004
#define EXT2_FEATURE_RO_COMPAT_ANY		0xffffffff

#define EXT2_FEATURE_INCOMPAT_COMPRESSION	0x0001
#define EXT2_FEATURE_INCOMPAT_FILETYPE		0x0002
#define EXT3_FEATURE_INCOMPAT_RECOVER		0x0004
#define EXT3_FEATURE_INCOMPAT_JOURNAL_DEV	0x0008
#define EXT2_FEATURE_INCOMPAT_META_BG		0x0010
#define EXT2_FEATURE_INCOMPAT_ANY		0xffffffff

#define EXT2_FEATURE_COMPAT_SUPP	EXT2_FEATURE_COMPAT_EXT_ATTR
#define EXT2_FEATURE_INCOMPAT_SUPP	(EXT2_FEATURE_INCOMPAT_FILETYPE| \
					 EXT2_FEATURE_INCOMPAT_META_BG)
#define EXT2_FEATURE_RO_COMPAT_SUPP	(EXT2_FEATURE_RO_COMPAT_SPARSE_SUPER| \
					 EXT2_FEATURE_RO_COMPAT_LARGE_FILE| \
					 EXT2_FEATURE_RO_COMPAT_BTREE_DIR)
#define EXT2_FEATURE_RO_COMPAT_UNSUPPORTED	~EXT2_FEATURE_RO_COMPAT_SUPP
#define EXT2_FEATURE_INCOMPAT_UNSUPPORTED	~EXT2_FEATURE_INCOMPAT_SUPP

/* Default values for user and/or group using reserved blocks */
#define	EXT2_DEF_RESUID		0
#define	EXT2_DEF_RESGID		0

/* Default mount options */
#define EXT2_DEFM_DEBUG		0x0001
#define EXT2_DEFM_BSDGROUPS	0x0002
#define EXT2_DEFM_XATTR_USER	0x0004
#define EXT2_DEFM_ACL		0x0008
#define EXT2_DEFM_UID16		0x0010
    /* Not used by ext2, but reserved for use by ext3 */
#define EXT3_DEFM_JMODE		0x0060 
#define EXT3_DEFM_JMODE_DATA	0x0020
#define EXT3_DEFM_JMODE_ORDERED	0x0040
#define EXT3_DEFM_JMODE_WBACK	0x0060

#define EXT2_NAME_LEN 256

/* Structure of a directory entry */
struct ext2_dir_entry {
	uint32_t	inode;			/* Inode number */
	uint16_t	rec_len;		/* Directory entry length */
	uint16_t	name_len;		/* Name length */
	char	name[];			/* File name, up to EXT2_NAME_LEN */
};

/*
 * The new version of the directory entry.  Since EXT2 structures are
 * stored in intel byte order, and the name_len field could never be
 * bigger than 255 chars, it's safe to reclaim the extra byte for the
 * file_type field.
 */
struct ext2_dir_entry_2 {
	uint32_t	inode;		/* Inode number */
	uint16_t	rec_len;	/* Directory entry length */
	uint8_t	name_len;		/* Name length */
	uint8_t	file_type;
	char	name[EXT2_NAME_LEN];	/* File name.*/
};

/*
 * Ext2 directory file types.  Only the low 3 bits are used.  The other bits are * reserved for now.
 */
enum {
	EXT2_FT_UNKNOWN		= 0,
	EXT2_FT_REG_FILE	= 1,
	EXT2_FT_DIR		= 2,
	EXT2_FT_CHRDEV		= 3,
	EXT2_FT_BLKDEV		= 4,
	EXT2_FT_FIFO		= 5,
	EXT2_FT_SOCK		= 6,
	EXT2_FT_SYMLINK		= 7,
	EXT2_FT_MAX
};

/*
 * EXT2_DIR_PAD defines the directory entries boundaries
 *
 * NOTE: It must be a multiple of 4
 */
#define EXT2_DIR_PAD		 	4
#define EXT2_DIR_ROUND 			(EXT2_DIR_PAD - 1)
#define EXT2_DIR_REC_LEN(name_len)	(((name_len) + 8 + EXT2_DIR_ROUND) & \
					 ~EXT2_DIR_ROUND)
#define EXT2_MAX_REC_LEN		((1<<16)-1)

/* Inode dynamic state flags */
#define EXT2_STATE_NEW			0x00000001 /* inode is newly created */

/* Helper functions */
struct ext2_super_block ext2_get_super_block();
void ext2_trace_super_block(struct ext2_super_block);

void ext2_trace_group_desc(struct ext2_group_desc d);
struct ext2_group_desc ext2_get_group_desc();

void ext2_trace_inode(struct ext2_inode inode);
struct ext2_inode ext2_get_inode(int inode);
struct ext2_inode ext2_get_root_inode();
void increase_inode_size(struct ext2_inode * inode,int inode_index);
void ext2_write_inode(struct ext2_inode inode,int inode_index);

void ext2_trace_dir(struct ext2_dir_entry_2 dir);
struct ext2_dir_entry_2 ext2_get_dir_entry(struct ext2_inode inode,int index);

int inode_by_path(char * path,struct ext2_inode * inode);

int ext2_read(struct ext2_inode inode, unsigned int head);
void ext2_write(int inode_index,struct ext2_inode inode, unsigned int head,uint8_t value);

/*related globals used by r0nix*/
int ext2_block_size;
