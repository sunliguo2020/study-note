Physical Structure

The physical structure of Ext2 filesystems has been strongly influenced by the layout of the BSD filesystem. A filesystem is made up of block groups. Block groups are analogous to BSD FFS's cylinder groups. However, block groups are not tied to the physical layout of the blocks on the disk, since modern drives tend to be optimized for sequential access and hide their physical geometry to the operating system.

,---------+---------+---------+---------+---------,
| Boot    | Block   | Block   |   ...   | Block   |
| sector  | group 1 | group 2 |         | group n |
`---------+---------+---------+---------+---------'

Each block group contains a redundant copy of crucial filesystem control informations (superblock and the filesystem descriptors) and also contains a part of the filesystem (a block bitmap, an inode bitmap, a piece of the inode table, and data blocks). The structure of a block group is represented in this table:

,---------+---------+---------+---------+---------+---------,
| Super   | FS        | Block     | Inode   | Inode   | Data    |
| block    | desc.   | bitmap  | bitmap  | table   | blocks  |
`---------+---------+---------+---------+---------+---------'
超级块 组描述符 块位图 索引节点位图 索引结点表  数据块

Using block groups is a big win in terms of reliability: since the control structures are replicated in each block group, it is easy to recover from a filesystem where the superblock has been corrupted. This structure also helps to get good performances: by reducing the distance between the inode table and the data blocks, it is possible to reduce the disk head seeks during I/O on files.

In Ext2fs, directories are managed as linked lists of variable length entries. Each entry contains the inode number, the entry length, the file name and its length. By using variable length entries, it is possible to implement long file names without wasting disk space in directories. 




