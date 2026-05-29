find / | cpio -o >test.cpio
cpio -it<test.cpio
cpio -id<test.cpio

tar -czvf root@expa:/var/home/home.tar /home
dump -0uf root@exap:/var/home.dump /home
