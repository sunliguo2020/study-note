### 1、jsonpath安装

```python
pip install jsonpath
```

### 2、jsonpath提取数据的方法

```python
from jsonpath import jsonpath

result = jsonpath(a,'jsonpath语法故障字符串')
```

### 3、jsonpath语法规则

| JsonPath | 描述                                                         |
| -------- | ------------------------------------------------------------ |
| $        | 根节点 查询根节点                                            |
| @        | 现行节点  查询当前节点                                       |
| .or[]    | 取子节点                                                     |
| n/a      | 取父节点，jsonpath为支持                                     |
| ..       | 就是不管位置，选择所有符合条件的数据  递归搜索节点           |
| *        | 匹配所有元素节点                                             |
| n/a      | 根据属性访问，json不支持，因为json是个key-value递归结构，不需要数属性访问 |
| []       | 迭代器标示(可以在里边做简单的迭代操作，如数组下标，根据内容选值等) |
| [,]      | 支持迭代器中做多选                                           |
| ?()      | 支持过滤操作                                                 |
| ()       | 支持表达式计算                                               |
| n/a      | 分组，JsonPath不支持                                         |

### 4、jsonpath使用实例

```python
book_dict = { 
  "store": {
    "book": [ 
      { "category": "reference",
        "author": "Nigel Rees",
        "title": "Sayings of the Century",
        "price": 8.95
      },
      { "category": "fiction",
        "author": "Evelyn Waugh",
        "title": "Sword of Honour",
        "price": 12.99
      },
      { "category": "fiction",
        "author": "Herman Melville",
        "title": "Moby Dick",
        "isbn": "0-553-21311-3",
        "price": 8.99
      },
      { "category": "fiction",
        "author": "J. R. R. Tolkien",
        "title": "The Lord of the Rings",
        "isbn": "0-395-19395-8",
        "price": 22.99
      }
    ],
    "bicycle": {
      "color": "red",
      "price": 19.95
    }
  }
}

from jsonpath import jsonpath
print(jsonpath(book_dict,'$..author')) #如果取不到返回false

```

| JsonPath               | Result                  |
| ---------------------- | ----------------------- |
| $.store.book[*].author | store中的所有的book作者 |
| $…author               | 所有的作者              |
| $.store.*              | store下的所有元素       |
| $.store…price          | store中的所有价钱       |
| $…book[2]              | 第三本书                |
| $…book[(@.length-1)]   | 最后一本书              |
| $…book[0,1]            | 取前两本书              |
| $…book[?(@.isbn)]      | 获取有jsbn的所有数      |
| $…book[?(@.price<10)]  | 获取价格大于10          |
| $…*                    | 匹配所有数据            |