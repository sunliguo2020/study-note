options {
directory "/var/named";
dump-file "/var/named/data/cache_dump.db";
statistics-file "/var/named/data/named_stats.txt";
};
include "/etc/rndc.key";
zone "." { 
	type hint;	
file "named.ca"; 
};
zone "example.com" { 
type slave;
file "slaves/example.com.zone";
masters {192.168.16.177;};
};
zone "16.168.192.in-addr.arpa" {
type slave; 
file "slaves/192.168.16.arpa"; 
masters {192.168.16.177;}; 
};
