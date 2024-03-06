## [Django MultiValueDict](https://www.cnblogs.com/dbf-/p/13525445.html)

```py
from django.utils.datastructures import MultiValueDict
```

MultiValueDict 是 dict 的子类，可以处理一个 key 对应多个 value 的情况

## 结构

### 构造函数

```py
def __init__(self, key_to_list_mapping=())
```

虽然传给构造函数的是 value 为 list 的字典。但是 MultiValueDict 的结构并不是这样的

示例：

```py
m_dict = MultiValueDict({'a': ['1', '2'], 'b': ['1']})
print(m_dict['a'])
```

输出结果：

```undefined
2
```

并没有得到一个 list ,因为 MultiValueDict 的 `get` 方法返回的是最新的一个数据

## 方法

### get

get 用于获取一个 key 对应的最新的 value，如果没有就会返回 default

```py
get(self, key, default=None)
```

### getlist

getlist 用于获取一个 key 对应的所有 value 的列表，如果没有找到返回 default

```py
getlist(self, key, default=None)
```

### setlist

setlist 用于设置一个 key 对应的 value 列表，如果 key 已经存在则替换原来的 value 列表，如果不存在则创建新的键值对

```py
setlist(self, key, list_)
```

### setdefault

setdefault 用于初始化一个键值对，如果对应的 key 不存在就会创建一个，对应的 value 为 `[default]`

```py
setdefault(self, key, default=None)
```

示例：

```py
m_dict = MultiValueDict({'a': ['1', '2'], 'b': ['1']})
print(m_dict)
m_dict.setdefault('b')
m_dict.setdefault('c')
print(m_dict)
```

输出结果：

```python
<MultiValueDict: {'a': ['1', '2'], 'b': ['1']}>
<MultiValueDict: {'a': ['1', '2', '3'], 'b': ['1'], 'c': [None]}>
```

因为本来 `'b'` 已经存在，所以直接跳过，只初始化一个 `'c': [None]`

### setlistdefault

setlistdefault 用于初始化一个键值对，如果对应的 key 不存在就会创建一个，对应的 value 为 `default`，默认的 value 为 `[]`

```py
setlistdefault(self, key, default=None)
```

示例：

```py
m_dict = MultiValueDict({'a': ['1', '2'], 'b': ['1']})
print(m_dict)
m_dict.setlistdefault('c')
m_dict.setlistdefault('d', default_list='d')
print(m_dict)
```

输出结果：

```bash
<MultiValueDict: {'a': ['1', '2'], 'b': ['1']}>
<MultiValueDict: {'a': ['1', '2', '3'], 'b': ['1'], 'c': [], 'd': 'd'}>
```

### items & values

两个方法都会返回一个生成器
item 每次会返回一个元祖，其中包含了 key 和 key 对应的最新的 value
values 每次只会返回最新的 value

```py
m_dict = MultiValueDict({'a': ['1', '2'], 'b': ['1']})
for i in m_dict.items():
	print(i)
for i in m_dict.values():
	print(i)
```

输出结果：

```py
('a', '2')
('b', '1')
2
1
```

### lists

lists 方法会返回一个
每次返回一个元祖，其中包含 key 和 key 所对应的 value list

```py
m_dict = MultiValueDict({'a': ['1', '2'], 'b': ['1']})
for i in m_dict.lists():
	print(i)
```

输出结果：

```py
('a', ['1', '2'])
('b', ['1'])
```

### dict

dict 方法会将 MultiValueDict 转为 Dict，Dict 的 value 为 MultiValueDict 对应 key 的 value 中最新的

### update

update 用于更新 MultiValueDict，会将用于更新的字典的值添加到对应 key 的 value 后
用于更新的字典可以是 MultiValueDict 也可以是普通字典类型

```py
m_dict = MultiValueDict({'a': ['1', '2'], 'b': ['1']})
update_dict = MultiValueDict({'a': ['1', '3'], 'c': ['1']})
m_dict.update(update_dict)
print(m_dict)
```

输出结果：

```bash
<MultiValueDict: {'a': ['1', '2', '1', '3'], 'b': ['1'], 'c': ['1']}>
```