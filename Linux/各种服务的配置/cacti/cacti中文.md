
终于找到错误日志：
/var/log/httpd/error_log


(process:115837): Pango-WARNING **: shaping failure, expect ugly output. shape-engine='PangoFcShapeEngine', font='NSimSun 9.9990234375', text='??'

(process:115837): Pango-WARNING **: failed to create cairo scaled font, expect ugly output. the offending font is 'NSimSun 9.9990234375'

(process:115837): Pango-WARNING **: font_face status is: file not found

(process:115837): Pango-WARNING **: scaled_font status is: file not found

(process:115838): Pango-WARNING **: failed to create cairo scaled font, expect ugly output. the offending font is 'NSimSun 9.9990234375'

(process:115838): Pango-WARNING **: font_face status is: file not found

(process:115838): Pango-WARNING **: scaled_font status is: file not found

(process:115838): Pango-WARNING **: shaping failure, expect ugly output. shape-engine='PangoFcShapeEngine', font='NSimSun 9.9990234375', text='??'

(process:115838): Pango-WARNING **: failed to create cairo scaled font, expect ugly output. the offending font is 'NSimSun 9.9990234375'

(process:115838): Pango-WARNING **: font_face status is: file not found

(process:115838): Pango-WARNING **: scaled_font status is: file not found


[root@localhost httpd]# locate simsun
/usr/share/fonts/chinese/simsun
/usr/share/fonts/chinese/simsun/simsun.ttc
[root@localhost httpd]# rm -f /usr/share/fonts/chinese/simsun/
rm: cannot remove ‘/usr/share/fonts/chinese/simsun/’: Is a directory
[root@localhost httpd]# rm -f /usr/share/fonts/chinese/simsun/ -r
[root@localhost httpd]# 
[root@localhost httpd]# 