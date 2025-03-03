#统计某列数据相同项最多的前几个

```sql
SELECT md5sum, COUNT(*) as count
FROM guhua
GROUP BY md5sum
ORDER BY count DESC
LIMIT 3;
```



# ｍysql查询字段类型为json数据

是的，你的 `WHERE` 条件可能写错了。问题出在 `data` 字段的查询方式上。`data` 字段是 `JSONField`，直接使用 `=` 进行比较时，MySQL 会将其视为字符串比较，而不是 JSON 结构比较。

### **问题分析**

- `data` 字段是 `JSONField`，存储的是 JSON 数据。
- 在 MySQL 中，`JSONField` 的查询需要使用 JSON 函数（如 `JSON_CONTAINS` 或 `JSON_EXTRACT`）来提取或比较 JSON 数据。
- 直接使用 `=` 比较时，MySQL 会将 JSON 数据转换为字符串进行比较，这可能导致查询失败。

---

### **正确查询方式**
以下是几种正确的查询方式：

#### **方法 1：使用 `JSON_CONTAINS`**
`JSON_CONTAINS` 用于检查 JSON 文档中是否包含指定的值。

```sql
SELECT * 
FROM get_getdaglperson 
WHERE JSON_CONTAINS(data, '{"errno": 1}') 
LIMIT 1;
```

- 该查询会检查 `data` 字段中是否包含 `{"errno": 1}`。

---

#### **方法 2：使用 `JSON_EXTRACT`**
`JSON_EXTRACT` 用于提取 JSON 文档中的特定字段值。

```sql
SELECT * 
FROM get_getdaglperson 
WHERE JSON_EXTRACT(data, '$.errno') = 1 
LIMIT 1;
```

- `$.errno` 表示提取 `data` 字段中的 `errno` 值。
- 该查询会检查 `data` 字段中的 `errno` 是否等于 `1`。

---

#### **方法 3：使用 `->` 或 `->>` 操作符**
MySQL 提供了 `->` 和 `->>` 操作符来简化 JSON 字段的提取和比较。

- `->`：提取 JSON 字段的值（返回 JSON 格式）。
- `->>`：提取 JSON 字段的值并转换为字符串。

```sql
SELECT * 
FROM get_getdaglperson 
WHERE data->'$.errno' = 1 
LIMIT 1;
```

或者：

```sql
SELECT * 
FROM get_getdaglperson 
WHERE data->>'$.errno' = '1' 
LIMIT 1;
```

---

### **注意事项**
1. **JSON 路径语法**：
   - `$.errno`：表示提取 `errno` 字段的值。
   - `$.data`：表示提取 `data` 字段的值。

2. **数据类型匹配**：
   - 如果 `errno` 是整数，直接比较 `1`。
   - 如果 `errno` 是字符串，比较 `'1'`。

3. **性能问题**：
   - 如果 `data` 字段的数据量很大，建议在 `errno` 字段上添加索引（如果可能）。
   - 如果无法添加索引，可以考虑将 `errno` 提取到单独的字段中。

---

### **示例**
假设 `data` 字段的值为：
```json
{"errno": 1, "errmsg": "暂无数据！", "data": ""}
```

#### **查询 `errno` 为 1 的记录**
```sql
SELECT * 
FROM get_getdaglperson 
WHERE JSON_EXTRACT(data, '$.errno') = 1 
LIMIT 1;
```

#### **查询 `errmsg` 为 "暂无数据！" 的记录**
```sql
SELECT * 
FROM get_getdaglperson 
WHERE JSON_EXTRACT(data, '$.errmsg') = '暂无数据！' 
LIMIT 1;
```

---

### **总结**
- 使用 `JSON_CONTAINS`、`JSON_EXTRACT` 或 `->`/`->>` 操作符来查询 `JSONField` 字段。
- 避免直接使用 `=` 比较 JSON 数据。
- 如果查询性能较差，可以考虑优化数据结构或添加索引。

