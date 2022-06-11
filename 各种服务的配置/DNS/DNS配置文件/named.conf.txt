options {
        directory "/var/named";
        dump-file "/var/named/data/cache_dump.db";
        statistics-file  "/var/named/data/named_stats.txt";
};
include "/etc/rndc.key";

zone "." { 
	type hint;	
file "named.ca"; 
};


zone "example.com" { 
	type master;
	file "example.com.zone"; 
allow-transfer {
192.168.1.177;
192.168.7.17;
};
};

zone "200.168.192.in-addr.arpa" {
	type master; 
	file "192.168.200.arpa"; 
allow-transfer {
192.168.1.177;
192.168.7.17;
};
};
