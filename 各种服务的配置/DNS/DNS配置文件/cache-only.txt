options {
	directory "/var/named";
	dump-file "/var/named/data/cache_dump.db";
	statistics-file "/var/named/data/named_stats.txt";
	version "4.9.11";
forward only;
	forwarders {
		192.168.200.202;
	};
};
include "/etc/rndc.key";
