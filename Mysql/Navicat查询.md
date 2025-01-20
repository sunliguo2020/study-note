#统计某列数据相同项最多的前几个

```sql
SELECT md5sum, COUNT(*) as count
FROM guhua
GROUP BY md5sum
ORDER BY count DESC
LIMIT 3;
```

