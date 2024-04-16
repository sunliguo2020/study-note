### mysql某列类型为json时
```
SELECT * FROM get_hisinformation WHERE JSON_EXTRACT(data, '$.data') = '[]' and is_delete = 0;


UPDATE get_hisinformation   
SET is_delete = 1   
WHERE JSON_EXTRACT(data, '$.data') = '[]' AND is_delete = 0;


```